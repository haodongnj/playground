// g++ -std=c++17 main.cpp
#include "shape.hpp"
#include "circle.hpp"
#include <vector>

class IntVector {
    std::vector<int> data;
    public:
    IntVector() : data{1, 2, 3, 4, 5} {}
    void draw(std::ostream& os) const {
        os << "IntVector: ";
        for(const auto i : data){
            os << i << " ";
        }
    }
};

int main(){
    Shape shape((Circle()));
    Shape vector_as_shape((IntVector()));
    
    draw(shape, std::cout);
    draw(vector_as_shape, std::cout);

    return 0;
}