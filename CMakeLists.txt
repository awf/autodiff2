CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## Find Boost
#SET(BOOST_ROOT "c:/pkg/boost_1_59_0/awf-install")
SET(Boost_INCLUDE_DIR "c:/pkg/boost_1_59_0/awf-install/include/boost-1_59" )
FIND_PACKAGE(Boost REQUIRED) # COMPONENTS unit_test_framework )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

## Find Eigen
INCLUDE_DIRECTORIES( "C:\\pkg\\Eigen-3.2.5\\awf-install\\include\\eigen3" )


# stan
INCLUDE_DIRECTORIES("C:/dev/github/stan/src")

PROJECT(autodiff)

#ADD_EXECUTABLE(Vec_test autodiff/Vec_test.cpp autodiff/Vec.h)

ADD_EXECUTABLE(autodiff 
      autodiff/autodiff.cpp 
      autodiff/bundle.cpp 
      autodiff/dnn.cpp 
      autodiff/boost_test.cpp 
      autodiff/copy.h 
      autodiff/counting_iterator.h 
      autodiff/Zero.h 
      autodiff/Vec.h 
      autodiff/Mat.h
      autodiff/Mat_test.cpp 
      autodiff/Vec_test.cpp
      autodiff/flat_view.h
      autodiff/Dot.h )

#target_link_libraries(autodiff ${Boost_LIBRARIES})

ADD_EXECUTABLE(perf autodiff/perf.cpp)


#ADD_EXECUTABLE(stan_autodiff stan.cpp c:/dev/github/stan/src/stan/agrad/rev/var_stack.cpp)

add_custom_target(Documents SOURCES "autodiff/Differentiating Containers.md" )
