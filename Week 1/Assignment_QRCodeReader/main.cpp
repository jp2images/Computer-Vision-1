
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

    cout << bbox.at<float>(0, 0) << endl; //22
    cout << bbox.at<float>(0, 1) << endl; //82
    cout << bbox.at<float>(0, 2) << endl; //126
    cout << bbox.at<float>(0, 3) << endl; //82

    int n = bbox.cols;
           
    for (int i = 0; i < n; i++) {
        cout << "index i: " << i << " :" << bbox.at<float>(0, i) << endl << endl;

        cv::line(img, 
            cv::Point2i(bbox.at<float>(0, i), bbox.at<float>(0, i)),
            cv::Point2i(bbox.at<float>(0,(i + 1) % n), bbox.at<float>(0,(i + 1) % n)),
            cv::Scalar(255, 0, 255), 3, LINE_AA);

        cout << "(" << bbox.at<float>(0, i) << ", " << bbox.at<float>(0, (i + 1) % n) << ")" << endl;



        //cv::line(img,
        //    cv::Point2i(bbox.at<float>(0, i), bbox.at<float>(0, i)),
        //    cv::Point2i(bbox.at<float>(0, (i + 1) % n), bbox.at<float>(0, (i + 1) % n)),
        //    cv::Scalar(255, 0, 255), 3, LINE_AA);

        //cout << "(" << bbox.at<float>(0, i) << ", " << bbox.at<float>(0, (i + 1) % n) << ")" << endl;


        //line(img, 
        //    Point2i(bbox.at<float>(0, i), bbox.at<float>(0, i)), 
        //    Point2i(bbox.at<float>(0, (i + 1) % n), bbox.at<float>(0, (i + 1) % n)), 
        //    Scalar(255, 0, 0), 3, LINE_AA);

        //Internet Sample
        //line(img, 
        //    Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), 
        //    Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), 
        //    Scalar(255, 0, 0), 3);


        cv::imshow("IdResult2", img);
        cv::waitKey(0);
    }


    //cv::imshow("Result", rectifiedImage);
    //cv::imshow("IdResult", img);
    //cv::waitKey(0);

    return 0;
}
