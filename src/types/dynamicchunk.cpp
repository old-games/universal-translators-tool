/***************************************************************
 * Name:      dynamicchunk.cpp
 * Purpose:   DynamicChunk
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/


#include "pch.h"
#include "dynamicchunk.h"



DynamicChunk::DynamicChunk(const DynamicChunk& other):
	mSizeDependies(other.mSizeDependies)
{
	for (auto val: other.mValues)
	{
		auto copy = val->Clone();
		mValues.push_back(copy);
		mValMap[copy->GetName()] = copy;
	}
}



void DynamicChunk::AddValue(const std::string& name, DataType type)
{
	AddValueInternal(name, type, doLITTLE_ENDIAN);
}



void DynamicChunk::AddBEValue(const std::string& name, DataType type)
{
	AddValueInternal(name, type, doBIG_ENDIAN);
}



void DynamicChunk::AddValueInternal(const std::string& name,
	DataType type, DataOrder order)
{
	IDataValue::Ptr val;

	switch (type)
	{
		case DataType::dtBYTE:
			val = std::make_shared<ByteData>(name, order);
		break;

		case DataType::dtWORD:
			val = std::make_shared<WordData>(name, order);
		break;

		case DataType::dtDWORD:
			val = std::make_shared<DWordData>(name, order);
		break;

		case DataType::dtCHAR:
			val = std::make_shared<CharData>(name, order);
		break;

		case DataType::dtSHORT:
			val = std::make_shared<ShortData>(name, order);
		break;

		case DataType::dtLONG:
			val = std::make_shared<LongData>(name, order);
		break;
		
		default:
			wxLogError("DynamicChunk::AddValue error: unknown data type %d", type);
	}

	if (val)
	{
		mValues.push_back(val);
		mValMap[name] = val;
	}
}



void DynamicChunk::AddCustomValue(const std::string& name, size_t size)
{
	IDataValue::Ptr val = std::make_shared<CustomData>(name, size);
	mValues.push_back(val);
	mValMap[name] = val;
}



void DynamicChunk::SetSizeDependcy(const std::string& customData,
		const std::string& sizeVar)
{
	mSizeDependies[customData] = sizeVar;
}



int DynamicChunk::LuaGetValue(const std::string& name) const
{
	auto it = mValMap.find(name);

	if (it == mValMap.end())
	{
		wxLogError("DynamicChunk::LuaGetValue error: %s not found!", name.c_str());
		return 0;
	}

	return it->second->LuaGetValue();
}



int DynamicChunk::GetIntValue(const std::string& name) const
{
	return GetValue<int>(name);
}



unsigned int DynamicChunk::GetUnsignedIntValue(const std::string& name) const
{
	return GetValue<unsigned int>(name);
}




template<typename T>
T DynamicChunk::GetValue(const std::string& name) const
{
	auto it = mValMap.find(name);
	T res = (T) -1;

	if (it == mValMap.end())
	{
		wxLogError("DynamicChunk::GetValue error: %s not found!", name.c_str());
		return res;
	}

	auto val = it->second;

	switch (val->GetType())
	{
		case DataType::dtBYTE:
			res = std::static_pointer_cast<ByteData>(val)->GetValue();
		break;

		case DataType::dtWORD:
			res = std::static_pointer_cast<WordData>(val)->GetValue();
		break;

		case DataType::dtDWORD:
			res = std::static_pointer_cast<DWordData>(val)->GetValue();
		break;

		case DataType::dtCHAR:
			res = std::static_pointer_cast<CharData>(val)->GetValue();
		break;

		case DataType::dtSHORT:
			res = std::static_pointer_cast<ShortData>(val)->GetValue();
		break;

		case DataType::dtLONG:
			res = std::static_pointer_cast<LongData>(val)->GetValue();
		break;

		default:
			wxLogError("DynamicChunk::GetValue error: can't get %s as integer!", name.c_str());
	}

	return res;
}



void DynamicChunk::CheckDependcy(IDataValue::Ptr val)
{
	wxASSERT(val->GetType() == DataType::dtCUSTOM);
	auto it = mSizeDependies.find(val->GetName());

	if (it == mSizeDependies.end())
	{
		return;
	}

	auto data = std::static_pointer_cast<CustomData>(val);
	unsigned size = GetUnsignedIntValue(it->second);

	if (size != (unsigned) -1)
	{
		data->SetSize(size);
	}
}



bool DynamicChunk::Load(wxInputStream& input)
{
	for (auto val: mValues)
	{
		if (val->GetType() == DataType::dtCUSTOM)
		{
			CheckDependcy(val);
		}

		if (!val->Load(input))
		{
			return false;
		}
	}

	return true;
}



bool DynamicChunk::Save(wxOutputStream& output)
{
	for (auto val: mValues)
	{
		if (!val->Save(output))
		{
			return false;
		}
	}

	return true;
}



size_t DynamicChunk::GetDynamicStructSize() const
{
	size_t res = 0;

	for (auto val: mValues)
	{
		res += val->GetSize();
	}

	return res;
}

