/***************************************************************
 * Name:      createdlgimpl.cpp
 * Purpose:   Implementation of CreateProjectDlg class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-18
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/



#include "pch.h"
#include "createdlgimpl.h"
#include "luacontrol.h"



CreateProjectDlg::CreateProjectDlg():
	CreateProjectGui(NULL),
	mReady( false )
{
	Init();
}



CreateProjectDlg::~CreateProjectDlg(void)
{
}



void CreateProjectDlg::Init()
{
	wxArrayString modules;

	if ( !Lua::Get().call( "getAvailableModules" ) ||
		!Helpers::PullTableOfStrings( modules ) || 
		modules.size() == 0 )
	{
		Lua::ShowLastError();
		return;
	}

	mModulesCombo->Clear();
	mModulesCombo->Append( modules );
	mModulesCombo->SetSelection(0);

	UpdateVersionsCombo();

	mReady = true;
}



void CreateProjectDlg::UpdateVersionsCombo()
{
	wxArrayString versions;

	if ( Lua::Get().call( "getModuleVersions", GetModule().ToStdString() ) )
	{
		Helpers::PullTableOfStrings( versions );
	}

	mVersionsCombo->Clear();

	if (versions.size() > 0)
	{
		mVersionsCombo->Append( versions );
		mVersionsCombo->SetSelection(0);
	}

	mVersionsCombo->Enable(versions.size() > 0);
}



wxString CreateProjectDlg::GetPath() const
{
	return mFileDlg->GetPath();
}



wxString CreateProjectDlg::GetModule() const
{
	return mModulesCombo->GetValue();
}



wxString CreateProjectDlg::GetVersion() const
{
	return mVersionsCombo->GetValue();
}



wxString CreateProjectDlg::GetGamePath() const
{
	return mDirDlg->GetPath();
}



/* virtual */ void CreateProjectDlg::OnModuleChanged( wxCommandEvent& event ) 
{ 
	UpdateVersionsCombo();
	event.Skip(); 
}



/* virtual */ void CreateProjectDlg::OnProjectFileNameChanged( wxFileDirPickerEvent& event )
{
	if (mDirDlg->GetPath().IsEmpty() && mFileDlg->GetPath().length() > 2)
	{
		wxString path, name, ext;
		wxFileName::SplitPath( mFileDlg->GetPath(), &path, &name, &ext );
		mDirDlg->SetDirName( path );
	}

	event.Skip();
}



/* virtual */ void CreateProjectDlg::OnOKButtonClick( wxCommandEvent& event )
{
	wxString dir = mDirDlg->GetPath();

	if (dir.IsEmpty() || !wxFileName::DirExists( dir ))
	{
		wxLogError("Game's folder MUST be selected!");
		return;
	}

	if ( dir.Last() != wxFileName::GetPathSeparator( wxPATH_NATIVE ) )
	{
		dir += wxFileName::GetPathSeparator( wxPATH_NATIVE );
		mDirDlg->SetPath( dir );
	}
	event.Skip();
}

