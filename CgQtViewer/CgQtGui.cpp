

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgColorChangEvent.h"
#include "../CgEvents/CgSubdivideEvent.h"
#include "../CgEvents/CgButtonClickedEvent.h"
#include "../CgEvents/CgRenderObjectEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>


CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;


    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    option_panel = new QWidget;
    createOptionsTab(option_panel);

    QTabWidget* m_tabs = new QTabWidget();
//    m_tabs->addTab(opt,"&My Tab1");
//    m_tabs->addTab(otheropt,"&My Tab2");

    QWidget *objektopt = new QWidget();
    m_tabs->addTab(option_panel, "&Options");


    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2020"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);


    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);



}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QGroupBox* CgQtGui::createObjectSelectPanel()
{

    QGroupBox *groupBox = new QGroupBox(tr("Objektoption"));

    radio1 = new QRadioButton(tr("Würfel"));
    connect(radio1, SIGNAL(clicked(bool)), this, SLOT(radioButtonChanged()));
    radio1->setChecked(true);

    radio2 = new QRadioButton(tr("Polyline"));
    connect(radio2, SIGNAL(clicked(bool)), this, SLOT(radioButtonChanged()));
    radio3 = new QRadioButton(tr("Rotatioskörper"));
    connect(radio3, SIGNAL(clicked(bool)), this, SLOT(radioButtonChanged()));
    radio4 = new QRadioButton(tr("Scenegraph"));
    connect(radio4, SIGNAL(clicked(bool)), this, SLOT(radioButtonChanged()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addWidget(radio4);
    groupBox->setLayout(vbox);

    return groupBox;

}

QSlider* CgQtGui::createColorSlider() {
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 255);
    slider->setSingleStep(1);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QGroupBox* CgQtGui::createColorSliders()
{
    QGroupBox *groupBox = new QGroupBox(tr("Farbwahl"));

    QHBoxLayout *hbox = new QHBoxLayout();

    QSlider *sliderRed = createColorSlider();
    sliderRed->setValue(Cg::BASECOLOR[0] * 255);
    connect(sliderRed, SIGNAL(valueChanged(int)), this, SLOT(slotRedColorChanged(int)));

    QSlider *sliderGreen = createColorSlider();
    sliderGreen->setValue(Cg::BASECOLOR[1] * 255);
    connect(sliderGreen, SIGNAL(valueChanged(int)), this, SLOT(slotGreenColorChanged(int)));

    QSlider *sliderBlue = createColorSlider();
    sliderBlue->setValue(Cg::BASECOLOR[2] * 255);
    connect(sliderBlue, SIGNAL(valueChanged(int)), this, SLOT(slotBlueColorChanged(int)));


    hbox->addWidget(sliderRed);
    hbox->addWidget(sliderGreen);
    hbox->addWidget(sliderBlue);

    groupBox->setLayout(hbox);

    return groupBox;


//    colorLabel = new QLabel("Color");
//    tab_options_control->addWidget(colorLabel);
//    redColorSpinBox = new QSpinBox();
//    redColorSpinBox->setMinimum(0);
//    redColorSpinBox->setMaximum(255);
//    redColorSpinBox->setValue(Cg::BASECOLOR[0] * 255);
//    redColorSpinBox->setPrefix("RED: ");
//    connect(redColorSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotRedColorChanged(int)));
//    tab_color_control->addWidget(redColorSpinBox);

//    greenColorSpinBox = new QSpinBox();
//    greenColorSpinBox->setMinimum(0);
//    greenColorSpinBox->setMaximum(255);
//    greenColorSpinBox->setValue(Cg::BASECOLOR[1] * 255);
//    greenColorSpinBox->setPrefix("GREEN: ");
//    connect(greenColorSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotGreenColorChanged(int)));
//    tab_color_control->addWidget(greenColorSpinBox);

//    blueColorSpinBox = new QSpinBox();
//    blueColorSpinBox->setMinimum(0);
//    blueColorSpinBox->setMaximum(255);
//    blueColorSpinBox->setValue(Cg::BASECOLOR[2] * 255);
//    blueColorSpinBox->setPrefix("BLUE: ");
//    connect(blueColorSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotBlueColorChanged(int)));
//    tab_color_control->addWidget(blueColorSpinBox);
}

QGroupBox* CgQtGui::createRiesenfeldControl() {
    QGroupBox *groupBox = new QGroupBox(tr("Unterteilungsschritte"));

    QVBoxLayout *tab_laneRiesenfeld_control = new QVBoxLayout();

    QHBoxLayout* tab_laneRiesenfeld_input = new QHBoxLayout();
    laneRiesenfeldSpin = new QSpinBox();
    laneRiesenfeldSpin->setMinimum(1);
    laneRiesenfeldSpin->setMaximum(15);
    laneRiesenfeldSpin->setValue(1);
    connect(laneRiesenfeldSpin, SIGNAL(valueChanged(int)), this, SLOT(slotSubdivideChanged(int)));
    tab_laneRiesenfeld_input->addWidget(laneRiesenfeldSpin);

    buttonLaneGo = new QPushButton();
    QString input = "Schritt: " + QString::number(step) + " von " + QString::number(maxSteps);
    buttonLaneGo->setText(input);
    connect(buttonLaneGo, SIGNAL(released()), this, SLOT(slotSchrittButtonClicked()));
    tab_laneRiesenfeld_input->addWidget(buttonLaneGo);

    QPushButton *clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(released()), this, SLOT(slotClearButtonClicked()));

    tab_laneRiesenfeld_control->addLayout(tab_laneRiesenfeld_input);

    tab_laneRiesenfeld_control->addWidget(clearButton);

    groupBox->setLayout(tab_laneRiesenfeld_control);

    return groupBox;

}

QGroupBox* CgQtGui::createRotationControl() {
    QGroupBox *groupBox = new QGroupBox(tr("Rotationsschritte"));

    QHBoxLayout* solidOfRevolution_cotrol = new QHBoxLayout();
    revolutionSegmentsSpinBox = new QSpinBox();
    revolutionSegmentsSpinBox->setMinimum(1);
    revolutionSegmentsSpinBox->setMaximum(10000);
    revolutionSegmentsSpinBox->setValue(1);
    connect(revolutionSegmentsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotRevolutionSegmentsChanged(int)));
    solidOfRevolution_cotrol->addWidget(revolutionSegmentsSpinBox);

    buttonRevolutionGo = new QPushButton("Generieren");
    connect(buttonRevolutionGo, SIGNAL(released()), this, SLOT(slotRevolutionGoClicked()));
    solidOfRevolution_cotrol->addWidget(buttonRevolutionGo);

    groupBox->setLayout(solidOfRevolution_cotrol);

    return groupBox;
}
void CgQtGui::createOptionPanelExample1(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    tab1_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
    // mySpinBox1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab1_control->addWidget(mySpinBox1);


    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab1_control->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab1_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );



    parent->setLayout(tab1_control);

}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();



    /*Example for using a button group */

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    parent->setLayout(tab2_control);

}

void CgQtGui::createOptionsTab(QWidget *panel) {
    tab_options_control = new QVBoxLayout();

    tab_options_control->addWidget(createObjectSelectPanel());

    tab_options_control->addWidget(createColorSliders());

    riesenFeldControl = createRiesenfeldControl();
    riesenFeldControl->setVisible(false);
    rotationControl = createRotationControl();
    rotationControl->setVisible(false);

    tab_options_control->addWidget(riesenFeldControl);
    tab_options_control->addWidget(rotationControl);
    panel->setLayout(tab_options_control);

}

void CgQtGui::radioButtonChanged() {
    std::cout << riesenFeldControl << ", " << rotationControl << std::endl;
    CgBaseEvent* e;
    if (radio1->isChecked()) {
        riesenFeldControl->setVisible(false);
        rotationControl->setVisible(false);
        e = new CgRenderObjectEvent(Cg::CgRenderObjectEvent, 0);
    } else if (radio2->isChecked()){
        riesenFeldControl->setVisible(true);
        rotationControl->setVisible(false);
        e = new CgRenderObjectEvent(Cg::CgRenderObjectEvent, 1);

    }
    if (radio3->isChecked()) {
        riesenFeldControl->setVisible(true);
        rotationControl->setVisible(true);
        e = new CgRenderObjectEvent(Cg::CgRenderObjectEvent, 2);
    }
    if (radio4->isChecked()) {
        riesenFeldControl->setVisible(true);
        rotationControl->setVisible(false);
        e = new CgRenderObjectEvent(Cg::CgRenderObjectEvent, 3);
    }

    notifyObserver(e);
}

void CgQtGui::slotRedColorChanged(int value)
{
    CgBaseEvent* e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Red, value);

    notifyObserver(e);

}
void CgQtGui::slotGreenColorChanged(int value)
{
    CgBaseEvent* e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Green, value);

    notifyObserver(e);
}
void CgQtGui::slotBlueColorChanged(int value)
{
    CgBaseEvent* e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Blue, value);

    notifyObserver(e);
}

void CgQtGui::slotSubdivideChanged(int value) {
    CgBaseEvent*  e = new CgSubdivideEvent(Cg::CgSubdivideEvent, value);
    maxSteps = value;
    QString input = "Schritt: " + QString::number(step) + " von " + QString::number(maxSteps);
    buttonLaneGo->setText(input);
    notifyObserver(e);
}
void CgQtGui::slotSchrittButtonClicked() {
    CgBaseEvent* e = new CgButtonClickedEvent(Cg::CgButtonClicked, Cg::MakeStep);
    if (step < maxSteps) {
        step++;
        QString input = "Schritt: " + QString::number(step) + " von " + QString::number(maxSteps);
        buttonLaneGo->setText(input);
    }

    notifyObserver(e);
}
void CgQtGui::slotClearButtonClicked() {
    CgBaseEvent* e = new CgButtonClickedEvent(Cg::CgButtonClicked, Cg::ClearSteps);
    step = 1;
    QString input = "Schritt: " + QString::number(step) + " von " + QString::number(maxSteps);
    buttonLaneGo->setText(input);
    notifyObserver(e);
}

void CgQtGui::slotRevolutionSegmentsChanged(int value) {
    std::cout << "FUnktioniert" << std::endl;
    CgBaseEvent* e = new CgSubdivideEvent(Cg::CgRevolutionSegmentsEvent, value);
    notifyObserver(e);
}
void CgQtGui::slotRevolutionGoClicked() {
    CgBaseEvent* e = new CgButtonClickedEvent(Cg::CgButtonClicked, Cg::GenerateRevolution);
    notifyObserver(e);
}

void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{

}
void CgQtGui::slotMyCheckBox1Changed()
{

}
void CgQtGui::slotLoadMeshFile()
{



    QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));


    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}


void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotMyButton1Pressed()
{
    std::cout << "button 1 pressed " << std::endl;

}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

    // std::cout << QApplication::keyboardModifiers() << std::endl;

    //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


    if(event->type()==QEvent::MouseButtonPress)
    {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
    }

    if(event->type()==QEvent::MouseMove)
    {
        CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                         glm::vec2(event->localPos().x() ,event->localPos().y()),
                                         (Cg::MouseButtons)event->button());
        notifyObserver(e);
    }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
    CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
    notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
    CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
    notifyObserver(e);
}


CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





