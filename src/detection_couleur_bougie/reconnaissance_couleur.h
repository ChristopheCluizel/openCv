#ifndef DEF_RECONNAISSANCE_COULEUR
#define DEF_ACQUISITION_IMAGE

#include<highgui.h>
#include<cv.h>
#include<string>

std::string reconnaitre_couleur();
void selectionRectangle(int evt, int souris_x, int souris_y, int flags, void *param);
std::string indicationCouleur(IplImage *selectionCouleur);

#endif

