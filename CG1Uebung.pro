QT       += core gui opengl widgets

TEMPLATE = app

TARGET = CgViewer

SOURCES += main.cpp \
    CgQtViewer/CGQtGLRenderWidget.cpp \
    CgQtViewer/CgQtGui.cpp \
    CgBase/CgObservable.cpp \
    CgEvents/CgMouseEvent.cpp \
    CgQtViewer/CgQtMainApplication.cpp \
    CgSceneGraph/CgSceneControl.cpp \
    CgEvents/CgKeyEvent.cpp \
    CgSceneGraph/CgExampleTriangle.cpp \
    CgQtViewer/CgQtGlBufferObject.cpp \
    CgQtViewer/CgTrackball.cpp \
    CgEvents/CgWindowResizeEvent.cpp \
    CgEvents/CgLoadObjFileEvent.cpp \
    CgUtils/ObjLoader.cpp \
    CgEvents/CgTrackballEvent.cpp \
    CgEvents/CgColorChangEvent.cpp \
    CgSceneGraph/CgCube.cpp \
    CgSceneGraph/CgPolyline.cpp \
    CgEvents/CgSubdivideEvent.cpp \
    CgEvents/CgButtonClickedEvent.cpp \
    CgSceneGraph/CgTriangleMesh.cpp \
    CgUtils/IdGenerator.cpp \
    CgSceneGraph/CgSolidOfRevolution.cpp \
    CgEvents/CgRenderObjectEvent.cpp \
    CgSceneGraph/CgScenegraphEntity.cpp \
    CgSceneGraph/CgAppearance.cpp \
    CgSceneGraph/CgScenegraph.cpp

HEADERS += \
    CgQtViewer/CgQtGLRenderWidget.h \
    CgQtViewer/CgQtGui.h \
    CgBase/CgObserver.h \
    CgBase/CgObservable.h \
    CgBase/CgBaseEvent.h \
    CgBase/CgEnums.h \
    CgEvents/CgMouseEvent.h \
    CgQtViewer/CgQtMainApplication.h \
    CgSceneGraph/CgSceneControl.h \
    CgEvents/CgKeyEvent.h \
    CgBase/CgBaseRenderer.h \
    CgBase/CgBaseRenderableObject.h \
    CgSceneGraph/CgExampleTriangle.h \
    CgBase/CgBasePointCloud.h \
    CgBase/CgBaseTriangleMesh.h \
    CgBase/CgBasePolygonMesh.h \
    CgBase/CgBasePolyline.h \
    CgBase/CgBaseSceneControl.h \
    CgQtViewer/CgQtGlBufferObject.h \
    CgQtViewer/CgTrackball.h \
    CgEvents/CgWindowResizeEvent.h \
    CgEvents/CgLoadObjFileEvent.h \
    CgUtils/ObjLoader.h \
    CgBase/CgBaseImage.h \
    CgEvents/CgTrackballEvent.h \
    CgEvents/CgColorChangEvent.h \
    CgSceneGraph/CgCube.h \
    CgSceneGraph/CgPolyline.h \
    CgEvents/CgSubdivideEvent.h \
    CgEvents/CgButtonClickedEvent.h \
    CgUtils/IdGenerator.h \
    CgSceneGraph/CgTriangleMesh.h \
    CgUtils/IdGenerator.h \
    CgSceneGraph/CgSolidOfRevolution.h \
    CgEvents/CgRenderObjectEvent.h \
    CgSceneGraph/CgScenegraphEntity.h \
    CgSceneGraph/CgAppearance.h \
    CgSceneGraph/CgScenegraph.h

