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

  void process(int64_t ticks, int sample) override;

  void setValue(AudioSampleValue *val, int channel = 0) { value = val; }
  AudioSampleValue* getValue(int channel = 0) { return value; }
  void updateConnections() override {}

private:

  AudioSampleValue *defaultValue = new AudioSampleValue();;
  AudioSampleValue *value = defaultValue;

};
