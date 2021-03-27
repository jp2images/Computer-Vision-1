
#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp> //imwrite
#include <opencv2/imgproc.hpp>

#include "dataPath.hpp";


using namespace std;
using namespace cv;

int main() {
    cout << "Hello, World!" << endl;
    cout << "OpenCV version is " << CV_VERSION << endl;

    cv::Mat img = cv::imread(DATA_PATH + "images/truth.png", IMREAD_GRAYSCALE);



    return 0;
}
