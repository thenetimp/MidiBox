/**
 *
 *
 *
 */
 #include <MIDI.h>

const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int buttonStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int midiStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int toggleStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
long toggleTimer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/**
 * Set up the arduino program.
 */
void setup()
{
  // Set up all the pins
  for(int i=0; i < 10; i++)
  {
    pinMode(buttons[i], INPUT);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  // Set up all the p
  for(int btnIdx=0; btnIdx < 10; btnIdx++)
  {
    // Get the current state of the button at btnIdx
    buttonStatus[btnIdx] = digitalRead(buttons[btnIdx]);

    // If the button state goes high.
    if(buttonStatus[btnIdx] == HIGH && toggleStatus[btnIdx] == LOW  && toggleTimer[btnIdx] < (millis() - 400))
    {
      toggleStatus[btnIdx] = HIGH;
      toggleTimer[btnIdx] = millis();
      if(midiStatus[btnIdx] == LOW)
      {
        MIDI.sendControlChange((btnIdx+1), 127, 1);
        midiStatus[btnIdx] = HIGH;
      }
      else
      {
        MIDI.sendControlChange((btnIdx+1), 0, 1);
        midiStatus[btnIdx] = LOW;
      }
    } 

    if(buttonStatus[btnIdx] == LOW)
    {
      toggleStatus[btnIdx] = LOW;
    }   
  }    
}
