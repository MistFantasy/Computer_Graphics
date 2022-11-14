QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    color_model_dialog.cpp \
    complexnumber.cpp \
    fractal_data.cpp \
    fractal_dialog.cpp \
    fractal_dialog_window.cpp \
    main.cpp \
    mainwindow.cpp \
    renderthread.cpp \
    triangle.cpp \
    triangle_data.cpp \
    triangle_dialog.cpp \
    triangle_dialog_window.cpp

HEADERS += \
    color_model_dialog.h \
    complexnumber.h \
    fractal_data.h \
    fractal_dialog.h \
    fractal_dialog_window.h \
    mainwindow.h \
    renderthread.h \
    triangle.h \
    triangle_data.h \
    triangle_dialog.h \
    triangle_dialog_window.h

FORMS += \
    color_model_dialog.ui \
    fractal_dialog.ui \
    fractal_dialog_window.ui \
    mainwindow.ui \
    triangle_dialog.ui \
    triangle_dialog_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
