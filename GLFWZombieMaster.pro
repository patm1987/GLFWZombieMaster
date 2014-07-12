TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += libs/glm

SOURCES += \
    src/main.cpp \
    src/renderer.cpp \
    src/utils/autolist.cpp \
    src/utils/singleton.cpp \
    src/utils/utils.cpp \
    src/scenegraph/graphnode.cpp \
    src/scenegraph/scenegraph.cpp \
    src/entity/camera.cpp \
    src/entity/entity.cpp \
    src/entity/renderable.cpp

HEADERS += \
    src/renderer.h \
    src/utils/autolist.h \
    src/utils/singleton.h \
    src/utils/utils.h \
    src/scenegraph/graphnode.h \
    src/scenegraph/scenegraph.h \
    src/entity/camera.h \
    src/entity/entity.h \
    src/entity/renderable.h

INCLUDEPATH += src

win32: LIBS += -L$$PWD/libs/glfw-3.0.4.bin/lib-msvc110/ -lglfw3 \
	-lgdi32 -luser32 -lkernel32

LIBS += -lopengl32

INCLUDEPATH += $$PWD/libs/glfw-3.0.4.bin/include
DEPENDPATH += $$PWD/libs/glfw-3.0.4.bin/lib-msvc110
