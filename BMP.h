#include <stdint.h>
#include <vector>

#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <unistd.h>

using namespace std;

struct Color{
	uint8_t B, G, R;

	bool operator == (Color y){
		return B == y.B && G == y.G && R == y.R;
	}
};

struct BITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;

	void in(MyPictureFile infile){
		bfType = infile.in16_t(false);
		if (bfType == 16973){ //424D
			bfSize = infile.in32_t(true);
			cerr << "bfSize: " << hex << bfSize << " " << dec << bfSize << endl;
			bfReserved1 = infile.in16_t(true);
			cerr << "bfReserved1: " << hex << bfReserved1 << " " << dec << bfReserved1 << endl;
			bfReserved2 = infile.in16_t(true);
			cerr << "bfReserved2: " << hex << bfReserved2 << " " << dec << bfReserved2 << endl;
			bfOffBits = infile.in32_t(true);
			cerr << "bfOffBits: " << hex << bfOffBits << " " << dec << bfOffBits << endl;
		}
	}

	void out(MyPictureFile outfile){
		outfile.out16_t(bfType, false);
		if (bfType == 16973){
			cerr << endl << endl;
			outfile.out32_t(bfSize, true);
			cerr << "bfSize: " << hex << bfSize << " " << dec << bfSize << endl;
			outfile.out16_t(bfReserved1, true);
			outfile.out16_t(bfReserved2, true);
			outfile.out32_t(bfOffBits, true);
			cerr << "bfReserved1: " << hex << bfReserved1 << " " << dec << bfReserved1 << endl;
			cerr << "bfReserved2: " << hex << bfReserved2 << " " << dec << bfReserved2 << endl;
			cerr << "bfOffBits: " << hex << bfOffBits << " " << dec << bfOffBits << endl;
		}
	}
};

struct BITMAPINFO{
	uint32_t Size; //siz of this block
	uint32_t Width;
	uint32_t Height;
	uint16_t Planes;
	uint16_t BitCount;
	uint32_t Compression;
	uint32_t SizeImage;
	uint32_t XPelsPerMeter;
	uint32_t YPelsPerMeter;
	uint32_t ClrUsed;
	uint32_t ClrImportant;
	vector<unsigned char> something;

	void in(MyPictureFile infile, bool reverse){
		Size = infile.in32_t(reverse);
		cerr << "Size: " << Size << endl;
		Width = infile.in32_t(reverse);
		cerr << "Width: " << hex << Width << " " << dec << Width <<endl;
		Height = infile.in32_t(reverse);
		cerr << "Height: " << hex << Height << " " << dec << Height <<endl;
		Planes = infile.in16_t(reverse);
		cerr << "Planes: " << hex << Planes << " " << dec << Planes <<endl;
		BitCount = infile.in16_t(reverse);
		cerr << "BitCount: " << hex << BitCount << " " << dec << BitCount <<endl;
		Compression = infile.in32_t(reverse);
		cerr << "Compression: " << hex << Compression << " " << dec << Compression <<endl;
		SizeImage = infile.in32_t(reverse);
		cerr << "SizeImage: " << hex << SizeImage << " " << dec << SizeImage <<endl;
		XPelsPerMeter = infile.in32_t(reverse);
		cerr << "XPelsPerMeter: " << hex << XPelsPerMeter << " " << dec << XPelsPerMeter <<endl;
		YPelsPerMeter = infile.in32_t(reverse);
		cerr << "YPelsPerMeter: " << hex << YPelsPerMeter << " " << dec << YPelsPerMeter <<endl;
		ClrUsed = infile.in32_t(reverse);
		cerr << "ClrUsed: " << hex << ClrUsed << " " << dec << ClrUsed <<endl;
		ClrImportant = infile.in32_t(reverse);
		cerr << "ClrImportant: " << hex << ClrImportant << " " << dec << ClrImportant <<endl;
		if (Size == 40)
			return;
	}

	void out(MyPictureFile outfile, bool reverse){
		outfile.out32_t(Size, reverse);
		outfile.out32_t(Width, reverse);
		outfile.out32_t(Height, reverse);
		outfile.out16_t(Planes, reverse);
		outfile.out16_t(BitCount, reverse);
		outfile.out32_t(Compression, reverse);
		outfile.out32_t(SizeImage, reverse);
		outfile.out32_t(XPelsPerMeter, reverse);
		outfile.out32_t(YPelsPerMeter, reverse);
		outfile.out32_t(ClrUsed, reverse);
		outfile.out32_t(ClrImportant, reverse);
		if (Size == 40)
			return;
	}
};

struct BMP_PICTURE{
	BITMAPFILEHEADER header;
	BITMAPINFO info;
	vector<vector<Color> > picture;

	vector<Color> & operator [](int n){
		return picture[n];
	}

	void in(MyPictureFile infile){
		header.in(infile);
		info.in(infile, true);
		int tmp = ((((info.Width * 3) + 3) >> 2) << 2) - info.Width * 3;
		picture.resize(info.Width);
		for (int i = 0; i < info.Width; ++i){
			picture[i].resize(info.Height);
		}
		for (int i = 0; i < info.Height; ++i){
			for (int j = 0; j < info.Width; ++j){
				picture[j][i].B = infile.inu8_t();
				picture[j][i].G = infile.inu8_t();
				picture[j][i].R = infile.inu8_t();
			}
			for (int _ = 0; _ < tmp; ++_){
				infile.in();
			}
		}
	}

	void out(MyPictureFile outfile){
		header.out(outfile);
		info.out(outfile, true);
		int tmp = ((((info.Width * 3) + 3) >> 2) << 2) - info.Width * 3;
		for (int i = 0; i < info.Height; ++i){
			for (int j = 0; j < info.Width; ++j){
				outfile.outu8_t(picture[j][i].B);
				outfile.outu8_t(picture[j][i].G);
				outfile.outu8_t(picture[j][i].R);
			}
			for (int _ = 0; _ < tmp; ++_){
				outfile.outu8_t(0);
			}
		}
	}

	int DrawLine(int x1, int y1, int x2, int y2, Color C){
		const int X[] = {1, 0, -1, 0};
		const int Y[] = {0, 1, 0, -1};
		//cerr << "_________\n";
		if (x1 < 0 || x2 < 0 || x1 >= info.Width || x2 >= info.Width)
			return -1;
		if (y1 < 0 || y2 < 0 || y1 >= info.Height || y2 >= info.Height)
			return -1;
		//cerr << "x1 y1 x2 y2 " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
		int nowx = x1;
		int nowy = y1;
		int distance1 = (x2 - nowx) * (x2 - nowx) + (y2 - nowy) * (y2 - nowy);
		int distance2 = info.Height * info.Height + info.Width * info.Width + 1;
		int newdistance;
		int distance;
		while (distance > 0){
			//cerr << "distance: " << distance << endl;
			//cerr << "y2 = " << y2 << endl;
			//sleep(1);
			int ans1 = 0;
			int ans2 = 0;
			for (int i = 0; i < 4; ++i){
				int newx = nowx + X[i];
				int newy = nowy + Y[i];
				newdistance = (x2 - newx) * (x2 - newx) + (y2 - newy) * (y2 - newy);
				//cerr << "newdistance, i " << newdistance << " " << i << endl;
				if (newdistance < distance1){
					distance2 = distance1;
					distance1 = newdistance;
					ans2 = ans1;
					ans1 = i;
				}
				else{
					if (newdistance < distance2){
						ans2 = i;
						distance2 = newdistance;
					}
				}
			}
			nowx += X[ans1];
			nowy += Y[ans1];
			//cerr << "nowx, nowy" << nowx << " " << info.Width << " " << nowy << " " << info.Height << endl;
			//cerr << "x2, y2: " << x2 << " " << y2 << endl;
			//cerr << "distance: " << distance << endl;
			distance = (x2 - nowx) * (x2 - nowx) + (y2 - nowy) * (y2 - nowy);
			picture[nowx][nowy] = C;
		}
	}
};