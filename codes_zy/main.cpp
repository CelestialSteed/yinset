#include "Model.h"

// int main(int argc, const char *argv[])
int main()
{
    std::string filename = "polyhedron.obj";
    Model model({1.5,3});
    model.loadObjFile("dataset/" + filename);
    // model.deleteVertex(0);
    const Integer n = 10;
    model.test(n);
    model.saveObjFile("output/" + filename);

    std::cout << "output successfully" << std::endl;
    return 0;
}