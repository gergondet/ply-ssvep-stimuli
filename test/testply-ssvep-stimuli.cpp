#include <bci-interface/BCIInterface.h>
#include <bci-interface/DisplayObject/PLYObject.h>

#include <iostream>
#include <libgen.h>

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

    int cmd = -1;
    iface.OculusDisplayLoop(cmd);

    return 0;
}
