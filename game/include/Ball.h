#ifndef __REBOUND_BALL_H__
#define __REBOUND_BALL_H__

class Ball
{
    public:
        Ball();
        void SetPosition(osg::Vec3 poz);
        float MoveTo(osg::Vec3 poz, float speed);
    private:
        osg::ref_ptr<osg::Geode> _geode;
        osg::ref_ptr<osg::PositionAttitudeTransform> _xform;
        osg::Vec3 _poz;
};

#endif //__REBOUND_BALL_H__