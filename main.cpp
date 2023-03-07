#include "Model.h"

// int main(int argc, const char *argv[])
int main()
{   vector <vector<int>> holes;
    std::string filename = "cube.obj";
    Model model({1.5,3});
    model.loadObjFile("dataset/" + filename);
    // model.deleteVertex(0);
    const Integer n = 10;   //fixEdge里n是最大次数吗？
    model.test(n,holes);
   // printf("%d",(int)holes.size());
   for (int i = 0; i < holes.size(); i++) {      // 行数
   for (int j = 0; j < holes[i].size(); j++) {  // A[i].size() 第i行的列数
     printf("%d ",holes[i][j]);
   }
   printf("\n");}
    model.saveObjFile("output/" + filename);

    std::cout << "output successfully" << std::endl;
    return 0;
}