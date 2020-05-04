#ifndef CGSOLIDOFREVOLUTION_H
#define CGSOLIDOFREVOLUTION_H

#include "CgTriangleMesh.h"

class CgSolidOfRevolution : public CgTriangleMesh
{
public:
    CgSolidOfRevolution();

    void createRotationBody();

    void setRotationCurve(std::vector<glm::vec3> curve);
    void setRotationSteps(int rotationSteps);
private:

    std::vector<glm::vec3> m_rotationCurve;
    int m_rotationSteps;

};

#endif // CGSOLIDOFREVOLUTION_H
