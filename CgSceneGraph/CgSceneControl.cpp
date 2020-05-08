#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgColorChangEvent.h"
#include "CgEvents/CgSubdivideEvent.h"
#include "CgEvents/CgButtonClickedEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgEvents/CgRenderObjectEvent.h"
#include "CgExampleTriangle.h"
#include "CgCube.h"
#include "CgPolyline.h"
#include "CgSolidOfRevolution.h"
#include "CgTriangleMesh.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgUtils/ObjLoader.h"
#include <string>

CgSceneControl::CgSceneControl()
{
    m_triangle=NULL;
    m_cube = NULL;
    testPolyline = NULL;
    testRevolution = NULL;

    m_base_object = NULL;

    m_current_transformation=glm::mat4(1.);
    glm::mat4 scalemat = glm::mat4(1.);
    scalemat = glm::scale(scalemat,glm::vec3(0.3,0.3,0.3));

    m_current_transformation=m_current_transformation*scalemat;
    m_lookAt_matrix= glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_proj_matrix= glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation=glm::mat4(1.);

//    m_triangle= new CgExampleTriangle(21);
    m_cube = new CgCube();

//    testPolyline = new CgPolyline(std::vector<glm::vec3> {glm::vec3(0.5, 0.5, 0.5), glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.5, -0.5, -0.5), glm::vec3(-0.5, 0.5, 0.0), glm::vec3(0.5, 0.5, 0.5)}, 200);
//        testPolyline = new CgPolyline(
//                    std::vector<glm::vec3> {
//                        glm::vec3(-1.5, 1.0, 0.0),
//                        glm::vec3(0.0, 0.5, 0.0),
//                        glm::vec3(1.5, 1.0, 0.0),
//                        glm::vec3(0.0, -1.5, 0.0),
//                        glm::vec3(-1.5, 1.0, 0.0)
//                    },
//                    300
//                    );

     testPolyline = new CgPolyline(std::vector<glm::vec3> {
                                                   glm::vec3(0.0, 1, 0.0),
                                                   glm::vec3(1, 0, 0.0),
                                                   glm::vec3(0.333, -0.2 , 0.0),
                                                   glm::vec3(0.5, -0.4, 0.0),
                                                   glm::vec3(0.33, -0.5, 0.0),
                                                   glm::vec3(1.0, -0.9, 0.0),
                                                   glm::vec3(1.0, -1, 0.0)
                                               });
    testRevolution = new CgSolidOfRevolution();
//    testRevolution->setRotationCurve(std::vector<glm::vec3> {
//                                  glm::vec3(0.0, 1, 0.0),
//                                  glm::vec3(1, 0, 0.0),
//                                  glm::vec3(0.333, -0.2 , 0.0),
//                                  glm::vec3(0.5, -0.4, 0.0),
//                                  glm::vec3(0.33, -0.5, 0.0),
//                                  glm::vec3(1.0, -0.9, 0.0),
//                                  glm::vec3(1.0, -1, 0.0)
//                              });

    polyLineActive = false;

    m_base_object = m_cube;
//    m_triangle_mesh = new CgTriangleMesh();
//    m_triangle_mesh->calculateNormals();

}


CgSceneControl::~CgSceneControl()
{
//    if(m_triangle!=NULL)
//        delete m_triangle;
//    if(m_cube!=NULL)
//        delete m_cube;
//    if(!m_polyLines.empty())
//        for (auto poly : m_polyLines)
//            delete poly;
//    if(testPolyline!=NULL)
//        delete testPolyline;
//    if(testRevolution!=NULL)
//        delete testRevolution;
//    delete m_triangle_mesh;
    if (m_base_object != NULL)
        delete m_base_object;
    if (testPolyline != NULL)
        delete testPolyline;
}

void CgSceneControl::setRenderer(CgBaseRenderer* r)
{
    m_renderer=r;
    m_renderer->setSceneControl(this);

//    if(m_triangle!=NULL)
//        m_renderer->init(m_triangle);
//    if(m_cube!=NULL) {
//        m_renderer->init(m_cube);
//        for (CgPolyline* line : m_cube->getFaceNormalPolylines()) {
//            m_renderer->init(line);
//        }
//        for (CgPolyline* line : m_cube->getVertexNormalPolylines()) {
//            m_renderer->init(line);
//        }
//    }

//    if(!m_polyLines.empty())
//        for (CgPolyline* poly : m_polyLines)
//            m_renderer->init(poly);
////    if(testPolyline!=NULL)
////        m_renderer->init(testPolyline);
//    if(testRevolution!=NULL) {
//        for (CgPolyline* line : testRevolution->getFaceNormalPolylines()) {
//            m_renderer->init(line);
//        }
//        for (CgPolyline* line : testRevolution->getVertexNormalPolylines()) {
//            m_renderer->init(line);
//        }
//    }

//    m_renderer->init(m_triangle_mesh);
//    for (CgPolyline* line : m_triangle_mesh->getFaceNormalPolylines()) {
//        m_renderer->init(line);
//    }
//    for (CgPolyline* line : m_triangle_mesh->getVertexNormalPolylines()) {
//        m_renderer->init(line);
//    }        m_renderer->init(m_base_object);
    m_renderer->init(m_base_object);
    for (CgPolyline* line : m_base_object->getFaceNormalPolylines()) {
        m_renderer->init(line);
    }
    for (CgPolyline* line : m_base_object->getVertexNormalPolylines()) {
        m_renderer->init(line);
    }
    m_renderer->init(testPolyline);




}


void CgSceneControl::renderObjects()
{

    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....
    if (!m_polyLines.empty())
        m_renderer->setUniformValue("mycolor", glm::vec4(m_polyLines[0]->getColor(), 1.0));
    else if (testPolyline != NULL)
        m_renderer->setUniformValue("mycolor", glm::vec4(testPolyline->getColor(), 1.0));
    else
        m_renderer->setUniformValue("mycolor", glm::vec4(Cg::BASECOLOR));

    m_renderer->setUniformValue("matDiffuseColor",glm::vec4(0.35,0.31,0.09,1.0));
    m_renderer->setUniformValue("lightDiffuseColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matAmbientColor",glm::vec4(0.25,0.22,0.06,1.0));
    m_renderer->setUniformValue("lightAmbientColor",glm::vec4(1.0,1.0,1.0,1.0));


    m_renderer->setUniformValue("matSpecularColor",glm::vec4(0.8,0.72,0.21,1.0));
    m_renderer->setUniformValue("lightSpecularColor",glm::vec4(1.0,1.0,1.0,1.0));





    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation* m_current_transformation ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix",m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix",mv_matrix);
    m_renderer->setUniformValue("normalMatrix",normal_matrix);

//    if(m_triangle!=NULL)
//        m_renderer->render(m_triangle);
//    if(m_cube!=NULL) {
//        m_renderer->render(m_cube);
//        for (CgPolyline* line : m_cube->getFaceNormalPolylines()) {
//            m_renderer->render(line);
//        }
//        for (CgPolyline* line : m_cube->getVertexNormalPolylines()) {
//            m_renderer->render(line);
//        }
//    }

//    if(!m_polyLines.empty())
//        for (CgPolyline* poly : m_polyLines)
//            m_renderer->render(poly);
////    if(testPolyline!=NULL)
////        m_renderer->render(testPolyline);
//    if(testRevolution!=NULL) {
//        m_renderer->render(testRevolution);
//        for (CgPolyline* line : testRevolution->getFaceNormalPolylines()) {
//            m_renderer->render(line);
//        }
//        for (CgPolyline* line : testRevolution->getVertexNormalPolylines()) {
//            m_renderer->render(line);
//        }
//    }


    if (polyLineActive) {
        std::cout << polyLineActive << std::endl;
        m_renderer->render(testPolyline);
    } else {
        m_renderer->render(m_base_object);
        for (CgPolyline* line : m_base_object->getFaceNormalPolylines()) {
            m_renderer->render(line);
        }
        for (CgPolyline* line : m_base_object->getVertexNormalPolylines()) {
            m_renderer->render(line);
        }
    }


}

void CgSceneControl::handleEvent(CgBaseEvent* e)
{
    if (e->getType() == Cg::CgRenderObjectEvent) {
        CgRenderObjectEvent* ev = (CgRenderObjectEvent*) e;
        std::cout << "RenderButton: " << ev->getButtonNumber() << std::endl;
        if (ev->getButtonNumber() == 0) {
            polyLineActive = false;
            m_base_object = m_cube;
            m_renderer->init(m_base_object);
        } else if (ev->getButtonNumber() == 1) {
            polyLineActive = true;
            m_renderer->init(testPolyline);

        } else {
            polyLineActive = false;

            m_base_object = testRevolution;
            m_renderer->init(m_base_object);
        }
        m_renderer->redraw();

    }

    if (e->getType() & Cg::CgColorChangeEvent) {
        CgColorChangeEvent* ev = (CgColorChangeEvent*) e;
        if(!m_polyLines.empty())
            for (CgPolyline* poly : m_polyLines) {
                poly->setColor(ev->getColor(), ev->getValue());
            }
        if (testPolyline != NULL) {
            testPolyline->setColor(ev->getColor(), ev->getValue());
        }

        m_renderer->redraw();
    }

    if (e->getType() & Cg::CgSubdivideEvent) {
        CgSubdivideEvent* ev = (CgSubdivideEvent*) e;
        testPolyline->setMaxSubdivision(ev->getValue());
        std::cout << "SUBDIVIDE EVENT" << std::endl;

    }

    if (e->getType() & Cg::CgRevolutionSegmentsEvent) {
        CgSubdivideEvent* ev = (CgSubdivideEvent*) e;
        testRevolution->setRotationSteps(ev->getValue());
        std::cout << "REVOLUTION SEGMENTS EVENT" << std::endl;


    }

    if (e->getType() & Cg::CgButtonClicked) {
        CgButtonClickedEvent* ev = (CgButtonClickedEvent*) e;

        if (ev->getButtonEventType() == Cg::MakeStep) {
            testPolyline->applyLaneRiesenfeld(1);
            std::cout << "MAKE STEP EVENT" << std::endl;

            m_renderer->init(testPolyline);
            m_renderer->redraw();
        } else if (ev->getButtonEventType() == Cg::ClearSteps) {
            std::cout << "CLEAR STEP EVENT" << std::endl;

            testPolyline->reset();
            m_renderer->init(testPolyline);
            m_renderer->redraw();
        } else if (ev->getButtonEventType() == Cg::GenerateRevolution) {
            std::cout << "GENERATRE REVOLUTION EVENT" << std::endl;

            testRevolution->setRotationCurve(testPolyline->getVertices());
            testRevolution->createRotationBody();
            m_renderer->init(testRevolution);
//            for (int i = 0; i < testRevolution->getFaceNormals().size(); i = i+2) {
//                m_polyLines.push_back(
//                            new CgPolyline(
//                                std::vector<glm::vec3> {testRevolution->getFaceNormals().at(i), testRevolution->getFaceNormals().at(i) + testRevolution->getFaceNormals().at(i)},
//                                i)
//                            );
//                }
//            for (CgPolyline* poly : m_polyLines) {
//                m_renderer->init(poly);
//            }

            for (CgPolyline* line : testRevolution->getFaceNormalPolylines()) {
                m_renderer->init(line);
            }
            for (CgPolyline* line : testRevolution->getVertexNormalPolylines()) {
                m_renderer->init(line);
            }

            m_renderer->redraw();

        }

    }

    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.
    if(e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent* ev = (CgMouseEvent*)e;
        //std::cout << *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }


    if(e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent* ev = (CgTrackballEvent*)e;


        m_trackball_rotation=ev->getRotationMatrix();
        m_renderer->redraw();

    }


    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if(e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent* ev = (CgKeyEvent*)e;
        std::cout << *ev <<std::endl;

        if(ev->text()=="+")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(1.2,1.2,1.2));
            m_current_transformation=m_current_transformation*scalemat;
            m_renderer->redraw();
        }
        if(ev->text()=="-")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat,glm::vec3(0.8,0.8,0.8));

            m_current_transformation=m_current_transformation*scalemat;

            m_renderer->redraw();
        }
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if(e->getType() & Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent* ev = (CgWindowResizeEvent*)e;
        std::cout << *ev <<std::endl;
        m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if(e->getType() & Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent* ev = (CgLoadObjFileEvent*)e;


        ObjLoader* loader= new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

        std::vector<glm::vec3> norm;
        loader->getNormalData(norm);

        std::vector<unsigned int> indx;
        loader->getFaceIndexData(indx);



//        m_triangle->init(pos,norm,indx);
//        m_renderer->init(m_triangle);

        m_base_object->init(pos, norm, indx);
        m_base_object->calculateNormals();
        for (CgPolyline* line : m_base_object->getFaceNormalPolylines()) {
            m_renderer->init(line);
        }
        for (CgPolyline* line : m_base_object->getVertexNormalPolylines()) {
            m_renderer->init(line);
        }
        m_renderer->init(m_base_object);

//        for (CgPolyline* line : m_triangle_mesh->getFaceNormalPolylines()) {
//            m_renderer->init(line);
//        }
//        for (CgPolyline* line : m_triangle_mesh->getVertexNormalPolylines()) {
//            m_renderer->init(line);
//        }

        m_renderer->redraw();
    }

    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}
