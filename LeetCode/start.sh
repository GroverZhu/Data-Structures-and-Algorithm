# cmake 生成

# 生成release debug两个版本
if [[ ! -n "$1" || $1 = "build" ]]; then

    if [ ! -d "cmake-build-debug" ]; then
        mkdir cmake-build-debug
    fi

    if [ ! -d "cmake-build-release" ]; then
        mkdir cmake-build-release
    fi

    cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=DEBUG .. && make -j 
    cd ../cmake-build-release && cmake .. && make -j
fi

# 仅生成debug版本
if [[ $1 = "debug" ]]; then

    if [ ! -d "cmake-build-debug" ]; then
        mkdir cmake-build-debug
    fi

    cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=DEBUG .. && make -j 
fi

# 仅生成release版本
if [[ $1 = "release" ]]; then

    if [ ! -d "cmake-build-release" ]; then
        mkdir cmake-build-release
    fi

    cd cmake-build-release && cmake .. && make -j
fi

# 测试release版本代码
if [[ $1 = "run" ]]; then

    if [[ ! -d "cmake-build-release" ]]; then
        echo execution not exits!
        exit 1;
    fi

    cd cmake-build-release
    for file in ` ls `
    do 
        if [[ -f ${file} && -x ${file} ]]; then
            echo "In release mode run ${file}......"
            ./$file
            if [[ $? -ne 0 ]]; then
                echo "In release mode run ${file} failed!"
                exit 1
            fi
        fi
    done

    echo "In release mode all tests passed!"

    cd ../cmake-build-debug
    for file in ` ls `
    do 
        if [[ -f ${file} && -x ${file} ]]; then
            echo "In debug mode run ${file}......"
            ./$file
            if [[ $? -ne 0 ]]; then
                echo "In debug mode run ${file} failed!"
                exit 1
            fi
        fi
    done

    echo "In debug mode all tests passed!"
fi

if [[ $1 && $1 = "clean" ]]; then
    rm -rf cmake-build-*
fi

