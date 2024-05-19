# Data Structures and Algorithm

Record the data structures and algorithm jounery, the cpskill move to this [repo](https://github.com/GroverZhu/CPSKILL)

The `build_support`, `.github`, `CmakeLists.txt` is modify from [bustub](https://github.com/cmu-db/bustub)

project structure
```
./
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build_support
└── src
```

# run this project



- Supported OS: Linux or MacOS
- Software: g++ or LLVM, CMAKE
- Build the project: 
    - in the current dirctory, use the command `mkdir build && cd build && cmake .. && make all -j`
    - if you want in the debug mode, use this command `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=DEBUG .. && make all -j`
    - all the executable files are in the directory `build/bin`
    - `make format` can format all the code which defined in the file `.clang-format`
    - in `build/bin` directory, run `bash ../../build_support/run_executable.sh` will run all the algorithms.
    - `make check-format`