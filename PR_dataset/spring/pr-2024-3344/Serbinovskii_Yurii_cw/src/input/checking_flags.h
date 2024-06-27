#pragma once

#include <iostream>
#include <getopt.h>
#include <unordered_map>
#include <string>
#include "../other/messages.h"

std::unordered_map<std::string, std::string> getFlags(int argc, char** argv);