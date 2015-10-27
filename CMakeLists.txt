CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## Find Boost
SET(Boost_INCLUDE_DIR "c:/pkg/boost_1_59_0/awf-install/include/boost-1_59" )
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

## Find Eigen
INCLUDE_DIRECTORIES( "C:\\pkg\\Eigen-3.2.5\\awf-install\\include\\eigen3" )


# stan
INCLUDE_DIRECTORIES("C:/dev/github/stan/src")

PROJECT(autodiff)

ADD_EXECUTABLE(Vec_test autodiff/Vec_test.cpp autodiff/Vec.h)

ADD_EXECUTABLE(autodiff autodiff/autodiff.cpp autodiff/Vec.h autodiff/Dot.h )

#ADD_EXECUTABLE(stan_autodiff stan.cpp c:/dev/github/stan/src/stan/agrad/rev/var_stack.cpp)

add_custom_target(Documents SOURCES "autodiff/Differentiating Containers.md" )
