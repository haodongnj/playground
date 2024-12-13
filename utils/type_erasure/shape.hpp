#pragma once

#include <iostream>
#include <memory>

class Shape {
    public:
    template<typename T>
    Shape(const T& t) : concept(new ShapeModel<T>(t)) {}

    private:
    class ShapeConcept {
        public:
        virtual ~ShapeConcept() {}
        virtual void draw(std::ostream& os) const = 0;
    };

    template<typename T>
    class ShapeModel : public ShapeConcept {
        public:
        ShapeModel(const T& t) : impl(t) {}
        virtual void draw(std::ostream& os) const {
            impl.draw(os);
        }

        private:
        T impl;
    };

    std::unique_ptr<ShapeConcept> concept;

    friend void draw(const Shape& shape, std::ostream& os){
        shape.concept->draw(os);        
    }
};
