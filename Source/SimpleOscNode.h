/*
  ==============================================================================

    SimpleOscNode.h
    Created: 10 Jun 2021 1:22:13pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

class SimpleOscNode : virtual public Node
{
public:
  SimpleOscNode(juce::String nm);

  void process(int64_t ticks, int sample) override;

  void setValue(AudioSampleValue* val) { value = val; }
  AudioSampleValue* getValue() { return value; }
  void updateConnections() override {}

private:
  MidiNoteValue* defaultNote = new MidiNoteValue();
  SwitchValue* defaultGate = new SwitchValue(false);
  AudioSampleValue* defaultValue = new AudioSampleValue();
  SwitchValue* gate = defaultGate;
  MidiNoteValue* note = defaultNote;
  AudioSampleValue* value = defaultValue;

};
