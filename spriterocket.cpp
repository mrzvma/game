#include "spriterocket.h"

//=============================================================
SpriteRocket::SpriteRocket(pTFuncSpriteBase pFMove, ResurseImages *pResImages, QString nameSprite, int speed, float x0, float y0,
                           int levelLive, int levelPower)
                          : BaseSprite(pResImages, nameSprite, speed, x0, y0, levelLive, levelPower)
{
    mTypeSprite=ROCKET;
    pFuncMove=pFMove;
    mX0=mX=x0-pDataImages->mWidth/2;
    mY0=mY=y0-pDataImages->mHeight;
    //qDebug()<<this<<"SpriteRocket(QString ImageFilePath, QString MaskFilePath, double speed, double x0, double y0, int widgt, int heigt)";

}
//=============================================================
void SpriteRocket::move()
{
    (this->*pFuncMove)();
    //y=y-frameClock;
    //if(y<mHeightSceneMin) mState=DEATH;
}
//=============================================================
void SpriteRocket::setParamScene(const int width, const int height)
{
    mWidthSceneMin=0-pDataImages->mWidth;
    mWidthSceneMax=width;
    mHeightSceneMin=0-pDataImages->mHeight;
    mHeightSceneMax=height;
}
//=============================================================
SpriteRocket::~SpriteRocket()
{
    //qDebug()<<this<<"~SpriteRocket()";
}
//=============================================================
bool SpriteRocket::contact()
{
    double delta=0;
    double deltaSize=0;
    bool shot=false;
    QLinkedList<BaseSprite*>::Iterator it;
    switch (mState)
    {
    case LIVE:
        it=pSceneBuffer->lpSprites.begin();
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
                        delta=qAbs(2 * ((*it)->mX - mX) + (*it)->pDataImages->mWidth - pDataImages->mWidth);
                        deltaSize=((*it)->pDataImages->mWidth+pDataImages->mWidth)/4*3;
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
                                 pSceneBuffer->addToCountPanelElement(PanelElement::SCORE, (*it)->mScore);
                                 pSceneBuffer->setCountToTextPanelElement(PanelElement::SCORE);
                            }
                            mState=STRICKEN;
                            pDataImages=pResurseImages->getDataImages("EXPLOSION");
                            mTimeOutAnimation=0;
                            mCurImageHorizontal=0;
                            mCurImageVertical=0;
                            pFuncMove=&BaseSprite::fMoveStand;
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
