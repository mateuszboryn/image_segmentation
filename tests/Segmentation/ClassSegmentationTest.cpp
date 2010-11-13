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
	SegmentsCollection sc(s);
	ClassSegmentation classSegmentation(s);

	Mat m(Size(50, 49), CV_8U);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, sc, 1), logic_error);
	m = Mat(Size(49, 50), CV_8U);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, sc, 1), logic_error);

	m = Mat(Size(50, 50), CV_8S);
	BOOST_CHECK_THROW(classSegmentation.segmentation(m, sc, 1), logic_error);
}

BOOST_AUTO_TEST_CASE(Image)
{
	Size s(50, 50);
	SegmentsCollection sc(s);
	ClassSegmentation classSegmentation(s);

	Mat image = imread(DATA_DIR "1.bmp", -1);
	BOOST_CHECK(s == image.size());
	BOOST_CHECK(image.type() == CV_8U);

	classSegmentation.segmentation(image, sc, 1);
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(0)->image, imread(DATA_DIR "1.bmp", -1)));
	imwrite(RESULTS_DIR "segment_1.bmp", sc.getSegment(0)->image);

	image = imread(DATA_DIR "2.bmp", -1);
	classSegmentation.segmentation(image, sc, 1);
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 0);

	image = imread(DATA_DIR "3.bmp", -1);
	classSegmentation.segmentation(image, sc, 1);
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(0)->image, imread(DATA_DIR "3.bmp", -1)));
	imwrite(RESULTS_DIR "segment_3.bmp", sc.getSegment(0)->image);

	image = imread(DATA_DIR "4.bmp", -1);
	classSegmentation.segmentation(image, sc, 1);
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 1);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(0)->image, imread(DATA_DIR "4.bmp", -1)));
	imwrite(RESULTS_DIR "segment_4.bmp", sc.getSegment(0)->image);

	image = imread(DATA_DIR "5.bmp", -1);
	classSegmentation.segmentation(image, sc, 1);
	BOOST_CHECK_EQUAL(sc.getSegmentsCount(), 14);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(0)->image, imread(DATA_DIR "6.bmp", -1)));
	imwrite(RESULTS_DIR "segment_5.bmp", sc.getSegment(0)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(1)->image, imread(DATA_DIR "7.bmp", -1)));
	imwrite(RESULTS_DIR "segment_6.bmp", sc.getSegment(1)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(2)->image, imread(DATA_DIR "8.bmp", -1)));
	imwrite(RESULTS_DIR "segment_7.bmp", sc.getSegment(2)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(3)->image, imread(DATA_DIR "9.bmp", -1)));
	imwrite(RESULTS_DIR "segment_8.bmp", sc.getSegment(3)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(4)->image, imread(DATA_DIR "10.bmp", -1)));
	imwrite(RESULTS_DIR "segment_9.bmp", sc.getSegment(4)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(5)->image, imread(DATA_DIR "11.bmp", -1)));
	imwrite(RESULTS_DIR "segment_10.bmp", sc.getSegment(5)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(6)->image, imread(DATA_DIR "12.bmp", -1)));
	imwrite(RESULTS_DIR "segment_11.bmp", sc.getSegment(6)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(7)->image, imread(DATA_DIR "13.bmp", -1)));
	imwrite(RESULTS_DIR "segment_12.bmp", sc.getSegment(7)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(8)->image, imread(DATA_DIR "14.bmp", -1)));
	imwrite(RESULTS_DIR "segment_13.bmp", sc.getSegment(8)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(9)->image, imread(DATA_DIR "15.bmp", -1)));
	imwrite(RESULTS_DIR "segment_14.bmp", sc.getSegment(9)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(10)->image, imread(DATA_DIR "16.bmp", -1)));
	imwrite(RESULTS_DIR "segment_15.bmp", sc.getSegment(10)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(11)->image, imread(DATA_DIR "17.bmp", -1)));
	imwrite(RESULTS_DIR "segment_16.bmp", sc.getSegment(11)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(12)->image, imread(DATA_DIR "18.bmp", -1)));
	imwrite(RESULTS_DIR "segment_17.bmp", sc.getSegment(12)->image);
	BOOST_CHECK(ImageComparator::isEqual<u_int8_t>(sc.getSegment(13)->image, imread(DATA_DIR "19.bmp", -1)));
	imwrite(RESULTS_DIR "segment_18.bmp", sc.getSegment(13)->image);

}

