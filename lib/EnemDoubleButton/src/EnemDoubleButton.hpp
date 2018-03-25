#pragma once

#include <Arduino.h>
#include <Bounce2.h>

class EnemDoubleButton
{
private:
  const int delayBounce;
  const int delayBoth;
  const int delayDouble;

  const int pinUp;
  Bounce upDebouncer;

  const int pinDown;
  Bounce downDebouncer;

  unsigned long upSince = 0;
  unsigned long downSince = 0;

  unsigned long lastActionSince = 0;
  int lastAction;

  bool upPressed = false;
  bool downPressed = false;
  bool stopPressed = false;
  bool doublePressed = false;

  bool lastUp = false;
  bool lastDown = false;
  bool lastStop = false;

  void upPress();
  void upRelease();
  void upPressDouble();
  void downPress();
  void downRelease();
  void downPressDouble();
  void stopPress();
  void stopRelease();
  void stopPressDouble();

public:
  EnemDoubleButton(int pinUp, int pinDown, int delayBounce, int delayBoth, int delayDouble);
  void setup();
  void loop();
  bool isUpPressed(bool dbl=false);
  bool isDownPressed(bool dbl=false);
  bool isStopPressed(bool dbl=false);
  bool isDoublePressed();
};
