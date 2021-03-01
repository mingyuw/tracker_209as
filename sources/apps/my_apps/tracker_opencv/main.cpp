#include <iostream>
#include <cstring>
#include <time.h>

#include <opencv2/tracking/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


using namespace std;
using namespace cv;
int main( int argc, char** argv ){
  // show help
  if(argc<3){
    cout<<
      " Usage: tracker <video_name>\n"
      " examples:\n"
      " webcam ID\n"
      " video path_to_video_file\n"
      << endl;
    return 0;
  }
  // declares all required variables
  Rect roi;
  Mat frame;
  
  // create a tracker object
  //Ptr<Tracker> tracker = TrackerKCF::create();
  //char tracker_name[] = "TrackerKCF";
  
  //Ptr<Tracker> tracker = TrackerCSRT::create();
  //char tracker_name[] = "TrackerCSRT";
  
  Ptr<Tracker> tracker = TrackerMIL::create();
  char tracker_name[] = "TrackerMIL";

  
  VideoCapture cap;  
  std::string input_source = argv[1];
  std::string video = argv[2];  
  
  if (input_source == "webcam") {
    // set input video

    int deviceID = stoi(video);
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
  }
  else if (input_source == "video") {
    cap = VideoCapture(video);
  }
  else {
    return 0;
  }

  int frame_count = 0;
  for ( ;; ){
    // wait for key to select object 
    if(waitKey(1)==' ')
      break;
    // get frame from the video      
    cap >> frame;
    resize(frame, frame, Size(), 0.5, 0.5);
    putText(frame, "Select obj and press space to start tracking", Point(frame.size().width - 700, frame.size().height - 100), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255));
    // show image with the tracked object
    imshow("tracker",frame);
    if (frame_count++ > 55)
    {
      break;     
    }
  }
  frame_count = 0;
  // get bounding box
  roi = selectROI("tracker",frame);
  //quit if ROI was not selected
  if(roi.width == 0 || roi.height == 0)
    return 0;
  // initialize the tracker
  tracker->init(frame,roi);
  // perform the tracking process
  printf("Start the tracking process using %s, press ESC to quit.\n", tracker_name);

  int fps_frame = 0;
  float fps = 0;
  const int sec_average_4_fps_calc = 2;
  char tracker_str[200];
  struct timespec ts;
  clock_gettime( CLOCK_MONOTONIC, &ts);
  long start_tick = ts.tv_sec;
  long start_tick_total = start_tick; 
  for ( ;; ){
    // get frame from the video
    frame_count ++;
    fps_frame ++;
    clock_gettime( CLOCK_MONOTONIC, &ts );
    long end_tick = ts.tv_sec - start_tick;
    if (end_tick  >= sec_average_4_fps_calc)
    {
      clock_gettime( CLOCK_MONOTONIC, &ts);
      start_tick = ts.tv_sec; 
      fps = float(fps_frame) / sec_average_4_fps_calc;
      fps_frame = 0; 
      float time_elapsed = ts.tv_sec - start_tick_total;
      printf("Frames elapsed = %d, Time elapsed = %.3f, Curr FPS = %.2f \n", frame_count, time_elapsed, fps);
    }
    cap >> frame;

    // stop the program if no more images
    if(frame.rows == 0 || frame.cols == 0)
    {
      // Calculate the average FPS
      clock_gettime( CLOCK_MONOTONIC, &ts);
      float time_elapsed = float(ts.tv_sec - start_tick_total);
      printf("Total frames = %d, Time elapsed = %.3fs \n", frame_count, time_elapsed);
      printf("Average FPS = %.2f\n", (frame_count) / time_elapsed);
      break;
    }  
    resize(frame, frame, Size(), 0.5, 0.5);    
    // update the tracking result
    tracker->update(frame,roi);
    // draw the tracked object
    rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );
    sprintf(tracker_str,"Frame = %u, FPS = %.2f ", frame_count, fps);
    putText(frame, tracker_str, Point(roi.x, roi.y -10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar( 255, 0, 0 ));
    // show image with the tracked object
    imshow("tracker",frame);
    //quit on ESC button
    if(waitKey(1)==27)break;
  }
  return 0;
}