#include <stdint.h>
#include <vector>

#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <vector>

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
		cerr << (int) picture[5][5].R << " " << (int) picture[5][5].G << " " << (int) picture[5][5].B << " |" <<  endl;
	}
};