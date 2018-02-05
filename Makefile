CC = g++
CFLAGS = -std=c++11 -Ofast -c
LFLAGS = -std=c++11 -Ofast
OBJS = main.o datatable.o bspline.o bsplinebasis.o bsplinebasis1d.o bsplinebuilder.o serializer.o datapoint.o function.o mykroneckerproduct.o knots.o utilities.o
PROGNAME = SplinterTest
#INCLUDE = -I/home/jake/Desktop/splinter/include/

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PROGNAME)

utilities.o: utilities.cpp
	$(CC) $(CFLAGS) utilities.cpp

mykroneckerproduct.o: mykroneckerproduct.cpp
	$(CC) $(CFLAGS) mykroneckerproduct.cpp

knots.o: knots.cpp
	$(CC) $(CFLAGS) knots.cpp

function.o: function.cpp
	$(CC) $(CFLAGS) function.cpp

datapoint.o: datapoint.cpp
	$(CC) $(CFLAGS) datapoint.cpp

serializer.o: serializer.cpp
	$(CC) $(CFLAGS) serializer.cpp

bsplinebuilder.o: bsplinebuilder.cpp
	$(CC) $(CFLAGS) bsplinebuilder.cpp

bsplinebasis.o: bsplinebasis.cpp
	$(CC) $(CFLAGS) bsplinebasis.cpp

datatable.o: datatable.cpp
	$(CC) $(CFLAGS) datatable.cpp

bspline.o: bspline.cpp
	$(CC) $(CFLAGS) bspline.cpp

bsplinebasis1d.o: bsplinebasis1d.cpp
	$(CC) $(CFLAGS) bsplinebasis1d.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm *.o $(PROGNAME)
