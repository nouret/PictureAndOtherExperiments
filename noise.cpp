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

int main(){

	MyPictureFile InFile;
	InFile.type = 2;
	InFile.infile = stdin;

	BMP_PICTURE MyPicture;
	MyPicture.in(InFile);

	MyPictureFile OutFile;
	OutFile.type = 2;
	OutFile.outfile = stdout;
	//BMP_PICTURE NewPicture(640, 480, 921654, 921600);
	BMP_PICTURE NewPicture;
	NewPicture.header = MyPicture.header;
	NewPicture.info = MyPicture.info;
	NewPicture.picture.resize((int) NewPicture.info.Width);
	DRandom Nomber;
	for (int i = 0; i < (int) NewPicture.info.Width; ++i){
		NewPicture.picture[i].resize((int) NewPicture.info.Height);
		for (int j = 0; j < (int) NewPicture.info.Height; ++j){
			NewPicture[i][j].R = (Nomber.RangeRandom(0, 256, 25) + MyPicture[i][j].R) / 2;
			NewPicture[i][j].G = (Nomber.RangeRandom(0, 256, 25) + MyPicture[i][j].G) / 2;
			NewPicture[i][j].B = (Nomber.RangeRandom(0, 256, 25) + MyPicture[i][j].B) / 2;
		}
	}
	NewPicture.out(OutFile);
	return 0;
}