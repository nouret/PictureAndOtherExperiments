#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>

using namespace std; //is very bad

//void Print(void * )

struct Error{
	string s;
};

struct MyPictureFile{
	int type;
	FILE * infile;
	FILE * outfile;
	istream * instream;
	ostream * outstream;

	unsigned char in(){
		unsigned char c;
		if (type == 1){
			(* instream) >> c;
		}
		if (type == 2){
			fread(&c, 1, 1, infile);
		}
		return c;
	}

	uint8_t inu8_t(){
		uint8_t n;
		unsigned char c;
		c = in();
		n = (uint8_t) c;
		return n;
	}

	void outu8_t(uint8_t n){
		out((unsigned char) n);
	}

	int16_t in16_t(bool reverse){
		int16_t n = 0;
		unsigned char c[2];
		for (int _  = 0; _ < 2; ++_){
			c[_] = in();
		}
		if (reverse){
			for (int _ = 0; _ < 2; ++_){
				n += c[1 - _];
				if (_ < 1)
					n <<= 8;
			}
		}
		else{
			for (int _ = 0; _ < 2; ++_){
				n += c[_];
				if (_ < 1)
					n <<= 8;
			}
		}
		return n;
	}

	int32_t in32_t(bool reverse){
		int32_t n = 0;
		unsigned char c[4];
		for (int _  = 0; _ < 4; ++_){
			c[_] = in();
		}
		if (reverse){
			for (int _ = 0; _ < 4; ++_){
				n += c[3 - _];
				if (_ < 3)
					n <<= 8;
			}
		}
		else{
			for (int _ = 0; _ < 4; ++_){
				n += c[_];
				if (_ < 3)
					n <<= 8;
			}
		}
		return n;
	}

	void out(unsigned char c){
		if (type == 1){
			(* outstream) << c;
		}
		if (type == 2){
			fprintf(outfile, "%c", c);
		}
	}

	void out16_t(int16_t n, bool reverse){
		if (reverse){
			for (int _  = 0; _ < 2; ++_){
				out((unsigned char) (((n / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
		}
		else{
			for (int _  = 1; _ >= 0; --_){
				out((unsigned char) (((n / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
		}
	}

	void out32_t(int32_t n, bool reverse){
		if (reverse){
			for (int _  = 0; _ < 4; ++_){
				out((unsigned char) (((n / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
		}
		else{
			for (int _  = 3; _ >= 0; --_){
				out((unsigned char) (((n / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
		}
	}
};

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
		int tmp = ((((info.Width * 3) + 3) << 2) >> 2) - info.Width * 3;
		picture.resize(info.Height);
		unsigned char c;
		//int tmp = ((((info.Height * 3) + 3) << 2) >> 2) - info.Height * 3;
		//cerr << "| " << dec << info.Height * 3 << " " << ((((info.Height * 3) + 3) << 2) >> 2) - info.Height * 3 << endl;
		cerr << "tmp: " << tmp << endl;
		for (int i = 0; i < info.Height; ++i){
			picture[i].resize(info.Width);
			for (int j = 0; j < info.Width; ++j){
				picture[i][j].B = infile.inu8_t();
				picture[i][j].G = infile.inu8_t();
				picture[i][j].R = infile.inu8_t();
			}
			for (int _ = 0; _ < tmp; ++_){
				infile.in();
			}
		}
	}

	void out(MyPictureFile outfile){
		header.out(outfile);
		info.out(outfile, true);
		//int tmp = ((((info.Height * 3) + 3) << 2) >> 2) - info.Height * 3;
		int tmp = ((((info.Width * 3) + 3) << 2) >> 2) - info.Width * 3;
		//int tmp = 3;
		for (int i = 0; i < info.Height; ++i){
			for (int j = 0; j < info.Width; ++j){
				outfile.outu8_t(picture[i][j].B);
				outfile.outu8_t(picture[i][j].G);
				outfile.outu8_t(picture[i][j].R);
			}
			for (int _ = 0; _ < tmp; ++_){
				outfile.outu8_t(0);
			}
		}
	}
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
	for (int x = 0; x < (int) MyPicture.info.Width; ++x){
		//MyPicture[x].resize(MyPicture.info.y);
		for (int y = 0; y < (int) MyPicture.info.Height; ++y){
			MyPicture[x][y] = NewColor;
			//MyPicture[x][y].R = rand() % (MyPicture[x][y].R + 1);
			//MyPicture[x][y].G = rand() % (MyPicture[x][y].G + 1);
			//MyPicture[x][y].B = rand() % (MyPicture[x][y].B + 1);
		}
	}
	//DFS(MyPicture.picture, StartX, StartY, NewColor);
	/*int x, y;
	for (x = 0; x < (int) MyPicture.info.x / 2; ++x){
		y = (MyPicture.info.x / 2);
	}
	*/ 
	//cerr << MyPicture.info.MySize << endl;
	//fstream fout;
	//fout.open("Без имени(копия).bmp", ios::out | ios::binary);
	//cout << MyPicture << endl;
	MyPicture.out(MyFile);
	return 0;
}