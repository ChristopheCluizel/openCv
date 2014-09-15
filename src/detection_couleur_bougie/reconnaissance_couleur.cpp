#include<iostream>
#include"reconnaissance_couleur.h"

using namespace std;

IplImage *imageOriginale, *imageSortie, *mask;
CvRect selection;
int x=100, y=60, width=400, height=300, sommeCouleurBleue =0, sommeCouleurRouge =0;
bool clic=false;
string couleur;

string reconnaitre_couleur()
{
    char c;
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);  //creer les 2 fenetres, une en entree
    cvNamedWindow("sortie", CV_WINDOW_AUTOSIZE);    //une autre en sortie
    imageOriginale=cvLoadImage("imageFromCapture.jpg", CV_LOAD_IMAGE_UNCHANGED);    //charge les images
    imageSortie=cvLoadImage("imageFromCapture.jpg", CV_LOAD_IMAGE_UNCHANGED);

    selection=cvRect(x,y,width,height); //indique quelle est la selection
    cvRectangle(imageSortie,cvPoint(x,y), cvPoint(x+width, y+height), cvScalar(0,255,0));   //dessine le rectangle sur l'image

    cvSetImageROI(imageSortie, selection);  //zoom sur le rectangle
    couleur=indicationCouleur(imageSortie); //indique la couleur a l'interieur du rectangle
    cvResetImageROI(imageSortie);   //sort du zoom

    cvShowImage("original", mask);
    cvShowImage("sortie", imageSortie);
    cout<<"La couleur de la bougie est "<<couleur<<endl;//juste pour soutenance
    while(c!='q')//juste pour voir le rectangle a l'ecran pour verifier qu'il encadre la couleur
    {
        c=cvWaitKey(10);
    }

    cvDestroyAllWindows();
    cvReleaseImage(&imageOriginale);
    cvReleaseImage(&imageSortie);
    cvReleaseImage(&mask);
    return couleur;
}
string indicationCouleur(IplImage *selectionCouleur)
{
    mask = cvCreateImage(cvGetSize(selectionCouleur), selectionCouleur->depth, 1);

    IplImage* imgHSV = cvCreateImage(cvGetSize(selectionCouleur), IPL_DEPTH_8U, 3);
    cvCvtColor(selectionCouleur, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV

    cvInRangeS(imgHSV, cvScalar(92,99,209), cvScalar(115,247,256), mask);
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
	cvInRangeS(imgHSV, cvScalar(0,168,228), cvScalar(58,256,256), mask);   //en HSV
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
    if(sommeCouleurRouge>6000)
        return "rouge";
    else if(sommeCouleurBleue>6000)
    {
            return "bleu";
    }
    else
        return "incolore";
}
