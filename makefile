### paths
# sources
SRC=./src
MAIN_SRC=$(SRC)/main
LIB_SRC=$(SRC)/lib
TEST_SRC=$(SRC)/test
# build
BUILD=./build
# build -> objs
OBJ=$(BUILD)/obj
MAIN_OBJ=$(OBJ)/main
LIB_OBJ=$(OBJ)/lib
TEST_OBJ=$(OBJ)/test
# build -> bins
BIN=$(BUILD)/bin
MAIN_BIN=$(BIN)/main
LIB_BIN=$(BIN)/lib
TEST_BIN=$(BIN)/test
### commands
# compilation
COMPILE=g++ -I $(MAIN_SRC)
# deletion
DELETE=rm -rf

all:	setup $(TEST_BIN)/test01

$(TEST_BIN)/test01:	$(TEST_SRC)/test01.cpp $(MAIN_OBJ)/ImageNG.o
	echo creation of the test01 executable
	$(COMPILE) \
	$(TEST_SRC)/test01.cpp \
	$(MAIN_OBJ)/ImageNG.o \
	-o $(TEST_BIN)/test01

$(MAIN_OBJ)/ImageNG.o:	$(MAIN_SRC)/ImageNG.cpp $(MAIN_SRC)/ImageNG.h
	echo creation of the ImageNG object file
	$(COMPILE) \
	$(MAIN_SRC)/ImageNG.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageNG.o

setup:
	echo setup of the directories
	# the - before mkdir is to make sure make ignore the error if the dir can't be created
	-mkdir \
	$(BUILD) \
	$(OBJ) \
	$(MAIN_OBJ) \
	$(LIB_OBJ) \
	$(TEST_OBJ) \
	$(BIN) \
	$(MAIN_BIN) \
	$(LIB_BIN) \
	$(TEST_BIN)

clean:
	echo deletion of the object directory
	$(DELETE) $(OBJ)/*
	make setup

full-clean:
	echo deletion of ALL the build directories
	$(DELETE) $(BUILD)/*
	make setup