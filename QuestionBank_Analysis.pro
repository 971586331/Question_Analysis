
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuestionBank_Analysis
TEMPLATE = app

HEADERS += \
    mainwindow.h \
    main.h \
    qtsql_operation.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    qtsql_operation.cpp

FORMS += \
    mainwindow.ui

RESOURCES +=

RC_FILE+=app.rc

OTHER_FILES += \
    Generate_tables_24px_557045_easyicon.net.ico \
    app.rc
