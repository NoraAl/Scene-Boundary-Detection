#include "final.h"


/************************************************
 segment: this is a very long function, with very long for loop
 almost done every thing
 ************************************************/

void segment (VideoCapture vid){
    
    /* 1. open the xml classification files and push the content to Mats */
    
    Mat abruptClasses, abruptFeatures, gradualClasses, gradualFeatures;
    open("../data/AbruptClasses.xml", "AbruptClasses", abruptClasses);
    open("../data/AbruptFeatures.xml", "AbruptFeatures", abruptFeatures);
    open("../data/GradualClasses.xml", "GradualClasses", gradualClasses);
    open("../data/GradualFeatures.xml", "GradualFeatures", gradualFeatures);
    
    
    /* 2. call Opencv function train on the previous Mats */
    Ptr<ml::KNearest>  nearestAbrupt(ml::KNearest::create());
    nearestAbrupt->train(abruptFeatures, ml::ROW_SAMPLE, abruptClasses);
    
    Ptr<ml::KNearest>  nearestGradual(ml::KNearest::create());
    nearestGradual->train(gradualFeatures, ml::ROW_SAMPLE, gradualClasses);
    
    /* 3.a. get the size of the video */
    int n = vid.get(CV_CAP_PROP_FRAME_COUNT);
    
    
    /* 3.b. define variables needed */
    int d = L*L*2; int shots = 1, wait = 1, current = 0, wasgradual = 0, continuous = 2;
    
    /* 3.c. define and create the kernel */
    int K[LR][LR];
    memset(K, 0, sizeof(int) * LR * LR);/* if created outside function you don't need to initiliaze (stds)*/
    
    for (int i = 0 ; i < LR; i++){
        for (int j = 0; j < LR-i; j++){
            K[i][j] = -1;
            if ((i+j)>= (L/2)-1 && i <(L/2))
                K[i][j] = 1;
        }
    }
    
    /* 3.d. define bufferes to create matrix S, S is not nxn but rather LRxLR
     which is here 9x9 instead of thousands*thousands */
    Mat frame, tempGlobal[L], tempBlocks[L];
    int S[LR][LR][2], globalInd[L];
    
    /* 4. fill the buffers with the first L elements */
    for (int i = 0; i < L; i++) {
        vid.set(CV_CAP_PROP_POS_FRAMES, i);
        vid.read(frame);
        cvtColor(frame, frame, CV_BGR2YUV);
        
        tempGlobal[i] = globalHistogram(frame);
        tempBlocks[i] = blockHistogram(frame);
        globalInd[i] = i;
    }
    
    /*set to the last read frame, because in the loop it will read the farthest every iteration*/
    int frameIndex = L-1, showIndex = L/2, i, farthest, counter = (LR* -1)+2;
    vid.set(CV_CAP_PROP_POS_FRAMES, frameIndex);
    
    
    /*************************
     looping over frames and creating S and X
     *************************/
    for (i = 0, farthest = L-1 ; vid.read(frame) ; i++, farthest++, vid.set(CV_CAP_PROP_POS_FRAMES, ++frameIndex)) {
        
        current = i % L;
        
        
        /* 1. read the frame of index (frameIndex) */
        cvtColor(frame, frame, CV_BGR2YUV);
        
        tempGlobal[farthest%L] = globalHistogram(frame);
        tempBlocks[farthest%L] = blockHistogram(frame);
        globalInd[farthest%L] = farthest;
        
        
        /* 2. calculat a single row of S */
        for (int k = 1; k < L; k++) {
            int gDistance = compareHist(tempGlobal[current], tempGlobal[(current+k)%L], CV_COMP_CHISQR_ALT );
            int bDistance = compareHist(tempBlocks[current], tempBlocks[(current+k)%L], CV_COMP_CHISQR_ALT );

            S[i%LR][k-1][0] = gDistance;
            S[i%LR][k-1][1] = bDistance;
   
        }
        
        
        /* 3. calculat a single row of X */
        if (counter>0){/*matrix S is now filled with sufficint information for matrix X*/
            
            Mat temp;
            int r = (i+1)%LR;
            
            for (int k = 0; k < LR; k++){
                for (int l =0; l<LR-k; l++) {

                    int next = (r+k)%LR;
                    temp.push_back((K[k][l]*S[next][l][0])/d);
                    temp.push_back((K[k][l]*S[next][l][1])/d);
                }
            }
            
            Mat floatFeatures, flattenedFeatures;
            
            temp.convertTo(floatFeatures, CV_32FC1);
            flattenedFeatures = floatFeatures.reshape(1, 1);
            int classid = 0;
            Mat currenntClass(0, 0, CV_32F);
            
            if (wasgradual){
                if (continuous){
                    nearestGradual->findNearest(flattenedFeatures, 3, currenntClass);
                    classid = currenntClass.at<float>(0, 0);
                    if (classid){
                        
                    } else{
                        continuous--;
                        if (!continuous){//two continuous frames are normal
                            wasgradual = 0;
                            shots++;
                            wait = -10;
                            continuous = 2;
                            cout<< "gradual ends\n";
                        }
                    }
                }
            }
            else if (wait > 0){
                nearestAbrupt->findNearest(flattenedFeatures, 3, currenntClass);
                classid = currenntClass.at<float>(0, 0);
                
                if (classid){// it is abrupt
                    shots++;
                    wait = -10;
                }else{
                    //test for gradual
                    nearestGradual->findNearest(flattenedFeatures, 3, currenntClass);
                    
                    classid = currenntClass.at<float>(0, 0);
                    if (classid){
                        wasgradual++;
                    }
                }
            }
            vid.set(CV_CAP_PROP_POS_FRAMES, showIndex++);
            vid.read(frame);
            if (wasgradual)
                showframe(frame, -1);
            else
                showframe(frame, shots);
            //cout << classid<<endl;
            wait++;
            
        }
        counter++;
        /*end 2*/
    }
    
    cout<<endl;
    
}



/************************************************
 open xml files and push the content to Mat type for further processing
 ************************************************/
void open(string filename, string annotation, Mat& mat){
    FileStorage abruptCF(filename, FileStorage::READ);
    
    if (abruptCF.isOpened() == false) {
        err <<"cannot open "<<filename <<endl;
        throw err.str();
    }
    abruptCF[annotation] >> mat;      // read classifications section into Mat classifications variable
    abruptCF.release();
}


