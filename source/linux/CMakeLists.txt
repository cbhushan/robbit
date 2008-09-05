
cmake_minimum_required(VERSION 2.6)

ADD_DEFINITIONS( -O3 -ggdb )

ADD_EXECUTABLE(
  Robbit
  Robbit.cpp
  )

TARGET_LINK_LIBRARIES(
  Robbit

  fltk fltk_gl 
  GL GLU
  glut 
  png
  )
