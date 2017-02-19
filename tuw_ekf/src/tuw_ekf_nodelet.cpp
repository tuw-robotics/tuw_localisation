// this should really be in the implementation (.cpp file)
#include <pluginlib/class_list_macros.h>
#include <tuw_ekf_nodelet.h>
#include <tf/transform_datatypes.h>

// watch the capitalization carefully
PLUGINLIB_EXPORT_CLASS ( tuw_ekf::EKFNodelet, nodelet::Nodelet )

namespace tuw_ekf {
void EKFNodelet::onInit() {
    NODELET_DEBUG ( "Initializing nodelet..." );
    ros::NodeHandle &n         = getNodeHandle();
    ros::NodeHandle &private_nh = getPrivateNodeHandle();
    /// subscribes to  odometry values
    tf_broadcaster = std::make_shared<tf::TransformBroadcaster>();
    sub_odometry_ = n.subscribe ( "odom", 1, &EKFNodelet::callbackOdometry, this );
}


/**
 * copies incoming odemetry messages to the base class
 * @param odom
 **/
void EKFNodelet::callbackOdometry ( const nav_msgs::OdometryPtr &odom ) {
    NODELET_DEBUG ( "callbackOdometry..." );

    tf::Transform transform;
    transform.setOrigin ( tf::Vector3 ( 1, 0, 0 ) );
    tf::Quaternion q ( 0, 0, 0, 1 );
    transform.setRotation ( q );
    tf_broadcaster->sendTransform ( tf::StampedTransform ( transform, ros::Time::now(), "map", "odom" ) );
}


}
