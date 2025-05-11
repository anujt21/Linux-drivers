# NetworkingTool
The tool is used to create a custom DNS sinkhole server to prevent ads and trackers.

## Installation
The kernel modules can be generated using:
'''bash
./build.sh

For cross compilation set the ARCH, CROSS_COMPILE, and KDIR variable:
'''bash
export ARCH = arm64
export CROSS_COMPILE = aarch64-linux-gnu-
export KDIR = ~/linux
'''
Set the KDIR variable to the local linux environment.

Execute the build command:
'''bash
./build.sh
'''
