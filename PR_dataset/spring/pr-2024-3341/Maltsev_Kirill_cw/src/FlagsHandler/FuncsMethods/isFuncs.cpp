/**
 * @file isFuncs.cpp
 * @brief Implementation of methods (isFunctions - for tracking wich doFunction should be executed) for FlagsHandler class
 * @version 0.1.0
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "FlagsHandler.h"


bool FlagsHandler::isHelp()
{
    std::set<int> required_flags = {};
    std::set<int> optional_flags = {HELP_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool FlagsHandler::isInfo()
{
    std::set<int> required_flags = {INFO_IDX};
    std::set<int> optional_flags = {INPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool FlagsHandler::isCircle()
{
    std::set<int> required_flags = {CIRCLE_IDX, CENTER_IDX, RADIUS_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX, FILL_IDX, FILL_COLOR_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags) && !(flags_[FILL_IDX].entered && !flags_[FILL_COLOR_IDX].entered);
}

bool FlagsHandler::isRGBFilter()
{
    std::set<int> required_flags = {RGBFILTER_IDX, COMPONENT_NAME_IDX, COMPONENT_VALUE_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool FlagsHandler::isSplit()
{
    std::set<int> required_flags = {SPLIT_IDX, NUMBER_X_IDX, NUMBER_Y_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool FlagsHandler::isSquaredLines()
{
    std::set<int> required_flags = {SQUARED_LINES_IDX, LEFT_UP_IDX, SIDE_SIZE_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX, FILL_IDX, FILL_COLOR_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags) && !(flags_[FILL_IDX].entered && !flags_[FILL_COLOR_IDX].entered);
}

bool FlagsHandler::isOutsideOrnament()
{
    std::set<int> required_flags = {OUTSIDE_ORNAMENT_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}