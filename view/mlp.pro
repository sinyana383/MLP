QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/Graph/graph_realisation.cpp \ 
    ../model/Graph/layer.cpp \
    ../model/Graph/neuron.cpp \
    ../model/MLP.cpp \
    ../model/Matrix/Matrix.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ../control/Control.cpp

HEADERS += \
    ../model/Graph/graph.h \
    ../model/Graph/layer.h \
    ../model/Graph/neuron.h \
    ../model/MLP.hpp \
    ../model/Matrix/Matrix.hpp \
    form.h \
    mainwindow.h \
    qcustomplot.h \
    ../control/Control.hpp

FORMS += \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    emnist-letters-test.csv \
    emnist-letters-train.csv \
    weights.w
