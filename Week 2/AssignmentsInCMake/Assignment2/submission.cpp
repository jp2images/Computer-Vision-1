
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//#include "dataPath.hpp"

using namespace std;
using namespace cv;

//Some global variables just for the sake of ease during training.
cv::Point rectStart, rectEnd;
cv::Mat source;
//Prototype the function for when we add files
void drawBox(int, int, int, int, void*);

const int ESC_KEY = 27;
const int C_KEY = 99;

int main() {
    std::string DATA_PATH = "../";
    const string mouseWindow = "Mouse Window";
    string croppedImageName = DATA_PATH + "cropped.jpg";

    //read in the image
    source = cv::imread(DATA_PATH + "sample.jpg");

    cv::Mat clearedImage = source.clone();
    cv::Mat croppedImage = source.clone();

    cv::namedWindow(mouseWindow, cv::WINDOW_NORMAL);
    cv::setMouseCallback(mouseWindow, drawBox);

    int k = 0;


    while (k != ESC_KEY) { //not equal to the Esc key pressed
        cv::imshow(mouseWindow, source);
        //Write some text on the screen for directions.
        cv::putText(source, "Choose the the box starting point and drag.",
            cv::Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1, cv::LINE_AA);
        cv::putText(source, "Press Esc to save the last box as a crop",
            cv::Point(10, 45), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1, cv::LINE_AA);
        cv::putText(source, "and Exit. Press c to clear and start over.",
            cv::Point(10, 70), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1, cv::LINE_AA);

        k = cv::waitKey(20) & 0xFF;

        if (k == C_KEY) clearedImage.copyTo(source);
    }

    croppedImage = clearedImage(cv::Range(rectStart.y, rectEnd.y), cv::Range(rectStart.x, rectEnd.x));

    cv::imwrite(croppedImageName, croppedImage);
    cv::imshow("Cropped Image", croppedImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}


void drawBox(int action, int xPos, int yPos, int flags, void* userdata) {

    switch (action) {
    case cv::EVENT_LBUTTONDOWN:
        //Starting position for the crop
        rectStart = cv::Point(xPos, yPos);
        break;

    case cv::EVENT_LBUTTONUP:
        //Ending position of the crop.
        rectEnd = cv::Point(xPos, yPos);

        //draw the rectangle
        cv::rectangle(source, rectStart, rectEnd, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
        break;
    }
}