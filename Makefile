all: main

git:
	git add *.cpp *.h Makefile CommitNomber *.py
	git commit -m "auto 7"
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

main: main.o
	g++ main.o -o main
	./main 128 0 128 0 0 < Без\ имени.bmp > Без\ имени\(копия\).bmp
	make clean

main.o: main.cpp MyPictureFile.h BMP.h random.h
	g++ -c main.cpp

clean:
	rm -rf try.o try deleteme.o deleteme Imj.o Imj qwe.o qwe main.o main


