#ifndef __REBOUND_CONTROLLER_H_
#define __REBOUND_CONTROLLER_H_

struct MoveSample
{
    uint16 x;
    uint16 y;
    uint32 time;
};

class Controller
{
    public:
};

typedef struct _IplImage IplImage;
struct CvCapture;

class WebCamController : public Controller
{
    public:
        WebCamController();
        ~WebCamController();
        void test();

    private:
        void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
        void drawCross(IplImage *frame, int x, int y, int size, int width);

        CvCapture* capture;
};

class MouseController : public Controller
{
    public:
        MouseController();
};

class NetController : public Controller
{
    public:
        NetController();
};

#endif // __REBOUND_CONTROLLER_H_