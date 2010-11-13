/*
 * ImageComparator.h
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#ifndef IMAGECOMPARATOR_H_
#define IMAGECOMPARATOR_H_

#include <cv.h>
#include <stdexcept>

class ImageComparator {
public:
	ImageComparator(){}
	virtual ~ImageComparator(){}

	template<typename T>
	static bool isEqual(const cv::Mat& image1, const cv::Mat& image2)
	{
		if (image1.type() != image2.type()) {
			throw std::logic_error("image1.type() != image2.type()");
		}
		if (image1.size() != image2.size()) {
			throw std::logic_error("image1.size() != image2.size()");
		}
		if (image1.size().width < 1 || image1.size().height < 1) {
			throw std::logic_error("image1.size().width < 1 || image1.size().height < 1");
		}

		for (int y = 0; y < image1.size().height; ++y) {
			for (int x = 0; x < image1.size().width; ++x) {
				if (image1.at<T> (y, x) != image2.at<T> (y, x)) {
					return false;
				}
			}
		}
		return true;
	}
};

#endif /* IMAGECOMPARATOR_H_ */
