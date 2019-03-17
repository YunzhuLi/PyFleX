PyFleX
======


Compile demo
------------

    cd demo/compiler/makelinux64/
    make


Compile demo using cmake
------------------------

    cd examples/
    mkdir build; cd build; cmake ..; make -j
    ./example


Compile demo with cmake & Pybind11
----------------------------------

    cd bindings/
    mkdir build; cd build; cmake ..; make -j
    export PYFLEXROOT=/home/yunzhu/Documents/PyFleX
    export PYTHONPATH=${PYFLEXROOT}/bindings/build:$PYTHONPATH
    export export LD_LIBRARY_PATH=${PYFLEXROOT}/external/SDL2-2.0.4/lib/x64:$LD_LIBRARY_PATH

    python -c "import pyflex; pyflex.main()"

    cd ${PYFLEX}/bindings/examples
    python test.py


Demo
----


References
----------

- Original NVIDIA FleX - 1.2.0 [readme](./README_FleX.md)
