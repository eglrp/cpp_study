#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<vector>
#include<iostream>
#include<string>
#include<sstream>

using namespace cv;
using namespace std;


void cut_image_left(int n)
{
	string res;
	stringstream ss;
	ss << n;
	ss >> res;
	string m = res + ".tif";
	Mat left = imread("03751_epl.tif");
	int img_row = left.rows;
	int img_col = left.cols;
	Mat ROI_L(left, Rect(0, (n - 1) * 100, img_col, 100));
	imwrite("F:\\workplace\\Cut_image\\Cut_image\\cut_left\\" + m, ROI_L);
	cout << res + "left succeed" << endl;
}

void cut_image_right(int n)
{
	string res;
	stringstream ss;
	ss << n;
	ss >> res;
	string m = res + ".tif";
	Mat right = imread("03753_epl.tif");
	int img_row = right.rows;
	int img_col = right.cols;
	Mat ROI_R(right, Rect(0, (n - 1) * 100, img_col, 100));
	imwrite("F:\\workplace\\Cut_image\\Cut_image\\cut_right\\" + m, ROI_R);
	cout << res + "right succeed" << endl;
}

void cut()
{
	for (int n = 1; n < 4; n++)
	{
		cut_image_left(n);
	}
	for (int m = 1; m < 4; m++)
	{
		cut_image_right(m);
	}
}