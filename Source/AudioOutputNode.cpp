/*
  ==============================================================================

    AudioOutputNode.cpp
    Created: 10 Jun 2021 3:29:06pm
    Author:  rhall

  ==============================================================================
*/

#include "AudioOutputNode.h"

AudioOutputNode::AudioOutputNode(juce::String nm)
{
  name = juce::String(nm);
  MonoAudioInputConnector* in = new MonoAudioInputConnector("AudioInput", this);
  inputs[in->getName()] = in;
}

void AudioOutputNode::process(int64_t ticks)
{

}