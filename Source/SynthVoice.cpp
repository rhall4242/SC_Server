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
  nodeInit();
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound *sound)
{
  return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
  MidiInputNode* node = dynamic_cast<MidiInputNode*>(nodeTree.getByName("SysMidiInputNode"));
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
  MidiInputNode* node = dynamic_cast<MidiInputNode*>(nodeTree.getByName("SysMidiInputNode"));
  MidiNoteValue* val = node->getValue();
  val->start_time = std::chrono::system_clock::now().time_since_epoch().count();
  val->sample = 0;
  val->note = 0;
  val->vel = 0;
  node->setValue(val);
  SwitchValue* gate = new SwitchValue{false};
  gate->switchval = false;
  node->setGate(gate);
//  if (!allowTailOff ) //|| !adsr.isActive())
//  {
//    clearCurrentNote();
//  }
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
  AudioOutputNode* out = dynamic_cast<AudioOutputNode*>(nodeTree["SysAudioOutputNode"]);
  for (int i = 0; i < numSamples; i++)
  {
    nodeTree.clearAllReadyFlags();
    out->process(ticks, i);
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
      auto val = out->getValue(channel);
      synthBuffer.setSample(channel, i, val->sample);
    }
  }
  gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
//  adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
  for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
  {
    outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
  }
}


void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
//  adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::nodeInit()
{
    MidiInputNode* midiInputNode = new MidiInputNode("SysMidiInputNode");
    nodeTree.addNode(midiInputNode);
    MonoOsc1Node* monoOsc1Node = new MonoOsc1Node("SysMonoOsc1Node");
    nodeTree.addNode(monoOsc1Node);
    MonoOsc1Node* monoOsc1Node2 = new MonoOsc1Node("SysMonoOsc1Node2");
    nodeTree.addNode(monoOsc1Node2);
    AudioOutputNode* audioOutputNode = new AudioOutputNode("SysAudioOutputNode");
    nodeTree.addNode(audioOutputNode);
    Value8Node* value8Node = new Value8Node("Value8Node");
    nodeTree.addNode(value8Node);
    MSEGNode* msegNode = new MSEGNode("MSEGNode");
    msegNode->loadDesc("/home/rhall/JUCE/projects/SC_Server/TestMSEG.json");
    nodeTree.addNode(msegNode);
    MSEGNode* msegNode2 = new MSEGNode("MSEGNode2");
    msegNode2->loadDesc("/home/rhall/JUCE/projects/SC_Server/TestMSEG2.json");
    nodeTree.addNode(msegNode2);
    MonoControlOutputConnector* trueOut = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["TrueOutput"]);
    MidiOutputConnector* midiOut = dynamic_cast<MidiOutputConnector*>(midiInputNode->outputs["MidiOutput"]);
    MidiInputConnector* midiIn =  dynamic_cast<MidiInputConnector*>(monoOsc1Node->inputs["MidiInput"]);
    Connection *c1 = new Connection();
    c1->connect(midiOut, midiIn);
    MonoControlOutputConnector* gateOut = dynamic_cast<MonoControlOutputConnector*>(midiInputNode->outputs["GateOutput"]);
    MonoControlInputConnector* gateIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["GateInput"]);
    Connection *c2 = new Connection();
    c2->connect(trueOut, gateIn);
    MonoAudioOutputConnector* audioOut = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node->outputs["AudioOutput"]);
    MonoAudioInputConnector* audioIn =  dynamic_cast<MonoAudioInputConnector*>(audioOutputNode->inputs["AudioInput"]);
    Connection *c3 = new Connection();
    c3->connect(audioOut, audioIn);
    MidiInputConnector* midiIn2 =  dynamic_cast<MidiInputConnector*>(monoOsc1Node2->inputs["MidiInput"]);
    Connection *c4 = new Connection();
    c4->connect(midiOut, midiIn2);
    MonoControlInputConnector* gateIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["GateInput"]);
    Connection *c5 = new Connection();
    c5->connect(trueOut, gateIn2);
    MonoAudioOutputConnector* audioOut2 = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node2->outputs["AudioOutput"]);
    MonoAudioInputConnector* fmIn =  dynamic_cast<MonoAudioInputConnector*>(monoOsc1Node->inputs["FMInput"]);
    Connection *c6 = new Connection();
    c6->connect(audioOut2, fmIn);
    MonoControlOutputConnector* ratioOut = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["V1Output"]);
    MonoControlInputConnector* ratioIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["RatioInput"]);
    Connection *c7 = new Connection();
    c7->connect(ratioOut, ratioIn);
    MonoControlInputConnector* gateIn3 =  dynamic_cast<MonoControlInputConnector*>(msegNode->inputs["GateInput"]);
    Connection *c8 = new Connection();
    c8->connect(gateOut, gateIn3);
    MonoControlInputConnector* levelIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["LevelInput"]);
    MonoControlOutputConnector* msegOut = dynamic_cast<MonoControlOutputConnector*>(msegNode->outputs["MSEGOutput"]);
    Connection *c9 = new Connection();
    c9->connect(msegOut, levelIn);
    MonoControlInputConnector* gateIn4 =  dynamic_cast<MonoControlInputConnector*>(msegNode2->inputs["GateInput"]);
    Connection *c10 = new Connection();
    c10->connect(gateOut, gateIn4);
    MonoControlInputConnector* levelIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["LevelInput"]);
    MonoControlOutputConnector* msegOut2 = dynamic_cast<MonoControlOutputConnector*>(msegNode2->outputs["MSEGOutput"]);
    Connection *c11 = new Connection();
    c11->connect(msegOut2, levelIn2);

}
