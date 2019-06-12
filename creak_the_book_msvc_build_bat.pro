QT -= gui

CONFIG += c++17
CONFIG -= app_bundle

SOURCES += main.cpp

DEFINES *= CURRENT_DIR=\\\"$$PWD\\\"
DEFINES *= CURRENT_QT_BIN_DIR=\\\"$$[QT_INSTALL_BINS]\\\"




















