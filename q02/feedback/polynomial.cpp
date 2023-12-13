#include <iostream>
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial(){
    order_=1;
    a_ = new float[2];
    a_[0]=1;
    a_[1]=1;
}

Polynomial::Polynomial(unsigned int order){
    order_=order;
    a_ = new float[order+1];
    for (unsigned int x=0; x<order+1; x++){
        a_[x] = 1; 
    }
}

Polynomial::Polynomial(Polynomial const &p){
    a_ = NULL;
    copy_(p);
}

Polynomial::~Polynomial(){
    destroy_();
}
// Default constructor
// constructs a first-order polynomial with all coefficients set to 1.

// One-parameter constructor
// constructs a polynomial of user-supplied order with all coefficients set to 1.

// helper function to copy - IMPLEMENT ME
void Polynomial::copy_(const Polynomial &p) {
    delete[] a_;

    order_ = p.order_;
    a_ = new float[order_+1];
    for (unsigned int x=0; x<order_+1;x++){
        a_[x]= p.a_[x];
    }
}

// helper function to destroy - IMPLEMENT ME
void Polynomial::destroy_() {
    delete[] a_;
}



Polynomial const & Polynomial::operator=(Polynomial const &p){
    if (this != &p){copy_(p);}
    return *this;
}


// Copy constructor - must use copy_() function
// constructs a new polynomial that is a copy of an existing polynomial

// Destructor - must use destroy_() function
// destroys a polynomial object

// Assignment operator - must use copy_() function
// assigns rhs Polynomial object to 'this' Polynomial object

// getPolyOrder
// returns the polynomial order

unsigned int Polynomial::getPolyOrder(){
    return order_;
}

// getCoeff
// returns the coefficient of the x^i term in polynomial
// note: If the object does not contain a term with power i (e.g., 
//       i>order_), a coefficient value of zero is returned.

float Polynomial::getCoeff(unsigned int order){
    if(order>order_){return 0;}
    return a_[order];
}


// setCoeff
// If i <= order_, set a term, value*x^i, in a polynomial
bool Polynomial::setCoeff(unsigned int order, float value){
    if (order>order_) {return false;}
    a_[order] = value;
    return true;  
}

// addition operator
// adds two polynomials together and returns a new polynomial 
Polynomial Polynomial::operator+(Polynomial const &p){
    Polynomial old = *this;
    if (this->order_ < p.order_){
        this->order_ = p.order_;
        destroy_();
        this->a_ = new float[order_];
        for (unsigned int x=0;x <old.order_+1; x++){
            this->a_[x]=old.a_[x];
        }
        for (unsigned int x=0;x <order_+1; x++){
            this->a_[x] += p.a_[x];
        }
    }else{
        for (unsigned int x=0;x <order_+1; x++){
            this->a_[x] += p.a_[x];
        }
    }
    return *this;

}

// insertion operator for output
// note: This function has been provided for you -- DO NOT CHANGE IT!
ostream & operator << (ostream &out, const Polynomial& p)
{
    bool printed = false;

    for (int i = p.order_; i >= 0; i--)
    {
        float c = p.a_[i];

        if (c != 0.0)
        {
            if (printed) out << " + ";
            printed = true;
            out << c << "*X^" << i;
        }
    }

    return out;
}
