
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //imwrite

#include "dataPath.hpp"

using namespace std;


int main()
{
    std::string myPath = "../../Week 1/DataFiles/Data";
    
    //Get and Load Elon's image
    std::string faceImagePath = myPath + "/images/musk.jpg";
    cv::Mat faceImage = cv::imread(faceImagePath);

    const string elonWindow = "Elon Musk";
    cv::namedWindow(elonWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(elonWindow, faceImage);
    cv::waitKey(0);
    //cv::destroyWindow(elonWindow);



    //Get and Load the Sungrlasses
    std::string glassImagePath = myPath + "/images/sunglass.png";
    cv::Mat glassPNG = cv::imread(glassImagePath, -1);
    resize(glassPNG, glassPNG, cv::Size(300, 100));

    cout << "Image Dimensions: " << glassPNG.size() << endl;
    cout << "Number of Channels: " << glassPNG.channels() << endl;

    cv::Mat glassBGRAChannels[4];
    cv::Mat glassBGRChannels[3];
    //Seperate the image into individual channels
    cv::split(glassPNG, glassBGRAChannels);

    for (int i = 0; i < 3; i++) {
        //Copy the B, G, R channels and drop the alpha
        glassBGRChannels[i] = glassBGRAChannels[i];
    }

    cv::Mat glassBGR, glassMask1;

    //Put the image back together without the alpha channel
    merge(glassBGRChannels, 3, glassBGR);
    //Create a mask with the alpha channel
    glassMask1 = glassBGRAChannels[3];


    const string glassesWindow = "Elon's Glasses";
    cv::namedWindow(glassesWindow, cv::WINDOW_AUTOSIZE);
    cv::imshow(glassesWindow, glassPNG);
    cv::waitKey(0);
    //cv::destroyWindow(glassesWindow);




    





   



  
    //// Scaling Down the image 1.5 times by specifying both scaling factors
    //double scaleUpX = 2;
    //double scaleUpY = 2;

    //// Scaling Down the image 0.6 times specifying a single scale factor.
    //double scaleDown = 0.6;

    //cv::Mat scaledUpImage, scaledDownImage;

    //cv::resize(image, scaledDownImage, cv::Size(), scaleDown, scaleDown, cv::INTER_LINEAR);

    //const string scaledDownWindow = "scaledDownWindow";
    //cv::namedWindow(scaledDownWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(scaledDownWindow, scaledDownImage);
    //cv::waitKey(0);

    //cv::imwrite("../results/scaledUp.png", scaledDownImage);
    //cv::destroyWindow(scaledDownWindow);


    //resize(image, scaledUpImage, cv::Size(), scaleUpX, scaleUpY, cv::INTER_LINEAR);

    //const string scaledUpWindow = "scaledUpWindow";
    //cv::namedWindow(scaledUpWindow, cv::WINDOW_AUTOSIZE);
    //cv::imshow(scaledUpWindow, scaledUpImage);
    //cv::waitKey(0);

    //cv::imwrite("../results/scaledDown.png", scaledUpImage);
    //cv::destroyWindow(scaledUpWindow);

    //cout << "Scaled Up Image size = " << scaledUpImage.size() << endl;
    //cout << "Scaled Down Image size = " << scaledDownImage.size() << endl;



    //cv::Mat mask1 = cv::Mat::zeros(image.size(), image.type());
    ////const string maskedWindow = "maskWindow";
    ////cv::namedWindow(maskedWindow, cv::WINDOW_AUTOSIZE);
    ////cv::imshow(maskedWindow, mask1);
    ////cv::waitKey(0);
    ////cv::destroyWindow(maskedWindow);


    //mask1(cv::Range(50, 200), cv::Range(170, 320)).setTo(255);
    ////const string maskedWindow = "maskWindow";
    ////cv::namedWindow(maskedWindow, cv::WINDOW_AUTOSIZE);
    ////cv::imshow(maskdeWindow, mask1);
    ////cv::waitKey(0);
    ////cv::destroyWindow(maskedWindow);



    //cv::Mat mask2;
    //cv::inRange(image, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), mask2);
    //const string maskedWindow2 = "maskWindow2";
    //cv::namedWindow(maskedWindow2, cv::WINDOW_AUTOSIZE);
    //cv::imshow(maskedWindow2, mask2);
    //cv::waitKey(0);
    //cv::destroyWindow(maskedWindow2);



    ////Close the original image
    //cv::destroyWindow(myWindow);
}

