
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ../src
  )

qt4_wrap_ui(EQT_UI
  mainwindow.ui
  )

add_executable(eQExample
  ${EQT_UI}
  main.cpp
  application.cpp
  applicationThread.cpp
  channel.cpp
  contextCreator.cpp
  mainwindow.cpp
  window.cpp
  )

target_link_libraries(eQExample
  eQute
  ${QT_LIBRARIES}
  ${EQUALIZER_LIBRARIES}
  )
