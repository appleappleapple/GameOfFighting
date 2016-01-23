#ifndef __ChineseString_H__  
#define __ChineseString_H__  
#include "iconv/iconv.h"//重点记得加上去
static char g_GBKConvUTF8Buf[5000] = {0};
class ChineseString
{
public:
	static const char* GBKToUTF8(const char *strChar)//将字符串转成UFT-8
	{
		iconv_t iconvH;
		iconvH = iconv_open("utf-8","gb2312");
		if (iconvH == 0)
		{
			return NULL;
		}
		size_t strLength = strlen(strChar);
		size_t outLength = strLength*4;
		size_t copyLength = outLength;
		memset(g_GBKConvUTF8Buf, 0, 5000);

		char* outbuf = (char*) malloc(outLength);
		char* pBuff = outbuf;
		memset(outbuf, 0, outLength);

		if (-1 == iconv(iconvH, &strChar, &strLength, &outbuf, &outLength))
		{
			iconv_close(iconvH);
			return NULL;
		}
		memcpy(g_GBKConvUTF8Buf,pBuff,copyLength);
		free(pBuff);
		iconv_close(iconvH);
		return g_GBKConvUTF8Buf;
	}
};
#endif  