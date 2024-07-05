//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_EXCEPTIONS_H
#define ASTAR_EXCEPTIONS_H

#include<iostream>
#include<stdexcept>

class invalid_coordinates: public std::invalid_argument {
public:
    explicit invalid_coordinates(const std::string& msg): std::invalid_argument(msg){}
};

class path_not_found: public std::runtime_error {
public:
    explicit path_not_found(const std::string& msg): std::runtime_error(msg){}
};

class failed_character_init: public std::invalid_argument {
public:
    explicit failed_character_init(const std::string& msg): std::invalid_argument(msg){}
};


#endif //ASTAR_EXCEPTIONS_H
