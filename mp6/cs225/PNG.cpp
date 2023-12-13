/**
 * @file PNG.cpp
 * Implementation of a simple PNG class using HSLAPixels and the lodepng PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>
#include "lodepng/lodepng.h"
#include "PNG.h"
#include "RGB_HSL.h"
#include "../tileimage.h"

namespace cs225 {
  void PNG::_copy(PNG const & other) {
    // Clear self
    delete[] imageData_;

    // Copy `other` to self
    width_ = other.width_;
    height_ = other.height_;
    imageData_ = new HSLAPixel[width_ * height_];
    for (unsigned i = 0; i < width_ * height_; i++) {
      imageData_[i] = other.imageData_[i];
    }
  }

  PNG::PNG() {
    width_ = 0;
    height_ = 0;
    imageData_ = NULL;
  }

  PNG::PNG(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
    imageData_ = new HSLAPixel[width * height];
  }

  PNG::PNG(PNG const & other) {
    imageData_ = NULL;
    _copy(other);
  }

  PNG::~PNG() {
    delete[] imageData_;
  }

  PNG const & PNG::operator=(PNG const & other) {
    if (this != &other) { _copy(other); }
    return *this;
  }

  bool PNG::operator==(PNG const & other) const {
    if (width_ != other.width_) { return false; }
    if (height_ != other.height_) { return false; }

    for (unsigned i = 0; i < width_ * height_; i++) {
      HSLAPixel & p1 = imageData_[i];
      HSLAPixel & p2 = other.imageData_[i];
      if (p1 != p2) { return false; }
    }

    return true;
  }

  bool PNG::operator!=(PNG const & other) const {
    return !(*this == other);
  }

  HSLAPixel & PNG::getPixel(unsigned int x, unsigned int y) const {
    if (width_ == 0 || height_ == 0) {
      cerr << "ERROR: Call to cs225::PNG::getPixel() made on an image with no pixels." << endl;
      assert(width_ > 0);
      assert(height_ > 0);
    }

    if (x >= width_) {
      cerr << "WARNING: Call to cs225::PNG::getPixel(" << x << "," << y << ") tries to access x=" << x
          << ", which is outside of the image (image width: " << width_ << ")." << endl;
      cerr << "       : Truncating x to " << (width_ - 1) << endl;
      x = width_ - 1;
    }

    if (y >= height_) {
      cerr << "WARNING: Call to cs225::PNG::getPixel(" << x << "," << y << ") tries to access y=" << y
          << ", which is outside of the image (image height: " << height_ << ")." << endl;
      cerr << "       : Truncating y to " << (height_ - 1) << endl;
      y = height_ - 1;
    }

    unsigned index = x + (y * width_);
    return imageData_[index];
  }

  bool PNG::readFromFile(string const & fileName) {
    vector<unsigned char> byteData;
    unsigned error = lodepng::decode(byteData, width_, height_, fileName);

    if (error) {
      cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << endl;
      return false;
    }

    delete[] imageData_;
    imageData_ = new HSLAPixel[width_ * height_];

    for (unsigned i = 0; i < byteData.size(); i += 4) {
      rgbaColor rgb;
      rgb.r = byteData[i];
      rgb.g = byteData[i + 1];
      rgb.b = byteData[i + 2];
      rgb.a = byteData[i + 3];

      hslaColor hsl = rgb2hsl(rgb);
      HSLAPixel & pixel = imageData_[i/4];
      pixel.h = hsl.h;
      pixel.s = hsl.s;
      pixel.l = hsl.l;
      pixel.a = hsl.a;
    }

    return true;
  }

  bool PNG::writeToFile(string const & fileName) {
    unsigned char *byteData = new unsigned char[width_ * height_ * 4];

    for (unsigned i = 0; i < width_ * height_; i++) {
      hslaColor hsl;
      hsl.h = imageData_[i].h;
      hsl.s = imageData_[i].s;
      hsl.l = imageData_[i].l;
      hsl.a = imageData_[i].a;

      rgbaColor rgb = hsl2rgb(hsl);

      byteData[(i * 4)]     = rgb.r;
      byteData[(i * 4) + 1] = rgb.g;
      byteData[(i * 4) + 2] = rgb.b;
      byteData[(i * 4) + 3] = rgb.a;
    }

    unsigned error = lodepng::encode(fileName, byteData, width_, height_);
    if (error) {
      cerr << "PNG encoding error " << error << ": " << lodepng_error_text(error) << endl;
    }

    delete[] byteData;
    return (error == 0);
  }

  unsigned int PNG::width() const {
    return width_;
  }

  unsigned int PNG::height() const {
    return height_;
  }

  void PNG::resize(unsigned int newWidth, unsigned int newHeight) {
    // Create a new vector to store the image data for the new (resized) image
    HSLAPixel * newImageData = new HSLAPixel[newWidth * newHeight];

    // Copy the current data to the new image data, using the existing pixel
    // for coordinates within the bounds of the old image size
    for (unsigned x = 0; x < newWidth; x++) {
      for (unsigned y = 0; y < newHeight; y++) {
        if (x < width_ && y < height_) {
          HSLAPixel & oldPixel = this->getPixel(x, y);
          HSLAPixel & newPixel = newImageData[ (x + (y * newWidth)) ];
          newPixel = oldPixel;
        }
      }
    }

    // Clear the existing image
    delete[] imageData_;

    // Update the image to reflect the new image size and data
    width_ = newWidth;
    height_ = newHeight;
    imageData_ = newImageData;
  }

  std::size_t PNG::computeHash() const {
    std::hash<float> hashFunction;
    std::size_t hash = 0;


    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        HSLAPixel & pixel = this->getPixel(x, y);
        hash = (hash << 1) + hash + hashFunction(pixel.h);
        hash = (hash << 1) + hash + hashFunction(pixel.s);
        hash = (hash << 1) + hash + hashFunction(pixel.l);
        hash = (hash << 1) + hash + hashFunction(pixel.a);
      }
    }

    return hash;
  }

  std::ostream & operator << ( std::ostream& os, PNG const& png ) {
    os << "PNG(w=" << png.width() << ", h=" << png.height() << ", hash=" << std::hex << png.computeHash() << std::dec << ")";
    return os;
  }


  void PNG::paste(PNG* the_tile, int startX, int startY, int resolution){
    for(unsigned int i = 0 ; i < (unsigned int)resolution ; i++ ){
      for (unsigned int j = 0 ; j < (unsigned int)resolution ; j++){
        this->getPixel(startX+i,startY+j) = the_tile->getPixel(i,j);
      }
    }
  }
  PNG* PNG::generateResizedImage(int startX, int startY, int resolution) {

      // set the resized_ image to size: resolution x resolution
      PNG *temp = new PNG(resolution,resolution);

      // If possible, avoid floating point comparisons. This helps ensure that
      // students' photomosaic's are diff-able with solutions
      if (this->width() % resolution == 0) {
          int scalingRatio = this->width() / resolution;

          for (int x = 0; x < resolution; x++) {
              for (int y = 0; y < resolution; y++) {
                  int pixelStartX = (x)     * scalingRatio;
                  int pixelEndX   = (x + 1) * scalingRatio;
                  int pixelStartY = (y)     * scalingRatio;
                  int pixelEndY   = (y + 1) * scalingRatio;

                  temp->getPixel(x, y) = getScaledPixelInt(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
              }
          }
      } else { // scaling is necessary
          double scalingRatio = static_cast<double>(this->width()) / resolution;

          for (int x = 0; x < resolution; x++) {
              for (int y = 0; y < resolution; y++) {
                  double pixelStartX = (double)(x)     * scalingRatio;
                  double pixelEndX   = (double)(x + 1) * scalingRatio;
                  double pixelStartY = (double)(y)     * scalingRatio;
                  double pixelEndY   = (double)(y + 1) * scalingRatio;

                  temp->getPixel(x, y) = getScaledPixelDouble(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
              }
          }
      }
    return temp;
  }    

  HSLAPixel PNG::getScaledPixelDouble(double startX, double endX,
          double startY, double endY) const
  {
      double leftFrac = 1.0 - startX + floor(startX);
      double rightFrac = endX - floor(endX);
      double topFrac = 1.0 - startX + floor(startX);
      double bottomFrac = endX - floor(endX);

      int startXint = static_cast<int>(startX);
      int endXint = static_cast<int>(ceil(endX));
      int startYint = static_cast<int>(startY);
      int endYint = static_cast<int>(ceil(endY));

      double h_sin = 0, h_cos = 0, s = 0, l = 0;
      double totalPixels = 0.0;

      for (int x = startXint; x < endXint; x++) {
          for (int y = startYint; y < endYint; y++) {
              double weight = 1.0;
              if (x == startXint) weight *= leftFrac;
              if (x == endXint)   weight *= rightFrac;
              if (y == startYint) weight *= topFrac;
              if (y == endYint)   weight *= bottomFrac;

              HSLAPixel & pixel = this->getPixel(x, y);
              double h_rad = pixel.h * M_PI / 180;
              h_sin += sin( h_rad ) * weight;
              h_cos += cos( h_rad ) * weight;
              s += pixel.s * weight;
              l += pixel.l * weight;

              totalPixels += weight;
          }
      }

      HSLAPixel color;
      color.h = atan2(h_sin, h_cos) * 180 / M_PI;
      if (color.h < 0) {
          color.h += 360;
      }
      color.s = s / totalPixels;
      color.l = l / totalPixels;
      return color;
  }

  HSLAPixel PNG::getScaledPixelInt(int startXint, int endXint,
          int startYint, int endYint) const
  {
      double h_sin = 0, h_cos = 0, s = 0, l = 0;
      double totalPixels = 0;

      for (int x = startXint; x < endXint; x++) {
          for (int y = startYint; y < endYint; y++) {
              HSLAPixel & pixel = this->getPixel(x, y);
              double h_rad = pixel.h * M_PI / 180;
              h_sin += sin( h_rad );
              h_cos += cos( h_rad );
              s += pixel.s;
              l += pixel.l;

              totalPixels++;
          }
      }

      HSLAPixel color;
      color.h = atan2(h_sin, h_cos) * 180 / M_PI;
      if (color.h < 0) {
          color.h += 360;
      }
      color.s = s / totalPixels;
      color.l = l / totalPixels;
      return color;
  }



  
}
  




