# Linear and Interger Programming

## by Sriram Sankaranarayanan, Shalom D. Ruben

The project contains source code of the programming assignments of the course.

### Structure

* src - contains all source code
* src/lplib - source code of Linear Programming Library
* src/homework* - source code of homeworks
* configs - config files of homeworks
* data - homeworks files provided by course instructors
* result - results iof homeworks
* run.py - main script

### How to use

#### 1. Build the project
    mkdir build
    cd build
    cmake ..
    make

#### 2. Config and run run.py

The scripts initially run all tests and in case of success run homework tasks.

To import settings of the homework use **import** instruction in the beginning of the file:

    # import homework settings
    import config21 as config
