#include <YArenaOdorController.h>


YArenaOdorController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
