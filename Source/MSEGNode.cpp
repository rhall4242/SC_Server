/*
  ==============================================================================

    MSEGNode.cpp
    Created: 16 Jun 2021 5:34:17am
    Author:  rhall

  ==============================================================================
*/

#include "MSEGNode.h"

MSEGNode::MSEGNode(juce::String nm)
{
  name = juce::String(nm);
  MonoControlInputConnector* gate = new MonoControlInputConnector("GateInput", this);
  inputs[gate->getName()] = gate;
  MonoControlInputConnector* level = new MonoControlInputConnector("LevelInput", this);
  inputs[level->getName()] = level;
  MonoControlOutputConnector* out = new MonoControlOutputConnector("MSEGOutput", this);
  outputs[out->getName()] = out;
}

void MSEGNode::updateConnections()
{
  gateIn = dynamic_cast<MonoControlInputConnector*>(inputs["GateInput"]);
  if (gateIn->isConnected())
  {
    gateFrom = dynamic_cast<MonoControlOutputConnector*>(gateIn->from);
  }
  levelIn = dynamic_cast<MonoControlInputConnector*>(inputs["LevelInput"]);
  if (levelIn->isConnected())
  {
    levelFrom = dynamic_cast<MonoControlOutputConnector*>(levelIn->from);
  }
  output = dynamic_cast<MonoControlOutputConnector*>(outputs["MSEGOutput"]);
}

void MSEGNode::process(int64_t ticks, int sample)
{
  float retval = 0.0f;
  if (gateIn->isConnected())
  {
    Node* fromNode = gateFrom->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
    }
    gate = static_cast<SwitchValue*>(gateFrom->value);
    
    if (!gate->switchval)
    {
      if (lastGate)
      {
        state = Tailoff;
      }
    }
    else
    {
      if (!lastGate)
      {
        state = Play;
        mseg_sample = 0;
      }
    } 
    lastGate = gate->switchval;   
  }
  else
  {
    gate = defaultGate;
    return;
  }
  if (levelIn->isConnected())
  {
    Node* fromNode = levelFrom->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
    }
    level = static_cast<ScalarValue*>(levelFrom->value);
  }
  else
  {
    level = defaultLevel;
  }
  if (mseg_sample == 0)
  {
    retval = desc.pointList[0].second;
  }
  if (mseg_sample >= desc.pointList[desc.pointList.size()-1].first * scale)
  {
    retval = desc.pointList[desc.pointList.size()-1].second;
  }
  for (int i = 0; i < desc.pointList.size(); i++)
  {
    auto p1 = desc.pointList[i].first * scale;
    auto p2 = desc.pointList[i+1].first * scale;
    if (mseg_sample > p1 && mseg_sample < p2)
    {
      auto xdelta = ((float)(mseg_sample - p1)) / ((float)(p2 - p1));
      auto ydelta = desc.pointList[i+1].second - desc.pointList[i].second;
      retval = desc.pointList[i].second + (xdelta * ydelta);
    }
  }
  value->val = retval;
  output->value = value;
  ready = true;
  mseg_sample++;
}

void MSEGNode::loadDesc(juce::String filename)
{
  juce::var json = juce::JSON::parse(juce::File(filename));
  desc.sample_rate = int(json.getProperty("sample_rate", juce::var()));
  desc.sustain = bool(json.getProperty("sustain", juce::var()));
  juce::Array<juce::var>* sust = json.getProperty("sustain_point", juce::var()).getArray();
  desc.sustain_point = MSEG_Pt(int((*sust)[0]), float((*sust)[1]));
  juce::Array<juce::var>* points = json.getProperty("points", juce::var()).getArray();
  for (auto& vpt : *points)
  {
    MSEG_Pt pt = MSEG_Pt(int((vpt)[0]), float((vpt)[1]));
    desc.pointList.push_back(pt);
  }
}