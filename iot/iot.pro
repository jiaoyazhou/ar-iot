DESTDIR = ../nlinux
TEMPLATE = app
TARGET = iot
QT += Qt3Support \
    core \
    gui \
    sql \
    xml \
    network
INCLUDEPATH += ../nlinux/include
LIBS += -L../nlinux/lib \
    -lycapi \
    -lQZXing \
    -lpng \
    -lqrencode \
    -lsqlite3
HEADERS += userdef.h \
    database/Database.h \
    ui/expertinfo_operation_window.h \
    ui/expertinfo_window.h \
    comcontrol/protocol.h \
    comcontrol/serial_control.h \
    ui/mctrtabchart1.h \
    ui/mainwindow.h \
    comcontrol/comcontrol.h \
    qrcode/qrcode.h \
    ui/video_show.h \
    video/videodevice.h \
    widget/qpushbutton_new.h \
    ui/iot.h \
    ui/setting.h \
    ui/login.h \
    ui/maincontrol.h \
    ui/statusbar.h \
    global.h \
    systat/get_cpu.h \
    systat/sysstat.h
SOURCES += database/Database.cpp \
    ui/expertinfo_operation_window.cpp \
    ui/expertinfo_window.cpp \
    comcontrol/protocol.c \
    comcontrol/serial_control.c \
    ui/mctrtabchart1.cpp \
    ui/mainwindow.cpp \
    comcontrol/comcontrol.cpp \
    qrcode/qrcode.cpp \
    ui/video_show.cpp \
    video/videodevice.cpp \
    widget/qpushbutton_new.cpp \
    ui/iot.cpp \
    ui/setting.cpp \
    ui/login.cpp \
    ui/maincontrol.cpp \
    ui/statusbar.cpp \
    global.cpp \
    systat/get_cpu.c \
    systat/sysstat.c \
    main.cpp
FORMS += ui/mainwindow.ui \
    ui/video_show.ui \
    ui/login.ui \
    ui/maincontrol.ui \
    ui/setting.ui \
    ui/statusbar.ui
RESOURCES += png.qrc
