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

class EditPanel;
class ImageInfo;
class PaletteHolderCtrl;

class ImageEditor: public EditPanelGui, public IEditor
{
public:
	ImageEditor( wxWindow* parent, wxWindowID eventsId = wxID_ANY);
	~ImageEditor(void);

	void SetBitmap( wxBitmap* bitmap );

	EditPanel* GetEditPanel()
	{
		return mEditPanel;
	}

	void SetEditPanel( EditPanel* editPanel );
	void ChangeImagePalette( Palette* pal );
	
	// from IEditor
	virtual bool SaveEditor();
	virtual bool LoadEditor();
	virtual bool SaveEditor( wxOutputStream& output );
	virtual bool LoadEditor( wxInputStream& input );
	virtual const Origin*	GetOrigin() const;
	virtual void SetInfo( IInfo* info );


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
};

#endif
