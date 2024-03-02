
DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

HEADERS += \
  colors.h \
  basic_object3d.h \
  cone.h \
  cylinder.h \
  object3d.h \
  axis.h \
  object3dr.h \
  ply.h \
  sphere.h \
  tetrahedron.h \
  cube.h \
  glwidget.h \
  window.h \
  file_ply_stl.h

SOURCES += \
  basic_object3d.cc \
  cone.cc \
  cylinder.cc \
  object3d.cc \
  axis.cc \
  object3dr.cc \
  ply.cc \
  sphere.cc \
  tetrahedron.cc \
  cube.cc \
  main.cc \
  glwidget.cc \
  window.cc \
  file_ply_stl.cc

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
