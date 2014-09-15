#include<iostream>
#include<opencv/highgui.h>
#include<opencv/cv.h>

using namespace std;

IplImage *imageOriginale, *imageSortie, *mask;
CvRect selection;
int x=0, y=0, width=100, height=100, sommeCouleurBleue =0, sommeCouleurRouge =0;
bool clic=false;

void indicationCouleur(IplImage *selectionCouleur)
{
    mask = cvCreateImage(cvGetSize(selectionCouleur), selectionCouleur->depth, 1);
    cvInRangeS(selectionCouleur, cvScalar(200), cvScalar(255), mask);
    for(int i = 0; i < mask->width; i++)
    {
		for(int j = 0; j < mask->height; j++)
		{
			if(((uchar *)(mask->imageData + j*mask->widthStep))[i] == 255)  //code couleur = BGR
			{
				sommeCouleurBleue++;
			}
		}
	}
	cvInRangeS(selectionCouleur, cvScalar(0,0,0), cvScalar(0,0,255), mask);
    for(int i = 0; i < mask->width; i++)
    {
		for(int j = 0; j < mask->height; j++)
		{
			if(((uchar *)(mask->imageData + j*mask->widthStep))[i] == 255)
			{
				sommeCouleurRouge++;
			}
		}
	}
    if((sommeCouleurBleue+sommeCouleurRouge)<(width*height-0.5*(width*height)))
        cout<<"Incolore"<<endl;
    else
    {
        if(sommeCouleurBleue>sommeCouleurRouge)
            cout<<"Bleu"<<endl;
        if(sommeCouleurBleue<sommeCouleurRouge)
            cout<<"Rouge"<<endl;
    }
    clic=false;
}
void selectionRectangle(int evt, int souris_x, int souris_y, int flags, void *param)
{
    if(evt==CV_EVENT_LBUTTONDOWN)
    {
        sommeCouleurBleue=0;
        sommeCouleurRouge=0;
        x=(souris_x-(width/2));
        y=(souris_y-(height/2));
        cvCopy(imageOriginale,imageSortie,0);
        clic=true;
    }
}

int main(int argc, char *argv[])
{
    char c;

    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("sortie", CV_WINDOW_AUTOSIZE);
    imageOriginale=cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    imageSortie=cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    cvSetMouseCallback("sortie", selectionRectangle,0);

    cvShowImage("original", imageOriginale);
    cvShowImage("sortie", imageSortie);


    while(c!='q')
    {
        selection=cvRect(x,y,width,height);
        cvRectangle(imageSortie,cvPoint(x,y), cvPoint(x+width, y+height), cvScalar(0,255,0));   //dessine le rectangle

        cvSetImageROI(imageSortie, selection);  //zoom sur le rectangle
        if(clic==true)
            indicationCouleur(imageSortie);
        cvResetImageROI(imageSortie);   //sort du zoom

        cvShowImage("original", mask);
        cvShowImage("sortie", imageSortie);
        c=cvWaitKey(10);
    }

    cvDestroyAllWindows();
    cvReleaseImage(&imageOriginale);
    cvReleaseImage(&imageSortie);
    cvReleaseImage(&mask);

    return 0;
}
