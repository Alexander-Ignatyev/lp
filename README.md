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

### Convex Optimisation: Resources

#### Convex Optimization by Boyd and Vandenberghe

[Free e-book page](http://web.stanford.edu/~boyd/cvxbook/)

#### EE103 - Applied Numerical Computing by Vandenberghe
[Course page](http://www.seas.ucla.edu/~vandenbe/ee103.html) (see least-squares and least-norm pages)

[Prof. L. Vandenberghe page](http://www.seas.ucla.edu/~vandenbe/index.html)

#### CVX examples
[CVX examples page](http://cvxr.com/cvx/examples/)
Figures, examples, and exercises from the book Convex Optimization -> Chapter 6: Approximation and fitting -> Quadratic smoothing

#### CVXOPT examples
[CVXOPT examples page](http://cvxopt.org/examples/index.html) especially see [Quadratic smoothing](http://cvxopt.org/examples/book/smoothrec.html) and [Penalty function approximation](http://cvxopt.org/examples/book/penalties.html)