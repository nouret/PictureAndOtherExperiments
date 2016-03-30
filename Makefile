all: try

qwe: qwe.o
	g++ qwe.o -o qwe
	./qwe
	make clean

qwe.o: qwe.cpp
	g++ -c qwe.cpp

Imj: Imj.o
	g++ Imj.o -o Imj
	./Imj

Imj.o: Imj.cpp
	g++ -c Imj.cpp

deleteme: deleteme.o
	g++ deleteme.o -o deleteme
	./deleteme

deleteme.o: deleteme.cpp
	g++ -c deleteme.cpp

try: try.o
	g++ try.o -o try
	./try 13 179 69 30 30 < Без\ имени.bmp > Без\ имени\(копия\).bmp
	make clean

try.o: try.cpp
	g++ -c try.cpp

clean:
	rm -rf try.o try deleteme.o deleteme Imj.o Imj qwe.o qwe