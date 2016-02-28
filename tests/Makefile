all: TestMap

TestMap: TestMap.c Map.o Map_Element.o utils.o
	cc -D "DEBUG" TestMap.c ../src/control/Map_Element.o ../src/control/Map.o ../src/control/utils.o -o TestMap

Map.o:
	CC -g -O -c ../src/control/Map.c -o ../src/control/Map.o

Map_Element.o:
	CC -g -O -c ../src/control/Map_Element.c -o ../src/control/Map_Element.o

utils.o:
	CC -g -O -c ../src/control/utils.c -o ../src/control/utils.o

clean:
	rm TestMap ../src/control/Map_Element.o ../src/control/Map.o ../src/control/utils.o
