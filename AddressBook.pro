#-------------------------------------------------
#
# Project created by QtCreator 2020-06-25T20:40:36
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddressBook
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    createnew.cpp \
    addrelative.cpp \
    addfriend.cpp \
    addclassmate.cpp \
    addcolleague.cpp \
    call.cpp \
    email.cpp \
    messdemo.cpp \
    search.cpp \
    birthday.cpp \
    register.cpp \
    login.cpp \
    asr.cpp \
    sendemail/emailaddress.cpp \
    sendemail/mimeattachment.cpp \
    sendemail/mimecontentformatter.cpp \
    sendemail/mimefile.cpp \
    sendemail/mimehtml.cpp \
    sendemail/mimeinlinefile.cpp \
    sendemail/mimemessage.cpp \
    sendemail/mimemultipart.cpp \
    sendemail/mimepart.cpp \
    sendemail/mimetext.cpp \
    sendemail/quotedprintable.cpp \
    sendemail/sendemailthread.cpp \
    sendemail/smtpclient.cpp \
    inputemailpassword.cpp \
    headpath.cpp

HEADERS += \
        mainwindow.h \
    createnew.h \
    addrelative.h \
    addfriend.h \
    addclassmate.h \
    addcolleague.h \
    call.h \
    email.h \
    messdemo.h \
    search.h \
    birthday.h \
    register.h \
    login.h \
    asr.h \
    sendemail/emailaddress.h \
    sendemail/mimeattachment.h \
    sendemail/mimecontentformatter.h \
    sendemail/mimefile.h \
    sendemail/mimehtml.h \
    sendemail/mimeinlinefile.h \
    sendemail/mimemessage.h \
    sendemail/mimemultipart.h \
    sendemail/mimepart.h \
    sendemail/mimetext.h \
    sendemail/quotedprintable.h \
    sendemail/sendemailthread.h \
    sendemail/smtpclient.h \
    sendemail/smtpmime.h \
    inputemailpassword.h \
    headpath.h

FORMS += \
        mainwindow.ui \
    createnew.ui \
    call.ui \
    email.ui \
    messdemo.ui \
    search.ui \
    birthday.ui \
    register.ui \
    login.ui \
    inputemailpassword.ui

RESOURCES += \
    res.qrc

#DEFINES+=QT_NO_DEBUG_OUTPUT

DISTFILES += \
    sendemail/sendemail.pri
include($$PWD/modules/sms/sms.pri)
#include ($$PWD/sendemail/sendemail.pri)
#INCLUDEPATH += $$PWD
#INCLUDEPATH += $$PWD/sendemail
