#include "Model.h"

// int main(int argc, const char *argv[])
int main()
{
    std::string filename = "cube.obj";
    Model model({1, 2});
    model.loadObjFile("dataset/" + filename);
    // model.deleteVertex(0);
    model.deleteEdge(1);
    model.saveObjFile("output/" + filename);
    return 0;
}