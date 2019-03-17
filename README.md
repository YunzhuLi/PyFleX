PyFleX
======

[Nvidia FleX](https://developer.nvidia.com/flex) is an amazing particle-based simulator for simulating rigid bodies, fluids, clothing, etc. In this repo, we have developed a Python warpper for setting up and interacting with several different [enviroments](#demo).

Prerequisite
------------

This code base is tested with Ubuntu 16.04 LTS and CUDA 9.1. Other versions might work but are not guaranteed.

Compile and play with the original demo provided by NVIDIA FleX
---------------------------------------------------------------

First compile the demo

    cd demo/compiler/makelinux64/
    make -j

Then go to the target folder and start the demo!

    cd ../../../bin/linux64
    ./NvFlexDemoReleaseCUDA_x64


Compile PyFleX with cmake & Pybind11
----------------------------------

    cd bindings/
    mkdir build; cd build; cmake ..; make -j
    export PYFLEXROOT=/home/yunzhu/Documents/PyFleX
    export PYTHONPATH=${PYFLEXROOT}/bindings/build:$PYTHONPATH
    export export LD_LIBRARY_PATH=${PYFLEXROOT}/external/SDL2-2.0.4/lib/x64:$LD_LIBRARY_PATH

    python -c "import pyflex; pyflex.main()"

    cd ${PYFLEX}/bindings/examples
    python test.py


## Demo
-------


References
----------

- Original NVIDIA FleX - 1.2.0 [readme](./README_FleX.md)
