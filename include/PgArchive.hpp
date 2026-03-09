#pragma once
#include <libpq-fe.h>
#include <string>
#include "Archive.hpp"

class PgArchive : public Archive
{
public:
    PgArchive(const std::string& connInfo);
    ~PgArchive();

    void appendArchive(
        const std::string& Id,
        const std::string& nameSensor,
        double value,
        State state
    ) override;

private:
    PGconn* conn_ = nullptr;
};
