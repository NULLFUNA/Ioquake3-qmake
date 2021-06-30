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
    ../code/game/ai_chat.c \
    ../code/game/ai_cmd.c \
    ../code/game/ai_dmnet.c \
    ../code/game/ai_dmq3.c \
    ../code/game/ai_main.c \
    ../code/game/ai_team.c \
    ../code/game/ai_vcmd.c \
    ../code/game/bg_misc.c \
    ../code/game/bg_pmove.c \
    ../code/game/bg_slidemove.c \
    ../code/game/g_active.c \
    ../code/game/g_arenas.c \
    ../code/game/g_bot.c \
    ../code/game/g_client.c \
    ../code/game/g_cmds.c \
    ../code/game/g_combat.c \
    ../code/game/g_items.c \
    ../code/game/g_main.c \
    ../code/game/g_mem.c \
    ../code/game/g_misc.c \
    ../code/game/g_missile.c \
    ../code/game/g_mover.c \
    ../code/game/g_session.c \
    ../code/game/g_spawn.c \
    ../code/game/g_svcmds.c \
    ../code/game/g_syscalls.c \
    ../code/game/g_target.c \
    ../code/game/g_team.c \
    ../code/game/g_trigger.c \
    ../code/game/g_utils.c \
    ../code/game/g_weapon.c \
    ../code/qcommon/q_math.c \
    ../code/qcommon/q_shared.c
