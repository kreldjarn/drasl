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
    setSize (200, 200);
}

DraslAudioProcessorEditor::~DraslAudioProcessorEditor()
{
}

//==============================================================================
void DraslAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Midi Volume", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void DraslAudioProcessorEditor::resized()
{
    midi_volume.setBounds(40, 30, 20, getHeight()-60);
}

void DraslAudioProcessorEditor::sliderValueChanged(Slider *slider) {
    processor.note_on_vel = midi_volume.getValue();
}
