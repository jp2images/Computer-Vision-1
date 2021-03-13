
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "dataPath.hpp"

using namespace std;
using namespace cv;

//Some global variables just for the sake of ease during training.
cv::Point center, circumference;
cv::Mat source;
//Prototype the function for when we add files
void drawCircle(int, int, int, int, void*);


int main() {

    //read in the image
    source = cv::imread(DATA_PATH + "sample.jpg");

    cv::Mat clearedImage = source.clone();
    cv::namedWindow("Window");

    cv::setMouseCallback("Window", drawCircle);

    int k = 0;

    while (k != 27) { //not equal to the Esc key pressed
        cv::imshow("Window", source);
        cv::putText(source, "Choose the circle center and drag.",
            cv::Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.7,
            Scalar(255, 255, 255), 1, cv::LINE_AA);
        cv::putText(source, "Press Esc to exit and c to clear.",
            cv::Point(10, 45), FONT_HERSHEY_SIMPLEX, 0.7,
            Scalar(255, 255, 255), 1, cv::LINE_AA);

        k = cv::waitKey(20) & 0xFF;

        if (k == 99) clearedImage.copyTo(source);
    }

    return 0;
}



void drawCircle(int action, int xPos, int yPos, int flags, void* userdata) {

    switch (action) {
    case cv::EVENT_LBUTTONDOWN:
        center = cv::Point(xPos, yPos);
        cv::circle(source, center, 1, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
        break;

    case cv::EVENT_LBUTTONUP:
        //calculate the circles radius
        circumference = cv::Point(xPos, yPos);
        float radius = sqrt(pow(center.x - circumference.x, 2) + pow(center.y - circumference.y, 2));

        //draw the circle
        cv::circle(source, center, radius, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);

        cv::imshow("Window", source);
        break;
    }
}
