#include "basesprite.h"

//=============================================================
BaseSprite::BaseSprite(ResurseImages *pResImages, QString nameSprite, int speed, float x0, float y0, int levelLive, int levelPower)
{
    //qDebug()<<"baseSprite(QString ImageFilePath, QString MaskFilePath, double speed, int x0, int y0, int width, int height)";
    mX=mX0=x0;
    mY=mY0=y0;
    mSpeed=speed; //Скорость 1 пиксель в сеунду.
    mWidthSceneMin=0;
    mHeightSceneMin=0;
    mWidthSceneMax=0;
    mHeightSceneMax=0;
    pResurseImages=pResImages;
    pDataImages=pResurseImages->getDataImages(nameSprite);
    mCurImageHorizontal=0;
    mCurImageVertical=0;
    mTimeOutAnimation=pDataImages->mTimeOutAnimation;
    setSpriteImage(mCurImageHorizontal, mCurImageVertical);
    mState=LIVE;
    mTypeSprite=NONE;
    mLevelLive=levelLive;
    mLevelPower=levelPower;
    mScore=levelLive;
}
//=============================================================
BaseSprite::~BaseSprite()
{
    //qDebug() << "~baseSprite()";
}
//=============================================================
DataImages* BaseSprite::getDataImage()
{
return pDataImages;
}
//=============================================================
void BaseSprite::setDataImage(QString nameSprite)
{
    pDataImages=pResurseImages->getDataImages(nameSprite);
}
//=============================================================
void BaseSprite::fMoveLineY()
{
    mY=mY0=mY+4*mFrameClock;
    if(mY>mHeightSceneMax) mState=DEATH; //pSceneBuffer->deleteSprite(pBaseSprite);
}
//=============================================================
bool BaseSprite::setSpriteImage(int i, int j)
{
    if(i>=pDataImages->mCountHorizontal||j>=pDataImages->mCountVertical) return false;
    pImage=pDataImages->vvpImage.at(j).at(i);
    //qDebug()<<&(*pImage);
    return true;
}
//=============================================================
void BaseSprite::fMoveStand()
{

}
//=============================================================
void BaseSprite::fMoveLineYUp()
{
    mY=mY0=mY-mFrameClock;
    if( mY < (mHeightSceneMin-pDataImages->mHeight) ) mState=DEATH;
}
//=============================================================
