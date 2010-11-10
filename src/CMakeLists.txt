PROJECT(segmentation_test)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Boost REQUIRED program_options)
FIND_PACKAGE(OpenCV REQUIRED)

SET(segmentation_test_LIBRARIES 
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${OpenCV_LIBS}
)

ADD_DEFINITIONS(-Wall -pedantic -Wno-sign-compare -p -O3 -Werror=return-type)

SET(segmentation_test_SOURCES 
	main.cpp
	Segmentation.cpp
)

ADD_EXECUTABLE(st ${segmentation_test_SOURCES})

SET_TARGET_PROPERTIES(st PROPERTIES LINK_FLAGS -p)

TARGET_LINK_LIBRARIES(st ${segmentation_test_LIBRARIES})
