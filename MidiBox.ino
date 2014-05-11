/**
 *
 *
 *
 */
 #include <MIDI.h>

// Constant represents the Digital I/O pins of the arduino.
const int buttons[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// These arrays represents states of buttons and of what has been
// sent to the remote MIDI device, one state for each button
int buttonStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int midiStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int toggleStatus[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
long toggleTimer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/**
 * Set up the arduino program.
 */
void setup()
{
  // Set up all the pins as an input
  for(int i=0; i < 10; i++)
  {
    pinMode(buttons[i], INPUT);
  }

  // Tell MIDI to read all channels though we are not going to
  // user it at the moment it is needed to initialize the library
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  // Set up all the p
  for(int btnIdx=0; btnIdx < 10; btnIdx++)
  {
    // Get the current state of the button at btnIdx
    buttonStatus[btnIdx] = digitalRead(buttons[btnIdx]);

    // If the button state goes HIGH toggle the midiStatus.
    if(buttonStatus[btnIdx] == HIGH && toggleStatus[btnIdx] == LOW  && toggleTimer[btnIdx] < (millis() - 400))
    {
      // is used to keep us from sending a constant button push during the loop. 
      toggleStatus[btnIdx] = HIGH;
      toggleTimer[btnIdx] = millis();
      
      // If the MIDI status is LOW change it HIGH
      // else the MIDI status is HIGH change it LOW
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

    // If we're released the button then we can set the toggleStatus LOW
    // to prepare for the next time we push the button.
    if(buttonStatus[btnIdx] == LOW)
    {
      toggleStatus[btnIdx] = LOW;
    }   
  }    
}
