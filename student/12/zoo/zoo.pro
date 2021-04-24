TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    animal.cpp \
    bird.cpp \
    owl.cpp \
    giraffe.cpp \
    mammal.cpp \
    cockatoo.cpp

HEADERS += \
    animal.hh \
    bird.hh \
    owl.hh \
    giraffe.hh \
    mammal.hh \
    cockatoo.hh
