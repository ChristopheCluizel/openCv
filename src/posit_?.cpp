#include<iostream>
#include<cmath>
#include<opencv/highgui.h>
#include<cv.h>

#define PI 3.141596535
using namespace std;

int main(int argc, char *argv[])
{
    //float cubeSize = 10.0;
    std::vector<CvPoint3D32f> modelPoints;
    modelPoints.push_back(cvPoint3D32f(28.0f, 28.0f, -28.0f));
    modelPoints.push_back(cvPoint3D32f(28.0f, -28.0f, -28.0));
    modelPoints.push_back(cvPoint3D32f(28.0f, 28.0f,28.0f));
    modelPoints.push_back(cvPoint3D32f(-28.0f, 28.0f, -28.0f));
    CvPOSITObject *positObject = cvCreatePOSITObject( &modelPoints[0], static_cast<int>(modelPoints.size()) );

    std::vector<CvPoint2D32f> projectedPoints;
    projectedPoints.push_back(cvPoint2D32f(-171,54));
    projectedPoints.push_back(cvPoint2D32f(-171,-66));
    projectedPoints.push_back(cvPoint2D32f(-105,43));
    projectedPoints.push_back(cvPoint2D32f(-258,52));

    CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 1.0e-4f);
    CvMatr32f rotation_matrix = new float[9];
    CvVect32f translation_vector = new float[3];

    cvPOSIT(positObject, &projectedPoints[0], 640, criteria,rotation_matrix, translation_vector );

    for(int i=0;i<3;i++)
    {
        cout<<translation_vector[i]<<endl;
    }
    /*float estimatedYaw;
    float estimatedPitch;
    float estimatedRoll;
    float C;

    estimatedRoll=atan2(-rotation_matrix[3], sqrt(pow(rotation_matrix[0],2)+pow(rotation_matrix[3],2)));
    C=cos(estimatedRoll);
    estimatedYaw=atan2(rotation_matrix[3]/C, rotation_matrix[0]/C);
    estimatedPitch=atan2(rotation_matrix[7]/C, rotation_matrix[8]/C);

    estimatedYaw   *= (float) ( 180.0 / PI );
    estimatedPitch *= (float) ( 180.0 / PI );
    estimatedRoll  *= (float) ( 180.0 / PI );

    cout<<"pitch : "<<estimatedPitch<<endl;
    cout<<"yaw : "<<estimatedYaw<<endl;
    cout<<"roll : "<<estimatedRoll<<endl;*/

    cvReleasePOSITObject(&positObject);
    delete rotation_matrix;
    delete translation_vector;

    return 0;
}
