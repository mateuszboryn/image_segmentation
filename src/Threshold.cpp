/*
 * Threshold.cpp
 *
 *  Created on: 12-11-2010
 *      Author: mateusz
 */

#include "Threshold.h"

#include <iostream>

using namespace cv;
using namespace std;

Threshold::Threshold()
{
}

Threshold::~Threshold()
{
}

void Threshold::thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold,
		u_char belowOrEqualValue, u_char aboveValue, cv::Mat& result)
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
				if (image.at<u_int8_t> (y, x) > threshold) {
					result.at<u_int8_t> (y, x) = aboveValue;
				} else {
					result.at<u_int8_t> (y, x) = belowOrEqualValue;
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
				u_int8_t brightness = image.at<u_int8_t> (y, x);
				histogram[brightness]++;
			}
		}
	}
}

int Threshold::findOptimalThreshold(int *histogram)
{
	double sum=0;
	int cnt=0;
	for (int i = 0; i < histogramSize; ++i) {
		sum += histogram[i] * i;
		cnt += histogram[i];
	}
	if (cnt == 0) {
		throw logic_error("empty histogram");
	}
	int currentThreshold = sum / cnt;
	int prevThreshold = currentThreshold;

	int iterations = 0;
	do {
		iterations++;
		double sumBelowOrEqual = 0;
		int cntBelowOrEqual = 0;
		for (int i = 0; i <= currentThreshold; ++i) {
			cntBelowOrEqual += histogram[i];
			sumBelowOrEqual += histogram[i] * i;
		}

		double sumAbove = 0;
		int cntAbove = 0;
		for (int i = currentThreshold + 1; i < histogramSize; ++i) {
			cntAbove += histogram[i];
			sumAbove += histogram[i] * i;
		}

//		double meanBelowOrEqual = cntBelowOrEqual == 0 ? 0 : sumBelowOrEqual / cntBelowOrEqual;
		double meanBelowOrEqual = sumBelowOrEqual / cntBelowOrEqual; //cntBelowOrEqual > 0
		double meanAbove = cntAbove == 0 ? histogramSize - 1 : sumAbove / cntAbove;

		prevThreshold = currentThreshold;
		currentThreshold = (meanBelowOrEqual + meanAbove) / 2;
	} while (abs(prevThreshold - currentThreshold) > 0);

	cout << "Threshold::findOptimalThreshold() iterations = " << iterations << endl;
	return currentThreshold;
}
