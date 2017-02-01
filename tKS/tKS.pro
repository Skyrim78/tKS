#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T09:43:46
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tKS
TEMPLATE = app


SOURCES += main.cpp\
        tks.cpp \
    cstreet.cpp \
    street.cpp \
    cstatus.cpp \
    cdiscount.cpp \
    cregion.cpp \
    ccity.cpp \
    cplan.cpp \
    cbase.cpp

HEADERS  += tks.h \
    cstreet.h \
    street.h \
    cstatus.h \
    cdiscount.h \
    cregion.h \
    ccity.h \
    cplan.h \
    cbase.h

FORMS    += tks.ui \
    street.ui
