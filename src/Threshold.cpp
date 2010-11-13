/*
 * Threshold.cpp
 *
 *  Created on: 12-11-2010
 *      Author: mateusz
 */

#include "Threshold.h"

using namespace cv;
using namespace std;

Threshold::Threshold()
{
}

Threshold::~Threshold()
{
}

void Threshold::thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold,
		u_char belowValue, u_char aboveOrEqualValue, cv::Mat& result)
{
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}
	if (mask.type() != CV_8U) {
		throw logic_error("mask.type() != CV_8U");
	}
	if (result.type() != CV_8U) {
		throw logic_error("mask.type() != CV_8U");
	}
	if (image.size() != mask.size()) {
		throw logic_error("image.size() != mask.size()");
	}
	if (image.size() != result.size()) {
		throw logic_error("image.size() != result.size()");
	}
	if (!(threshold >= 0 && threshold <= 255)) {
		throw logic_error("!(threshold >= 0 && threshold <= 255)");
	}

	Size imageSize = image.size();
	for (int y = 0; y < imageSize.height; ++y) {
		for (int x = 0; x < imageSize.width; ++x) {
			if (mask.at<u_int8_t> (y, x) != 0) {
				if (image.at<u_int8_t> (y, x) >= threshold) {
					result.at<u_int8_t> (y, x) = aboveOrEqualValue;
				} else {
					result.at<u_int8_t> (y, x) = belowValue;
				}
			}
		}
	}
}

void Threshold::histogram(const cv::Mat& image, const cv::Mat& mask, int *histogram)
{
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}
	if (mask.type() != CV_8U) {
		throw logic_error("mask.type() != CV_8U");
	}
	if (image.size() != mask.size()) {
		throw logic_error("image.size() != mask.size()");
	}
	if (image.size().width < 1 || image.size().height < 1) {
		throw logic_error("image.size().width < 1 || image.size().height < 1");
	}

	for (int i = 0; i < histogramSize; ++i) {
		histogram[i] = 0;
	}

	Size imageSize = image.size();
	for (int y = 0; y < imageSize.height; ++y) {
		for (int x = 0; x < imageSize.width; ++x) {
			if (mask.at<u_int8_t> (y, x) != 0) {
				histogram[image.at<u_int8_t> (y, x)]++;
			}
		}
	}
}

//ThresholdedImage Threshold::thresholdImageOptimal(const cv::Mat& image, const cv::Mat& mask,
//		int threshold, int eps)
//{
//	ThresholdedImage result;
//	int prevThreshold = threshold;
//
//	int i = 0;
//	do {
//		//		cout << "Segmentation::findOptimalThreshold (" << i << ") threshold = " << threshold << endl;
//		result = thresholdImage(image, mask, threshold);
//		//		cout << "Segmentation::findOptimalThreshold result.meanGrayAbove = " << result.meanGrayAbove << endl;
//		//		cout << "Segmentation::findOptimalThreshold result.meanGrayBelow = " << result.meanGrayBelow << endl;
//
//		prevThreshold = threshold;
//		threshold = (result.meanGrayAbove + result.meanGrayBelow) / 2;
//		++i;
//
//	} while (abs(prevThreshold - threshold) > eps);
//
//	return result;
//}

/*int Segmentation::getMean(const cv::Mat& image, const cv::Mat& mask)
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
 }*/
