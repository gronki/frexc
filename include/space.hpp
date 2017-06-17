//---------------------------------------------------------------------------

#ifndef spaceH
#define spaceH
#include <math.h>
//---------------------------------------------------------------------------
#include "ldouble.hpp"

class Space {
protected:
        int scrW, scrH;
        l_double cX, cY, vpW, vpH, aX, aY;
public:
        Space (int scrW, int scrH, l_double cX, l_double cY, l_double vpW);

        int to_screen_x (l_double x);
        int to_screen_y (l_double y);

        inline int get_screen_w () {
                return scrW; }

        inline int get_screen_h () {
                return scrH; }

        l_double to_real_x (int x);
        l_double to_real_y (int y);

        l_double get_pixel_size ();

};
#endif
