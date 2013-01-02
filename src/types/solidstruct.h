/***************************************************************
 * Name:      solidstruct.h
 * Purpose:   class to hold Lua defined structure
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2013-01-01
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef SOLIDSTRUCT_H_INCLUDED
#define SOLIDSTRUCT_H_INCLUDED


#define MAXIMUM_SOLID_ITEMS		128



class StructItem
{
public:

	enum StructItemType
	{
		siChar,
		siByte,
		siShort,
		siWord,
		siLong,
		siDWord,
		siString,
		siData,
		siUnknown
	};
	
	StructItem();
	StructItem(const StructItem& other);

	void SetValue(const wxString& name, size_t size, void* src );

	template<typename T> 
	T GetAs()
	{
		return static_cast<T>( *mValue );
	}	
	
	std::string GetAs()
	{
		return std::string( (char*) mValue, mSize );
	}
	
private:

	wxString	mName;
	size_t		mSize;
	void*		mValue;
	
};



class SolidStruct
{

public:
	SolidStruct();
	
	bool IsOk() const { return mData != NULL; }
	void Init( const char* srcBuf, size_t srcSize, size_t num );
	//void SetValue( const char* varName, )

private:

	void*			mData;
	size_t			mNum;
	StructItem		mValues[MAXIMUM_SOLID_ITEMS];

};

#endif // SOLIDSTRUCT_H_INCLUDED
