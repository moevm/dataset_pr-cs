#pragma once

#include <cmath>
#include <map>

#include "image_editor.h"

namespace ornaments {

enum PatternsId {
  k_rectangle = 1,
  k_circle,
  k_semicircle,
};

const std::map<const std::string, int> kPatterns{
	{"rectangle", k_rectangle},
	{"circle", k_circle},
	{"semicircles", k_semicircle}
};

}

