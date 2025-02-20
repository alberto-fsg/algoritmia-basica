#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Load the image
    cv::Mat image = cv::imread("profile.jpg");

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Create a window and display the image
    cv::namedWindow("Profile Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Profile Image", image);

    // Wait for a key press indefinitely
    cv::waitKey(0);

    // Close all OpenCV windows
    cv::destroyAllWindows();
    return 0;
}
