#ifndef CGSCENEGRAPHENTITY_H
#define CGSCENEGRAPHENTITY_H

#include "CgBase/CgBaseRenderableObject.h"
#include "CgAppearance.h"

#include <vector>
#include<glm/glm.hpp>

class CgScenegraphEntity
{
public:
    CgScenegraphEntity(glm::mat4 current_transformation);

    std::vector<CgBaseRenderableObject*> getListOfObjects();
    glm::mat4 getCurrentTransformation();
    CgAppearance getAppearance();
    CgScenegraphEntity* getParent();
    std::vector<CgScenegraphEntity*> getChildren();

    void addObject(CgBaseRenderableObject* obj);
    void addChildren(CgScenegraphEntity* child);
    void setParent(CgScenegraphEntity* parent);

private:
    std::vector<CgBaseRenderableObject*> list_of_objects;
    glm::mat4 m_current_transformation;

    CgAppearance m_appearance;

    CgScenegraphEntity* m_parent;
    std::vector<CgScenegraphEntity*> m_children;
};

#endif // CGSCENEGRAPHENTITY_H
