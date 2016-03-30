struct BITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;

	void in(FILE * in){
		unsigned char c[4];
		bfType = 0;
		for (int _  = 0; _ < 2; ++_){
			fread(&c[_], 1, 1, in);
			bfType += c[_];
			if (_ < 1)
				bfType <<= 8;
		}
		if (bfType == 16973){ //424D
			for (int _ = 0; _ < 4; ++_){
				fread(&c[_], 1, 1, in);
			}
			bfSize = 0;
			for (int _  = 0; _ < 4; ++_){
				bfSize += c[3 - _];
				if (_ < 3)
					bfSize <<= 8;
			}
			for (int _ = 0; _ < 2; ++_){
				fread(&c[_], 1, 1, in);
			}
			bfReserved1 = 0;
			for (int _  = 0; _ < 2; ++_){
				bfReserved1 += c[1 - _];
				if (_ < 1)
					bfReserved1 <<= 8;
			}
			for (int _ = 0; _ < 2; ++_){
				fread(&c[_], 1, 1, in);
			}
			bfReserved2 = 0;
			for (int _  = 0; _ < 2; ++_){
				bfReserved2 += c[1 - _];
				if (_ < 1)
					bfReserved2 <<= 8;
			}
			for (int _ = 0; _ < 4; ++_){
				fread(&c[_], 1, 1, in);
			}
			bfOffBits = 0;
			for (int _  = 0; _ < 4; ++_){
				bfOffBits += c[3 - _];
				if (_ < 3)
					bfOffBits <<= 8;
			}
		}
	}

	void out(FILE * out){
		for (int _  = 1; _ >= 0; --_){
			fprintf(out, "%c", (unsigned char) (((bfType / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
		}
		if (bfType == 16973){
			for (int _  = 0; _ < 4; ++_){
				fprintf(out, "%c", (unsigned char) (((bfSize / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int _  = 0; _ < 2; ++_){
				fprintf(out, "%c", (unsigned char) (((bfReserved1 / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int _  = 0; _ < 2; ++_){
				fprintf(out, "%c", (unsigned char) (((bfReserved2 / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int _  = 0; _ < 4; ++_){
				fprintf(out, "%c", (unsigned char) (((bfOffBits / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
		}
	}
};

struct BITMAPINFO{
	uint32_t size; //siz of this block
	uint32_t x;
	uint32_t y;
	vector<unsigned char> something;

	void in(FILE * in){
		unsigned char c[4];
		if (true){ //4D42
			for (int _ = 0; _ < 4; ++_){
				fread(&c[_], 1, 1, in);
			}
			size = 0;
			for (int _  = 0; _ < 4; ++_){
				size += c[3 - _];
				if (_ < 3)
					size <<= 8;
			}
			for (int _ = 0; _ < 4; ++_){
				fread(&c[_], 1, 1, in);
			}
			x = 0;
			for (int _  = 0; _ < 4; ++_){
				x += c[3 - _];
				if (_ < 3)
					x <<= 8;
			}
			for (int _ = 0; _ < 4; ++_){
				fread(&c[_], 1, 1, in);
			}
			y = 0;
			for (int _  = 0; _ < 4; ++_){
				y += c[3 - _];
				if (_ < 3)
					y <<= 8;
			}
			something.resize(size - 12);
			for (int i = 0; i < size - 12; ++i){
				fread(&something[i], 1, 1, in);
			}
		}
	}

	void out(FILE * out){
		if (true){
			for (int _  = 0; _ < 4; ++_){
				fprintf(out, "%c", (unsigned char) (((size / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int _  = 0; _ < 4; ++_){
				fprintf(out, "%c", (unsigned char) (((x / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int _  = 0; _ < 4; ++_){
				fprintf(out, "%c", (unsigned char) (((y / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8))));
			}
			for (int i = 0; i < (int) something.size(); ++i){
				fprintf(out, "%c", something[i]);
			}
		}
	}
};

struct BMP_PICTURE{
	BITMAPFILEHEADER header;
	BITMAPINFO info;
	vector<vector<Color> > picture;

	vector<Color> operator [](int n){
		return picture[n];
	}

	void in(FILE * in){
		header.in(in);
		info.in(in);
		picture.resize(info.x);
		unsigned char c;
		for (int i = 0; i < info.x; ++i){
			int Y = info.y;
			Y += 3;
			Y >>= 2; //Y % 4 == 0
			Y <<= 2;
			picture[i].resize(Y);
			for (int j = 0; j < Y; ++j){
				fread(&c, 1, 1, in);
				picture[i][j].B = (uint8_t) c;
				fread(&c, 1, 1, in);
				picture[i][j].G = (uint8_t) c;
				fread(&c, 1, 1, in);
				picture[i][j].R = (uint8_t) c;
			}
		}
	}

	void out(FILE * out){
		header.out(out);
		info.out(out);
		for (int i = 0; i < info.x; ++i){
			int Y = info.y;
			Y += 3;
			Y >>= 2; //Y % 4 == 0
			Y <<= 2;
			picture[i].resize(Y);
			for (int j = 0; j < Y; ++j){
				fprintf(out, "%c%c%c", (unsigned char) picture[i][j].B, (unsigned char) picture[i][j].G,
					(unsigned char) picture[i][j].R);
			}
		}
	}
};
