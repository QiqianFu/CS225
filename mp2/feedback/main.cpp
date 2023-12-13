// #include "Image.h"
#include "StickerSheet.h"
// using namespace cs225;

int main() {
  Image image_1,image_2,image_3,image_4,image_5;
  image_1.readFromFile("/home/fqq/cs225sp23/mp2/i.png");
  image_3.readFromFile("/home/fqq/cs225sp23/mp2/flower.png");
  image_4.readFromFile("/home/fqq/cs225sp23/mp2/truck.png");
  image_5.readFromFile("/home/fqq/cs225sp23/mp2/trainagle.png");
  image_2.readFromFile("/home/fqq/cs225sp23/mp2/alma.png");
  StickerSheet base_image(image_2, 1);
  base_image.addSticker(image_1,100,100);
  base_image.changeMaxStickers(5);
  base_image.removeSticker(0);
  base_image.addSticker(image_3,100,200);
  base_image.addSticker(image_4,200,300);
  base_image.addSticker(image_5,700,400);
  base_image.addSticker(image_1,700,100);

  Image anser = base_image.render();
  anser.writeToFile("myImage.png");

  
  return 0;
}
