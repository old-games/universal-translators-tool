/***************************************************************
 * Name:      palwindowimpl.h
 * Purpose:   PaletteWindowGui implementation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef PALWDINWOIMPL_H_INCLUDED
#define PALWDINWOIMPL_H_INCLUDED


#include "simplegui.h"

// forward declarations
class PalettePanel;



class PaletteWindowImpl: public PaletteWindowGui
{
public:
	PaletteWindowImpl( wxWindow* parent );
	~PaletteWindowImpl(void);

	UttColour GetColour(bool right);

	void SetColour(bool right, const UttColour& colour);
	int	FindColour( bool right, const UttColour& colour, bool andSet = false );
	bool IsLocked() { return mLockCheck->IsChecked(); }
	void Lock( bool b = true );
	bool CheckLocked();

protected:
	virtual void OnCommandEvent( wxCommandEvent& event );
	virtual void OnSpinCtrl( wxSpinEvent& event );
	virtual void OnPaletteChangeEvent( ChangePaletteEvent& event );
	virtual void OnColourPickEvent( ColourPickEvent& event );	
private:

	void PaletteChanged();
	void SetSpinsBase();
	void OnPaint( wxPaintEvent& event );
	void PalTypeChanged();
	void UpdateColour(bool right);
	void UpdateSpin(bool right);
	void IndexChanged(bool right);
	void UpdateColours();
	void UpdateSpins();
	void SpinEnable(bool b = true);
	void LockChanged();

	PalettePanel*	mPalPanel;
	Palette*		mPalette;
};

#endif
