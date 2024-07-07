#ifndef _CLSID_H
#define _CLSID_H

#pragma once

//***** CLASS ID type
/*#ifdef DEBUG
#include <string>
struct CLASS_ID
{
    u64 id;
    std::string name;

    CLASS_ID()
    {
        id = 0;
        name = "";
    }

    CLASS_ID(u64 id)
    {
        this->id = id;
        name.reserve(9);
        name[8] = 0;
        for (int i = 7; i >= 0; i--)
        {
            name[i] = char(id & 0xff);
        	id >>= 8;
        }
    }

    CLASS_ID(u64 id, LPCSTR name)
    {
        this->id = id;
        this->name = name;
    }

    CLASS_ID(char a, char b, char c, char d, char e, char f, char g, char h)
    {
        this->id = u64((u64(a) << u64(56)) | (u64(b) << u64(48)) | (u64(c) << u64(40)) | (u64(d) << u64(32)) | (u64(e) << u64(24)) | (u64(f) << u64(16)) | (u64(g) << u64(8)) | (u64(h)));
        this->name = name;
    }

    CLASS_ID& operator=(const CLASS_ID& other)
    {
        id = other.id;
        name = other.name;
        return *this;
    }

    bool operator==(const CLASS_ID& other) const
    {
        return id == other.id;
    }

    bool operator!=(const CLASS_ID& other) const
    {
        return id != other.id;
    }

    bool operator<(const CLASS_ID& other) const
    {
        return id < other.id;
    }

    bool operator>(const CLASS_ID& other) const
    {
        return id > other.id;
    }

    bool operator<=(const CLASS_ID& other) const
    {
        return id <= other.id;
    }

    bool operator>=(const CLASS_ID& other) const
    {
        return id >= other.id;
    }

};
#define MK_CLSID(a,b,c,d,e,f,g,h) \
		CLASS_ID(a,b,c,d,e,f,g,h)
    	
#define MK_CLSID_INV(a,b,c,d,e,f,g,h) MK_CLSID(h,g,f,e,d,c,b,a)
#else*/
typedef u64		CLASS_ID;
#define MK_CLSID(a,b,c,d,e,f,g,h) \
    	CLASS_ID((CLASS_ID(a)<<CLASS_ID(56))|(CLASS_ID(b)<<CLASS_ID(48))|(CLASS_ID(c)<<CLASS_ID(40))|(CLASS_ID(d)<<CLASS_ID(32))|(CLASS_ID(e)<<CLASS_ID(24))|(CLASS_ID(f)<<CLASS_ID(16))|(CLASS_ID(g)<<CLASS_ID(8))|(CLASS_ID(h)))

#define MK_CLSID_INV(a,b,c,d,e,f,g,h) MK_CLSID(h,g,f,e,d,c,b,a)
//#endif

extern XRCORE_API void		__stdcall CLSID2TEXT(CLASS_ID id, LPSTR text);
extern XRCORE_API CLASS_ID	__stdcall TEXT2CLSID(LPCSTR text);

#endif
