#ifndef POLY_H
#define POLY_H

using namespace std;

class Polynomial {

  private:
    unsigned int order_;    // polynomial order
    float *a_;              // polynomial coefficients

    



    void copy_(const Polynomial &p);   // helper function to copy 
    void destroy_();                   // helper function to destroy

  public:
    Polynomial();
    Polynomial(unsigned int order);
    Polynomial(Polynomial const &p);
    ~Polynomial();
    Polynomial const & operator= (Polynomial const &p);
    Polynomial operator+ (Polynomial const &p);
    unsigned int getPolyOrder();
    bool setCoeff(unsigned int order, float value);
    float getCoeff(unsigned int order);

    // Default constructor
    // constructs a first-order polynomial with all coefficients set to 1.

    // One-parameter constructor
    // constructs a polynomial of user-supplied order with all coefficients set to 1.

    // Copy constructor - must use copy_() function
    // constructs a new polynomial that is a copy of an existing polynomial

    // Destructor - must use destroy_() function
    // destroys a polynomial object

    // Assignment operator - must use copy_() function
    // assigns rhs Polynomila object to 'this' Polynomila object

    // addition operator
    // adds two polynomials together and returns a new polynomial 

    // getPolyOrder
    // returns the polynomial order

    // getCoeff
    // returns the coefficient of the x^i term in polynomial
    // note: If the object does not contain a term with power i (e.g., 
    //       i>order_), a coefficient value of zero is returned.

    // setCoeff
    // If i <= order_, set a term, value*x^i, in a polynomial

    // insertion operator for output
    // note: This function has been provided for you -- DO NOT CHANGE IT!
    friend ostream& operator<< (ostream& os, const Polynomial &p);

};

#endif
