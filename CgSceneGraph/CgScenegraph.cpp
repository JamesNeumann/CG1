#include "CgScenegraph.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

CgScenegraph::CgScenegraph(CgScenegraphEntity* root)
{
    m_root_node = root;
    m_modelview_matrix_stack.push(m_root_node->getCurrentTransformation());
    srand(time(NULL));
}

void CgScenegraph::renderSceneGraph(CgBaseRenderer *renderer, glm::mat4 sceneMatrix) {
    render(renderer, m_root_node, sceneMatrix);
}


void CgScenegraph::render(CgBaseRenderer* renderer, CgScenegraphEntity* entity, glm::mat4 sceneMatrix) {
    renderer->setUniformValue("modelviewMatrix",sceneMatrix);

    for(auto obj : entity->getListOfObjects()) {
        renderer->setUniformValue("mycolor", glm::vec4(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), 1));
        renderer->render(obj);

    }

    pushMatrix();

    for (auto child : entity->getChildren()) {
        render(renderer, child, sceneMatrix * child->getCurrentTransformation());
    }
    popMatrix();

}

void CgScenegraph::setRootEntity(CgScenegraphEntity *root) {
    m_root_node = root;
}

CgScenegraphEntity* CgScenegraph::getRootEntity() {
    return m_root_node;
}


CgScenegraph::~CgScenegraph() {
    delete m_root_node;
}
