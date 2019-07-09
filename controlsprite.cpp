#include "controlsprite.h"


//=============================================================
ControlSprite::ControlSprite(ResurseImages *pResImages, QString nameSprite, int speed, int x0, int y0, int levelLive, int levelPower, int shotsPerSecond)
                            : BaseSprite(pResImages, nameSprite, speed, x0, y0, levelLive, levelPower)
{
    qDebug()<<this<<"ControlSprite(QString ImageFilePath, QString MaskFilePath, double speed, int x0, int y0, int widgt, int heigt)";
    m_PushedUP=false;
    m_PushedDOWN=false;
    m_PushedLEFT=false;
    m_PushedRIGTH=false;
    m_PushedFIRE=false;
    mTypeSprite=CONTROL;
    mCurImageHorizontal=3;
    mCurImageVertical=0;
    mTimeOutFireCur=0;
    mLevelLiveMax=levelLive;
    mTimeOutFire=shotsPerSecond; //shotsPerSecond количество выстрелов в секунду
    setSpriteImage(mCurImageHorizontal, mCurImageVertical);

}
//=============================================================
ControlSprite::~ControlSprite()
{
    //qDebug()<<this<<"~ControlSprite()";
}
//=============================================================
void ControlSprite::move()
{
    if(mState==LIVE)
    {
        if(m_PushedUP) mY-=mFrameClock;
        if(m_PushedDOWN) mY+=mFrameClock;
        if(m_PushedLEFT)
        {
            if(mCurImageHorizontal>0&&mTimeOutAnimation<=0)
            {
                mCurImageHorizontal--;
            }
            mX-=mFrameClock;
        }
        else
        {
            if(mCurImageHorizontal<3&&mTimeOutAnimation<=0)
            {
                mCurImageHorizontal++;
            }
        }
        if(m_PushedRIGTH)
        {
            if(mCurImageHorizontal<6&&mTimeOutAnimation<=0)
            {
                mCurImageHorizontal++;
            }
            mX+=mFrameClock;
        }
        else
        {
            if(mCurImageHorizontal>3&&mTimeOutAnimation<=0)
            {
                mCurImageHorizontal--;
            }
        }
        if(m_PushedFIRE)
        {
            if(mTimeOutFireCur<=0)
            {
                mTimeOutFireCur=mTimeOutFire;
                fire();
            }
        }
        if(mTimeOutAnimation<=0) mTimeOutAnimation=pDataImages->mTimeOutAnimation;
        else mTimeOutAnimation--;
        setSpriteImage(mCurImageHorizontal, mCurImageVertical);
        mTimeOutFireCur--;
    }
    if(mY<mHeightSceneMin) mY=mHeightSceneMin;
    if(mY>mHeightSceneMax) mY=mHeightSceneMax;
    if(mX<mWidthSceneMin) mX=mWidthSceneMin;
    if(mX>mWidthSceneMax) mX=mWidthSceneMax;
}
//=============================================================
void ControlSprite::setParamScene(const int width, const int height)
{
    mWidthSceneMin=0;
    mWidthSceneMax=width-pDataImages->mWidth;
    mHeightSceneMin=0;
    mHeightSceneMax=height-pDataImages->mHeight;
}
//=============================================================
bool ControlSprite::eventFilter(QObject *object, QEvent *event)
{
    if (object == pWidget && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //qDebug()<<keyEvent->nativeScanCode()<<keyEvent->key()<<keyEvent->nativeVirtualKey();
        switch(keyEvent->nativeVirtualKey())
        {
        case Qt::Key_W:
            m_PushedUP=true;
            break;
        case Qt::Key_S:
            m_PushedDOWN=true;
            break;
        case Qt::Key_A:
            m_PushedLEFT=true;
            break;
        case Qt::Key_D:
            m_PushedRIGTH=true;
            break;
        case Qt::Key_Space:
            m_PushedFIRE=true;
            break;
        }
    }
    if (object == pWidget && event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch(keyEvent->nativeVirtualKey())
        {
        case Qt::Key_W:
            m_PushedUP=false;
            break;
        case Qt::Key_S:
            m_PushedDOWN=false;
            break;
        case Qt::Key_A:
            m_PushedLEFT=false;
            break;
        case Qt::Key_D:
            m_PushedRIGTH=false;
            break;
        case Qt::Key_Space:
            m_PushedFIRE=false;
            break;
        }
    }
    return false;
}
//=============================================================
void ControlSprite::fire()
{
    SpriteRocket* pSpriteRocket=new SpriteRocket(&BaseSprite::fMoveLineYUp, pResurseImages, "ROCKET", 200, mX+pDataImages->mWidth/2, mY, 10, 10);
    pSceneBuffer->addSprite(pSpriteRocket);
    //qDebug()<<pSceneBuffer->mSprites.begin()<<*(pSceneBuffer->mSprites.begin())<<pSceneBuffer->mSprites.end()<<pSceneBuffer->mSprites.size()<<"fire()";
}
//=============================================================
bool ControlSprite::contact()
{
    double delta=0;
    double deltaSize=0;
    bool shot=false;
    QLinkedList<BaseSprite*>::Iterator it=pSceneBuffer->lpSprites.begin();
    switch (mState)
    {
    case LIVE:
        while(it!=pSceneBuffer->lpSprites.end())
        {
            switch ((*it)->mTypeSprite)
            {
            case ENEMY:
                if((*it)->mState==LIVE)
                {
                    delta=qAbs(2 * ((*it)->mY - mY) + (*it)->pDataImages->mHeight - pDataImages->mHeight);
                    deltaSize=((*it)->pDataImages->mHeight+pDataImages->mHeight)/4*3;
                    if(delta<=deltaSize)
                    {
                        //qDebug()<<x<<y<<(*it)->x<<(*it)->y<<delta<<deltaH<<"Shot"<<(*it);
                        delta=qAbs(2 * ((*it)->mX - mX) + (*it)->pDataImages->mWidth - pDataImages->mWidth);
                        deltaSize=((*it)->pDataImages->mHeight+pDataImages->mHeight)/4*3;
                        if(delta<=deltaSize)
                        {
                            (*it)->mLevelLive-=mLevelPower;
                            if( ((*it)->mLevelLive)<=0 )
                            {
                                (*it)->mState=STRICKEN;
                                (*it)->pDataImages=(*it)->pResurseImages->getDataImages("EXPLOSION");
                                (*it)->mTimeOutAnimation=0;
                                (*it)->mCurImageHorizontal=0;
                                (*it)->mCurImageVertical=0;
                                (*it)->pFuncMove=&BaseSprite::fMoveStand;
                                pSceneBuffer->mScore+=(*it)->mScore;
                            }
                            mLevelLive-=(*it)->mLevelPower;
                            //qDebug()<<mLevelLive;
                            pSceneBuffer->scalePanelProcessBar(PanelElement::LIVE_LEVEL, mLevelLive);
                            pSceneBuffer->addToCountPanelElement(PanelElement::SCORE, (*it)->mScore);
                            if(mLevelLive<=0)
                            {
                                mState=STRICKEN;
                                pDataImages=pResurseImages->getDataImages("EXPLOSION");
                                mTimeOutAnimation=0;
                                mCurImageHorizontal=0;
                                mCurImageVertical=0;
                                pFuncMove=&BaseSprite::fMoveStand;
                            }
                            shot=true;
                        }
                    }
                }
                break;
            default:
                break;
            }
            ++it;
        }
        break;
    case STRICKEN:
        if( mTimeOutAnimation == 0 )
        {
            if( mCurImageHorizontal < pDataImages->mCountHorizontal )
            {
                //qDebug()<<"strickenSprite"<<mCurImageHorizontal<<mTimeOutAnimation;
                setSpriteImage(mCurImageHorizontal, mCurImageVertical);
                mCurImageHorizontal++;
                mTimeOutAnimation=pDataImages->mTimeOutAnimation;
            }
            else mState=DEATH;
        }
        else
        {
            mTimeOutAnimation--;
        }
        break;
    default:
        break;
    }
    return shot;
}
//=============================================================
void ControlSprite::setFrameClock(const int frameClock)
{
    mFrameClock=(float)mSpeed/frameClock;
    mTimeOutFire=frameClock/mTimeOutFire;
}
//=============================================================
