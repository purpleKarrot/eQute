##
# Copyright (c) 2011 Daniel Pfeifer, All rights reserved.
#
# This file is freely distributable without licensing fees and
# is provided without guarantee or warrantee expressed or implied.
# This file is -not- in the public domain.
##

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
project(eQute)

find_package(Boost "1.47" REQUIRED system thread NO_MODULE)
include(${Boost_USE_FILE})

find_package(Equalizer "1.1" REQUIRED NO_MODULE)
#include(${Equalizer_USE_FILE})

set(QT_USE_QTOPENGL ON)
find_package(Qt "4.7" REQUIRED QtCore QtGui QtOpenGL)
include(${QT_USE_FILE})

include_directories(
  include
  )

add_subdirectory(example)
add_subdirectory(src)
