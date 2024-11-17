#include "hello_triangle.h"
#include "hello_triangle_ebo.h"

int main()
{
    //HelloTriangle* triangle = new HelloTriangle();
    //triangle->Run();
    HelloTriangleEbo* triangleEbo = new HelloTriangleEbo();
    triangleEbo->Run();
}