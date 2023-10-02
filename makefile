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
# silent log using printf
LOG=@printf


all:	setup $(TEST_BIN)/test01
	$(LOG) '\n\033[44mmake all finished\033[49m\n\n'

$(TEST_BIN)/test01:	$(TEST_SRC)/test01.cpp $(MAIN_OBJ)/ImageNG.o
	$(LOG) '\n\033[42mcreation of the test01 executable\033[49m\n'
	$(COMPILE) \
	$(TEST_SRC)/test01.cpp \
	$(MAIN_OBJ)/ImageNG.o \
	-o $(TEST_BIN)/test01

$(MAIN_OBJ)/ImageNG.o:	$(MAIN_SRC)/ImageNG.cpp $(MAIN_SRC)/ImageNG.h
	$(LOG) '\n\033[42mcreation of the ImageNG object file\033[49m\n'
	$(COMPILE) \
	$(MAIN_SRC)/ImageNG.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageNG.o

setup:
	$(LOG) '\n\033[42msetup of the directories\033[49m\n'
# the - before mkdir is to make sure make ignore the error if the dir can't be created
	mkdir \
	-p \
	$(MAIN_OBJ) \
	$(LIB_OBJ) \
	$(TEST_OBJ) \
	$(MAIN_BIN) \
	$(LIB_BIN) \
	$(TEST_BIN)
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