SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
FILE(GLOB FILES *.cpp)
ADD_EXECUTABLE(image_segmentation ${FILES})
TARGET_LINK_LIBRARIES(image_segmentation ${image_segmentation_LIBRARIES})