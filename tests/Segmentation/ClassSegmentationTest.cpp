#include <unistd.h>
#include <iostream>
#include "ImageComparator.h"

#include "ClassSegmentation.h"
#include <highgui.h>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

#define DATA_DIR "../../../tests/data/Segmentation/"
#define RESULTS_DIR "../../../tests/results/Segmentation/"

using namespace cv;

BOOST_AUTO_TEST_CASE( PWD )
{
	char *pwd = get_current_dir_name();
	cout << "Current working directory: \"" << pwd << "\"\n";
	// workspace/image_segmentation/build/tests/Threshold
	free(pwd);
}

BOOST_AUTO_TEST_CASE( Params )
{
	{
		BOOST_CHECK_THROW(ClassSegmentation classSegmentation(Size(0,1)), logic_error);
	}
	{
		BOOST_CHECK_THROW(ClassSegmentation classSegmentation(Size(1,0)), logic_error);
	}

	Size s(50, 50);
	ClassSegmentation classSegmentation(s);

	Mat m(Size(50, 49), CV_8U);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, 1), logic_error);
	m = Mat(Size(49, 50), CV_8U);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, 1), logic_error);

	m = Mat(Size(50, 50), CV_8S);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, 1), logic_error);
}

BOOST_AUTO_TEST_CASE(Image)
{
	Size s(50, 50);
	ClassSegmentation classSegmentation(s);

	Mat image = imread(DATA_DIR "1.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	classSegmentation.segmentation(image, 1);
	BOOST_CHECK_EQUAL(classSegmentation.getSegments().size(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[0], imread(DATA_DIR "1.bmp", -1)));
	imwrite(RESULTS_DIR "segment_1.bmp", classSegmentation.getSegments()[0]);

	image = imread(DATA_DIR "2.bmp", -1);
	classSegmentation.segmentation(image, 1);
	BOOST_CHECK_EQUAL(classSegmentation.getSegments().size(), 0);

	image = imread(DATA_DIR "3.bmp", -1);
	classSegmentation.segmentation(image, 1);
	BOOST_CHECK_EQUAL(classSegmentation.getSegments().size(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[0], imread(DATA_DIR "3.bmp", -1)));
	imwrite(RESULTS_DIR "segment_3.bmp", classSegmentation.getSegments()[0]);

	image = imread(DATA_DIR "4.bmp", -1);
	classSegmentation.segmentation(image, 1);
	BOOST_CHECK_EQUAL(classSegmentation.getSegments().size(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[0], imread(DATA_DIR "4.bmp", -1)));
	imwrite(RESULTS_DIR "segment_4.bmp", classSegmentation.getSegments()[0]);

	image = imread(DATA_DIR "5.bmp", -1);
	classSegmentation.segmentation(image, 1);
	BOOST_CHECK_EQUAL(classSegmentation.getSegments().size(), 14);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[0], imread(DATA_DIR "6.bmp", -1)));
	imwrite(RESULTS_DIR "segment_5.bmp", classSegmentation.getSegments()[0]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[1], imread(DATA_DIR "7.bmp", -1)));
	imwrite(RESULTS_DIR "segment_6.bmp", classSegmentation.getSegments()[1]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[2], imread(DATA_DIR "8.bmp", -1)));
	imwrite(RESULTS_DIR "segment_7.bmp", classSegmentation.getSegments()[2]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[3], imread(DATA_DIR "9.bmp", -1)));
	imwrite(RESULTS_DIR "segment_8.bmp", classSegmentation.getSegments()[3]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[4], imread(DATA_DIR "10.bmp", -1)));
	imwrite(RESULTS_DIR "segment_9.bmp", classSegmentation.getSegments()[4]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[5], imread(DATA_DIR "11.bmp", -1)));
	imwrite(RESULTS_DIR "segment_10.bmp", classSegmentation.getSegments()[5]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[6], imread(DATA_DIR "12.bmp", -1)));
	imwrite(RESULTS_DIR "segment_11.bmp", classSegmentation.getSegments()[6]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[7], imread(DATA_DIR "13.bmp", -1)));
	imwrite(RESULTS_DIR "segment_12.bmp", classSegmentation.getSegments()[7]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[8], imread(DATA_DIR "14.bmp", -1)));
	imwrite(RESULTS_DIR "segment_13.bmp", classSegmentation.getSegments()[8]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[9], imread(DATA_DIR "15.bmp", -1)));
	imwrite(RESULTS_DIR "segment_14.bmp", classSegmentation.getSegments()[9]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[10], imread(DATA_DIR "16.bmp", -1)));
	imwrite(RESULTS_DIR "segment_15.bmp", classSegmentation.getSegments()[10]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[11], imread(DATA_DIR "17.bmp", -1)));
	imwrite(RESULTS_DIR "segment_16.bmp", classSegmentation.getSegments()[11]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[12], imread(DATA_DIR "18.bmp", -1)));
	imwrite(RESULTS_DIR "segment_17.bmp", classSegmentation.getSegments()[12]);

	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(classSegmentation.getSegments()[13], imread(DATA_DIR "19.bmp", -1)));
	imwrite(RESULTS_DIR "segment_18.bmp", classSegmentation.getSegments()[13]);
}

