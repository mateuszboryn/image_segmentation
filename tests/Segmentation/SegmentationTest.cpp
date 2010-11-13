#include <unistd.h>
#include <iostream>
#include "ImageComparator.h"

#include "Segmentation.h"
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
	Segmentation s(RESULTS_DIR);


}

