//
// Created by william on 4/6/21.
//
#include "data_settings.h"
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
void export_settings_cams(float Brightness,float Contrast, float Saturation, float Gain, float Exposure,int Frames_per_second)
{
    ofstream myfile;
    myfile.open("Exported_Settings.csv");
    myfile << Brightness;
    myfile << "\r\n";
    myfile << Contrast;
    myfile << "\r\n";
    myfile << Saturation;
    myfile << "\r\n";
    myfile << Gain;
    myfile << "\r\n";
    myfile << Exposure;
    myfile << "\r\n";
    myfile << Frames_per_second;
    myfile << "\r\n";
    myfile.close();
    printf("Exported parameters succesfully");
}