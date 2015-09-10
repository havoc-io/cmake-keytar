#include "keytar.h"

namespace keytar {

bool ReplacePassword(const std::string& service,
                     const std::string& account,
                     const std::string& password) {
    keytar::DeletePassword(service, account);
    return keytar::AddPassword(service, account, password);
}

} // namespace keytar
