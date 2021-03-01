
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";

using namespace std;
//using namespace cv;

void pltImg(cv::Mat imageToShow, string imageNameOnWindow) {
    const string windowName = imageNameOnWindow;
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, imageToShow);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
}

int main() {
    //cout << "Hello, World!" << endl;
    //cout << "OpenCV version is " << CV_VERSION << endl;
    string imageName = DATA_PATH + "/images/boy.jpg";

    // Load an image
    cv::Mat image;
    image = cv::imread(imageName, cv::IMREAD_COLOR);
    //pltImg(image, "Boy");

    // **********************************************
    // Drawing a line on an image
    // **********************************************

    // Copy the image so we don't mess witht eh oringinal
    //cv::Mat imageLine = image.clone();
    //cv::line(imageLine, cv::Point(200, 80), cv::Point(280, 80), cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
    //pltImg(imageLine, "Boy with a line");

    // **********************************************
    // Drawing a circle
    // **********************************************
    //cv::Mat imageCircle = image.clone();
    //cv::circle(imageCircle, cv::Point(245, 125), 100, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    //pltImg(imageCircle, "Image with a circle");

    // **********************************************
    // Drawing a filled circle
    // **********************************************
    //cv::Mat imageFilledCircle = image.clone();
    //cv::circle(imageFilledCircle, cv::Point(245, 125), 100, cv::Scalar(0, 0, 255), -1, cv::LINE_AA);
    //pltImg(imageFilledCircle, "Image with a circle");


    // **********************************************
    // Drawing an ellipse
    // **********************************************
    //cv::Mat imageElipse = image.clone();
    //cv::ellipse(imageElipse         // Image
    //    , cv::Point(250, 125)       // Center Point
    //    , cv::Point(100, 50)        // Size of the axis
    //    , 0                         // Angle of the ellipse
    //    , 0                         // Beginning o gthe angle to display
    //    , 360                       // End of the displaying angel
    //    , cv::Scalar(0, 0, 255)     // Color
    //    , 1                         // Border line thickness
    //    , cv::LINE_8                // Line Type
    //    , 0);                       // Shift

    //cv::ellipse(imageElipse         // Image
    //    , cv::Point(250, 125)       // Center Point
    //    , cv::Point(100, 50)        // Size of the axis
    //    , 90                        // Angle of the ellipse
    //    , 0                         // Beginning o gthe angle to display
    //    , 360                       // End of the displaying angel
    //    , cv::Scalar(255, 0, 255)   // Color
    //    , 5                         // Border line thickness
    //    , cv::LINE_8                // Line Type
    //    , 0);                       // Shift

    //pltImg(imageElipse, "Ellipse");

    // **********************************************

    //cv::Mat imageFilledElipse = image.clone();
    //cv::ellipse(imageFilledElipse   // Image
    //    , cv::Point(250, 125)       // Center Point
    //    , cv::Point(100, 50)        // Size of the axis
    //    , 0                         // Angle of the ellipse
    //    , 180                       // Beginning o gthe angle to display
    //    , 360                       // End of the displaying angel
    //    , cv::Scalar(0, 0, 255)     // Color
    //    , 1                         // Border line thickness
    //    , cv::LINE_AA               // Line Type
    //    , 0);                       // Shift

    //cv::ellipse(imageFilledElipse   // Image
    //    , cv::Point(250, 125)       // Center Point
    //    , cv::Point(100, 50)        // Size of the axis
    //    , 0                         // Angle of the ellipse
    //    , 0                         // Beginning o gthe angle to display
    //    , 180                       // End of the displaying angel
    //    , cv::Scalar(255, 0, 255)   // Color
    //    , -1                        // Border line thickness
    //    , cv::LINE_AA               // Line Type
    //    , 0);                       // Shift

    //pltImg(imageFilledElipse, "Filled Ellipse");

    // **********************************************
    // Drawing a rectangle
    // **********************************************
    //cv::Mat imageRectangle = image.clone();
    //cv::rectangle(imageRectangle
    //    , cv::Point(170, 50)
    //    , cv::Point(300, 200)
    //    , cv::Scalar(255, 0, 0)
    //    , 2
    //    , cv::LINE_8);
    //pltImg(imageRectangle, "Rectangle");



    // **********************************************
    // Drawing some basic text
    // **********************************************
    {
        cv::Mat imageText = image.clone();
        string txtString = "I am studying";
        double fontScale = 1.5;
        int fontFace = cv::FONT_HERSHEY_COMPLEX;
        cv::Scalar fontColor = cv::Scalar(250, 10, 10);
        int fontThickness = 2;

        cv::putText(imageText, txtString, cv::Point(20, 350), fontFace, fontScale, fontColor, fontThickness, cv::LINE_AA);
        pltImg(imageText, "Text");
    }

    // **********************************************
    // Drawing some text sized
    // **********************************************
    {
        cv::Mat imageSizedText = image.clone();
        string txtString = "I am studying";
        int pixelHeight = 20;

        int fontFace = cv::FONT_HERSHEY_COMPLEX;
        cv::Scalar fontColor = cv::Scalar(250, 10, 10);
        int fontThickness = 2;

        double fontScale = cv::getFontScaleFromHeight(fontFace, pixelHeight, fontThickness);
        cout << "font scale: " << fontScale << endl << endl;

        cv::putText(imageSizedText, txtString, cv::Point(20, 350), fontFace, fontScale, fontColor, fontThickness, cv::LINE_AA);
        pltImg(imageSizedText, "Text");
    }



    // **********************************************
    // Drawing text get height and width
    // **********************************************
    {
        cv::Mat imageGetTextSize = image.clone();
        string txtString = "I am studying";

        int imageHeight = imageGetTextSize.rows;
        int imageWidth = imageGetTextSize.cols;

        int pixelHeight = 20;

        int fontFace = cv::FONT_HERSHEY_COMPLEX;
        cv::Scalar fontColor = cv::Scalar(250, 10, 10);
        int fontThickness = 2;

        double fontScale = cv::getFontScaleFromHeight(fontFace, pixelHeight, fontThickness);

        int baseline = 0;
        cv::Size textSize = cv::getTextSize(txtString, fontFace, fontScale, fontThickness, &baseline);
            
        int textWidth = textSize.width;
        int textHeight = textSize.height;

        cout << "Text Width: " << textWidth << ", Text Height: " << textHeight << ", baseline: " << baseline << endl << endl;

        int xCoordinate = (imageWidth - textWidth) / 2;
        int yCoordinate = (imageHeight - baseline - 10);
        cout << "Text box bottom lent: (" << xCoordinate << ", " << yCoordinate << ")" << endl << endl;

        //Draw the canvas using a filled rectangle
        cv::Scalar canvasColor = cv::Scalar(255, 255, 255);
        cv::Point canvasBottomLeft(xCoordinate, yCoordinate + baseline);
        cv::Point canvaTopRight(xCoordinate + textWidth, yCoordinate - textHeight);
        
        cv::rectangle(imageGetTextSize, canvasBottomLeft, canvaTopRight, canvasColor, -1);

        cout << "Canvas Bottom Lenft: " << canvasBottomLeft << ", Top Right: " << canvaTopRight << endl << endl;

        int lineThickness = 2;
        cv::Point lineLeft(xCoordinate, yCoordinate);
        cv::Point lineRight(xCoordinate + textWidth, yCoordinate);
        cv::Scalar lineColor = cv::Scalar(0, 255, 0);

        cv::line(imageGetTextSize, lineLeft, lineRight, lineColor, lineThickness, cv::LINE_AA);
        
        cv::putText(imageGetTextSize, txtString, cv::Point(xCoordinate, yCoordinate), fontFace, fontScale, fontColor, fontThickness, cv::LINE_AA);
        pltImg(imageGetTextSize, "Text");
    }

    return 0;
}
