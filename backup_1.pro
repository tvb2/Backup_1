QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Relay.cpp \
    TimeRelayFuncA.cpp \
    TimeRelayFuncB.cpp \
    backupeval.cpp \
    main.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    qcustomplot.cpp \
    sizeStruct.cpp \
    userdata.cpp

HEADERS += \
    Declarations.h \
    Relay.h \
    SizeStruct.h \
    TimeRelayFuncA.h \
    TimeRelayFuncB.h \
    backupeval.h \
    mainwindow.h \
    plotwindow.h \
    qcustomplot.h \
    userdata.h

FORMS += \
    mainwindow.ui \
    plotwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
