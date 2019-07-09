#ifndef PANELELEMPROGRESSBAR_H
#define PANELELEMPROGRESSBAR_H

#include "panelelement.h"

class PanelElemProgressBar : public PanelElement
{
public:    
    float mScaleProcess;
    int mWidthImageProgress;
    PanelElemProgressBar(QImage *imageContext, QImage *imageContextBackground, ResurseImages *resurseImages, QString nameImage,
                         QString nameImageEmpty, QString nameImageProgress, NamePanelElement nameElement=NONAME,
                         int count=0, int offsetImage=0, int x=0, int y=0, int width=0, int height=0, int row=0, int col=0);
    virtual void paint();
    virtual void paintBackground();
    void setCurImageProcess();

protected:
    int mOffsetImage;
    QImage* pImageContextBackground;
    QImage* pImageEmpty;
    QImage* pImageProgress;
    QImage* pImageProgressCur;

};

#endif // PANELELEMPROGRESSBAR_H
