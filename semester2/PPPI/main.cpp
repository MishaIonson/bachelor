#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace std;
using namespace cv;

void detectAndDisplay( Mat frame );
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
int main( void )
{
    VideoCapture capture;
    capture.open(0);
    Mat frame;
    if( !face_cascade.load( face_cascade_name ) )
    {
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        printf("--(!)Error loading eyes cascade\n");
        return -1;
    };
    if ( ! capture.isOpened() )
    {
        printf("--(!)Error opening video capture\n");
        return -1;
    }
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" —(!) No captured frame — Break!");
            break;
        }
        detectAndDisplay( frame );
        int c = waitKey(10);
        if( (char)c == 27 )
        {
            break;
        }
    }
    return 0;
}
int pos[10][2]; // 1st - faces number, 2nd - coordinates
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(70, 70) );
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 0, 13, 26), 4, 8, 0 );
        circle(frame,center,1,Scalar( 0, 13, 26 ), 4, 8, 0);
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        Point before(2*(faces[i].x + faces[i].width/2) - pos[i][0], 2*(faces[i].y + faces[i].height/2) - pos[i][1]);
        line(frame, before, center, Scalar(0, 13, 26), 4, 8, 0);
        pos[i][0] = faces[i].x + faces[i].width/2;
        pos[i][1] = faces[i].y + faces[i].height/2;
        std::cout<< "Face index" << i << ": x-" << faces[i].x + faces[i].width/2 << ", y-" << faces[i].y + faces[i].height/2 << endl;
    }

    imshow( window_name, frame );
}
