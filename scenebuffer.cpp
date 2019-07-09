#include "scenebuffer.h"

//=============================================================
SceneBuffer::SceneBuffer(ResurseImages *pResImages, Widget *widget, int width, int height, int frame)
{
    mWidth=width;
    mHeight=height;
    mHeightPanel=height/8;
    mSizeFont=mHeightPanel*4/11;
    mRow1=(mHeightPanel-2*mSizeFont)/3;
    mRow2=2*mRow1+mSizeFont;
    mColumn1=width/100;
    mColumn4=width*3/8+mColumn1;
    mHeightScene=height-mHeightPanel;
    pLabel = new QLabel;
    pLabelPanel = new QLabel;
    pVBL = new QVBoxLayout;
    pPainter = new QPainter();
    pPanel=new QImage(width, mHeightPanel, QImage::Format_RGB32);
    pPanelBackground = new QImage(width, mHeightPanel, QImage::Format_RGB32);
    pScene = new QImage(width, height, QImage::Format_RGB32);    
    pBackground = new QImage(width, mHeightScene, QImage::Format_RGB32);
    pPanelBackground->load(":/images/panel.png");
    pBackground->load(":/images/space4.jpg");
    *pScene = pScene->scaled(width, mHeightScene);
    *pBackground = pBackground->scaled(width, mHeightScene);
    *pPanelBackground=pPanelBackground->scaled(width, mHeightPanel);
    mTimeOut = 1000/frame;
    mFrame=frame; //Частота кадров в секунду.
    debug=0;
    pResurseImages=pResImages;
    PanelElement *pPanelElement;
    PanelElemProgressBar *pPanelElemProgressBar;
    pPanelElement=new PanelElement(pPanelBackground, pResurseImages, "BURAN", PanelElement::SHIP, PanelElement::IMAGE, mColumn1, mRow1, 0, mHeightPanel-2*mRow1, 3, 0);
    pPanelElement->paint();
    mColumn2=2*mRow1+pPanelElement->mWidth;
    mColumn3=width*2/8+mColumn1;
    pPanelElement->setDataElement("LEVEL:", PanelElement::GAME_LEVEL_TEXT, PanelElement::TEXT, mColumn3, mRow1, 0, mSizeFont);
    pPanelElement->paint();
    pPanelElement->setDataElement("1", PanelElement::GAME_LEVEL, PanelElement::TEXT, mColumn4, mRow1, 0, mSizeFont);
    pPanelElement->setContext(pPanel);
    addPanelElement(pPanelElement);
    pPanelElement=new PanelElement(pPanelBackground, pResurseImages, "SCORE:", PanelElement::SCORE_TEXT, PanelElement::TEXT, mColumn3, mRow2, 0, mSizeFont);
    pPanelElement->paint();
    pPanelElement->setDataElement("0", PanelElement::SCORE, PanelElement::TEXT, mColumn4, mRow2, 0, mSizeFont);
    pPanelElement->setContext(pPanel);
    addPanelElement(pPanelElement);
    pPanelElemProgressBar=new PanelElemProgressBar(pPanel, pPanelBackground, pResurseImages, "LIVEFRAME", "LIVEFRAME2", "LIVELINE",
                                           PanelElement::LIVE_LEVEL, 100, 76, mColumn2, mRow1, 0, mSizeFont+mRow1);
    pPanelElemProgressBar->paintBackground();
    addPanelElement(pPanelElemProgressBar);
    pVBL->setMargin(0);
    pVBL->setSpacing(0);
    pVBL->addWidget(pLabelPanel, 0);
    pVBL->addWidget(pLabel, 1);
    widget->setLayout(pVBL);
    mScore=0;
    //qDebug() << "Конструктор SceneBuffer::SceneBuffer(int width, int height, int TimeOut)";
}
//=============================================================
SceneBuffer::~SceneBuffer()
{
    delete pBackground;
    delete pScene;
    delete pPanelBackground;
    delete pPanel;
    delete pPainter;
    delete pLabel;
    delete pLabelPanel;
    delete pVBL;
    //QDebug dbg=qDebug();
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        //dbg<<"~SceneBuffer() delete "<<*itPanel<<(*itPanel)->mNameElement<<"size lpPanelElements"<<lpPanelElements.size();
        //dbg=qDebug();
        delete *itPanel;
        itPanel=lpPanelElements.erase(itPanel);
    }
    QLinkedList<BaseSprite*>::Iterator it=lpSprites.begin();
    while(it!=lpSprites.end())
    {
        //qDebug()<<"~SceneBuffer() delete "<<*it<<(*it)->mTypeSprite<<"size lpSprites"<<lpSprites.size();
        delete *it;
        it=lpSprites.erase(it);
    }
    //qDebug() << "Деструктор SceneBuffer::~SceneBuffer()";
}
//=============================================================
void SceneBuffer::setTimeOut(int TimeOut)
{
    mTimeOut=TimeOut;
}
//=============================================================
void SceneBuffer::start()
{
    oTime.start();
    oTimer.singleShot(mTimeOut, this, SLOT(start()));    
    moveSprites();
    //qDebug()<<"Время подготовки сцены:"<<oTime.elapsed()<<"мсек"<<lpSprites.size();
}
//=============================================================
void SceneBuffer::setLabel(QLabel* pLabel)
{
    SceneBuffer::pLabel=pLabel;
}
//=============================================================
void SceneBuffer::addSprite(BaseSprite *pBaseSprite)
{

    pBaseSprite->setFrameClock(mFrame); //Скорость изменения движения в 1 кадр
    pBaseSprite->setParamScene(mWidth, mHeightScene);
    pBaseSprite->pSceneBuffer=this;
    //if (pBaseSprite->mTypeSprite==BaseSprite::CONTROL) scalePanelProcessBar(PanelElement::LIVE_LEVEL, pBaseSprite->mLevelLive);
    lpSprites.append(pBaseSprite);
}
//=============================================================
bool SceneBuffer::deleteSprite(BaseSprite *pBaseSprite)
{
    //qDebug()<<pBaseSprite->mTypeSprite<<lpSprites.begin()<<lpSprites.end()<<lpSprites.size()<<"deleteSprite";
    if(lpSprites.removeOne(pBaseSprite))
    {
        delete pBaseSprite;
        return true;
    }
    qDebug()<<"NO deleteSprite";
    return false;
}
//=============================================================
void SceneBuffer::paintSprites()
{
    *pPanel=*pPanelBackground;
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        (*itPanel)->paint();
        ++itPanel;
    }
    pLabelPanel->setPixmap(QPixmap::fromImage(*pPanel, Qt::AutoColor));
    *pScene = *pBackground;
    pPainter->begin(pScene);
    QLinkedList<BaseSprite*>::Iterator it=lpSprites.begin();
    while(it!=lpSprites.end())
    {
        pPainter->drawImage((*it)->mX, (*it)->mY, *((*it)->pImage));
        ++it;
    }
    pPainter->end();
    pLabel->setPixmap(QPixmap::fromImage(*pScene,Qt::AutoColor));
}
//=============================================================
void SceneBuffer::moveSprites()
{
    QLinkedList<BaseSprite*>::Iterator it=lpSprites.begin();
    while(it!=lpSprites.end())  //Обработка движений
    {
        //qDebug()<<mSprites.begin()<<*(mSprites.begin())<<mSprites.end()<<it<<mSprites.size()<<"moveSprite()1";
        (*it)->move();
        ++it;
    }
    it=lpSprites.begin();
    while(it!=lpSprites.end())  //Обработка столкновений
    {
        (*it)->contact();
        ++it;
    }
    it=lpSprites.begin();
    while(it!=lpSprites.end())  //Обработка состояний
    {
        switch ( (*it)->mState )
        {
        case BaseSprite::DEATH:
            qDebug()<<*(it)<<lpSprites.size()<<"deleteSprite";
            delete *it;
            it=lpSprites.erase(it);
            break;
        default:
            ++it;
            break;
        }
    }
    moveImageBackground();
    paintSprites();
    debug++;
}
//=============================================================
int SceneBuffer::getTimeOut()
{
    return mTimeOut;
}
//=============================================================
void SceneBuffer::addPanelElement(PanelElement *pPanelElement)
{
    lpPanelElements.append(pPanelElement);
}
//=============================================================
bool SceneBuffer::setTextPanelElement(PanelElement::NamePanelElement nameElement, QString text)
{
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        if(nameElement==(*itPanel)->mNameElement)
        {
            (*itPanel)->mText=text;
            return true;
        }
        ++itPanel;
    }
    return false;
}
//=============================================================
bool SceneBuffer::addToCountPanelElement(PanelElement::NamePanelElement nameElement, int number)
{
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        if(nameElement==(*itPanel)->mNameElement)
        {
            (*itPanel)->mCount+=number;
            return true;
        }
        ++itPanel;
    }
    return false;
}
//=============================================================
bool SceneBuffer::setCountToTextPanelElement(PanelElement::NamePanelElement nameElement)
{
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        if(nameElement==(*itPanel)->mNameElement)
        {
            (*itPanel)->mText=QString::number((*itPanel)->mCount);
            return true;
        }
        ++itPanel;
    }
    return false;
}
//=============================================================
bool SceneBuffer::scalePanelProcessBar(PanelElement::NamePanelElement nameElement, int number)
{
    QLinkedList<PanelElement*>::Iterator itPanel=lpPanelElements.begin();
    while(itPanel!=lpPanelElements.end())
    {
        if(nameElement==(*itPanel)->mNameElement && (*itPanel)->mTypeElement==PanelElement::PROGRESS_IMAGE)
        {
            PanelElemProgressBar *ptr;
            ptr=dynamic_cast<PanelElemProgressBar*>(*itPanel);
            ptr->mCount=number*(ptr->mScaleProcess);
            //qDebug()<<number<<ptr->mCount;
            ptr->setCurImageProcess();
            return true;
        }
        ++itPanel;
    }
    return false;
}
//=============================================================
void SceneBuffer::moveImageBackground()
{
    pPainter->begin(pBackground);
    pPainter->drawImage(0, 0, pBackground->copy(0, pBackground->height()-1, pBackground->width(), 1));
    pPainter->drawImage(0, 1, pBackground->copy(0, 0, pBackground->width(), pBackground->height()-1));
    pPainter->end();
}
//=============================================================
