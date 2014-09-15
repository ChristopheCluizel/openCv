#include<iostream>
#include<opencv/highgui.h>
#include<cv.h>

using namespace std;

int main(int argc, char *argv[])
{
    IplImage *frame;
    char c;
    CvCapture *capture=cvCaptureFromCAM(0); //mettre 0 si webcam interne et 1 si externe

    cvNamedWindow("video", CV_WINDOW_AUTOSIZE);

    while(c!='q')
    {
        frame=cvQueryFrame(capture);
        if(c=='s')
        {
            cvSaveImage("imageFromCapture.jpg",frame);
        }
        cvShowImage("video", frame);
        c=cvWaitKey(40);
    }


    cvReleaseImage(&frame);
    cvReleaseCapture(&capture);

    return 0;
}
