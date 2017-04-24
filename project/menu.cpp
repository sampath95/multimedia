#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;


#include <iostream>
int main()
{
	int actionchoice;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : dilation / erosion"<< endl;
	cout << "2 : resizing"<< endl;
	cout << "3 : lighten / darken"<< endl;
	cout << "4 : panorama / stitching"<< endl;
	cin >> actionchoice;

	if (actionchoice == 1)
		{cout << "one" << endl;}
	if (actionchoice == 2)
		{cout << "two" << endl;}
	if (actionchoice == 3)
		{cout << "three" << endl;}
	if (actionchoice == 4)
		{cout << "four" << endl;}
}




