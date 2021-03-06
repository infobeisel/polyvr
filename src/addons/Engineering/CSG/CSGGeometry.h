#ifndef CSGGEOMETRY_H_
#define CSGGEOMETRY_H_

#include <string>
#include "OpenSG/OSGConfig.h"
#include "core/objects/geometry/VRGeometry.h"

namespace CGAL { class Polyhedron; }

OSG_BEGIN_NAMESPACE;

class Octree;

class CSGGeometry : public VRGeometry {
    private:
        CGAL::Polyhedron* polyhedron = 0;
        string operation = "unite";
        bool editMode = true;
        Matrix oldWorldTrans;
        float THRESHOLD = 1e-4;
        Octree* oct = 0;

    protected:
        void applyTransform(CGAL::Polyhedron* p, Matrix m);
        void setCSGGeometry(CGAL::Polyhedron* p);
        CGAL::Polyhedron* getCSGGeometry();
        size_t isKnownPoint(OSG::Pnt3f newPoint);
        GeometryTransitPtr toOsgGeometry(CGAL::Polyhedron* p);
        CGAL::Polyhedron* toPolyhedron(GeometryRecPtr geometry, Matrix worldTransform, bool& success);

        CGAL::Polyhedron* subtract(CGAL::Polyhedron* minuend, CGAL::Polyhedron* subtrahend);
        CGAL::Polyhedron* unite(CGAL::Polyhedron* first, CGAL::Polyhedron* second);
        CGAL::Polyhedron* intersect(CGAL::Polyhedron* first, CGAL::Polyhedron* second);

        void enableEditMode();
        bool disableEditMode();

        void saveContent(xmlpp::Element* e);
        void loadContent(xmlpp::Element* e);

    public:
        CSGGeometry(std::string name);
        virtual ~CSGGeometry();

        bool setEditMode(bool b);
        bool getEditMode();

        void setOperation(string op);
        string getOperation();
        static vector<string> getOperations();
};

OSG_END_NAMESPACE;

#endif /* CSGGEOMETRY_H_ */
