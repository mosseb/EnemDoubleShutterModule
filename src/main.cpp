#include <Homie.h>
#include <EEPROM.h>

#include <EnemDoubleButton.hpp>
#include <EnemShutter.hpp>

const int TRANSMIT_INTERVAL = 1;
const int PIN_UP = D1;
const int PIN_DOWN = D2;
const int PIN_SHUTTER1_UPDOWN = D3;
const int PIN_SHUTTER1_PROCESS = D4;
const int SHUTTER1_UPCOURSETIME_SEC = 15;
const int SHUTTER1_DOWNCOURSETIME_SEC = 10;

unsigned long lastTransmit = 0;
bool sensorOpenState = false;

EnemDoubleButton button = EnemDoubleButton(PIN_UP, PIN_DOWN, 60, 100, 1000);
EnemShutter shutter = EnemShutter(PIN_SHUTTER1_UPDOWN, PIN_SHUTTER1_PROCESS, button, SHUTTER1_UPCOURSETIME_SEC, SHUTTER1_DOWNCOURSETIME_SEC, 0.1);

bool lastUpState = false;
bool lastDownState = false;
bool lastStopState = false;
bool lastDoubleState = false;

HomieNode garageOpenNode("sensorOpen", "booleanState");

void loopHandler() {
  bool upState = button.isUpPressed();
  bool downState = button.isDownPressed();
  bool stopState = button.isStopPressed();
  bool doubleState = button.isDoublePressed();

  if(upState != lastUpState || downState != lastDownState || stopState != lastStopState || doubleState != lastDoubleState)
  {
    Serial.println(String(String(millis()) + ": up[" + String(upState) + "] - down[" + String(downState) + "] - stop[" + String(stopState) + "] - double[" + String(doubleState) + "]"));

    if(upState && !lastUpState)
    {
      shutter.setLevel(0);
    }

    if(downState && !lastDownState)
    {
      shutter.setLevel(100);
    }

    if(stopState && !lastStopState)
    {
      shutter.stop();
    }

    lastUpState = upState;
    lastDownState = downState;
    lastStopState = stopState;
    lastDoubleState = doubleState;
  }
}

void setup() {
  Serial.begin(115200);

  Homie.setFirmware("garage", "1.0.0");
  Homie.registerNode(garageOpenNode);
  Homie.setLoopFunction(loopHandler);
  Homie.setup();

  button.setup();

  shutter.setup();

  //Init first time values
  lastUpState = button.isUpPressed();
  lastDownState = button.isDownPressed();
}

void loop() {
  shutter.loop();
  Homie.loop();
}
