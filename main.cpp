#include "final.h"

ostringstream err;

/************************************************
 main
 ************************************************/
int main(int argc, char *argv[]) {
    try {
        
        if (argc < 2){
            err << "No video file has been selected."  << endl;
            help();
            throw err.str();
        }
        
        if (argc > 2 ){
            err << "Too many arguments."  << endl;
            help();
            throw err.str();
        }
        
        processVideo(argv[1]);
        
    } catch (string error) {
        cout << "Error:\t" << error << endl;
        return -1;
    }
    return 0;
}

void help(){
    err << "Use:\t./detectScenes ../data/xxx.mp4"  << endl;
    err << "Ex:\t./detectScenes ../data/icedCoffee.mp4"  << endl;
}
