#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
   cs225::PNG png;
   if (!png.readFromFile(inputFile))
   {
     std::cout << "No file loaded" << std::endl;
     return;
   }
   int width = png.width();
   int height = png.height();

   // Output file
   cs225::PNG out_png(width, height);

   // Rotate png
   for (int i = 0; i < width; i++)
   {
     for (int j = 0; j < height; j++)
     {
       cs225::HSLAPixel & pixel = out_png.getPixel(i, j);
       pixel = png.getPixel(width - i - 1, height - j - 1);
     }
   }

    // Save file
    out_png.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned i = 0; i < png.width(); i++)
  {
    for (unsigned j = 0; j < png.height(); j++)
    {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      // customize work
      pixel.h = i * 888 % 200;
      pixel.s = .65;
      pixel.l = .2;
      pixel.a = 1;
    }
    
  }
  
  return png;
}
