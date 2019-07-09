#ifndef RESURSEIMAGES_H
#define RESURSEIMAGES_H

#include <QImage>
#include <QVector>
#include <QDebug>

struct DataImages
{
    QString mName;
    QImage *pImage;
    QVector <QVector <QImage*>> vvpImage;
    int mWidth;
    int mHeight;
    int mCountHorizontal;
    int mCountVertical;
    int mTimeOutAnimation;
};

class ResurseImages
{
public:
    static QVector <DataImages> vDataImages;
    ResurseImages();
    ~ResurseImages();
    QImage* getImageFromName(QString name);
    QImage* getImageFromIndex(int index);
    void addImage(QString name, QImage *image, int width, int height,
                  int countHorizontal=1, int countVertical=1, float TimeOutAnimation=0);
    void addImage(QString name, QString imageName, int width, int height,
                  int countHorizontal=1, int countVertical=1, float TimeOutAnimation=0);
    void loadImages();
    DataImages* getDataImages(QString nameSprite);
    void syncTimeOutAnimation(int timeOut=1);
    QImage getUnitImage(const QString name, int row=0, int col=0);

};

#endif // RESURSEIMAGES_H
