/*
 * ClassSegmentation.cpp
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#include "ClassSegmentation.h"

using namespace std;
using namespace cv;

ClassSegmentation::ClassSegmentation(cv::Size imageSize) :
	imageSize(imageSize)
{
	if (imageSize.width < 1 || imageSize.height < 1) {
		throw logic_error("imageSize.width < 1 || imageSize.height < 1");
	}
}

ClassSegmentation::~ClassSegmentation()
{
}

void ClassSegmentation::segmentation(const cv::Mat& originalImage, int minSegmentArea)
{
	image = originalImage.clone();
	if (image.size() != imageSize) {
		throw logic_error("image.size() != visitedPixels.size()");
	}
	if (image.type() != CV_8U) {
		throw logic_error("image.type() != CV_8U");
	}

	segments.clear();

	int w = image.size().width;
	int h = image.size().height;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			if (image.at<u_int8_t> (y, x) != 0) {
				int area = 0;
				cv::Mat segment = extractSegment(y, x, area);
				if (area >= minSegmentArea) {
					segments.push_back(segment);
				}
			}
		}
	}
}

cv::Mat ClassSegmentation::extractSegment(int y, int x, int& area)
{
	u_int8_t colorClass = image.at<u_int8_t> (y, x);
	int w = image.size().width - 1, h = image.size().height - 1;
	area = 0;

	while (!points.empty()) {
		points.pop();
	}

	points.push(Point(x, y));
	image.at<u_int8_t> (points.top()) = 0;

	Mat segment = Mat::zeros(imageSize, CV_8U);
	while (!points.empty()) {
		Point p = points.top();
		points.pop();

		segment.at<u_int8_t> (p) = 255;
		//		s->image.at<u_int8_t> (p) = 255;
		area++;
		if (p.x > 0) { // left
			Point newP(p.x - 1, p.y);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x > 0 && p.y > 0) { // left upper
			Point newP(p.x - 1, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.y > 0) { // upper
			Point newP(p.x, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w && p.y > 0) { // right upper
			Point newP(p.x + 1, p.y - 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w) { // right
			Point newP(p.x + 1, p.y);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x < w && p.y < h) { // right lower
			Point newP(p.x + 1, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.y < h) { // lower
			Point newP(p.x, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
		if (p.x > 0 && p.y < h) { // left lower
			Point newP(p.x - 1, p.y + 1);
			if (image.at<u_int8_t> (newP) == colorClass) {
				image.at<u_int8_t> (newP) = 0;
				points.push(newP);
			}
		}
	}
	return segment;
}

SegmentsVector& ClassSegmentation::getSegments()
{
	return segments;
}
