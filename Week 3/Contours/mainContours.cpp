
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
//using namespace cv;

int main() {

    string imagePath = DATA_PATH + "images/Contour.png";
    cv::Mat image = cv::imread(imagePath);

    cv::Mat imageCopy = image.clone();

    cv::Mat imageGray;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::imshow("Image", imageGray);
    cv::waitKey(0);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    
    //Find all of the contours
    cv::findContours(imageGray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cout << "Number of contours found = " << contours.size() << endl;

    cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 0), 6);
    cv::imshow("All Contours", image);
    cv::waitKey(0);
  

    // find only the outside contours
    cv::findContours(imageGray, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cout << "Number of contours found = " << contours.size() << endl;

    image = imageCopy.clone();

    cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 0), 6);
    cv::imshow("Outer Contours", image);
    cv::waitKey(0);


    //Get the properties of the contours
    cv::findContours(imageGray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 3);

    cv::Moments M;
    int x, y;

    //use the contour moments to find the centroid
    for (size_t i = 0; i < contours.size(); i++) {
        //moments are weighted averages of pixel intensities and return certain properties
        M = cv::moments(contours[i]);
        x = int(M.m10 / double(M.m00));
        y = int(M.m01 / double(M.m00));

        //mark the center of each contour
        cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 1);
    }

    cv::imshow("Center of contours", image);
    cv::waitKey(0);



    //use the contour moments to find the centroid
    for (size_t i = 0; i < contours.size(); i++) {
        M = cv::moments(contours[i]);
        x = int(M.m10 / double(M.m00));
        y = int(M.m01 / double(M.m00));

        //mark the center of each contour
        cv::circle(image, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 1);
        cv::putText(image, to_string(i + 1), cv::Point(x + 40, y - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    }
    cv::imshow("Labeled Center of contours", image);
    cv::waitKey(0);


    //Areas and perimeters
    double area;
    double perimeter;
    
    cout << endl;
    for (size_t i = 0; i < contours.size(); i++) {
        area = cv::contourArea(contours[i]);
        perimeter = cv::arcLength(contours[i], true);
        cout << "Contour #" << i + 1 << " has area: " << area << "\tand perimeter: " << perimeter << endl;
    }
    cout << endl << endl;


    //Place a bounding box around the contours
    //image = imageCopy.clone();
    cv::Rect rect;

    for (size_t i = 0; i < contours.size(); i++) {
        rect = cv::boundingRect(contours[i]);
        cv::rectangle(image, rect, cv::Scalar(200, 200, 200), 2);
    }

    cv::imshow("Bounding Box", image);
    cv::waitKey(0);


    //Display the contours with rotated rectangles (smallest rectangle around the contour)
    cv::Mat rotImage = imageCopy.clone();
    cv::RotatedRect rotRect;
    cv::Point2f rect_points[4];
    cv::Mat boxPoints2f, boxPointsCov;
        
    for (size_t i = 0; i < contours.size(); i++) {
        rotRect = cv::minAreaRect(contours[i]);
        cv::boxPoints(rotRect, boxPoints2f);
        boxPoints2f.assignTo(boxPointsCov, CV_32S);
        cv::polylines(rotImage, boxPointsCov, true, cv::Scalar(150, 150, 150), 2);
    }
    cv::imshow("Rotated Rectangles", rotImage);
    cv::waitKey(0);


    //Fit a circle around the contours
    cv::Mat circleImage = imageCopy.clone();

    cv::Point2f center;
    float radius;

    for (size_t i = 0; i < contours.size(); i++) {
        cv::minEnclosingCircle(contours[i], center, radius);
        cv::circle(circleImage, center, radius, cv::Scalar(0,120, 120),2);
    }
    cv::imshow("Circles around the contours", circleImage);
    cv::waitKey(0);


    //Ellipse around the contours
    //A fitted ellipse won't completely enclose a contour.
    cv::Mat ellipseImage = imageCopy.clone();
    cv::RotatedRect ellipseRect;

    for (size_t i = 0; i < contours.size(); i++) {
        // Fit an ellipse
        // We can fit an ellipse only when our contour has minimum 5 points
        if (contours.size() < 5) continue;
        ellipseRect = cv::fitEllipse(contours[i]);
        cv::ellipse(ellipseImage, ellipseRect, cv::Scalar(128, 128, 0), 2);
    }
    cv::imshow("Ellipse around the contours", ellipseImage);
    cv::waitKey(0);

    return 0;
}
