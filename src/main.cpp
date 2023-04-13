#include <iostream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>


#include "frame.h"


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <npz filename>" << std::endl;
    return 1;
  }

  std::string npz_filename = argv[1];

  // Initialize point cloud object
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>());
  cloud->points.resize(max_points);

  // Initialize the visualizer
  pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
  viewer->setBackgroundColor(0, 0, 0);
  viewer->addCoordinateSystem(1.0);
  viewer->initCameraParameters();

  // Start the rendering loop
  while (!viewer->wasStopped()) {
    // Create a Frame object by loading an npz file
    Frame frame(npz_filename);

    // Visualize the frame using the visualize member function
    frame.visualize(viewer, cloud);


    // Add delay
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // viewer->spinOnce(100);
    viewer->spin();

  }

  return 0;
}