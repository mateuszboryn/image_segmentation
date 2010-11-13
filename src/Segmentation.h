/*
 * Segmentation.h
 *
 *  Created on: Nov 10, 2010
 *      Author: mboryn
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <cv.h>
#include <highgui.h>
#include <string>
#include <stdexcept>

struct ThresholdedImage {
	cv::Mat image;
	cv::Mat maskBelow;
	int meanGrayBelow;
	cv::Mat maskAbove;
	int meanGrayAbove;
};


class Segmentation
{
public:
	Segmentation(const std::string outDir);
	virtual ~Segmentation();

	cv::Mat segmentImage(const cv::Mat& image);

private:
	std::string outDir;
	ThresholdedImage thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold);
	int getMean(const cv::Mat& image, const cv::Mat& mask);
	ThresholdedImage findOptimalThreshold(const cv::Mat& image, const cv::Mat& mask, int threshold, int eps);
	int thresholdImageCnt;

};

#endif /* SEGMENTATION_H_ */
