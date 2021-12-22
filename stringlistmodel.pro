QT += qml quick
QT += charts
SOURCES += \
    JsonOperations/biometricdb.cpp \
    JsonOperations/biometricuser.cpp \
    biometrickeyboardmodel.cpp \
    main.cpp \
    passwordcontroller.cpp
RESOURCES += stringlistmodel.qrc

HEADERS += \
    JsonOperations/biometricdb.h \
    JsonOperations/biometricuser.h \
    biometrickeyboardmodel.h \
    passwordcontroller.h
