#include <memory>

#include "tutorial_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using AddThreeInts = tutorial_interfaces::srv::AddThreeInts;
rclcpp::Node::SharedPtr g_node = nullptr;

void handle_service(
	const std::shared_ptr<AddThreeInts::Request> request,
	const std::shared_ptr<AddThreeInts::Response> response)
{
	response->sum = request->a + request->b + request->c;
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n" \
			"a: %ld\tb: %ld\t c:%ld\t", request->a, request->b, request->c);
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response [%ld]",
			(long int)response->sum);
}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	auto node = rclcpp::Node::make_shared("add_three_ints_server"); 
	auto service = node->create_service<AddThreeInts>("add_three_ints", &handle_service);


	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints :)");
		
	rclcpp::spin(node);
	rclcpp::shutdown();
	node = nullptr;
	return 0;
}
