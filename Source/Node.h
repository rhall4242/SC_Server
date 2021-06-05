/*
  ==============================================================================

    Node.h
    Created: 3 Jun 2021 2:30:54pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Connector.h"
#include "Value.h"

enum NodeType
{
  MIDI_Input_Node = 1,
  Audio_Output_Node,
  Simple_Osc_Node
};

class Node
{
public:
  NodeType type;
  std::map<juce::String, InputConnector*> inputs;
  std::map<juce::String, OutputConnector*> outputs;
  juce::String name;

  virtual void process(int64_t ticks) = 0;
};