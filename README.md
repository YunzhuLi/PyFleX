# PyFleX

[Nvidia FleX](https://developer.nvidia.com/flex) is an amazing particle-based simulator for simulating rigid bodies, fluids, clothing, etc. In this repo, we have developed Python bindings for setting up and interacting with [enviroments](#demo) of different kind.

## Prerequisite

This code base is tested with Ubuntu 16.04 LTS and CUDA 9.1. Other versions might work but are not guaranteed.

## Compile and play with the original demo provided by NVIDIA FleX

First compile the demo

    cd demo/compiler/makelinux64/
    make -j

Then go to the target folder and start the demo!

    cd ../../../bin/linux64
    ./NvFlexDemoReleaseCUDA_x64


## Compile PyFleX with CMake & Pybind11

Go to the root folder of `PyFleX`, and set up paths

    export PYFLEXROOT=${PWD}
    export PYTHONPATH=${PYFLEXROOT}/bindings/build:$PYTHONPATH
    export export LD_LIBRARY_PATH=${PYFLEXROOT}/external/SDL2-2.0.4/lib/x64:$LD_LIBRARY_PATH

Start compiling

    cd bindings/
    mkdir build; cd build; cmake ..; make -j
    export PYFLEXROOT=/home/yunzhu/Documents/PyFleX
    export PYTHONPATH=${PYFLEXROOT}/bindings/build:$PYTHONPATH
    export export LD_LIBRARY_PATH=${PYFLEXROOT}/external/SDL2-2.0.4/lib/x64:$LD_LIBRARY_PATH

    python -c "import pyflex; pyflex.main()"

    cd ${PYFLEX}/bindings/examples
    python test.py


## Demo


## APIs


## References

- Original NVIDIA FleX - 1.2.0 [README](doc/README_FleX.md)
