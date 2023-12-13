#include "StickerSheet.h"
#include "Image.h"

using namespace cs225;

StickerSheet::StickerSheet(){
    Image *pointer_image = new Image();
    picture_ = pointer_image;
    count_ = 0;
    number_ = 0;
    head   = new Sticker[number_];
}


StickerSheet::~StickerSheet(){
    destroy();
}
void StickerSheet::destroy(){
    delete[] head; 
    delete picture_;
}

StickerSheet::StickerSheet(const Image & picture,unsigned max){

    Image *pointer_image = new Image();

    // pointer_image->resize(picture.width(),picture.height());
    *pointer_image = picture;
    picture_=pointer_image;
    count_ = 0;
    number_ = max;
    head   = new Sticker[number_];
}

StickerSheet::StickerSheet(const StickerSheet& other){
    copy(other);
}

StickerSheet const &StickerSheet::operator= (StickerSheet const & other){
    copy(other);
    return *this;
}

void StickerSheet::copy(StickerSheet const & other){
    this->number_=other.number_;
    this->count_=other.count_;
    this->picture_=other.picture_;
    destroy();
    head = new Sticker[number_];
    for (unsigned int i = 0 ;i < count_ ; i++){
        this->head[i] = other.head[i];
    }

}

void StickerSheet::changeMaxStickers(unsigned max){
    Sticker* old_head = head;
    Sticker* new_head = new Sticker[max];
    for(unsigned i = 0; i<number_ ; i++){
        new_head[i] = old_head[i];

    }
    number_ = max;
    delete[] head; 
    head = new_head;
}

int StickerSheet::addSticker(Image & sticker,unsigned x, unsigned y){
    if (number_==count_){return -1;}

    head[count_].x_ = x;
    head[count_].y_ = y;
    head[count_].Sticker_picture = &sticker;
    count_+=1;
    return count_;
}

bool StickerSheet::translate(unsigned index,unsigned x, unsigned y){
    if (index >= count_){return false;}
    head[index].x_ = x;
    head[index].y_ = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if(index >= count_){return;}
    for(unsigned i = index ; i <count_-1 ; i++){
        head[i].x_=head[i+1].x_;
        head[i].y_=head[i+1].y_;
        head[i].Sticker_picture = head[i+1].Sticker_picture; 
    }
    count_-=1;

}
Image* StickerSheet::getSticker	(unsigned index)const{
    if(index >= count_){return nullptr;}
    return head[index].Sticker_picture;
}
Image StickerSheet::render()const{

    Image *new_image = picture_;
    for (unsigned i = 0; i < count_; i++){
        unsigned int x = head[i].Sticker_picture->width();
        unsigned int y = head[i].Sticker_picture->height();
        if (x+head[i].x_>new_image->width()){
            new_image->resize(x+head[i].x_,new_image->height());
        }
        if (y+head[i].y_>new_image->height()){
            new_image->resize(new_image->width(),head[i].y_+y);
        }  
        for (unsigned int k = 0; k<x ; k++){
            for (unsigned int j=0;  j<y ; j++){
                if (head[i].Sticker_picture->getPixel(k,j)->a != 0){
                    cs225::HSLAPixel *en = new_image->getPixel(k+head[i].x_,j+head[i].y_);
                    cs225::HSLAPixel *on = head[i].Sticker_picture->getPixel(k,j);
                    en->a=on->a;
                    en->h=on->h;
                    en->l=on->l;
                    en->s=on->s;
                }
            }
        }
    }
    return *new_image;
}

