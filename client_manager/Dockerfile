FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    wget \
    curl \
    libpq-dev \
    libssl-dev \
    build-essential \
    pkg-config \
    gdb \
    gdbserver \
    rsync \
    ca-certificates \
    sudo \
    && apt-get clean

RUN apt-get install -y python3 python3-pip

RUN useradd -ms /bin/bash developer && echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
USER developer
WORKDIR /home/developer

RUN git clone --depth 1 https://github.com/jtv/libpqxx.git && \
    cd libpqxx && \
    cmake -B build -S . -DPQXX_BUILD_SHARED=ON -DPQXX_BUILD_TEST=OFF && \
    cmake --build build && \
    sudo cmake --install build && \
    sudo ldconfig

ENV LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"

CMD ["/bin/bash"]
