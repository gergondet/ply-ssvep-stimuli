#include <bci-interface/DisplayObject/PLYObject.h>

#include <boost/bind.hpp>

#include <OculusWindow.h>

#include "PLYMesh.h"

namespace bciinterface
{

struct PLYObjectImpl
{
    PLYObjectImpl(const std::string & model) : mesh()
    {
        mesh.loadFromFile(model);
    }

    inline void RegisterWithOculus(OculusWindow * window)
    {
        if(window)
        {
            window->addGLcallback(boost::bind(&PLYMesh::render, &mesh, _1));
        }
    }

    PLYMesh mesh;
};

PLYObject::PLYObject(const std::string & model)
: impl(new PLYObjectImpl(model))
{
}

void PLYObject::RegisterWithOculus(OculusWindow * window)
{
    impl->RegisterWithOculus(window);
}

void PLYObject::Display(sf::RenderTarget * app, unsigned int frameCount, sf::Clock & clock)
{
}

glm::mat4 & PLYObject::GetModel()
{
    return impl->mesh.getModel();
}

void PLYObject::SetModel(const glm::mat4 & model)
{
    impl->mesh.setModel(model);
}

}
