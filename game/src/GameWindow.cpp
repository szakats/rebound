#include "common.h"

#include "WindowManager.h"
#include "GameWindow.h"
#include "Ball.h"

#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>

GameWindow::GameWindow() : Window(NULL)
{
    osg::ref_ptr<osg::Group> root = WindowManager::Instance().GetRoot();

    Ball *b = new Ball(); // tmp

    osg::ref_ptr<osg::Geode> geode2 = new osg::Geode();
    geode2->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(5,5,5), 1.0f)));
    root->addChild(geode2);

    b->MoveTo(osg::Vec3(0,30,0), 10);

    WindowManager::Instance().GetViewer().setCameraManipulator(new osgGA::TrackballManipulator());
}