/***************************************************************
 * Name:      solidstruct.cpp
 * Purpose:   implementation of SolidStruct
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2013-01-01
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "solidstruct.h"


StructItem::StructItem(): 
	mName( wxEmptyString ), 
	mSize(0), 
	mValue(NULL) 
{
}



StructItem::StructItem(const StructItem& other): 
	mName(other.mName), 
	mSize(other.mSize),
	mValue(other.mValue)
{

}



void StructItem::SetValue(const wxString& name, size_t size, void* src )
{
	mName = name;
	mSize = size;
	mValue = src;
}