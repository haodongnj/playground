#include "shape.hpp"
#include "circle.hpp"

int main(){
    Circle circle;
    Shape shape(circle);
    draw(shape, std::cout);

    return 0;
}