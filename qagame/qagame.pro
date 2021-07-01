QT -= gui

TEMPLATE = lib
DEFINES += QAGAME_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

QMAKE_CC = g++
QMAKE_CXX = g++

DESTDIR = ./../debug/baseq3/

HEADERS += \
    ../code/game/ai_chat.h \
    ../code/game/ai_cmd.h \
    ../code/game/ai_dmnet.h \
    ../code/game/ai_dmq3.h \
    ../code/game/ai_main.h \
    ../code/game/ai_team.h \
    ../code/game/ai_vcmd.h \
    ../code/game/bg_local.h \
    ../code/game/bg_public.h \
    ../code/game/chars.h \
    ../code/game/g_local.h \
    ../code/game/g_public.h \
    ../code/game/g_team.h \
    ../code/game/inv.h \
    ../code/game/match.h \
    ../code/game/syn.h \
    ../code/qcommon/q_shared.h

SOURCES += \
    ../code/game/g_main.cpp \
    ../code/qcommon/q_math.c \
    ../code/qcommon/q_shared.c \
    ../code/game/ai_chat.cpp \
    ../code/game/ai_cmd.cpp \
    ../code/game/ai_dmnet.cpp \
    ../code/game/ai_dmq3.cpp \
    ../code/game/ai_main.cpp \
    ../code/game/ai_team.cpp \
    ../code/game/ai_vcmd.cpp \
    ../code/game/bg_misc.cpp \
    ../code/game/bg_pmove.cpp \
    ../code/game/bg_slidemove.cpp \
    ../code/game/g_active.cpp \
    ../code/game/g_arenas.cpp \
    ../code/game/g_bot.cpp \
    ../code/game/g_client.cpp \
    ../code/game/g_cmds.cpp \
    ../code/game/g_combat.cpp \
    ../code/game/g_items.cpp \
    ../code/game/g_mem.cpp \
    ../code/game/g_misc.cpp \
    ../code/game/g_missile.cpp \
    ../code/game/g_mover.cpp \
    ../code/game/g_session.cpp \
    ../code/game/g_spawn.cpp \
    ../code/game/g_svcmds.cpp \
    ../code/game/g_syscalls.cpp \
    ../code/game/g_target.cpp \
    ../code/game/g_team.cpp \
    ../code/game/g_trigger.cpp \
    ../code/game/g_utils.cpp \
    ../code/game/g_weapon.cpp
