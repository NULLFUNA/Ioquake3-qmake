QT -= gui
QT += core

TEMPLATE = lib
DEFINES += CGAME_LIBRARY

CONFIG += c++11
QMAKE_CXXFLAGS += -fpermissive

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QMAKE_CC = g++
QMAKE_CXX = g++

DESTDIR = ./../debug/bin/

HEADERS += \
    ../code/cgame/cg_local.h \
    ../code/cgame/cg_public.h \
    ../code/cgame/wui.h \
    ../code/game/bg_public.h \
    ../code/qcommon/q_shared.h \
    ../code/qcommon/shared.h

SOURCES += \
    ../code/cgame/cg_consolecmds.cpp \
    ../code/cgame/cg_draw.cpp \
    ../code/cgame/cg_drawtools.cpp \
    ../code/cgame/cg_effects.cpp \
    ../code/cgame/cg_ents.cpp \
    ../code/cgame/cg_event.cpp \
    ../code/cgame/cg_info.cpp \
    ../code/cgame/cg_localents.cpp \
    ../code/cgame/cg_main.cpp \
    ../code/cgame/cg_marks.cpp \
    ../code/cgame/cg_particles.cpp \
    ../code/cgame/cg_players.cpp \
    ../code/cgame/cg_playerstate.cpp \
    ../code/cgame/cg_predict.cpp \
    ../code/cgame/cg_scoreboard.cpp \
    ../code/cgame/cg_servercmds.cpp \
    ../code/cgame/cg_snapshot.cpp \
    ../code/cgame/cg_syscalls.cpp \
    ../code/cgame/cg_view.cpp \
    ../code/cgame/cg_weapons.cpp \
    ../code/cgame/wui.cpp \
    ../code/cgame/wui_killhistory.cpp \
    ../code/cgame/wui_status.cpp \
    ../code/cgame/wui_weaponselect.cpp \
    ../code/game/bg_misc.cpp \
    ../code/game/bg_pmove.cpp \
    ../code/game/bg_slidemove.cpp \
    ../code/qcommon/q_math.c \
    ../code/qcommon/q_shared.c \
    ../code/cgame/wui_itempickup.cpp

