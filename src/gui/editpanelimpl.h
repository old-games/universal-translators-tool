/***************************************************************
 * Name:      editpanelimpl.h
 * Purpose:   ImageEditor declaration
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-29
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef EDITPANELIMPL_H_INCLUDED
#define EDITPANELIMPL_H_INCLUDED


#include "uttpanelsgui.h"
#include "types/ieditor.h"

class EditPanel;
class ImageInfo;
class PaletteHolderCtrl;

enum ImageEditorMode
{
	iemFullMode,
	iemChildMode
};

class ImageEditor: public EditPanelGui, public IEditor
{
public:
	ImageEditor( wxWindow* parent, ImageEditorMode mode, wxWindowID eventsId = wxID_ANY);
	~ImageEditor(void);

	void SetBitmap( wxBitmap* bitmap );

	EditPanel* GetEditPanel()
	{
		return mEditPanel;
	}

	void SetEditPanel( EditPanel* editPanel );
	void ChangeImagePalette( PalettePtr pal );
	
	// from IEditor
	virtual bool SaveEditor();
	virtual bool LoadEditor();

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	virtual OriginPtr GetOrigin() const override;
	virtual void SetInfo(IInfoPtr info) override;

protected:

	virtual void OnCommandEvent( wxCommandEvent& event );
	//virtual void OnImageChangeEvent( ChangeImageEvent& event );
	virtual void OnRebuildDataEvent( EditorRebuildDataEvent& event );

private:

	void ClearImage( bool force = false );
	void UpdateImage();

	bool CheckChanges();
	void SetGridEnabled();
	void SetGridMode();
	void SetGridColour();
	void SetPaletteAsMain();

	EditPanel*			mEditPanel;
	PaletteHolderCtrl*	mPalettePanel;
	ImageEditorMode		mMode;
};

#endif
