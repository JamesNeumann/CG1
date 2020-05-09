#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include "CgScenegraphEntity.h"
#include "CgBase/CgBaseRenderer.h"
#include <stack>

class CgScenegraph
{
public:
    CgScenegraph(CgScenegraphEntity* root);
    void renderSceneGraph(CgBaseRenderer* renderer, glm::mat4 sceneMatrix);


    void setRootEntity(CgScenegraphEntity* root);
    CgScenegraphEntity* getRootEntity();
    ~CgScenegraph();

private:
    CgScenegraphEntity* m_root_node;
    std::stack <glm::mat4> m_modelview_matrix_stack;
    void render(CgBaseRenderer *renderer, CgScenegraphEntity* entity, glm::mat4 sceneMatrix);

    void pushMatrix() {m_modelview_matrix_stack.push(m_modelview_matrix_stack.top()); }
    void popMatrix() {m_modelview_matrix_stack.pop();}
    void applyTransform(glm::mat4 arg) {m_modelview_matrix_stack.top()*=arg;}
};

#endif // CGSCENEGRAPH_H
