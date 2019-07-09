#include "resurseimages.h"

ResurseImages::ResurseImages()
{

}
//=============================================================
ResurseImages::~ResurseImages()
{
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        QVector<QVector<QImage*>>::Iterator itVVP=it->vvpImage.begin();
        while(itVVP!=it->vvpImage.end())
        {
            QVector<QImage*>::Iterator itVP=itVVP->begin();
            while(itVP!=itVVP->end())
            {
                //qDebug()<<it->mName<<"delete"<<*itVP;
                delete itVP;
                itVP=itVVP->erase(itVP);
            }
            //qDebug()<<it->mName<<"erase_itVVP"<<itVVP;
            itVVP=it->vvpImage.erase(itVVP);
        }
        //qDebug()<<it->mName<<"erase_it"<<it;
        it=vDataImages.erase(it);
    }
}
//=============================================================
void ResurseImages::loadImages()
{
    addImage("CONTROL", ":/images/3.png", 70, 70);
    addImage("ENEMY_1", ":/images/r8down.png", 80, 80);
    addImage("ENEMY_2", ":/images/S2down.png", 80, 80);
    addImage("ENEMY_3", ":/images/5.png", 40, 40);
    addImage("ROCKET", ":/images/k4.png", 60, 60);
    addImage("EXPLOSION", ":/images/exp.png", 40, 40, 13, 1, 0.04);
    addImage("T-50", ":/images/T-50.png", 60, 90, 7, 1, 0.08);
    addImage("BURAN", ":/images/buran.png", 60, 90, 7, 1, 0.08);
    addImage("LIVEFRAME", ":/images/LiveEmpty.png", 400, 80);
    addImage("LIVEFRAME2", ":/images/LiveEmpty2.png", 400, 80);
    addImage("LIVELINE", ":/images/LiveLine.png", 312, 80);
}
//=============================================================
void ResurseImages::addImage(QString name, QString imageName, int width, int height,
                             int countHorizontal, int countVertical, float TimeOutAnimation)
{
    TimeOutAnimation=TimeOutAnimation*1000;
    QImage *pLoadImage=new QImage(imageName);
    *pLoadImage=pLoadImage->scaled(width*countHorizontal, height*countVertical);
    QVector<QVector<QImage*>> tmpVVP;
    QImage* pTmpImage;
    for(int i=0; i<countVertical; i++)
    {
        QVector<QImage*> tmpVP;
        for(int j=0; j<countHorizontal; j++)
        {
            pTmpImage=new QImage(pLoadImage->copy(j*width, i*height, width, height));
            tmpVP.append(pTmpImage);
        }
        tmpVVP.append(tmpVP);
    }
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        if(it->mName==name)
        {
            delete it->pImage;
            it->pImage=pLoadImage;
            it->mWidth=pLoadImage->width();
            it->mHeight=pLoadImage->height();
            it->mCountHorizontal=countHorizontal;
            it->mCountVertical=countVertical;
            it->mTimeOutAnimation=TimeOutAnimation;
            return;
        }
        ++it;
    }
    vDataImages.append(DataImages()={name, pLoadImage, tmpVVP, width, height, countHorizontal, countVertical, (int)TimeOutAnimation});
}
//=============================================================
void ResurseImages::addImage(QString name, QImage *image, int width, int height,
                             int countHorizontal, int countVertical, float TimeOutAnimation)
{
    TimeOutAnimation=TimeOutAnimation*1000;
    QImage *pLoadImage=new QImage(image->scaled(width*countHorizontal, height*countVertical));//Надо проверить объект после выхода из функции;
    QVector<QVector<QImage*>> tmpVVP;
    tmpVVP.reserve(countVertical);
    QImage* pTmpImage;
    for(int i=0; i<countHorizontal; i++)
    {
        QVector<QImage*> tmpVP;
        tmpVP.reserve(countHorizontal);
        for(int j=0; j<countVertical; j++)
        {
            pTmpImage=new QImage(pLoadImage->copy(i, j, width, height));
            tmpVP.append(pTmpImage);
        }
        tmpVVP.append(tmpVP);
    }
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        if(it->mName==name)
        {
            delete it->pImage;
            it->pImage=pLoadImage;
            it->mWidth=pLoadImage->width();
            it->mHeight=pLoadImage->height();
            it->mCountHorizontal=countHorizontal;
            it->mCountVertical=countVertical;
            it->mTimeOutAnimation=TimeOutAnimation;
            return;
        }
        ++it;
    }
    vDataImages.append(DataImages()={name, pLoadImage, tmpVVP, width, height, countHorizontal, countVertical, (int)TimeOutAnimation});
}
//=============================================================
QImage* ResurseImages::getImageFromName(QString name)
{
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        if(it->mName==name)
        {
            return it->pImage;
        }
        ++it;
    }
    return new QImage();
}
//=============================================================
DataImages* ResurseImages::getDataImages(QString nameSprite)
{
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        if(it->mName==nameSprite) return it;
        ++it;
    }
    return new DataImages();
}
//=============================================================
void ResurseImages::syncTimeOutAnimation(int timeOut)
{
    QVector<DataImages>::Iterator it=vDataImages.begin();
    while(it!=vDataImages.end())
    {
        it->mTimeOutAnimation=it->mTimeOutAnimation/timeOut;
        ++it;
    }
}
//=============================================================
QImage ResurseImages::getUnitImage(const QString name, int row, int col)
{
    DataImages *pDataImages;
    pDataImages=getDataImages(name);
    if(row>=pDataImages->mCountHorizontal||col>=pDataImages->mCountVertical) return QImage();
    return pDataImages->pImage->copy(row*pDataImages->mWidth, col*pDataImages->mHeight, pDataImages->mWidth, pDataImages->mHeight);
}
//=============================================================
QVector<DataImages> ResurseImages::vDataImages;
