/*
  ==============================================================================

    Value.h
    Created: 3 Jun 2021 1:26:20pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <cstdint>

enum ValueType
{
  MidiNote = 1,
  OSC,
  Audio,
  Control
};

class SCValue
{
public:
  ValueType type;
};

typedef uint8_t midi_note_t;
typedef uint8_t midi_vel_t;


class MidiNoteValue : virtual public SCValue
{
public:  
  ValueType type {MidiNote};
  midi_note_t note;
  midi_vel_t vel;
};

class AudioSampleValue : virtual public SCValue
{
public:  
  ValueType type {Audio};
  float sample;
};
