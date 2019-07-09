#ifndef PANELELEMENT_H
#define PANELELEMENT_H

#include <QObject>
#include "resurseimages.h"
#include <QDebug>
#include <QString>
//#include <QLabel>
#include <QPainter>
#include <QBitmap>



class PanelElement : public QObject
{
    Q_OBJECT

public:
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    int mCount;
    float mScale;
    QString mText;
    enum NamePanelElement{NONAME, SHIP, LIVE_HEART, LIVE_LEVEL, POWER_LEVEL, GAME_LEVEL_TEXT, GAME_LEVEL, SCORE_TEXT, SCORE};
    enum TypePanelElement{NONE, TEXT, IMAGE, PROGRESS_IMAGE};
    NamePanelElement mNameElement;
    TypePanelElement mTypeElement;

    explicit PanelElement(QObject *parent = 0);
    PanelElement(QImage *imageContext, ResurseImages *resurseImages, QString name, NamePanelElement nameElement=NONAME, TypePanelElement typeElement=NONE,
                 int x=0, int y=0, int width=0, int height=0, int row=0, int col=0);
    virtual void paint();
    void setDataElement(QString name, NamePanelElement nameElement=NONAME, TypePanelElement typeElement=NONE,
                         int x=0, int y=0, int width=0, int height=0, int row=0, int col=0);
    void setContext(QImage *imageContext);
    virtual ~PanelElement();

protected:
    QImage* pImage;
    QImage* pImageContext;
    ResurseImages* pResurseImages;
    DataImages *pDataImages;
    QPainter* pPainter;
    QString mNameFont;

};

#endif // PANELELEMENT_H
