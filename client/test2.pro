QT       += core gui
QT       += network
LIBS += -lWs2_32
QT       += widgets
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
    chattable.cpp \
    file.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    sign_up.cpp \
    controlwidget.cpp \
    myrect.cpp \
    screen.cpp \
    qslabel.cpp

HEADERS += \
    chattable.h \
    file.h \
    global.h \
    mainwindow.h \
    sign_up.h \
    controlwidget.h \
    myrect.h \
    screen.h \
    qslabel.h

FORMS += \
    chattable.ui \
    controlwidget.ui \
    mainwindow.ui \
    sign_up.ui \

    controlwidget.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    image/control_01.jpg \
    image/control_02.jpg \
    image/control_03.jpg \
    image/control_04.jpg \
    image/control_05.jpg \
    image/control_06.jpg \
    image/control_07.jpg \
    image/control_08.jpg \
    image/control_09.jpg \
    image/control_10.jpg \
    image/control_11.jpg \
    image/control_12.jpg \
    image/control_13.jpg \
    ../../Pictures/screen/screenshot.png

TRANSLATIONS += \
    test2_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
