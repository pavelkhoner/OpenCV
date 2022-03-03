#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
/// канальность
cv::Mat BBC(cv::Mat img, int imgcolor = 0) {

	cv::Mat output_img(img.cols, img.rows, img.type());
	cv::Mat zmat = cv::Mat::zeros(cv::Size(img.cols, img.rows), CV_8UC1);

	std::vector<cv::Mat> chanel;
	std::vector<cv::Mat> sp;

	cv::split(img, sp);

	switch (imgcolor)
	{
	case 0:
		chanel.push_back(sp[0]);
		chanel.push_back(zmat);
		chanel.push_back(zmat);
		break;
	case 1:
		chanel.push_back(zmat);
		chanel.push_back(sp[1]);
		chanel.push_back(zmat);
		break;
	case 2:
		chanel.push_back(zmat);
		chanel.push_back(zmat);
		chanel.push_back(sp[2]);
		break;
	default:
		break;
	}

	cv::merge(chanel, output_img);

	return output_img;
}

int main() {
	// инициализируем наше изображение
	const std::string ipath = "C:/sandbox/khoner_p_d/data/cross_0256x0256.png";

	cv::Mat inimg = cv::imread(ipath, cv::IMREAD_COLOR);

	// сохран€ем его с 25%
	cv::imwrite("cross_0256x0256_025.jpg", inimg, { cv::ImwriteFlags::IMWRITE_JPEG_QUALITY, 25 });

	// создадим "cross_png_img"
	cv::Mat cross_png_img, temp, temp2;
	cv::Mat rc = BBC(inimg, 2);
	cv::Mat gc = BBC(inimg, 1);
	cv::Mat bc = BBC(inimg, 0);

	cv::hconcat(inimg, rc, temp);
	cv::hconcat(gc, bc, temp2);
	cv::vconcat(temp, temp2, cross_png_img);

	cv::imwrite("cross_0256x0256_png_channels.png", cross_png_img);

	//и еще одно

	cv::Mat jpg_img = cv::imread("./cross_0256x0256_025.jpg", cv::IMREAD_COLOR);

	cv::Mat cross_jpg_img, temp3, temp4;
	cv::Mat rc_m = BBC(jpg_img, 2);
	cv::Mat gc_m = BBC(jpg_img, 1);
	cv::Mat bc_m = BBC(jpg_img, 0);

	cv::hconcat(jpg_img, rc_m, temp3);
	cv::hconcat(gc_m, bc_m, temp4);
	cv::vconcat(temp3, temp4, cross_jpg_img);

	cv::imwrite("cross_0256x0256_jpg_channels.png", cross_jpg_img);

	// √√√√√»»—“ќ√–јћћјј

	std::vector<int> hist_size = { 256 };
	std::vector<float> range = { 0, 256 };

	cv::Mat png_blue_hist, png_green_hist, png_red_hist;

	std::vector<cv::Mat> png_channels(3);
	cv::split(inimg, png_channels);

	cv::calcHist(std::vector<cv::Mat>{ png_channels[0] }, { 0 }, cv::Mat(), png_blue_hist, hist_size, range, true);
	cv::calcHist(std::vector<cv::Mat>{ png_channels[1] }, { 0 }, cv::Mat(), png_green_hist, hist_size, range, true);
	cv::calcHist(std::vector<cv::Mat>{ png_channels[2] }, { 0 }, cv::Mat(), png_red_hist, hist_size, range, true);

	cv::Mat png_hist_image(1024, 1024, CV_8UC3, cv::Scalar(255, 255, 255));

	for (int i = 1; i < hist_size[0]; i++) {
		cv::line(png_hist_image, cv::Point(4 * (i - 1), png_blue_hist.at<float>(i - 1)), cv::Point(4 * i, png_blue_hist.at<float>(i)), cv::Scalar(255, 0, 0), 2, 8, 0);
		cv::line(png_hist_image, cv::Point(4 * (i - 1), png_green_hist.at<float>(i - 1)), cv::Point(4 * i, png_green_hist.at<float>(i)), cv::Scalar(0, 255, 0), 2, 8, 0);
		cv::line(png_hist_image, cv::Point(4 * (i - 1), png_red_hist.at<float>(i - 1)), cv::Point(4 * i, png_red_hist.at<float>(i)), cv::Scalar(0, 0, 255), 2, 8, 0);
	}

	cv::imwrite("png_hist.png", png_hist_image);


	cv::Mat jpg_blue_hist, jpg_green_hist, jpg_red_hist;

	std::vector<cv::Mat> jpg_channels(3);
	///сплитаем картинки
	cv::split(jpg_img, jpg_channels);
////красный
	cv::calcHist(std::vector<cv::Mat>{ jpg_channels[2] }, { 0 }, cv::Mat(), jpg_red_hist, hist_size, range, true);
	//// зеленый
	cv::calcHist(std::vector<cv::Mat>{ jpg_channels[1] }, { 0 }, cv::Mat(), jpg_green_hist, hist_size, range, true);
	     ////синий
	cv::calcHist(std::vector<cv::Mat>{ jpg_channels[0] }, { 0 }, cv::Mat(), jpg_blue_hist, hist_size, range, true);

	cv::Mat jpg_hist_image(1024, 1024, CV_8UC3, cv::Scalar(255, 255, 255));

	for (int i = 1; i < hist_size[0]; i++) {
		cv::line(jpg_hist_image, cv::Point(4 * (i - 1), jpg_blue_hist.at<float>(i - 1)), cv::Point(4 * i, jpg_blue_hist.at<float>(i)), cv::Scalar(255, 0, 0), 2, 8, 0);
		cv::line(jpg_hist_image, cv::Point(4 * (i - 1), jpg_green_hist.at<float>(i - 1)), cv::Point(4 * i, jpg_green_hist.at<float>(i)), cv::Scalar(0, 255, 0), 2, 8, 0);
		cv::line(jpg_hist_image, cv::Point(4 * (i - 1), jpg_red_hist.at<float>(i - 1)), cv::Point(4 * i, jpg_red_hist.at<float>(i)), cv::Scalar(0, 0, 255), 2, 8, 0);
	}

	cv::imwrite("jpg_hist.png", jpg_hist_image);


	return 0;
}