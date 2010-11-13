PROJECT(image_segmentation)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Boost REQUIRED program_options unit_test_framework)
FIND_PACKAGE(OpenCV REQUIRED)

SET(image_segmentation_LIBRARIES 
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${OpenCV_LIBS}
)

ADD_DEFINITIONS(-Wall)
ADD_DEFINITIONS(-pedantic)
ADD_DEFINITIONS(-Wno-sign-compare)
ADD_DEFINITIONS(-p)
ADD_DEFINITIONS(-O3)
ADD_DEFINITIONS(-Werror=return-type)

enable_testing()


MACRO(ADD_TEST_CASE TEST_NAME)
    ADD_EXECUTABLE(${TEST_NAME} 
        ${TEST_NAME}.cpp 
        ${ARGN}
    )
    
    target_link_libraries(${TEST_NAME}
        ${image_segmentation_LIBRARIES}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

    add_test(${TEST_NAME} ${TEST_NAME})
ENDMACRO(ADD_TEST_CASE)

add_subdirectory(src)
add_subdirectory(tests)
