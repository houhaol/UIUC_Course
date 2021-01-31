/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

class StickerSheet
{
public:

    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet (const StickerSheet &other);
    const StickerSheet & operator= (const StickerSheet &other);
    
    void changeMaxStickers (unsigned max);
    int addSticker (Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);
    void removeSticker (unsigned index);
    Image * getSticker (unsigned index);
    Image render () const;

    void clear();
    void copy(const StickerSheet& other);
private:
    // create a array of pointers to object scene
    Image** scene;
    unsigned int* xcoord;
    unsigned int* ycoord;
    unsigned int* layer;
    unsigned int stickerMax;
    // Default base image
    Image* base;
};

