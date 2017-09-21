# Video Boundary Detection
![](https://i.imgur.com/4lLMym1.png)

This is a very simple implementation for the algorithm in  [*"Video Segmentation via Temporal Pattern Classification"*](http://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=4130365)  paper. The kernel being used is the **full similarity** kernel. The sequentail number of the scene will appear on the upper left corner of the window. If the change in scene is gradual, the symbol '-' indicates that, as in the picture above. 
You can put any mp4 video inside the directory `data` for test.

## General
- **Language**: C++.
- **Library**: OpenCV.
- **Build System**: CMake.
- **Video extensions**: MP4.

## Build
The project can be built with [CMake](https://cmake.org). Once cloned, cd to the repository (i.e. Scene-Boundary-Detection), and you can follow the below steps:

```sh
$ mkdir build
$ cd build
$ cmake ..
```
Then 
```sh
$ make
```
For the following step, the `xxx.mp4` is any mp4 file located inside the directory `data`:
```sh
$ ./detectScenes ../data/xxx.mp4
```
### Notes
- This repository is only the **test** part of the algorithm, the **training** repository will be uploaded for better training.
- The used OpenCV library has some issues with `AVI` extension.
- There is some overhead. It is to buffer the computation and show the result immediately, regardless of the video length.
- Performance is an issue right now: no optimization is being utilized.
- Frames are being processed as they are. No change in size, skipping frames or any other kind of downsampling.

### Credit
Included videos are from Vimo library. How to download from Vimo: [official link.](https://help.vimeo.com/hc/en-us/articles/229678128-Downloading-videos)

- [Soto Coffee](https://vimeo.com/41298356), `SotoCoffee.mp4`, by Miles Peterson. 
- [How to Make Japanese Iced Coffee](https://vimeo.com/109992850), `icedCoffee.mp4`, by Counter Culture Coffee.
