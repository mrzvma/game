#include "spriteenemy.h"

SpriteEnemy::SpriteEnemy(pTFuncSpriteEnemy pMove, float ampletude, float period, ResurseImages *pResImages, QString nameSprite, int speed,
                         float x0, float y0, int levelLive, int levelPower)
                        : BaseSprite(pResImages, nameSprite, speed, x0, y0, levelLive, levelPower)
{
    //qDebug()<<this<<"SpriteEnemy(double ampletude, double period, QString ImageFilePath, QString MaskFilePath, double speed, double x0, double y0, int width, int height)";
    mAngel_x=90;
    mAngel_y=90;
    mAmpletude=ampletude;
    mPeriod=period;
    pFuncMove=(pTFuncSpriteBase)pMove;
    mTypeSprite=ENEMY;
    mStateFunc=0;
}

//=============================================================
void SpriteEnemy::move()
{
    (this->*pFuncMove)();
}
//=============================================================
void SpriteEnemy::setParamScene(const int width, const int height)
{
    mWidthSceneMin=0-pDataImages->mWidth-mAmpletude;
    mWidthSceneMax=width+mAmpletude;
    mHeightSceneMin=0-pDataImages->mHeight-mAmpletude;
    mHeightSceneMax=height+mAmpletude;
}
//=============================================================
SpriteEnemy::~SpriteEnemy()
{
    //qDebug()<<this<<"~SpriteEnemy()";
}
//=============================================================
void SpriteEnemy::fMoveOrbit_1()
{
                mX=mX0+mAmpletude*qCos(qDegreesToRadians(mAngel_x));
                mY=mY0+mAmpletude*qSin(qDegreesToRadians(mAngel_x));
                mY0+=2*mFrameClock;
                mAngel_x=(int)(mAngel_x+mPeriod*mFrameClock)%360;
                if(mY0>mHeightSceneMax) mState=DEATH;
                //qDebug()<<x<<y;
}
//=============================================================
void SpriteEnemy::fMoveOrbit_2()
{
                mX=mX0+mAmpletude*qCos(qDegreesToRadians(mAngel_x));
                mY0=mY+=2*mFrameClock;
                mAngel_x=(int)(mAngel_x+mPeriod*mFrameClock)%360;
                if(mY0>mHeightSceneMax) mState=DEATH;
                //qDebug()<<x<<y;
}
//=============================================================
void SpriteEnemy::fMoveComplex_1()
{
    if(mY0<=100&&mStateFunc<2)
    {
        mStateFunc=1;
        fMoveLineY();
        return;
    }
    if(mY0<=200&&mStateFunc<3)
    {

        mStateFunc=2;
        fMoveOrbit_2();
        //qDebug()<<x<<y<<x0<<y0<<mAngel_x;
        return;
    }
    if(mY0<=300&&mStateFunc<4)
    {
        if(mStateFunc==2)
        {
            mX0=mX;
            mY0=mY-mAmpletude;
            mAngel_x=90;
            mStateFunc=3;
        }
        fMoveOrbit_1();
        //qDebug()<<x<<y<<x0<<y0<<mAngel_x;
        return;
    }
    if(mY0<=400&&mStateFunc<5)
    {
        if(mStateFunc==3)
        {
            mX0=mX;
            mY0=mY+mAmpletude;
            mAngel_x=90;
            mStateFunc=4;
        }
        fMoveOrbit_2();
        return;
    }
    if(mY0>400)
    {
        mStateFunc=5;
        fMoveLineY();
        return;
    }
}
//=============================================================
bool SpriteEnemy::contact()
{
    bool shot=false;
    switch (mState)
    {
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
QVector<SpriteEnemy::pTFuncSpriteEnemy> SpriteEnemy::vpTFuncSpriteEnemy(QVector<SpriteEnemy::pTFuncSpriteEnemy> ()
                                                                        <<&SpriteEnemy::fMoveOrbit_1
                                                                        <<&SpriteEnemy::fMoveOrbit_2
                                                                        <<&SpriteEnemy::fMoveComplex_1
                                                                        <<&BaseSprite::fMoveLineY);


