/**
 * @file StickerSheet.cpp
 *
 * @author Howie Liu
 * @date Fri Mar 17 3:21:15 AM
 */

#include "StickerSheet.h"

namespace cs225 {

void StickerSheet::copy_(const StickerSheet& other) {
    base_ = new Image(*other.base_);
    max_ = other.max_;
    stickers_ = new Image*[max_]();
    ratio     = new double[max_];
    x_= new unsigned[max_];
    y_= new unsigned[max_];
    for (unsigned i = 0; i < max_; ++i) {
        if (other.stickers_[i] != nullptr) {
            stickers_[i] = new Image(*other.stickers_[i]);
            ratio[i] = other.ratio[i];
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
        }
    }
}

void StickerSheet::destroy_() {
    if (max_ != 0) {
        delete[] y_;
        y_ = nullptr;
        delete[] x_;
        x_ = nullptr;
        for (unsigned i = 0; i < max_; ++i) {
            if (stickers_[i] != nullptr) {
                delete stickers_[i];
            }
        }
        delete[] stickers_;
        delete[] ratio;
        ratio = nullptr;
        stickers_ = nullptr;
    }
    delete base_;
    base_ = nullptr;
}

StickerSheet::StickerSheet()
    : base_(new Image),
      max_(0),
      ratio(nullptr),
      stickers_(nullptr),
      x_(nullptr),
      y_(nullptr) {}

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    base_ = new Image(picture);
    max_ = max;
    if (max != 0) {
        stickers_ = new Image*[max]();
        ratio     = new double[max];
        x_ = new unsigned[max];
        y_ = new unsigned[max];
    } else {
        ratio = nullptr;
        stickers_ = nullptr;
        x_ = nullptr;
        y_ = nullptr;
    }
}

StickerSheet::~StickerSheet() {
    destroy_();
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    copy_(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    if (this != &other) {
        destroy_();
        copy_(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max != 0) {
        Image** new_stickers = new Image*[max]();
        double* new_ratio = new double[max_];
        unsigned* new_x = new unsigned[max];
        unsigned* new_y = new unsigned[max];
        for (unsigned i = 0; i < max && i < max_; ++i) {
            if (stickers_[i] != nullptr) {
                new_stickers[i] = new Image(*stickers_[i]);
                new_ratio[i]= ratio[i];
                new_x[i] = x_[i];
                new_y[i] = y_[i];
                delete stickers_[i];
                stickers_[i] = nullptr;
            }
        }
        if (max_ != 0) {
            delete[] y_;
            delete[] x_;
            delete[] stickers_;
            delete[] ratio;
        } 
        y_ = new_y;
        x_ = new_x;
        ratio = new_ratio;
        stickers_ = new_stickers;
    } else {
        if (max_ != 0) {
            delete[] y_;
            y_ = nullptr;
            delete[] x_;
            x_ = nullptr;
            delete[] ratio;
            ratio = nullptr;
            delete[] stickers_;
            stickers_ = nullptr;
        }
    }
    max_ = max;
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y, double ratio) {
    unsigned index = 0;
    for (; index < max_ && stickers_[index] != nullptr; ++index);
    if (index == max_) {
        return -1;
    } else {
        stickers_[index] = new Image(sticker);
        this->ratio[index] = ratio;
        x_[index] = x;
        y_[index] = y;
        return index;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= max_ || stickers_[index] == nullptr) {
        return false;
    } else {
        x_[index] = x;
        y_[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < max_ && stickers_[index] != nullptr) {
        delete stickers_[index];
        ratio[index] = 0;
        stickers_[index] = nullptr;
    }
}

Image* StickerSheet::getSticker(unsigned index) const {
    return index < max_ ? stickers_[index] : nullptr;
}

Image StickerSheet::render() const {
    unsigned int w_out = base_->width();
    unsigned int h_out = base_->height();
    unsigned index;
    for (index = 0; index < max_; ++index) {
        if (stickers_[index] != nullptr) {

            stickers_[index]->scale(ratio[index]);

            if (stickers_[index]->width() + x_[index] > w_out) {
                w_out = stickers_[index]->width() + x_[index];
            }
            if (stickers_[index]->height() + y_[index] > h_out) {
                h_out = stickers_[index]->height() + y_[index];
            }
        }
    }
    Image output = Image(w_out, h_out);
    HSLAPixel* output_pixel;
    HSLAPixel* base_pixel;
    HSLAPixel* sticker_pixel;
    unsigned x, y;
    // copy base to output
    for (x = 0; x < base_->width(); ++x) {
        for (y = 0; y < base_->height(); ++y) {
            base_pixel = base_->getPixel(x, y);
            output_pixel = output.getPixel(x, y);
            *output_pixel = *base_pixel;
        }
    }
    // loop over every sticker
    for (index = 0; index < max_; ++index) {
        // only do so if non-empty
        if (stickers_[index] != nullptr) {
            Image* sticker = stickers_[index];
            // loop over every pixel
            for (x = 0; x < sticker->width(); ++x) {
                for (y = 0; y < sticker->height(); ++y) {
                    sticker_pixel = sticker->getPixel(x, y);
                    // alpha is not 0
                    if (sticker_pixel->a > 1e-6) {
                        output_pixel =
                            output.getPixel(x + x_[index], y + y_[index]);
                        *output_pixel = *sticker_pixel;
                    }
                }
            }
        }
    }
    return output;
}

}; // cs225 namespace