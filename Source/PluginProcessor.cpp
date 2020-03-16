/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DraslAudioProcessor::DraslAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input", AudioChannelSet::stereo(), true).withOutput("Output", AudioChannelSet::stereo(), true))
{
}

DraslAudioProcessor::~DraslAudioProcessor()
{
}

//==============================================================================
const String DraslAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DraslAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DraslAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DraslAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DraslAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DraslAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DraslAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DraslAudioProcessor::setCurrentProgram (int index)
{
}

const String DraslAudioProcessor::getProgramName (int index)
{
    return {};
}

void DraslAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DraslAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    std::cout << "DraslAudioProcessor::prepareToPlay()" << std::endl;
    AudioFormatManager fm;
    fm.registerBasicFormats();
    
    junkyard.clear();
    
    AudioBuffer<float> buf;
    std::cout << "DraslAudioProcessor::prepareToPlay(): Reading files" << std::endl;
    std::string base_path = "/Users/kreldjarn/Desktop/junkbox_test/sample";
    for (int i = 0; i < 10; ++i) {
        std::string file_path = base_path + std::to_string(i) + ".wav";
        std::cout << "File: " << file_path;
        AudioFormatReader *reader = fm.createReaderFor(File(file_path));
        int len = (int)reader->lengthInSamples;
        std::cout << ", length: " << len << std::endl;
        buf = AudioBuffer<float>(2, len);
        reader->read(&buf, 0, len, 0, 1, 1);
        
        junkyard.add(buf);
        
        buf.clear();
        delete reader;
    }
    junk.setSize(5);
    junk.populate(junkyard);
    std::cout << "DraslAudioProcessor::prepareToPlay(): exiting" << std::endl;
}

void DraslAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DraslAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() == AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
        return false;
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DraslAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // For now, we trigger sample playback on all MIDI note on messages
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);) {
        if (m.isNoteOn()) {
            std::cout << "DraslAudioProcessor::processBlock(): Midi note on" << std::endl;
            junk.triggerAt(time);
        }
    }
    
    junk.processBlock(buffer);
}

//==============================================================================
bool DraslAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DraslAudioProcessor::createEditor()
{
    return new DraslAudioProcessorEditor (*this);
}

//==============================================================================
void DraslAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DraslAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DraslAudioProcessor();
}
