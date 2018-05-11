#ifndef __JUCER_HEADER_VIDEOVLC__
#define __JUCER_HEADER_VIDEOVLC__
//[Headers]
#include <vlc/vlc.h>
#include <vlc/libvlc.h>
#include "../JuceLibraryCode/JuceHeader.h"
class VLCEventCallback
{
	public:
		virtual ~VLCEventCallback() {}
		virtual void vlcTimeChanged(int64_t newTime) = 0;
		virtual void vlcPaused() = 0;
		virtual void vlcStarted() = 0;
		virtual void vlcStopped() = 0;
};

//[/Headers]
class VLCWrapper : public Component,
	private Timer
{
public:
	//==============================================================================
	VLCWrapper ();
	~VLCWrapper();

	//==============================================================================
	enum {
		STATE_IDLE_CLOSE,
		STATE_OPENING,
		STATE_BUFFERING,
		STATE_PLAYING,
		STATE_PAUSED,
		STATE_STOPPING,
		STATE_ENDED,
		STATE_ERROR,
	};
	//[UserMethods]     -- You can add your own custom methods in this section.
	void play();
	void stop();
	void pause();
	void setPosition(int p_posi);
	int getPosition();
	void setRate(float p_rate);
	float getRate();
	void setVolume(int p_vol);
	int getVolume();
	void loadMedia(String media);
	bool isLoadMedia;
	int getState();
	float getDuration();
	void setOsd(const String &text);
	void attachCallback(VLCEventCallback *cb);
	
	//[/UserMethods]

	void paint (Graphics& g);
	void resized();


	//==============================================================================
	juce_UseDebuggingNewOperator

private:
	//[UserVariables]   -- You can add your own custom variables in this section.
	void timerCallback();
	Component *vlc_visor;
	libvlc_instance_t *vlc_instan;
	libvlc_media_player_t *vlc_mplayer;
	libvlc_media_t *vlc_media;
	libvlc_event_manager_t*  vlc_event_manager;
	VLCEventCallback *eventCallback;
	//[/UserVariables]
	//==============================================================================

	//==============================================================================
	// (prevent copy constructor and operator= being generated..)
	VLCWrapper (const VLCWrapper&);
	const VLCWrapper& operator= (const VLCWrapper&);
};


#endif   // __JUCER_HEADER_VIDEOVLC__