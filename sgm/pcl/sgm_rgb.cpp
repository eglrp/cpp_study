#include <pcl/visualization/cloud_viewer.h>
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;
using namespace pcl;

int user_data;
//相机内参，根据输入改动
const double u0 = 1329.49 / 8;                                                   //由于后面resize成原图的1/4所以有些参数要缩小相同倍数
const double v0 = 954.485 / 8;
const double fx = 6872.874 / 8;
const double fy = 6872.874 / 8;
const double Tx = 174.724;
const double doffs = 293.97 / 8;


void viewerOneOff(visualization::PCLVisualizer& viewer)                          //该函数功能是设置viewer信息 
{
	viewer.setBackgroundColor(0.0, 0.0, 0.0);                                    //函数具体实现对可视化对象背景颜色设置
}

int main()
{

	/***************************************************************************************************************************
	*pointcloud为PCL中的一种数据结构，PointCloud是一个C++类，包含point在内的一些数据域；
	存储了数据类型为PointT的一个动态数组，例如，对于一个包含了XYZ数据的点云，points是包含了元素为pcl::PointXYZ一个vector；
	如：	pcl::PointCloud<pcl::PointXYZ> cloud;
	      std::vector<pcl::PointXYZ> data = cloud.points;  
	****************************************************************************************************************************/
	
	PointCloud<PointXYZRGB> cloud_a;                                              //实例化模板类PointCloud，每一个点的类型都被设置成pcl::PointXYZRGB
	PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);              //创建一个PointCloud<PointXYZRGB> boost共享指针并进行实例化
	
    Mat color1 = imread("city.tif");//读入图像(-1原图，1彩色图，0灰度图)
	  Mat depth = imread("result.jpg");//深度图 
									   /*****************
    Mat color1 = imread("test11.png");
	Mat depth = imread("test12.png"); ****************/

	//Resize
	//color1.resize();

	Mat color;                                                                    //改变大小后的图像
	resize(color1, color, Size(color1.cols / 8, color1.rows / 8), 0, 0, CV_INTER_LINEAR);   


	//resize函数改变图像的大小
	/**********************************************************************************************************************************
	如果你事先已经指定好dst图像的大小,可通过这种方式调用函数 resize(src, dst, dst.size(), (fx=)0, (fy=)0, interpolation)
	src：输入，原图像，即待改变大小的图像；	dst：输出，改变大小之后的图像，这个图像和原图像具有相同的内容，只是大小和原图像不一样而已；
	fx：width方向的缩放比例；   fy：height方向的缩放比例;  
	interpolation：这个是指定插值的方式，图像缩放之后，肯定像素要进行重新计算的，就靠这个参数来指定重新计算像素的方式
	INTER_LINEAR - 双线性插值，如果最后一个参数你不指定，默认使用这种方法          
	***********************************************************************************************************************************/


	//imshow("h",color);
	//waitKey(0);

	int rowNumber = color.rows;
	int colNumber = color.cols;

	cloud_a.height = rowNumber;
	cloud_a.width = colNumber;
	cloud_a.points.resize(cloud_a.width * cloud_a.height);	
	for (unsigned int u = 0; u < rowNumber; ++u)
	{
		for (unsigned int v = 0; v < colNumber; ++v)
		{
			/*unsigned int num = rowNumber*colNumber-(u*colNumber + v)-1;*/
			unsigned int num = u * colNumber + v;
			double Xw = 0, Yw = 0, Zw = 0;

			// 计算这个点的空间坐标
			Zw = fx * Tx / (((double)depth.at<Vec3b>(u, v)[0]) + doffs);
			Xw = (v + 1 - u0) * Zw / fx;
			Yw = (u + 1 - v0) * Zw / fy;
			
			cloud_a.points[num].b = color.at<Vec3b>(u, v)[0];
			cloud_a.points[num].g = color.at<Vec3b>(u, v)[1];
			cloud_a.points[num].r = color.at<Vec3b>(u, v)[2];
			// 把p加入到点云中
			cloud_a.points[num].x = Xw;
			cloud_a.points[num].y = Yw;
			cloud_a.points[num].z = Zw;
		}
	}
   
	*cloud = cloud_a;
	//可视化程序中所对应的地物
	visualization::CloudViewer viewer("Cloud Viewer");                           //... 为cloud添加对应的场景,创建viewer对象 

	viewer.showCloud(cloud);

	viewer.runOnVisualizationThreadOnce(viewerOneOff);

	while (!viewer.wasStopped())
	{
		user_data = 9;
	}

	return 0;

	/*********************************************************************************************************
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size = " << cloud->points.size() << endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile("pointcloud.pcd", *cloud);

	// 清除数据并退出
	cloud->points.clear();
	cout << "Point cloud saved." << endl;
	return 0;

	*************************************************************************************************************/








}
