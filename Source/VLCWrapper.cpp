#include "VLCWrapper.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define LIBVLC_USE_PTHREAD_CANCEL
#ifdef _MSC_VER
#define ssize_t int
#else
#define MODULE_STRING "wrapper"
#endif
#include <assert.h>
#include <vlc/media_player_internal.h>
static inline void lock_input(libvlc_media_player_t *mp)
{
	vlc_mutex_lock(&mp->input.lock);
}

static inline void unlock_input(libvlc_media_player_t *mp)
{
	vlc_mutex_unlock(&mp->input.lock);
}

/*
* Retrieve the input thread. Be sure to release the object
* once you are done with it. (libvlc Internal)
*/
input_thread_t *libvlc_get_input_thread(libvlc_media_player_t *p_mi)
{
	input_thread_t *p_input_thread;

	assert(p_mi);

	lock_input(p_mi);
	p_input_thread = p_mi->input.p_thread;
	if (p_input_thread)
		vlc_object_hold(p_input_thread);
	else
		libvlc_printerr("No active input");
	unlock_input(p_mi);

	return p_input_thread;
}

/*
* Remember to release the returned vout_thread_t.
*/
static vout_thread_t **GetVouts(libvlc_media_player_t *p_mi, size_t *n)
{
	input_thread_t *p_input = libvlc_get_input_thread(p_mi);
	if (!p_input)
	{
		*n = 0;
		return NULL;
	}

	vout_thread_t **pp_vouts;
	if (input_Control(p_input, INPUT_GET_VOUTS, &pp_vouts, n))
	{
		*n = 0;
		pp_vouts = NULL;
	}
	vlc_object_release (p_input);
	return pp_vouts;
}

static vout_thread_t *GetVout (libvlc_media_player_t *mp, size_t num)
{
	vout_thread_t *p_vout = NULL;
	size_t n;
	vout_thread_t **pp_vouts = GetVouts (mp, &n);
	if (pp_vouts == NULL)
		goto err;

	if (num < n)
		p_vout = pp_vouts[num];

	for (size_t i = 0; i < n; i++)
		if (i != num)
			vlc_object_release (pp_vouts[i]);
	libvlc_free (pp_vouts);

	if (p_vout == NULL)
		err:
	libvlc_printerr ("Video output not active");
	return p_vout;
}

static void HandleVLCEvents(const libvlc_event_t* pEvent, void* pUserData)
{
	VLCEventCallback* cb = reinterpret_cast<VLCEventCallback*>(pUserData);
	if (!cb)
	{
		return;
	}

	switch (pEvent->type)
	{
	case libvlc_MediaPlayerTimeChanged:
		cb->vlcTimeChanged(pEvent->u.media_player_time_changed.new_time);
		break;
	case libvlc_MediaPlayerPlaying:
		cb->vlcStarted();
		break;
	case libvlc_MediaPlayerPaused:
		cb->vlcPaused();
		break;
	case libvlc_MediaPlayerStopped:
	case libvlc_MediaPlayerEndReached:
		cb->vlcStopped();
		break;
	}
}

class VisorVLC : public Component
{
	public:
		VisorVLC()
		{
			setAlwaysOnTop(false);
		}
		void paint(Graphics &g) {}
};

VLCWrapper::VLCWrapper ()
	: Component ("VideoVLC"), vlc_mplayer(nullptr), eventCallback(nullptr)
{
	setSize (400, 200);
	vlc_visor = new VisorVLC();
	vlc_visor->setOpaque(true);
	vlc_visor->addToDesktop(ComponentPeer::windowIsTemporary);
	isLoadMedia = false;

	const char * const vlc_args[] =
	{
		"--osd", "--aout", "none", "--text-renderer", "any"
	};

	vlc_instan = libvlc_new (5, vlc_args);
	vlc_mplayer = libvlc_media_player_new(vlc_instan);
	vlc_event_manager = libvlc_media_player_event_manager(vlc_mplayer);
}

VLCWrapper::~VLCWrapper()
{
	attachCallback(0);
	/* Stop playing */
	if (vlc_mplayer)
	{
		libvlc_media_player_stop (vlc_mplayer);
		/* Free the media_player */
		libvlc_media_player_release (vlc_mplayer);
		libvlc_release (vlc_instan);
	}
	
	delete vlc_visor;
}

void VLCWrapper::attachCallback(VLCEventCallback *cb)
{
	if (eventCallback)
	{
		libvlc_event_detach (vlc_event_manager, libvlc_MediaPlayerTimeChanged, HandleVLCEvents, eventCallback);
		libvlc_event_detach (vlc_event_manager, libvlc_MediaPlayerPlaying, HandleVLCEvents, eventCallback);
		libvlc_event_detach (vlc_event_manager, libvlc_MediaPlayerPausableChanged, HandleVLCEvents, eventCallback);
		libvlc_event_detach (vlc_event_manager, libvlc_MediaPlayerPaused, HandleVLCEvents, eventCallback);
		libvlc_event_detach (vlc_event_manager, libvlc_MediaPlayerStopped, HandleVLCEvents, eventCallback);
	}
	eventCallback = cb;
	if (cb)
	{
		libvlc_event_attach (vlc_event_manager, libvlc_MediaPlayerTimeChanged, HandleVLCEvents, cb);
		libvlc_event_attach (vlc_event_manager, libvlc_MediaPlayerPlaying, HandleVLCEvents, cb);
		libvlc_event_attach (vlc_event_manager, libvlc_MediaPlayerPausableChanged, HandleVLCEvents, cb);
		libvlc_event_attach (vlc_event_manager, libvlc_MediaPlayerPaused, HandleVLCEvents, cb);
		libvlc_event_attach (vlc_event_manager, libvlc_MediaPlayerStopped, HandleVLCEvents, cb);
	}
}

void VLCWrapper::paint (Graphics& g)
{
	g.fillAll (Colours::black);
}

void VLCWrapper::resized()
{
	Logger::outputDebugString("VLCWrapper::resized bounds==" + getBounds().toString());
}

void VLCWrapper::timerCallback()
{
	vlc_visor->setBounds(getScreenX(), getScreenY(), getWidth(), getHeight());
	if (getState() == STATE_ENDED)
	{
		stopTimer();
		vlc_visor->setVisible(false);
	}
	vlc_visor->toFront(false);
}

void VLCWrapper::play()
{
	if (isLoadMedia == false)
	{
		return;
	}
	libvlc_media_player_play (vlc_mplayer);
	startTimer(1);
	vlc_visor->setVisible(true);
}

void VLCWrapper::stop()
{
	if (isLoadMedia == false)
	{
		return;
	}
	libvlc_media_player_stop(vlc_mplayer);
	vlc_visor->setVisible(false);
	stopTimer();
}

void VLCWrapper::pause()
{
	if (isLoadMedia == false)
	{
		return;
	}
	libvlc_media_player_pause(vlc_mplayer);
}

void VLCWrapper::setRate(float p_rate)
{
	if (isLoadMedia == false)
	{
		return;
	}
	libvlc_media_player_set_rate(vlc_mplayer, p_rate);
}

float VLCWrapper::getRate()
{
	if (isLoadMedia == false)
	{
		return -1;
	}
	float vr = libvlc_media_player_get_rate(vlc_mplayer);
	return vr;
}

void VLCWrapper::setPosition(int p_posi)
{
	if (isLoadMedia == false)
	{
		return;
	}
	libvlc_media_t *curMedia = libvlc_media_player_get_media (vlc_mplayer);
	
	if (curMedia == NULL)
		return;

	float pos = (float)(p_posi) / (float)10000;
	libvlc_media_player_set_position (vlc_mplayer, pos);
}

int VLCWrapper::getPosition()
{
	if (isLoadMedia == false)
	{
		return -1;
	}
	libvlc_media_t *curMedia = libvlc_media_player_get_media (vlc_mplayer);

	if (curMedia == NULL)
		return -1;

	float pos = libvlc_media_player_get_position (vlc_mplayer);
	int vr = (int)(pos*(float)(10000));
	return vr;
}

void VLCWrapper::loadMedia(String pmedia)
{
	
	vlc_media = libvlc_media_new_location (vlc_instan, pmedia.toStdString().c_str());

	if (vlc_mplayer != 0)
	{
		stop();
	}

	libvlc_media_player_set_media (vlc_mplayer, vlc_media);
	libvlc_media_release (vlc_media);

	if (SystemStats::getOperatingSystemName() == "Linux")
	{
		libvlc_media_player_set_xwindow(vlc_mplayer, (uint32_t)vlc_visor->getWindowHandle());
	}
	else if (SystemStats::getOperatingSystemName() == "MacOSX") {
		libvlc_media_player_set_agl(vlc_mplayer, (uint32_t)vlc_visor->getWindowHandle());
	}
	else {
		libvlc_media_player_set_hwnd(vlc_mplayer, vlc_visor->getWindowHandle());
	}
	
	isLoadMedia = true;
}

void VLCWrapper::setVolume(int p_vol)
{
	if (isLoadMedia == false)
	{
		return;
	}
	if (p_vol>100)
	{
		p_vol = 100;
	}
	if (p_vol<0)
	{
		p_vol = 0;
	}

	libvlc_audio_set_volume(vlc_mplayer, p_vol);
}

int VLCWrapper::getVolume()
{
	if (isLoadMedia == false)
	{
		return -1;
	}
	int vr = libvlc_audio_get_volume(vlc_mplayer);

	return vr;
}

int VLCWrapper::getState()
{
	if (isLoadMedia == false)
	{
		return 0;
	}
	return libvlc_media_get_state(vlc_media);
}

float VLCWrapper::getDuration()
{
	if (isLoadMedia == false)
	{
		return 0;
	}
	return libvlc_media_player_get_length(vlc_mplayer);
}

void VLCWrapper::setOsd(const String &text)
{
	vout_thread_t *vout_t = GetVout(vlc_mplayer, 0);
	if (vout_t)
	{
		vout_OSDText(vout_t, SPU_DEFAULT_CHANNEL, SUBPICTURE_ALIGN_LEFT, 1000, "OSDME");
		vlc_object_release(vout_t);
	}
}