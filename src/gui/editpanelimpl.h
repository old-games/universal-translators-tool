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

class ImageEditor:
	public EditPanelGui
{
public:
	ImageEditor( wxWindow* parent );
	~ImageEditor(void);

	void SetBitmap( wxBitmap* bitmap );

	EditPanel* GetEditPanel()
	{
		return mEditPanel;
	}

	void SetEditPanel( EditPanel* editPanel );

protected:

	virtual void OnCommandEvent( wxCommandEvent& event );
	virtual void OnImageChangeEvent( ChangeImageEvent& event );

private:

	void SetImage( ImageInfo* newImage );
	void ClearImage( bool force = false );
	void UpdateImage();

	bool CheckChanges();
	void SetGridEnabled();
	void SetGridMode();
	void SetGridColour();

	EditPanel*	mEditPanel;
	ImageInfo*	mImageInfo;
};

#endif
