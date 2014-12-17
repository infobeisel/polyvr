#ifndef VRRECORDER_H_INCLUDED
#define VRRECORDER_H_INCLUDED

#include <OpenSG/OSGConfig.h>
#include <string>
#include <vector>

OSG_BEGIN_NAMESPACE;
using namespace std;

class VRView;
class VRFrame;

class VRRecorder {
    private:
        VRView* view = 0;
        vector<VRFrame*> captures;

    public:
        VRRecorder();

        void setView(int i);
        void capture();
        void compile(string path);
        void clear();
        int getRecordingSize();
        float getRecordingLength();
};

OSG_END_NAMESPACE;

#endif // VRRECORDER_H_INCLUDED
