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
COMPILE=g++ -I $(MAIN_SRC) -Wall -DDEBUG -DDEBUGVERBOSE
# deletion
DELETE=rm -rf
# silent log using printf
LOG=@printf


all:	full-clean $(TEST_BIN)/test01 $(TEST_BIN)/test02
	$(LOG) '\n\033[44mmake all finished\033[49m\n\n'

$(MAIN_OBJ)/ImageNG.o:	$(MAIN_SRC)/ImageNG.cpp $(MAIN_SRC)/ImageNG.h
	$(LOG) '\n\033[42mcreation of the ImageNG object file\033[49m\n'
	$(COMPILE) \
	$(MAIN_SRC)/ImageNG.cpp \
	-c \
	-o $(MAIN_OBJ)/ImageNG.o

$(MAIN_OBJ)/Dimension.o:	$(MAIN_SRC)/Dimension.cpp $(MAIN_SRC)/Dimension.h
	$(LOG) '\n\033[42mcreation of the Dimension object file\033[49m\n'
	$(COMPILE) \
	$(MAIN_SRC)/Dimension.cpp \
	-c \
	-o $(MAIN_OBJ)/Dimension.o

$(TEST_BIN)/test01:	$(TEST_OBJ)/test01.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/Dimension.o
	$(LOG) '\n\033[42mcreation of the test01 executable\033[49m\n'
	$(COMPILE) \
	$(TEST_OBJ)/test01.o \
	$(MAIN_OBJ)/ImageNG.o \
	$(MAIN_OBJ)/Dimension.o \
	-o $(TEST_BIN)/test01

$(TEST_OBJ)/test01.o:	$(TEST_SRC)/test01.cpp
	$(LOG) '\n\033[42mcreation of the test01 object file\033[49m\n'
	$(COMPILE) \
	$(TEST_SRC)/test01.cpp \
	-c \
	-o $(TEST_OBJ)/test01.o

$(TEST_BIN)/test02:	$(TEST_OBJ)/test02.o $(MAIN_OBJ)/ImageNG.o $(MAIN_OBJ)/Dimension.o
	$(LOG) '\n\033[42mcreation of the test02 executable\033[49m\n'
	$(COMPILE) \
	$(TEST_OBJ)/test02.o \
	$(MAIN_OBJ)/ImageNG.o \
	$(MAIN_OBJ)/Dimension.o \
	-o $(TEST_BIN)/test02

$(TEST_OBJ)/test02.o:	$(TEST_SRC)/test02.cpp
	$(LOG) '\n\033[42mcreation of the test02 object file\033[49m\n'
	$(COMPILE) \
	$(TEST_SRC)/test02.cpp \
	-c \
	-o $(TEST_OBJ)/test02.o

setup:
	$(LOG) '\n\033[42msetup of the directories\033[49m\n'
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