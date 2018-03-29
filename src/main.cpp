#include <Homie.h>
#include <Shutters.h>

#include <EnemDoubleButton.hpp>

//const int TRANSMIT_INTERVAL = 1;
const int PIN_UP = D1;
const int PIN_DOWN = D2;
const int PIN_SHUTTER1_UPDOWN = D6;
const int PIN_SHUTTER1_PROCESS = D7;
const int SHUTTER1_UPCOURSETIME_SEC = 15000;
const int SHUTTER1_DOWNCOURSETIME_SEC = 10000;
const float SHUTTER1_CALIBRATION_RATIO = 0.1;

//unsigned long lastTransmit = 0;
//bool sensorOpenState = false;

EnemDoubleButton button = EnemDoubleButton(PIN_UP, PIN_DOWN, 60, 100, 1000);

bool lastUpState = false;
bool lastDownState = false;
bool lastStopState = false;
bool lastDoubleState = false;

Shutters shutter1;

HomieNode volet1Node("volet1", "volet");

bool volet1PositionHandler(const HomieRange& range, const String& value)
{
  Homie.getLogger() << "volet1PositionHandler" << endl;
  return true;
}

void onShuttersLevelReached(Shutters* shutters, byte level) {
  Serial.print("Shutters at ");
  Serial.print(level);
  Serial.println("%");
}

void shuttersOperationHandler(Shutters* s, ShuttersOperation operation) {
  switch (operation) {
    case ShuttersOperation::UP:
      Serial.println("Shutters going up.");
      // TODO: Implement the code for the shutters to go up
      break;
    case ShuttersOperation::DOWN:
      Serial.println("Shutters going down.");
      // TODO: Implement the code for the shutters to go down
      break;
    case ShuttersOperation::HALT:
      Serial.println("Shutters halting.");
      // TODO: Implement the code for the shutters to halt
      break;
  }
}

void shuttersWriteStateHandler(Shutters* shutters, const char* state, byte length) {
}

/*
void shuttersUp() {
  Serial.println("Shutters going up.");
  // TODO: Implement the code for the shutters to go up
}

void shuttersDown() {
  Serial.println("Shutters going down.");
  // TODO: Implement the code for the shutters to go down
}

void shuttersHalt() {
  Serial.println("Shutters halted.");
  // TODO: Implement the code for the shutters to halt
}

uint8_t shuttersGetState() {
  return 255;
}

void shuttersSetState(uint8_t state) {
  Serial.print("Saving state ");
  Serial.print(state);
  Serial.println(".");
}

void onShuttersLevelReached(uint8_t level) {
  Serial.print("Shutters at ");
  Serial.print(level);
  Serial.println("%");
}

Shutters shutter1(SHUTTER1_DOWNCOURSETIME_SEC, shuttersUp, shuttersDown, shuttersHalt, shuttersGetState, shuttersSetState,
  SHUTTER1_CALIBRATION_RATIO, onShuttersLevelReached);
*/
void loopHandler() {
  button.loop();
  shutter1.loop();

  bool upState = button.isUpPressed();
  bool downState = button.isDownPressed();
  bool stopState = button.isStopPressed();
  bool doubleState = button.isDoublePressed();

  if(upState != lastUpState || downState != lastDownState || stopState != lastStopState || doubleState != lastDoubleState)
  {
    Homie.getLogger() << millis() << ": up[" << upState << "] - down[" << downState << "] - stop[" << stopState
      << "] - double[" << doubleState << "]" << endl;

    if(upState && !lastUpState)
    {
      Homie.getLogger() << "Shutter1 consigne 0" << endl;
      shutter1.setLevel(0);
    }

    if(downState && !lastDownState)
    {
      Homie.getLogger() << "Shutter1 consigne 100" << endl;
      shutter1.setLevel(100);
    }

    if(stopState && !lastStopState)
    {
      Homie.getLogger() << "Shutter1 stop" << endl;
      shutter1.stop();
    }

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

  shutter1/*.begin();*/
    .setOperationHandler(shuttersOperationHandler)
    .setWriteStateHandler(shuttersWriteStateHandler)
    .setCourseTime(SHUTTER1_UPCOURSETIME_SEC, SHUTTER1_DOWNCOURSETIME_SEC)
    .setCalibrationRatio(SHUTTER1_CALIBRATION_RATIO)
    .onLevelReached(onShuttersLevelReached)
    .begin();
//    .setLevel(30);

  button.setup();

  digitalWrite(PIN_SHUTTER1_UPDOWN, HIGH);
  digitalWrite(PIN_SHUTTER1_PROCESS, HIGH);

  pinMode(PIN_SHUTTER1_UPDOWN,OUTPUT);
  pinMode(PIN_SHUTTER1_PROCESS,OUTPUT);

  //shutter.setup();
}

void loop() {
  Homie.loop();
}
