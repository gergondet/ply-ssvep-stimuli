#ifndef _H_PLYOBJECT_H_
#define _H_PLYOBJECT_H_

#include <bci-interface/DisplayObject.h>

#include <boost/shared_ptr.hpp>

class OculusWindow;

namespace bciinterface
{

struct PLYObjectImpl;

class PLYObject : public DisplayObject
{
public:
    PLYObject(const std::string & model);

    virtual void RegisterWithOculus(OculusWindow * window);

    virtual void Display(sf::RenderTarget * app, unsigned int frameCount, sf::Clock & clock);
private:
    boost::shared_ptr<PLYObjectImpl> impl;
};

} // namespace bciinterface

#endif
