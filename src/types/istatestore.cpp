/***************************************************************
 * Name:      istatestore.cpp
 * Purpose:	  Implementation of IStateStore
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-30
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/



#include "pch.h"
#include "istatestore.h"



const wxString TEMP_FILENAME = "__savestate_temp__";
#define SET_TEMPORARY wxString::Format( "%s%X.utemp", TEMP_FILENAME, (unsigned int) this )


IStateStore::IStateStore():
	mMyName( wxEmptyString ),
	mVersion( noFileHeader ),
	mMyTemporary(SET_TEMPORARY)
{
}



IStateStore::IStateStore(const wxString& myName, int version):
	mMyName( myName ),
	mVersion( version ),
	mMyTemporary(SET_TEMPORARY)
{
}



IStateStore::IStateStore( const IStateStore& other ):
	mMyName( other.mMyName ),
	mVersion( other.mVersion ),
	mMyTemporary( other.mMyTemporary )
{
}



/* virtual */ IStateStore::~IStateStore()
{

}



bool IStateStore::SaveToFile( const wxString& fileName )
{
	STOPWATCH_BEGIN;
	
	wxFileOutputStream stream( mMyTemporary );
	bool res = false;

	if (stream.IsOk())
	{
		wxBusyInfo info("Saving, please wait...");
		res = SaveToStream( stream );
		stream.Close();

		if (res)
		{
			res = this->RenameTemporary( fileName );
		}
	}
	else
	{
		wxLogError(wxString::Format("%s::SaveToFile: can't create temporary file (%s) to save data!", mMyName, mMyTemporary));
	}

	STOPWATCH_END(wxString("IStateStore::SaveToFile ").Append(fileName));
	return res;
}



bool IStateStore::LoadFromFile( const wxString& fileName, bool useMemory /* true */ )
{
	STOPWATCH_BEGIN;
	
	wxFileInputStream stream(fileName);
	bool res = false;
	void* block = NULL;
	
	if (stream.IsOk())
	{
		wxBusyInfo info("Loading, please wait...");

		if (useMemory)
		{
			size_t size = stream.GetSize();
			block = malloc(size);
			stream.Read( block, size );
			res = LoadFromStream( wxMemoryInputStream(block, size) );
		}
		else
		{
			res = LoadFromStream( stream );
		}

	}
	else
	{
		wxLogError(wxString::Format("%s::LoadFromFile: can't open file (%s) to read data!", mMyName, fileName));
	}

	if (block)
	{
		free(block);
	}

	STOPWATCH_END(wxString("IStateStore::LoadFromFile ").Append(fileName));
	return res;
}



bool IStateStore::SaveToStream( wxOutputStream& output)
{
	wxBusyCursor busy;

	bool res = false;

	if ( mVersion == noFileHeader || 
		(SaveString( output, mMyName ) && SaveSimpleType<wxInt32>( output, mVersion )) )
	{
		res = SaveState( output );
	}
	else
	{
		wxLogError(wxString::Format("%s::SaveToStream: can't write header data to stream!", mMyName));
	}

	return res;
}



bool IStateStore::LoadFromStream( wxInputStream& input )
{
	wxBusyCursor busy;

	wxString name = wxEmptyString;
	wxInt32 version = noFileHeader;

	// correct SkipHeader if the next line changing
	bool res = mVersion == noFileHeader ? true :
		LoadString( input, name ) && LoadSimpleType<wxInt32>( input, version );

	if ( res )
	{
		res = mMyName == name;
		if ( !res )
		{
			wxLogError(wxString::Format("%s::LoadFromStream: not expected header ID (%s)!", mMyName, name));
		}
		else
		{
			res = this->LoadState( input, version );
		}
	}
	else
	{
		wxLogError(wxString::Format("%s::LoadFromStream: can't read header data from stream!", mMyName));
	}

	return res;
}



/* static */ bool IStateStore::SkipHeader( wxInputStream& input )	// used by IEditor
{
	wxString str;
	wxInt32 ver;
	return LoadString( input, str ) && LoadSimpleType<wxInt32>( input, ver );
}



bool IStateStore::RenameTemporary( const wxString& fileName )
{
	bool res = ::wxRenameFile( mMyTemporary, fileName, true );

	if (!res)
	{
		wxLogError(wxString::Format("%s::RenameTemporary: can't rename temporary file (%s) to %s!", mMyName, mMyTemporary, fileName));
	}

	//else
	//{
	//	if (!::wxRemoveFile( mMyTemporary ))
	//	{
	//		wxLogWarning(wxString::Format("%s::RenameTemporary: temporary file (%s) renamed to %s, but deleting of tempfile was unsuccessful!", mMyName, mMyTemporary, fileName));
	//	}
	//}

	return res;
}



/* static */ bool IStateStore::SaveString(wxOutputStream& output, const wxString& txt)
{
	wxInt32 len = txt.Len();

	if ( SaveSimpleType<wxInt32>(output, len) )
	{
		len *= sizeof(wchar_t);
		output.Write(txt.c_str().AsWChar(), len );
		return CheckLastWrite(output, len);
	}
	return false;
}



/* static */ bool IStateStore::WriteLine(wxOutputStream& output, const wxString& txt)
{
	wxInt32 len = txt.Len();
	output.Write(txt.c_str(), len );
	bool ret = CheckLastWrite(output, len);
	
	if (ret)
	{
		output.Write("\r", 1); 
	}
	
	return ret;
}



/* static */ bool IStateStore::LoadString(wxInputStream& input, wxString& txt)
{
	wxInt32 len = 0;
	bool ret = LoadSimpleType<wxInt32>(input, len);

	if (ret)
	{
		len *=  sizeof(wchar_t);
		wchar_t* buf = (wchar_t*) malloc(len);
		input.Read(buf, len);
		if (CheckLastRead(input, len))
		{
			txt = wxString(buf, len / sizeof(wchar_t));
			ret = true;
		}
		free(buf);
	}

	return ret;
}



/* static */ bool IStateStore::SaveData(wxOutputStream& output, const void* src, size_t size)
{
	output.Write(src, size );
	return CheckLastWrite(output, size);
}



/* static */ bool IStateStore::LoadData(wxInputStream& input, void* dest, size_t size)
{
	input.Read(dest, size);
	return CheckLastRead(input, size);
}


