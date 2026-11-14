QT += widgets core serialbus network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debug/modbusdebug.cpp \
    device/deviceconfig.cpp \
    device/dialog.cpp \
    device/projectconfig.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    debug/modbusdebug.h \
    device/deviceconfig.h \
    device/dialog.h \
    device/projectconfig.h \
    mainwindow.h

FORMS += \
    debug/modbusdebug.ui \
    device/deviceconfig.ui \
    device/dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 构建后自动把初始配置拷到 exe 目录
CONFIG += file_copies
COPIES += configFiles
configFiles.files = $$PWD/resources/project_config.json

# MinGW debug：exe 在 $$OUT_PWD/debug
configFiles.path = $$OUT_PWD/debug


INCLUDEPATH +=
    $$PWD/device/deviceconfig.h
    $$PWD/device/projectconfig.h
    $$PWD/device/dialog.h

RESOURCES += \
    resources/resources.qrc
