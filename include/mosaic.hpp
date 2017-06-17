
#ifndef MOSAIC_HPP
#define MOSAIC_HPP

#include "ldouble.hpp"
#include "rgb.hpp"

class Mosaic {
protected:
	Mosaic* MC;
	int XS, YS;
	
	int color (float t) {
		int a;
		t = 1 - t;
		if (t >= 0 && t <= 1) {
			a = 255*t;
		} else if (t > 1) {
			a = 255;
		} else {
			a = 0;
		}
		return R_G_B (a,a,a);
	}
	
	virtual int pixel (int x, int y) = 0;
	
	
public:
	Mosaic () : MC(this), XS(0), YS(0) {}
	Moasic (int X, int Y) : XS(X), YS(Y) {}
	
	void import (Mosaic* m) {
		MC = m;
	}
};

class MosaicSpace : public Mosaic {
	
	
#endif
