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

#include <omp.h>

#include <time.h>

using namespace std; //is very bad

const Color White = Color(255, 255, 255);
const Color Black = Color(0, 0, 0);
const Color Green = Color(0, 255, 0);

const int K = 50;

struct MyData{
	unsigned int id;
	vector<Color> points;
	vector<Color> questions;
	vector<int> ansver;
	Color me;
};

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
	//cerr << "gogogo!\n";
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

	//vector<MyData> Threads;
	//int ThreadsCounter = 0;

	//cerr << "sfdfsd" << endl;

	timespec StartTimespec;
	clock_gettime(CLOCK_REALTIME, &StartTimespec /*clockid_t clk_id, struct timespec *res*/);
	double Start = (double) StartTimespec.tv_sec + (double) StartTimespec.tv_nsec / 1000000000.;

	while (not good){
		#pragma omp parallel for
		for (int _ = 0; _ < K; ++_){
			SumColorsR[_] = 0;
			SumColorsG[_] = 0;
			SumColorsB[_] = 0;
			CountColors[_] = 0;
		}
		//Threads.clear();
		//Threads.resize((int) MyPicture.info.Width);
		/*
		for (int i = 0; i < (int) MyPicture.info.Width; ++i){
			Threads[i].id = ThreadsCounter;
			Threads[i].points.resize(K);
			++ThreadsCounter;
			for (int _ = 0; _ < K; ++_){
				Threads[i].points[_] = centers[_];
			}
			Threads[i].questions.resize((int) MyPicture.info.Height);
			for (int j = 0; j < (int) MyPicture.info.Height; ++j){
				Threads[i].questions[j] = MyPicture[i][j];
			}
		}
		*/
		#pragma omp parallel for
		for (int i = 0; i < (int) MyPicture.info.Width; ++i){
			//cerr << i << endl;
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
		#pragma omp parallel for
		for (int _ = 0; _ < K; ++_){
			if (CountColors[_] != 0){
				if (((int) round(((double) SumColorsR[_]) / ((double) CountColors[_]))) != centers[_].R){
					//cout << endl << (int) centers[_].R << " -R- ";
					centers[_].R = (int) ((((double) SumColorsR[_]) / ((double) CountColors[_])) + 0.5);
					//cout << (int) centers[_].R << endl;
					good = false;
				}
				if (((int) round(((double) SumColorsG[_]) / ((double) CountColors[_]))) != centers[_].G){
					//cout << endl << (int) centers[_].G << " -G- ";
					centers[_].G = (int) ((((double) SumColorsG[_]) / ((double) CountColors[_])) + 0.5);
					//cout << (int) centers[_].G << endl;
					good = false;
				}
				if (((int) round(((double) SumColorsB[_]) / ((double) CountColors[_]))) != centers[_].B){
					//cout << endl << (int) centers[_].B << " -B- ";
					centers[_].B = (int) ((((double) SumColorsB[_]) / ((double) CountColors[_])) + 0.5);
					//cout << (int) centers[_].B << endl;
					good = false;
				}
			}
			else{
				//cerr << centers[_].R << " " << centers[_].G << " " << centers[_].B << endl;
			}
		}
		//good = true;
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

	clock_gettime(CLOCK_REALTIME, &StartTimespec /*clockid_t clk_id, struct timespec *res*/);
	printf("%f\n", (double) StartTimespec.tv_sec + (double) StartTimespec.tv_nsec / 1000000000. - Start);
	//cout << clock_getres(CLOCK_REALTIME, &StartTimespec /*clockid_t clk_id, struct timespec *res*/) /* - Start*/ << endl;

	MyPictureFile OutFile0;
	OutFile0.type = 2;
	FILE * File0 = fopen("out0.bmp", "w");
	OutFile0.outfile = File0;
	MyPictureFile OutFile1;
	OutFile1.type = 2;
	FILE * File1 = fopen("out1.bmp", "w");
	OutFile1.outfile = File1;
	MyPictureFile OutFile2;
	OutFile2.type = 2;
	FILE * File2 = fopen("out2.bmp", "w");
	OutFile2.outfile = File2;
	MyPictureFile OutFile3;
	OutFile3.type = 2;
	FILE * File3 = fopen("out3.bmp", "w");
	OutFile3.outfile = File3;
	MyPictureFile OutFile4;
	OutFile4.type = 2;
	FILE * File4 = fopen("out4.bmp", "w");
	OutFile4.outfile = File4;
	MyPictureFile OutFile5;
	OutFile5.type = 2;
	FILE * File5 = fopen("out5.bmp", "w");
	OutFile5.outfile = File5;
	MyPictureFile OutFile6;
	OutFile6.type = 2;
	FILE * File6 = fopen("out6.bmp", "w");
	OutFile6.outfile = File6;
	MyPictureFile OutFile7;
	OutFile7.type = 2;
	FILE * File7 = fopen("out7.bmp", "w");
	OutFile7.outfile = File7;
	MyPictureFile OutFile8;
	OutFile8.type = 2;
	FILE * File8 = fopen("out8.bmp", "w");
	OutFile8.outfile = File8;
	MyPictureFile OutFile9;
	OutFile9.type = 2;
	FILE * File9 = fopen("out9.bmp", "w");
	OutFile9.outfile = File9;
	MyPictureFile OutFile10;
	OutFile10.type = 2;
	FILE * File10 = fopen("out10.bmp", "w");
	OutFile10.outfile = File10;
	MyPictureFile OutFile11;
	OutFile11.type = 2;
	FILE * File11 = fopen("out11.bmp", "w");
	OutFile11.outfile = File11;
	MyPictureFile OutFile12;
	OutFile12.type = 2;
	FILE * File12 = fopen("out12.bmp", "w");
	OutFile12.outfile = File12;
	MyPictureFile OutFile13;
	OutFile13.type = 2;
	FILE * File13 = fopen("out13.bmp", "w");
	OutFile13.outfile = File13;
	MyPictureFile OutFile14;
	OutFile14.type = 2;
	FILE * File14 = fopen("out14.bmp", "w");
	OutFile14.outfile = File14;
	MyPictureFile OutFile15;
	OutFile15.type = 2;
	FILE * File15 = fopen("out15.bmp", "w");
	OutFile15.outfile = File15;
	MyPictureFile OutFile16;
	OutFile16.type = 2;
	FILE * File16 = fopen("out16.bmp", "w");
	OutFile16.outfile = File16;
	MyPictureFile OutFile17;
	OutFile17.type = 2;
	FILE * File17 = fopen("out17.bmp", "w");
	OutFile17.outfile = File17;
	MyPictureFile OutFile18;
	OutFile18.type = 2;
	FILE * File18 = fopen("out18.bmp", "w");
	OutFile18.outfile = File18;
	MyPictureFile OutFile19;
	OutFile19.type = 2;
	FILE * File19 = fopen("out19.bmp", "w");
	OutFile19.outfile = File19;
	MyPictureFile OutFile20;
	OutFile20.type = 2;
	FILE * File20 = fopen("out20.bmp", "w");
	OutFile20.outfile = File20;
	MyPictureFile OutFile21;
	OutFile21.type = 2;
	FILE * File21 = fopen("out21.bmp", "w");
	OutFile21.outfile = File21;
	MyPictureFile OutFile22;
	OutFile22.type = 2;
	FILE * File22 = fopen("out22.bmp", "w");
	OutFile22.outfile = File22;
	MyPictureFile OutFile23;
	OutFile23.type = 2;
	FILE * File23 = fopen("out23.bmp", "w");
	OutFile23.outfile = File23;
	MyPictureFile OutFile24;
	OutFile24.type = 2;
	FILE * File24 = fopen("out24.bmp", "w");
	OutFile24.outfile = File24;
	MyPictureFile OutFile25;
	OutFile25.type = 2;
	FILE * File25 = fopen("out25.bmp", "w");
	OutFile25.outfile = File25;
	MyPictureFile OutFile26;
	OutFile26.type = 2;
	FILE * File26 = fopen("out26.bmp", "w");
	OutFile26.outfile = File26;
	MyPictureFile OutFile27;
	OutFile27.type = 2;
	FILE * File27 = fopen("out27.bmp", "w");
	OutFile27.outfile = File27;
	MyPictureFile OutFile28;
	OutFile28.type = 2;
	FILE * File28 = fopen("out28.bmp", "w");
	OutFile28.outfile = File28;
	MyPictureFile OutFile29;
	OutFile29.type = 2;
	FILE * File29 = fopen("out29.bmp", "w");
	OutFile29.outfile = File29;
	MyPictureFile OutFile30;
	OutFile30.type = 2;
	FILE * File30 = fopen("out30.bmp", "w");
	OutFile30.outfile = File30;
	MyPictureFile OutFile31;
	OutFile31.type = 2;
	FILE * File31 = fopen("out31.bmp", "w");
	OutFile31.outfile = File31;
	MyPictureFile OutFile32;
	OutFile32.type = 2;
	FILE * File32 = fopen("out32.bmp", "w");
	OutFile32.outfile = File32;
	MyPictureFile OutFile33;
	OutFile33.type = 2;
	FILE * File33 = fopen("out33.bmp", "w");
	OutFile33.outfile = File33;
	MyPictureFile OutFile34;
	OutFile34.type = 2;
	FILE * File34 = fopen("out34.bmp", "w");
	OutFile34.outfile = File34;
	MyPictureFile OutFile35;
	OutFile35.type = 2;
	FILE * File35 = fopen("out35.bmp", "w");
	OutFile35.outfile = File35;
	MyPictureFile OutFile36;
	OutFile36.type = 2;
	FILE * File36 = fopen("out36.bmp", "w");
	OutFile36.outfile = File36;
	MyPictureFile OutFile37;
	OutFile37.type = 2;
	FILE * File37 = fopen("out37.bmp", "w");
	OutFile37.outfile = File37;
	MyPictureFile OutFile38;
	OutFile38.type = 2;
	FILE * File38 = fopen("out38.bmp", "w");
	OutFile38.outfile = File38;
	MyPictureFile OutFile39;
	OutFile39.type = 2;
	FILE * File39 = fopen("out39.bmp", "w");
	OutFile39.outfile = File39;

	BMP_PICTURE NewPicture[K];

	//MyPictureFile OutFile;
	//OutFile.type = 2;
	//OutFile.outfile = stdout;
	#pragma omp parallel for
	for (int _ = 0; _ < K; ++_){
		NewPicture[_].header = MyPicture.header;
		NewPicture[_].info = MyPicture.info;
		NewPicture[_].picture.resize((int) NewPicture[_].info.Width);
	}
	#pragma omp parallel for
	for (int i = 0; i < (int) MyPicture.info.Width; ++i){
		for (int _ = 0; _ < K; ++_){
			NewPicture[_].picture[i].resize((int) MyPicture.info.Height);
		}
		for (int j = 0; j < (int) MyPicture.info.Height; ++j){
			for (int _ = 0; _ < K; ++_){
				NewPicture[_][i][j] = White;
				NewPicture[_][i][j].R = 250;
				NewPicture[_][i][j].B = 250;
			}
			int min_dist_c = 256 * 256 * 3;
			int index_min_dist_c;
			for (int _ = 0; _ < K; ++_){
				if (min_dist_c > centers[_].distance(MyPicture[i][j])){
					min_dist_c = centers[_].distance(MyPicture[i][j]);
					index_min_dist_c = _;
				}
			}
			NewPicture[index_min_dist_c][i][j] = MyPicture[i][j];
		}
	}
	
	NewPicture[0].out(OutFile0);
	NewPicture[1].out(OutFile1);
	NewPicture[2].out(OutFile2);
	NewPicture[3].out(OutFile3);
	NewPicture[4].out(OutFile4);
	NewPicture[5].out(OutFile5);
	NewPicture[6].out(OutFile6);
	NewPicture[7].out(OutFile7);
	NewPicture[8].out(OutFile8);
	NewPicture[9].out(OutFile9);
	NewPicture[10].out(OutFile10);
	NewPicture[11].out(OutFile11);
	NewPicture[12].out(OutFile12);
	NewPicture[13].out(OutFile13);
	NewPicture[14].out(OutFile14);
	NewPicture[15].out(OutFile15);
	NewPicture[16].out(OutFile16);
	NewPicture[17].out(OutFile17);
	NewPicture[18].out(OutFile18);
	NewPicture[19].out(OutFile19);
	NewPicture[20].out(OutFile20);
	NewPicture[21].out(OutFile21);
	NewPicture[22].out(OutFile22);
	NewPicture[23].out(OutFile23);
	NewPicture[24].out(OutFile24);
	NewPicture[25].out(OutFile25);
	NewPicture[26].out(OutFile26);
	NewPicture[27].out(OutFile27);
	NewPicture[28].out(OutFile28);
	NewPicture[29].out(OutFile29);
	NewPicture[30].out(OutFile30);
	NewPicture[31].out(OutFile31);
	NewPicture[32].out(OutFile32);
	NewPicture[33].out(OutFile33);
	NewPicture[34].out(OutFile34);
	NewPicture[35].out(OutFile35);
	NewPicture[36].out(OutFile36);
	NewPicture[37].out(OutFile37);
	NewPicture[38].out(OutFile38);
	NewPicture[39].out(OutFile39);

	return 0;
}