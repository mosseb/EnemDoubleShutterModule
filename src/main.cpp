#include <Homie.h>
#include <Shutters.h>
#include <EEPROM.h>

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
byte publishingLevel = ShuttersInternal::LEVEL_NONE;
unsigned long publishingUpCourseTime = 0;
unsigned long publishingDownCourseTime = 0;

HomieNode volet1Node("volet1", "volet");

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

  //Garde fou : plus d'une minute = foutage de gueule
  if(upCourseTime > 60000) { return false; }

  unsigned long downCourseTime = shutter1.getDownCourseTime();

  shutter1
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingUpCourseTime = upCourseTime;

  return true;
}

bool volet1downCourseTimeHandler(const HomieRange& range, const String& value)
{
  unsigned long downCourseTime;
  if(!positiveIntTryParse(value, downCourseTime)) { return false; }

  //Garde fou : plus d'une minute = foutage de gueule
  if(downCourseTime > 60000) { return false; }

  unsigned long upCourseTime = shutter1.getUpCourseTime();

  shutter1
    .reset()
    .setCourseTime(upCourseTime, downCourseTime)
    .begin();

  publishingDownCourseTime = downCourseTime;

  return true;
}

void onShuttersLevelReached(Shutters* shutters, byte level) {
  Serial.print("Shutters at ");
  Serial.print(level);
  Serial.println("%");
  publishingLevel = level;
}

void shuttersOperationHandler(Shutters* s, ShuttersOperation operation) {
  switch (operation) {
    case ShuttersOperation::UP:
      Serial.println("Shutters going up.");
      // TODO: Implement the code for the shutters to go up
      digitalWrite(PIN_SHUTTER1_UPDOWN, LOW);
      digitalWrite(PIN_SHUTTER1_PROCESS, LOW);
      break;
    case ShuttersOperation::DOWN:
      Serial.println("Shutters going down.");
      // TODO: Implement the code for the shutters to go down
      digitalWrite(PIN_SHUTTER1_UPDOWN, HIGH);
      digitalWrite(PIN_SHUTTER1_PROCESS, LOW);
      break;
    case ShuttersOperation::HALT:
      Serial.println("Shutters halting.");
      // TODO: Implement the code for the shutters to halt
      digitalWrite(PIN_SHUTTER1_PROCESS, HIGH);
      break;
  }
}

void readInEeprom(char* dest, byte length, Shutters* shutters) {
  for (byte i = 0; i < length; i++) {
    //TODO remplacer 0 par le rang du volet * taille de la struct
    dest[i] = EEPROM.read(0 + i);
  }
}

void shuttersWriteStateHandler(Shutters* shutters, const char* state, byte length) {
  for (byte i = 0; i < length; i++) {
    //TODO remplacer 0 par le rang du volet * taille de la struct
    EEPROM.write(0 + i, state[i]);
    EEPROM.commit();
  }
}

void loopHandler() {
  if(publishingLevel != ShuttersInternal::LEVEL_NONE)
  {
    volet1Node.setProperty("level").send(String(publishingLevel));
    publishingLevel = ShuttersInternal::LEVEL_NONE;
  }

  if(publishingUpCourseTime != 0)
  {
    volet1Node.setProperty("upCourseTime").send(String(publishingUpCourseTime));
    publishingUpCourseTime = 0;
  }

  if(publishingDownCourseTime != 0)
  {
    volet1Node.setProperty("downCourseTime").send(String(publishingDownCourseTime));
    publishingDownCourseTime = 0;
  }
}

void upPressed(EnemDoubleButton* button)
{
  shutter1.setLevel(0);
}

void downPressed(EnemDoubleButton* button)
{
  shutter1.setLevel(100);
}

void stopPressed(EnemDoubleButton* button)
{
  shutter1.stop();
}

void upDoublePressed(EnemDoubleButton* button)
{
  volet1Node.setProperty("externalUpCommand").send("1");
}

void downDoublePressed(EnemDoubleButton* button)
{
  volet1Node.setProperty("externalDownCommand").send("1");
}

void stopDoublePressed(EnemDoubleButton* button)
{
  volet1Node.setProperty("externalStopCommand").send("1");
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
    publishingUpCourseTime = SHUTTER1_UPCOURSETIME_SEC;
  }

  if(shutter1.getDownCourseTime() == 0)
  {
    publishingDownCourseTime = SHUTTER1_DOWNCOURSETIME_SEC;
  }

  shutter1
    .setCourseTime(publishingUpCourseTime, publishingDownCourseTime)
    .setCalibrationRatio(SHUTTER1_CALIBRATION_RATIO)
    .onLevelReached(onShuttersLevelReached)
    .begin();

  button.setup();

  button.setUpPressHandler(&upPressed);
  button.setDownPressHandler(&downPressed);
  button.setStopPressHandler(&stopPressed);
  button.setUpDoublePressHandler(&upDoublePressed);
  button.setDownDoublePressHandler(&downDoublePressed);
  button.setStopDoublePressHandler(&stopDoublePressed);

  digitalWrite(PIN_SHUTTER1_UPDOWN, HIGH);
  digitalWrite(PIN_SHUTTER1_PROCESS, HIGH);

  pinMode(PIN_SHUTTER1_UPDOWN,OUTPUT);
  pinMode(PIN_SHUTTER1_PROCESS,OUTPUT);

  //shutter.setup();
}

void HomieIndependentLoop()
{
  button.loop();
  shutter1.loop();
/*
  bool upState = button.isUpPressed();
  bool downState = button.isDownPressed();
  bool stopState = button.isStopPressed();
  bool doubleState = button.isDoublePressed();

  if(upState != lastUpState || downState != lastDownState || stopState != lastStopState || doubleState != lastDoubleState)
  {
    //Homie.getLogger() << millis() << ": up[" << upState << "] - down[" << downState << "] - stop[" << stopState
//      << "] - double[" << doubleState << "]" << endl;

    if(upState && !lastUpState)
    {
      //Homie.getLogger() << "Shutter1 consigne 0" << endl;
      shutter1.setLevel(0);
    }

    if(downState && !lastDownState)
    {
      //Homie.getLogger() << "Shutter1 consigne 100" << endl;
      shutter1.setLevel(100);
    }

    if(stopState && !lastStopState)
    {
      //Homie.getLogger() << "Shutter1 stop" << endl;
      shutter1.stop();
    }

    lastUpState = upState;
    lastDownState = downState;
    lastStopState = stopState;
    lastDoubleState = doubleState;
  }
  */
}

void loop() {
  Homie.loop();
  HomieIndependentLoop();
}
