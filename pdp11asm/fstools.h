#include <string>

#ifdef WIN32
void saveStringToFile(const char* fileName, const void* buf, size_t len);
void loadStringFromFile(std::string& buf, const char* fileName);
void chdirToFile(const char* fileName);
std::string replaceExtension(const std::string& fileName, const char* ext);

typedef char syschar_t;
typedef std::string sysstring_t;
#define _T(S) L##S
#else
typedef char syschar_t;
typedef std::string sysstring_t;
#define _T(S) S
#endif

void saveStringToFile(const char* fileName, const void* buf, size_t len);
void loadStringFromFile(std::string& buf, const char* fileName);
void chdirToFile(const char* fileName);
std::string replaceExtension(const std::string& fileName, const char* ext);

