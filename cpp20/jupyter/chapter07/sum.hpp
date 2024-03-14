#ifndef JUPYTER_CHAPTER07_SUM_HPP
#define JUPYTER_CHAPTER07_SUM_HPP

auto sum = [](auto&& elems){
    auto result = 0;
    for(auto&& elem : elems){
        result += elem;
    }
    return result;
};

#endif
