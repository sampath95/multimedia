#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


using namespace cv;
using namespace std;

/// Global variables
Mat src,img, img_dst, erosion_dst, dilation_dst;

double alpha; 
int beta;  


/** Function Headers */
void Erosion();
void Dilation();
void img_resize();
void brightdark();
int menu();


///MAIN
int main(int, char** argv)
{	
	/// Load an image
	src = imread( argv[1], IMREAD_COLOR );
	int choice;
	if( src.empty() )
		{ return -1; }
		choice = menu();
	if(choice==1){
	int a;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : Erosion "<< endl;
	cout << "2 : Dilation"<< endl;
	cin >> a;
	 	if (a==1)
			{
			    Erosion();
			    waitKey(0);
			    return 0;
			}
		if (a == 2)
			{
			    Dilation();
			    waitKey(0);
			    return 0;
			}
	}//endchoice1
	if(choice==2){	
			img_resize();
			waitKey(0);
			return 0;
	}//endchoice2
	if(choice==3){	 
			brightdark();
			waitKey(0);
			return 0;
	}//endchoice3
}//end menu
	
	
//you can call menu anytime 
int menu()
{
	int z;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : Erosion / Dilation"<< endl;
	cout << "2 : resizing"<< endl;
	cout << "3 : lighten / darken"<< endl;
	cout << "4 : panorama / stitching"<< endl;
	cin >> z;
	return z;
}


//![erosion]
void Erosion()
{
  int erosion_elem;
  cout<<"Erosion element : 0 Rect, 1 Cross, 2 Ellipse"<<endl;
  cin>>erosion_elem;

  int erosion_size;
  cout<<"Erosion size : ?"<<endl;
  cin>>erosion_size;

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
  imshow( "Erosion", erosion_dst );
}


/** @function Dilation */
void Dilation()
{
  int dilation_elem;
  cout<<"Erosion element : 0 Rect, 1 Cross, 2 Ellipse"<<endl;
  cin>>dilation_elem;

  int dilation_size;
  cout<<"Erosion size : ?"<<endl;
  cin>>dilation_size;

  int dilation_type = 0;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  /// Apply the dilation operation
  dilate( src, dilation_dst, element );
  imshow( "Dilation", dilation_dst );
}


//function resize
void img_resize(){

    double w, h;
    Size s = src.size();
    cout<<"width : "<<endl;
    cin>>w;
    cout<<"height : "<<endl;
    cin>>h;
    if(w==0)
    {
      h=h/s.height;
      w=h;
    }
    else if(h==0)
    {
      w=w/s.height;
      h=w;
    }
    else if(h==0 && w==0)
    {
      w=w;
      h=h;
    }
    else
    {
      w=w/s.width;
      h=h/s.width;
    }
    resize(src, img_dst, Size(), w, h);
    imshow("Resize",img_dst);
}


//function darkandlight
void brightdark()
{
	Mat new_src = Mat::zeros( src.size(), src.type() );

 /// Initialize values
 
 std::cout<<"* Enter the alpha value [0.0-3.0]: ";std::cin>>alpha;
 std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;

 /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
 for( int y = 0; y < src.rows; y++ )
    { for( int x = 0; x < src.cols; x++ )
         { for( int c = 0; c < 3; c++ )
              {
      new_src.at<Vec3b>(y,x)[c] =
         saturate_cast<uchar>( alpha*( src.at<Vec3b>(y,x)[c] ) + beta );
             }
    }
    }

 /// Create Windows
 namedWindow("Original Image", 1);
 namedWindow("New Image", 1);

 /// Show stuff
 imshow("Original Image", src);
 imshow("New Image", new_src);
	
}

