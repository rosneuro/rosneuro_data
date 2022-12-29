cmake_minimum_required(VERSION 2.8.3)
project(rosneuro_data)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(catkin REQUIRED COMPONENTS 
			 roscpp
			 std_msgs
			 rosneuro_msgs
)

find_package(PkgConfig)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

catkin_package(
  INCLUDE_DIRS 
	include
  LIBRARIES 
	${PROJECT_NAME}
  CATKIN_DEPENDS
  	roscpp
	std_msgs
	rosneuro_msgs

  DEPENDS
)

###########
## Build ##
###########

include_directories(${catkin_INCLUDE_DIRS} 
					include
)

add_library(${PROJECT_NAME}
			src/NeuroData.cpp
			src/NeuroDataTools.cpp
)

target_link_libraries(${PROJECT_NAME} 
					  ${catkin_LIBRARIES} 
)

add_dependencies(${PROJECT_NAME} 
				 ${catkin_EXPORTED_TARGETS}
)

#################
## Executables ##
#################

add_executable(test_neurodata src/test_neurodata.cpp)
target_link_libraries(test_neurodata rosneuro_data)

add_executable(test_neurodata_operations src/test_neurodata_operations.cpp)
target_link_libraries(test_neurodata_operations rosneuro_data)

add_executable(test_neurodata_tools src/test_neurodata_tools.cpp)
target_link_libraries(test_neurodata_tools rosneuro_data)


#################
##   Install   ##
#################
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)


