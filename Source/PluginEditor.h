/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SC_ServerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SC_ServerAudioProcessorEditor (SC_ServerAudioProcessor&);
    ~SC_ServerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    juce::TextButton menuButton {"Menu"};
    std::function<void()> menuClicked {[this] (){ mainMenu();}};
    void mainMenu();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SC_ServerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SC_ServerAudioProcessorEditor)
};
