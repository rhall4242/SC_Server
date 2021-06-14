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
  Control,
  Scalar,
  Switch
};

class SCValue
{
public:
  ValueType type;
};

typedef uint8_t midi_note_t;
typedef uint8_t midi_vel_t;


class MidiNoteValue : public SCValue
{
public:  
  ValueType type {MidiNote};
  int64_t start_time {0};
  int sample;
  midi_note_t note {0};
  midi_vel_t vel {0};
};

class AudioSampleValue : public SCValue
{
public:  
  ValueType type {Audio};
  float sample {0.0f};
};

class ScalarValue : public SCValue
{
public:  
  ScalarValue(float v = 0.0f) { val = v; }
  ValueType type {Scalar};
  float val {0.0f};
};

class SwitchValue : public SCValue
{
public:  
  SwitchValue(bool b) {switchval = b;}
  ValueType type {Switch};
  bool switchval {false};
};
