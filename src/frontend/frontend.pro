QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/Calculate.cc \
    ../backend/Credit.cc \
    ../backend/RPNConverter.cc \
    credit_window.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../Controller/CalcController.h \
    ../Controller/CreditController.h \
    ../backend/Calculate.h \
    ../backend/Credit.h \
    ../backend/RPNConverter.h \
    credit_window.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit_window.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
