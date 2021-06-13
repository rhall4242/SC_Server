/*
  ==============================================================================

    MidiInputNode.h
    Created: 4 Jun 2021 10:05:27am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

class MidiInputNode : virtual public Node
{
public:
  MidiInputNode(juce::String nm);

  NodeType type {MIDI_Input_Node};

  void process(int64_t ticks, int sample) override;

  void setValue(MidiNoteValue* val) { value = val; }
  MidiNoteValue* getValue() { return value; }
  void setGate(SwitchValue* g) { gate = g; }
  SwitchValue* getGate() { return gate; }

private:

  MidiNoteValue* value = new MidiNoteValue();;
  SwitchValue* gate = new SwitchValue(false);

};
