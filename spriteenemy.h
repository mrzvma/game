#ifndef SPRITEENEMY_H
#define SPRITEENEMY_H

#include <QObject>
#include "basesprite.h"


class SpriteEnemy : public BaseSprite
{

public:
    typedef void (SpriteEnemy::* pTFuncSpriteEnemy)();
    float mAmpletude;
    float mPeriod;
    float mAngel_x;
    float mAngel_y;
    static QVector<pTFuncSpriteEnemy> vpTFuncSpriteEnemy;
    SpriteEnemy(pTFuncSpriteEnemy pMove, float ampletude=0, float period=0, ResurseImages *pResImages=new ResurseImages(),
                QString nameSprite="", int speed=1, float x0=0, float y0=0, int levelLive=1, int levelPower=1);
    virtual void move();
    virtual void setParamScene(const int width, const int height);
    virtual bool contact();
    virtual ~SpriteEnemy();
    void fMoveOrbit_1();
    void fMoveOrbit_2();
    void fMoveComplex_1();

protected:
    int mStateFunc;

    //pTFuncSpriteEnemy pMove;

};

#endif // SPRITEENEMY_H
