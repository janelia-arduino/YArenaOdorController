#include <YArenaValveController.h>


YArenaValveController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
