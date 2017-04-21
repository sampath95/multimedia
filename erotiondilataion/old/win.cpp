

#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const String keys =
    "{help h usage ?  |      | print this message   }"
    "{@image          |<none>| image to show        }"
;

// store the position of trackbar
int blurAmount=1;

// call back function to execute every time the trackbar change
static void onChange(int pos, void* userInput);

// call back for mouse input
static void onMouse( int event, int x, int y, int, void* userInput);

int main( int argc, const char** argv )
{

  CommandLineParser parser(argc, argv, keys);
  parser.about("ISEP C++ 2017");

  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }

  String img_filename = parser.get<String>(0);

  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  Mat img = imread(img_filename);
  namedWindow("img", WINDOW_AUTOSIZE);

  // create the Trackbar
  createTrackbar("img", "img", &blurAmount, 50, onChange, &img);

  // define the callback for ,ouse events
  setMouseCallback("img", onMouse, &img);

  // Call back to onChange function
  onChange(blurAmount, &img);

  // wait app for a key to exit
  waitKey(0);

  // Destroy the windows
  destroyWindow("img");

  return 0;
}

// Trackbar call back function
static void onChange(int pos, void* userInput)
{
  if(pos <= 0)
    return;

  // result
  Mat imgBlur;

  // casting the input user img to
  Mat* img = (Mat*)userInput;

  // Apply a blur filter
  blur(*img, imgBlur, Size(pos, pos));

  //exercise: apply a different filter using 'pos' as the transformation scalar factor.

  // Show the result
  imshow("img", imgBlur);
}

//Mouse callback
static void onMouse( int event, int x, int y, int, void* userInput )
{
  if( event != EVENT_LBUTTONDOWN )
    return;

  // casting the userInput to the current image
  Mat* img= (Mat*)userInput;

  // Draw point
  circle(*img, Point(x, y), 5, Scalar(255,0,0), -1);

  //exercise: draw an ellipse instead of circle

  // apply the blue filter to the new point
  onChange(blurAmount, img);
}