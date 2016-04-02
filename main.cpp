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
const Color Black = Color(0, 0, 0);

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
	MyPictureFile MyFile;
	MyFile.type = 2;
	MyFile.infile = stdin;
	MyFile.outfile = stdout;
	cerr << "gogogo!\n";
	if (argc != 6) {
		cerr << "Error\n";
		return 0;
	}
	Color NewColor;
	NewColor.R = (uint8_t) atoi(argv[1]);
	NewColor.G = (uint8_t) atoi(argv[2]);
	NewColor.B = (uint8_t) atoi(argv[3]);
	int StartX = (int) atoi(argv[4]);
	int StartY = (int) atoi(argv[5]);
	cerr << (int) NewColor.R << " " << (int) NewColor.G << " " << (int) NewColor.B << endl;
	BMP_PICTURE MyPicture;
	MyPicture.in(MyFile);
	DRandom Nomber;
	//DFS(MyPicture.picture, StartX, StartY, NewColor);
	int N = 100;
	int X[N];
	int Y[N];
	Color Colors[N];
	for (int _ = 0; _ < N; ++_){
		X[_] = rand() % (int) MyPicture.info.Width;
		Y[_] = rand() % (int) MyPicture.info.Height;
		Colors[_].R = rand() % 255;
		Colors[_].G = rand() % 255;
		Colors[_].B = rand() % 255;
	}
	for (int x = 0; x < (int) MyPicture.info.Width; ++x){
		for (int y = 0; y < (int) MyPicture.info.Height; ++y){
			int dist, ans, min = MyPicture.info.Width * MyPicture.info.Width + MyPicture.info.Height * MyPicture.info.Height + 1;
			bool b = false;
			for (int _ = 0; _ < N; ++_){
				dist = (X[_] - x) * (X[_] - x) + (Y[_] - y) * (Y[_] - y);
				if (min == dist){
					//b = true;
				}
				if (min > dist){
					min = dist;
					b = false;
					ans = _;
				}
			}
			if (b){
				MyPicture[x][y] = Black;
			}
			else{
				MyPicture[x][y] = Colors[ans];
			}
		}
	}
	//DFS(MyPicture.picture, StartX, StartY, NewColor);
	MyPicture.out(MyFile);
	return 0;
}