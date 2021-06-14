/*
  ==============================================================================

    MonoOsc1Node.cpp
    Created: 13 Jun 2021 7:40:35pm
    Author:  rhall

  ==============================================================================
*/

#include "MonoOsc1Node.h"

MonoOsc1Node::MonoOsc1Node(juce::String nm)
{
  name = juce::String(nm);
  MidiInputConnector* in = new MidiInputConnector("MidiInput", this);
  inputs[in->getName()] = in;
  MonoControlInputConnector* gate = new MonoControlInputConnector("GateInput", this);
  inputs[gate->getName()] = gate;
  MonoControlInputConnector* level = new MonoControlInputConnector("LevelInput", this);
  inputs[level->getName()] = level;
  MonoAudioInputConnector* fm = new MonoAudioInputConnector("FMInput", this);
  inputs[fm->getName()] = fm;
  MonoAudioInputConnector* ring = new MonoAudioInputConnector("RingInput", this);
  inputs[ring->getName()] = ring;
  MonoControlInputConnector* option = new MonoControlInputConnector("OptionInput", this);
  inputs[option->getName()] = option;
  MonoControlInputConnector* ratio = new MonoControlInputConnector("RatioInput", this);
  inputs[ratio->getName()] = ratio;
  MonoAudioOutputConnector* out = new MonoAudioOutputConnector("AudioOutput", this);
  outputs[out->getName()] = out;
}

void MonoOsc1Node::process(int64_t ticks, int sample)
{
  MidiInputConnector* in = dynamic_cast<MidiInputConnector*>(inputs["MidiInput"]);
  if (in->isConnected())
  {
    MidiOutputConnector* from = dynamic_cast<MidiOutputConnector*>(in->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
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
      fromNode->process(ticks, sample);
    }
    gate = static_cast<SwitchValue*>(from->value);
  }
  else
  {
    gate = defaultGate;
  }
  MonoControlInputConnector* levelIn = dynamic_cast<MonoControlInputConnector*>(inputs["LevelInput"]);
  if (levelIn->isConnected())
  {
    MonoControlOutputConnector* from = dynamic_cast<MonoControlOutputConnector*>(levelIn->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
    }
    level = static_cast<ScalarValue*>(from->value);
  }
  else
  {
    level = defaultLevel;
  }
  MonoAudioInputConnector* fmIn = dynamic_cast<MonoAudioInputConnector*>(inputs["FMInput"]);
  if (fmIn->isConnected())
  {
    MonoAudioOutputConnector* from = dynamic_cast<MonoAudioOutputConnector*>(fmIn->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
    }
    fm = static_cast<AudioSampleValue*>(from->value);
  }
  else
  {
    fm = defaultFM;
  }
  MonoControlInputConnector* ratioIn = dynamic_cast<MonoControlInputConnector*>(inputs["RatioInput"]);
  if (ratioIn->isConnected())
  {
    MonoControlOutputConnector* from = dynamic_cast<MonoControlOutputConnector*>(ratioIn->from);
    Node* fromNode = from->owner;
    if (!fromNode->isReady())
    {
      fromNode->process(ticks, sample);
    }
    ratio = static_cast<ScalarValue*>(from->value);
  }
  else
  {
    ratio = defaultRatio;
  }
  if (gate->switchval)
  {
    auto freq = juce::MidiMessage::getMidiNoteInHertz(note->note) * ratio->val;
    auto delta = ((float) note->sample) / 48000.0f;
    auto period = 1.0f / freq;
    auto phase = (fmod(delta, period) / period) * juce::MathConstants<float>::twoPi;
    auto vel = ((float) note->vel) / 127.0;
    auto lev = level->val;
    value->sample = lev * vel * sin(phase + sin(fm->sample * juce::MathConstants<float>::pi));
  }
  else
  {
    value->sample = 0.0f;
  }
  MonoAudioOutputConnector* output = dynamic_cast<MonoAudioOutputConnector*>(outputs["AudioOutput"]);
  output->value = value;
  ready = true;

}