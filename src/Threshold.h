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

class Threshold {
public:
	Threshold();
	virtual ~Threshold();
	void thresholdImage(const cv::Mat& image, const cv::Mat& mask, int threshold,
			u_char belowOrEqualValue, u_char aboveValue, cv::Mat& result);

	static const int histogramSize = 256;
	/**
	 * Calculate histogram.
	 * @param image
	 * @param mask
	 * @param histogram This must be allocated array of histogramSize elements type int.
	 */
	void histogram(const cv::Mat& image, const cv::Mat& mask, int *histogram);

	/**
	 *
	 * @param histogram This must be allocated array of histogramSize elements type int.
	 * @return Optimal threshold.
	 */
	int findOptimalThreshold(int *histogram);

	//	void thresholdImageOptimal(const cv::Mat& image, const cv::Mat& mask, int threshold, int eps);
};

#endif /* THRESHOLD_H_ */
