#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>
using namespace std::chrono_literals;

void mycallback(rclcpp::Node::SharedPtr node,rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub)
{
static int count;
auto message = std_msgs::msg::String();
message.data = "Hello world! " + std::to_string(count++);
RCLCPP_INFO(node->get_logger(), "Publish: %s", message.data.c_str());
pub->publish(message);
}
int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
auto node = std::make_shared<rclcpp::Node>("node_psub1_1");
auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
auto pub = node->create_publisher<std_msgs::msg::String>("topic_psub1_1", qos_profile );

std::function<void()> fn = std::bind(mycallback, node, pub);
auto timer = node->create_wall_timer(100ms, fn);
rclcpp::spin(node);
rclcpp::shutdown();
return 0;
}