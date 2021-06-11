/*
  ==============================================================================

    AudioOutputNode.h
    Created: 10 Jun 2021 3:29:06pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Node.h"

class AudioOutputNode : virtual public Node
{
public:
  AudioOutputNode(juce::String nm);

  NodeType type {Audio_Output_Node};

  void process(int64_t ticks) override;

  void setValue(AudioSampleValue val) { value = val; }
  AudioSampleValue getValue() { return value; }

private:

  AudioSampleValue value;

};
