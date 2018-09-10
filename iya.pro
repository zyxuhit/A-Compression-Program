#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T14:34:39
#
#-------------------------------------------------

QT       += core gui

TARGET = iya
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    iya.cpp \
    passdialog.cpp

HEADERS  += widget.h \
    Utility.h \
    LZW.h \
    Lk_stack.h \
    Huffman.h \
    passdialog.h

FORMS    += widget.ui \
    passdialog.ui
