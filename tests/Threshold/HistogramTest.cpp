#include <unistd.h>
#include <iostream>

#include "Threshold.h"
#include "ImageComparator.h"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace cv;

#define DATA_DIR "../../../tests/data/Threshold/"
#define RESULTS_DIR "../../../tests/results/Threshold/"

BOOST_AUTO_TEST_CASE( PWD )
{
	char *pwd = get_current_dir_name();
	cout << "Current working directory: \"" << pwd << "\"\n";
	// workspace/image_segmentation/build/tests/Threshold
	free(pwd);
}

BOOST_AUTO_TEST_CASE( Params )
{
	Mat image;
	Mat mask;
	int histogram[Threshold::histogramSize];
	Threshold t;
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);

	image = Mat::zeros(Size(10, 10), CV_8U);
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);

	mask = Mat::zeros(Size(10, 10), CV_8U);
	t.histogram(image, mask, histogram);

	image = Mat::zeros(Size(10, 9), CV_8U);
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);

	image = Mat::zeros(Size(9, 10), CV_8U);
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);

	image = Mat::zeros(Size(10, 10), CV_8S);
	mask = Mat::zeros(Size(10, 10), CV_8U);
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);

	image = Mat::zeros(Size(10, 10), CV_8U);
	mask = Mat::zeros(Size(10, 10), CV_8S);
	BOOST_CHECK_THROW(t.histogram(image, mask, histogram), logic_error);
}

BOOST_AUTO_TEST_CASE( Images )
{
	Mat image = imread(DATA_DIR "1.bmp", -1);
	Mat mask = Mat::ones(Size(50, 50), CV_8U);

	int histogram[Threshold::histogramSize];
	Threshold t;

	t.histogram(image, mask, histogram);
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		if (i == 255) {
			BOOST_CHECK(histogram[i] == 50 * 50);
		} else {
			BOOST_CHECK(histogram[i] == 0);
		}
	}

	image = imread(DATA_DIR "2.bmp", -1);
	t.histogram(image, mask, histogram);
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		if (i == 0) {
			BOOST_CHECK(histogram[i] == 50 * 50);
		} else {
			BOOST_CHECK(histogram[i] == 0);
		}
	}

	image = imread(DATA_DIR "5.bmp", -1);
	t.histogram(image, mask, histogram);
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		if (i == 85) {
			BOOST_CHECK(histogram[i] == 50 * 50 - 25 * 15);
		} else if (i == 170) {
			BOOST_CHECK(histogram[i] == 25 * 15);
		} else {
			BOOST_CHECK(histogram[i] == 0);
		}
	}

	mask = imread(DATA_DIR "3.bmp", -1);
	t.histogram(image, mask, histogram);
	for (int i = 0; i < Threshold::histogramSize; ++i) {
		if (i == 85) {
			BOOST_CHECK(histogram[i] == 25 * 50 - 16 * 15);
		} else if (i == 170) {
			BOOST_CHECK(histogram[i] == 16 * 15);
		} else {
			BOOST_CHECK(histogram[i] == 0);
		}
	}

}
