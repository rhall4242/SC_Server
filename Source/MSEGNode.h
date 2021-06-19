/*
  ==============================================================================

    MSEGNode.h
    Created: 16 Jun 2021 5:34:17am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

typedef std::pair<int, float> MSEG_Pt;

class MSEGDesc
{
public:
    int sample_rate;
    bool sustain;
    MSEG_Pt sustain_point;
    std::vector<MSEG_Pt> pointList;
};

enum MSEGState
{
  Idle = 1,
  Play,
  Sustain,
  Tailoff
};

class MSEGNode : virtual public Node
{
public:
  MSEGNode(juce::String nm);

  NodeType type {MSEG_Node};

  void process(int64_t ticks, int sample) override;

  void updateConnections() override;

  MSEGDesc desc;

  void loadDesc(juce::String filename);
  void saveDesc(juce::String filename, MSEGDesc desc);

private:

  MonoControlInputConnector* gateIn;
  MonoControlOutputConnector* gateFrom;
  MonoControlInputConnector* levelIn;
  MonoControlOutputConnector* levelFrom;
  MonoControlOutputConnector* output;

  SwitchValue* defaultGate = new SwitchValue(false);
  ScalarValue* defaultLevel = new ScalarValue(1.0f);
  SwitchValue* gate = defaultGate;
  ScalarValue* level = defaultLevel;
  ScalarValue * value = new ScalarValue(0.0f);

  bool lastGate {false};
  MSEGState state {Idle};
  int mseg_sample {0};
  float scale {1.0f};
};
