/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ZeroVideoOverlay.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ZeroVideoOverlay::ZeroVideoOverlay ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (bottomState = new Label ("bottom",
                                                TRANS("--:--:--")));
    bottomState->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bottomState->setJustificationType (Justification::centred);
    bottomState->setEditable (false, false, false);
    bottomState->setColour (TextEditor::textColourId, Colours::black);
    bottomState->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::Rotary);
    slider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    slider->setColour (Slider::backgroundColourId, Colours::white);
    slider->setColour (Slider::thumbColourId, Colour (0xbeff0ea6));
    slider->setColour (Slider::trackColourId, Colours::black);
    slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x84ffffff));
    slider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (320, 200);


    //[Constructor] You can add your own custom stuff here..

	ENetAddress address;
	ENetEvent event;
	ENetPeer *peer;
	ENetHost *client;

	if (enet_initialize () != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
	}

    //[/Constructor]
}

ZeroVideoOverlay::~ZeroVideoOverlay()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bottomState = nullptr;
    slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroVideoOverlay::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroVideoOverlay::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    bottomState->setBounds (0, getHeight() - 24, proportionOfWidth (1.0000f), 24);
    slider->setBounds (getWidth() - 64, getHeight() - 64, 64, 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroVideoOverlay::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroVideoOverlay::vlcTimeChanged(int64_t newTime)
{
	MessageManagerLock mmlock;
	bottomState->setText(String(newTime),sendNotificationAsync);
}
void ZeroVideoOverlay::vlcPaused()
{

}
void ZeroVideoOverlay::vlcStarted()
{

}
void ZeroVideoOverlay::vlcStopped()
{

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroVideoOverlay" componentName=""
                 parentClasses="public Component, public VLCEventCallback" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="320" initialHeight="200">
  <BACKGROUND backgroundColour="0"/>
  <LABEL name="bottom" id="436cf21e24ae3409" memberName="bottomState"
         virtualName="" explicitFocusOrder="0" pos="0 24R 100% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="--:--:--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="f10b34363fa15f96" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="64R 64R 64 64" bkgcol="ffffffff"
          thumbcol="beff0ea6" trackcol="ff000000" rotaryslideroutline="84ffffff"
          min="0" max="10" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
