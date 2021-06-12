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
  MonoAudioInputConnector* in = dynamic_cast<MonoAudioInputConnector*>(inputs["AudioInput"]);
  if (in->isConnected())
  {
    MonoAudioOutputConnector* from = dynamic_cast<MonoAudioOutputConnector*>(in->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks);
    }
    value = static_cast<AudioSampleValue*>(from->value);
  }
  else
  {
    value = defaultValue;
  }
  ready = true;
}