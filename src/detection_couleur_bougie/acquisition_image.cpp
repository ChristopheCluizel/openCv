#include"acquisition_image.h"

using namespace std;

void acquerir_image(IplImage *frame,CvCapture *capture)
{
    frame=cvQueryFrame(capture);    //rafraichit la frame
    cvSaveImage("imageFromCapture.jpg",frame);      //enregistre l'image dans le dossier de l'executable
}

