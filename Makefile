all: main

pragma: pragma.o
	g++ -fopenmp pragma.o -o pragma
	./pragma
	make clean

pragma.o:
	g++ -fopenmp -c pragma.cpp -o pragma.o

try: try.o
	g++ -pthread try.o -o try -std=c++11
	./try
	make clean

try.o: try.cpp
	g++ -pthread -c try.cpp -std=c++11

git:
	git add *.cpp *.h Makefile CommitNomber *.py *.bmp
	git commit -m "auto 18"
	git push
	python3 massage.py > Makefile2
	mv Makefile2 Makefile

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

noise: noise.o
	g++ noise.o -o noise
	./noise < fluttershy.bmp > noise2.bmp
	make clean

noise.o: noise.cpp MyPictureFile.h BMP.h random.h
	g++ -c noise.cpp

main: main.o
	g++ -pthread main.o -o main -std=c++11 -lrt
	./main < Без\ имени\(копия\).bmp
	#./main < qwerty.bmp
	make clean

mainfast: mainfast.o
	g++ -fopenmp mainfast.o -o mainfast -lrt
	./mainfast < Без\ имени\(копия\).bmp
	#./main < qwerty.bmp
	make clean

mainfast.o: mainfast.cpp MyPictureFile.h BMP.h random.h
	g++ -fopenmp -c mainfast.cpp -o mainfast.o -lrt

main.o: main.cpp MyPictureFile.h BMP.h random.h
	g++ -pthread -c main.cpp -std=c++11 -lrt

try_mutex: try_mutex.o
	g++ try_mutex.o -o try_mutex.out -fopenmp
	./try_mutex.out
	make clean

try_mutex.o: try_mutex.cpp
	g++ -c try_mutex.cpp -o try_mutex.o -std=c++11

clean:
	rm -rf try.o try deleteme.o deleteme Imj.o Imj qwe.o qwe main.o main noise.o noise
	rm -rf try2 try2.o pragma pragma.o mainfast.o mainfast
	rm -rf try_mutex.out try_mutex.o
