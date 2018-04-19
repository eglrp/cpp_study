#include <iostream> //��׼���������
#include <pcl/io/pcd_io.h> //PCL��PCD��ʽ�ļ����������ͷ�ļ�
#include <pcl/point_types.h> //PCL�Ը��ָ�ʽ�ĵ��֧��ͷ�ļ�
#include <pcl/visualization/cloud_viewer.h>//���Ʋ鿴����ͷ�ļ�
int main(int argc, char** argv)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // �������ƣ�ָ�룩

	if (pcl::io::loadPCDFile<pcl::PointXYZ>("pointcloud.pcd", *cloud) == -1) //* ����PCD��ʽ���ļ�������ļ������ڣ�����-1
	{
		PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //�ļ�������ʱ�����ش�����ֹ����
		return (-1);
	}
	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");//ֱ�Ӵ���һ����ʾ����
	viewer.showCloud(cloud);//�����������ʾ����
	while (!viewer.wasStopped())
	{
	}
	return (0);
}