#ifndef VRLOD_H_INCLUDED
#define VRLOD_H_INCLUDED

#include "core/objects/object/VRObject.h"
#include <OpenSG/OSGDistanceLOD.h>

OSG_BEGIN_NAMESPACE;
using namespace std;

class VRLod : public VRObject {
    private:
        DistanceLODRecPtr lod;
        bool decimate = false;
        Vec3f center;
        uint decimateNumber = 0;
        map<uint, float> distances;
        map<uint, VRObject*> decimated;
        map<uint, float> decimation;

        void update();
        void decimateGeometries(VRObject* o, float f);

    protected:
        VRObject* copy(vector<VRObject*> childs);

        void saveContent(xmlpp::Element* e);
        void loadContent(xmlpp::Element* e);

    public:
        /** initialise **/
        VRLod(string name = "0");
        ~VRLod();

        void setCenter(Vec3f c);
        Vec3f getCenter();
        void setDistance(uint i, float dist);
        void addDistance(float dist);
        vector<float> getDistances();

        void addEmpty();

        void setDecimate(bool b, int N);
        bool getDecimate();
        int getDecimateNumber();
};

OSG_END_NAMESPACE;

#endif // VRLOD_H_INCLUDED
