#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include "opencv2/stitching.hpp"



using namespace cv;
using namespace std;

/// Global variables
Mat src,img, imageDst, eroDst, dilaDst;

double alpha; 
int beta;  
//panorama
bool try_use_gpu = false;
Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imgs;
string result_name = "result.jpg";
//end panorama
		  


/** Function Headers ***************************************************************/
//Ero and Dila
void Erosion();
void Dilatation();
//Resize
void newSize();
//Light Dark
void darkandlight();
//menu and load
void loadimage();
int menu();
//panorama
void printUsage();
int parseCmdArgs(int argc, char** argv);

///MAIN ****************************************************************************
int main(int argc, char** argv)
{	
		
	int choice; //choice diplayed for the user
	choice = menu();
	if(choice==1){
		int a; // two new choices for erosion or dilatation
		cout << "Please choose the action you want to do on the image :" << endl;
		cout << "1 : Erosion "<< endl;
		cout << "2 : Dilatation"<< endl;
		cin >> a;
	 	if (a==1)
			{  
				loadimage(); //load the source image
				if( src.empty() ) // in case of the source is empty to not have an error
				{ return -1; }
			    Erosion(); //call function
			    waitKey(0);
				cout << "thank you for your time; if you want to continue please select the below option" << endl;			    
			    return 0;
			    
			}
		if (a == 2)
			{
				loadimage();
				if( src.empty() )
				{ return -1; }
			    Dilatation();
			    waitKey(0);
			    return 0;
			}
	}//endchoice1 Ero/dila
	if(choice==2){	
			
				loadimage();
				if( src.empty() )
				{ return -1; }
				newSize();
				waitKey(0);
				return 0;
			
	}//endchoice2 Resize
	if(choice==3){	 
		
				loadimage();
				if( src.empty() )
				{ return -1; }
				darkandlight();
				waitKey(0);
				return 0;
	}//endchoice3 Darkenlight
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
	}//end choice 4 Panorama
}// END Main ********************************************************************************
	

/** Functions ******************************************************************************/
//we can call menu anytime // prints the menu of choice we have available to do on the src image, will then ask for an input in main()
int menu()
{
	int z;
	cout << "Please choose the action you want to do on the image :" << endl;
	cout << "1 : Erosion / Dilatation"<< endl;
	cout << "2 : resizing"<< endl;
	cout << "3 : lighten / darken"<< endl;
	cout << "4 : panorama"<< endl;
	cin >> z;
	return z;
}

//load image for erosion/dilatio/resizing/lightdark
void loadimage()
{
	string imagename;
	cout<<"Enter the Name of the image"<<endl;
	cin>>imagename;
	src = imread(imagename);
				
}
//Erode Dilate ******************************************************************************
//Erosion
void Erosion()
{
  int eroElem;
  eroElem=1;

  int eroSize; //we choose the size of the structuring element
  cout<<"Erosion size : ?"<<endl;
  cin>>eroSize;
  int eroType = 0; 
  //we choose the structuring element we want to use
  if( eroElem == 0 ){ eroType = MORPH_RECT; }
  else if( eroElem == 1 ){ eroType = MORPH_CROSS; }
  else if( eroElem == 2) { eroType = MORPH_ELLIPSE; }

  //create the structuring elements with zeros and ones
  Mat element = getStructuringElement( eroType,
        Size( 2*eroSize + 1, 2*eroSize+1 ),
        Point( eroSize, eroSize ) );

  ///apply the erosion operation tot the src image with the structuring element
  erode( src, eroDst, element );
  imshow( "Erosion", eroDst );
}


//Dilatation
void Dilatation()
{
  int dilaElem=0;

  int dilaSize; //we choose the size of the structuring element
  cout<<"Dilatation Size : ?"<<endl;
  cin>>dilaSize;
  int dilaType = 0;
  //we choose the structuring element we want to use
  if( dilaElem == 0 ){ dilaType = MORPH_RECT; }
  else if( dilaElem == 1 ){ dilaType = MORPH_CROSS; }
  else if( dilaElem == 2) { dilaType = MORPH_ELLIPSE; }

  //create the structuring elements with zeros and ones
  Mat element = getStructuringElement( dilaType,
                                       Size( 2*dilaSize + 1, 2*dilaSize+1 ),
                                       Point( dilaSize, dilaSize ) );

  ///apply the dilatation operation tot the src image with the structuring element
  dilate( src, dilaDst, element );
  imshow( "Dilatation", dilaDst );
}


//Function resize **************************************************************************
void newSize(){

    double w, h;
    Size s = src.size();
    cout<<"width : "<<endl;
    cin>>w; //choose the width of the output image
    cout<<"height : "<<endl;
    cin>>h; //choose the height of the output image
    //special case when w or h are equals to 0 to not get an error
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
    else //other usual case when we've enter a new width and height
    {
      w=w/s.width;
      h=h/s.width;
    }

    // apply the resize with the new w and h parameters
    resize(src, imageDst, Size(), w, h);
    imshow("Resize",imageDst);
}


//Function darkandlight ******************************************************************
void darkandlight()
{
	//we initialize the new image we'll have in output
	Mat new_src = Mat::zeros( src.size(), src.type() );

 	/// we initialize values of alpha and beta which determines light/dark
	std::cout<<"* Enter the alpha value [0.0-3.0]: ";std::cin>>alpha;
	std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;

	/// we do the operation new_image(i,j) = alpha*image(i,j) + beta
	// it will take each pixels of the image by rows 'x' and column 'y' and change its three colors values 'c' by alpha and beta (so we have a 3vect table)
	for( int y = 0; y < src.rows; y++ )
	    { for( int x = 0; x < src.cols; x++ )
	        { for( int c = 0; c < 3; c++ )
	            {
			    new_src.at<Vec3b>(y,x)[c] =
	        	saturate_cast<uchar>( alpha*( src.at<Vec3b>(y,x)[c] ) + beta );
	            }
	    	}
    }

	/// we create windows to show original image and new lighten/darken image
	namedWindow("Source Image", 1);
	namedWindow("New Image", 1);

	/// we show the images in the windows
	imshow("Source Image", src);
	imshow("New Image", new_src);
	
}


//Panorama *****************************************************************************
void printUsage()
{
    cout <<
        "if you want to use panorama please enter ./cpp image1 image2";
}

