# tracker_209as
## Scope of the project

1. Overall project goal, vision, and specific aims (deliverables) describe clearly what you are trying to do, why is it important, and how is it done today

    The project is to conduct research of the latest version of SiamFC(v2/CVPR'17) and SimaFC++(arXiv:1911.06188), which are popular object tracking algorithms. Open source code of SiamFC++ will be studied and executed. The performance of the SiamFC++ will be compared to Nvidia commercial proprietary non-open source tracker. The algorithm of SiamFC++ and/or SiamFC will be optimized and rewritten in C/C++, and also will be analyzed to determine if it can be efficiently implemented on FPGA with High-Level Synthesis (HLS) and/or Verilog, and if possible, on openOPU platform. Previous studies and optimization of SiamFC and SiamFC++ are all on GPU platforms. Implementing SiamFC and SiamFC++ on FPGA may provide a low power, low latency alternative. No related research has been found on internet.

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

    TBD

1. References (with hyperlinks to papers, websites etc.)

    https://www.robots.ox.ac.uk/~luca/siamese-fc.html;    
    https://developer.nvidia.com/Deepstream-sdk;    
    https://arxiv.org/abs/1911.06188;    
    https://github.com/MegviiDetection/video_analyst;

## How to build and run the project
Prerequisite: NVIDIA DeepStream SDK

Installation instructions can be found here: 

https://docs.nvidia.com/metropolis/deepstream/dev-guide/text/DS_Quickstart.html

After installation, using the following steps to run the tracker app

1. enter tracker app folder
```Bash
cd ~/tracker_209as/sources/apps/my_apps/tracker
```
2. Build the tracker app
```Bash
make
```
3. Run tracker app
```Bash
./tracker -c configs/config.txt -t
```
