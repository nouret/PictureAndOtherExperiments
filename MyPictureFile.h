#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdint.h>

using namespace std;

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