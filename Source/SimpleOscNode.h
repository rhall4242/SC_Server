/*
  ==============================================================================

    SimpleOscNode.h
    Created: 10 Jun 2021 1:22:13pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

class SimpleOscNode : virtual public Node
{
public:
  SimpleOscNode(juce::String nm);

  NodeType type {Simple_Osc_Node};

  void process(int64_t ticks) override;

  void setValue(AudioSampleValue val) { value = val; }
  AudioSampleValue getValue() { return value; }

private:

  AudioSampleValue value;

};
