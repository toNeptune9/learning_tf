#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

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
  ros::NodeHandle node;
  //ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback); //listen to the pose
  tf::TransformBroadcaster br;
  tf::Transform transform;
  ros::Rate rate(10.0);
  while(node.ok()){
    
    transform.setOrigin( tf::Vector3(0.0, 3.0, 0.0) );
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "circle"));
    rate.sleep();
// x, y, z
    transform.setOrigin( tf::Vector3(2.0*sin(ros::Time::now().toSec()), 2.0*cos(ros::Time::now().toSec()), 0.0) );
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
  
  }


  //ros::spin();
  return 0;
};