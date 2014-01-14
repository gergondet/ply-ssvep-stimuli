#include <bci-interface/BCIInterface.h>
#include <bci-interface/DisplayObject/PLYObject.h>
#include <bci-interface/Utils/FontManager.h>
#include <bci-interface/DisplayObject/FPSCounter.h>

#include <boost/thread.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/System.hpp>

#include <iostream>
#include <libgen.h>

void update(bciinterface::PLYObject * object, sf::Clock & anim_clock)
{
    while(1)
    {
        static float angle = 0;
        glm::mat4 anim_box = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
        angle += 90*anim_clock.getElapsedTime().asMicroseconds()/1e6;
        anim_clock.restart();
        glm::mat4 model_box = glm::translate(glm::mat4(1.0f), glm::vec3(0., 0.25, 0.5));
        model_box = model_box*anim_box;
        object->SetModel(model_box);
    }
}

int main(int argc, char * argv[])
{
    unsigned int width = 1280;
    unsigned int height = 800;

    bciinterface::BCIInterface iface(width, height);
    iface.InitOculus("/home/gergondet/devel/share/OculusWindow");

    std::string model = std::string(dirname(argv[0])) + "/models/can.ply";
    bciinterface::PLYObject * object = new bciinterface::PLYObject(model);
    object->RegisterWithOculus(iface.GetOculusWindow());
    iface.AddObject(object);

    bciinterface::FontManager fm;
    bciinterface::FPSCounter fps_c(fm.GetDefaultFont());
    iface.AddNonOwnedObject(&fps_c);

    sf::Clock anim_clock;
    boost::thread th( boost::bind(&update, object, boost::ref(anim_clock)) );

    int cmd = -1;
    iface.OculusDisplayLoop(cmd);
//    boost::thread th2( boost::bind(&bciinterface::BCIInterface::OculusDisplayLoop, &iface, boost::ref(cmd), "") );
//    th2.join();

    return 0;
}
