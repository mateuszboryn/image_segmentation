/*
 * SegmentsCollection.h
 *
 *  Created on: 13-11-2010
 *      Author: mateusz
 */

#ifndef SEGMENTSCOLLECTION_H_
#define SEGMENTSCOLLECTION_H_

#include <cv.h>
#include <stdexcept>
#include <vector>
#include <boost/shared_ptr.hpp>

struct Segment {
	cv::Mat image;
	int segmentClass;
	int segmentArea;
};

class SegmentsCollection {
public:
	//SegmentsCollection(int initialCapacity);
	SegmentsCollection(cv::Size imageSize);
	virtual ~SegmentsCollection();

	boost::shared_ptr<Segment> createSegment();
	void removeRecentlyCreatedSegment();

	boost::shared_ptr<Segment> getSegment(size_t index);

	size_t getSegmentsCount() const;

	cv::Size getImageSize() const;

	void clear();

	void merge(const SegmentsCollection& sc);
private:
	cv::Size imageSize;
	std::vector<boost::shared_ptr<Segment> > segments;

};

#endif /* SEGMENTSCOLLECTION_H_ */
