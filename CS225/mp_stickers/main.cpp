#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("tests/alma.png");
  Image png1; png1.readFromFile("tests/i.png");
  Image png2; png2.readFromFile("tests/i.png");
  Image png3; png3.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(png1, 0, 0);
  sheet.addSticker(png2, 400, 500);
  sheet.addSticker(png3, 600, 200);

  Image output = sheet.render();
  output.writeToFile("alma_trible.png");

  return 0;
}
