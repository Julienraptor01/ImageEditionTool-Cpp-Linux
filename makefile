# OS specific setup
ID=$(shell . /etc/os-release ; echo $$ID)
ifeq "$(ID)" "debian"
OS=debian
else ifeq "$(ID)" "fedora"
OS=fedora
else
ID_LIKE=$(shell . /etc/os-release ; echo $$ID_LIKE)
ifeq "$(ID_LIKE)" "debian"
OS=debian
else ifeq "$(ID_LIKE)" "fedora"
OS=fedora
else
endif
endif
ifeq "$(OS)" "debian"
QT5_HEADERS=/usr/include/x86_64-linux-gnu/qt5
SHARED_OBJECTS=/usr/lib/x86_64-linux-gnu
else ifeq "$(OS)" "fedora"
QT5_HEADERS=/usr/include/qt5
SHARED_OBJECTS=/usr/lib64
else ifndef OS
$(error OS not supported)
endif
### paths
# sources sub directories
MAIN=/main
LIB=/lib
TEST=/test
MYQT=/MyQT
# sources
SRC=./src
MAIN_SRC=$(SRC)$(MAIN)
TEST_SRC=$(SRC)$(TEST)
LIB_SRC=$(SRC)$(LIB)
MYQT_LIB_SRC=$(LIB_SRC)$(MYQT)
# build
BUILD=./build
# build -> objs
OBJ=$(BUILD)/obj
MAIN_OBJ=$(OBJ)$(MAIN)
TEST_OBJ=$(OBJ)$(TEST)
LIB_OBJ=$(OBJ)$(LIB)
MYQT_LIB_OBJ=$(LIB_OBJ)$(MYQT)
# build -> bins
BIN=$(BUILD)/bin
MAIN_BIN=$(BIN)$(MAIN)
TEST_BIN=$(BIN)$(TEST)
LIB_BIN=$(BIN)$(LIB)
MYQT_LIB_BIN=$(LIB_BIN)$(MYQT)
### commands
# compile arguments
SRC_COMPILE_ARGS=-I $(MAIN_SRC) -Wall# -Xlinker --verbose
SRC_COMPILE_ADD_ARGS=-DDEBUG -DDEBUGVERBOSE
LIB_COMPILE_ARGS=-pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I$(SHARED_OBJECTS)/qt5/mkspecs/linux-g++ -isystem $(QT5_HEADERS) -isystem $(QT5_HEADERS)/QtWidgets -isystem $(QT5_HEADERS)/QtGui -isystem $(QT5_HEADERS)/QtCore -I $(LIB_SRC)
LIB_COMPILE_LINKER_ARGS=-lSDL -lpthread -Wl,-O1 $(SHARED_OBJECTS)/libQt5Widgets.so $(SHARED_OBJECTS)/libQt5Gui.so $(SHARED_OBJECTS)/libQt5Core.so $(SHARED_OBJECTS)/libGL.so
# compilation
COMPILE=g++
SRC_COMPILE=$(COMPILE) $(SRC_COMPILE_ARGS) $(SRC_COMPILE_ADD_ARGS)
LIB_COMPILE=$(COMPILE) $(LIB_COMPILE_ARGS)
# deletion
DELETE=rm -rf
# silent log using printf
LOG=@printf


all:	full-clean $(TEST_BIN)/test01 $(TEST_BIN)/test02 $(TEST_BIN)/test03
	$(LOG) '\n\033[44mmake all finished\033[49m\n\n'

$(MAIN_OBJ)/ImageNG.o:	$(MAIN_SRC)/ImageNG.cpp $(MAIN_SRC)/ImageNG.h
	$(LOG) '\n\033[42mcreation of the ImageNG object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/ImageNG.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageNG.o

$(MAIN_OBJ)/Dimension.o:	$(MAIN_SRC)/Dimension.cpp $(MAIN_SRC)/Dimension.h
	$(LOG) '\n\033[42mcreation of the Dimension object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/Dimension.cpp \
	-c \
	-o $(MAIN_OBJ)/Dimension.o

$(TEST_BIN)/test01:	$(TEST_OBJ)/test01.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/Dimension.o
	$(LOG) '\n\033[42mcreation of the test01 executable\033[49m\n'
	$(SRC_COMPILE) \
	$(TEST_OBJ)/test01.o \
	$(MAIN_OBJ)/ImageNG.o \
	$(MAIN_OBJ)/Dimension.o \
	-o $(TEST_BIN)/test01

$(TEST_OBJ)/test01.o:	$(TEST_SRC)/test01.cpp $(MAIN_SRC)/ImageNG.h $(MAIN_SRC)/Dimension.h
	$(LOG) '\n\033[42mcreation of the test01 object file\033[49m\n'
	$(SRC_COMPILE) \
	$(TEST_SRC)/test01.cpp \
	-c \
	-o $(TEST_OBJ)/test01.o

$(TEST_BIN)/test02:	$(TEST_OBJ)/test02.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/Dimension.o
	$(LOG) '\n\033[42mcreation of the test02 executable\033[49m\n'
	$(SRC_COMPILE) \
	$(TEST_OBJ)/test02.o \
	$(MAIN_OBJ)/ImageNG.o \
	$(MAIN_OBJ)/Dimension.o \
	-o $(TEST_BIN)/test02

$(TEST_OBJ)/test02.o:	$(TEST_SRC)/test02.cpp $(MAIN_SRC)/ImageNG.h $(MAIN_SRC)/Dimension.h
	$(LOG) '\n\033[42mcreation of the test02 object file\033[49m\n'
	$(SRC_COMPILE) \
	$(TEST_SRC)/test02.cpp \
	-c \
	-o $(TEST_OBJ)/test02.o

$(TEST_BIN)/test03:	$(TEST_OBJ)/test03.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/Dimension.o $(MYQT_LIB_OBJ)/MyQT.o
	$(LOG) '\n\033[42mcreation of the test03 executable\033[49m\n'
	$(SRC_COMPILE) $(LIB_COMPILE_ARGS)$(MYQT) \
	$(TEST_OBJ)/test03.o \
	$(MAIN_OBJ)/ImageNG.o \
	$(MAIN_OBJ)/Dimension.o \
	$(MYQT_LIB_OBJ)/MyQT.o \
	-o $(TEST_BIN)/test03 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test03.o:	$(TEST_SRC)/test03.cpp $(MAIN_SRC)/ImageNG.h $(MAIN_SRC)/Dimension.h $(MYQT_LIB_SRC)/MyQT.h
	$(LOG) '\n\033[42mcreation of the test03 object file\033[49m\n'
	$(SRC_COMPILE) $(LIB_COMPILE_ARGS)$(MYQT) \
	$(TEST_SRC)/test03.cpp \
	-c \
	-o $(TEST_OBJ)/test03.o

$(MYQT_LIB_OBJ)/MyQT.o:	$(MYQT_LIB_SRC)/MyQT.cpp $(MYQT_LIB_SRC)/MyQT.h $(MAIN_SRC)/ImageNG.h $(MAIN_SRC)/Dimension.h
	$(LOG) '\n\033[42mcreation of the MyQT object file\033[49m\n'
	$(LIB_COMPILE)$(MyQT) $(SRC_COMPILE_ARGS) \
	$(MYQT_LIB_SRC)/MyQT.cpp \
	-c \
	-o $(MYQT_LIB_OBJ)/MyQT.o

setup:
	$(LOG) '\n\033[42msetup of the directories\033[49m\n'
	mkdir \
	-p \
	$(MAIN_OBJ) \
	$(TEST_OBJ) \
	$(LIB_OBJ) \
	$(MYQT_LIB_OBJ) \
	$(MAIN_BIN) \
	$(TEST_BIN) \
	$(LIB_BIN) \
	$(MYQT_LIB_BIN)
	$(LOG) '\n\033[44mmake setup finished\033[49m\n\n'

clean:
	$(LOG) '\n\033[41mdeletion of the object directory\033[49m\n'
	$(DELETE) $(OBJ)/*
	make setup
	$(LOG) '\n\033[44mmake clean finished\033[49m\n\n'

full-clean:
	$(LOG) '\n\033[41mdeletion of ALL the build directories\033[49m\n'
	$(DELETE) $(BUILD)/*
	make setup
	$(LOG) '\n\033[44mmake full-clean finished\033[49m\n\n'