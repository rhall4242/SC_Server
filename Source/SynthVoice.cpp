/*
  ==============================================================================

    SynthVoice.cpp
    Created: 5 Jun 2021 9:52:57am
    Author:  rhall

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice(Synth* s) : synth(s)
{
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound *sound)
{
  return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
  MidiInputNode* node = dynamic_cast<MidiInputNode*>(synth->nodeTree.getByName("SysMidiInputNode"));
  MidiNoteValue* val = node->getValue();
  val->start_time = std::chrono::system_clock::now().time_since_epoch().count();
  val->sample = 0;
  val->note = midiNoteNumber;
  val->vel = (int) (velocity * 127.0f);
  node->setValue(val);
  SwitchValue* gate = new SwitchValue(true);
  gate->switchval = true;
  node->setGate(gate);

//  osc.setWaveFrequency(midiNoteNumber);
//  adsr.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
//  adsr.noteOff();
  MidiInputNode* node = dynamic_cast<MidiInputNode*>(synth->nodeTree.getByName("SysMidiInputNode"));
  MidiNoteValue* val = node->getValue();
  val->start_time = std::chrono::system_clock::now().time_since_epoch().count();
  val->sample = 0;
  val->note = 0;
  val->vel = 0;
  node->setValue(val);
  SwitchValue* gate = new SwitchValue{false};
  gate->switchval = false;
  node->setGate(gate);
  if (!allowTailOff ) //|| !adsr.isActive())
  {
    clearCurrentNote();
  }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
//  adsr.setSampleRate(sampleRate);
  juce::dsp::ProcessSpec spec;
  spec.maximumBlockSize = samplesPerBlock;
  spec.sampleRate = sampleRate;
  spec.numChannels = outputChannels;
//  osc.prepareToPlay(spec);
  gain.prepare(spec);
  gain.setGainLinear(0.35f);
  isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
  jassert(isPrepared);
//  if (!isVoiceActive())
//    return;
  synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
  synthBuffer.clear();
  juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
  auto ticks = std::chrono::system_clock::now().time_since_epoch().count();
  AudioOutputNode* out = dynamic_cast<AudioOutputNode*>(synth->nodeTree["SysAudioOutputNode"]);
  for (int i = 0; i < numSamples; i++)
  {
    synth->nodeTree.clearAllReadyFlags();
    out->process(ticks, i);
    auto val = out->getValue();
    synthBuffer.setSample(0, i, val->sample);
  }
//  osc.getNextAudioBlock(audioBlock);
  gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
//  adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
  for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
  {
      outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
  }
  /*
  if (!adsr.isActive())
  {
    clearCurrentNote();
  }
*/
}


void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
//  adsr.updateADSR(attack, decay, sustain, release);
}
