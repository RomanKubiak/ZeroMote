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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "VLCWrapper.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ZeroVideoOverlay  : public Component,
                          public VLCEventCallback,
                          public Slider::Listener
{
public:
    //==============================================================================
    ZeroVideoOverlay ();
    ~ZeroVideoOverlay();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void vlcTimeChanged(int64_t newTime);
	void vlcPaused();
	void vlcStarted();
	void vlcStopped();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> bottomState;
    ScopedPointer<Slider> slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroVideoOverlay)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
