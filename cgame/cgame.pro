QT -= gui

TEMPLATE = lib
DEFINES += CGAME_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = ./../debug/baseq3/

HEADERS += \
    ../code/cgame/cg_local.h \
    ../code/cgame/cg_public.h \
    ../code/game/bg_public.h \
    ../code/qcommon/q_shared.h

SOURCES += \
    ../code/cgame/cg_consolecmds.c \
    ../code/cgame/cg_draw.c \
    ../code/cgame/cg_drawtools.c \
    ../code/cgame/cg_effects.c \
    ../code/cgame/cg_ents.c \
    ../code/cgame/cg_event.c \
    ../code/cgame/cg_info.c \
    ../code/cgame/cg_localents.c \
    ../code/cgame/cg_main.c \
    ../code/cgame/cg_marks.c \
    ../code/cgame/cg_particles.c \
    ../code/cgame/cg_players.c \
    ../code/cgame/cg_playerstate.c \
    ../code/cgame/cg_predict.c \
    ../code/cgame/cg_scoreboard.c \
    ../code/cgame/cg_servercmds.c \
    ../code/cgame/cg_snapshot.c \
    ../code/cgame/cg_syscalls.c \
    ../code/cgame/cg_view.c \
    ../code/cgame/cg_weapons.c \
    ../code/game/bg_misc.c \
    ../code/game/bg_pmove.c \
    ../code/game/bg_slidemove.c \
    ../code/qcommon/q_math.c \
    ../code/qcommon/q_shared.c
