QT += widgets serialbus network charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartstest.cpp \
    common/modbusmanager.cpp \
    dashboard/clustercard.cpp \
    dashboard/dashboard.cpp \
    debug/modbusdebug.cpp \
    device/deviceconfig.cpp \
    device/dialog.cpp \
    device/projectconfig.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    chartstest.h \
    common/modbusmanager.h \
    common/modbusmap.h \
    dashboard/clustercard.h \
    dashboard/dashboard.h \
    debug/modbusdebug.h \
    device/deviceconfig.h \
    device/dialog.h \
    device/projectconfig.h \
    mainwindow.h

FORMS += \
    chartstest.ui \
    dashboard/clustercard.ui \
    dashboard/dashboard.ui \
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


INCLUDEPATH += \
    $$PWD/device \
    $$PWD/common \
    $$PWD/debug \
    $$PWD/dashboard

RESOURCES += \
    resources/resources.qrc
