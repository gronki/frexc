
#include <renderer.hpp>

int* FractalRenderer::render (int* bitmap, Space& spc, int samples) {
        int __iterations = iterations;

        l_double a = spc.get_pixel_size ();
        l_double dl = a/samples;

        l_double xx,yy;

        l_double samples_coords[70][2];

        int x, y, i, j, r, g, b, t;
        int W = spc.get_screen_w ();
        int H = spc.get_screen_h ();
        int samples2 = samples*samples;

        i = 0;
        for (x = 0; x < samples; ++x)
        for (y = 0; y < samples; ++y) {
                samples_coords[i][0] = dl/2 - a/2 + x*dl;
                samples_coords[i][1] = dl/2 - a/2 + y*dl;
                ++i;
        }

        for (y = 0; y < H; ++y)
        for (x = 0; x < W; ++x) {
                r=g=b=0;
                xx = spc.to_real_x(x);
                yy = spc.to_real_y(y);
                for (i = 0; i < samples2; ++i) {
                        t = color (xx + samples_coords[i][0],
                                   yy + samples_coords[i][1],
                                   __iterations);
                        r += GET_RED(t);
                        g += GET_GREEN(t);
                        b += GET_BLUE(t);
                }
                r /= samples2; g /= samples2; b /= samples2;
                bitmap[y*W+x] = R_G_B(r,g,b);
        }
        return bitmap;
}

int FractalRenderer::makeclr (float t) {
        return R_G_B (  (int)(GET_RED(color2) + (GET_RED(color1) - GET_RED(color2))*t),
                        (int)(GET_GREEN(color2) + (GET_GREEN(color1) - GET_GREEN(color2))*t),
                        (int)(GET_BLUE(color2) + (GET_BLUE(color1) - GET_BLUE(color2))*t));
}

int MandelbrotRenderer::color (l_double a, l_double b, int iters) {
        int i;
        l_double x = x0, y = y0, x1;
        for (i = 0; i < iters; ++i) {
                x1 = x;
                x = x*x - y*y + a;
                y = 2*x1*y + b;
                if (x*x + y*y > 5)
                        break;
        }
        if (i+1 >= iters && color_fractal) {
                return color0;
        } else {
                float t = i / (float) iters;
                t = 3*t - 3*t*t + t*t*t; //2*t - t*t;
                return makeclr (t);
        }
}


int MandelbrotRendererDist::color (l_double a, l_double b, int iters) {
        int i;
        l_double x = x0, y = y0, x1;
        for (i = 0; i < iters; ++i) {
                x1 = x;
                x = x*x - y*y + a;
                y = 2*x1*y + b;
                if (x*x + y*y > 5)
                        break;
        }
        if (i+1 >= iters && color_fractal) {
                return color0;
        } else {
                float t = sqrt(x*x + y*y)/10.0;
                t = (t>1) ? 1 : t;
               // t = 3*t - 3*t*t + t*t*t; //2*t - t*t;
                return makeclr (t);
        }
}


int JuliaRenderer::color (l_double x, l_double y, int iters) {
        int i; l_double x1;
        for (i = 0; i < iters; ++i) {
                x1 = x;
                x = x*x - y*y + x0;
                y = 2*x1*y + y0;
                if (x*x + y*y > 5)
                        break;
        }
        if (i+1 >= iters && color_fractal) {
                return color0;
        } else {
                float t = i / (float) iters;
                t = 3*t - 3*t*t + t*t*t; // 2*t - t*t;
                return makeclr (t);
        }
}

int JuliaRendererDist::color (l_double x, l_double y, int iters) {
        int i; l_double x1;
        for (i = 0; i < iters; ++i) {
                x1 = x;
                x = x*x - y*y + x0;
                y = 2*x1*y + y0;
                if (x*x + y*y > 5)
                        break;
        }
        if (i+1 >= iters && color_fractal) {
                return color0;
        } else {
                float t = sqrt(x*x + y*y)/10.0;
                t = (t>1) ? 1 : t;
             //   t = 3*t - 3*t*t + t*t*t; //2*t - t*t;
                return makeclr (t);
        }
}


