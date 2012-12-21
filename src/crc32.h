/***************************************************************
 * Name:      crc32.h
 * Purpose:   CRC32 calculating
 * Author:    Pavlovets Ilia (based on Gary S. Brown implementation)
 * Created:   2012-12-21 
 * Copyright: 
 * License:
 **************************************************************/

#ifndef CRC__H
#define CRC__H


namespace Helpers
{
	wxUint32 updateCRC32(unsigned char ch, wxUint32 crc);
	wxUint32 crc32buf(const char *buf, size_t len);
}


#endif /* CRC__H */