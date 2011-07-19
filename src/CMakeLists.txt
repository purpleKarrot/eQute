
# if GLX is NOT defined, Equalizer defines some types that conflict with Qt
#add_definitions(-DGLX)

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

message(STATUS "${QT_LIBRARIES}")
