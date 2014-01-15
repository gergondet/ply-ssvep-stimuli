#ifndef _H_PLYSSVEPSTIMULUS_H_
#define _H_PLYSSVEPSTIMULUS_H_

#include <boost/shared_ptr.hpp>

#include <bci-interface/DisplayObject/SSVEPStimulus.h>

#include <glm/glm.hpp>

class OculusWindow;

namespace bciinterface
{

struct PLYSSVEPStimulusImpl;

class PLYSSVEPStimulus : public bciinterface::SSVEPStimulus 
{
public:
    PLYSSVEPStimulus(const std::string & model, int frequency, int screenFrequency);

    virtual void RegisterWithOculus(OculusWindow * window);

    virtual void Display(sf::RenderTarget * app, unsigned int frameCount, sf::Clock & clock);

    virtual void Highlight();

    virtual void Unhighlight();

    glm::mat4 & GetModel();

    void SetModel(const glm::mat4 & model);
private:
    boost::shared_ptr<PLYSSVEPStimulusImpl> impl;
};

} // namespace bciinterface

#endif
