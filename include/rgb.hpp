
#ifndef RGB_HPP
#define RGB_HPP

#define MASK_BLUE        0xFF0000
#define GET_BLUE(clr) ((clr & MASK_BLUE) >> 16)

#define MASK_GREEN      0xFF00
#define GET_GREEN(clr) ((clr & MASK_GREEN) >> 8)

#define MASK_RED       0xFF
#define GET_RED(clr) (clr & MASK_RED)

#define R_G_B(r,g,b) (((b&0xFF) << 16) | ((g&0xFF) << 8) | (r & 0xFF))
#define BGR(x) ((x & 0x00FF00) | ((x & 0xFF0000)>>16) | ((x & 0x0000FF) << 16))

#endif
