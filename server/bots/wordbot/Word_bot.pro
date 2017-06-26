TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += no_keywords
SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++11


INCLUDEPATH += /usr/include/boost

LIBS += -L/usr/include/boost -lboost_system
LIBS += -L/usr/include/boost  -lboost_thread
LIBS += -L/usr/include/boost  -lboost_timer
LIBS += -L/usr/include/boost  -levent -lssl -lrt -lcrypto -lpthread

INCLUDEPATH += /usr/include/python3.4m
LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lpython3.4m
LIBS += -lz -lexpat -ldl -lutil
