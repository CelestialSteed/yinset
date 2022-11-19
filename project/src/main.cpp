#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include <math.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstdio>

#include "mesh.h"
#include "toyin.h"

using namespace std;

int main(int argc, char** argv)
{
    Mesh * m = new Mesh();
    std::string filename = "../dataset/monkey坏.obj";
    //cout << filename << endl;
    m -> loadObjFile(filename);
    m -> loadModel();
    
    cout << m -> tris.size() << endl;
    HoleFiller hFiller(*m);
	hFiller.fillHoles();
    cout << m -> tris.size() << endl;
    
    string newname = "output";
    m -> makeObj(newname);


    return 0;
}