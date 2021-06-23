/*
  ==============================================================================

    MidiInputNode.cpp
    Created: 4 Jun 2021 10:05:27am
    Author:  rhall

  ==============================================================================
*/

#include "MidiInputNode.h"

MidiInputNode::MidiInputNode(juce::String nm)
{
  name = juce::String(nm);
  type = MIDI_Input_Node;
  midiOut = new MidiOutputConnector("MidiOutput", this);
  outputs[midiOut->getName()] = midiOut;
  gateOut = new MonoControlOutputConnector("GateOutput", this);
  outputs[gateOut->getName()] = gateOut;
}

void MidiInputNode::process(int64_t ticks, int sample)
{
  value->sample++;
  midiOut->value = value;
  gateOut->value = gate;
  ready = true;
}