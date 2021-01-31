#include "StickerSheet.h"
#include "Image.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    // Todo
    scene = new Image* [max];
    xcoord = new unsigned int [max];
    ycoord = new unsigned int [max];

    for (unsigned int i = 0; i < max; i++)
    {
        scene[i] = NULL;
        xcoord[i] = 0;
        ycoord[i] = 0;
    }
    stickerMax = max;
    stickers = 0;
    base = new Image(picture);
}

StickerSheet::~StickerSheet()
{
    // Todo
    clear();
}

void StickerSheet::clear()
{
    for (unsigned int i = 0; i < stickers; i++)
    {
        if (scene[i] != NULL)
        {
            delete scene[i];
            scene[i] = NULL;
        }
    }
    if (scene != NULL)
    {
        delete[] scene;
        scene = NULL;
    }
    if (xcoord != NULL)
    {
        delete[] xcoord;
        xcoord = NULL;
    }
    if (ycoord != NULL)
    {
        delete[] ycoord;
        ycoord = NULL;
    }
    if (base != NULL)
    {
        delete base;
        base = NULL;
    }

}

StickerSheet::StickerSheet (const StickerSheet &other)
{
    // Todo
    copy(other);
}

void StickerSheet::copy(const StickerSheet &other)
{
    stickers = other.stickers;
    stickerMax = other.stickerMax;
    base = new Image(*other.base);
    xcoord = new unsigned int [stickerMax];
    ycoord = new unsigned int [stickerMax];
    scene = new Image* [stickerMax];
    
    for (unsigned int i = 0; i < stickers; i++)
    {
        scene[i] = NULL;
        // scene[i] = new Image(*other.scene[i]);
        scene[i] = new Image();
        *scene[i] = *other.scene[i];
        xcoord[i] = other.xcoord[i];
        ycoord[i] = other.ycoord[i];
    }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other)
{
    // Todo
    if (this == &other)
    {
        return *this;
    }
    
    clear();
    copy(other);
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
    // Todo
    if (max == stickerMax)
    {
        return;
    }
    // Error: changeMaxStickers() does not discard stickers when resized larger

    Image** tmpScene = new Image* [stickers];
    unsigned int* tmpXcoord = new unsigned int [stickers];
    unsigned int* tmpYcoord = new unsigned int [stickers];
    for (unsigned int i = 0; i < stickers; i++)
    {
        tmpScene[i] = NULL;
        tmpXcoord[i] = 0;
        tmpYcoord[i] = 0;
    }

    if (max < stickers)
    {
        for (unsigned int i = 0; i < stickers; i++)
        {
        tmpScene[i] = scene[i];
        tmpXcoord[i] = xcoord[i];
        tmpYcoord[i] = ycoord[i];
        }
        delete[] scene;
        delete[] xcoord;
        delete[] ycoord;

        scene = new Image* [max];
        xcoord = new unsigned int [max];
        ycoord = new unsigned int [max];

        for (unsigned int i = max; i < stickers; i++)
        {
            delete tmpScene[i];
            tmpScene[i] = NULL;
        }
        
        stickers = max;
        for (unsigned int i = 0; i < stickers; i++)
        {
            scene[i] = tmpScene[i];
            xcoord[i] = tmpXcoord[i];
            ycoord[i] = tmpYcoord[i];
        }
    }
    else // max > stickers
    {
        for (unsigned int i = 0; i < stickers; i++)
        {
            tmpScene[i] = scene[i];
            tmpXcoord[i] = xcoord[i];
            tmpYcoord[i] = ycoord[i];
        }
        delete[] scene;
        delete[] xcoord;
        delete[] ycoord;
        
        scene = new Image* [max];
        xcoord = new unsigned int [max];
        ycoord = new unsigned int [max];
        
        for (unsigned int i = 0; i < stickers; i++)
        {
            scene[i] = tmpScene[i];
            xcoord[i] = tmpXcoord[i];
            ycoord[i] = tmpYcoord[i];
        }
    }
    stickerMax = max;
    delete[] tmpScene;
    delete[] tmpXcoord;
    delete[] tmpYcoord;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y)
{
    // Todo
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        // case 1, no more space
        if (stickers == stickerMax)
        {
            return -1;
        }
        else if (i == stickers)
        {
            scene[i] = new Image(sticker);
            xcoord[i] = x;
            ycoord[i] = y;
            stickers++;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y)
{
    // Todo
    if (index > stickers)
    {
        return false;
    }
    else
    {
        xcoord[index] = x;
        ycoord[index] = y;
        return true;
    }
}

void StickerSheet::removeSticker (unsigned index)
{
    // Todo
    if (index < stickerMax && scene[index] != NULL)
    {
        delete scene[index];
        for (unsigned int i = index; i < stickerMax - 1; i++)
        {
            scene[i] = scene[i+1];
            xcoord[i] = xcoord[i+1];
            ycoord[i] = ycoord[i+1];
        }
        scene[stickerMax - 1] = NULL;
        stickers--;
    }
    else
    {
        return;
    }
}

Image * StickerSheet::getSticker (unsigned index)
{
    // Todo
    if (index >= stickers)
    {
        return NULL;
    }
    return scene[index];
    
}

Image StickerSheet::render () const
{
    // Todo
    Image output(*base);
    unsigned int maxWidth = base->width();
    unsigned int maxHeight = base->height();
    
    // iterate all sitckers
    for (unsigned int i = 0; i < stickers; i++)
    {
        unsigned int stickerWidth = scene[i]->width();
        unsigned int stickerHeight = scene[i]->height();
        
        // check size if larger than the base picture and do resize work
        if (stickerWidth + xcoord[i] > output.width())
        {
            maxWidth = stickerWidth + xcoord[i];
        }
        if (stickerHeight + ycoord[i] > output.height())
        {
            maxHeight = stickerHeight + ycoord[i];
        }

        // resize output
        output.resize(maxWidth, maxHeight);

        // add stickers
        for (unsigned int x = 0; x < stickerWidth; x++)
        {
            for (unsigned int y = 0; y < stickerHeight; y++)
            {
                // check alpha channel
                cs225::HSLAPixel & outputPixel = output.getPixel(x + xcoord[i], y + ycoord[i]);
                cs225::HSLAPixel & scenePixel = scene[i]->getPixel(x,y);

                if (scenePixel.a != 0)
                {
                    outputPixel = scenePixel;
                }
            }
        }
    }
    return output;
}
