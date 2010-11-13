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

ThresholdedImage Threshold::thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold)
{
	ThresholdedImage result;
	double sumBelow = 0;
	int cntBelow = 0;
	double sumAbove = 0;
	int cntAbove = 0;

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

//	thresholdImageCnt++;
//
//	stringstream ss;
//	ss << outDir << "thresholdImage_" << thresholdImageCnt << "_above.png";
//	cout << "Saving image: " << ss.str() << endl;
//	imwrite(ss.str().c_str(), result.maskAbove);
//
//	ss.str("");
//	ss << outDir << "thresholdImage_" << thresholdImageCnt << "_below.png";
//	cout << "Saving image: " << ss.str() << endl;
//	imwrite(ss.str().c_str(), result.maskBelow);

	return result;
}

ThresholdedImage Threshold::thresholdImageOptimal(const cv::Mat& image, const cv::Mat& mask, int threshold, int eps)
{
	ThresholdedImage result;
	int prevThreshold = threshold;

	int i = 0;
	do {
//		cout << "Segmentation::findOptimalThreshold (" << i << ") threshold = " << threshold << endl;
		result = thresholdImage(image, mask, threshold);
//		cout << "Segmentation::findOptimalThreshold result.meanGrayAbove = " << result.meanGrayAbove << endl;
//		cout << "Segmentation::findOptimalThreshold result.meanGrayBelow = " << result.meanGrayBelow << endl;

		prevThreshold = threshold;
		threshold = (result.meanGrayAbove + result.meanGrayBelow) / 2;
		++i;

	} while (abs(prevThreshold - threshold) > eps);

	return result;
}

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
