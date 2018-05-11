/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ZeroVideoOverlay.h"

//==============================================================================
MainContentComponent::MainContentComponent(ZeroVideoOverlay *_overlay) : overlay(_overlay)
{
	addAndMakeVisible(zeroMain = new ZeroMain(overlay));
	setSize(640, 600);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{

}

void MainContentComponent::resized()
{
}