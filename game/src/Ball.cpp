#include "common.h"

#include "Ball.h"
#include "WindowManager.h"

#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <osgAL/SoundNode>
#include <osgAL/SoundRoot>
#include <osgAL/SoundManager>
#include <osgAL/SoundState>

osg::ref_ptr<osgAL::SoundNode> createSound(const std::string& file)
{
	// Create a sample, load a .wav file.
	openalpp::Sample *sample = new openalpp::Sample(file.c_str());

	// Create a named sound state.
	osg::ref_ptr<osgAL::SoundState> sound_state = new osgAL::SoundState("bee");

	// Let the soundstate use the sample we just created
	sound_state->setSample(sample);

	// Set its gain (volume) to 0.9
	sound_state->setGain(0.9f);

	// Set its pitch to 1 (normal speed)
	sound_state->setPitch(1);

	// Make it play
	sound_state->setPlay(true);

	// The sound should loop over and over again
	sound_state->setLooping(true);

	// Allocate a hardware soundsource to this soundstate (priority 10)
	//
	sound_state->allocateSource(10, false);

	// At 40 the gain will be half of full!
	sound_state->setReferenceDistance(5);
	sound_state->setRolloffFactor(4);
	sound_state->apply();

	// Add the soundstate to the sound manager, so we can find it later on if we want to
	osgAL::SoundManager::instance()->addSoundState(sound_state.get());

	// Create a sound node and attach the soundstate to it.
	osg::ref_ptr<osgAL::SoundNode> sound = new osgAL::SoundNode;
	sound->setSoundState(sound_state.get());

	return sound;
}

Ball::Ball()
    : _geode(new osg::Geode),
      _xform(new osg::PositionAttitudeTransform),
      _poz(0,0,0)
{
    osgAL::SoundManager::instance()->init(16);
	osgAL::SoundManager::instance()->getEnvironment()->setDistanceModel(openalpp::InverseDistance);
	osgAL::SoundManager::instance()->getEnvironment()->setDopplerFactor(1);

    osg::ref_ptr<osg::Group> root = WindowManager::Instance().GetRoot();
    _geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0,0,0), 0.7f)));
    _xform->addChild(_geode);
    _xform->addChild(createSound("bee.wav"));
    root->addChild(_xform);
}

float Ball::MoveTo(osg::Vec3 poz, float speed)
{
    osg::ref_ptr<osg::AnimationPath> path(new osg::AnimationPath());

    path->setLoopMode(osg::AnimationPath::LOOP); //tmp
    
    osg::Vec3 d = poz - _poz;
    float dist = sqrt(d.x()*d.x() + d.y()*d.y() + d.z()*d.z());
    float time = dist / speed;
    path->insert(0, osg::AnimationPath::ControlPoint(_poz));
    path->insert(time, osg::AnimationPath::ControlPoint(poz));
    _poz = poz;

    _xform->setUpdateCallback(new osg::AnimationPathCallback(path));
    return time;
}