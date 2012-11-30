/***************************************************************
 * Name:      istatestore.h
 * Purpose:	  Interface class to save and load state of child
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-30
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef ISTATESTORE_H_INCLUDED
#define ISTATESTORE_H_INCLUDED



class IStateStore
{

public:

	IStateStore( const wxString& myName, int version );

	bool SaveToFile( const wxString& fileName );
	bool LoadFromFile( const wxString& fileName );

	bool SaveToStream( wxOutputStream& output);
	bool LoadFromStream( wxInputStream& input );

	inline static bool CheckLastWrite(wxOutputStream& output, size_t val)
	{
		return output.LastWrite() == val;
	}

	inline static bool CheckLastRead(wxInputStream& input, size_t val)
	{
		return input.LastRead() == val;
	}

	template<typename T>
	static bool SaveSimpleType(wxOutputStream& output, const T val)
	{
		output.Write(&val, sizeof(T));
		return CheckLastWrite(output, sizeof(T));
	}

	template<typename T>
	static bool LoadSimpleType(wxInputStream& input, T& val)
	{
		input.Read(&val, sizeof(T));
		return CheckLastRead(input, sizeof(T));
	}

	static bool SaveString(wxOutputStream& output, const wxString& txt);
	static bool LoadString(wxInputStream& input, wxString& txt);

	static bool SaveData(wxOutputStream& output, const void* src, size_t size);
	static bool LoadData(wxInputStream& input, void* dest, size_t size);

protected:

	virtual bool SaveState( wxOutputStream& output ) = 0;
	virtual bool LoadState( wxInputStream& input, int version ) = 0;

	wxString	mMyName;
	wxInt32		mVersion;


private:

	bool RenameTemporary( const wxString& fileName );

	wxString	mMyTemporary;
};



#endif	// ISTATESTORE_H_INCLUDED
