QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app
VERSION = 1.0.0.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogs/dialogedittoken.cpp \
    aesfacade.cpp \
    afterauthstrategy.cpp \
    dialogs/dialogaddchat.cpp \
    dialogs/dialogchatslist.cpp \
    dialogs/dialogcreatepassword.cpp \
    dialogs/dialogpasswordenter.cpp \
    dialogs/dialogchatconfirmation.cpp \
    dialogs/dialogchatsettings.cpp \
    dialogs/dialoglicenseview.cpp \
    dialogs/dialogsettings.cpp \
    dialogs/dialogtoken.cpp \
    floor.cpp \
    main.cpp \
    mainwindow.cpp \
    messageassembler.cpp \
    settings.cpp \
    showtokenstrategy.cpp \
    third_party/AES.cpp \
    vkApi/vkapi.cpp \
    vkApi/vkchat.cpp \
    vkApi/vkerror.cpp \
    vkApi/vkmessagedelivery.cpp \
    vkApi/vkuser.cpp \
    vkApi/vkuserhandler.cpp \
    vkApi/vkchathandler.cpp \
    widgets/chatactionbutton.cpp

HEADERS += \
    AppInfo.h \
    Dialogs/dialogedittoken.h \
    aesfacade.h \
    afterauthstrategy.h \
    dialogs/dialogaddchat.h \
    dialogs/dialogchatslist.h \
    dialogs/dialogcreatepassword.h \
    dialogs/dialogpasswordenter.h \
    dialogs/dialogchatconfirmation.h \
    dialogs/dialogchatsettings.h \
    dialogs/dialoglicenseview.h \
    dialogs/dialogsettings.h \
    dialogs/dialogtoken.h \
    floor.h \
    mainwindow.h \
    messageassembler.h \
    settings.h \
    showtokenstrategy.h \
    third_party/AES.h \
    third_party/CompileTime/CompileTime.h \
    vkApi/AbstractMethod.h \
    vkApi/vkapi.h \
    vkApi/vkchat.h \
    vkApi/vkerror.h \
    vkApi/vkmessagedelivery.h \
    vkApi/vkuser.h \
    vkApi/vkuserhandler.h \
    vkApi/vkchathandler.h \
    widgets/chatactionbutton.h \
    rassert.h

FORMS += \
    dialogs/dialogedittoken.ui \
    dialogs/dialogaddchat.ui \
    dialogs/dialogchatslist.ui \
    dialogs/dialogcreatepassword.ui \
    dialogs/dialogpasswordenter.ui \
    dialogs/dialogchatconfirmation.ui \
    dialogs/dialogchatsettings.ui \
    dialogs/dialoglicenseview.ui \
    dialogs/dialogsettings.ui \
    dialogs/dialogsettings.ui \
    dialogs/dialogtoken.ui \
    mainwindow.ui

TRANSLATIONS += \
    RUFINA_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32 {
    QMAKE_TARGET_COMPANY = "Rishat D. Kagirov"
    QMAKE_TARGET_PRODUCT = "AMS Rufina"
    QMAKE_TARGET_DESCRIPTION = "System of automated sending messages to conversations of VKontakte"
    QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2021 Rishat D. Kagirov"
    RC_ICONS = assets/icons/icon.ico
    RC_LANG = 0x0419
    RC_CODEPAGE = 1200
}
