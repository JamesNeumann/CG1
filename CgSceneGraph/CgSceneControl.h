#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgBase/CgBaseRenderableObject.h"
#include <glm/glm.hpp>
#include <vector>

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class CgCube;
class CgPolyline;
class CgSolidOfRevolution;
class CgTriangleMesh;


class CgScenegraph;


class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();



private:

    bool polyLineActive;
    bool scenegraphActive;

    CgBaseRenderer* m_renderer;


    CgScenegraph* m_scenegraph;


    CgExampleTriangle* m_triangle;
    CgCube* m_cube;

    CgTriangleMesh* m_triangle_mesh;

    CgTriangleMesh* m_base_object;

    std::vector<CgPolyline*> m_polyLines;
    CgPolyline* testPolyline;
    CgSolidOfRevolution* testRevolution;
    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
};

#endif // CGSCENECONTROL_H
