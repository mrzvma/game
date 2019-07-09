#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QColor>
#include "scenebuffer.h"
#include "controlsprite.h"
#include "spriteenemy.h"
#include "generatorsprates.h"
//#include "resurseimages.h"

int main(int argc, char *argv[])
{
//    QObjectPrivate obj;
    QApplication a(argc, argv);
    //Q_INIT_RESOURCE(images);
    //const int X_MIN=200;
    //const int Y_MIN=200;
    const int X_WIDTH=800;
    const int Y_HEIGHT=600;
    Widget* pGame = new Widget;
    pGame->setFixedSize(X_WIDTH, Y_HEIGHT);
    ResurseImages *pResurseImages = new ResurseImages();
    pResurseImages->loadImages();
    SceneBuffer* pScene = new SceneBuffer(pResurseImages, pGame, X_WIDTH,Y_HEIGHT, 50);
    //SceneBuffer pScene1(pResurseImages, pGame, X_WIDTH,Y_HEIGHT, 80);
    pResurseImages->syncTimeOutAnimation(pScene->getTimeOut());
    GeneratorSprates* pGeneratorSprates = new GeneratorSprates(pResurseImages, X_WIDTH, Y_HEIGHT, 1000);
    pGeneratorSprates->setSprate(BaseSprite::ENEMY, 5);
    pGeneratorSprates->setSprate(BaseSprite::ENEMY, 10);
    pGeneratorSprates->setSprate(BaseSprite::ENEMY, 15);
    pGeneratorSprates->setSprate(BaseSprite::ENEMY, 20);
    //pGeneratorSprates->setSprate(BaseSprite::ENEMY, 90);
    QObject::connect(pGeneratorSprates, SIGNAL(sendSprates(BaseSprite*)), pScene, SLOT(addSprite(BaseSprite*)));
    ControlSprite* pControlSprite = new ControlSprite(pResurseImages, "BURAN", 200, 300, 400, 100, 1, 5);
    pControlSprite->pWidget=pGame;
    pGame->installEventFilter(pControlSprite);
    pScene->addSprite(pControlSprite);
    pScene->start();
    pGeneratorSprates->start();
    pGame->show();
    //qDebug()<<a.allWidgets();
    int result=a.exec();

    delete pGeneratorSprates;
    delete pScene;
    delete pResurseImages;
    delete pGame;

    return result;
}
