#pragma once

#include <vector>
#include "ArchiveRecord.hpp"

class ArchiveRepotr
{
public:
    static void printSummary(const std::vector<ArchiveRecord>& records);
};