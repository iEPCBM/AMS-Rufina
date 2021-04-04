QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aesfacade.cpp \
    afterauthstrategy.cpp \
    dialogaddchat.cpp \
    dialogchatslist.cpp \
    dialogcreatepassword.cpp \
    dialogpasswordenter.cpp \
    dialogsettings.cpp \
    dialogtoken.cpp \
    floor.cpp \
    main.cpp \
    mainwindow.cpp \
    messageassembler.cpp \
    settings.cpp \
    showtokenstrategy.cpp \
    third_party/AES.cpp \
    vkApi/vkapi.cpp \
    vkApi/vkchat.cpp \
    vkApi/vkuser.cpp \
    vkApi/vkuserhandler.cpp \
    vkApi/vkchathandler.cpp \
    widgets/chatactionbutton.cpp

HEADERS += \
    aesfacade.h \
    afterauthstrategy.h \
    dialogaddchat.h \
    dialogchatslist.h \
    dialogcreatepassword.h \
    dialogpasswordenter.h \
    dialogsettings.h \
    dialogtoken.h \
    floor.h \
    mainwindow.h \
    messageassembler.h \
    settings.h \
    showtokenstrategy.h \
    third_party/AES.h \
    vkApi/AbstractMethod.h \
    vkApi/vkapi.h \
    vkApi/vkchat.h \
    vkApi/vkuser.h \
    vkApi/vkuserhandler.h \
    vkApi/vkchathandler.h \
    widgets/chatactionbutton.h

FORMS += \
    dialogaddchat.ui \
    dialogchatslist.ui \
    dialogcreatepassword.ui \
    dialogpasswordenter.ui \
    dialogsettings.ui \
    dialogsettings.ui \
    dialogtoken.ui \
    mainwindow.ui

TRANSLATIONS += \
    RUFINA_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = assets/icons/icon.ico
