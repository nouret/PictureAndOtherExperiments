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
const Color Green = Color(0, 255, 0);

const int K = 5;

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
	if (argc != 1) {
		cerr << "Error\n";
		return 0;
	}
	BMP_PICTURE MyPicture;
	MyPicture.in(InFile);

	Color centers[K];

	vector<vector<int> > PictureMap;
	PictureMap.resize((int) MyPicture.info.Width);
	for (int _ = 0; _ < (int) MyPicture.info.Width; ++_){
		PictureMap[_].resize((int) MyPicture.info.Height);
	}
	int SumColorsR[K], SumColorsG[K], SumColorsB[K], CountColors[K];

	bool good = false;

	//int kngkklsglk = 0;

	for (int _ = 0; _ < K; ++_){
		centers[_].R = rand() % 255;
		centers[_].G = rand() % 255;
		centers[_].B = rand() % 255;
	}

	while (not good){
		for (int _ = 0; _ < K; ++_){
			SumColorsR[_] = 0;
			SumColorsG[_] = 0;
			SumColorsB[_] = 0;
			CountColors[_] = 0;
		}
		for (int i = 0; i < (int) MyPicture.info.Width; ++i){
			for (int j = 0; j < (int) MyPicture.info.Height; ++j){
				int min_dist_c = 256 * 256 * 3;
				int index_min_dist_c;
				for (int _ = 0; _ < K; ++_){
					if (min_dist_c > centers[_].distance(MyPicture[i][j])){
						min_dist_c = centers[_].distance(MyPicture[i][j]);
						index_min_dist_c = _;
					}
				}
				SumColorsR[index_min_dist_c] += MyPicture[i][j].R;
				SumColorsG[index_min_dist_c] += MyPicture[i][j].G;
				SumColorsB[index_min_dist_c] += MyPicture[i][j].B;
				CountColors[index_min_dist_c] ++;
			}
		}
		good = true;
		for (int _ = 0; _ < K; ++_){
			if (((int) round(((double) SumColorsR[_]) / ((double) CountColors[_]))) != centers[_].R){
				centers[_].R = (int) (round(((double) SumColorsR[_]) / ((double) CountColors[_])));
			}
			if (((int) round(((double) SumColorsG[_]) / ((double) CountColors[_]))) != centers[_].G){
				centers[_].G = (int) (round(((double) SumColorsG[_]) / ((double) CountColors[_])));
			}
			if (((int) round(((double) SumColorsB[_]) / ((double) CountColors[_]))) != centers[_].B){
				centers[_].B = (int) (round(((double) SumColorsB[_]) / ((double) CountColors[_])));
			}
		}
		/*
		cerr << endl;
		cerr << (int) centers[0].R << " " << (int) centers[0].G << " " << (int) centers[0].B << endl;
		cerr << (int) centers[1].R << " " << (int) centers[1].G << " " << (int) centers[1].B << endl;
		cerr << (int) centers[2].R << " " << (int) centers[2].G << " " << (int) centers[2].B << endl;
		cerr << endl;

		kngkklsglk++;
		if (kngkklsglk > 100){
			good = true;
		}
		*/
	}

	MyPictureFile OutFile;
	OutFile.type = 2;
	OutFile.outfile = stdout;
	BMP_PICTURE NewPicture;
	NewPicture.header = MyPicture.header;
	NewPicture.info = MyPicture.info;
	NewPicture.picture.resize((int) NewPicture.info.Width);
	for (int i = 0; i < (int) NewPicture.info.Width; ++i){
		NewPicture.picture[i].resize((int) NewPicture.info.Height);
		for (int j = 0; j < (int) NewPicture.info.Height; ++j){
			NewPicture[i][j] = White;
			int min_dist_c = 256 * 256 * 3;
			int index_min_dist_c;
			for (int _ = 0; _ < K; ++_){
				if (min_dist_c > centers[_].distance(MyPicture[i][j])){
					min_dist_c = centers[_].distance(MyPicture[i][j]);
					index_min_dist_c = _;
				}
			}
			if (index_min_dist_c == 4){
				NewPicture[i][j] = MyPicture[i][j];
			}
		}
	}
	NewPicture.out(OutFile);
	return 0;
}