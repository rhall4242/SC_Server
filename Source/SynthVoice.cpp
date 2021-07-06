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
    clearCurrentNote();
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
  if (!isVoiceActive())
    return;
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
    createConnection(midiOut, midiIn);
    MonoControlOutputConnector* gateOut = dynamic_cast<MonoControlOutputConnector*>(midiInputNode->outputs["GateOutput"]);
    MonoControlInputConnector* gateIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["GateInput"]);
    createConnection(trueOut, gateIn);
    MonoAudioOutputConnector* audioOut = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node->outputs["AudioOutput"]);
    MonoAudioInputConnector* audioIn =  dynamic_cast<MonoAudioInputConnector*>(audioOutputNode->inputs["AudioInput"]);
    createConnection(audioOut, audioIn);
    MidiInputConnector* midiIn2 =  dynamic_cast<MidiInputConnector*>(monoOsc1Node2->inputs["MidiInput"]);
    createConnection(midiOut, midiIn2);
    MonoControlInputConnector* gateIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["GateInput"]);
    createConnection(trueOut, gateIn2);
    MonoAudioOutputConnector* audioOut2 = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node2->outputs["AudioOutput"]);
    MonoAudioInputConnector* fmIn =  dynamic_cast<MonoAudioInputConnector*>(monoOsc1Node->inputs["FMInput"]);
    createConnection(audioOut2, fmIn);
    MonoControlOutputConnector* ratioOut = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["V1Output"]);
    MonoControlInputConnector* ratioIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["RatioInput"]);
    createConnection(ratioOut, ratioIn);
    MonoControlInputConnector* gateIn3 =  dynamic_cast<MonoControlInputConnector*>(msegNode->inputs["GateInput"]);
    createConnection(gateOut, gateIn3);
    MonoControlInputConnector* levelIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["LevelInput"]);
    MonoControlOutputConnector* msegOut = dynamic_cast<MonoControlOutputConnector*>(msegNode->outputs["MSEGOutput"]);
    createConnection(msegOut, levelIn);
    MonoControlInputConnector* gateIn4 =  dynamic_cast<MonoControlInputConnector*>(msegNode2->inputs["GateInput"]);
    createConnection(gateOut, gateIn4);
    MonoControlInputConnector* levelIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["LevelInput"]);
    MonoControlOutputConnector* msegOut2 = dynamic_cast<MonoControlOutputConnector*>(msegNode2->outputs["MSEGOutput"]);
    createConnection(msegOut2, levelIn2);
    MonoControlInputConnector* optionIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["OptionInput"]);
    MonoControlOutputConnector* optionOut = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["V3Output"]);
    createConnection(optionOut, optionIn);
    MonoControlInputConnector* optionIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["OptionInput"]);
    MonoControlOutputConnector* optionOut2 = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["V4Output"]);
    createConnection(optionOut, optionIn);
}

Connection* SynthVoice::createConnection(OutputConnector *in, InputConnector *out, juce::String nm)
{
  Connection *conn = new Connection(juce::String(nm));
  connectionTree.addConnection(conn);
  conn->connect(in, out);
  return conn;
}

void SynthVoice::loadLayout()
{
  connectionTree.clearTree();
  nodeTree.clearTree();
  juce::File f("/home/rhall/JUCE/projects/SC_GUI/Layout1.json");
  juce::String json = f.loadFileAsString();
  nodeTree.fromJSON(json);
  connectionTree.fromJSON(json, &nodeTree);
  MidiInputNode* midiInputNode = dynamic_cast<MidiInputNode*>(nodeTree.getByName("SysMidiInputNode"));
  MonoControlOutputConnector* gateOut = dynamic_cast<MonoControlOutputConnector*>(midiInputNode->outputs["GateOutput"]);
  MonoOsc1Node* monoOsc1Node = dynamic_cast<MonoOsc1Node*>(nodeTree.getByName("MonoOsc1Node"));
  MonoAudioOutputConnector* audioOut = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node->outputs["AudioOutput"]);
}