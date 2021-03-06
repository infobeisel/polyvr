#ifndef VRRECORDER_H_INCLUDED
#define VRRECORDER_H_INCLUDED

#include <OpenSG/OSGVector.h>
#include <string>
#include <vector>

#include "core/utils/VRFunction.h"

OSG_BEGIN_NAMESPACE;
using namespace std;

class VRView;
class VRFrame;
class VRTransform;
class Image;

class VRRecorder {
    private:
        int viewID = 0;
        VRView* view = 0;
        vector<VRFrame*> captures;
        int maxFrames = -1;

        VRFunction<bool>* toggleCallback = 0;
        VRFunction<int>* updateCallback = 0;

        void on_record_toggle(bool b);

    public:
        VRRecorder();

        void setView(int i);
        void capture();
        void compile(string path);
        void clear();
        int getRecordingSize();
        float getRecordingLength();
        void setMaxFrames(int maxf);
        bool frameLimitReached();
        void setTransform(VRTransform* t, int f);
        Vec3f getFrom(int f);
        Vec3f getDir(int f);
        Vec3f getAt(int f);
        Vec3f getUp(int f);
        Image* get(int f);

        VRFunction<bool>* getToggleCallback();
};

OSG_END_NAMESPACE;

#endif // VRRECORDER_H_INCLUDED
