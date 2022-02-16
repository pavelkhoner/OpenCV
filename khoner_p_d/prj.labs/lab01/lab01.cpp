#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img(180, 768, CV_8UC1);
	// draw dummy image
	img = 0;
	cv::Rect2d rc = { 0, 0, 768, 60 };
	///// 1.gradient
	for (int i = 0; i < 180; i++)
		for (int j = 0; j < 768; j++)
		{
			img.at<char>(i, j) = j / 3;
		}
	cv::rectangle(img, rc, { 100 }, 1);
	rc.y += rc.height;
	////check ur time
	auto start = std::chrono::high_resolution_clock::now();
	 //// 2.gamma correction with pow
	cv::Mat tmp(img);
	tmp.convertTo(tmp, CV_32FC1);
	tmp = tmp / 255.0f;
	cv::pow(tmp, 2.3f, tmp);
	tmp = tmp * 255.0f;
	tmp.convertTo(tmp, CV_8UC1);
	////stop time
	auto stop = std::chrono::high_resolution_clock::now();
	///enter time
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "G1 = " << duration.count() << " ms"
		<< "\n";
	tmp(rc).copyTo(img(rc));

	cv::rectangle(img, rc, { 250 }, 1);
	rc.y += rc.height;
	////check ur time
	start = std::chrono::high_resolution_clock::now();
	//// gamma corection with for
	for(int i = rc.y; i < 180; i++) 
		for (int j = 0; j < 768; j++) {
			img.at<uchar>(i, j) = pow(img.at<uchar>(i, j) / 255.0f, 2.3f) * 255.0f;
		}
	////time
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "G2 = " << duration.count() << " m"
		<< "\n";
	
	cv::rectangle(img, rc, { 150 }, 1);

	// save result
	cv::imwrite("lab01.png", img);

}
