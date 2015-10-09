TEMPLATE	= lib
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows

# CONFIG    -= debug  # RELEASE is active
CONFIG    -= release  # DEBUG is active

CONFIG    += staticlib

INCLUDEPATH = ./Header

HEADERS		+=  ./Header/sstRec02Lib.h
HEADERS		+= sstRec02LibInt.h

SOURCES		+=  sstRec02.cpp \
    sstRec03CargoMem.cpp \
    sstRec02TestIntern.cpp \
    sstRec02TestRec.cpp
    #sstRec02Cargo.cpp
SOURCES		+=  sstRec02CargoKey.cpp
SOURCES		+=  sstRec02CargoKeyInt.cpp
SOURCES		+=  sstRec02Int.cpp
SOURCES		+=  sstRec02Vector.cpp

OTHER_FILES += README.md

debug{
  TARGET		= sst_rec02_lib_d
}
release{
  TARGET		= sst_rec02_lib_r
}

DESTDIR     = ../libs

