//
// Created by niels on 16/03/18.
//

#ifndef PACMAN_CONFIG_H
#define PACMAN_CONFIG_H

#include <iostream>
#include <istream>
#include <map>

class Config
{
public:
    Config() = delete;
    Config(std::string path);
private:
    std::map<std::string, std::string> values = std::map<std::string, std::string>();
};

#endif //PACMAN_CONFIG_H
