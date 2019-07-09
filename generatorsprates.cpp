#include "generatorsprates.h"

GeneratorSprates::GeneratorSprates(QObject *parent) : QObject(parent)
{
    mTimeOut=1000;
    mWidth=0;
    mHeight=0;
    initVNameSprites();
}
//=============================================================
GeneratorSprates::GeneratorSprates(ResurseImages *pResImages, int width, int height, int timeOut)
{
    pResurseImages=pResImages;
    mTimeOut=timeOut;
    mWidth=width;
    mHeight=height;
    initVNameSprites();
}
//=============================================================
void GeneratorSprates::start()
{
    oTimer.singleShot(mTimeOut, this, SLOT(start()));
    addSprite();
    generate();
}
//=============================================================
bool GeneratorSprates::addSprite()
{
    bool result=false;
    int rand;
    DataSprates oDataSprates;
    QVector<SettingSprates>::Iterator it=vSettingSprates.begin();
    while(it<vSettingSprates.end())
    {
        if( (qrand()%100) <= (it->mPersent) )
        {
            switch (it->mTapeSprite)
            {
            case BaseSprite::ENEMY:
                rand=qrand()%(SpriteEnemy::vpTFuncSpriteEnemy.size());
                oDataSprates.pMoveFunc=SpriteEnemy::vpTFuncSpriteEnemy.at(rand);
                rand=qrand()%(vNameSprites.size());
                oDataSprates.mNameSprite=vNameSprites.at(rand);
                oDataSprates.levelLive=(1+rand)*10;
                break;
            default:
                break;
            }
            rand=qrand()%3;
            switch (rand)
            {
            case 1:
                oDataSprates.mGroupe=5;
                break;
            case 2:
                oDataSprates.mGroupe=3;
                break;
            default:
                oDataSprates.mGroupe=1;
                break;
            }
            oDataSprates.speed=(qrand()%10)+2;
            oDataSprates.mAmpletude=(qrand()%25)+50;
            oDataSprates.mPeriod=(qrand()%10)+5;
            oDataSprates.x=rand=qrand()%(mWidth-50);
            oDataSprates.y=0-oDataSprates.mAmpletude-50;
            oDataSprates.mTapeSprite=it->mTapeSprite;            

            vDataSprates.append(oDataSprates);
            result=true;
            //qDebug()<<oDataSprates.x<<oDataSprates.y<<oDataSprates.mTapeSprite<<oDataSprates.pMoveFunc<<oDataSprates.mGroupe;
        }
        ++it;
    }
    return result;
}
//=============================================================
void GeneratorSprates::generate()
{
    BaseSprite* pBaseSprite;
    QVector<DataSprates>::Iterator it=vDataSprates.begin();
    while(it<vDataSprates.end())
    {
        if( (it->mGroupe) > 0 )
        {
            it->mGroupe--;
            switch (it->mTapeSprite)
            {
            case BaseSprite::ENEMY:
                pBaseSprite=new SpriteEnemy(it->pMoveFunc, it->mAmpletude, it->mPeriod, pResurseImages, it->mNameSprite, it->speed, it->x, it->y,
                                            it->levelLive);
                emit sendSprates(pBaseSprite);
                break;
            default:
                break;
            }            
        }
        else
        {
            //qDebug()<<vDataSprates.begin()<<vDataSprates.end()<<it<<"erase"<<vDataSprates.size();
            vDataSprates.erase(it);
        }
        ++it;
    }
}
//=============================================================
void GeneratorSprates::setSprate(BaseSprite::TypeSprite tapeSprite, int persent)
{
     SettingSprates sSettingSprates;
     sSettingSprates.mTapeSprite=tapeSprite;
     sSettingSprates.mPersent=persent;
     vSettingSprates.append(sSettingSprates);
}
//=============================================================
void GeneratorSprates::initVNameSprites()
{
    vNameSprites<<"ENEMY_1"<<"ENEMY_2"<<"ENEMY_3";
}
//=============================================================
QVector<QString> GeneratorSprates::vNameSprites;
ResurseImages *GeneratorSprates::pResurseImages;
