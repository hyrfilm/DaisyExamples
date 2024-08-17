#ifndef REVERB_H
#define REVERB_H

#include "daisy_seed.h"
#include <cstddef>  // for size_t
#include "arm_math.h"  // for float32_t

void init();
void process(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t block);

#endif
