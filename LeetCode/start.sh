# cmake 生成

# 生成release debug两个版本
if [[ ! -n "$1" || $1 = "build" ]]; then

    if [ ! -d "cmake-build-debug" ]; then
        mkdir cmake-build-debug
    fi

    if [ ! -d "cmake-build-release" ]; then
        mkdir cmake-build-release
    fi

    cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=DEBUG .. && make -j 4
    cd ../cmake-build-release && cmake .. && make -j4
fi

# 仅生成debug版本
if [[ $1 = "debug" ]]; then

    if [ ! -d "cmake-build-debug" ]; then
        mkdir cmake-build-debug
    fi

    cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=DEBUG .. && make -j 4
fi

# 仅生成release版本
if [[ $1 = "release" ]]; then

    if [ ! -d "cmake-build-release" ]; then
        mkdir cmake-build-release
    fi

    cd cmake-build-release && cmake .. && make -j 4
fi


if [[ $1 && $1 = "clean" ]]; then
    rm -rf cmake-build-*
fi

