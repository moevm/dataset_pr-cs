#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>


#include "imageStructs.h"
#include "parsing_fucntions.h"

std::vector<std::vector<Pixel>> ornament(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap);


