QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    writepad.cpp

HEADERS += \
    writepad.h

FORMS += \
    writepad.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/copy.png \
    images/create.png \
    images/cut.png \
    images/font.png \
    images/info.png \
    images/new.png \
    images/open.png \
    images/paste.png \
    images/print.png \
    images/save.png \
    images/underline.png

RESOURCES += \
    Resources.qrc
