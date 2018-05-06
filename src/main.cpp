#include <Homie.h>
#include <Shutters.h>
#include <EEPROM.h>

#include <EnemDoubleButton.hpp>

const int SHUTTER1_PIN_UP = D3; // Up button commmand
const int SHUTTER1_PIN_DOWN = D4; // Down button command
const int SHUTTER1_PIN_UPDOWN = D1; // Up or Down selection : IN1 relay
const int SHUTTER1_PIN_PROCESS = D2; // Start or Stop control : IN2 relay
const int SHUTTER1_UPCOURSETIME_SEC = 15000;
const int SHUTTER1_DOWNCOURSETIME_SEC = 10000;
const float SHUTTER1_CALIBRATION_RATIO = 0.1;

const int SHUTTER2_PIN_UP = D7; // Up button commmand
const int SHUTTER2_PIN_DOWN = D8; // Down button command
const int SHUTTER2_PIN_UPDOWN = D5; // Up or Down selection : IN1 relay
const int SHUTTER2_PIN_PROCESS = D6; // Start or Stop control : IN2 relay
const int SHUTTER2_UPCOURSETIME_SEC = 15000;
const int SHUTTER2_DOWNCOURSETIME_SEC = 10000;
const float SHUTTER2_CALIBRATION_RATIO = 0.1;

EnemDoubleButton button1 = EnemDoubleButton(SHUTTER1_PIN_UP, SHUTTER1_PIN_DOWN, 60, 100, 1000);
EnemDoubleButton button2 = EnemDoubleButton(SHUTTER2_PIN_UP, SHUTTER2_PIN_DOWN, 60, 100, 1000);

Shutters shutter1;
Shutters shutter2;

byte publishingLevel1 = ShuttersInternal::LEVEL_NONE;
unsigned long publishingUpCourseTime1 = 0;
unsigned long publishingDownCourseTime1 = 0;

byte publishingLevel2 = ShuttersInternal::LEVEL_NONE;
unsigned long publishingUpCourseTime2 = 0;
unsigned long publishingDownCourseTime2 = 0;

HomieNode volet1Node("volet1", "volet");
HomieNode volet2Node("volet2", "volet");

bool positiveIntTryParse(const String& value, unsigned long& out)
{
  for (byte i = 0; i < value.length(); i++) {
    if (isDigit(value.charAt(i)) == false) return false;
  }

  out = value.toInt();

  return true;
}

bool volet1LevelHandler(const HomieRange& range, const String& value)
{
  unsigned long level;
  if(!positiveIntTryParse(value, level)) { return false; }

  if (level > 100) return false;

  shutter1.setLevel(level);

  return true;
}

bool volet1upCourseTimeHandler(const HomieRange& range, const String& value)
{
  unsigned long upCourseTime;
  if(!positiveIntTryParse(value, upCourseTime)) { return false; }

  //Garde fou : plus d'une minute = foutage de gueule, pas moins de 5 secondes, = foutage de gueule aussi !
  if(upCourseTime > 60000) { return false; }
  if(upCourseTime < 5000) { return false; }

  unsigned long downCourseTime = shutter1.getDownCourseTime();

  shutter1
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingUpCourseTime1 = upCourseTime;

  return true;
}

bool volet1downCourseTimeHandler(const HomieRange& range, const String& value)
{
  unsigned long downCourseTime;
  if(!positiveIntTryParse(value, downCourseTime)) { return false; }

  //Garde fou : plus d'une minute = foutage de gueule, pas moins de 5 secondes, = foutage de gueule aussi !
  if(downCourseTime > 60000) { return false; }
  if(downCourseTime < 5000) { return false; }

  unsigned long upCourseTime = shutter1.getUpCourseTime();

  shutter1
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingDownCourseTime1 = downCourseTime;

  return true;
}

bool volet2LevelHandler(const HomieRange& range, const String& value)
{
  unsigned long level;
  if(!positiveIntTryParse(value, level)) { return false; }

  if (level > 100) return false;

  shutter2.setLevel(level);

  return true;
}

bool volet2upCourseTimeHandler(const HomieRange& range, const String& value)
{
  unsigned long upCourseTime;
  if(!positiveIntTryParse(value, upCourseTime)) { return false; }

  //Garde fou : plus d'une minute = foutage de gueule, pas moins de 5 secondes, = foutage de gueule aussi !
  if(upCourseTime > 60000) { return false; }
  if(upCourseTime < 5000) { return false; }

  unsigned long downCourseTime = shutter2.getDownCourseTime();

  shutter2
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingUpCourseTime2 = upCourseTime;

  return true;
}

bool volet2downCourseTimeHandler(const HomieRange& range, const String& value)
{
  unsigned long downCourseTime;
  if(!positiveIntTryParse(value, downCourseTime)) { return false; }

  //Garde fou : plus d'une minute = foutage de gueule, pas moins de 5 secondes, = foutage de gueule aussi !
  if(downCourseTime > 60000) { return false; }
  if(downCourseTime < 5000) { return false; }

  unsigned long upCourseTime = shutter2.getUpCourseTime();

  shutter2
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingDownCourseTime2 = downCourseTime;

  return true;
}

void onShuttersLevelReached(Shutters* shutters, byte level) {
  Serial.print("Shutters at ");
  Serial.print(level);
  Serial.println("%");

  if(shutters == &shutter1)
  {
    publishingLevel1 = level;
  }

  if(shutters == &shutter2)
  {
    publishingLevel2 = level;
  }
}

void shuttersOperationHandler(Shutters* shutters, ShuttersOperation operation) {
  switch (operation) {
    case ShuttersOperation::UP:
      Serial.println("Shutters going up.");
      if(shutters == &shutter1)
      {
        digitalWrite(SHUTTER1_PIN_UPDOWN, LOW);
        digitalWrite(SHUTTER1_PIN_PROCESS, LOW);
      }
      if(shutters == &shutter2)
      {
        digitalWrite(SHUTTER2_PIN_UPDOWN, LOW);
        digitalWrite(SHUTTER2_PIN_PROCESS, LOW);
      }
      break;
    case ShuttersOperation::DOWN:
      Serial.println("Shutters going down.");
      if(shutters == &shutter1)
      {
        digitalWrite(SHUTTER1_PIN_UPDOWN, HIGH);
        digitalWrite(SHUTTER1_PIN_PROCESS, LOW);
      }
      if(shutters == &shutter2)
      {
        digitalWrite(SHUTTER2_PIN_UPDOWN, HIGH);
        digitalWrite(SHUTTER2_PIN_PROCESS, LOW);
      }
      break;
    case ShuttersOperation::HALT:
      Serial.println("Shutters halting.");
      if(shutters == &shutter1)
      {
        digitalWrite(SHUTTER1_PIN_PROCESS, HIGH);
      }
      if(shutters == &shutter2)
      {
        digitalWrite(SHUTTER2_PIN_PROCESS, HIGH);
      }
      break;
  }
}

void readInEeprom(char* dest, byte length, Shutters* shutters) {
  int offset = 0;

  if(shutters == &shutter1)
  {
    offset = 0;
  }

  if(shutters == &shutter2)
  {
    offset = length;
  }

  for (byte i = 0; i < length; i++) {
    dest[i] = EEPROM.read(offset + i);
  }
}

void shuttersWriteStateHandler(Shutters* shutters, const char* state, byte length) {
  int offset = 0;

  if(shutters == &shutter1)
  {
    offset = 0;
  }

  if(shutters == &shutter2)
  {
    offset = length;
  }

  for (byte i = 0; i < length; i++) {
    EEPROM.write(offset + i, state[i]);
    EEPROM.commit();
  }
}

void loopHandler() {
  if(publishingLevel1 != ShuttersInternal::LEVEL_NONE)
  {
    volet1Node.setProperty("level").send(String(publishingLevel1));
    publishingLevel1 = ShuttersInternal::LEVEL_NONE;
  }

  if(publishingUpCourseTime1 != 0)
  {
    volet1Node.setProperty("upCourseTime").send(String(publishingUpCourseTime1));
    publishingUpCourseTime1 = 0;
  }

  if(publishingDownCourseTime1 != 0)
  {
    volet1Node.setProperty("downCourseTime").send(String(publishingDownCourseTime1));
    publishingDownCourseTime1 = 0;
  }

  if(publishingLevel2 != ShuttersInternal::LEVEL_NONE)
  {
    volet2Node.setProperty("level").send(String(publishingLevel2));
    publishingLevel2 = ShuttersInternal::LEVEL_NONE;
  }

  if(publishingUpCourseTime2 != 0)
  {
    volet2Node.setProperty("upCourseTime").send(String(publishingUpCourseTime2));
    publishingUpCourseTime2 = 0;
  }

  if(publishingDownCourseTime2 != 0)
  {
    volet2Node.setProperty("downCourseTime").send(String(publishingDownCourseTime2));
    publishingDownCourseTime2 = 0;
  }
}

void upPressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    shutter1.setLevel(0);
  }
  if(button == &button2)
  {
    shutter2.setLevel(0);
  }
}

void downPressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    shutter1.setLevel(100);
  }
  if(button == &button2)
  {
    shutter2.setLevel(100);
  }
}

void stopPressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    shutter1.stop();
  }
  if(button == &button2)
  {
    shutter2.stop();
  }
}

void upDoublePressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    volet1Node.setProperty("externalUpCommand").send("1");
  }
  if(button == &button2)
  {
    volet2Node.setProperty("externalUpCommand").send("1");
  }
}

void downDoublePressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    volet1Node.setProperty("externalDownCommand").send("1");
  }
  if(button == &button2)
  {
    volet2Node.setProperty("externalDownCommand").send("1");
  }
}

void stopDoublePressed(EnemDoubleButton* button)
{
  if(button == &button1)
  {
    volet1Node.setProperty("externalStopCommand").send("1");
  }
  if(button == &button2)
  {
    volet2Node.setProperty("externalStopCommand").send("1");
  }
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  EEPROM.begin(512);

  Homie_setFirmware("volet", "1.0.5");
  Homie.setLoopFunction(loopHandler);
  Homie.setup();

  volet1Node.advertise("level").settable(volet1LevelHandler);
  volet1Node.advertise("upCourseTime").settable(volet1upCourseTimeHandler);
  volet1Node.advertise("downCourseTime").settable(volet1downCourseTimeHandler);
  volet1Node.advertise("externalUpCommand");
  volet1Node.advertise("externalDownCommand");
  volet1Node.advertise("externalStopCommand");

  char storedShuttersState[shutter1.getStateLength()];
  readInEeprom(storedShuttersState, shutter1.getStateLength(), &shutter1);

  shutter1
    .setOperationHandler(shuttersOperationHandler)
    .setWriteStateHandler(shuttersWriteStateHandler)
    .restoreState(storedShuttersState);

  if(shutter1.getUpCourseTime() == 0)
  {
    publishingUpCourseTime1 = SHUTTER1_UPCOURSETIME_SEC;
  }
  else
  {
    publishingUpCourseTime1 = shutter1.getUpCourseTime();
  }

  if(shutter1.getDownCourseTime() == 0)
  {
    publishingDownCourseTime1 = SHUTTER1_DOWNCOURSETIME_SEC;
  }
  else
  {
    publishingDownCourseTime1 = shutter1.getDownCourseTime();
  }

  shutter1
    .setCourseTime(publishingUpCourseTime1, publishingDownCourseTime1)
    .setCalibrationRatio(SHUTTER1_CALIBRATION_RATIO)
    .onLevelReached(onShuttersLevelReached)
    .begin();

  button1.setup();

  button1.setUpPressHandler(&upPressed);
  button1.setDownPressHandler(&downPressed);
  button1.setStopPressHandler(&stopPressed);
  button1.setUpDoublePressHandler(&upDoublePressed);
  button1.setDownDoublePressHandler(&downDoublePressed);
  button1.setStopDoublePressHandler(&stopDoublePressed);

  digitalWrite(SHUTTER1_PIN_UPDOWN, HIGH);
  digitalWrite(SHUTTER1_PIN_PROCESS, HIGH);

  pinMode(SHUTTER1_PIN_UPDOWN,OUTPUT);
  pinMode(SHUTTER1_PIN_PROCESS,OUTPUT);

  volet2Node.advertise("level").settable(volet2LevelHandler);
  volet2Node.advertise("upCourseTime").settable(volet2upCourseTimeHandler);
  volet2Node.advertise("downCourseTime").settable(volet2downCourseTimeHandler);
  volet2Node.advertise("externalUpCommand");
  volet2Node.advertise("externalDownCommand");
  volet2Node.advertise("externalStopCommand");

  readInEeprom(storedShuttersState, shutter2.getStateLength(), &shutter2);

  shutter2
    .setOperationHandler(shuttersOperationHandler)
    .setWriteStateHandler(shuttersWriteStateHandler)
    .restoreState(storedShuttersState);

  if(shutter2.getUpCourseTime() == 0)
  {
    publishingUpCourseTime2 = SHUTTER2_UPCOURSETIME_SEC;
  }
  else
  {
    publishingUpCourseTime2 = shutter2.getUpCourseTime();
  }

  if(shutter2.getDownCourseTime() == 0)
  {
    publishingDownCourseTime2 = SHUTTER2_DOWNCOURSETIME_SEC;
  }
  else
  {
    publishingDownCourseTime2 = shutter2.getDownCourseTime();
  }

  shutter2
    .setCourseTime(publishingUpCourseTime2, publishingDownCourseTime2)
    .setCalibrationRatio(SHUTTER2_CALIBRATION_RATIO)
    .onLevelReached(onShuttersLevelReached)
    .begin();

  button2.setup();

  button2.setUpPressHandler(&upPressed);
  button2.setDownPressHandler(&downPressed);
  button2.setStopPressHandler(&stopPressed);
  button2.setUpDoublePressHandler(&upDoublePressed);
  button2.setDownDoublePressHandler(&downDoublePressed);
  button2.setStopDoublePressHandler(&stopDoublePressed);

  digitalWrite(SHUTTER2_PIN_UPDOWN, HIGH);
  digitalWrite(SHUTTER2_PIN_PROCESS, HIGH);

  pinMode(SHUTTER2_PIN_UPDOWN,OUTPUT);
  pinMode(SHUTTER2_PIN_PROCESS,OUTPUT);
}

void HomieIndependentLoop()
{
  button1.loop();
  shutter1.loop();
  button2.loop();
  shutter2.loop();
}

void loop() {
  Homie.loop();
  HomieIndependentLoop();
}
