#include "final.h"

static int size;

void saveNew(Mat m, string filename, string annotaion){
    FileStorage classesfile(filename, FileStorage::WRITE);//FileStorage classesfile("classes.xml", FileStorage::WRITE);
    
    classesfile << annotaion << m;//classesfile << "classes" << m;
    if (classesfile.isOpened() == false){
        err << "unable to open training "<<annotaion<<" in "<<filename<<endl;// file";
        throw err.str();
    }
    
    classesfile.release();
    
    
}


/************************************************
 process video: open and send vid to process
 ************************************************/
void processVideo (string filename){
    VideoCapture vid;
    
    Mat frame, framYuv;
    
    if(!vid.open(filename)){
        err << "cannot open file: \""<< filename<<"\" ."  << endl;
        throw err.str();
    }
    

    
    if (!vid.isOpened()) {
        err << "error reading video file" << std::endl << std::endl;
        throw err.str();
    }
    
    if (vid.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
        err << "video file must have at least one frame";
        throw err.str();
    }
    
    const string outputfile = "fromeImages_"+filename;
    //VideoWriter outputvid(outputfile);
    segment (vid);
    
}


/************************************************
 Show the frame, and write the shot count
 ************************************************/
void showframe(Mat& frame, int count){
    string s;
    if(count<0)
        s = "-";
    else
        s = to_string(count);
    putText(frame, s, Point2f(80,80), FONT_HERSHEY_PLAIN, 6.0, CV_RGB(0,0,0), 5.0);
    putText(frame, s, Point2f(80,80), FONT_HERSHEY_PLAIN, 6.0, CV_RGB(0,255,0), 3.0);
    Size size(frame.cols/2,frame.rows/2);
    resize(frame, frame, size);
    imshow("Segmentaion", frame);
    waitKey(5);
}


