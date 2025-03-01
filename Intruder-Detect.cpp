
#include <opencv2/opencv.hpp>
#include <windows.h>

int main() 
{
  // Set the video file path
  std::string video_path = "theifs.mp4";
  std::string alarm_sound_path ="alert.wav";

  // Open the video capture object
  cv::VideoCapture cam(video_path);

  // Check if the video capture object is opened successfully
  if (!cam.isOpened()) 
  {
    std::cout << "Error: Could not open video file." << std::endl;
    return 1;
  }

  // Loop to process video frames
  while (true) 
  {
    // Read two consecutive frames
    cv::Mat frame1, frame2;
    bool ret = cam.read(frame1) && cam.read(frame2);

    // Check if the frames are successfully captured
    if (!ret) 
    {
      std::cout << "Error: Failed to capture frame." << std::endl;
      break;
    }

    // Calculate the absolute difference between frames
    cv::Mat diff;
    cv::absdiff(frame1, frame2, diff);

    // Convert the difference to grayscale
    cv::Mat grey;
    cv::cvtColor(diff, grey, cv::COLOR_BGR2GRAY);

    // Apply Gaussian blur to the grayscale image
    cv::Mat blur;
    cv::GaussianBlur(grey, blur, cv::Size(5, 5), 0);

    // Threshold the blurred image to create a binary image
    cv::Mat thresh;
    cv::threshold(blur, thresh, 20, 255, cv::THRESH_BINARY);

    // Dilate the binary image to enhance the detected regions
    cv::Mat dilate;
    cv::dilate(thresh, dilate, cv::Mat(), cv::Point(-1, -1), 3);

    // Find contours in the dilated image
    std::vector < std::vector < cv::Point >> contours;
    cv::findContours(dilate, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Loop through detected contours
    for (const auto & c: contours) 
    {
      // Skip contours with small area
      if (cv::contourArea(c) < 2000) 
      {
        continue;
      }

      // Get the bounding box coordinates of the contour
      cv::Rect rect = cv::boundingRect(c);

      // Draw a rectangle around the detected object
      cv::rectangle(frame1, rect, cv::Scalar(0, 255, 0), 2);

      // Play an alert sound
      PlaySoundA(alarm_sound_path.c_str(), NULL, SND_ASYNC);

      // system("mplayer alert.wav");  for Linux 

      // Wait for a short time
      cv::waitKey(10);
    }

    // Check for user input to exit the loop
    int key = cv::waitKey(10);
    if (key == 'q') 
    {
      break;
    } 
    else 
    if (key == 'p') 
    {
      // Pause the video capture when 'p' is pressed
      cv::waitKey(0);
    }

    // Display the frame with drawn rectangles
    cv::imshow("Camera", frame1);
  }

  // Release the video capture object and close all windows
  cam.release();
  cv::destroyAllWindows();

  return 0;
}
