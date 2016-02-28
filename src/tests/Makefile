all: TestMap

TestMap: TestMap.c Map.o Map_Element.o utils.o
	cc TestMap.c ../control/Map_Element.o ../control/Map.o ../control/utils.o -o TestMap

Map.o:
	CC -g -O -c ../control/Map.c -o ../control/Map.o

Map_Element.o:
	CC -g -O -c ../control/Map_Element.c -o ../control/Map_Element.o

utils.o:
	CC -g -O -c ../control/utils.c -o ../control/utils.o

clean: 
	rm TestMap ./control/Map_Element.o ../control/Map.o
