#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;


#include <iostream>

/// Global variables
Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;
/** Function Headers */
void Erosion( int, void* );

///MAIN
int main(int, char** argv)
{
	/// Load an image
	src = imread( argv[1], IMREAD_COLOR );

	if( src.empty() )
		{ return -1; }

	int actionchoice;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : dilation / erosion"<< endl;
	cout << "2 : resizing"<< endl;
	cout << "3 : lighten / darken"<< endl;
	cout << "4 : panorama / stitching"<< endl;
	cin >> actionchoice;

	if (actionchoice == 1)
		{

		/// Create windows
		  namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
		/// Create Erosion Trackbar
		  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
			  &erosion_elem, max_elem,
			  Erosion );

		  createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
			  &erosion_size, max_kernel_size,
			  Erosion );
		/// Default start
		  Erosion( 0, 0 );
		  waitKey(0);
		  return 0;
		}

	if (actionchoice == 2)
		{cout << "two" << endl;}
	if (actionchoice == 3)
		{cout << "three" << endl;}
	if (actionchoice == 4)
		{cout << "four" << endl;}
}

///in main


///!in main

//![erosion]
/**
 * @function Erosion
 */
void Erosion( int, void* )
{
  int erosion_type = 0;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  //![kernel]
  Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
  //![kernel]

  /// Apply the erosion operation
  erode( src, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
}
//![erosion]


