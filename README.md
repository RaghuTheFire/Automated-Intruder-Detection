# Automated-intruder-detection
Save your security maintenance money by simply building your own . Your siblings will be afraid to steal anything from your room. Learn OpenCV, computer vision, motion detection, tracking movement, image processing and so much more 

# Intruder-Detect.cpp

This C++ code is an implementation of a motion detection system using the OpenCV library. 
Here's a breakdown of what the code does: 
1. The code includes the necessary header files for OpenCV and the Windows API.
2. 2. The `main()` function is the entry point of the program.
3. The video file path and the alarm sound file path are set.
4. A `cv::VideoCapture` object is created to open the video file.
5. The code checks if the video file is opened successfully. If not, it prints an error message and exits.
6. The program enters a loop to process the video frames.
7. In each iteration of the loop, two consecutive frames are read from the video capture object.
8. The absolute difference between the two frames is calculated to detect motion.
9. The difference image is converted to grayscale and then blurred using a Gaussian filter.
10. The blurred image is thresholded to create a binary image, which is then dilated to enhance the detected regions.
11. Contours are detected in the dilated image, and the contours with an area greater than 2000 pixels are considered as detected objects.
12. For each detected object, a green rectangle is drawn around it on the first frame, and an alert sound is played.
13. The processed frame is displayed in a window named "Camera".
14. The loop continues until the user presses the 'q' key to exit the program or the 'p' key to pause the video capture.
15. Finally, the video capture object is released, and all windows are closed.
