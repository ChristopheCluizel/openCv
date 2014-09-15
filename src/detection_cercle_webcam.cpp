#include<iostream>
#include <cv.h>
#include <opencv/highgui.h>
#include<math.h>

 #include <iostream>

 using namespace std;
 using namespace cv;

 int main( int argc, const char** argv )
 {
     IplImage *image_originale, *image_grise;
     CvMemStorage *storage =cvCreateMemStorage(0);
     CvCapture *capture;
     char key;
     int threshold1=1, threshold2 =1;

     capture=cvCaptureFromCAM(1);
     cvNamedWindow("image_originale",CV_WINDOW_AUTOSIZE);
     cvNamedWindow("image_grise",CV_WINDOW_AUTOSIZE);
     cvMoveWindow("image_originale",0,0);
     cvMoveWindow("image_grise",710,0);

     cvCreateTrackbar("threshold1", "image_grise",&threshold1, 300, NULL);
     cvCreateTrackbar("threshold2", "image_grise",&threshold2, 300, NULL);

    while(key!='q')
    {
        image_originale=cvQueryFrame(capture);
        image_grise=cvCreateImage(cvGetSize(image_originale), image_originale->depth,1);
        cvCvtColor( image_originale, image_grise, CV_RGB2GRAY );



        cvSmooth(image_grise,image_grise,CV_GAUSSIAN, 5,5);
        CvSeq *results =cvHoughCircles(image_grise, storage, CV_HOUGH_GRADIENT, 2,200, threshold1,threshold2);

        for(int i=0;i<results->total; i++)
        {
            float *p=(float*)cvGetSeqElem(results,i);
            CvPoint pt=cvPoint(cvRound(p[0]), cvRound(p[1]));

            cvCircle(image_originale, pt, cvRound(p[2]),CV_RGB(255,0,0));
        }
        cvShowImage("image_originale", image_originale);
        cvShowImage("image_grise", image_grise);
        key=cvWaitKey(10);
    }


    cvDestroyAllWindows();
    cvReleaseImage(&image_grise);
    cvReleaseImage(&image_originale);
    cvReleaseCapture(&capture);
    cvReleaseMemStorage(&storage);

      return 0;
 }

