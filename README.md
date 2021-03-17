# tracker_209as
## Scope of the project

1. Overall project goal, vision, and specific aims (deliverables) describe clearly what you are trying to do, why is it important, and how is it done today

    The project is to conduct research of the latest version of SiamFC(v2/CVPR'17) which are popular object tracking algorithms. A portion of python source code, Alexnet backbone and weights of https://github.com/logiklesuraj/SiamFC is used when implemention siamfc_tracker using cython and C/C++. 
    
    The performance of the siamfc_tracker was compared to Nvidia commercial proprietary non-open source tracker and opencv trackers. After evaluation, the CNN portion of the Alexnet can be implemented on FPGA using openOPU toolchain. 

1. Technical approach covering data sets, algorithms, etc. and novelty of your approach.

    For the comparison matrix, the pre-trained model provided by the creators and Nvida will be used. 
Algorithm used are SiamFC, NvDCF, KLT, and IOU.

1. Implementation, experimental evaluation, success metrics, and key findings.

    A report will be provided for the comparison matrix and the possible algorithm modification or improvement so it will fit into FPGA. 

1. Prior work examples including references, and the relative novelty of your work.

    Prior work examples include SiamFC open source code, and links to Nvidia DeepStream SDK.

1. Strengths and weakness, and future directions.

    The intention of the project is evaluating the feasibility and possible benefits implementing of a popular tracker on FPGA platform. However, with the ever increasing performance of modern GPUs, implementing SiamFC tracker on FPGA may not make sense from either technical or economy point of view. A more FPGA/ASCI friendly tracker may need to be created.

1. Contributions of each team member.

    Mingyu Wang will cover the entire project.

1. Section with links to PDF of your final presentation slides, and any data sets not in your repo.

    Presentaton slides in both PDF and PPTX format can be found in this google driver folder
    https://drive.google.com/drive/folders/1kQ9oYGNKJQIJq9AKnScDSJJKIHCBMGqS?usp=sharing

1. References (with hyperlinks to papers, websites etc.)

    https://www.robots.ox.ac.uk/~luca/siamese-fc.html;    
    https://developer.nvidia.com/Deepstream-sdk;    
    https://arxiv.org/abs/1911.06188;    
    https://github.com/MegviiDetection/video_analyst;
    https://github.com/logiklesuraj/SiamFC;

## How to build and run the project

All projects are built and tested on ubuntu 18.04
### Build and run DeepStream trackers test app
Prerequisite: NVIDIA DeepStream SDK

Installation instructions can be found here: 

https://docs.nvidia.com/metropolis/deepstream/dev-guide/text/DS_Quickstart.html

After installation, using the following steps to build run the tracker test app

1. enter tracker_deepstream app folder
```Bash
cd ~/tracker_209as/sources/apps/my_apps/tracker_deepstream
```
2. Build the tracker app
```Bash
make
```
3. Run tracker app
```Bash
./tracker -c configs/config.txt -t
```

To switch trackers, change the tracker libary in configs/config files in the [tracker] section
### Build and run OpenCV trackers test app
Prerequisite: OpenCV 4.5.x

Installation instructions can be found here: 

https://docs.opencv.org/master/d2/de6/tutorial_py_setup_in_ubuntu.html 

After installation, using the following steps to run the tracker test app

1. enter tracker_opencv app folder
```Bash
cd ~/tracker_209as/sources/apps/my_apps/tracker_opencv
```
2. Build the tracker app
```Bash
mkdir build
cd build
cmake ../.
make
```
3. Run tracker app
```Bash
./tracker_opencv video ../../../../../videos/single_car.mp4
```
To switch trackers, change the following line in main.cpp under create tracker object section and make again

See https://docs.opencv.org/3.4/d9/df8/group__tracking.html for the list of trackers supported by OpenCV

### Build and run SiamFC tracker app

SimaFC tracker is a python based application wrapped with cython and embeded into C/C++. The advantages of using Cython can be found at https://cython.org/

Python code, NN models and weights are partially from https://github.com/logiklesuraj/SiamFC, with some modifications

Prerequisites: 

* Python 3.6.x, note Python 3.8.x was tested but it caused segmentation error when embedded into C/C++ application
* OpenCV 4.5.x
* Pytorch. Pytorch can be install using following command assuming you use cuda 10.2 
```Bash
conda install pytorch torchvision torchaudio cudatoolkit=10.2 -c pytorch
```

Using the following steps to run the SiamTracker app
1. enter tracker_siamfc app folder
```Bash
cd ~/tracker_209as/sources/apps/my_apps/tracker_siamfc
```
2. Build SiamTracker app
```Bash
make
```
3. Run SiamTracker app
```Bash
./tracker_siamfc
```


