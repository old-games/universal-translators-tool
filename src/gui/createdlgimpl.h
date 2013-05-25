/***************************************************************
 * Name:      createdlgimpl.h
 * Purpose:   Dialog of creating new dialog
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-18
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef CREATEDIALOGIMPL_H_INCLUDED
#define CREATEDIALOGIMPL_H_INCLUDED

#include "uttdialogsgui.h"

class CreateProjectDlg : public CreateProjectGui
{
public:
	CreateProjectDlg();
	~CreateProjectDlg(void);

	wxString GetPath() const;
	wxString GetModule() const;
	wxString GetVersion() const;
	wxString GetGamePath() const;

	bool IsReady() const { return mReady; }

private:

	virtual void OnModuleChanged( wxCommandEvent& event );
	virtual void OnProjectFileNameChanged( wxFileDirPickerEvent& event );
	virtual void OnOKButtonClick( wxCommandEvent& event );

	void Init();
	void UpdateVersionsCombo();

	bool mReady;
};

#endif	// CREATEDIALOGIMPL_H_INCLUDED
