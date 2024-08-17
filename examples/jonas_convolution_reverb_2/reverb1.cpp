#include "daisy_seed.h"
#include "dsp.h"
#include "IR_shorter.h"

using namespace daisy;


#define FORWARD_FFT 1
#define INVERSE_FFT 0

int32_t IRindex = 0;
const int32_t BLOCK_SIZE = 64;
float32_t *INsegment = NULL;
float32_t *OUTsegment = NULL;
float32_t *IRsegment = NULL;
float32_t *INxIR = NULL;

arm_rfft_fast_instance_f32 rfft_instance; // FFT instance
// Other global variables related to DSP processing

// 1. Allocate memory for processing
void allocateMemory(int32_t blockSize) {
    INsegment = (float32_t*) malloc(4 * blockSize);
    OUTsegment = (float32_t*) malloc(4 * blockSize);
    IRsegment = (float32_t*) malloc(4 * blockSize);
    INxIR = (float32_t*) malloc(4 * blockSize * 2);
}

const int32_t IR_LENGTH = 480000;  // Length of the IR in samples
void readIR() {
    for(int32_t i = 0; i < BLOCK_SIZE; i++) {
        // Calculate the current position in the IR, applying the modulus to loop
        int32_t irPos = (IRindex + i) % IR_LENGTH;

        // Get the 16-bit sample and convert it to a float
        int16_t sample = IR_shorter[irPos];
        IRsegment[i] = static_cast<float32_t>(sample) / 32768.0f;
    }
    // Update the IRindex for the next block
    IRindex = (IRindex + BLOCK_SIZE) % IR_LENGTH;
}

// Perform the convolution
void doConvolution() {
    // Transform time -> frequency domain
    arm_rfft_fast_f32(&rfft_instance, INsegment, INsegment, FORWARD_FFT);
    arm_rfft_fast_f32(&rfft_instance, IRsegment, IRsegment, FORWARD_FFT);

    // Complex multiplication in the frequency domain
    arm_cmplx_mult_cmplx_f32(INsegment, IRsegment, INxIR, BLOCK_SIZE);

    // Transform frequency -> time domain
    arm_rfft_fast_f32(&rfft_instance, INxIR, OUTsegment, INVERSE_FFT);
}

// 2. Process a new block of audio
void process(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t block) {
    // Update the input and output segments
    for(size_t i = 0; i < block; i++) {
        INsegment[i] = in[0][i];
    }

    // Process the IR (could be done before processing starts)
    readIR();

    // Perform convolution
    doConvolution();

    // Write the output
    for(size_t i = 0; i < block; i++) {
        out[0][i] = OUTsegment[i];
        out[1][i] = OUTsegment[i];
    }
}

// Call this once in the main initialization
void init() {
    allocateMemory(BLOCK_SIZE);

    // Initialize the FFT instance
    arm_rfft_fast_init_f32(&rfft_instance, BLOCK_SIZE);
}
