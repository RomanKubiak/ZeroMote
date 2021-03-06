/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "ZeroVideoOverlay.h"
#include "MainComponent.h"



//==============================================================================
class vlctestApplication  : public JUCEApplication
{
public:
    //==============================================================================
    vlctestApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
		File settingsFile = File::getSpecialLocation(File::userApplicationDataDirectory).getChildFile(ProjectInfo::projectName).getChildFile("settings.json");
		if (!settingsFile.existsAsFile())
		{
			if (settingsFile.create().wasOk())
			{
				if (!settingsFile.replaceWithText(String(BinaryData::default_json, BinaryData::default_jsonSize)))
				{
					Logger::writeToLog("ERROR: can't write default settings to: " + settingsFile.getFullPathName());
				}
			}
		}

		var settings = JSON::parse(settingsFile);
        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);

			overlay = new ZeroVideoOverlay();
			overlay->addToDesktop(ComponentPeer::windowIsTemporary);
			overlay->setAlwaysOnTop(true);
			overlay->toFront(true);
			overlay->setVisible(true);

            setContentOwned (new MainContentComponent(overlay), true);
			
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
		void moved() override
		{
			Logger::outputDebugString("MainWindow::moved bounds==" + getBounds().toString());
			overlay->setTopLeftPosition(getBounds().getTopLeft());
			overlay->setSize(640, 480);
		}

		void resized() override
		{
			Logger::outputDebugString("MainWindow::resized bounds==" + getBounds().toString());
		}
        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
			ScopedPointer<ZeroVideoOverlay> overlay;
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (vlctestApplication)
