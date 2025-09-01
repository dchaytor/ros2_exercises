#include <chrono>
#include <cinttypes>
#include <memory>

#include "tutorial_interfaces/srv/add_three_ints.hpp"
#include "rclcpp/rclcpp.hpp"

using AddThreeInts = tutorial_interfaces::srv::AddThreeInts;

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("add_three_ints_client");
	auto client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");

	auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
	request->a = 39;
	request->b = 1;
	request->c = 2;

	while (!client->wait_for_service(std::chrono::seconds(1)))	{
		if (!rclcpp::ok())	{
			RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
			return 1;
		}
		RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
	}
	
	auto result = client->async_send_request(request);
	if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS)
	{
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
	} else	{
		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_three_ints");
	}

	rclcpp::shutdown();
	return 0;
}
