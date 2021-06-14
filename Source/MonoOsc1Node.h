/*
  ==============================================================================

    MonoOsc1Node.h
    Created: 13 Jun 2021 7:40:35pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

class MonoOsc1Node : virtual public Node
{
public:
  MonoOsc1Node(juce::String nm);

  NodeType type {Mono_Osc_1_Node};

  void process(int64_t ticks, int sample) override;

  void setValue(AudioSampleValue* val) { value = val; }
  AudioSampleValue* getValue() { return value; }

private:
  MidiNoteValue* defaultNote = new MidiNoteValue();
  SwitchValue* defaultGate = new SwitchValue(false);
  AudioSampleValue* defaultValue = new AudioSampleValue();
  ScalarValue* defaultLevel = new ScalarValue(1.0f);
  AudioSampleValue* defaultFM = new AudioSampleValue();
  ScalarValue* defaultRatio = new ScalarValue(1.0f);
  SwitchValue* gate = defaultGate;
  MidiNoteValue* note = defaultNote;
  AudioSampleValue* value = defaultValue;
  ScalarValue* level = defaultLevel;
  AudioSampleValue* fm = defaultFM;
  ScalarValue* ratio = defaultRatio;
};