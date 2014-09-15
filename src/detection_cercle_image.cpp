#include<iostream>
#include <cv.h>
#include <opencv/highgui.h>
#include<math.h>

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;

 int main( int argc, const char** argv )
 {
     IplImage *image = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
     CvMemStorage *storage =cvCreateMemStorage(0);
     cvSmooth(image,image,CV_GAUSSIAN, 5,5);
     CvSeq *results =cvHoughCircles(image, storage, CV_HOUGH_GRADIENT, 0.0001, image->width/10);

    for(int i=0;i<results->total; i++)
    {
        float *p=(float*)cvGetSeqElem(results,i);
        CvPoint pt=cvPoint(cvRound(p[0]), cvRound(p[1]));
        cvCircle(image, pt, cvRound(p[2]),CV_RGB(255,0,0));
    }
    cvNamedWindow("cvHoughCircles",1);
    cvShowImage("cvHoughCircles",image);
    cvWaitKey(0);

      return 0;
 }
