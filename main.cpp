#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include "MyPictureFile.h"
#include "BMP.h"
#include <cmath>
#include "random.h"

using namespace std; //is very bad

const Color White = Color(255, 255, 255);

struct Error{
	string s;
};

void DFS(vector<vector<Color> > & map, int x, int y, Color c){
	const int X[] = {1, 0, -1, 0};
	const int Y[] = {0, 1, 0, -1};
	Color last = map[x][y];
	if (last == c)
		return;
	map[x][y] = c;
	for (int i = 0; i < 4; ++i){
		int newx = x + X[i];
		int newy = y + Y[i];
		if (0 <= newx && newx < (int) map.size() && 0 <= newy && newy < (int) map[0].size()){
			if (map[newx][newy] == last){
				DFS(map, newx, newy, c);
			}
		}
	}
}

int main(int argc, char* argv[]){
	//fstream fin;
	MyPictureFile MyFile;
	MyFile.type = 2;
	MyFile.infile = stdin;
	MyFile.outfile = stdout;
	//fin.open("Без имени.bmp", ios::in | ios::binary);
	//if (!fin){ cout << "Файл не открыт\n";}
	cerr << "gogogo!\n";
	if (argc != 6) {
		cerr << "Error\n";
		return 0;
	}
	//char c;
	//stdstream >> c;
	Color NewColor;
	NewColor.R = (uint8_t) atoi(argv[1]);
	NewColor.G = (uint8_t) atoi(argv[2]);
	NewColor.B = (uint8_t) atoi(argv[3]);
	int StartX = (int) atoi(argv[4]);
	int StartY = (int) atoi(argv[5]);
	cerr << (int) NewColor.R << " " << (int) NewColor.G << " " << (int) NewColor.B << endl;
	BMP_PICTURE MyPicture;
	//cin >> MyPicture;
	MyPicture.in(MyFile);
	//cerr << MyPicture.info.Width << " " << MyPicture.info.Height << endl;
	//MyPicture.info.x = 1000;
	//MyPicture.info.y = 1000;
	//MyPicture.Picture.resize(MyPicture.info.x);
	DRandom N;
	//DFS(MyPicture.picture, StartX, StartY, NewColor);
	for (int x = 0; x < (int) MyPicture.info.Width; ++x){
		//MyPicture[x].resize(MyPicture.info.y);
		for (int y = 0; y < (int) MyPicture.info.Height; ++y){
			MyPicture[x][y] = White;
			//MyPicture[x][y].R = rand() % (MyPicture[x][y].R + 1);
			//MyPicture[x][y].G = rand() % (MyPicture[x][y].G + 1);
			//MyPicture[x][y].B = rand() % (MyPicture[x][y].B + 1);
			//cerr << x << " " << y << endl;
			//MyPicture[x][y].R = (MyPicture[x][y].R + 5 * N.RangeRandom(0, 256, (x + y) / 10)) / 6;
			//MyPicture[x][y].G = (MyPicture[x][y].G + 5 * N.RangeRandom(0, 256, (x + y) / 10)) / 6;
			//MyPicture[x][y].B = (MyPicture[x][y].B + 5 * N.RangeRandom(0, 256, (x + y) / 10)) / 6;
		}
	}
	for (int i = 0; i < 10; ++i){
		int x1 = rand() % ((int) MyPicture.info.Width), y1 = rand() % ((int) MyPicture.info.Height);
		int x2 = rand() % ((int) MyPicture.info.Width), y2 = rand() % ((int) MyPicture.info.Height);
		MyPicture.DrawLine(x1, y1, x2, y2, NewColor);
	}
	//DFS(MyPicture.picture, StartX, StartY, NewColor);
	MyPicture.out(MyFile);
	return 0;
}