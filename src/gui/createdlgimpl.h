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

#include "simplegui.h"

class CreateProjectDlg : public CreateProjectGui
{
public:
	CreateProjectDlg();
	~CreateProjectDlg(void);

	wxString GetPath() const;
	wxString GetModule() const;
	wxString GetVersion() const;
	bool IsReady() const { return mReady; }

private:

	virtual void OnModuleChanged( wxCommandEvent& event );

	void Init();
	void UpdateVersionsCombo();

	bool mReady;
};

#endif	// CREATEDIALOGIMPL_H_INCLUDED