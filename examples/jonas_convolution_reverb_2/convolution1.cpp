/** Generation of a simple Audio signal */
#include "daisy_seed.h"
#include "arm_math.h"
#include <cmath>
#include "IR_shorter.h"

/** This prevents us from having to type "daisy::" in front of a lot of things. */
using namespace daisy;

#define BLOCK_SIZE 64
#define FORWARD_FFT 1
#define INVERSE_FFT 0

float32_t *INsegment;
float32_t *OUTsegment;
float32_t *IRsegment;
float32_t *INxIR;

arm_cfft_instance_f32 cfft_instance; // fft_instance
//arm_rfft_fast_init_1024_f32(&FFT_WINDOW); // real fft data

//outLen = BLOCK_SIZE + BLOCK_SIZE - 1;

long IRindex = 0;

// float *in = <pointer to your input signal>;
// float *ir = <pointer to your impulse response>;
// float *out = <pointer to audio out>
void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t block)
{


    for(long i=0;i<(BLOCK_SIZE*2);i+=2) {
        float32_t sampleLo = (IR[(i + IRindex)%BLOCK_SIZE]);
        float32_t sampleHi = (IR[(i + 1 + IRindex)%BLOCK_SIZE]);

	    sampleHi*=16;
	    IRsegment = sampleLo + sampleHi;
    }
    IRindex+=BLOCK_SIZE;

    /* Copy the input values to the fft input buffers */
    //arm_copy_f32(IR, IRsegment, MAX_BLOCKSIZE/2); //TODO: KOM IHÅG ATTT DENNA MÅSTE KONVERTERAS FRÅN 16/24bitar till floats vid inladdning
    arm_copy_f32(in, INsegment, MAX_BLOCKSIZE/2); // OBS!!!!!!!!!

    // transform time -> frequency domain
    arm_rfft_fast_f32(&cfft_instance, INsegment, FORWARD_FFT, 1);    // Forward FFT on input
    arm_rfft_fast_f32(&cfft_instance, IRsegment, FORWARD_FFT, 1);    // Forward FFT on impulse response

    /* Complex Multiplication of the two input buffers in frequency domain */
    arm_cmplx_mult_cmplx_f32(INsegment, IRsegment, INxIR, MAX_BLOCKSIZE);

    // transform time <- frequency domain
    arm_rfft_fast_f32(INxIR, OUTsegment, INVERSE_FFT, 1);

    for(size_t i=0;i<block;i++) {
      out[0][i] = OUTsegment[i];
      out[1][i] = OUTsegment[i];
    }
}


int main(void)
{
    INsegment = (float32_t*) malloc(4*BLOCK_SIZE);
    OUTsegment = (float32_t*) malloc(4*BLOCK_SIZE);
    IRsegment = (float32_t*) malloc(4*BLOCK_SIZE);
    INxIR = (float32_t*) malloc(4*BLOCK_SIZE*2);

    DaisySeed hw;

    /** Global Hardware access */

    /** Initialize our hardware */
    hw.Configure();
    hw.Init();
    hw.SetAudioBlockSize(BLOCK_SIZE);

    /** Start the Audio engine, and call the "AudioCallback" function to fill new data */
    hw.StartAudio(AudioCallback);


    /** Infinite Loop */
    while(1) {}
}

