/***************************************************************
 * Name:      palholderctrl.h
 * Purpose:   Addititonal control for Font and Image editors
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef PALHOLDERCTRL_H_INCLUDED
#define PALHOLDERCTRL_H_INCLUDED

class PaletteWindowImpl;

class PaletteHolderCtrl: public PaletteHolderGui
{
public:
	PaletteHolderCtrl( wxWindow* parent );
	~PaletteHolderCtrl();


private:

	virtual void OnPalHideBtnClick( wxCommandEvent& event );
	void UpdateState();

	PaletteWindowImpl*	mPaletteCtrl;
};

#endif
