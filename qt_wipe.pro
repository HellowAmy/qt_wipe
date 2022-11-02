QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    files_info.cpp \
    lib/wipe/blkdev.c \
    lib/wipe/dir.c \
    lib/wipe/file.c \
    lib/wipe/io.c \
    lib/wipe/lock.c \
    lib/wipe/mainA.c \
    lib/wipe/mt.c \
    lib/wipe/percent.c \
    lib/wipe/prompt.c \
    lib/wipe/rand.c \
    lib/wipe/str.c \
    lib/wipe/text.c \
    lib/wipe/wipe.c \
    main.cpp \
    qt_butt.cpp \
    qt_dialog.cpp \
    qt_frameless.cpp \
    qt_list_butt.cpp \
    qt_manage.cpp \
    qt_move_it.cpp \
    qt_show.cpp \
    qt_wipe.cpp \
    rules/qt_rules.cpp \
    rules/wid_rules.cpp \
    sys_info.cpp \
    sys_section_file.cpp \
    wid_list_butt.cpp \
    wid_main.cpp \
    wid_sys_browser.cpp \
    wid_sys_info.cpp \
    wid_sys_wipe.cpp \
    wid_tab_list.cpp \
    widget.cpp

HEADERS += \
    files_info.h \
    lib/wipe/blkdev.h \
    lib/wipe/config.h \
    lib/wipe/debug.h \
    lib/wipe/dir.h \
    lib/wipe/file.h \
    lib/wipe/header.h \
    lib/wipe/io.h \
    lib/wipe/lock.h \
    lib/wipe/main.h \
    lib/wipe/mt.h \
    lib/wipe/percent.h \
    lib/wipe/prompt.h \
    lib/wipe/rand.h \
    lib/wipe/require.h \
    lib/wipe/std.h \
    lib/wipe/str.h \
    lib/wipe/text.h \
    lib/wipe/version.h \
    lib/wipe/wipe.h \
    lib/wipe/wipeinterface.h \
    qt_butt.h \
    qt_dialog.h \
    qt_frameless.h \
    qt_list_butt.h \
    qt_manage.h \
    qt_move_it.h \
    qt_show.h \
    qt_wipe.h \
    rules/qt_rules.h \
    rules/wid_rules.h \
    sys_info.h \
    sys_section_file.h \
    wid_list_butt.h \
    wid_main.h \
    wid_sys_browser.h \
    wid_sys_info.h \
    wid_sys_wipe.h \
    wid_tab_list.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic/pic.qrc

DISTFILES += \
    lib/wipe/config.h.in
