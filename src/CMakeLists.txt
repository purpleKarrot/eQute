
add_library(eQute SHARED
  eqShutdownEvent.cpp
  qtEventHandler.cpp
  qtGLContextCreator.cpp
  qtGLContextRequestEvent.cpp
  qtGLWidget.cpp
  qtMainWindow.cpp
  qtWindow.cpp
  )

target_link_libraries(eQute
  ${EQUALIZER_LIBRARIES}
  ${QT_LIBRARIES}
  )
