#include <Homie.h>
#include <Shutters.h>

#include <EnemDoubleButton.hpp>

//const int TRANSMIT_INTERVAL = 1;
const int PIN_UP = D1;
const int PIN_DOWN = D2;
//const int PIN_SHUTTER1_UPDOWN = D3;
//const int PIN_SHUTTER1_PROCESS = D4;
//const int SHUTTER1_UPCOURSETIME_SEC = 15;
//const int SHUTTER1_DOWNCOURSETIME_SEC = 10;

//unsigned long lastTransmit = 0;
//bool sensorOpenState = false;

EnemDoubleButton button = EnemDoubleButton(PIN_UP, PIN_DOWN, 60, 100, 1000);

bool lastUpState = false;
bool lastDownState = false;
bool lastStopState = false;
bool lastDoubleState = false;

HomieNode volet1Node("volet1", "volet");

bool volet1PositionHandler(const HomieRange& range, const String& value)
{
  Homie.getLogger() << "volet1PositionHandler" << endl;
  return true;
}

void loopHandler() {
  bool upState = button.isUpPressed();
  bool downState = button.isDownPressed();
  bool stopState = button.isStopPressed();
  bool doubleState = button.isDoublePressed();

  if(upState != lastUpState || downState != lastDownState || stopState != lastStopState || doubleState != lastDoubleState)
  {
    Homie.getLogger() << millis() << ": up[" << upState << "] - down[" << downState << "] - stop[" << stopState
      << "] - double[" << doubleState << "]";
/*
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
*/
    lastUpState = upState;
    lastDownState = downState;
    lastStopState = stopState;
    lastDoubleState = doubleState;
  }
}

void setup() {
  Serial.begin(115200);

  Homie_setFirmware("volet", "1.0.2");
  Homie.setLoopFunction(loopHandler);
  Homie.setup();

  volet1Node.advertise("state");
  volet1Node.advertise("position").settable(volet1PositionHandler);

  button.setup();

  //shutter.setup();
}

void loop() {
  button.loop();
  Homie.loop();
}
