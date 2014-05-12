/***************************************************************
 * Name:      symbolpanel.h
 * Purpose:   SymbolPanel has to be used to edit font symbol
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef SYMBOLPANEL_H_INCLUDED
#define SYMBOLPANEL_H_INCLUDED

#include "editpanel.h"

class ControlLine;
class FontInfo;

enum ControlLines
{
	clSymbolWidth,
	clSymbolHeight,
	clBaseLine,
	clCapLine,
	clLowLine,
	clNum
};

class SymbolPanel :
	public EditPanel
{
public:
	SymbolPanel( wxWindow* parent, wxWindowID eventsId = wxID_ANY );
	~SymbolPanel(void);

	void SetFontInfo( FontInfoPtr info, int symbolNumber );

protected:

	virtual void Render( wxDC& dc );
	virtual void SetShowParams();

	virtual bool MouseButton( int btn, bool up );
	virtual bool MouseModifiersButton( int modifier, int btn, bool up );
	virtual bool MouseMoving( int modifier, int btn );

private:

	void SyncronizeValues();
	void UpdateBitmap();
	void UpdateControlLines();
	bool CheckControlLines();
	bool BeginDragLine();
	bool DragLine();
	void EndDragLine();

	FontInfoPtr		mFontInfo;
	bool			mAllowEdit;
	int				mSymbolNumber;
	int				mActiveLine;
	bool			mDragLine;
	wxPoint			mDragPoint;
	ControlLine*	mLines[ clNum ];
};

#endif
