#ifndef SPRITEROCKET_H
#define SPRITEROCKET_H

#include "basesprite.h"
//#include "scenebuffer.h"
//#include <QVector>

class SpriteRocket : public BaseSprite
{
public:
    typedef void (SpriteRocket::* pTFuncSpriteRocket)();
    SpriteRocket(pTFuncSpriteBase pFMove, ResurseImages *pResImages=new ResurseImages(), QString nameSprite="", int speed=1,
                 float x0=0, float y0=0, int levelLive=1, int levelPower=1);
    virtual void move();
    virtual void setParamScene(const int width, const int height);
    virtual bool contact();
    virtual ~SpriteRocket();
};

#endif // SPRITEROCKET_H
