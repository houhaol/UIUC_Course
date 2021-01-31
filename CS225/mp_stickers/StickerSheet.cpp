#include "StickerSheet.h"
#include "Image.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    // Todo
    scene = new Image* [max];
    layer = new unsigned int [max]; // store true if sticker exist otherwise false

    for (unsigned int i = 0; i < max; i++)
    {
        scene[i] = NULL;
        // xcoord[i] = 0;
        // ycoord[i] = 0;
        layer[i] = 0;
    }
    xcoord = new unsigned int [max];
    ycoord = new unsigned int [max];
    stickerMax = max;
    stickerCount = 0;
    base = new Image(picture);
}

StickerSheet::~StickerSheet()
{
    // Todo
    clear();
}

void StickerSheet::clear()
{
    for (unsigned int i = 0; i < stickerMax; i++)
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
    if (layer != NULL)
    {
        delete[] layer;
        layer = NULL;
    }
}

StickerSheet::StickerSheet (const StickerSheet &other)
{
    // Todo
    copy(other);
}

void StickerSheet::copy(const StickerSheet &other)
{
    // initialize
    stickerMax = other.stickerMax;
    base = new Image(*other.base);
    xcoord = new unsigned int [stickerMax];
    ycoord = new unsigned int [stickerMax];
    scene = new Image* [stickerMax];
    layer = new unsigned int [stickerMax];
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        scene[i] = NULL;
        layer[i] = 0;
    }
    
    // copy
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        if (other.scene[i] != NULL)
        {
            scene[i] = new Image(*other.scene[i]);
        }else
        {
            scene[i] = NULL;
        }
        
        // scene[i] = new Image();
        // *scene[i] = *other.scene[i];
        
        xcoord[i] = other.xcoord[i];
        ycoord[i] = other.ycoord[i];

        layer[i] = other.layer[i];
    }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other)
{
    // Todo
    if (this != &other)
    {
        clear();
        copy(other);
    }
    
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max)
{
    // Todo
    if (max == stickerMax)
    {
        return;
    }
    // Initialize
    Image** tmpScene = new Image* [max];
    unsigned int* tmpXcoord = new unsigned int [max];
    unsigned int* tmpYcoord = new unsigned int [max];
    unsigned int* tmpLayer = new unsigned int [max];
    for (unsigned int i = 0; i < max; i++)
    {
        tmpScene[i] = NULL;
        tmpXcoord[i] = 0;
        tmpYcoord[i] = 0;
        tmpLayer[i] = 0;
    }

    // check smaller or bigger for the scope
    unsigned int tmpMax;
    if (max < stickerMax)
    {
        tmpMax = max;
    } else
    {
        tmpMax = stickerMax;
    }

    // copy stuff
    for (unsigned int i = 0; i < tmpMax; i++)
    {
        tmpScene[i] = scene[i];
        tmpLayer[i] = layer[i];
        tmpXcoord[i] = xcoord[i];
        tmpYcoord[i] = ycoord[i];
    }
    
    // clear old
    delete[] xcoord;
    delete[] ycoord;
    delete[] layer;
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        if (scene[i] != NULL)
        {
            scene[i] = NULL;
        }
    }
    delete[] scene;
    scene = NULL;

    // Transfer tmp to cur
    xcoord = tmpXcoord;
    ycoord = tmpYcoord;
    layer = tmpLayer;
    scene = tmpScene;
    stickerMax = max;

    // free tmp?
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y)
{
    // Todo
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        if (layer[i] == 0) 
        {
            // if (scene[i] != NULL)
            // {
            //     delete scene[i];
            // }
            scene[i] = new Image(sticker);
            // scene[i] = &sticker;
            xcoord[i] = x;
            ycoord[i] = y;
            layer[i] = 1;
            return i;
        }
    }
    return -1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y)
{
    // Todo
    // if (index > stickerMax || layer[index] == 0)
    if (index > stickerMax || scene[index] == NULL)
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
        scene[index] = NULL;
        layer[index] = 0;
    }
}

Image * StickerSheet::getSticker (unsigned index)
{
    // Todo
    if (index >= stickerMax)
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
    for (unsigned int i = 0; i < stickerMax; i++)
    {
        if (scene[i] != NULL)
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
    }
    return output;
}
