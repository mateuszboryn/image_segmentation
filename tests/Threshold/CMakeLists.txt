ADD_EXECUTABLE(ThresholdTest ThresholdTest.cpp)

target_link_libraries(ThresholdTest ${image_segmentation_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(ThresholdTest ThresholdTest)