FROM mcr.microsoft.com/vscode/devcontainers/cpp:ubuntu-22.04

# Install additional system packages.
RUN apt-get update && \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y install --no-install-recommends build-essential libgmp-dev libyaml-cpp-dev


RUN curl -L https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-linux.tar.gz > premake-5.0.0-alpha16-linux.tar.gz
RUN tar -zxf  premake-5.0.0-alpha16-linux.tar.gz -C tmp/
RUN cp tmp/premake5 usr/bin/

#RUN curl -L https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz > tmp/boost_1_76_0.tar.gz
#RUN tar -zxf  tmp/boost_1_76_0.tar.gz -C tmp/
#RUN cd tmp/boost_1_76_0 && \
#    ./bootstrap.sh && \
#    ./b2 && \
#    ./b2 install
vcpkg install boost