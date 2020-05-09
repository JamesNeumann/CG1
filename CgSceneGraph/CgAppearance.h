#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include<glm/glm.hpp>

class CgAppearance
{
public:
    CgAppearance();
    glm::vec3 getObjectColor();
    glm::vec3 getDifuseMaterial();
    void setObjectColor(glm::vec3 color);
    void getDifuseMaterial(glm::vec3 difuseMaterial);
private:
    glm::vec3 object_color;
    glm::vec3 difuse_material;
};

#endif // CGAPPEARANCE_H
