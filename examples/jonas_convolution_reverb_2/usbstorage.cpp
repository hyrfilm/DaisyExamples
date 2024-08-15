#include "daisy_seed.h"
#include <cmath>

using namespace daisy;

DaisySeed hw;

bool update = false;

float r = 0, g = 0, b = 0;

for(int i=0;i<1000;i++)
{
    hw.led1.Set(1, 1, 1);
    hw.UpdateLeds();
}


void UsbCallback(uint8_t* buf, uint32_t* len)
{
    memcpy(sumbuff, buf, *len);
    rx_size = *len;
    update  = true;
}

int main(void)
{
    hw.Configure();
    hw.Init();
    update  = false;
    rx_size = 0;
    hw.usb_handle.Init(UsbHandle::FS_INTERNAL);
    // Todo: replace delay with while(!usb_handle.IsInitialized()) {} or similar
    System::Delay(500);
    hw.usb_handle.SetReceiveCallback(UsbCallback, UsbHandle::FS_INTERNAL);
    for(;;)
    {
        if(update && rx_size > 0)
        {
            //hw.usb_handle.TransmitInternal(sumbuff, rx_size);
            update = false;
        }

        for(int i=0;i<1000;i++)
        {
            hw.led1.Set(1, 0, 0);
            hw.UpdateLeds();
        }
        System::Delay(2);
    }
}
