//---------------------------------------------------------------------------

#ifndef rendererH
#define rendererH

#include <math.h>

#include "space.hpp"
#include "ldouble.hpp"
#include "rgb.hpp"

//---------------------------------------------------------------------------

class FractalRenderer {
protected:
        virtual int color (l_double x, l_double y, int iters) = 0;
        int makeclr (float t);
public:
        int* render (int* bitmap, Space& spc, int sampling);
        int iterations;
        int color0, color1, color2;
        bool color_fractal;
        l_double x0, y0;

        FractalRenderer (l_double x, l_double y, int iters = 150)
                : iterations (iters), color_fractal(0),
                color0(0), color1(0), color2(0xFFFFFF),
                x0(x), y0(y) { }
};

class MandelbrotRenderer : public FractalRenderer {
protected:
        int color (l_double x, l_double y, int iters);
public:
        MandelbrotRenderer (l_double x, l_double y, int iters)
               : FractalRenderer (x,y,iters)   {   }
};


class MandelbrotRendererDist : public FractalRenderer {
protected:
        int color (l_double x, l_double y, int iters);
public:
        MandelbrotRendererDist (l_double x, l_double y, int iters)
               : FractalRenderer (x,y,iters)   {   }
};


class JuliaRenderer : public FractalRenderer {
protected:
        int color (l_double x, l_double y, int iters);
public:
        JuliaRenderer (l_double x, l_double y, int iters) 
               : FractalRenderer (x,y,iters)  {   }
};

class JuliaRendererDist : public FractalRenderer {
protected:
        int color (l_double x, l_double y, int iters);
public:
        JuliaRendererDist (l_double x, l_double y, int iters) 
               : FractalRenderer (x,y,iters)  {   }
};

#endif
