QT       += sql \
            multimedia \
            multimediawidgets \
            network\
            printsupport\
            serialport


QT += core charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
                                    printsupport

#CONFIG += console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Account.cpp \
    arduino.cpp \
    chat.cpp \
    connection.cpp \
    employee.cpp \
    employeemanagement.cpp \
    main.cpp \
    login.cpp \
    sign_up.cpp

HEADERS += \
    Account.h \
    arduino.h \
    chat.h \
    connection.h \
    employee.h \
    employeemanagement.h \
    login.h \
    sign_up.h

FORMS += \
    chat.ui \
    employeemanagement.ui \
    login.ui \
    reset.ui \
    sign_up.ui

QMAKE_CXXFLAGS += -std=gnu++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
