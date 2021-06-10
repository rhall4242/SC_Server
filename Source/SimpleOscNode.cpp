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
  MidiInputConnector* in = new MidiInputConnector("MidiInput");
  inputs[in->getName()] = in;
  MonoAudioOutputConnector* out = new MonoAudioOutputConnector("AudioOutput");
  outputs[out->getName()] = out;
}

void SimpleOscNode::process(int64_t ticks)
{

}