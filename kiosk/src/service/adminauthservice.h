#pragma once
#include <QString>

class AdminAuthService
{
public:
    bool authenticate(const QString& pin);
};