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
  MidiOutputConnector* out = new MidiOutputConnector("MidiOutput", this);
  outputs[out->getName()] = out;
  MonoControlOutputConnector* gate = new MonoControlOutputConnector("GateOutput", this);
  outputs[gate->getName()] = gate;
}

void MidiInputNode::process(int64_t ticks, int sample)
{
  value->sample++;
  MidiOutputConnector* output = dynamic_cast<MidiOutputConnector*>(outputs["MidiOutput"]);
  output->value = value;
  MonoControlOutputConnector* gateOut = dynamic_cast<MonoControlOutputConnector*>(outputs["GateOutput"]);
  gateOut->value = gate;
  ready = true;
}