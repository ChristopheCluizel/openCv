#include<iostream>
#include<string>
//##############################inclusion header opencv###################
#include<opencv/highgui.h>
#include<cv.h>
#include<opencv/cv.h>

#include"acquisition_image.h"
#include"reconnaissance_couleur.h"

using namespace std;

int main(int argc, char *argv[])
{
    string couleur;
    int compteur =0;

    IplImage *frame;
    CvCapture *capture=cvCaptureFromCAM(0); //mettre 0 si webcam interne et 1 si externe

    while(compteur<50)
    {
        frame=cvQueryFrame(capture);    //rafraichit la frame
        compteur++;
    }

    acquerir_image(frame, capture);
    couleur = reconnaitre_couleur();
    //cout<<"La couleur de la bougie est "<<couleur<<endl;

    cvReleaseImage(&frame); //libere la memoire allouee
    cvReleaseCapture(&capture);

    return 0;
}
