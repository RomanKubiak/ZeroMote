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

#include "ZeroMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroVideoOverlay.h"
//[/MiscUserDefs]

//==============================================================================
ZeroMain::ZeroMain (ZeroVideoOverlay *_overlay)
    : overlay(_overlay)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (vlc = new VLCWrapper());

    addAndMakeVisible (textButton = new TextButton ("Play"));
    textButton->addListener (this);

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (true);
    textEditor->setReturnKeyStartsNewLine (true);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setColour (TextEditor::backgroundColourId, Colour (0x41ffffff));
    textEditor->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    textEditor->setColour (TextEditor::outlineColourId, Colour (0x00ffffff));
    textEditor->setText (TRANS("http://user:Jesien01.@uranus.hopto.org:8554/stream/video.mjpeg"));


    //[UserPreSize]
	vlc->attachCallback(overlay);
    //[/UserPreSize]

    setSize (640, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ZeroMain::~ZeroMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    vlc = nullptr;
    textButton = nullptr;
    textEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    vlc->setBounds (0, 0, 640, 480);
    textButton->setBounds (8, 528, 150, 24);
    textEditor->setBounds (0, 488, 640, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroMain::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
		vlc->loadMedia(textEditor->getText());
		vlc->play();
		vlc->toBack();

        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ZeroMain::moved()
{
    //[UserCode_moved] -- Add your code here...
    //[/UserCode_moved]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroMain" componentName=""
                 parentClasses="public Component" constructorParams="ZeroVideoOverlay *_overlay"
                 variableInitialisers="overlay(_overlay)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="640"
                 initialHeight="600">
  <METHODS>
    <METHOD name="moved()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="" id="8a738eb729bd9b3d" memberName="vlc" virtualName=""
                    explicitFocusOrder="0" pos="0 0 640 480" class="VLCWrapper" params=""/>
  <TEXTBUTTON name="Play" id="1991ccadb6da15cc" memberName="textButton" virtualName=""
              explicitFocusOrder="0" pos="8 528 150 24" buttonText="Play" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="e1a9b5497fb3dc28" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="0 488 640 32" bkgcol="41ffffff"
              hilitecol="0" outlinecol="ffffff" initialText="http://user:Jesien01.@uranus.hopto.org:8554/stream/video.mjpeg"
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
