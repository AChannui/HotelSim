From opensuse/leap:15.5

RUN true \
    && zypper install -y --type pattern devel_C_C++ \
    && zypper install -y \
        cmake \
        gdb \
        gdbserver \
        less \
        vim \
        zsh \
    && true
