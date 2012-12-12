/***************************************************************
 * Name:      buffer.h
 * Purpose:   declaration of Buffer class (was conceived to transfer data
 *			  between C++ and Lua VM, but std::string is enough)
 *
 * TODO:	  I think this class may be useful in future, if not - delete it
 *
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED




class Buffer
{
public:

	Buffer();
	Buffer( const std::string& src );

	// if ownData is true Buffer takes ownership over src pointer
	// if not - data will be copied
	Buffer( void* src, size_t size, bool ownData = true  );
	Buffer( const Buffer& other );
	virtual ~Buffer();

	Buffer* Clone() { return new Buffer(*this); }

	void Clear();
	bool IsOk() const { return mData != NULL; }

	void SetData( void* src, size_t size, bool ownData = true  );
	void SetData( const std::string& src );

	std::string GetBufferAsString();

	static Buffer BAD_BUFFER;
private:

	void*	mData;
	size_t	mSize;
	bool	mOwnData;
};

#endif // BUFFER_H_INCLUDED
