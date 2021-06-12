/*
  ==============================================================================

    Node.h
    Created: 3 Jun 2021 2:30:54pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Value.h"
#include "Connector.h"

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
  bool ready {false};
  bool isReady() { return ready; }

  virtual void process(int64_t ticks) = 0;
};

class NodeTree : virtual public std::map<juce::String, Node*>
{
public:
  void addNode(Node *node);
  Node *getByName(juce::String name);
  void clearAllReadyFlags();
};