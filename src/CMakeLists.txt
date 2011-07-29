
qt4_wrap_cpp(EQUTE_MOC
  application.hpp
  )

add_library(eQute SHARED
  ${EQUTE_MOC}
  application.cpp
  factory.cpp
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
boost_link_libraries(eQute
  thread
  )
