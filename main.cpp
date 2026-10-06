#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 1. 打开摄像头（0表示第一个摄像头）
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Camera not found!" << std::endl;
        return -1;
    }

    // 2. 加载人脸检测器
    cv::CascadeClassifier faceDetector;
    faceDetector.load("D:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml");
    if (faceDetector.empty()) {
        std::cout << "Detector load faild!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::vector<cv::Rect> faces;

    // 3. 循环：不断读摄像头画面 + 检测人脸 + 显示
    while (true) {
        cap >> frame;                    // 从摄像头读一帧画面
        if (frame.empty()) break;

        // 检测人脸
        faceDetector.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(30, 30));

        // 画红框
        for (size_t i = 0; i < faces.size(); i++) {
            cv::rectangle(frame, faces[i], cv::Scalar(0, 0, 255), 2);
        }

        // 显示
        cv::imshow("Arsit - Face Tracking", frame);

        // 按ESC键退出（ESC的ASCII码是27）
        if (cv::waitKey(30) == 27) break;
    }

    cap.release();  // 释放摄像头
    return 0;
}