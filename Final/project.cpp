#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include "opencv2/stitching.hpp"



using namespace cv;
using namespace std;

/// Global variables
Mat src,img, img_dst, erosion_dst, dilation_dst;

double alpha; 
int beta;  
 //panorama
			bool try_use_gpu = false;
			Stitcher::Mode mode = Stitcher::PANORAMA;
			vector<Mat> imgs;
			string result_name = "result.jpg";
			//panorama
		  


/** Function Headers */
void Erosion();
void Dilation();
void img_resize();
void brightdark();
void loadimage();
int menu();
//panorama
void printUsage();
int parseCmdArgs(int argc, char** argv);

///MAIN
int main(int argc, char** argv)
{	
		
	int choice;
	choice = menu();
	if(choice==1){
	int a;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : Erosion "<< endl;
	cout << "2 : Dilation"<< endl;
	cin >> a;
	 	if (a==1)
			{  
				loadimage();	
			    Erosion();
			    waitKey(0);
cout << "thank you for your time; if you want to continue please select the below option" << endl;			    
			    
			   return 0;
			    
			}
		if (a == 2)
			{
				loadimage();
				if( src.empty() )
				{ return -1; }
			    Dilation();
			    waitKey(0);
			    return 0;
			}
	}//endchoice1
	if(choice==2){	
			
				loadimage();
				if( src.empty() )
				{ return -1; }
				img_resize();
				waitKey(0);
				return 0;
			
	}//endchoice2
	if(choice==3){	 
		
				loadimage();
				if( src.empty() )
				{ return -1; }
				brightdark();
				waitKey(0);
				return 0;
	}//endchoice3
	
	if(choice==4){
		  
				int number_files;
				cout<<"Enter the --NUMBER-- of image you want to sticth"<<endl;
				cin>>number_files;
		  		vector<string> files(number_files);
		    
		 
		  for (int x=0;x<number_files;x++)
		  { 
			  
			  cout<<"Enter the image names"<<endl;
			  cin>>files[x];
			  
			  Mat img = imread(files[x]);
			  imgs.push_back(img);
			  cout<<"-------------------------------------------------"<<endl;	  
  		  }
		
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK)
			{
				cout << "Can't stitch images, error code = " << int(status) << endl;
				return -1;
			}

				imwrite(result_name, pano);
				imshow(result_name,pano);
				waitKey(0);
				return 0;
    
			}
    

	}
	
	
//you can call menu anytime 
int menu()
{
	int z;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : Erosion / Dilation"<< endl;
	cout << "2 : resizing"<< endl;
	cout << "3 : lighten / darken"<< endl;
	cout << "4 : panorama"<< endl;
	cin >> z;
	return z;
}

//load image for erosion/dilatio/resizing/dark

void loadimage()
{
				string imagename;
				cout<<"Enter the Name of the image"<<endl;
				cin>>imagename;
				src = imread(imagename);
				
}

//![erosion]
void Erosion()
{
  int erosion_elem;
  erosion_elem=1;

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
  int dilation_elem=0;

  int dilation_size;
  cout<<"Dilation Size : ?"<<endl;
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
//panorama
void printUsage()
{
    cout <<
        "if you want to use panorama please enter ./cpp image1 image2";
}
int parseCmdArgs(int argc, char** argv)
{
    if (argc == 1)
    {
        printUsage();
        return -1;
    }
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "--help" || string(argv[i]) == "/?")
        {
            printUsage();
            return -1;
        }
        else if (string(argv[i]) == "--try_use_gpu")
        {
            if (string(argv[i + 1]) == "no")
                try_use_gpu = false;
            else if (string(argv[i + 1]) == "yes")
                try_use_gpu = true;
            else
            {
                cout << "Bad --try_use_gpu flag value\n";
                return -1;
            }
            i++;
        }
        else if (string(argv[i]) == "--output")
        {
            result_name = argv[i + 1];
            i++;
        }
        else if (string(argv[i]) == "--mode")
        {
            if (string(argv[i + 1]) == "panorama")
                mode = Stitcher::PANORAMA;
            else if (string(argv[i + 1]) == "scans")
                mode = Stitcher::SCANS;
            else
            {
                cout << "Bad --mode flag value\n";
                return -1;
            }
            i++;
        }
        else
        {
            Mat img = imread(argv[i]);
            if (img.empty())
            {
                cout << "Can't read image '" << argv[i] << "'\n";
                return -1;
            }
            imgs.push_back(img);
        }
    }
    return 0;
}

