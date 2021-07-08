QT -= gui

TEMPLATE = lib
DEFINES += BASERENDER_LIBRARY

CONFIG += c++11
QMAKE_CXXFLAGS += -fpermissive
QMAKE_CXXFLAGS += -Wno-narrowing

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QMAKE_CC = g++
QMAKE_CXX = g++

DESTDIR = ./../debug/bin/
# LIBS += -LSDL2 -lpsapi
INCLUDEPATH += ../code/SDL2/include

HEADERS += \
	../code/qcommon/q_shared.h \
	../code/qcommon/qcommon.h \
	../code/renderercommon/iqm.h \
	../code/renderercommon/qgl.h \
	../code/renderercommon/tr_common.h \
	../code/renderercommon/tr_public.h \
	../code/renderercommon/tr_types.h \
	../code/renderergl1/tr_local.h

SOURCES += \
	../code/qcommon/q_math.cpp \
	../code/qcommon/q_shared.cpp \
	../code/renderergl1/tr_altivec.cpp \
	../code/renderergl1/tr_animation.cpp \
	../code/renderergl1/tr_backend.cpp \
	../code/renderergl1/tr_bsp.cpp \
	../code/renderergl1/tr_cmds.cpp \
	../code/renderergl1/tr_curve.cpp \
	../code/renderergl1/tr_flares.cpp \
	../code/renderergl1/tr_image.cpp \
	../code/renderergl1/tr_init.cpp \
	../code/renderergl1/tr_light.cpp \
	../code/renderergl1/tr_main.cpp \
	../code/renderergl1/tr_marks.cpp \
	../code/renderergl1/tr_mesh.cpp \
	../code/renderergl1/tr_model.cpp \
	../code/renderergl1/tr_model_iqm.cpp \
	../code/renderergl1/tr_scene.cpp \
	../code/renderergl1/tr_shade.cpp \
	../code/renderergl1/tr_shade_calc.cpp \
	../code/renderergl1/tr_shader.cpp \
	../code/renderergl1/tr_shadows.cpp \
	../code/renderergl1/tr_sky.cpp \
	../code/renderergl1/tr_subs.cpp \
	../code/renderergl1/tr_surface.cpp \
	../code/renderergl1/tr_world.cpp
