//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// IGESOptionsScreen.cpp: implementation of the IGESOptionsScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "IGESOptionsScreen.h"

#include <intl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IGESOptionsScreen::IGESOptionsScreen( ScreenMgr* mgr ) : BasicScreen( mgr, 250, 174 + 50 + 120 + 26, _("Untrimmed IGES Options") )
{
    m_FLTK_Window->callback( staticCloseCB, this );

    m_OkFlag = false;
    m_PrevUnit = 0;
    m_PrevSplit = false;
    m_PrevSplitSub = false;
    m_PrevCubic = false;
    m_PrevToCubicTol = 1e-6;
    m_PrevPropExportOrigin = false;

    m_PrevLabelID = true;
    m_PrevLabelName = true;
    m_PrevLabelSurfNo = true;
    m_PrevLabelSplitNo = true;
    m_PrevLabelDelim = vsp::DELIM_COMMA;

    m_GenLayout.SetGroupAndScreen( m_FLTK_Window, this );
    m_GenLayout.AddY( 25 );

    m_GenLayout.AddYGap();

    m_LenUnitChoice.AddItem( _("MM") );
    m_LenUnitChoice.AddItem( _("CM") );
    m_LenUnitChoice.AddItem( _("M") );
    m_LenUnitChoice.AddItem( _("IN") );
    m_LenUnitChoice.AddItem( _("FT") );
    m_GenLayout.AddChoice( m_LenUnitChoice, _("Length Unit") );
    m_GenLayout.AddYGap();

    m_GenLayout.AddButton( m_SplitSurfsToggle, _("Split Surfaces") );
    m_GenLayout.AddYGap();
    m_GenLayout.AddButton( m_SplitSubSurfsToggle, _("Split U/W-Const Sub-Surfaces") );
    m_GenLayout.AddYGap();
    m_GenLayout.AddButton( m_TrimTEToggle, _("Omit TE Surfaces") );
    m_GenLayout.AddYGap();
    m_GenLayout.AddButton( m_ToCubicToggle, _("Demote Surfs to Cubic") );
    m_GenLayout.AddSlider( m_ToCubicTolSlider, _("Tolerance"), 10, "%5.4g", 0, true );
    m_GenLayout.AddYGap();
    m_GenLayout.AddButton( m_PropExportOriginToggle, _("Export Props At Origin") );
    m_GenLayout.AddYGap();

    m_GenLayout.AddDividerBox( _("Surface Name") );
    m_GenLayout.AddButton( m_LabelIDToggle, _("Geom ID") );
    m_GenLayout.AddButton( m_LabelNameToggle, _("Geom Name") );
    m_GenLayout.AddButton( m_LabelSurfNoToggle, _("Surface Number") );
    m_GenLayout.AddButton( m_LabelSplitNoToggle, _("Split Number") );

    m_LabelDelimChoice.AddItem( _("Comma") );
    m_LabelDelimChoice.AddItem( _("Underscore") );
    m_LabelDelimChoice.AddItem( _("Space") );
    m_LabelDelimChoice.AddItem( _("None") );
    m_GenLayout.AddChoice( m_LabelDelimChoice, _("Delimiter") );

    m_GenLayout.AddY( 25 );
    m_GenLayout.SetFitWidthFlag( false );
    m_GenLayout.SetSameLineFlag( true );
    m_GenLayout.SetButtonWidth( 100 );

    m_GenLayout.AddX( 20 );
    m_GenLayout.AddButton( m_OkButton, _("OK") );
    m_GenLayout.AddX( 10 );
    m_GenLayout.AddButton( m_CancelButton, _("Cancel") );
    m_GenLayout.ForceNewLine();
}

IGESOptionsScreen::~IGESOptionsScreen()
{
}

bool IGESOptionsScreen::Update()
{
    Vehicle *veh = VehicleMgr.GetVehicle();

    if( veh )
    {
        m_LenUnitChoice.Update( veh->m_IGESLenUnit.GetID() );
        m_SplitSurfsToggle.Update( veh->m_IGESSplitSurfs.GetID() );
        m_SplitSubSurfsToggle.Update( veh->m_IGESSplitSubSurfs.GetID() );
        m_ToCubicToggle.Update( veh->m_IGESToCubic.GetID() );
        m_ToCubicTolSlider.Update( veh->m_IGESToCubicTol.GetID() );
        m_TrimTEToggle.Update( veh->m_IGESTrimTE.GetID() );
        m_PropExportOriginToggle.Update( veh->m_IGESExportPropMainSurf.GetID() );

        m_LabelIDToggle.Update( veh->m_IGESLabelID.GetID() );
        m_LabelNameToggle.Update( veh->m_IGESLabelName.GetID() );
        m_LabelSurfNoToggle.Update( veh->m_IGESLabelSurfNo.GetID() );
        m_LabelSplitNoToggle.Update( veh->m_IGESLabelSplitNo.GetID() );
        m_LabelDelimChoice.Update( veh->m_IGESLabelDelim.GetID() );

        if ( !veh->m_IGESToCubic() )
        {
            m_ToCubicTolSlider.Deactivate();
        }
    }

    m_FLTK_Window->redraw();

    return false;
}


void IGESOptionsScreen::Show()
{
    m_ScreenMgr->SetUpdateFlag( true );
    m_FLTK_Window->show();
}

void IGESOptionsScreen::CallBack( Fl_Widget* w )
{
    m_ScreenMgr->SetUpdateFlag( true );
}

void IGESOptionsScreen::GuiDeviceCallBack( GuiDevice* device )
{
    assert( m_ScreenMgr );

    if ( device == &m_OkButton )
    {
        m_OkFlag = true;
        Hide();
    }
    else if ( device == &m_CancelButton )
    {
        Vehicle *veh = VehicleMgr.GetVehicle();

        if( veh )
        {
            veh->m_IGESLenUnit.Set( m_PrevUnit );
            veh->m_IGESSplitSurfs.Set( m_PrevSplit );
            veh->m_IGESSplitSubSurfs.Set( m_PrevSplitSub );
            veh->m_IGESToCubic.Set( m_PrevCubic );
            veh->m_IGESToCubicTol.Set( m_PrevToCubicTol );
            veh->m_IGESTrimTE.Set( m_PrevTrimTE );
            veh->m_IGESExportPropMainSurf.Set( m_PrevPropExportOrigin );

            veh->m_IGESLabelID.Set( m_PrevLabelID );
            veh->m_IGESLabelName.Set( m_PrevLabelName );
            veh->m_IGESLabelSurfNo.Set( m_PrevLabelSurfNo );
            veh->m_IGESLabelSplitNo.Set( m_PrevLabelSplitNo );
            veh->m_IGESLabelDelim.Set( m_PrevLabelDelim );

        }
        Hide();
    }

    m_ScreenMgr->SetUpdateFlag( true );
}

bool IGESOptionsScreen::ShowIGESOptionsScreen()
{
    Show();

    m_OkFlag = false;

    Vehicle *veh = VehicleMgr.GetVehicle();

    if( veh )
    {
        m_PrevUnit = veh->m_IGESLenUnit();
        m_PrevSplit = veh->m_IGESSplitSurfs();
        m_PrevSplitSub = veh->m_IGESSplitSubSurfs();
        m_PrevCubic = veh->m_IGESToCubic();
        m_PrevToCubicTol = veh->m_IGESToCubicTol();
        m_PrevTrimTE = veh->m_IGESTrimTE();
        m_PrevPropExportOrigin = veh->m_IGESExportPropMainSurf();

        m_PrevLabelID = veh->m_IGESLabelID();
        m_PrevLabelName = veh->m_IGESLabelName();
        m_PrevLabelSurfNo = veh->m_IGESLabelSurfNo();
        m_PrevLabelSplitNo = veh->m_IGESLabelSplitNo();
        m_PrevLabelDelim = veh->m_IGESLabelDelim();
    }

    while( m_FLTK_Window->shown() )
    {
        Fl::wait();
    }

    return m_OkFlag;
}

void IGESOptionsScreen::CloseCallBack( Fl_Widget *w )
{
    assert( m_ScreenMgr );

    Vehicle *veh = VehicleMgr.GetVehicle();

    if( veh )
    {
        veh->m_IGESLenUnit.Set( m_PrevUnit );
        veh->m_IGESSplitSurfs.Set( m_PrevSplit );
        veh->m_IGESSplitSubSurfs.Set( m_PrevSplitSub );
        veh->m_IGESToCubic.Set( m_PrevCubic );
        veh->m_IGESToCubicTol.Set( m_PrevToCubicTol );
        veh->m_IGESTrimTE.Set( m_PrevTrimTE );
        veh->m_IGESExportPropMainSurf.Set( m_PrevPropExportOrigin );

        veh->m_IGESLabelID.Set( m_PrevLabelID );
        veh->m_IGESLabelName.Set( m_PrevLabelName );
        veh->m_IGESLabelSurfNo.Set( m_PrevLabelSurfNo );
        veh->m_IGESLabelSplitNo.Set( m_PrevLabelSplitNo );
        veh->m_IGESLabelDelim.Set( m_PrevLabelDelim );
    }

    Hide();
}
