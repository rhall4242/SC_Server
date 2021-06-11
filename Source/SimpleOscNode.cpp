/*
  ==============================================================================

    SimpleOscNode.cpp
    Created: 10 Jun 2021 1:22:13pm
    Author:  rhall

  ==============================================================================
*/

#include "SimpleOscNode.h"

SimpleOscNode::SimpleOscNode(juce::String nm)
{
  name = juce::String(nm);
  MidiInputConnector* in = new MidiInputConnector("MidiInput", this);
  inputs[in->getName()] = in;
  MonoControlInputConnector* gate = new MonoControlInputConnector("GateInput", this);
  inputs[gate->getName()] = gate;
  MonoAudioOutputConnector* out = new MonoAudioOutputConnector("AudioOutput", this);
  outputs[out->getName()] = out;
}

void SimpleOscNode::process(int64_t ticks)
{

}