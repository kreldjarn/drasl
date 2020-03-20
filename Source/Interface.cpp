/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Interface.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Interface::Interface ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    size.reset (new Slider ("Size"));
    addAndMakeVisible (size.get());
    size->setRange (0, 50, 1);
    size->setSliderStyle (Slider::LinearHorizontal);
    size->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    size->setColour (Slider::thumbColourId, Colours::azure);
    size->addListener (this);

    size->setBounds (8, 8, 224, 24);

    slop.reset (new Slider ("Slop"));
    addAndMakeVisible (slop.get());
    slop->setRange (1, 5000, 0);
    slop->setSliderStyle (Slider::LinearHorizontal);
    slop->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slop->setColour (Slider::thumbColourId, Colours::azure);
    slop->addListener (this);

    slop->setBounds (8, 40, 224, 24);

    gain.reset (new Slider ("Gain"));
    addAndMakeVisible (gain.get());
    gain->setRange (0, 1, 0);
    gain->setSliderStyle (Slider::LinearHorizontal);
    gain->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gain->setColour (Slider::thumbColourId, Colours::azure);
    gain->addListener (this);

    gain->setBounds (8, 72, 224, 24);

    sizeLabel.reset (new Label ("size label",
                                TRANS("Size")));
    addAndMakeVisible (sizeLabel.get());
    sizeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    sizeLabel->setJustificationType (Justification::centredLeft);
    sizeLabel->setEditable (false, false, false);
    sizeLabel->setColour (TextEditor::textColourId, Colours::black);
    sizeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    sizeLabel->setBounds (232, 8, 150, 24);

    slopLabel.reset (new Label ("slop label",
                                TRANS("Slop")));
    addAndMakeVisible (slopLabel.get());
    slopLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    slopLabel->setJustificationType (Justification::centredLeft);
    slopLabel->setEditable (false, false, false);
    slopLabel->setColour (TextEditor::textColourId, Colours::black);
    slopLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    slopLabel->setBounds (232, 40, 150, 24);

    gainLabel.reset (new Label ("gain label",
                                TRANS("Gain")));
    addAndMakeVisible (gainLabel.get());
    gainLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainLabel->setJustificationType (Justification::centredLeft);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (TextEditor::textColourId, Colours::black);
    gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    gainLabel->setBounds (232, 72, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Interface::~Interface()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    size = nullptr;
    slop = nullptr;
    gain = nullptr;
    sizeLabel = nullptr;
    slopLabel = nullptr;
    gainLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Interface::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff828282));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Interface::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Interface::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == size.get())
    {
        //[UserSliderCode_size] -- add your slider handling code here..
        //[/UserSliderCode_size]
    }
    else if (sliderThatWasMoved == slop.get())
    {
        //[UserSliderCode_slop] -- add your slider handling code here..
        //[/UserSliderCode_slop]
    }
    else if (sliderThatWasMoved == gain.get())
    {
        //[UserSliderCode_gain] -- add your slider handling code here..
        //[/UserSliderCode_gain]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int Interface::getSize() {
    return (int)size->getValue();
}

float Interface::getSlop() {
    return slop->getValue();
}

float Interface::getGain() {
    return gain->getValue();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Interface" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff828282"/>
  <SLIDER name="Size" id="1885005a6e82f75" memberName="size" virtualName=""
          explicitFocusOrder="0" pos="8 8 224 24" thumbcol="fff0ffff" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Slop" id="d356e12a7b994d7b" memberName="slop" virtualName=""
          explicitFocusOrder="0" pos="8 40 224 24" thumbcol="fff0ffff"
          min="0.0" max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Gain" id="77c88158f110ed76" memberName="gain" virtualName=""
          explicitFocusOrder="0" pos="8 72 224 24" thumbcol="fff0ffff"
          min="0.0" max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="size label" id="1738b7fb75f04bec" memberName="sizeLabel"
         virtualName="" explicitFocusOrder="0" pos="232 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Size" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="slop label" id="42a5996b1b0ef9e1" memberName="slopLabel"
         virtualName="" explicitFocusOrder="0" pos="232 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Slop" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="gain label" id="72ddca76aaf2fcf6" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="232 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

