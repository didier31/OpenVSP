//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//////////////////////////////////////////////////////////////////////

#include "MassPropScreen.h"

#include <intl.h>

MassPropScreen::MassPropScreen( ScreenMgr *mgr ) : BasicScreen( mgr, 300, 410, _("Mass Properties") )
{
    int borderPaddingWidth = 5;
    int yPadding = 7;
    int smallButtonWidth = 100;
    int largeButtonWidth = 200;
    int smallGap = 25;

    m_FLTK_Window->callback( staticCloseCB, this );

    m_MainLayout.SetGroupAndScreen( m_FLTK_Window, this );

    m_SelectedSetIndex = DEFAULT_SET;

    m_MainLayout.ForceNewLine();
    m_MainLayout.AddY( yPadding );
    m_MainLayout.AddX( borderPaddingWidth );

    m_MainLayout.AddSubGroupLayout( m_BorderLayout, m_MainLayout.GetRemainX() - borderPaddingWidth,
                                        m_MainLayout.GetRemainY() - borderPaddingWidth );

    m_BorderLayout.SetButtonWidth( smallButtonWidth );
    m_BorderLayout.AddSlider( m_NumSlicesInput, _("Num Slice:"), 200, "%6.0f" );
    m_BorderLayout.AddYGap();

    m_BorderLayout.AddChoice( m_SetChoice, _("Set") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.AddButton( m_ComputeButton, _("Compute") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.AddButton( m_DrawCgButton, _("Draw Cg") );

    m_BorderLayout.AddYGap();
    m_BorderLayout.AddDividerBox( "Results" );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_TotalMassOutput, _("Total Mass") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_XCgOutput, _("X Cg") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_YCgOutput, _("Y Cg") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_ZCgOutput, _("Z Cg") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IxxOutput, _("I xx") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IyyOutput, _("I yy") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IzzOutput, _("I zz") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IxyOutput, _("I xy") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IxzOutput, _("I xz") );

    m_BorderLayout.SetButtonWidth( largeButtonWidth );
    m_BorderLayout.AddOutput( m_IyzOutput, _("I yz") );
    m_BorderLayout.AddYGap();

    m_BorderLayout.SetFitWidthFlag( true );
    m_BorderLayout.SetSameLineFlag( false );

    m_BorderLayout.AddDividerBox( _("File Export") );

    m_BorderLayout.SetSameLineFlag( true );
    m_BorderLayout.SetFitWidthFlag( true );

    m_BorderLayout.SetButtonWidth( 0 );
    m_BorderLayout.AddOutput( m_FileSelect, "", smallGap );

    m_BorderLayout.SetFitWidthFlag( false );
    m_BorderLayout.SetButtonWidth( smallGap );
    m_BorderLayout.AddButton( m_FileTrigger, "..." );
}

bool MassPropScreen::Update()
{
    assert( m_ScreenMgr );
    Vehicle* veh = m_ScreenMgr->GetVehiclePtr();

    LoadSetChoice();

    m_NumSlicesInput.Update( veh->m_NumMassSlices.GetID() );

    m_DrawCgButton.Update( veh->m_DrawCgFlag.GetID() );

    m_CGDrawObj.m_PntVec.clear();
    if ( veh->m_DrawCgFlag.Get() )
    {
        m_CGDrawObj.m_Visible = true;
        m_CGDrawObj.m_PntVec.push_back( veh->m_CG );
    }
    else
    {
        m_CGDrawObj.m_Visible = false;
    }

    char str[255];
    char format[10] = " %6.3f";

    //Total Mass
    sprintf( str, format, veh->m_TotalMass );
    m_TotalMassOutput.Update( str );
    //X Cg
    vec3d cg = veh->m_CG;
    sprintf( str, format, cg.x() );
    m_XCgOutput.Update( str );
    //Y Cg
    sprintf( str, format, cg.y() );
    m_YCgOutput.Update( str );
    //Z Cg
    sprintf( str, format, cg.z() );
    m_ZCgOutput.Update( str );
    //I xx
    vec3d moi = veh->m_IxxIyyIzz;
    sprintf( str, format, moi.x() );
    m_IxxOutput.Update( str );
    //I yy
    sprintf( str, format, moi.y() );
    m_IyyOutput.Update( str );
    //I zz
    sprintf( str, format, moi.z() );
    m_IzzOutput.Update( str );
    //I xy
    vec3d pmoi = veh->m_IxyIxzIyz;
    sprintf( str, format, pmoi.x() );
    m_IxyOutput.Update( str );
    //I xz
    sprintf( str, format, pmoi.y() );
    m_IxzOutput.Update( str );
    //I yz
    sprintf( str, format, pmoi.z() );
    m_IyzOutput.Update( str );

    m_FileSelect.Update( veh->getExportFileName( vsp::MASS_PROP_TXT_TYPE ).c_str() );

    return true;
}

void MassPropScreen::Show()
{
    m_ScreenMgr->SetUpdateFlag( true );
    m_FLTK_Window->show();
}

void MassPropScreen::Hide()
{
    m_FLTK_Window->hide();
    m_ScreenMgr->SetUpdateFlag( true );
}

void MassPropScreen::LoadSetChoice()
{
    m_SetChoice.ClearItems();

    assert( m_ScreenMgr );
    Vehicle* veh = m_ScreenMgr->GetVehiclePtr();
    vector< string > set_name_vec = veh->GetSetNameVec();

    for ( int i = 0 ; i < ( int )set_name_vec.size() ; ++i )
    {
        m_SetChoice.AddItem( set_name_vec[i].c_str() );
    }

    m_SetChoice.UpdateItems();
    m_SetChoice.SetVal( m_SelectedSetIndex );
}

void MassPropScreen::GuiDeviceCallBack( GuiDevice* device )
{
    assert( m_ScreenMgr );

    Vehicle* veh = m_ScreenMgr->GetVehiclePtr();

    if ( device == &m_SetChoice )
    {
        m_SelectedSetIndex = m_SetChoice.GetVal();
    }
    else if ( device == &m_ComputeButton )
    {
        veh->MassPropsAndFlatten( m_SelectedSetIndex, veh->m_NumMassSlices.Get() );
    }
    else if ( device == &m_FileTrigger )
    {
        veh->setExportFileName( vsp::MASS_PROP_TXT_TYPE,
                                       m_ScreenMgr->GetSelectFileScreen()->FileChooser(
                                               "Select Mass Prop output file.", "*.txt" ) );
    }

    m_ScreenMgr->SetUpdateFlag( true );
}


void MassPropScreen::CallBack( Fl_Widget* w )
{
     assert( m_ScreenMgr );

    m_ScreenMgr->SetUpdateFlag( true );
}

void MassPropScreen::CloseCallBack( Fl_Widget* w )
{
    Hide();
}

void MassPropScreen::LoadDrawObjs( vector< DrawObj* >& draw_obj_vec )
{
    if ( IsShown() )
    {
        draw_obj_vec.push_back( &m_CGDrawObj );
    }
}