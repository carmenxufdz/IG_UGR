
DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

HEADERS += \
  colors.h \
  basic_object3d.h \
  object3d.h \
  axis.h \
  tetrahedron.h \
  cube.h \
  glwidget.h \
  window.h

SOURCES += \
  basic_object3d.cc \
  object3d.cc \
  axis.cc \
  tetrahedron.cc \
  cube.cc \
  main.cc \
  glwidget.cc \
  window.cc

#DEFINES+=LINUX
DEFINES+=WINDOWS

!linux{
INCLUDEPATH += C:\Users\carme\OneDrive\Documentos\Universidad\3º Ing. Inf\PRIMER CUATRI\Informática Gráfica\Prácticas\

LIBS += -lopengl32


CONFIG += c++14
QT += openglwidgets
}

linux{
LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++14
QT += widgets opengl openglwidgets
}
