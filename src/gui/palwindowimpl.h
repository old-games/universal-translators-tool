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


// forward declarations
class PalettePanel;





class PaletteWindowImpl :
	public PaletteWindowGui
{
public:
	PaletteWindowImpl( wxWindow* parent );
	~PaletteWindowImpl(void);
	wxColour GetColour(bool right);
	void SetColour(bool right, const wxColour& colour);
	int	FindColour( bool right, const wxColour& colour, bool andSet = false );

protected:
	virtual void OnCommandEvent( wxCommandEvent& event );
	virtual void OnSpinCtrl( wxSpinEvent& event );
	virtual void OnPaletteChangeEvent( ChangePaletteEvent& event );

private:

	void OnPaint( wxPaintEvent& event );
	void OwnerChanged();
	void PalTypeChanged();
	void UpdateColour(bool right);
	void UpdateSpin(bool right);
	void UpdateColours();
	void UpdateSpins();
	void SpinEnable(bool b = true);

	PalettePanel*	mPalPanel;
	Palette*		mPalettes[PalOwners::poNum];
};

#endif
