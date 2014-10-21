#include "VRMouse.h"
#include "core/utils/toString.h"
#include "core/setup/VRSetupManager.h"
#include "core/objects/VRCamera.h"
#include "VRSignal.h"
#include <GL/glut.h>

OSG_BEGIN_NAMESPACE;
using namespace std;

VRMouse::VRMouse() : VRDevice("mouse") {
    cam = 0;
    view = 0;
    clearSignals();
}

void VRMouse::clearSignals() {
    VRDevice::clearSignals();
    addSlider(5);
    addSlider(6);

    addSignal( 0, 0)->add( getDrop() );
    addSignal( 0, 1)->add( addDrag( getBeacon(), 0) );

    /*VRSignal* sig = addSignal( -1, 0);
    sig->add( addIntersect( getBeacon(), 0) );
    addUpdateSignal(sig);
    showHitPoint(true);*/
}

void VRMouse::multFull(Matrix _matrix, const Pnt3f &pntIn, Pnt3f  &pntOut) {
    float w = _matrix[0][3] * pntIn[0] +
                  _matrix[1][3] * pntIn[1] +
                  _matrix[2][3] * pntIn[2] +
                  _matrix[3][3];

    /*if (w <1) {
        fstream file("dump.txt", fstream::out | fstream::app);
        file << w << endl;
        file.close();
    }*/

    if(w == TypeTraits<float>::getZeroElement())
    {
        cout << "\nWARNING: w = " << _matrix[0][3] * pntIn[0] << " " << _matrix[1][3] * pntIn[1] << " " << _matrix[2][3] * pntIn[2];


        pntOut.setValues(
            (_matrix[0][0] * pntIn[0] +
             _matrix[1][0] * pntIn[1] +
             _matrix[2][0] * pntIn[2] +
             _matrix[3][0]             ),
            (_matrix[0][1] * pntIn[0] +
             _matrix[1][1] * pntIn[1] +
             _matrix[2][1] * pntIn[2] +
             _matrix[3][1]             ),
            (_matrix[0][2] * pntIn[0] +
             _matrix[1][2] * pntIn[1] +
             _matrix[2][2] * pntIn[2] +
             _matrix[3][2]             ) );
    }
    else
    {
        w = TypeTraits<float>::getOneElement() / w;

        pntOut.setValues(
            (_matrix[0][0] * pntIn[0] +
             _matrix[1][0] * pntIn[1] +
             _matrix[2][0] * pntIn[2] +
             _matrix[3][0]             ) * w,
            (_matrix[0][1] * pntIn[0] +
             _matrix[1][1] * pntIn[1] +
             _matrix[2][1] * pntIn[2] +
             _matrix[3][1]             ) * w,
            (_matrix[0][2] * pntIn[0] +
             _matrix[1][2] * pntIn[1] +
             _matrix[2][2] * pntIn[2] +
             _matrix[3][2]             ) * w );
    }
}

bool VRMouse::calcViewRay(PerspectiveCameraRecPtr pcam, Line &line, float x, float y, int W, int H){
    if(W <= 0 || H <= 0) return false;

    Matrix proj, projtrans, view;

    pcam->getProjection(proj, W, H);
    pcam->getProjectionTranslation(projtrans, W, H);

    Matrix wctocc;
    wctocc.mult(proj);
    wctocc.mult(projtrans);

    Matrix cctowc;
    cctowc.invertFrom(wctocc);


    Pnt3f from, at;
    multFull(cctowc, Pnt3f(x, y, -1), from);
    multFull(cctowc, Pnt3f(x, y, 0.1), at );

    Vec3f dir = at - from;
    line.setValue(from, dir);

    return true;
}

//3d object to emulate a hand in VRSpace
void VRMouse::updatePosition(int x, int y) {
    if (cam == 0) return;
    if (view == 0) return;

    float rx, ry;
    int w, h;
    w = view->getViewport()->calcPixelWidth();
    h = view->getViewport()->calcPixelHeight();
    view->getViewport()->calcNormalizedCoordinates(rx, ry, x, y);

    calcViewRay(cam->getCam(), ray, rx,ry,w,h);
    getBeacon()->setDir(ray.getDirection());
}

void VRMouse::mouse(int button, int state, int x, int y) {
    float _x, _y;
    if (view == 0) return;

    ViewportRecPtr v = view->getViewport();
    v->calcNormalizedCoordinates(_x, _y, x, y);
    change_slider(5,_x);
    change_slider(6,_y);

    updatePosition(x,y);
    if (state) change_button(button,false);
    else change_button(button,true);
}

void VRMouse::motion(int x, int y) {
    if (view == 0) return;

    float _x, _y;
    ViewportRecPtr v = view->getViewport();
    v->calcNormalizedCoordinates(_x, _y, x, y);
    change_slider(5,_x);
    change_slider(6,_y);

    updatePosition(x,y);
}

void VRMouse::setCamera(VRCamera* _cam) { cam = _cam; }

void VRMouse::setViewport(VRView* _view) { view = _view; }

Line VRMouse::getRay() { return ray; }

void VRMouse::save(xmlpp::Element* e) {
    VRDevice::save(e);
}

void VRMouse::load(xmlpp::Element* e) {
    VRDevice::load(e);
}

OSG_END_NAMESPACE;