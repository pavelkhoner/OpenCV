#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img(300, 450, CV_8UC1);
	// draw dummy image
	img = 0;
	//1.rectangles
	//chor
	for (int i = 0; i < 150; i++)
		for (int j = 0; j < 150; j++)
			img.at<char>(i, j) = 0;
		//bel
	for (int i = 0; i < 150; i++)
		for (int j = 150; j < 300; j++)
			img.at<char>(i, j) = 255;
	//ser
	for (int i = 0; i < 150; i++)
		for (int j = 300; j < 450; j++)
			img.at<char>(i, j) = 127;
     //belniz
	for (int i = 150; i < 300; i++)
		for (int j = 0; j < 150; j++)
			img.at<char>(i, j) = 255;
	///serniz
	for (int i = 150; i < 300; i++)
		for (int j = 150; j < 300; j++)
			img.at<char>(i, j) = 127;
	///krujochki
	int r = 30;
    ///perviy
	cv::circle(img, cv::Point(75, 75), r, 127, -1);
	//vtoroy
	cv::circle(img, cv::Point(225, 75), r, 0, -2);
	//tretiy
	cv::circle(img, cv::Point(375, 75), r, 255, -3);
	//perviyniz
	cv::circle(img, cv::Point(75, 225), r, 0, -4);
	//vtoroyniz
	cv::circle(img, cv::Point(225, 225), r, 255, -5);
	//poslednniz
	cv::circle(img, cv::Point(375, 225), r, 127, -6);

	cv::imwrite("kr.png", img);
	///2.filtr I1
	cv::Mat I;
	float kerI[4]{ 1,0,0,-1 };
	cv::Mat kerI_matrix(2, 2, CV_32FC1, kerI);
	cv::filter2D(img, I, -1, kerI_matrix);
	cv::imwrite("kr1.png", I);

	///3.filtrI2
	cv::Mat II;
	float kerII[4]{ 0,1,-1,0 };
	cv::Mat kerII_matrix(2, 2, CV_32FC1, kerII);
	cv::filter2D(img, II, -1, kerII_matrix);
	cv::imwrite("kr2.png", II);
	///4.

}
