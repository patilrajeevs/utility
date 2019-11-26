cmake_minimum_required(VERSION 3.5)

project (opencv_helper)

add_library(opencv_helper src/opencv_helper.cpp)
add_library(geometry_helper src/geometry_helper.cpp)

find_package( OpenCV REQUIRED )
target_link_libraries( opencv_helper ${OpenCV_LIBS} )
target_link_libraries( geometry_helper ${OpenCV_LIBS} )

set_target_properties(opencv_helper geometry_helper 
        PROPERTIES CXX_STANDARD 11
        )

install(TARGETS opencv_helper DESTINATION lib)
install(FILES src/opencv_helper.h DESTINATION include)

install(TARGETS geometry_helper DESTINATION lib)
install(FILES src/geometry_helper.h DESTINATION include)
