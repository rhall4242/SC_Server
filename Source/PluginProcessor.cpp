/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SC_ServerAudioProcessor::SC_ServerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    for (int i = 0; i < maxPolyphony; i++)
    {
        synth.addVoice(new SynthVoice(&synth));
    }
    nodeInit();
    std::cout << "SC_Server Initialized" << std::endl;
}

SC_ServerAudioProcessor::~SC_ServerAudioProcessor()
{
}

void SC_ServerAudioProcessor::nodeInit()
{
    MidiInputNode* midiInputNode = new MidiInputNode("SysMidiInputNode");
    synth.nodeTree.addNode(midiInputNode);
    MonoOsc1Node* monoOsc1Node = new MonoOsc1Node("SysMonoOsc1Node");
    synth.nodeTree.addNode(monoOsc1Node);
    MonoOsc1Node* monoOsc1Node2 = new MonoOsc1Node("SysMonoOsc1Node2");
    synth.nodeTree.addNode(monoOsc1Node2);
    AudioOutputNode* audioOutputNode = new AudioOutputNode("SysAudioOutputNode");
    synth.nodeTree.addNode(audioOutputNode);
    Value8Node* value8Node = new Value8Node("Value8Node");
    synth.nodeTree.addNode(value8Node);
    MidiOutputConnector* midiOut = dynamic_cast<MidiOutputConnector*>(midiInputNode->outputs["MidiOutput"]);
    MidiInputConnector* midiIn =  dynamic_cast<MidiInputConnector*>(monoOsc1Node->inputs["MidiInput"]);
    Connection *c1 = new Connection();
    c1->connect(midiOut, midiIn);
    MonoControlOutputConnector* gateOut = dynamic_cast<MonoControlOutputConnector*>(midiInputNode->outputs["GateOutput"]);
    MonoControlInputConnector* gateIn =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node->inputs["GateInput"]);
    Connection *c2 = new Connection();
    c2->connect(gateOut, gateIn);
    MonoAudioOutputConnector* audioOut = dynamic_cast<MonoAudioOutputConnector*>(monoOsc1Node->outputs["AudioOutput"]);
    MonoAudioInputConnector* audioIn =  dynamic_cast<MonoAudioInputConnector*>(audioOutputNode->inputs["AudioInput"]);
    Connection *c3 = new Connection();
    c3->connect(audioOut, audioIn);
    MidiInputConnector* midiIn2 =  dynamic_cast<MidiInputConnector*>(monoOsc1Node2->inputs["MidiInput"]);
    Connection *c4 = new Connection();
    c4->connect(midiOut, midiIn2);
    MonoControlInputConnector* gateIn2 =  dynamic_cast<MonoControlInputConnector*>(monoOsc1Node2->inputs["GateInput"]);
    MonoControlOutputConnector* trueOut = dynamic_cast<MonoControlOutputConnector*>(value8Node->outputs["TrueOutput"]);
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

}

//==============================================================================
const juce::String SC_ServerAudioProcessor::getName() const
{
    return "SC_Server";
}

bool SC_ServerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SC_ServerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SC_ServerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SC_ServerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SC_ServerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SC_ServerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SC_ServerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SC_ServerAudioProcessor::getProgramName (int index)
{
    return {};
}

void SC_ServerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SC_ServerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SC_ServerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SC_ServerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SC_ServerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SC_ServerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SC_ServerAudioProcessor::createEditor()
{
    return new SC_ServerAudioProcessorEditor (*this);
}

//==============================================================================
void SC_ServerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SC_ServerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SC_ServerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout SC_ServerAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat> ("GAIN", "Gain", juce::NormalisableRange<float> {0.01f, 1.0f,  0.01f, 0.3f}, 0.25f));

    return {params.begin(), params.end()};
}
