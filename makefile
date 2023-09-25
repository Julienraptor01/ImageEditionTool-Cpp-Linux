test01:	src/test/test01.cpp obj/ImageNG.o
	g++ \
	-I src/main \
	src/test/test01.cpp \
	obj/ImageNG.o \
	-o bin/test01

obj/ImageNG.o:	src/main/ImageNG.cpp src/main/ImageNG.h
	g++ \
	src/main/ImageNG.cpp \
	-c \
	-o obj/ImageNG.o


clean:
	rm \
	obj/*.o \
	core \
	-f

clobber:	clean
	rm \
	bin/*