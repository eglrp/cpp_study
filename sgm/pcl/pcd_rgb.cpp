#include <pcl/visualization/cloud_viewer.h>
#include <iostream>  
#include <pcl/io/io.h>  
#include <pcl/io/pcd_io.h>  
#include <opencv2/opencv.hpp>  

using namespace cv;
using namespace std;
using namespace pcl;

int user_data;
//����ڲΣ���������Ķ�
const double u0 = 1329.49 / 8;                                                   //���ں���resize��ԭͼ��1/4������Щ����Ҫ��С��ͬ����
const double v0 = 954.485 / 8;
const double fx = 6872.874 / 8;
const double fy = 6872.874 / 8;
const double Tx = 174.724;
const double doffs = 293.97 / 8;


void viewerOneOff(visualization::PCLVisualizer& viewer)                          //�ú�������������viewer��Ϣ 
{
	viewer.setBackgroundColor(0.0, 0.0, 0.0);                                    //��������ʵ�ֶԿ��ӻ����󱳾���ɫ����
}

int main()
{

	/***************************************************************************************************************************
	*pointcloudΪPCL�е�һ�����ݽṹ��PointCloud��һ��C++�࣬����point���ڵ�һЩ������
	�洢����������ΪPointT��һ����̬���飬���磬����һ��������XYZ���ݵĵ��ƣ�points�ǰ�����Ԫ��Ϊpcl::PointXYZһ��vector��
	�磺	pcl::PointCloud<pcl::PointXYZ> cloud;
	      std::vector<pcl::PointXYZ> data = cloud.points;  
	****************************************************************************************************************************/
	
	PointCloud<PointXYZRGB> cloud_a;                                              //ʵ����ģ����PointCloud��ÿһ��������Ͷ������ó�pcl::PointXYZRGB
	PointCloud<PointXYZRGB>::Ptr cloud(new PointCloud<PointXYZRGB>);              //����һ��PointCloud<PointXYZRGB> boost����ָ�벢����ʵ����
	
    Mat color1 = imread("city.tif");//����ͼ��(-1ԭͼ��1��ɫͼ��0�Ҷ�ͼ)
	  Mat depth = imread("result.jpg");//���ͼ 
									   /*****************
    Mat color1 = imread("test11.png");
	Mat depth = imread("test12.png"); ****************/

	//Resize
	//color1.resize();

	Mat color;                                                                    //�ı��С���ͼ��
	resize(color1, color, Size(color1.cols / 8, color1.rows / 8), 0, 0, CV_INTER_LINEAR);   


	//resize�����ı�ͼ��Ĵ�С
	/**********************************************************************************************************************************
	����������Ѿ�ָ����dstͼ��Ĵ�С,��ͨ�����ַ�ʽ���ú��� resize(src, dst, dst.size(), (fx=)0, (fy=)0, interpolation)
	src�����룬ԭͼ�񣬼����ı��С��ͼ��	dst��������ı��С֮���ͼ�����ͼ���ԭͼ�������ͬ�����ݣ�ֻ�Ǵ�С��ԭͼ��һ�����ѣ�
	fx��width��������ű�����   fy��height��������ű���;  
	interpolation�������ָ����ֵ�ķ�ʽ��ͼ������֮�󣬿϶�����Ҫ�������¼���ģ��Ϳ����������ָ�����¼������صķ�ʽ
	INTER_LINEAR - ˫���Բ�ֵ��������һ�������㲻ָ����Ĭ��ʹ�����ַ���          
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

			// ���������Ŀռ�����
			Zw = fx * Tx / (((double)depth.at<Vec3b>(u, v)[0]) + doffs);
			Xw = (v + 1 - u0) * Zw / fx;
			Yw = (u + 1 - v0) * Zw / fy;
			
			cloud_a.points[num].b = color.at<Vec3b>(u, v)[0];
			cloud_a.points[num].g = color.at<Vec3b>(u, v)[1];
			cloud_a.points[num].r = color.at<Vec3b>(u, v)[2];
			// ��p���뵽������
			cloud_a.points[num].x = Xw;
			cloud_a.points[num].y = Yw;
			cloud_a.points[num].z = Zw;
		}
	}
   
	*cloud = cloud_a;
	//���ӻ�����������Ӧ�ĵ���
	visualization::CloudViewer viewer("Cloud Viewer");                           //... Ϊcloud��Ӷ�Ӧ�ĳ���,����viewer���� 

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

	// ������ݲ��˳�
	cloud->points.clear();
	cout << "Point cloud saved." << endl;
	return 0;

	*************************************************************************************************************/








}
