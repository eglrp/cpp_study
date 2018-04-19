//together
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp> 
#include<stdio.h>    
#include<vector>
#include<iostream>
#include<stitching.hpp>
#include<string>
#include<sstream>

using namespace std;
using namespace cv;

int main()
{
	Mat img0 = imread("F:\\workplace\\Cut_image\\Cut_image\\result\\1.tif");
	Mat result;
	result.create(115 * img0.rows, img0.cols, img0.type());
	for (int n = 1; n < 116; n++) {
		string res;
		stringstream ss;
		ss << n;
		ss >> res;
		//string roi = "ROI" + res;
		//string name = "img" + res;
		string m = "F:\\workplace\\Cut_image\\Cut_image\\result\\"+res + ".tif";
		Mat img = imread(m);
		Mat roi(result, Rect(0, (n-1)*img.rows, img.cols, img.rows));
		img.copyTo(roi);
	}
	namedWindow("操作后的图像");
	imshow("操作后的图像", result);
	imwrite("result.jpg", result);
	//imwrite("cut_03753.png",dst);
	waitKey(0);
	system("pause");
	return 0;
}


	/*Mat img1 = imread("F:\\workplace\\Cut_image\\Cut_image\\result\\1.tif");
	Mat img2 = imread("F:\\workplace\\Cut_image\\Cut_image\\result\\2.tif");
	Mat img3 = imread("F:\\workplace\\Cut_image\\Cut_image\\result\\3.tif");
	Mat img4 = imread("F:\\workplace\\Cut_image\\Cut_image\\result\\4.tif");
	//Mat imageROI(src, Rect(0, 0, src.cols, 100));
	Mat res;
	res.create(4*img1.rows,img1.cols,img1.type());
	Mat ROI1(res, Rect(0, 0, img1.cols, img1.rows));
	img1.copyTo(ROI1);
	Mat ROI2(res, Rect(0, img1.rows, img1.cols, img1.rows));
	img2.copyTo(ROI2);
	Mat ROI3(res, Rect(0, 2*img1.rows, img1.cols, img1.rows));
	img3.copyTo(ROI3);
	Mat ROI4(res, Rect(0, 3*img1.rows, img1.cols, img1.rows));
	img4.copyTo(ROI4);*/
	
	/*namedWindow("操作后的图像");
	imshow("操作后的图像", roi);
	imwrite("right_result.jpg",result);
	//imwrite("cut_03753.png",dst);
	waitKey(0);
	system("pause");
	return 0;*/





