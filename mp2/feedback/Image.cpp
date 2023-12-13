
#include"Image.h"

using namespace cs225;

Image::Image():PNG(){}
// Image::Image(Image const & other):PNG(other){}
// Image const & Image::operator= (Image const & other){
    
//     return *this;
// }


void Image::lighten(){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->l <= 0.9){
                this->getPixel(i,j)->l += 0.1;
            }else{
                this->getPixel(i,j)->l = 1;

            }
        }
    }
}
void Image::lighten(double amount){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->l <= 1-amount){
                this->getPixel(i,j)->l += amount;
            }else{
                this->getPixel(i,j)->l = 1;
                

            }
        }
    }
}
void Image::darken(){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->l >= 0.1){
                this->getPixel(i,j)->l -= 0.1;
            }else{
                this->getPixel(i,j)->l = 0;

            }
        }
    }
}
void Image::darken(double amount){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->l >= amount){
                this->getPixel(i,j)->l -= amount;
            }else{
                this->getPixel(i,j)->l = 0;

            }
        }
    }
}
void Image::saturate(){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->s <= 0.9){
                this->getPixel(i,j)->s += 0.1;
            }else{
                this->getPixel(i,j)->s = 1;

            }
        }
    }
}
void Image::saturate(double amount){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->s <= 1-amount){
                this->getPixel(i,j)->s += amount;
            }else{
                this->getPixel(i,j)->s = 1;

            }
        }
    }
}
void Image::desaturate(){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->s >= 0.1){
                this->getPixel(i,j)->s -= 0.1;
            }else{
                this->getPixel(i,j)->s = 0;

            }
        }
    }
}
void Image::desaturate(double amount){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            if (this->getPixel(i,j)->s >= amount){
                this->getPixel(i,j)->s -= amount;
            }else{
                this->getPixel(i,j)->s = 0;

            }
        }
    }
}
void Image::grayscale(){
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            this->getPixel(i,j)->s = 0;
        }
    }
}
void Image::rotateColor(double degrees){
    if (degrees < 0 ){
        degrees+=360;
    }
    for (unsigned int i= 0; i< this->width(); i++){
        for (unsigned int j=0; j<this->height(); j++){
            this->getPixel(i,j)->h = this->getPixel(i,j)->h+degrees >=360 ?  this->getPixel(i,j)->h+degrees-360 :this->getPixel(i,j)->h+degrees;
        }
    }    

}
void Image::illinify(){

    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            
            if (this->getPixel(x, y)->h>293.5){this->getPixel(x, y)->h=11;}
            else if(this->getPixel(x, y)->h<=293.5 && this->getPixel(x, y)->h>113.5){this->getPixel(x, y)->h=216;}
            else if(this->getPixel(x, y)->h<=113.5){this->getPixel(x, y)->h=11;}
    }
  }
}

void Image::scale(double factor){
    Image scale_img(*this);
    resize((unsigned int)width()*factor,(unsigned int)height()*factor);
    for (unsigned int x = 0; x < (unsigned int)width(); x++) {
        for (unsigned int y = 0; y < (unsigned int)height(); y++) {
            unsigned int x_ = (unsigned int)x/factor;
            unsigned int y_ = (unsigned int)y/factor;
            HSLAPixel * newPixel = this->getPixel(x,y);
            newPixel->h = scale_img.getPixel(x_,y_)->h;
            newPixel->a = scale_img.getPixel(x_,y_)->a;
            newPixel->s = scale_img.getPixel(x_,y_)->s;
            newPixel->l = scale_img.getPixel(x_,y_)->l;
        }
    }
}

    


void Image::scale(unsigned w, unsigned h){
    Image scale_img(*this);
    this->resize(w,h);
    
    for (unsigned int x = 0; x < w; x++) {
        for (unsigned int y = 0; y < h; y++) {
            double factor1 = (double)w/scale_img.width();
            double factor2 = (double)h/scale_img.height(); 

            unsigned int x_ = (unsigned int)x/factor1;
            unsigned int y_ = (unsigned int)y/factor2;
            HSLAPixel * newPixel = this->getPixel(x,y);
            newPixel->h = scale_img.getPixel(x_,y_)->h;
            newPixel->a = scale_img.getPixel(x_,y_)->a;
            newPixel->s = scale_img.getPixel(x_,y_)->s;
            newPixel->l = scale_img.getPixel(x_,y_)->l;
        }
    }
}