/***************************************************************
 * Name:      dynamicchunk.h
 * Purpose:   class to support unknown FLIC (or not FLIC) chunks
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/



#ifndef __DYNAMIC_CHUNK_H__
#define __DYNAMIC_CHUNK_H__


#include "luacontrol.h"


enum class DataType : char
{
	dtBYTE,		// unsigned char	(1 byte)
	dtCHAR,		// char				(1 byte)
	dtWORD,		// unsigned short	(2 bytes)
	dtSHORT,	// short			(2 bytes)
	dtDWORD,	// unsigned int		(4 bytes)
	dtLONG,		// int				(4 bytes)
	dtCUSTOM
};


enum DataOrder : char
{
	doLITTLE_ENDIAN,
	doBIG_ENDIAN
};


class IDataValue
{
public:
	typedef std::shared_ptr<IDataValue> Ptr;

	IDataValue() = delete;
	IDataValue(const std::string& name, DataType type,
		DataOrder order = doLITTLE_ENDIAN):
			mName(name),
			mType(type),
			mOrder(order)
	{
	}

	IDataValue(const IDataValue& other):
		mName(other.mName),
		mType(other.mType)
	{
	}

	virtual ~IDataValue() = default;

	virtual Ptr Clone() const = 0;

	virtual bool Load(wxInputStream& input) = 0;
	virtual bool Save(wxOutputStream& output) = 0;

	inline DataType GetType() const { return mType; }
	inline const std::string& GetName() const { return mName; }
	inline DataOrder GetEndian() const { return mOrder; }

	virtual int LuaGetValue() const = 0;
	virtual size_t GetSize() const = 0;


	void SetEndian(DataOrder order) { mOrder = order; }

protected:
	
	virtual void SwapEndian() {}

	std::string		mName;
	DataType		mType;
	DataOrder		mOrder = doLITTLE_ENDIAN;
};



template<typename T, DataType DTYPE>
class DataValue: public IDataValue
{
public:
	DataValue(const std::string& name, DataOrder order):
		IDataValue(name, DTYPE, order)
	{}

	DataValue(const std::string& name, T& value):
		IDataValue(name, DTYPE),
		mValue(value)
	{}

	DataValue(const DataValue<T, DTYPE>& other):
		IDataValue(other),
		mValue(other.mValue)
	{}

	virtual Ptr Clone() const
	{
		return std::make_shared<DataValue<T, DTYPE>>(*this);
	}

	virtual bool Load(wxInputStream& input) override
	{
		bool res = IStateStore::LoadSimpleType(input, mValue);

		if (res)
		{
			SwapEndian();
		}

		return res;
	}

	virtual bool Save(wxOutputStream& output) override
	{
		SwapEndian();
		bool res = IStateStore::SaveSimpleType(output, mValue);
		SwapEndian();
		return res;
	}

	virtual int LuaGetValue() const override
	{
		OOLUA::push(Lua::Get(), mValue);
		return 1;
	}

	T GetValue() const { return mValue; }
	virtual size_t GetSize() const override { return sizeof(T); }


private:

	virtual void SwapEndian() override
	{
		switch (wxBYTE_ORDER)
		{
			case wxLITTLE_ENDIAN:
				if (mOrder != doLITTLE_ENDIAN)
				{
					Helpers::AutoSwapEndian(mValue);
				}
			break;

			case wxBIG_ENDIAN:
				if (mOrder != doBIG_ENDIAN)
				{
					Helpers::AutoSwapEndian(mValue);
				}
			break;
		}
	}

	T	mValue;
};



template<>
class DataValue<void, DataType::dtCUSTOM>: public IDataValue
{
public:
	DataValue(const std::string& name, size_t size):
		IDataValue(name, DataType::dtCUSTOM),
		mSize(size),
		mBuffer()
	{}

	DataValue(const DataValue<void, DataType::dtCUSTOM>& other):
		IDataValue(other),
		mSize(other.mSize)
	{
		if (other.mBuffer)
		{
			InitBuffer();
			memcpy(mBuffer, other.mBuffer, mSize);
		}
	}

	~DataValue()
	{
		free(mBuffer);
	}

	virtual Ptr Clone() const
	{
		return std::make_shared<DataValue<void, DataType::dtCUSTOM>>(*this);
	}

	virtual bool Load(wxInputStream& input) override
	{
		InitBuffer();
		return IStateStore::LoadData(input, mBuffer, mSize);
	}

	virtual bool Save(wxOutputStream& output) override
	{
		return IStateStore::SaveData(output, mBuffer, mSize);
	}

	void SetSize(size_t size)
	{
		mSize = size;
		InitBuffer(true);
	}

	virtual int LuaGetValue() const override
	{
		if (!mBuffer)
		{
			wxLogError("Can't get value from CUSTOM chunk - there is no data!");
			return 0;
		}

		lua_pushlstring(Lua::Get(), (const char*) mBuffer, mSize);
		return 1;
	}

	const void* GetValue() const { return mBuffer; }
	virtual size_t GetSize() const override { return mSize; }

private:

	void InitBuffer(bool reinit = false)
	{
		if (mBuffer)
		{
			if (!reinit)
			{
				return;
			}

			free(mBuffer);
		}

		mBuffer = malloc(mSize);
		memset(mBuffer, 0, mSize);
	}

	size_t		mSize = 0;
	void*		mBuffer = nullptr;
};

typedef DataValue<wxUint8, DataType::dtBYTE> ByteData;
typedef DataValue<wxUint16, DataType::dtWORD> WordData;
typedef DataValue<wxUint32, DataType::dtDWORD> DWordData;
typedef DataValue<wxInt8, DataType::dtCHAR> CharData;
typedef DataValue<wxInt16, DataType::dtSHORT> ShortData;
typedef DataValue<wxInt32, DataType::dtLONG> LongData;
typedef DataValue<void, DataType::dtCUSTOM> CustomData;



//////////////////////////////////////////////////////////////////////////
/// DynamicChunk



class DynamicChunk
{

	typedef std::list<IDataValue::Ptr> ValuesList;
	typedef std::map<std::string, IDataValue::Ptr> ValuesMap;
	typedef std::map<std::string, std::string> DependMap;

public:

	typedef std::shared_ptr<DynamicChunk> Ptr;

	DynamicChunk() = default;
	virtual ~DynamicChunk() = default;

	DynamicChunk(const DynamicChunk& other);

	Ptr Clone() const { return std::make_shared<DynamicChunk>(*this); }

	void AddValue(const std::string& name, DataType type);
	void AddBEValue(const std::string& name, DataType type);
	void AddCustomValue(const std::string& name, size_t size);
	void SetSizeDependcy(const std::string& customData,
		const std::string& sizeVar);

	bool Load(wxInputStream& input);
	bool Save(wxOutputStream& output);

	size_t GetDynamicStructSize() const;
	int LuaGetValue(const std::string& name) const;
	int GetIntValue(const std::string& name) const;
	unsigned int GetUnsignedIntValue(const std::string& name) const;

private:

	void AddValueInternal(const std::string& name, DataType type, DataOrder order);
	void CheckDependcy(IDataValue::Ptr val);

	template<typename T>
	T GetValue(const std::string& name) const;

	ValuesList	mValues;
	ValuesMap	mValMap;
	DependMap	mSizeDependies;
};



#endif // __DYNAMIC_CHUNK_H__
