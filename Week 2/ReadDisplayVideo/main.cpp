
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp"


#include <Windows.h> //GetCurrentDirectory
#include <filesystem>

using namespace std;
using namespace cv;

namespace fs = std::filesystem;
using namespace std::filesystem;

int main() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    DWORD dwRet;

    std::string myPath = "../../Data Files/";

    ////Show the current working directory
    //TCHAR pwd[MAX_PATH];
    //dwRet = GetCurrentDirectory(MAX_PATH, pwd);
    //path pathToDisplay(pwd);
    ////cout << pwd << endl << endl; //Memory address
    //cout << pathToDisplay << endl << endl;
    //for (const auto& entry : fs::directory_iterator(myPath))
    //    std::cout << entry.path() << std::endl << endl;


    
    //cv::VideoCapture cap(DATA_PATH + "chaplin.mp4");

    //if (!cap.isOpened()) {
    //    cout << endl << "Error opening video stream or file" << endl << endl;
    //    return -1;
    //}

    //cv::Mat frame;

    //int videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    //int videoHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    //cout << endl << endl << "Width: " << videoWidth << " Height: " << videoHeight << endl << endl;
    ////Start at a different position of the video
    //cap.set(CAP_PROP_POS_MSEC, 0);
    //cap >> frame;

    //cv::imshow("Frame", frame);
    //cv::waitKey(0);

    //while (cap.isOpened()) {
    //    cap >> frame;

    //    if (frame.empty()) {
    //        break;
    //    }

    //    cv::imshow("Frame", frame);
    //    cv::waitKey(25);
    //}

#pragma region USB Capture if connected
    cv::VideoCapture usbCam(0);
    if (!usbCam.isOpened()) {
        cout << "USBCam failed to open" << endl << endl;
        return -1;
    }
    
    int usbVideoWidth = usbCam.get(CAP_PROP_FRAME_WIDTH);
    int usbVideoHeight = usbCam.get(CAP_PROP_FRAME_HEIGHT);
    cout << endl << endl << "USB Width: " << usbVideoWidth << " USB Height: " << usbVideoHeight << endl << endl;
    
    //change the size of the video
    //usbCam.set(CAP_PROP_FRAME_WIDTH, 320);
    //usbCam.set(CAP_PROP_FRAME_WIDTH, 160);

    cv::Mat usbFrame;
    cv::Mat grayFrame;

    usbCam >> usbFrame;
    cv::imshow("USB Frame", usbFrame);
    cv::waitKey(0);

    while (usbCam.isOpened()) {
        usbCam >> usbFrame;

        if (usbFrame.empty()) {
            break;
        }

        //Open two windows one color and one gray scale
        cv::cvtColor(usbFrame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::imshow("USB Frame", usbFrame);
        cv::imshow("USB Gray", grayFrame);
        cv::waitKey(25);
    }

    cv::destroyAllWindows();


#pragma endregion


#pragma region Read and save a file
    //cv::VideoWriter out(DATA_PATH + "myChaplinVideo.mp4",
    //    cv::VideoWriter::fourcc('M', 'P', 'G', '4'), 10,
    //    cv::Size(videoWidth, videoHeight));
    //
    ////reset the video position
    //cap.set(CAP_PROP_POS_MSEC, 0);

    //while(cap.isOpened()) {
    //    cap >> frame;

    //    if (frame.empty()) break;

    //    out.write(frame);
    //    cv::imshow("My Video", frame);
    //    waitKey(25);  
    //}

    ////reset the video position
    //cap.set(CAP_PROP_POS_MSEC, 0);

    //while (cap.isOpened()) {
    //    cap >> frame;

    //    if (frame.empty()) {
    //        break;
    //    }

    //    cv::imshow("My Video", frame);
    //    cv::waitKey(25);
    //}

    //cap.release();
    //out.release();
#pragma endregion

    return 0;
}
