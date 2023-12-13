/**
 * @file PNG.h
 *
 * @author CS 225: Data Structures
 */

#ifndef HSLAPixel_H
#define HSLAPixel_H




using namespace std;

namespace cs225 {
    class HSLAPixel{
        public:
            double s,h,l,a;
            HSLAPixel();
            HSLAPixel(double h,double s,double l);
            HSLAPixel(double h,double s,double l,double a);

    };
}
#endif
