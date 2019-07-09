#ifndef SCENEBUFFER_H
#define SCENEBUFFER_H
#include <QImage>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QLinkedList>
#include "basesprite.h"
#include <QBitmap>
#include <QTime>
#include <QLayout>
#include "widget.h"
#include "panelelement.h"
#include "panelelemprogressbar.h"

class SceneBuffer : public QObject
{
    Q_OBJECT
protected:
    ResurseImages *pResurseImages;
    DataImages *pDataImages;
    QImage* pScene;
    QImage* pBackground;
    QImage* pPanel;
    QImage* pPanelBackground;
    QLabel* pLabel;
    QLabel* pLabelPanel;
    QVBoxLayout* pVBL;
    QTimer oTimer;
    int mTimeOut;
    QPainter* pPainter;
    int debug;
    int mFrame;
    QTime oTime;
    int mHeightPanel;
    int mHeightScene;
    int mSizeFont;
    int mRow1;
    int mRow2;
    int mColumn1;
    int mColumn2;
    int mColumn3;
    int mColumn4;

public:
    int mWidth;
    int mHeight;
    int mScore;
    QLinkedList<BaseSprite*> lpSprites;
    QLinkedList<PanelElement*> lpPanelElements;
    SceneBuffer(ResurseImages *pResImages, Widget* widget, int width=0, int height=0, int frame=25);
    void setTimeOut(int TimeOut);
    void setLabel(QLabel* pLabel);
    int getTimeOut();
    bool deleteSprite(BaseSprite* pBaseSprite);
    void paintSprites();
    void moveSprites();
    bool cleanSprites();
    void addPanelElement(PanelElement *pPanelElement);
    bool setTextPanelElement(PanelElement::NamePanelElement nameElement, QString text);
    bool addToCountPanelElement(PanelElement::NamePanelElement nameElement, int number);
    bool scalePanelProcessBar(PanelElement::NamePanelElement nameElement, int number);
    bool setCountToTextPanelElement(PanelElement::NamePanelElement nameElement);
    ~SceneBuffer();
    void moveImageBackground();

public slots:
    void start();
    void addSprite(BaseSprite* pBaseSprite);

};

#endif // SCENEBUFFER_H
