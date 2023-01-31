//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//////////////////////////////////////////////////////////////////////

#include "ImportScreen.h"
#include "ScreenMgr.h"

#include <intl.h>

using namespace vsp;

//==== Constructor ====//
ImportScreen::ImportScreen( ScreenMgr* mgr ) : BasicScreen( mgr , 200, 25 + 9*20 + 1*15 + 2*6, _("Import") )
{
    m_MainLayout.SetGroupAndScreen( m_FLTK_Window, this );
    m_MainLayout.AddX( 5 );
    m_MainLayout.AddY( 25 );
    m_MainLayout.AddSubGroupLayout( m_GenLayout, m_MainLayout.GetRemainX() - 5, m_MainLayout.GetRemainY() );

    m_GenLayout.SetChoiceButtonWidth( 50 );

    m_GenLayout.AddDividerBox( "File Format" );
    m_GenLayout.AddYGap();

    m_GenLayout.AddButton( m_TRIButton, "Cart3D (.tri)" );
    m_GenLayout.AddButton( m_STLButton, "Stereolith (.stl)" );
    m_GenLayout.AddButton( m_NASCARTButton, "NASCART (.dat)" );
    m_GenLayout.AddButton( m_XSecButton, _("XSec as Tri Mesh (.hrm)") );
    m_GenLayout.AddButton( m_XSecWireButton, _("XSec as Wireframe (.hrm)") );
    m_GenLayout.AddButton( m_PTSButton, _("Point Cloud (.pts)") );
    m_GenLayout.AddButton( m_V2Button, "OpenVSP v2 (.vsp)" );
    m_GenLayout.AddButton( m_BEMButton, _("Blade Element (.bem)") );
    m_GenLayout.AddButton( m_P3DWireButton, _("Plot3D as Wireframe (.p3d)") );

}

//==== Destructor ====//
ImportScreen::~ImportScreen()
{
}

//==== Import File ====//
void ImportScreen::ImportFile( string & in_file, int type )
{
    Vehicle *veh = VehicleMgr.GetVehicle();

    if ( type == IMPORT_STL )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import STL file?"), "*.stl" );
    }
    else if ( type == IMPORT_NASCART )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import NASCART file?"), "*.dat" );
    }
    else if ( type == IMPORT_CART3D_TRI )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import Cart3D Tri File?"), "*.tri" );
    }
    else if ( type == IMPORT_XSEC_MESH || type == IMPORT_XSEC_WIRE )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import XSec File?"), "*.hrm" );
    }
    else if ( type == IMPORT_PTS )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import Points File?"), "*.pts" );
    }
    else if ( type == IMPORT_V2 )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import OpenVSP v2 File?"), "*.vsp" );
    }
    else if ( type == IMPORT_BEM )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import Blade Element File?"), "*.bem" );
    }
    else if ( type == IMPORT_P3D_WIRE )
    {
        in_file = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Import Plot3D Unformatted File?"), "*.p3d" );
    }
    else
    {
        return;
    }

    if ( in_file.size() != 0 && in_file[ in_file.size() - 1] != '/' )
    {
        veh->ImportFile( in_file, type );
    }

    m_ScreenMgr->SetUpdateFlag( true );
}

//==== Callbacks ===//
void ImportScreen::CallBack( Fl_Widget *w )
{
    m_ScreenMgr->SetUpdateFlag( true );
}

void ImportScreen::GuiDeviceCallBack( GuiDevice* device )
{
    string in_file;

    if ( device == &m_STLButton )
    {
        ImportFile( in_file, IMPORT_STL );
    }
    else if ( device == &m_NASCARTButton )
    {
        ImportFile( in_file, IMPORT_NASCART );
    }
    else if ( device == &m_TRIButton )
    {
        ImportFile( in_file, IMPORT_CART3D_TRI );
    }
    else if ( device ==  &m_XSecButton )
    {
        ImportFile( in_file, IMPORT_XSEC_MESH );
    }
    else if ( device == &m_PTSButton )
    {
        ImportFile( in_file, IMPORT_PTS );
    }
    else if ( device == &m_V2Button )
    {
        ImportFile( in_file, IMPORT_V2 );
    }
    else if ( device == &m_BEMButton )
    {
        ImportFile( in_file, IMPORT_BEM );
    }
    else if ( device == &m_XSecWireButton )
    {
        ImportFile( in_file, IMPORT_XSEC_WIRE );
    }
    else if ( device == &m_P3DWireButton )
    {
        ImportFile( in_file, IMPORT_P3D_WIRE );
    }

    m_ScreenMgr->SetUpdateFlag( true );
}
