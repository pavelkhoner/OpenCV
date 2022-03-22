#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>

void Color_Reduction(cv::Mat& img, uchar div = 64)
{
	for (int y =  0; y < img.rows; ++y)
	{
		uchar* data = img.ptr(y);
		for (int x = 0; x < img.cols * img.channels(); ++x)
		{
			data[x] = data[x] - data[x] % div + div / 2;
		}
	}
}

void Binarisiotion(cv::Mat& img, uchar threshold)
{
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);
}

int main()
{

	cv::VideoCapture video("C:/sandbox/khoner_p_d/data/khoner_p_d_data_video1.MOV");
	if (!video.isOpened())
	{
		return -1;
	}

	cv::Mat frame[3];
	uint16_t frames_N = video.get(cv::CAP_PROP_FRAME_COUNT);

	for (int i = 0; i < frames_N; ++i)
	{
		if (i == (frames_N / 5) * 2)
		{
			video >> frame[0];
		}

		if (i == (frames_N / 5) * 3)
		{
			video >> frame[1];
		}

		if (i == (frames_N / 5) * 4)
		{
			video >> frame[2];
		}

		video.grab();
	}

	for (int i = 0; i < 3; ++i)
	{
		cv::imwrite("frame_" + std::to_string(i) + ".png", frame[i]);
	}

	cv::Mat Mask;

	for (int i = 0; i < 3; ++i)
	{
		Color_Reduction(frame[i]);
		cv::imwrite("frame_" + std::to_string(i) + "_CR.png", frame[i]);
		Binarisiotion(frame[i], 150);
		cv::imwrite("frame_" + std::to_string(i) + "_BINAR.png", frame[i]);
		cv::morphologyEx(frame[i], Mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(40, 40)));
		cv::imwrite("frame_" + std::to_string(i) + "_MORPH.png", Mask);

		cv::Mat centroids, stats, res;
		int n = cv::connectedComponentsWithStats(Mask, res, stats, centroids);
		std::vector<cv::Vec3b> labels(n);
		int max = 0, imax = 0;
		for (int j = 1; j < n; j++)
		{
			if (max < stats.at<int>(j, cv::CC_STAT_AREA))
			{
				max = stats.at<int>(j, cv::CC_STAT_AREA);
				imax = j;
			}
		}
		for (int j = 0; j < n; ++j)
		{
			labels[j] = cv::Vec3b(0, 0, 0);
		}
		labels[imax] = cv::Vec3b(255, 255, 255);
		cv::Mat exit(Mask.rows, Mask.cols, CV_8UC3);
		for (int a = 0; a < exit.rows; ++a)
		{
			for (int b = 0; b < exit.cols; ++b)
			{
				int label = res.at<int>(a, b);
				cv::Vec3b& pixel = exit.at<cv::Vec3b>(a, b);
				pixel = labels[label];
			}
		}
		cv::imwrite("frame_" + std::to_string(i) + "_CONECTED.png", exit);
	}

	return 0;
}
