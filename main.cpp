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
	MyPictureFile InFile;
	InFile.type = 2;
	InFile.infile = stdin;
	cerr << "gogogo!\n";
	if (argc != 0) {
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
	MyPictureFile OutFile;
	MyPicture.out(OutFile);
	return 0;
}