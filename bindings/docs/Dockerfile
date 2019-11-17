FROM nvidia/cuda:9.1-devel-ubuntu16.04

RUN apt update && apt install -y wget unzip curl bzip2 git
RUN curl -LO http://repo.continuum.io/miniconda/Miniconda-latest-Linux-x86_64.sh
RUN bash Miniconda-latest-Linux-x86_64.sh -p /miniconda -b
RUN rm Miniconda-latest-Linux-x86_64.sh
ENV PATH=/miniconda/bin:${PATH}
RUN conda update -y conda

RUN mkdir /workspace/ && cd /workspace/ && git clone https://github.com/YunzhuLi/PyFleX.git && cd PyFleX
RUN /workspace/PyFleX/bindings/scripts/install_deps.sh

WORKDIR /workspace

