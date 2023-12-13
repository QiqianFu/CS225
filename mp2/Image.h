#ifndef IMAGE_H
#define IMAGE_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class Image: public cs225::PNG{
    public:
        Image();
        // Image(unsigned w, unsigned h);
        // Image(Image const & other);
        // Image const & operator =(Image const & other);
        // ~Image();
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void grayscale(double degrees);
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w,unsigned h);
    
};









#endif