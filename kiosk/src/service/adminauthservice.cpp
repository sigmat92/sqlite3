#include "adminauthservice.h"

bool AdminAuthService::authenticate(const QString& pin)
{
    return pin == "1234";   // 🔐 Change later to secure method
}