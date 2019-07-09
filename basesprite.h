#ifndef BASESPRITE_H
#define BASESPRITE_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <qmath.h>
#include "resurseimages.h"

class SceneBuffer;
class BaseSprite : public QObject
{
    Q_OBJECT
public:
    typedef void (BaseSprite::* pTFuncSpriteBase)();
    ResurseImages *pResurseImages;
    DataImages *pDataImages;
    enum TypeSprite{NONE, ENEMY, CONTROL, ROCKET};
    enum StateSprite{LIVE, STRICKEN, DEATH};
    BaseSprite(ResurseImages *pResImages=new ResurseImages(), QString nameSprite="", int speed=1,
               float x0=0, float y0=0, int levelLive=1, int levelPower=1);
    virtual ~BaseSprite();
    DataImages* getDataImage();
    virtual void move()=0;
    virtual void setParamScene(const int width, const int height)=0;
    virtual bool contact()=0;
    void setDataImage(QString nameSprite);
    virtual void setFrameClock(const int frameClock) {mFrameClock=(float)mSpeed/frameClock;}
    //float getSpeed() const {return mSpeed;}
    bool setSpriteImage(int i, int j);
    float mX0;
    float mY0;
    float mX;
    float mY;
    StateSprite mState;
    int mTimeOutAnimation;
    int mCurImageHorizontal;
    int mCurImageVertical;
    int mWidthSceneMin;
    int mHeightSceneMin;
    int mWidthSceneMax;
    int mHeightSceneMax;
    float mFrameClock;
    SceneBuffer *pSceneBuffer;
    QImage *pImage;
    TypeSprite mTypeSprite;
    pTFuncSpriteBase pFuncMove;
    int mLevelLive;
    int mLevelPower;
    int mScore;
    void fMoveLineY();
    void fMoveLineYUp();
    void fMoveStand();

protected:
    int mSpeed;

};

#include "scenebuffer.h"
#endif // BASESPRITE_H

