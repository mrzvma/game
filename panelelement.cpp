#include "panelelement.h"

PanelElement::PanelElement(QObject *parent) : QObject(parent)
{

}
//=============================================================
PanelElement::PanelElement(QImage *imageContext, ResurseImages *resurseImages, QString name, NamePanelElement nameElement, TypePanelElement typeElement,
                           int x, int y, int width, int height, int row, int col)
{
    pImageContext=imageContext;
    pResurseImages=resurseImages;
    pPainter = new QPainter();
    pImage=new QImage();
    mNameFont="Arial";
    setDataElement(name, nameElement,  typeElement, x, y, width, height, row, col);
}
//=============================================================
PanelElement::~PanelElement()
{
    delete pPainter;
    delete pImage;
}
//=============================================================
void PanelElement::paint()
{
    pPainter->begin(pImageContext);
    switch (mTypeElement)
    {
    case IMAGE:
        pPainter->drawImage(mX, mY, *pImage);
        break;
    case TEXT:
        pPainter->setPen(Qt::black);
        pPainter->setFont(QFont(mNameFont, mHeight));
        pPainter->drawText(mX, mY, mText);
        break;
    default:
        break;
    }
    pPainter->end();

}
//=============================================================
void PanelElement::setDataElement(QString name, NamePanelElement nameElement, TypePanelElement typeElement,
                     int x, int y, int width, int height, int row, int col)
{
    mNameElement=nameElement;
    mTypeElement=typeElement;
    mCount=0;
    mScale=1;
    switch (mTypeElement)
    {
    case PROGRESS_IMAGE:
    case IMAGE:
        pDataImages=pResurseImages->getDataImages(name);
        mX=x;
        mY=y;
        if (width>0)
        {
            mWidth=width;
            if(height<=0)
            {
                mScale=(float)width/pDataImages->mWidth;
                mHeight=pDataImages->mHeight*mScale;
            }
        }
        else if(height>0)
        {
            mHeight=height;
            mScale=(float)height/pDataImages->mHeight;
            mWidth=pDataImages->mWidth*mScale;
        }
        *pImage=pResurseImages->getUnitImage(name, row, col).scaled(mWidth, mHeight);
        break;
    case TEXT:
        mX=x;
        mY=y+height;
        mText=name;
        mWidth=0;
        mHeight=height;
        break;
    default:
        break;
    }
}
//=============================================================
void PanelElement::setContext(QImage *imageContext)
{
    pImageContext=imageContext;
}
//=============================================================

