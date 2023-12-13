#ifndef STICKERSHEET_H
#define STICKERSHEET_H


#include "Image.h"

using namespace cs225;


class StickerSheet{
    public:
        StickerSheet();
        StickerSheet(const Image & picture,unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet& other);
        const StickerSheet& operator=	(const StickerSheet & other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image & sticker,unsigned x, unsigned y);
        bool translate(unsigned index,unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index)const;
        Image render()const;
        void copy(StickerSheet const & other);
        void destroy();
    private:
        unsigned number_;
        unsigned count_;
        Image* picture_;
        struct Sticker{
            Image *Sticker_picture;
            unsigned x_;
            unsigned y_;
            Sticker():Sticker_picture(nullptr),x_(0),y_(0){};
        };
        Sticker* head; 
};




#endif
