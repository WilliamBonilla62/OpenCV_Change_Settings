#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "data_settings.h"
using namespace cv;
using namespace std;

float Brightness;
float Contrast;
float Saturation;
float Gain;
float Exposure;
int Frames_per_second;

int B;
int C;
int S;
int G;
int E;
unsigned int microsecond = 1000000;
char winName[20]="Live Streaming";
Mat frame;
VideoCapture cap(0);
/**
 * Initialiaze the camera.
 *
 * To disbale the the the Auto exposure the value must be set to 0.25
 * Sets the FPS to 120 Hz
 *
 */
void expo_init(void)
{
    cap.set(CV_CAP_PROP_AUTO_EXPOSURE,0.25);
    cap.set(CV_CAP_PROP_FPS,Frames_per_second);
}
/**
 * Update value to the camera.
 *
 * Callback function that sends the new value from the trackbar to the camera
 * The value is devided by 100 so the value sent is between 0 and 1
 */
void onTrackbar_changed(int, void*)
{
    Brightness =float(B)/100;
    Contrast   =float(C)/100;
    Saturation =float(S)/100;
    //Gain       =float(G)/100;
    Exposure   =double(E)/100;

    cap.set(CV_CAP_PROP_BRIGHTNESS,Brightness);
    cap.set(CV_CAP_PROP_CONTRAST, Contrast);
    cap.set(CV_CAP_PROP_SATURATION, Saturation);
    //cap.set(CV_CAP_PROP_GAIN, Gain);
    cap.set(CV_CAP_PROP_EXPOSURE,double(Exposure));

}

int main(int, char**)
{
    intro:
        int camera_selec;
        printf("Which camera are you using ? \n");
        printf("Camera with case press 0\n");
        printf("Camera without case press 1\n");
        cin >> camera_selec;
        printf("%d",camera_selec);
    if (camera_selec == 0)
        {
            Frames_per_second = 30;
        }
    if(camera_selec == 1)
        {
            Frames_per_second = 120;
        }
    // Verify if a camera is connected
    if (!cap.isOpened())
    {
        // Ends the code if there is no camera
        return -1;
    }
    // Inits the camera
    expo_init();
    // Name the window by the value of winName
    namedWindow(winName);
    // Gets all the value from the camera
    Brightness = cap.get(CV_CAP_PROP_BRIGHTNESS);
    Contrast = cap.get(CV_CAP_PROP_CONTRAST);
    Saturation = cap.get(CV_CAP_PROP_SATURATION);
    //Gain = cap.get(CV_CAP_PROP_GAIN);
    Exposure = cap.get(CV_CAP_PROP_EXPOSURE);
    Frames_per_second = cap.get(CAP_PROP_FPS);
    // Display the values from camera
    cout << "====================================" << endl << endl;
    cout << "Default Brightness -------> " << Brightness << endl;
    cout << "Default Contrast----------> " << Contrast << endl;
    cout << "Default Saturation--------> " << Saturation << endl;
    cout << "Default Gain--------------> " << Gain << endl << endl;
    cout << "Default Exposure--------------> " << Exposure << endl << endl;
    cout << "Default FPS--------------> " << Frames_per_second << endl << endl;
    cout << "====================================" << endl;

    B = int(Brightness * 100);
    C = int(Contrast * 100);
    S = int(Saturation * 100);
    //G = int(Gain * -100);
    E = int(Exposure *100);

    createTrackbar("Brightness", winName, &B, 100, onTrackbar_changed);
    createTrackbar("Contrast", winName, &C, 100, onTrackbar_changed);
    createTrackbar("Saturation", winName, &S, 100, onTrackbar_changed);
    //createTrackbar("Gain", winName, &G, 100, onTrackbar_changed);
    createTrackbar("Exposure", winName, &E, 100, onTrackbar_changed);

    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    Size frame_size(frame_width, frame_height);

    for (;;) {
        //Let the user set the settings before recording the video
        // get a new frame from camera
        VideoWriter oVideoWriter("MyVideo.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),Frames_per_second, frame_size, true);
        cap >> frame;

        imshow(winName, frame);
        // Wait until user press some key for 50ms
        int iKey = waitKey(50);

        //if user press 'ESC' key
        if (iKey == 27)
        {
            break;
        }
    }
    export_settings_cams(Brightness, Contrast,  Saturation, 0 ,Exposure, Frames_per_second);
    destroyAllWindows();
    return 0;
}