all: main

pragma: pragma.o
	g++ -fopenmp pragma.o -o pragma
	./pragma
	make clean

pragma.o:
	g++ -fopenmp -c pragma.cpp -o pragma.o

try: try.o
	g++ try.o -o try
	./try
	make clean

try.o: try.cpp
	g++ -c try.cpp

git:
	git add *.cpp *.h Makefile CommitNomber *.py *.bmp
	git commit -m "auto 11"
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
	g++ main.o -o main
	./main < Без\ имени\(копия\).bmp
	#./main < qwerty.bmp
	make clean

mainfast: mainfast.o
	g++ -fopenmp mainfast.o -o mainfast
	./mainfast < Без\ имени\(копия\).bmp
	#./main < qwerty.bmp
	make clean

mainfast.o: main.cpp MyPictureFile.h BMP.h random.h
	g++ -fopenmp -c main.cpp -o mainfast.o

main.o: main.cpp MyPictureFile.h BMP.h random.h
	g++ -c main.cpp

clean:
	rm -rf try.o try deleteme.o deleteme Imj.o Imj qwe.o qwe main.o main noise.o noise try2 try2.o pragma pragma.o mainfast.o mainfast


