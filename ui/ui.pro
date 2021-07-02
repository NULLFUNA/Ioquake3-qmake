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
    ../code/game/bg_misc.cpp \
    ../code/q3_ui/ui_addbots.cpp \
    ../code/q3_ui/ui_atoms.cpp \
    ../code/q3_ui/ui_cdkey.cpp \
    ../code/q3_ui/ui_cinematics.cpp \
    ../code/q3_ui/ui_confirm.cpp \
    ../code/q3_ui/ui_connect.cpp \
    ../code/q3_ui/ui_controls2.cpp \
    ../code/q3_ui/ui_credits.cpp \
    ../code/q3_ui/ui_demo2.cpp \
    ../code/q3_ui/ui_display.cpp \
    ../code/q3_ui/ui_gameinfo.cpp \
    ../code/q3_ui/ui_ingame.cpp \
    ../code/q3_ui/ui_loadconfig.cpp \
    ../code/q3_ui/ui_main.cpp \
    ../code/q3_ui/ui_menu.cpp \
    ../code/q3_ui/ui_mfield.cpp \
    ../code/q3_ui/ui_mods.cpp \
    ../code/q3_ui/ui_network.cpp \
    ../code/q3_ui/ui_options.cpp \
    ../code/q3_ui/ui_playermodel.cpp \
    ../code/q3_ui/ui_players.cpp \
    ../code/q3_ui/ui_playersettings.cpp \
    ../code/q3_ui/ui_preferences.cpp \
    ../code/q3_ui/ui_qmenu.cpp \
    ../code/q3_ui/ui_removebots.cpp \
    ../code/q3_ui/ui_saveconfig.cpp \
    ../code/q3_ui/ui_serverinfo.cpp \
    ../code/q3_ui/ui_servers2.cpp \
    ../code/q3_ui/ui_setup.cpp \
    ../code/q3_ui/ui_sound.cpp \
    ../code/q3_ui/ui_sparena.cpp \
    ../code/q3_ui/ui_specifyserver.cpp \
    ../code/q3_ui/ui_splevel.cpp \
    ../code/q3_ui/ui_sppostgame.cpp \
    ../code/q3_ui/ui_spreset.cpp \
    ../code/q3_ui/ui_spskill.cpp \
    ../code/q3_ui/ui_startserver.cpp \
    ../code/q3_ui/ui_team.cpp \
    ../code/q3_ui/ui_teamorders.cpp \
    ../code/q3_ui/ui_video.cpp \
    ../code/qcommon/q_math.cpp \
    ../code/qcommon/q_shared.cpp \
    ../code/ui/ui_syscalls.cpp

