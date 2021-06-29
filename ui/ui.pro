QT -= gui

TEMPLATE = lib
DEFINES += UI_LIBRARY

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
    ../code/game/bg_public.h \
    ../code/q3_ui/ui_local.h \
    ../code/qcommon/q_shared.h \
    ../code/ui/ui_public.h \
    ../code/ui/ui_shared.h

SOURCES += \
    ../code/game/bg_misc.c \
    ../code/q3_ui/ui_addbots.c \
    ../code/q3_ui/ui_atoms.c \
    ../code/q3_ui/ui_cdkey.c \
    ../code/q3_ui/ui_cinematics.c \
    ../code/q3_ui/ui_confirm.c \
    ../code/q3_ui/ui_connect.c \
    ../code/q3_ui/ui_controls2.c \
    ../code/q3_ui/ui_credits.c \
    ../code/q3_ui/ui_demo2.c \
    ../code/q3_ui/ui_display.c \
    ../code/q3_ui/ui_gameinfo.c \
    ../code/q3_ui/ui_ingame.c \
    ../code/q3_ui/ui_loadconfig.c \
    ../code/q3_ui/ui_main.c \
    ../code/q3_ui/ui_menu.c \
    ../code/q3_ui/ui_mfield.c \
    ../code/q3_ui/ui_mods.c \
    ../code/q3_ui/ui_network.c \
    ../code/q3_ui/ui_options.c \
    ../code/q3_ui/ui_playermodel.c \
    ../code/q3_ui/ui_players.c \
    ../code/q3_ui/ui_playersettings.c \
    ../code/q3_ui/ui_preferences.c \
    ../code/q3_ui/ui_qmenu.c \
    ../code/q3_ui/ui_removebots.c \
    ../code/q3_ui/ui_saveconfig.c \
    ../code/q3_ui/ui_serverinfo.c \
    ../code/q3_ui/ui_servers2.c \
    ../code/q3_ui/ui_setup.c \
    ../code/q3_ui/ui_sound.c \
    ../code/q3_ui/ui_sparena.c \
    ../code/q3_ui/ui_specifyserver.c \
    ../code/q3_ui/ui_splevel.c \
    ../code/q3_ui/ui_sppostgame.c \
    ../code/q3_ui/ui_spreset.c \
    ../code/q3_ui/ui_spskill.c \
    ../code/q3_ui/ui_startserver.c \
    ../code/q3_ui/ui_team.c \
    ../code/q3_ui/ui_teamorders.c \
    ../code/q3_ui/ui_video.c \
    ../code/qcommon/q_math.c \
    ../code/qcommon/q_shared.c \
    ../code/ui/ui_syscalls.c
