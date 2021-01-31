/**
 * @file Image.cpp
 * Implementation of the Image class.
 */

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

void Image::lighten()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).l + 0.1 <= 1)
            {
                this->getPixel(i, j).l += 0.1;
            }
            else
            {
                this->getPixel(i, j).l = 1;
            }
        }
    }
}

void Image::lighten(double amount)
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).l + amount <= 1)
            {
                this->getPixel(i, j).l += amount;
            }
            else
            {
                this->getPixel(i, j).l = 1;
            }
        }
    }
}

void Image::darken()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).l - 0.1 >= 0)
            {
                this->getPixel(i, j).l -= 0.1;
            }
            else
            {
                this->getPixel(i, j).l = 0;
            }
        }
    }
}

void Image::darken(double amount)
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).l - amount >= 0)
            {
                this->getPixel(i, j).l -= amount;
            }
            else
            {
                this->getPixel(i, j).l = 0;
            }
        }
    }
}

void Image::saturate()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).s + 0.1 <= 1)
            {
                this->getPixel(i, j).s += 0.1;
            }
            else
            {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}
void Image::saturate(double amount)
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).s + amount <= 1)
            {
                this->getPixel(i, j).s += amount;
            }
            else
            {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}

void Image::desaturate()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).s - 0.1 >= 0)
            {
                this->getPixel(i, j).s -= 0.1;
            }
            else
            {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}
void Image::desaturate(double amount)
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i, j).s - amount >= 0)
            {
                this->getPixel(i, j).s -= amount;
            }
            else
            {
                this->getPixel(i, j).s = 0;
            }
        }
    }
}

void Image::grayscale()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            this->getPixel(i,j).s = 0;
        }
    }
}

void Image::rotateColor(double degrees)
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            this->getPixel(i,j).h += degrees;
            if (this->getPixel(i,j).h > 360)
            {
                this->getPixel(i,j).h -= 360;
            }
            if (this->getPixel(i,j).h < 0)
            {
                this->getPixel(i,j).h += 360;
            }
            
        }
    }
}

void Image::illinify()
{
    // To do List
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            if (this->getPixel(i,j).h > 113.5 && this->getPixel(i,j).h < 293.5)
            {
                this->getPixel(i,j).h = 216;
            }
            else
            {
                this->getPixel(i,j).h = 11;
            }
        }
    }
}

void Image::scale(double factor)
{
    // To do List
    Image *image = new Image(*this);
    unsigned int width = this->width();
    unsigned int height = this->height();
    width *= factor;
    height *= factor;
    PNG::resize(width, height);
    for (unsigned int i = 0; i < this->width(); i++)
    {
        for (unsigned int j = 0; j < this->height(); j++)
        {
            unsigned int new_i = i/factor;
            unsigned int new_j = j/factor;
            this->getPixel(i,j) = image->getPixel(new_i, new_j);
        }
    }
    delete image;
}
void Image::scale(unsigned w, unsigned h)
{
    // To do List
    double w_factor = w/this->width();
    double h_factor = h/this->height();
    double minfactor = std::min(w_factor, h_factor);
    this->scale(minfactor);
}