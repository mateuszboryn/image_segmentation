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

int Segmentation::imageCnt = 0;

Segmentation::Segmentation(cv::Size imageSize, const std::string outDir) :
	imageSize(imageSize), outDir(outDir + "/") //, cs(imageSize)
{
}

Segmentation::~Segmentation()
{
}

void Segmentation::segmentImage(cv::Mat& image)
{
	if (image.size() != imageSize) {
		throw logic_error("image.size() != imageSize");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}

	this->image = image;

	recurseLevel = 0;
	foundSegments.clear();

	Mat mask(imageSize, CV_8U);
	mask.setTo(255);

	stringstream ss;
	ss << outDir << "segmentImage_" << imageCnt << ".png";
	cout << "segmentImage(): Writing image: " << ss.str() << endl;
	imwrite(ss.str().c_str(), mask);
	imageCnt++;

	segmentRecursive(mask);
}

void Segmentation::segmentRecursive(cv::Mat& mask)
{
	int histogram[Threshold::histogramSize];
	th.histogram(image, mask, histogram);
	if (checkTerminationCondition(histogram)) {
		foundSegments.push_back(mask);
		return;
	}

	int threshold = th.findOptimalThreshold(histogram);
	Mat thresholded = Mat::zeros(imageSize, CV_8U);
	th.thresholdImage(image, mask, threshold, 127, 255, thresholded);

	stringstream ss;
	ss << outDir << "segmentRecursive_" << imageCnt << ".png";
	cout << "segmentRecursive(): Writing image: " << ss.str() << endl;
	imwrite(ss.str().c_str(), thresholded);
	imageCnt++;

	ClassSegmentation cs(imageSize);
	cs.segmentation(thresholded, minSegmentArea);

	for (int i = 0; i < cs.getSegments().size(); ++i) {
		segmentRecursive(cs.getSegments()[i]);
	}
}

bool Segmentation::checkTerminationCondition(int *histogram)
{
	// TODO: policzyc wariancje
	double sum = 0;
	double cnt = 0;
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		sum += i * histogram[i];
		cnt += histogram[i];
	}
	double mean = sum / cnt;

	sum = 0;
	cnt = 0;
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		sum += (i - mean) * (i - mean) * histogram[i];
		cnt += histogram[i];
	}
	double variance = sum / (cnt * Threshold::histogramSize * Threshold::histogramSize);

//	cout << "Segmentation::checkTerminationCondition(): sum = " << sum << endl;
//	cout << "Segmentation::checkTerminationCondition(): cnt = " << cnt << endl;
//	cout << "Segmentation::checkTerminationCondition(): Threshold::histogramSize = " << Threshold::histogramSize << endl;
//	cout << "Segmentation::checkTerminationCondition(): variance = " << variance << endl;

	// TODO: porwonac wariancje
	if (variance < minVariance) {
		return true;
	}
	return false;
}

SegmentsVector& Segmentation::getFoundSegments()
{
	return foundSegments;
}

void Segmentation::setMinVariance(double minVariance)
{
	this->minVariance = minVariance;
}

void Segmentation::setMinSegmentArea(int minSegmentArea)
{
	this->minSegmentArea = minSegmentArea;
}
