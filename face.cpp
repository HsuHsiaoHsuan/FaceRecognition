#include "opencv2/core/core.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, const char* argv[]) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << " </path/to/haar_cascade>" << endl;
        cout << "\t </path/to/haar_cascade> -- Path to the Haar Cascade for face detection." << endl;
        exit(1);
    }

    string fn_haar = string(argv[1]);

    CascadeClassifier haar_cascade;
    haar_cascade.load(fn_haar);

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Capture Device ID 0 cannot be opened." << endl;
        return -1;
    }

    Mat frame;

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
        }
    }




    return 0;
}
