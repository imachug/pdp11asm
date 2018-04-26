// PDP11 Assembler (c) 15-01-2015 vinxru

#include "lstwriter.h"
#include <string>
#include <assert.h>
#include "compiler.h"
#include <stdio.h>
#include "fstools.h"
#include <unistd.h>

void LstWriter::remark(size_t addr, unsigned type, const std::string& text)
{
    remarks.push_back(Remark());
    Remark& r = remarks.back();
    r.type = type;
    r.addr = addr;
    r.text = text;
}

//---------------------------------------------------------------------------------------------------------------------

void LstWriter::writeFile(const std::string& fileName) {
  std::string fileName2 = replaceExtension(fileName, "lst");
  if(fileName != fileName2) saveStringToFile(fileName2.c_str(), buffer.c_str(), buffer.size());
}

//-----------------------------------------------------------------------------

static size_t linelen(const char* p) {
  const char *a = strchr(p, '\r'), *b = strchr(p, '\n');
  if(a == 0 && b == 0) return strlen(p);
  if(a == 0 || b < a) return (size_t)(b - p);
  return (size_t)(a - p);
}

//-----------------------------------------------------------------------------

void LstWriter::appendBuffer(const char* data, size_t size) {
  size_t newSize = buffer.size() + size; //! Тут может быть переполнение
  if(newSize > buffer.capacity()) {
    size_t gran = buffer.capacity() + buffer.capacity()/2; //! Тут может быть переполнение
    if(newSize < gran) newSize = gran;
    buffer.reserve(newSize);
  }
  buffer.append(data, size);
//  write(0,data,size); // DEBUG
}

//-----------------------------------------------------------------------------

void LstWriter::beforeCompileLine() {
  if(!out || !p) return;
  out->writePosChanged = false;
  prev_writePtr = out->writePtr;
  prev_sigCursor = p->sigCursor;
  char info[256];
  snprintf(info, sizeof(info), "%04i %04X ", int(p->line), int(out->writePtr)); //! overflow
  appendBuffer(info);
}

//-----------------------------------------------------------------------------

void LstWriter::afterCompileLine3()
{
    afterCompileLine2();
    appendBuffer(prev_sigCursor, linelen(prev_sigCursor));
    appendBuffer("\r\n");
}

//-----------------------------------------------------------------------------

void LstWriter::afterCompileLine2()
{
    if(!out) return;
    const int MAX_OPCODES = 3;
    char info[MAX_OPCODES*7 + 16];
    char* ptr = info;
    if(!out->writePosChanged)
    {
        if(!hexMode)
        {
            size_t l = (out->writePtr - prev_writePtr) / 2;
            if(l > MAX_OPCODES) l = MAX_OPCODES;
            for(; l > 0; l--) {
                ptr += snprintf(ptr, info+sizeof(info)-ptr, "%06o ", (unsigned int)(*(unsigned short*)(out->writeBuf + prev_writePtr))); //! overflow
                prev_writePtr += 2;
            }
        } else {
            size_t l = (out->writePtr - prev_writePtr);
            if(l > MAX_OPCODES) l = MAX_OPCODES;
            for(; l > 0; l--) {
                ptr += snprintf(ptr, info+sizeof(info)-ptr, "%02X ", (unsigned int)(*(unsigned char*)(out->writeBuf + prev_writePtr))); //! overflow
                prev_writePtr ++;
            }
        }
    }
    memset(ptr, ' ', info+sizeof(info)-ptr); // Почему то указатель - указатель не дает size_t!
    info[MAX_OPCODES*7] = 9;
    info[MAX_OPCODES*7+1] = 9;
    info[MAX_OPCODES*7+2] = 0;
    appendBuffer(info);
}
