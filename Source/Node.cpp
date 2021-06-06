/*
  ==============================================================================

    Node.cpp
    Created: 3 Jun 2021 2:30:54pm
    Author:  rhall

  ==============================================================================
*/

#include "Node.h"

void NodeTree::addNode(Node* node)
{
  juce::String name = node->name;
  insert(std::pair(name, node));
}

Node* NodeTree::getByName(juce::String name)
{
  return (*this)[name];
}