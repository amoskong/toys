TEMPLATE = app
TARGET += 
DEPENDPATH += .
INCLUDEPATH += .
TRANSLATIONS += zh_CN.ts
QT	+= network
RESOURCES 	+= resource.qrc
#LIBS += -lshell32
RC_FILE += src.rc

# Input
HEADERS += mainWindow.h ipmsg.h subWindow.h serve.h 
SOURCES += main.cpp mainWindow.cpp serve.cpp subWindow.cpp msgManage.cpp
