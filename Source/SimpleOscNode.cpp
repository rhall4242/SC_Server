/*
  ==============================================================================

    SimpleOscNode.cpp
    Created: 10 Jun 2021 1:22:13pm
    Author:  rhall

  ==============================================================================
*/

#include "SimpleOscNode.h"

SimpleOscNode::SimpleOscNode(juce::String nm)
{
  name = juce::String(nm);
  MidiInputConnector* in = new MidiInputConnector("MidiInput", this);
  inputs[in->getName()] = in;
  MonoControlInputConnector* gate = new MonoControlInputConnector("GateInput", this);
  inputs[gate->getName()] = gate;
  MonoAudioOutputConnector* out = new MonoAudioOutputConnector("AudioOutput", this);
  outputs[out->getName()] = out;
}

void SimpleOscNode::process(int64_t ticks)
{
  MidiInputConnector* in = dynamic_cast<MidiInputConnector*>(inputs["MidiInput"]);
  if (in->isConnected())
  {
    MidiOutputConnector* from = dynamic_cast<MidiOutputConnector*>(in->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks);
    }
    note = static_cast<MidiNoteValue*>(from->value);
  }
  else
  {
    note = defaultNote;
  }
  MonoControlInputConnector* gateIn = dynamic_cast<MonoControlInputConnector*>(inputs["GateInput"]);
  if (gateIn->isConnected())
  {
    MonoControlOutputConnector* from = dynamic_cast<MonoControlOutputConnector*>(gateIn->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks);
    }
    gate = static_cast<SwitchValue*>(from->value);
  }
  else
  {
    gate = defaultGate;
  }
  if (gate->switchval)
  {
    auto freq = juce::MidiMessage::getMidiNoteInHertz(note->note);
    auto delta = (ticks - note->start_time) / (float) std::chrono::system_clock::period::den;
    auto period = 1.0f / freq;
    auto phase = (fmod(delta, period) / period) * juce::MathConstants<float>::twoPi;
    auto vel = ((float) note->vel) / 127.0;
    value->sample = vel * sin(phase);
  }
  else
  {
    value->sample = 0.0f;
  }
  MonoAudioOutputConnector* output = dynamic_cast<MonoAudioOutputConnector*>(outputs["AudioOutput"]);
  output->value = value;
  ready = true;

}