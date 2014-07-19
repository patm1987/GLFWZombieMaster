TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

INCLUDEPATH += libs/glm \
	libs/gl3w/include

SOURCES += \
    src/main.cpp \
    src/utils/autolist.cpp \
    src/utils/singleton.cpp \
    src/utils/utils.cpp \
    src/scenegraph/graphnode.cpp \
    src/scenegraph/scenegraph.cpp \
    src/entity/camera.cpp \
    src/entity/entity.cpp \
    src/entity/renderable.cpp \
    libs/gl3w/src/gl3w.c \
    src/renderer/shader.cpp \
    src/renderer/renderer.cpp

HEADERS += \
    src/utils/autolist.h \
    src/utils/singleton.h \
    src/utils/utils.h \
    src/scenegraph/graphnode.h \
    src/scenegraph/scenegraph.h \
    src/entity/camera.h \
    src/entity/entity.h \
    src/entity/renderable.h \
	src/stdafx.h \
    libs/gl3w/include/GL/gl3w.h \
    libs/gl3w/include/GL/glcorearb.h \
    src/renderer/shader.h \
    src/renderer/renderer.h

INCLUDEPATH += src

win32: LIBS += -L$$PWD/libs/glfw-3.0.4.bin/lib-msvc110/ -lglfw3 \
	-lgdi32 -luser32 -lkernel32

LIBS += -lopengl32

INCLUDEPATH += $$PWD/libs/glfw-3.0.4.bin/include
DEPENDPATH += $$PWD/libs/glfw-3.0.4.bin/lib-msvc110
