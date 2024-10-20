#pragma once
#include <string>

typedef std::string String;
class Console {
public:
    Console();
    Console(Console &&) = default;
    Console(const Console &) = default;
    Console &operator=(Console &&) = default;
    Console &operator=(const Console &) = default;
    ~Console();

private:
    
};
