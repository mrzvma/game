#ifndef GENERATORSPRATES_H
#define GENERATORSPRATES_H

#include <QObject>
#include "spriteenemy.h"
#include <QVector>
#include <QTimer>
#include <QDebug>
#include <QImage>

//#include "resurseimages.h"

class GeneratorSprates : public QObject
{
       Q_OBJECT
protected:
    int mTimeOut;
    int mWidth;
    int mHeight;

public:
    struct DataSprates
    {
        QString mNameSprite;
        BaseSprite::TypeSprite mTapeSprite;
        SpriteEnemy::pTFuncSpriteEnemy pMoveFunc;
        int mGroupe;
        double mAmpletude;
        double mPeriod;
        double speed;
        double x;
        double y;
        int levelLive;
    };
    struct SettingSprates
    {
        BaseSprite::TypeSprite mTapeSprite;
        int mPersent;
    };
    static QVector<QString> vNameSprites;
    static ResurseImages *pResurseImages;
    QTimer oTimer;    
    explicit GeneratorSprates(QObject *parent = 0);
    GeneratorSprates(ResurseImages *pResImages, int width, int height, int timeOut);
    QVector<DataSprates> vDataSprates;
    QVector<SettingSprates> vSettingSprates;
    void setTimer(int timeOut) {mTimeOut=timeOut;}
    void setWidth(int width) {mWidth=width;}
    void setHeight(int height) {mHeight=height;}
    void setSprate(BaseSprite::TypeSprite tapeSprite, int persent);
    bool addSprite();
    void generate();
    void initVNameSprites();

signals:
    void sendSprates(BaseSprite* pBaseSprite);

public slots:
    void start();
};

#endif // GENERATORSPRATES_H
