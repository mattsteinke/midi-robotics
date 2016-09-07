
/*MIDI TO ON/OFF (TTL)
• Listens for 8 MIDI note on/off messages and turns SS Relays on/off
• notesTimeout function protects the high current deviced from being left on incase a note off message is not heard
*/

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

// PINS
#define LED1 13 // LED - FLASH NOTE ON/OFF(MIDI) 
int outPutPin[8] = {3, 4, 5, 6, 7, 8, 9, 10};
/////////////////////////////////
int timeOut = 5000; // Duration for out timeout function
long noteStart[8]; // an array to keep track of note state markers
boolean noteOn[8]; // array of note state booleans
int chan = MIDI_CHANNEL_OMNI; // set MIDI channel here - replace MIDI_CHANNEL_OMNI with a channel number 1-16

// MIDI NOTES (INPUT)
int theNote[8] = {36, 38, 40, 41, 43, 45, 47, 48}; // increase the array for more notes

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
pinMode (LED1, OUTPUT);
for (int i = 0; i < 8; i = i + 1) // increase from 8 for more outputs
{
pinMode (outPutPin[i], OUTPUT);
}
MIDI.begin(chan); // Initialize the Midi Library - argument for channel number
MIDI.setHandleNoteOn(myHandleNoteOn);
MIDI.setHandleNoteOff(myHandleNoteOff);
//MIDI.setHandleControlChange(myControlChange); // This is for VolumeCC
}
void loop()
{
MIDI.read(); // Continuously check if MIDI data has been received.
notesTimeout();
}
///////////////////////////////// NOTE ON FUNCTION
void myHandleNoteOn(byte channel, byte pitch, byte velocity)
{
for (int i = 0; i < 8; i = i + 1) // increase for more
{
if (pitch == theNote[i])
{
digitalWrite(LED1, HIGH);
outPutPin[i] = HIGH;
noteStart[i] = millis(); // mark the time
noteOn[i] = true; // store the state
}
}
}

///////////////////////////////// MIDI NOTE OFF FUNCTION
void myHandleNoteOff(byte channel, byte pitch, byte velocity)
{
for (int i = 0; i < 8; i = i + 1) // increase for more
{
if (pitch == theNote[i])
{
digitalWrite(LED1, LOW);
outPutPin[i] = LOW;
noteOn[myPin] = false;
}

}
}
///////////////////////////////// Timeout Function -- this is to prevent our output from staying on if we don't get a note off message after a certain peroid (not all midi sequencers send an "all off" message when they stop playback)
void notesTimeout()
{
for(int i; i < 8; i++)
{
if(millis() - noteStart[i] > timOut && noteOn[i] == true)
{
digitalWrite(outPutPin[i], LOW);
noteOn[i] == false;
}

}
} 
