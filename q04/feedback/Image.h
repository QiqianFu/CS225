/**
 * @file Image.h
 *
 * @author Howie Liu
 * @date Fri Mar 17 3:21:15 AM
 */

#ifndef CS225_Image_H
#define CS225_Image_H

#include "cs225/PNG.h"

namespace cs225 {

class Image : public PNG {
public:

    /**
     * @brief Construct a new Image object
     */
    Image();

    /**
     * @brief Construct a new Image object
     * 
     * @param width width of the image
     * @param height height of the image
     */
    Image(unsigned width, unsigned height);


    /**
     * Lighten an Image by increasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     * @param amount    The desired increase in luminance.
     */
    void lighten(double amount = 0.1);

    /**
     * Darken an Image by decreasing the luminance of every pixel by amount.
     * This function ensures that the luminance remains in the range [0, 1].
     * @param amount    The desired decrease in luminance.
     */
    void darken(double amount = 0.1);

    /**
     * Saturates an Image by increasing the saturation of every pixel by amount.
     * This function ensures that the saturation remains in the range [0, 1].
     * @param amount    The desired increase in saturation.
     */
    void saturate(double amount = 0.1);

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by amount.
     * This function ensures that the saturation remains in the range [0, 1].
     * @param amount    The desired decrease in saturation.
     */
    void desaturate(double amount = 0.1);

    /**
     * Turns the image grayscale.
     */
    void grayscale();

    /**
     * Rotates the color wheel by degrees.
     * This function ensures that the hue remains in the range [0, 360].
     * @param degrees   The desired amount of rotation.
     */
    void rotateColor(double degrees);

    /**
     * Illinifies the image.
     */
    void illinify();

    /**
     * Scales the Image by a given factor.
     * This function both resizes the Image and scales the contents.
     * @param factor    Scale factor.
     */
    void scale(double factor);

    /**
     * Scales the image to fit within the size (w x h).
     * This function preserves the aspect ratio of the image,
     * so the result will always be an image of width w or of height h (not necessarily both).
     * @param w Desired width of the scaled Iamge
     * @param h Desired height of the scaled Image
     */
    void scale(unsigned w, unsigned h);

    void rotate(int degree);
};

};  // cs225 namespace


#endif // CS225_Image_H