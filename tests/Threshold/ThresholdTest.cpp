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

BOOST_AUTO_TEST_CASE( GraySquareOnGrayBackground )
{
	Mat image = imread(DATA_DIR "5.bmp", -1);
	Mat mask = Mat::ones(image.size(), CV_8U);

	BOOST_CHECK(image.size() == Size(50, 50));
	BOOST_CHECK(image.type() == CV_8U);

	Mat result = Mat::zeros(image.size(), CV_8U);
	Mat expectedResult = imread(DATA_DIR "5_expected.bmp", -1);

	BOOST_CHECK(result.size() == expectedResult.size());
	BOOST_CHECK(result.type() == expectedResult.type());

	Threshold t;

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 0, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "7.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_0.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 84, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "7.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_84.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 85, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "7.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_85.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 86, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_86.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 128, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_128.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 169, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_169.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 170, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_170.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 171, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "6.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_171.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 255, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "6.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_255.bmp", result);
}

BOOST_AUTO_TEST_CASE( GraySquareOnGrayBackgroundWithMask )
{
	Mat image = imread(DATA_DIR "5.bmp", -1);
	Mat mask = imread(DATA_DIR "3.bmp", -1);

	BOOST_CHECK(image.size() == Size(50, 50));
	BOOST_CHECK(image.type() == CV_8U);

	BOOST_CHECK(mask.size() == Size(50, 50));
	BOOST_CHECK(mask.type() == CV_8U);

	Mat result = Mat::zeros(image.size(), CV_8U);
	Mat expectedResult = imread(DATA_DIR "5_expected_mask_3.bmp", -1);

	BOOST_CHECK(result.size() == expectedResult.size());
	BOOST_CHECK(result.type() == expectedResult.type());

	Threshold t;

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 0, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "5_expected_mask_3_above.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_mask_0.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 84, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "5_expected_mask_3_above.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_mask_84.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 85, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "5_expected_mask_3_above.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_mask_85.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 86, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_mask_86.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 128, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_mask_128.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 169, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_mask_169.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 170, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, expectedResult) );
	imwrite(RESULTS_DIR "5_thresholded_mask_170.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 171, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "5_expected_mask_3_below.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_mask_171.bmp", result);

	result = Mat::zeros(image.size(), CV_8U);
	t.thresholdImage(image, mask, 255, 40, 230, result);
	BOOST_CHECK( ImageComparator::isEqual<u_char>(result, imread(DATA_DIR "5_expected_mask_3_below.bmp", -1)) );
	imwrite(RESULTS_DIR "5_thresholded_mask_255.bmp", result);
}

