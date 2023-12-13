#include <iostream>
#include "cubic.h"

using namespace std;

Cubic::Cubic():Polynomial(3){

}
Cubic::Cubic(float a1,float a2,float a3,float a4): Polynomial(3){
    setCoeff(3,a1);
    setCoeff(2,a2);
    setCoeff(1,a3);
    setCoeff(0,a4);

}


