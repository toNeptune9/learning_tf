#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;



void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf::TransformBroadcaster br; // to send the tf over the wire
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  //create a Transform object, and copy the information from the 2D turtle pose into the 3D transform.
  transform.setRotation(q); //set rotation
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name)); 
  // first arg - pass the tf, second timestamp, third - pass the name of the parent frame (world). fourth - pass the child link name
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");
  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback); //listen to the pose

  ros::spin();
  return 0;
};