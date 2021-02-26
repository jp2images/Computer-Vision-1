// BasicImageOperations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h> //GetCurrentDirectory
#include <iostream>
#include <stdio.h>
#include <tchar.h> //For the template TCHAR
#include <filesystem> //must use C++17 or later for directory_iterator

#include "dataPath.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //imwrite

namespace fs = std::filesystem;

using namespace std;
using namespace std::filesystem;


int main()
{
    DWORD dwRet;

    cout << "Hello World!\n";
    cout << "OpenCV Version: " << CV_VERSION << endl;

    std::string myPath = "../../Week 1/DataFiles/Data";

    //Show the directory data
    TCHAR pwd[MAX_PATH];
    dwRet = GetCurrentDirectory(MAX_PATH, pwd);
    path pathToDisplay(pwd);
    cout << pwd << endl << endl;
    cout << pathToDisplay << endl << endl;

    for (const auto& entry : fs::directory_iterator(myPath))
        std::cout << entry.path() << std::endl << endl;
    

    cv::Mat image = cv::imread(myPath + "/images/boy.jpg");
    //std::string path = DATA_PATH;

    const string myWindow = "myWindow";
    cv::namedWindow(myWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(myWindow, image);
    cv::waitKey(0);
    //cv::destroyWindow(myWindow);
    
    /*

    int resizeDownWidth = 300;
    int resizeDownHeight = 200;
    cv::Mat resizedDown;

    cv::resize(image, resizedDown, cv::Size(resizeDownWidth, resizeDownHeight), cv::INTER_LINEAR);

    const string downSizedWindow = "myWindow";
    cv::namedWindow(downSizedWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(downSizedWindow, resizedDown);
    cv::waitKey(0);
    cv::destroyWindow(downSizedWindow);



    // Mess up with the aspect ratio
    int resizeUpWidth = 600;
    int resizeUpHeight = 900;
    cv::Mat resizedUp;
    resize(image, resizedUp, cv::Size(resizeUpWidth, resizeUpHeight), cv::INTER_LINEAR);

    const string upSizedWindow = "myWindow";
    cv::namedWindow(upSizedWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(upSizedWindow, resizedUp);
    cv::waitKey(0);
    cv::destroyWindow(upSizedWindow);



    */
    // Scaling Down the image 1.5 times by specifying both scaling factors
    double scaleUpX = 2;
    double scaleUpY = 2;

    // Scaling Down the image 0.6 times specifying a single scale factor.
    double scaleDown = 0.6;

    cv::Mat scaledUpImage, scaledDownImage;

    cv::resize(image, scaledDownImage, cv::Size(), scaleDown, scaleDown, cv::INTER_LINEAR);

    const string scaledDownWindow = "scaledDownWindow";
    cv::namedWindow(scaledDownWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(scaledDownWindow, scaledDownImage);
    cv::waitKey(0);

    cv::imwrite("../results/scaledUp.png", scaledDownImage);
    cv::destroyWindow(scaledDownWindow);


    resize(image, scaledUpImage, cv::Size(), scaleUpX, scaleUpY, cv::INTER_LINEAR);

    const string scaledUpWindow = "scaledUpWindow";
    cv::namedWindow(scaledUpWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(scaledUpWindow, scaledUpImage);
    cv::waitKey(0);

    cv::imwrite("../results/scaledDown.png", scaledUpImage);
    cv::destroyWindow(scaledUpWindow);

    cout << "Scaled Up Image size = " << scaledUpImage.size() << endl;
    cout << "Scaled Down Image size = " << scaledDownImage.size() << endl;



    cv::Mat mask1 = cv::Mat::zeros(image.size(), image.type());
    //const string maskedWindow = "maskWindow";
    //cv::namedWindow(maskedWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(maskedWindow, mask1);
    //cv::waitKey(0);
    //cv::destroyWindow(maskedWindow);


    mask1(cv::Range(50, 200), cv::Range(170, 320)).setTo(255);
    //const string maskedWindow = "maskWindow";
    //cv::namedWindow(maskedWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(maskdeWindow, mask1);
    //cv::waitKey(0);
    //cv::destroyWindow(maskedWindow);



    cv::Mat mask2;
    cv::inRange(image, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), mask2);
    const string maskedWindow2 = "maskWindow2";
    cv::namedWindow(maskedWindow2, cv::WINDOW_AUTOSIZE);
    cv::imshow(maskedWindow2, mask2);
    cv::waitKey(0);
    cv::destroyWindow(maskedWindow2);



    //Close the original image
    cv::destroyWindow(myWindow);
}

