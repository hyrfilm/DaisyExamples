# Description: 
Example showing basic usage of RGB LED by mapping R/G values of LED 1 to knob.

# Controls:
| Control | Description | Comment |
| --- | --- | --- |
| Knob 1 | Led 1 Brightness | Sets the R brightness value for LED 1. |
| Knob 2 | Led 2 Brightness | Sets the G brightness value for LED 1. |

# Diagram
<img src="https://raw.githubusercontent.com/electro-smith/DaisyExamples/master/pod/SimpleLed/resources/SimpleLed.png" alt="Button_schem.png" style="width: 100%;"/>

# Code Snippet  
```cpp  
r = p_knob1.Process();
g = p_knob2.Process();

hw.led1.Set(r, g, b);    
hw.UpdateLeds();
```