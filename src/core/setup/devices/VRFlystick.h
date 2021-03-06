#ifndef VRFLYSTICK_H_INCLUDED
#define VRFLYSTICK_H_INCLUDED

#include "VRDevice.h"

OSG_BEGIN_NAMESPACE;
using namespace std;

class VRFlystick : public VRDevice {
    public:
        VRFlystick();

        void clearSignals();

        void update(vector<int> buttons, vector<float> sliders);
};


OSG_END_NAMESPACE;

#endif // VRFLYSTICK_H_INCLUDED
