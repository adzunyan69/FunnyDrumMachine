#include <iostream>
#include "GameModule/mainwindow.h"

int main(int argc, char *args[])
{
  GUI::MainWindow window;
  if (window.init() == false)
    return 1;

  if (window.loop() == false)
    return 2;
  return 0;
}
