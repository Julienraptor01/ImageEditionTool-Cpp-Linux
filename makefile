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
# use a generic rule to list all the main headers and the MyQT header
HEADERS=$(wildcard $(MAIN_SRC)/*.h) $(wildcard $(MYQT_LIB_SRC)/*.h)
# use a generic rule to list all the main objects and the MyQT object
OBJECTS=$(patsubst $(MAIN_SRC)/%.cpp,$(MAIN_OBJ)/%.o,$(wildcard $(MAIN_SRC)/*.cpp)) $(MYQT_LIB_OBJ)/MyQT.o
# use a generic rule to list all the tests
TESTS=$(patsubst $(TEST_SRC)/%.cpp,$(TEST_BIN)/%,$(wildcard $(TEST_SRC)/*.cpp))
### commands
# compile arguments
SRC_DEBUG_LINKER=-Xlinker --verbose
SRC_COMPILE_ARGS=-I $(MAIN_SRC) -Wall -Wextra -O3
SRC_COMPILE_ADD_ARGS=#-DDEBUG -DDEBUGVERBOSE -DDEBUGVERYVERBOSE
LIB_COMPILE_ARGS=-pipe -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I$(QT5_HEADERS)/mkspecs/linux-g++ -isystem $(QT5_HEADERS) -isystem $(QT5_HEADERS)/QtWidgets -isystem $(QT5_HEADERS)/QtGui -isystem $(QT5_HEADERS)/QtCore -I $(LIB_SRC)
LIB_COMPILE_LINKER_ARGS=-lQt5Widgets -lQt5Gui -lQt5Core -lGL -lSDL -lpthread
MYQT_LIB_COMPILE=$(LIB_COMPILE)$(MyQT) $(SRC_COMPILE_ARGS)
TEST_COMPILE_ARGS=$(OBJECTS)
# compilation
COMPILE=g++
SRC_COMPILE=$(COMPILE) $(SRC_COMPILE_ARGS) $(SRC_COMPILE_ADD_ARGS)
LIB_COMPILE=$(COMPILE) $(LIB_COMPILE_ARGS)
TEST_COMPILE=$(SRC_COMPILE)$(LIB_COMPILE_ARGS)$(MYQT)
# deletion
DELETE=rm -rf
# silent log using printf
LOG=@printf

.PHONY:	all setup clean full-clean
.SECONDARY:	$(OBJECTS) $(patsubst $(TEST_BIN)/%,$(TEST_OBJ)/%.o,$(TESTS))

all:	full-clean $(TESTS)
	$(LOG) '\n\033[44mmake all finished\033[49m\n\n'

#specific rule for the creation of the main object files of all the Image classes
#this uses some cursedness where if it's just Image % will contain "e" and if it's ImageNG % will contain "eNG", etc.
$(MAIN_OBJ)/Imag%.o:	$(MAIN_SRC)/Imag%.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the Imag$* object file\033[49m\n'
	$(SRC_COMPILE) \
	-I $(MYQT_LIB_SRC) \
	$(MAIN_SRC)/Imag$*.cpp \
	-c \
	-o $(MAIN_OBJ)/Imag$*.o

#generic rule for the creation of the main object files
$(MAIN_OBJ)/%.o:	$(MAIN_SRC)/%.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the $* object file\033[49m\n'
	$(SRC_COMPILE) \
	$(MAIN_SRC)/$*.cpp \
	-c \
	-o $(MAIN_OBJ)/$*.o

#generic rule for the creation of the test object files
$(TEST_OBJ)/%.o:	$(TEST_SRC)/%.cpp $(HEADERS)
	$(LOG) '\n\033[42mcreation of the $* object file\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_SRC)/$*.cpp \
	-c \
	-o $(TEST_OBJ)/$*.o

#generic rule for the creation of the test executables
$(TEST_BIN)/%:	$(TEST_OBJ)/%.o $(OBJECTS)
	$(LOG) '\n\033[42mcreation of the $* executable\033[49m\n'
	$(TEST_COMPILE) \
	$(TEST_OBJ)/$*.o \
	$(TEST_COMPILE_ARGS) \
	-o $(TEST_BIN)/$* \
	$(LIB_COMPILE_LINKER_ARGS)

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
