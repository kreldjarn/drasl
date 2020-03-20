/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DraslAudioProcessorEditor::DraslAudioProcessorEditor (DraslAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(interface);
    setSize (600, 400);
}

DraslAudioProcessorEditor::~DraslAudioProcessorEditor()
{
}

//==============================================================================
void DraslAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    interface.paint(g);
}

void DraslAudioProcessorEditor::resized()
{
    interface.resized();
}

void DraslAudioProcessorEditor::sliderValueChanged(Slider *slider) {
    interface.sliderValueChanged(slider);
    std::cout << "DraslAudioProcessorEditor::sliderValueChanged()" << std::endl;
    processor.setSize(interface.getSize());
    processor.setSlop(interface.getSlop());
    processor.setGainMultiplier(interface.getGain());
}
