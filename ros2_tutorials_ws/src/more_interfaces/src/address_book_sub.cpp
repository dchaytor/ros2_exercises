#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

const char* TOPIC_NAME = "address_book";
const short TOPIC_DEPTH = 10;

using namespace more_interfaces::msg;

class AddressSubscriber : public rclcpp::Node
{
	public:
	AddressSubscriber() : Node("address_subscriber")
	{
		auto address_callback = [this](const AddressBook &address) -> void {
			const char* phoneType = {(address.phone_type == address.PHONE_TYPE_HOME) ? "(home)" : ((address.phone_type == address.PHONE_TYPE_WORK) ? "(work)" : "(mobile)")};

				RCLCPP_INFO(this->get_logger(), "Name: %s %s | #: %s %s", address.first_name.c_str(), address.last_name.c_str(), address.phone_number.c_str(), phoneType);
			};
		subscription_ = this->create_subscription<AddressBook>(TOPIC_NAME, TOPIC_DEPTH, address_callback);
	}
	private:
		rclcpp::Subscription<AddressBook>::SharedPtr subscription_;
};

int main(int argc, char **argv)	
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<AddressSubscriber>());
	rclcpp::shutdown();
	return 0;
}
