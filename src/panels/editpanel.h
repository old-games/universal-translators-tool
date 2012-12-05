/***************************************************************
 * Name:      editpanel.h
 * Purpose:   modified DrawPanel for edit image
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-29
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef EDITPANEL_H_INCLUDED
#define EDITPANEL_H_INCLUDED

#include "drawpanel.h"


class PlacePixelCommand;
class ImageCopyPasteCommand;

class EditPanel: public DrawPanel
{

friend class ImageEditor;
friend class PlacePixelCommand;
friend class ImagePasteCommand;

public:

	EditPanel( wxWindow* parent );
	virtual ~EditPanel(void);

	void SetGridColour(const wxColour& color);
	const wxColour& GetGridColour()
	{
		return mGridColour;
	}

	void SetGridLogic(wxInt32 logic);

	void SetGridEnabled(bool b = true)
	{
		mDrawGrid = b;
	}

	void SetDrawFocus( bool b )
	{
		mDrawFocus = b;
	}

	void SetAllowEdit( bool b /* true */)
	{
		mAllowEdit = b;
	}

	static UttColour	gGlobalLeftColour;
	static UttColour	gGlobalRightColour;

protected:

	virtual bool MouseButton( int btn, bool up );
	virtual bool MouseModifiersButton( int modifier, int btn, bool up );
	virtual bool MouseMoving( int modifier, int btn );

	virtual bool KeyDown( int modifier, int keyCode );
	virtual bool KeyUp( int modifier, int keyCode );
	virtual bool CursorPressed( int directon );

	virtual void Render(wxDC& dc);
	virtual void SetShowParams();

	void DrawGrid( wxDC& dc );
	bool DoPlacePixel( const wxPoint& pos, const UttColour& color );
	bool DoPaste( const wxPoint& pos, const ImageInfo* img );
	bool GetPixel( const wxPoint& pos, UttColour& color );

	virtual	PlacePixelCommand*	CreatePlacePixelCommand();

	bool		mDrawing;
	bool		mDrawCursor;
	wxPoint     mCursor;				// coordinates of current pixel, must be always valid

private:

	void ClearGridPoints();
	bool CommandEdit();
	bool CommandPaste( const ImageInfo* newValue );
	bool BeginDrawing();
	void EndDrawing();
	bool PasteSelection();
	void SendRebuildDataEvent();


	bool		mDrawGrid;
	wxColour	mGridColour;
	wxPoint*	mGridPoints;
	wxInt32		mPointsNumber;
	wxPen		mGridPen;
	wxInt32		mGridLogic;

	UttColour	mCurrentColour;
	wxPoint		mPreviousPoint;
	bool		mAllowEdit;

};

#endif
