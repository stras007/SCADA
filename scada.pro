QT += widgets core serialbus network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debug/modbusdebug.cpp \
    device/deviceconfig.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    debug/modbusdebug.h \
    device/deviceconfig.h \
    mainwindow.h

FORMS += \
    debug/modbusdebug.ui \
    device/deviceconfig.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
