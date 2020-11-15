FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
  make \
  cmake \ 
  cppcheck \
  valgrind \
  doxygen \
  graphviz \
  clang \
  libgtest-dev \
  && apt-get install -y git \
&& rm -rf /var/lib/apt/lists* \