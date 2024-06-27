#include <vector>
#include <unordered_map>
#include <string>

#include "imageStructs.h"
#include "parsing_fucntions.h"

void outsideRect(BMPInfoHeader infoHeader, std::vector<std::vector<Pixel>> &bytesARR, std::unordered_map<std::string, std::string> argsMap);