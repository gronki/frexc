#include <space.hpp>




Space::Space (int scrW, int scrH, l_double cX, l_double cY, l_double vpW) {
        this->scrW = scrW;
        this->scrH = scrH;
        this->cX = cX;
        this->cY = cY;
        this->vpW = vpW;
        vpH = vpW * scrH / (scrW*1.0f);

        aX = cX - vpW/2.0f;
        aY = cY + vpH/2.0f;
}


l_double Space::get_pixel_size () {
        return (to_real_x (1) - to_real_x(0));
}

l_double Space::to_real_x (int x) {
        return aX + (l_double)x * vpW / (l_double)scrW;
}

l_double Space::to_real_y (int y) {
        return aY - (l_double)y * vpH / (l_double)scrH;
}

int Space::to_screen_x (l_double x) {
        return (int)((x - aX)*scrW/vpW);
}

int Space::to_screen_y (l_double y) {
        return (int)((aY - y)*scrH/vpH);
}
