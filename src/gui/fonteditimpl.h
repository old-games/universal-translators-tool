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

class FontEditImpl :
	public FontEditGui
{
public:
	FontEditImpl( wxWindow* parent );
	~FontEditImpl(void);

	void SetFont( const FontInfo& newFont );

	bool CheckChanges();
	bool SaveFont();

	SymbolPanel* GetSymbolPanel();

protected:

	void Render(wxDC& dc);
	void OnPaint(wxPaintEvent& event);

	virtual void OnBtnClick( wxCommandEvent& event );
	virtual void OnFontChangeEvent( ChangeFontEvent& event );
private:

	bool ShowSettings();
	bool CreateFont();

	SymbolEditGui*	mSymbolEditor;
	FontInfo*		mCurrentFont;
	int				mCurrentSymbol;
	bool			mHasChanges;


};

#endif
