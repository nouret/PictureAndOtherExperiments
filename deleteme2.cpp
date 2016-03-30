
istream & operator >>(istream & is, BITMAPFILEHEADER & b){
	unsigned char c[4];
	b.bfType = 0;
	for (int _  = 0; _ < 2; ++_){
		is >> c[_];
		cerr << "Print chars: " << hex << (int) c[_] << endl;
		b.bfType += c[_];
		if (_ < 1)
			b.bfType <<= 8;
	}
	cerr << "b.bfType: " << hex << b.bfType << " = " << dec << b.bfType << endl;
	if (b.bfType == 16973){ //424D
		cerr << "All is ok, I am 424D\n";
		for (int _ = 0; _ < 4; ++_){
			is >> c[_];
			cerr << "Print chars: " << hex << (int) c[_] << endl;
		}
		b.bfSize = 0;
		for (int _  = 0; _ < 4; ++_){
			b.bfSize += c[3 - _];
			if (_ < 3)
				b.bfSize <<= 8;
		}
		cerr << "bfSize: " << hex << b.bfSize << endl;
		for (int _ = 0; _ < 2; ++_){
			is >> c[_];
			cerr << "Print chars: " << hex << (int) c[_] << endl;
		}
		b.bfReserved1 = 0;
		for (int _  = 0; _ < 2; ++_){
			b.bfReserved1 += c[1 - _];
			if (_ < 1)
				b.bfReserved1 <<= 8;
		}
		for (int _ = 0; _ < 2; ++_){
			is >> c[_];
			cerr << "Print chars: " << hex << (int) c[_] << endl;
		}
		b.bfReserved2 = 0;
		for (int _  = 0; _ < 2; ++_){
			b.bfReserved2 += c[1 - _];
			if (_ < 1)
				b.bfReserved2 <<= 8;
		}
		cerr << "Res1: " << b.bfReserved1 << " Res2: " << b.bfReserved2 << endl;
		for (int _ = 0; _ < 4; ++_){
			is >> c[_];
			cerr << "Print chars: " << hex << (int) c[_] << endl;
		}
		b.bfOffBits = 0;
		for (int _  = 0; _ < 4; ++_){
			b.bfOffBits += c[3 - _];
			if (_ < 3)
				b.bfOffBits <<= 8;
		}
	}
	return is;
}

ostream & operator <<(ostream & os, BITMAPFILEHEADER const & b){
	for (int _  = 1; _ >= 0; --_){
		os << (unsigned char) (((b.bfType / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
	}
	if (b.bfType == 16973){
		for (int _  = 0; _ < 4; ++_){
			os << (unsigned char) (((b.bfSize / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int _  = 0; _ < 2; ++_){
			os << (unsigned char) (((b.bfReserved1 / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int _  = 0; _ < 2; ++_){
			os << (unsigned char) (((b.bfReserved2 / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int _  = 0; _ < 4; ++_){
			os << (unsigned char) (((b.bfOffBits / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
	}
	return os;
}

istream & operator >>(istream & is, BITMAPINFO & b){
	unsigned char c[4];
	if (true){ //4D42
		for (int _ = 0; _ < 4; ++_){
			is >> c[_];
		}
		b.size = 0;
		for (int _  = 0; _ < 4; ++_){
			b.size += c[3 - _];
			if (_ < 3)
				b.size <<= 8;
		}
		for (int _ = 0; _ < 4; ++_){
			is >> c[_];
		}
		b.x = 0;
		cerr << "x: " << b.x << endl;
		for (int _  = 0; _ < 4; ++_){
			b.x += c[3 - _];
			if (_ < 3)
				b.x <<= 8;
		}
		for (int _ = 0; _ < 4; ++_){
			is >> c[_];
		}
		b.y = 0;
		for (int _  = 0; _ < 4; ++_){
			b.y += c[3 - _];
			if (_ < 3)
				b.y <<= 8;
		}
		b.something.resize(b.size - 12);
		for (int i = 0; i < b.size - 12; ++i){
			is >> b.something[i];
		}
	}
	return is;
}

ostream & operator <<(ostream & os, BITMAPINFO const & b){
	if (true){
		for (int _  = 0; _ < 4; ++_){
			os << (unsigned char) (((b.size / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int _  = 0; _ < 4; ++_){
			os << (unsigned char) (((b.x / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int _  = 0; _ < 4; ++_){
			os << (unsigned char) (((b.y / (1 << (8 * _))) + (1 << (8 * _ + 8))) % (1 << (8 * _ + 8)));
		}
		for (int i = 0; i < (int) b.something.size(); ++i){
			os << b.something[i];
		}
	}
	return os;
}

istream & operator >>(istream & is, BMP_PICTURE & b){
	is >> b.header;
	is >> b.info;
	b.picture.resize(b.info.x);
	unsigned char c;
	for (int i = 0; i < b.info.x; ++i){
		b.picture[i].resize(b.info.y);
		int Y = b.info.y;
		Y += 3;
		Y >>= 2; //Y % 4 == 0
		Y <<= 2;
		b.picture[i].resize(Y);
		for (int j = 0; j < Y; ++j){
			is >> c;
			b.picture[i][j].B = (uint8_t) c;
			is >> c;
			b.picture[i][j].G = (uint8_t) c;
			is >> c;
			b.picture[i][j].R = (uint8_t) c;
		}
	}
	return is;
}

ostream & operator <<(ostream & os, BMP_PICTURE & b){
	os << b.header << b.info;
	for (int i = 0; i < b.info.x; ++i){
		int Y = b.info.y;
		Y += 3;
		Y >>= 2; //Y % 4 == 0
		Y <<= 2;
		for (int j = 0; j < Y; ++j){
			os << (unsigned char) b.picture[i][j].B << (unsigned char) b.picture[i][j].G << (unsigned char) b.picture[i][j].R;
		}
	}
	return os;
}
