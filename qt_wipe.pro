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
    main.cpp \
    qt_butt.cpp \
    qt_frameless.cpp \
    qt_list_butt.cpp \
    qt_manage.cpp \
    sys_info.cpp \
    wid_list_butt.cpp \
    wid_main.cpp \
    wid_sys_browser.cpp \
    wid_sys_info.cpp \
    wid_sys_wipe.cpp \
    wid_tab_list.cpp \
    widget.cpp

HEADERS += \
    files_info.h \
    qt_butt.h \
    qt_frameless.h \
    qt_list_butt.h \
    qt_manage.h \
    sys_info.h \
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
