#pragma once

#include <iostream>
#include <memory>
#include <utility>

class Shape {
    public:
    template<typename T>
    Shape(T&& t) : concept(new ShapeModel<T>(std::forward<T>(t))) {}

    private:
    class ShapeConcept {
        public:
        virtual ~ShapeConcept() {}
        virtual void draw(std::ostream& os) const = 0;
    };

    template<typename T>
    class ShapeModel : public ShapeConcept {
        public:
        ShapeModel(T&& t) : impl(std::forward<T>(t)) {}
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
