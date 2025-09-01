cmake_minimum_required(VERSION 3.8)
project(more_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(more_interfaces REQUIRED)

add_executable(publish_address_book src/publish_address_book.cpp)
target_link_libraries(publish_address_book rclcpp::rclcpp)

add_executable(subscribe_address src/address_book_sub.cpp)
target_link_libraries(subscribe_address rclcpp::rclcpp)

install(TARGETS
	publish_address_book
	subscribe_address
	DESTINATION lib/${PROJECT_NAME})

set(msg_files
	"msg/AddressBook.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
	${msg_files}
)

rosidl_get_typesupport_target(cpp_typesupport_target
	${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(publish_address_book "${cpp_typesupport_target}")
target_link_libraries(subscribe_address "${cpp_typesupport_target}")

ament_export_dependencies(rosidl_default_runtime)

ament_package()
