#include "fstools.h"

#ifdef WIN32
#include <windows.h>
#include <stdint.h>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <direct.h>

void saveStringToFile(const char* fileName2, const void* buf, size_t len)
{
    HANDLE h = CreateFile(fileName2, GENERIC_READ|GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if(h == INVALID_HANDLE_VALUE) throw std::runtime_error("Can't create lst file");
    DWORD wr;
    if(!WriteFile(h, buf, len, &wr, 0) || wr != len) { CloseHandle(h); throw std::runtime_error("Can't create lst file"); }
    CloseHandle(h);
}

//-----------------------------------------------------------------------------

uint64_t GetFileSize64(HANDLE hFile)
{
    DWORD dwSizeHigh=0, dwSizeLow=0;
    dwSizeLow = GetFileSize(hFile, &dwSizeHigh); //! Код ошибки?
    return ((uint64_t)dwSizeHigh * (uint64_t)(MAXDWORD+1)) + dwSizeLow;
}

//-----------------------------------------------------------------------------

void loadStringFromFile(std::string& buffer, const char* fileName)
{
    HANDLE h = CreateFile(fileName, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if(h == INVALID_HANDLE_VALUE) throw std::runtime_error("Can't open file");
    uint64_t size = GetFileSize64(h);
    if(size >= std::numeric_limits<size_t>::max()) { CloseHandle(h); throw std::runtime_error("Source file too large"); }
    buffer.resize(size);
    DWORD wr;
    if(!ReadFile(h, (LPVOID)buffer.c_str(), buffer.size(), &wr, 0) || wr != buffer.size()) { CloseHandle(h); throw std::runtime_error("Can't open file"); }
    CloseHandle(h);
}

//-----------------------------------------------------------------------------

void chdirToFile(const char* fileName) {
  char *a = strrchr(fileName, '/'), *b = strrchr(fileName, '\\');
  if(a==0 || b>a) a = b;
  if(a) _chdir(std::string(fileName, (size_t)(a-fileName)).c_str());
}

//-----------------------------------------------------------------------------

#else

#include <fstream>
#include <limits>
#include <unistd.h>
#include <string.h>

void saveStringToFile(const char* fileName2, const void* buf, size_t len)
{
    std::ofstream file;
    file.open(fileName2);
    if(!file.is_open()) throw std::runtime_error("Can't create lst file");
    file.write((const char*)buf, len);
}

//-----------------------------------------------------------------------------

void loadStringFromFile(std::string& buf, const char* fileName) {
    std::fstream file(fileName, std::ifstream::in|std::ifstream::binary);
    if(!file.is_open()) throw std::runtime_error("Can't open source file");
    std::streamoff size = file.rdbuf()->pubseekoff(0, std::fstream::end);
    if(size < 0 || size >= std::numeric_limits<size_t>::max()) throw std::runtime_error("Source file too large");
    buf.resize((size_t)size);
    file.rdbuf()->pubseekoff(0, std::fstream::beg);
    file.rdbuf()->sgetn(const_cast<char*>(buf.c_str()), buf.size());
}

//-----------------------------------------------------------------------------

void chdirToFile(const char* fileName) {
    const char *a = strrchr(fileName, '/');
    if(a) chdir(std::string(fileName, a-fileName).c_str()); //! Код ошибки
}

#endif

//-----------------------------------------------------------------------------

std::string replaceExtension(const std::string& fileName, const char* ext) {
    size_t s = fileName.rfind('.');
    if(s==std::string::npos || fileName.find('/', s)!=std::string::npos || fileName.find('\\', s)!=std::string::npos) return fileName;
    if(ext[0] == '\0') {
        // No extension
        return fileName.substr(0, s);
    }
    return fileName.substr(0,s+1) + ext;
}

