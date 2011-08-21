CC = g++
CFLAGS = -lm -std=c++0x 

all: libPAK.a pakEXE

#libPAK: libPAK.a

libPAK.a: libPAK/libPAK.o
	ar rvs ./libPAK.a libPAK.o

pakEXE: pakEXE/pakEXE.o libPAK.a
	mkdir -p Output
	$(CC) $(CFLAGS) pakEXE.o -o Output/pakEXE libPAK.a

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.a Output/
