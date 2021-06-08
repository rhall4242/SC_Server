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
//  juce::String name {"unnamed"};

  void process(int64_t ticks) override;

  void setValue(MidiNoteValue val) { value = val; }
  MidiNoteValue getValue() { return value; }

private:

  MidiNoteValue value;

};
