#-------------------------------------------------
#
# Project created by QtCreator 2013-05-05T13:15:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 8_puzzle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eightpuzzleinstance.cpp \
    eightpuzzlesolutioner.cpp

HEADERS  += mainwindow.h \
    eightpuzzleinstance.h \
    eightpuzzlesolutioner.h

FORMS    += mainwindow.ui
