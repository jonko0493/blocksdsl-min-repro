#include "sound.hpp"

int sine;		// sine position
int lfo;		// LFO position

mm_word on_stream_request( mm_word length, mm_addr dest, mm_stream_formats format )
{
//----------------------------------------------------------------------------------
    
    s16 *target = (s16 *)dest;
    
    //------------------------------------------------------------
    // synthensize a sine wave with an LFO applied to the pitch
    // the stereo data is interleaved
    //------------------------------------------------------------
    int len = length;
    for( ; len; len-- )
    {
        int sample = sinLerp(sine);
        
        // output sample for left
        *target++ = sample;
        
        // output inverted sample for right
        *target++ = -sample;
        
        sine += 500 + (sinLerp(lfo) >> 4);
        lfo = (lfo + 3);
    }
    
    return length;
}

SoundPlayer::SoundPlayer()
{
    mm_ds_system sys;
	sys.mod_count 			= 0;
	sys.samp_count			= 0;
	sys.mem_bank			= 0;
	mmInit(&sys);
}

void SoundPlayer::playSound()
{
    mm_stream mystream;
	mystream.sampling_rate	= 25000;					// sampling rate = 25khz
	mystream.buffer_length	= 1200;						// buffer length = 1200 samples
	mystream.callback		= on_stream_request;		// set callback function
	mystream.format			= MM_STREAM_16BIT_STEREO;	// format = stereo 16-bit
	mystream.timer			= MM_TIMER0;				// use hardware timer 0
	mystream.manual			= true;						// use manual filling
	mmStreamOpen(&mystream);
}

void SoundPlayer::stopSound()
{
    mmStreamClose();
}