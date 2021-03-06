#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T03:20:40
#
#-------------------------------------------------

include(vendor/vendor.pri)

QT       += core gui sql\
        winextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomatoDown
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    testpromote.cpp \
    lineedit.cpp \
    db.cpp \
    datetime.cpp \
    init.cpp \
    basemodel.cpp \
    usermodel.cpp \
    config.cpp \
    settingmodel.cpp \
    tools.cpp


HEADERS  += mainwindow.h \
    testpromote.h \
    lineedit.h \
    db.h \
    datetime.h \
    init.h \
    basemodel.h \
    usermodel.h \
    config.h \
    settingmodel.h \
    basedata.h \
    tools.h


FORMS    += mainwindow.ui \
    testpromote.ui

TRANSLATIONS += en_us.ts \
                zh_cn.ts \
                zh_tw.ts



RC_ICONS=TomatoDown.ico

RESOURCES += \
    resource.qrc

