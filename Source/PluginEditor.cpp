/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

extern int testmain(int, const char*[]);
const char * argv[] {"SC_Server"};

//==============================================================================
SC_ServerAudioProcessorEditor::SC_ServerAudioProcessorEditor (SC_ServerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    menuButton.onClick = menuClicked;
    addAndMakeVisible(menuButton);
//    testmain(1, argv);
}

SC_ServerAudioProcessorEditor::~SC_ServerAudioProcessorEditor()
{
}

//==============================================================================
void SC_ServerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SC_Server", getLocalBounds(), juce::Justification::centred, 1);
}

void SC_ServerAudioProcessorEditor::resized()
{
    menuButton.setBounds(15, 15, 50, 20);
}

void SC_ServerAudioProcessorEditor::mainMenu()
{
    juce::PopupMenu m;
    m.addItem (1, "Load Layout");
 
    const int result = m.show();
 
    if (result == 0)
    {
        // user dismissed the menu without picking anything
    }
    else if (result == 1)
    {
      audioProcessor.loadLayout();
    }      


}

