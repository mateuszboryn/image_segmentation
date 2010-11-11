/*
 * Segmentation.cpp
 *
 *  Created on: Nov 10, 2010
 *      Author: mboryn
 */

#include <iostream>
#include <sstream>
#include "Segmentation.h"

using namespace cv;
using namespace std;

Segmentation::Segmentation(const std::string outDir) :
	outDir(outDir + "/")
{
	// TODO Auto-generated constructor stub

}

Segmentation::~Segmentation()
{
	// TODO Auto-generated destructor stub
}

cv::Mat Segmentation::segmentImage(const cv::Mat& image)
{
	if (image.channels() != 1) {
		cout << "image.channels(): " << image.channels() << endl;
		throw logic_error("image.channels() != 1");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}

	thresholdImageCnt = 0;

	Mat ones = Mat::ones(image.size(), CV_8U);

	int mean = getMean(image, ones);

	cout << "mean: " << mean << endl;

	Mat afterAdaptive;

	adaptiveThreshold(image, afterAdaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 17, 1);
	imwrite((outDir + "adaptive.png").c_str(), afterAdaptive);

	ThresholdedImage first = findOptimalThreshold(image, ones, mean, 1);

	findOptimalThreshold(first.image, first.maskAbove, first.meanGrayAbove, 1);
	findOptimalThreshold(first.image, first.maskBelow, first.meanGrayBelow, 1);

	imwrite((outDir + "0.png").c_str(), image);

	return image;
}

ThresholdedImage Segmentation::thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold)
{
	ThresholdedImage result;
	double sumBelow = 0;
	int cntBelow = 0;
	double sumAbove = 0;
	int cntAbove = 0;

	result.image = image;
	result.maskAbove = Mat::zeros(image.size(), CV_8U);
	result.maskBelow = Mat::zeros(image.size(), CV_8U);

	Size imageSize = image.size();
	for (int x = 0; x < imageSize.width; ++x) {
		for (int y = 0; y < imageSize.height; ++y) {
			if (mask.at <u_int8_t> (y, x) != 0) {
				if (image.at <u_int8_t> (y, x) >= threshold) {
					result.maskAbove.at <u_int8_t> (y, x) = 255;
					sumAbove += image.at <u_int8_t> (y, x);
					++cntAbove;
				} else {
					result.maskBelow.at <u_int8_t> (y, x) = 255;
					sumBelow += image.at <u_int8_t> (y, x);
					++cntBelow;
				}
			}
		}
	}

	result.meanGrayAbove = cntAbove > 0 ? sumAbove / cntAbove : 0;
	result.meanGrayBelow = cntBelow > 0 ? sumBelow / cntBelow : 0;

	thresholdImageCnt++;

	stringstream ss;
	ss << outDir << "thresholdImage_" << thresholdImageCnt << "_above.png";
	cout << "Saving image: " << ss.str() << endl;
	imwrite(ss.str().c_str(), result.maskAbove);

	ss.str("");
	ss << outDir << "thresholdImage_" << thresholdImageCnt << "_below.png";
	cout << "Saving image: " << ss.str() << endl;
	imwrite(ss.str().c_str(), result.maskBelow);

	return result;
}

int Segmentation::getMean(const cv::Mat& image, const cv::Mat& mask)
{
	double sum = 0;
	int cnt = 0;

	Size imageSize = image.size();
	for (int x = 0; x < imageSize.width; ++x) {
		for (int y = 0; y < imageSize.height; ++y) {
			if (mask.at <u_int8_t> (y, x) != 0) {
				sum += image.at <u_int8_t> (y, x);
				++cnt;
			}
		}
	}
	if (cnt == 0) {
		return 0;
	}
	return sum / cnt;
}

ThresholdedImage Segmentation::findOptimalThreshold(const cv::Mat& image, const cv::Mat& mask, int threshold, int eps)
{
	ThresholdedImage result;
	int prevThreshold = threshold;

	int i = 0;
	do {
		cout << "Segmentation::findOptimalThreshold (" << i << ") threshold = " << threshold << endl;
		result = thresholdImage(image, mask, threshold);
		cout << "Segmentation::findOptimalThreshold result.meanGrayAbove = " << result.meanGrayAbove << endl;
		cout << "Segmentation::findOptimalThreshold result.meanGrayBelow = " << result.meanGrayBelow << endl;

		prevThreshold = threshold;
		threshold = (result.meanGrayAbove + result.meanGrayBelow) / 2;
		++i;

	} while (abs(prevThreshold - threshold) > eps);

	return result;
}
