/***************************************************************
 * Name:      fontsettingsimpl.h
 * Purpose:   FontSettingsGui implementation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-23
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef FONTSEETINGSIMPL_H_INCLUDED
#define FONTSEETINGSIMPL_H_INCLUDED



#include "uttdialogsgui.h"



class FontSettingsImpl :
	public FontSettingsGui
{
public:
	FontSettingsImpl( wxWindow* parent, FontInfoPtr finfo );
	~FontSettingsImpl(void);

protected:

	virtual void OnBtnClick( wxCommandEvent& event );
	virtual void OnSpinCtrl( wxSpinEvent& event );

private:

	bool ShowLetterCodes();
	void SetValuesToControls();
	void UpdateSpinRanges();

	FontInfoPtr		mFontInfo;

};

#endif
