#include "opencv2/core/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace cv;
using namespace std;

const char* original_window = "影像";
const char* croppedImage = "臉部截圖";
const char* faceLearn = "臉部學習";

int learnValue = 0;
string learnName = string("");

void on_slider_faceLearn(int, void*);

int main(int argc, const char* argv[]) {

    string fn_haar = string("../haarcascade_frontalface_alt.xml");
    CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Capture Device ID 0 cannot be opened." << endl;
        return -1;
    }
    namedWindow(original_window);
    createTrackbar(faceLearn, original_window, &learnValue, 1, on_slider_faceLearn);

    Mat frame;

    int file = 0;

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    for (;;) {

        cap >> frame;
        Mat original = frame.clone();
        Mat gray;
        cvtColor(original, gray, CV_BGR2GRAY);
        // Fine the faces in the frame.
        vector< Rect_<int> > faces;
        haar_cascade.detectMultiScale(gray, faces);
        // At this point you have the position of the faces in
        // faces. Now we'll get the faces, make a prediction and
        // annotate it in the video. Cool or what?
        for (int x = 0; x < faces.size(); x++) {
            Rect face_x = faces[x];
            Mat face = gray(face_x);
            Mat face_resized;
            // cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
            // int prediction = model->predict(face_resized);
            Mat croppedFaceImage;
            original(face_x).copyTo(croppedFaceImage);
            imshow(croppedImage, croppedFaceImage);
            rectangle(original, face_x, CV_RGB(0, 255, 0), 1);

            if (learnValue == 1) {
                std::ostringstream oss;
                oss << learnName << file << ".png";
                file++;
                imwrite(oss.str(), croppedFaceImage, compression_params);
                if ( file == 10) {
                    learnValue = 0;
                    setTrackbarPos(faceLearn, original_window, 0);
                }
            } else {
                file = 0;
            }
        }
        imshow(original_window, original);

        char key = (char) waitKey(20);
        if (key == 27) {
            break;
        }
    }

    return 0;
}

void on_slider_faceLearn(int, void*) {

    if (learnValue == 1) {
        string name;
        cout << "enter your name:";
        getline(cin, learnName);
    } else {
        learnName = string("");
    }
}
