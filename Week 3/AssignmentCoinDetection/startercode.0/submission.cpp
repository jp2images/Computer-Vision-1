// Coin Detection Assignment
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

//#include "dataPath.hpp";

using namespace std;
using namespace cv;


void displayImage(Mat image){
	imshow("Image",image);
	waitKey(0);
	destroyAllWindows();
}

Mat displayConnectedComponents(Mat &im)
{
	// Make a copy of the image
	Mat imLabels = im.clone();

	// First let's find the min and max values in imLabels
	Point minLoc, maxLoc;
	double min, max;

	// The following line finds the min and max pixel values
	// and their locations in an image.
	minMaxLoc(imLabels, &min, &max, &minLoc, &maxLoc);

	// Normalize the image so the min value is 0 and max value is 255.
	imLabels = 255 * (imLabels - min) / (max - min);

	// Convert image to 8-bits
	imLabels.convertTo(imLabels, CV_8U);

	// Apply a color map
	Mat imColorMap;
	applyColorMap(imLabels, imColorMap, COLORMAP_JET);

	return imColorMap;
}

//int main(){
//	
//	// Image path
//	string imagePath = DATA_PATH + "images/CoinsA.png";
//	// Read image
//	// Store it in the variable image
//	///
//	/// YOUR CODE HERE
//	///
//	Mat imageCopy = image.clone();
//	
//	displayImage(image);
//	
//	// Convert image to grayscale
//	// Store it in the variable imageGray
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageGray);
//	
//	// Split cell into channels
//	// Store them in variables imageB, imageG, imageR
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageB);
//	displayImage(imageG);
//	displayImage(imageR);
//	
//	// Perform thresholding
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Modify as required
//	displayImage(dst);
//	
//	// Perform morphological operations
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageDilated);
//	
//	// Get structuring element/kernel which will be used for dilation
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageEroded);
//	
//	// Setup SimpleBlobDetector parameters.
//	SimpleBlobDetector::Params params;
//
//	params.blobColor = 0;
//
//	params.minDistBetweenBlobs = 2;
//
//	// Filter by Area
//	params.filterByArea = false;
//
//	// Filter by Circularity
//	params.filterByCircularity = true;
//	params.minCircularity = 0.8;
//
//	// Filter by Convexity
//	params.filterByConvexity = true;
//	params.minConvexity = 0.8;
//
//	// Filter by Inertia
//	params.filterByInertia = true;
//	params.minInertiaRatio = 0.8;
//	
//	// Set up detector with params
//	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
//	
//	// Detect blobs
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print number of coins detected
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Mark coins using image annotation concepts we have studied so far
//	int x,y;
//	int radius;
//	double diameter;
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(image);
//	
//	// Find connected components
//	// Use displayConnectedComponents function provided above
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(colorMap);
//	
//	// Find all contours in the image
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print the number of contours found
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Draw all contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Remove the inner contours
//	// Display the result
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(image);
//	
//	// Print area and perimeter of all contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print maximum area of contour
//	// This will be the box that we want to remove
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Remove this contour and plot others
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Fit circles on coins
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(image);
//	
//	// Image path
//	imagePath = DATA_PATH + "images/CoinsB.png";
//	// Read image
//	// Store it in variable image
//	///
//	/// YOUR CODE HERE
//	///
//	imageCopy = image.clone();
//	
//	// Convert image to grayscale
//	// Store it in the variable imageGray
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageGray);
//	
//	// Split cell into channels
//	// Store them in variables imageB, imageG, imageR
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(imageB);
//	displayImage(imageG);
//	displayImage(imageR);
//	
//	// Perform thresholding
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(dst);
//	
//	// Perform morphological operations
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Setup SimpleBlobDetector parameters.
//
//	params.blobColor = 0;
//
//	params.minDistBetweenBlobs = 2;
//
//	// Filter by Area
//	params.filterByArea = false;
//
//	// Filter by Circularity
//	params.filterByCircularity = true;
//	params.minCircularity = 0.8;
//
//	// Filter by Convexity
//	params.filterByConvexity = true;
//	params.minConvexity = 0.8;
//
//	// Filter by Inertia
//	params.filterByInertia = true;
//	params.minInertiaRatio = 0.8;
//	
//	// Set up detector with params
//	detector = SimpleBlobDetector::create(params);
//	
//	// Detect blobs
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print number of coins detected
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Mark coins using image annotation concepts we have studied so far
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Find connected components
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Find all contours in the image
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print the number of contours found
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Draw all contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Remove the inner contours
//	// Display the result
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(image);
//	
//	// Print area and perimeter of all contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print maximum area of contour
//	// This will be the box that we want to remove
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Remove this contour and plot others
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Print area and perimeter of all contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Remove contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Draw revised contours
//	///
//	/// YOUR CODE HERE
//	///
//	
//	// Fit circles on coins
//	///
//	/// YOUR CODE HERE
//	///
//	
//	displayImage(image);
//	
//	return 0;
//}