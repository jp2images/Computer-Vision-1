
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc/imgproc.hpp>

#include "dataPath.hpp";
//#include "../../resource/lib/public/includeLibraries.h"
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    std::string imagePath = "../../Week 1/DataFiles/Data";

    cv::Mat bbox;
    cv::Mat rectifiedImage;

    cv::Mat img = cv::imread(imagePath + "/images/IDCard-Satya.png");

    //cv::imshow("qrcode", img);
    //cv::waitKey(0);

    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector();
    string opencvData = qrDecoder.detectAndDecode(img, bbox, rectifiedImage);

    if (opencvData.length() > 0) {
        cout << "QR Code detected!" << endl << endl;
        cout << opencvData << endl;
    }
    else {
        cout << "QR Code NOT detected!" << endl << endl;
    }

    int n = bbox.cols;

    //Top Horizontal
    cv::line(img,
        cv::Point2i(bbox.at<float>(0, 0), bbox.at<float>(0, 1)), cv::Point2i(bbox.at<float>(0, 2), bbox.at<float>(0, 1)),
        cv::Scalar(255, 0, 0), 3, LINE_AA);


    //Bottom Horizontal
    cv::line(img,
        cv::Point2i(bbox.at<float>(0, 0), bbox.at<float>(0, 2)+64), cv::Point2i(bbox.at<float>(0, 2), bbox.at<float>(0, 2)+64),
        cv::Scalar(255, 255, 0), 3, LINE_AA);


    //Left Vertical
    cv::line(img,
        cv::Point2i(bbox.at<float>(0, 0), bbox.at<float>(0, 1)), cv::Point2i(bbox.at<float>(0, 0), bbox.at<float>(0, 2)),
        cv::Scalar(255, 0, 0), 3, LINE_AA);


    //Right Vertical
    cv::line(img,
        cv::Point2i(bbox.at<float>(0, 2), bbox.at<float>(0, 2)), cv::Point2i(bbox.at<float>(0, 2), bbox.at<float>(0, 1)),
        cv::Scalar(255, 0, 0), 3, LINE_AA);



    //cv::line(img,
    //    cv::Point2i(126, bbox.at<float>(0, 1)), cv::Point2i(22, bbox.at<float>(0, 3)),
    //    cv::Scalar(90, 90, 90), 2, LINE_AA);



    cv::imshow("IdResult", img);
    cv::waitKey(0);
    cv::destroyWindow("IdResult");





    //cv::line(img,
    //    cv::Point2i(0, bbox.at<float>(0, 2)),
    //    cv::Point2i(0, (bbox.at<float>(0, 2 % n))),
    //    cv::Scalar(255, 0, 0), 3, LINE_AA);
    //cv::imshow("IdResult3", img);
    //cv::waitKey(0);

    //cv::line(img,
    //    cv::Point2i(bbox.at<float>(0, 3), 0),
    //    cv::Point2i(bbox.at<float>(0, 3 % n), 0),
    //    cv::Scalar(255, 0, 0), 3, LINE_AA);
    //cv::imshow("IdResult4", img);
    //cv::waitKey(0);


           
    for (int i = 0; i <n; i++) {
        cout << "index i: " << i << endl;

        //cv::line(img, 
        //    cv::Point2i(0, bbox.at<float>(0, i)), 
        //    cv::Point2i(0, bbox.at<float>(0, (i + 1) % n)),
        //    cv::Scalar(255, 0, 0), 3, LINE_AA);

        //cv::line(img,
        //    cv::Point2i(bbox.at<float>(0, i), 0),
        //    cv::Point2i(bbox.at<float>(0, (i + 1) % n), 0),
        //    cv::Scalar(255, 0, 0), 3, LINE_AA);




        //cv::imshow("IdResult", img);
        ////cv::imshow("Result", rectifiedImage);
        //cv::waitKey(0);
        //cv::destroyWindow("IdResult");
    }

    //cv::imshow("Result", rectifiedImage);
    //cv::imshow("IdResult", img);
    //cv::waitKey(0);

    return 0;
}
