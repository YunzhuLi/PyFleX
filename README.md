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

Try with `FluidFall` example. A window will pop up showing the simulation results.

    cd ${PYFLEXROOT}/bindings/examples
    python test_FluidFall.py


## Demo

Directly run the python script to see the environments. Screenshots will be stored in `${PYFLEXROOT}/bindings/examples/test_[env]/`.


**FluidFall** - Two drops of high-viscosity fluids are falling down and merging with each other.

    cd ${PYFLEXROOT}/bindings/examples
    python test_FluidFall.py

![](imgs/FluidFall.gif)


**BoxBath** - A block of water is flushing a rigid cube.

    cd ${PYFLEXROOT}/bindings/examples
    python test_BoxBath.py

![](imgs/BoxBath.gif)


**FluidShake** - Shaking a box of fluids. The following script will first simulate the scene, and then playback while removing the frontal box wall for visualization.

    cd ${PYFLEXROOT}/bindings/examples
    python test_FluidShake.py

![](imgs/FluidShake.gif)


**RiceGrip** - Shaking a box of fluids.

    cd ${PYFLEXROOT}/bindings/examples
    python test_RiceGrip.py

![](imgs/RiceGrip.gif)


**RigidFall** - A stack of rigid cubes falling down.

    cd ${PYFLEXROOT}/bindings/examples
    python test_RigidFall.py

![](imgs/RigidFall.gif)


**FluidIceShake** - Shaking a box of fluids and a rigid cube. The following script will first simulate the scene, and then playback while removing the frontal box wall for visualization.

    cd ${PYFLEXROOT}/bindings/examples
    python test_FluidIceShake.py

![](imgs/FluidIceShake.gif)


## APIs

Please see the bottom of `bindings/pyflex.cpp` for the supported APIs.


## References

- Original NVIDIA FleX - 1.2.0 [README](doc/README_FleX.md)
