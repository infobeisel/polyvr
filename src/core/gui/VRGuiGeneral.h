#ifndef VRGUIGENERAL_H_INCLUDED
#define VRGUIGENERAL_H_INCLUDED

#include <OpenSG/OSGConfig.h>
#include "core/scene/VRSceneManager.h"
#include "VRGuiSignals.h"
#include <gtkmm/menu.h>

OSG_BEGIN_NAMESPACE;
using namespace std;

class VRGuiGeneral {
    private:
        bool updating;

        // background signals
        bool setColor(GdkEventButton* b);
        void setPath();
        void setMode();

        // rendering signals
        void toggleFrustumCulling();
        void toggleOcclusionCulling();
        void toggleTwoSided();

        // other
        void dumpOSG();

    public:
        VRGuiGeneral();


        void updateScene();
};

OSG_END_NAMESPACE

#endif // VRGUIGENERAL_H_INCLUDED
