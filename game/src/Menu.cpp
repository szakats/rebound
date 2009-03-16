#include "common.h"

#include "Menu.h"
#include "WindowManager.h"

#include <osgText/Text>

class MouseHandler : public osgGA::GUIEventHandler
{
    public:
        virtual bool handle (const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
        {
            float x,y;
            switch(ea.getEventType())
            {
                case(osgGA::GUIEventAdapter::MOVE):
                    break;
                //case(osgGA::GUIEventAdapter::PUSH):
                case(osgGA::GUIEventAdapter::RELEASE):
                    x = ea.getX();
                    y = ea.getY();
                    break;
            }
            return false;
        }
};

void Menu::Draw()
{
    osg::ref_ptr<osg::Group> root = WindowManager::Instance().GetRoot();

    osg::ref_ptr<osg::Camera> camera(new osg::Camera);
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    root->addChild(camera);

    osg::ref_ptr<osg::Geode> geode(new osg::Geode);
    camera->addChild(geode);

    osgText::Font* font = osgText::readFontFile("D:\\rebound\\rebound\\win\\verdana.ttf");

    int z = 50;
    for(MenuItemList::iterator itr = _menuItems.begin(); itr != _menuItems.end(); ++itr)
    {
        osg::ref_ptr<osgText::Text> text(new osgText::Text());
        text->setText((*itr)->GetText());
        text->setFont(font);
        text->setCharacterSize(100);
        text->setPosition( osg::Vec3(50,z,0) );
        geode->addDrawable(text);
        z += 100;
    }

    WindowManager::Instance().GetViewer().addEventHandler(new MouseHandler); 

    //WindowManager::Instance().GetViewer().setCameraManipulator(new osgGA::CameraViewSwitchManipulator());
}