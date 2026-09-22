QT += widgets serialport charts sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarmpage.cpp \
    batterytestmanager.cpp \
    communicationpage.cpp \
    databasemanager.cpp \
    datapage.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    modbusdevice.cpp \
    modbusrtu.cpp \
    serialportmanager.cpp \
    settingpage.cpp \
    testpage.cpp

HEADERS += \
    alarmpage.h \
    batterydata.h \
    batterytestmanager.h \
    communicationpage.h \
    databasemanager.h \
    datapage.h \
    homepage.h \
    mainwindow.h \
    modbusdevice.h \
    modbusrtu.h \
    serialportmanager.h \
    settingpage.h \
    testpage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    style.qrc

DISTFILES += \
    style.qss
