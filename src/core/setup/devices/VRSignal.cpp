#include "VRSignal.h"

#include <boost/bind.hpp>
#include <OpenSG/OSGNode.h>
#include "core/utils/VRFunction.h"

OSG_BEGIN_NAMESPACE;
using namespace std;


void VRSignal::add(VRDevCb* fkt) {
    callbacks.push_back(fkt);
}

void VRSignal::sub(VRDevCb* fkt) {
    if (callbacks.size() == 0) return;
    for(itr = callbacks.begin(); itr != callbacks.end(); ++itr) {
        if (*itr != fkt) continue;
        callbacks.erase(itr);
        return;
    }
}

VRSignal::VRSignal(VRDevice* _dev) : dev(_dev) {
    trig_fkt = new VRFunction<int>("Signal_trigger", boost::bind(&VRSignal::trigger, this));
    _doUpdate = false;
}

VRSignal::~VRSignal() {
    delete trig_fkt;
}

void VRSignal::trigger() {
    for(itr = callbacks.begin(); itr != callbacks.end(); ++itr) (*(*itr))(dev);
}

void VRSignal::setUpdate(bool b) { _doUpdate = b; }
bool VRSignal::doUpdate() { return _doUpdate; }

VRFunction<int>* VRSignal::getTriggerFkt() { return trig_fkt; }

OSG_END_NAMESPACE