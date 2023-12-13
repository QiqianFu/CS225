/**
 * @file StickerSheet.h
 *
 * @author Howie Liu
 * @date Fri Mar 17 3:21:15 AM
 */

#ifndef CS225_StickerSheet_H
#define CS225_StickerSheet_H

#include "Image.h"
#include <iostream>

namespace cs225 {

class StickerSheet {
    Image* base_;       // Base pcture
    unsigned max_;      // max number of stickers
    Image** stickers_;  // the array of stickers
    unsigned* x_;       // x-coorninate of the stickers
    unsigned* y_;       // y-coorninate of the stickers
    double *ratio;
    // helper function to copy
    void copy_(const StickerSheet& other);
    // helper function to destroy
    void destroy_();    

public:

    /**
     * @brief Construct a new Sticker Sheet object
     */
    StickerSheet();

    /**
     * @brief Initializes the StickerSheet with a base `picture` and the
     * ability to hold `max` stickers.
     * 
     * @param picture The base picture to use in the StickerSheet
     * @param max The maximum number of stickers on this StickerSheet
     */
    StickerSheet(const Image& picture, unsigned max);

    /**
     * @brief Frees all space that was dynamically allocated.
     */
    ~StickerSheet();

    /**
     * @brief The copy constructor makes an independent copy of the source.
     * 
     * @param other The other StickerSheet object to copy data from
     */
    StickerSheet(const StickerSheet& other);

    /**
     * @brief The assignment operator for the StickerSheet class.
     * 
     * @param other The other Scene object to copy data from
     * @return a constant Scene reference
     */
    const StickerSheet& operator=(const StickerSheet& other);

    /**
     * @brief Modifies the maximum number of stickers that can be stored 
     * without changing existing stickers' indices. If the new maximum 
     * number is smaller than the current number of stickers, the stickers
     * with indices above `max` - 1 will be lost.
     * 
     * @param max The new value for the maximum number of Images.
     */
    void changeMaxStickers(unsigned max);

    /**
     * @brief Adds a sticker to the StickerSheet, so that the top-left
     * of the sticker's Image is at (x, y) on the StickerSheet. The sticker
     * must be added to the lowest possible layer available.
     * 
     * @param sticker The Image of the sticker.
     * @param x The x location of the sticker on the StickerSheet
     * @param y The y location of the sticker on the StickerSheet
     * @return The zero-based layer index the sticker was added to,
     * or -1 if the sticker cannot be added.
     */
    int addSticker(Image& sticker, unsigned x, unsigned y, double ratio);
    
    /**
     * @brief Changes the coordinates of the Image in the specified layer.
     * 
     * @param index Zero-based layer index of the sticker.
     * @param x The new x location of the sticker on the StickerSheet
     * @param y The new y location of the sticker on the StickerSheet
     * @return `true` if the translate was successful; otherwise `false`.
     */
    bool translate(unsigned index, unsigned x, unsigned y);
    
    /**
     * @brief Removes the sticker at the given zero-based layer index.
     * 
     * @param index The layer in which to delete the png
     */
    void removeSticker(unsigned index);

    /**
     * @brief Returns a pointer to the sticker at the specified index.
     * If the index is invalid, return nullptr.
     * 
     * @param index The layer in which to get the sticker.
     * @return A pointer to a specific Image in the StickerSheet
     */
    Image* getSticker(unsigned index) const;

    /**
     * @brief Renders the whole StickerSheet on a Image and returns it.
     * The base picture is drawn first and then each sticker is drawn in
     * order starting with layer zero (0), then layer one (1), and so on.
     * If a pixel's alpha channel in a sticker is zero (0), no pixel is
     * drawn for that sticker at that pixel. If the alpha channel is
     * non-zero, a pixel is drawn.
     * The returned Image always includes the full contents of the picture
     * and all stickers. This means that the size of the result image may
     * be larger than the base picture if some stickers go beyond the edge
     * of the picture.
     * 
     * @return Image an Image object representing the drawn scene
     */
    Image render() const;
};

}; // cs225 namespace

#endif
