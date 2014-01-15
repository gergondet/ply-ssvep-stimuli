#include "bci-interface/DisplayObject/PLYSSVEPStimulus.h"

#include "PLYMesh.h"

#include <OculusWindow.h>
#include <boost/bind.hpp>

namespace bciinterface
{

struct PLYSSVEPStimulusImpl
{
    PLYSSVEPStimulusImpl(const std::string & model)
    : mesh(), should_display(false)
    {
        mesh.loadFromFile(model);
    }

    void render(glm::mat4 & vp)
    {
        if(should_display)
        {
            mesh.render(vp);
        }
    }

    void RegisterWithOculus(OculusWindow * window)
    {
        if(window)
        {
            boost::function<void (glm::mat4 & vp)> fn = boost::bind(&PLYSSVEPStimulusImpl::render, this, _1);
            window->addGLcallback(fn);
        }
    }

    PLYMesh mesh;
    bool should_display;
};

PLYSSVEPStimulus::PLYSSVEPStimulus(const std::string & model, int frequency, int screenFrequency)
: SSVEPStimulus(frequency, screenFrequency), impl(new PLYSSVEPStimulusImpl(model))
{
}

void PLYSSVEPStimulus::RegisterWithOculus(OculusWindow * window)
{
    impl->RegisterWithOculus(window);
}

void PLYSSVEPStimulus::Display(sf::RenderTarget * app, unsigned int frameCount, sf::Clock & clock)
{
    impl->should_display = DisplayActive(frameCount);
}

void PLYSSVEPStimulus::Highlight()
{
    impl->mesh.Highlight();
}

void PLYSSVEPStimulus::Unhighlight()
{
    impl->mesh.Unhighlight();
}


glm::mat4 & PLYSSVEPStimulus::GetModel()
{
    return impl->mesh.getModel();
}

void PLYSSVEPStimulus::SetModel(const glm::mat4 & model)
{
    impl->mesh.setModel(model);
}

}
