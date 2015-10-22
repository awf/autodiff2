CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## Find Boost
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/pkg/boost_1_57_0" )
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/pkg/boost_1_57_0/libs")
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

## Find Eigen
INCLUDE_DIRECTORIES( "C:/Program Files (x86)/Eigen/include/eigen3" )


# stan
INCLUDE_DIRECTORIES("C:/dev/github/stan/src")

PROJECT(autodiff)

ADD_EXECUTABLE(autodiff autodiff/autodiff.cpp autodiff/Vec.h  )

ADD_EXECUTABLE(stan_autodiff stan.cpp c:/dev/github/stan/src/stan/agrad/rev/var_stack.cpp)

#ADD_EXECUTABLE(Vec_test autodiff/Vec_test.cpp autodiff/Vec.h)
