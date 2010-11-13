/*
 * Threshold.h
 *
 *  Created on: 12-11-2010
 *      Author: mateusz
 */

#ifndef THRESHOLD_H_
#define THRESHOLD_H_

#include <cv.h>
#include <highgui.h>
#include <string>
#include <stdexcept>

struct ThresholdedImage {
	cv::Mat maskBelow;
	int meanGrayBelow;
	cv::Mat maskAbove;
	int meanGrayAbove;
};


class Threshold {
public:
	Threshold();
	virtual ~Threshold();
	ThresholdedImage thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold);
	ThresholdedImage thresholdImageOptimal(const cv::Mat& image, const cv::Mat& mask, int threshold, int eps);
};

#endif /* THRESHOLD_H_ */
