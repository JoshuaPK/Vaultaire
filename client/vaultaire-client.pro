#-------------------------------------------------
# Vaultaire Client project file
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vaultaire-client
TEMPLATE = app

SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/MainMenu.cpp \
           src/ScanForm.cpp \
           src/ImageViewer.cpp \
           src/Scanner.cpp \
           src/Library.cpp \
           src/LibrarySettings.cpp \
           src/ScannerSettings.cpp \
           src/OcrSettings.cpp \
           src/SettingsDialog.cpp

HEADERS  += include/MainWindow.h \
            include/MainMenu.h \
            include/ScanForm.h \
            include/ImageViewer.h \
            include/Scanner.h \
            include/Library.h \
            include/LibrarySettings.h \
            include/ScannerSettings.h \
            include/OcrSettings.h \
            include/SettingsDialog.h

INCLUDEPATH += ./include

DESTDIR = bin
OBJECTS_DIR = build/objs
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

