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
  MidiOutputConnector* out = new MidiOutputConnector("MidiOutput");
  outputs[out->getName()] = out;
}

void MidiInputNode::process(int64_t ticks)
{

}