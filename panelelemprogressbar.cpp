#include "panelelemprogressbar.h"

PanelElemProgressBar::PanelElemProgressBar(QImage *imageContext, QImage *imageContextBackground, ResurseImages *resurseImages, QString nameImage,
                                           QString nameImageEmpty, QString nameImageProgress, NamePanelElement nameElement,
                                           int count, int offsetImage, int x, int y, int width, int height, int row, int col)
                                           : PanelElement(imageContext, resurseImages, nameImage, nameElement, PanelElement::PROGRESS_IMAGE,
                                                          x, y, width, height, row, col)
{    
    mOffsetImage=offsetImage*mScale;
    pImageEmpty=new QImage();
    pImageProgress=new QImage();
    pImageProgressCur=new QImage();
    pImageContextBackground=imageContextBackground;
    *pImageEmpty=pResurseImages->getUnitImage(nameImageEmpty, row, col).scaled(mWidth, mHeight);
    mWidthImageProgress=pResurseImages->getUnitImage (nameImageProgress, row, col).width();
    *pImageProgress=pResurseImages->getUnitImage(nameImageProgress, row, col).scaled(mWidthImageProgress*mScale, mHeight);
    mScaleProcess=(float)pImageProgress->width()/count;
    mCount=count*mScaleProcess;
    setCurImageProcess();
}
//=============================================================
void PanelElemProgressBar::paint()
{
    pPainter->begin(pImageContext);
    pPainter->drawImage(mX+mOffsetImage, mY, *pImageProgressCur);
    pPainter->drawImage(mX, mY, *pImageEmpty);
    pPainter->end();
}
//=============================================================
void PanelElemProgressBar::paintBackground()
{
    pPainter->begin(pImageContextBackground);
    pPainter->drawImage(mX, mY, *pImage);
    pPainter->end();
}
//=============================================================
void PanelElemProgressBar::setCurImageProcess()
{
    *pImageProgressCur=pImageProgress->copy(pImageProgress->width()-mCount, 0, mCount, mHeight);
    //qDebug()<<mCount;
}
//=============================================================
