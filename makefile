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
else ifeq "$(OS)" "fedora"
QT5_HEADERS=/usr/include/qt5
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
# lists
HEADERS=$(MAIN_SRC)/Image.h $(MAIN_SRC)/ImageNG.h $(MAIN_SRC)/ImageRGB.h $(MAIN_SRC)/ImageB.h $(MAIN_SRC)/Dimension.h $(MAIN_SRC)/Couleur.h $(MAIN_SRC)/Exception.h $(MAIN_SRC)/XYException.h $(MAIN_SRC)/ColorException.h $(MYQT_LIB_SRC)/MyQT.h
OBJECTS=$(MAIN_OBJ)/Image.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/ImageRGB.o $(MAIN_OBJ)/ImageB.o $(MAIN_OBJ)/Dimension.o $(MAIN_OBJ)/Couleur.o $(MAIN_OBJ)/Exception.o $(MAIN_OBJ)/XYException.o $(MAIN_OBJ)/ColorException.o $(MYQT_LIB_OBJ)/MyQT.o
### commands
# compile arguments
SRC_DEBUG_LINKER=-Xlinker --verbose
SRC_COMPILE_ARGS=-I $(MAIN_SRC) -Wall -Wextra
SRC_COMPILE_ADD_ARGS=#-DDEBUG -DDEBUGVERBOSE -DDEBUGVERYVERBOSE
LIB_COMPILE_ARGS=-pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I$(QT5_HEADERS)/mkspecs/linux-g++ -isystem $(QT5_HEADERS) -isystem $(QT5_HEADERS)/QtWidgets -isystem $(QT5_HEADERS)/QtGui -isystem $(QT5_HEADERS)/QtCore -I $(LIB_SRC)
LIB_COMPILE_LINKER_ARGS=-Wl,-O1 -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lSDL -lpthread
MYQT_LIB_COMPILE=$(LIB_COMPILE)$(MyQT) $(SRC_COMPILE_ARGS)
TEST_COMPILE_ARGS=$(OBJECTS)
# compilation
COMPILE=g++
SRC_COMPILE=$(COMPILE) $(SRC_COMPILE_ARGS) $(SRC_COMPILE_ADD_ARGS)
LIB_COMPILE=$(COMPILE) $(LIB_COMPILE_ARGS)
TEST_COMPILE=$(SRC_COMPILE) $(LIB_COMPILE_ARGS)$(MYQT)
# deletion
DELETE=rm -rf
# silent log using printf
LOG=@printf


all:	full-clean $(TEST_BIN)/test01 $(TEST_BIN)/test02 $(TEST_BIN)/test03 $(TEST_BIN)/test04 $(TEST_BIN)/test05 $(TEST_BIN)/test06
	$(LOG) '\n\033[44mmake all finished\033[49m\n\n'

$(MAIN_OBJ)/Image.o:	$(MAIN_SRC)/Image.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the Image object file\033[49m\n'
	$(SRC_COMPILE) \
	-I $(MYQT_LIB_SRC) \
	$(MAIN_SRC)/Image.cpp \
	-c \
	-o $(MAIN_OBJ)/Image.o

$(MAIN_OBJ)/ImageNG.o:	$(MAIN_SRC)/ImageNG.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the ImageNG object file\033[49m\n'
	$(SRC_COMPILE) \
	-I $(MYQT_LIB_SRC) \
	$(MAIN_SRC)/ImageNG.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageNG.o

$(MAIN_OBJ)/ImageRGB.o:	$(MAIN_SRC)/ImageRGB.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the ImageRGB object file\033[49m\n'
	$(SRC_COMPILE) \
	-I $(MYQT_LIB_SRC) \
	$(MAIN_SRC)/ImageRGB.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageRGB.o

$(MAIN_OBJ)/ImageB.o:	$(MAIN_SRC)/ImageB.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the ImageB object file\033[49m\n'
	$(SRC_COMPILE) \
	-I $(MYQT_LIB_SRC) \
	$(MAIN_SRC)/ImageB.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageB.o

$(MAIN_OBJ)/Dimension.o:	$(MAIN_SRC)/Dimension.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the Dimension object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/Dimension.cpp \
	-c \
	-o $(MAIN_OBJ)/Dimension.o

$(MAIN_OBJ)/Couleur.o:	$(MAIN_SRC)/Couleur.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the Couleur object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/Couleur.cpp \
	-c \
	-o $(MAIN_OBJ)/Couleur.o

$(MAIN_OBJ)/Exception.o:	$(MAIN_SRC)/Exception.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the Exception object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/Exception.cpp \
	-c \
	-o $(MAIN_OBJ)/Exception.o

$(MAIN_OBJ)/XYException.o:	$(MAIN_SRC)/XYException.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the XYException object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/XYException.cpp \
	-c \
	-o $(MAIN_OBJ)/XYException.o

$(MAIN_OBJ)/ColorException.o:	$(MAIN_SRC)/ColorException.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the ColorException object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/ColorException.cpp \
	-c \
	-o $(MAIN_OBJ)/ColorException.o

$(TEST_BIN)/test01:	$(TEST_OBJ)/test01.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test01 executable\033[49m\n'
	$(TEST_COMPILE) $(LIB_COMPILE_ARGS)$(MYQT) \
	$(TEST_OBJ)/test01.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test01 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test01.o:	$(TEST_SRC)/test01.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test01 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test01.cpp \
	-c \
	-o $(TEST_OBJ)/test01.o

$(TEST_BIN)/test02:	$(TEST_OBJ)/test02.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test02 executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/test02.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test02 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test02.o:	$(TEST_SRC)/test02.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test02 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test02.cpp \
	-c \
	-o $(TEST_OBJ)/test02.o

$(TEST_BIN)/test03:	$(TEST_OBJ)/test03.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test03 executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/test03.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test03 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test03.o:	$(TEST_SRC)/test03.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test03 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test03.cpp \
	-c \
	-o $(TEST_OBJ)/test03.o

$(TEST_BIN)/test04:	$(TEST_OBJ)/test04.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test04 executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/test04.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test04 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test04.o:	$(TEST_SRC)/test04.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test04 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test04.cpp \
	-c \
	-o $(TEST_OBJ)/test04.o

$(TEST_BIN)/test05:	$(TEST_OBJ)/test05.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test05 executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/test05.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test05 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test05.o:	$(TEST_SRC)/test05.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test05 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test05.cpp \
	-c \
	-o $(TEST_OBJ)/test05.o

$(TEST_BIN)/test06:	$(TEST_OBJ)/test06.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the test06 executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/test06.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/test06 \
	$(LIB_COMPILE_LINKER_ARGS)

$(TEST_OBJ)/test06.o:	$(TEST_SRC)/test06.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the test06 object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/test06.cpp \
	-c \
	-o $(TEST_OBJ)/test06.o

$(MYQT_LIB_OBJ)/MyQT.o:	$(MYQT_LIB_SRC)/MyQT.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the MyQT object file\033[49m\n'
	$(MYQT_LIB_COMPILE) \
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
