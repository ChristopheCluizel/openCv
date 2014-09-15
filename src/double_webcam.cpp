#include<iostream>
#include <cv.h>
#include <opencv/highgui.h>

using namespace std;

int main(int argc, char *argv[])
{
      //load the video file to the memory
     CvCapture *capture1 =     cvCaptureFromCAM(0), *capture2 = cvCaptureFromCAM(1);


    //create a window with the title "Video"
    cvNamedWindow("Video1");
    cvNamedWindow("Video2");

    while(true) {
             //grab and retrieve each frames of the video sequencially
             IplImage* frame1 = cvQueryFrame( capture1 ), *frame2 = cvQueryFrame(capture2);

             //show the retrieved frame in the "Video" window
             cvShowImage( "Video1", frame1 );
             cvShowImage( "Video2", frame2 );

            int c = cvWaitKey(60);



          //exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27)
            if((char)c==27 ) break;
   }

   //destroy the opened window
   cvDestroyAllWindows();
   //release memory
   cvReleaseCapture( &capture1 );
   cvReleaseCapture( &capture2 );

    return 0;
}
