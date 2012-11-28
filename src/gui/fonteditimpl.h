/***************************************************************
 * Name:      mainframeimpl.h
 * Purpose:   FontEditGui implementation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-17
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef FONTEDITIMPL_H_INCLUDED
#define FONTEDITIMPL_H_INCLUDED

class FontInfo;
class FontEditGui;
class SymbolEditGui;
class SymbolPanel;

class FontEditor :
	public FontEditGui
{
public:
	FontEditor( wxWindow* parent );
	~FontEditor(void);

	void SetFont( FontInfo* newFont );

	bool CheckChanges();
	bool SaveFont();

	SymbolPanel* GetSymbolPanel();
	void SetCurrentSymbol(int n);

protected:

	virtual void OnBtnClick( wxCommandEvent& event );
	virtual void OnFontChangeEvent( ChangeFontEvent& event );
	virtual void OnSymbolSelection( SymbolSelectionEvent& event );
	virtual void OnRebuildDataEvent( EditorRebuildDataEvent& event );
private:

	bool ShowSettings();
	bool CreateFont();
	void ClearFont( bool force = false );	// force - to clear memory from destructor
	void ChangeFontPalette( Palette* pal );
	void SetPaletteAsMain();
	void UpdateFont();
	void UpdateRibbon();

	SymbolEditGui*	mSymbolEditor;
	FontInfo*		mCurrentFont;
	int				mCurrentSymbol;
	bool			mHasChanges;


};

#endif
