#include "CgScenegraphEntity.h"

CgScenegraphEntity::CgScenegraphEntity(glm::mat4 current_transformation)
{
    m_current_transformation = current_transformation;
}

std::vector<CgBaseRenderableObject*> CgScenegraphEntity::getListOfObjects() {
    return list_of_objects;
}
glm::mat4 CgScenegraphEntity::getCurrentTransformation() {
    return m_current_transformation;
}
CgAppearance CgScenegraphEntity::getAppearance() {
    return m_appearance;
}
CgScenegraphEntity* CgScenegraphEntity::getParent() {
    return m_parent;
}
std::vector<CgScenegraphEntity*> CgScenegraphEntity::getChildren() {
    return m_children;
}

void CgScenegraphEntity::addObject(CgBaseRenderableObject* obj) {
    list_of_objects.push_back(obj);
}
void CgScenegraphEntity::addChildren(CgScenegraphEntity* child){
    m_children.push_back(child);
    child->setParent(this);
}
void CgScenegraphEntity::setParent(CgScenegraphEntity* parent) {
    m_parent = parent;
}
