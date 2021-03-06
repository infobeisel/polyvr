#ifndef VRFRAMEWORK_H_INCLUDED
#define VRFRAMEWORK_H_INCLUDED

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGNode.h>

OSG_BEGIN_NAMESPACE;
using namespace std;

void setMultisampling(bool on);
void initPolyVR(int argc, char **argv);

void startPolyVR();
void exitPolyVR();

void startPolyVR_testScene(NodeRecPtr n);

OSG_END_NAMESPACE;

#endif // VRFRAMEWORK_H_INCLUDED
