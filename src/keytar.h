#ifndef SRC_KEYTAR_H_
#define SRC_KEYTAR_H_

#include <string>

// Visibility macros
#ifdef _MSC_VER
    #define KEYTAR_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define KEYTAR_API __attribute__((visibility("default")))
#else
    #define KEYTAR_API
#endif

namespace keytar {

KEYTAR_API
bool AddPassword(const std::string& service,
                 const std::string& account,
                 const std::string& password);

KEYTAR_API
bool GetPassword(const std::string& service,
                 const std::string& account,
                 std::string* password);

KEYTAR_API
bool DeletePassword(const std::string& service, const std::string& account);

KEYTAR_API
bool FindPassword(const std::string& service, std::string* password);

KEYTAR_API
bool ReplacePassword(const std::string& service,
                     const std::string& account,
                     const std::string& password);

}  // namespace keytar

#endif  // SRC_KEYTAR_H_
