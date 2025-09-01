cmake_minimum_required(VERSION 3.8)
project(cpp_srvcli)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)

add_executable(server src/add_three_ints_server.cpp)
target_link_libraries(server PUBLIC rclcpp::rclcpp ${tutorial_interfaces_TARGETS})

add_executable(client src/add_three_ints_client.cpp)
target_link_libraries(client PUBLIC rclcpp::rclcpp ${tutorial_interfaces_TARGETS})

install(TARGETS
	server
	client
	DESTINATION lib/${PROJECT_NAME})

ament_package()
