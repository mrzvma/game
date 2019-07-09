#ifndef CONTROLSPRITE_H
#define CONTROLSPRITE_H


#include "basesprite.h"
#include "spriterocket.h"
#include <QKeyEvent>
#include "widget.h"


class ControlSprite : public BaseSprite
{

protected:

    bool m_PushedUP;
    bool m_PushedDOWN;
    bool m_PushedLEFT;
    bool m_PushedRIGTH;
    bool m_PushedFIRE;    
    int mTimeOutFire;
    int mTimeOutFireCur;
    int mLevelLiveMax;
    void fire();

public:
    Widget* pWidget;

    ControlSprite(ResurseImages *pResImages=new ResurseImages(), QString nameSprite="", int speed=1,
                  int x0=0, int y0=0, int levelLive=1, int levelPower=1, int shotsPerSecond=100);
    virtual ~ControlSprite();
    virtual void move();
    virtual void setParamScene(const int width, const int height);
    virtual bool contact();
    virtual void setFrameClock(const int frameClock);
    bool eventFilter(QObject *object, QEvent *event);

};
#endif // CONTROLSPRITE_H
