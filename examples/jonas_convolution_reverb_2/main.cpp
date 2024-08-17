// main.cpp
#include "daisy_seed.h"
#include "reverb.h"

using namespace daisy;

#define BLOCK_SIZE 64

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t block)
{
    process(in, out, block);
}

int main(void)
{
    DaisySeed hw;

    // prepare reverb
    init();

    /** Initialize our hardware */
    hw.Configure();
    hw.Init();
    hw.SetAudioBlockSize(BLOCK_SIZE);

    /** Start the Audio engine, and call the "AudioCallback" function to fill new data */
    hw.StartAudio(AudioCallback);

    /** Infinite Loop */
    while(1) {}
}
