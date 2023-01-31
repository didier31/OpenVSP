//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//
//////////////////////////////////////////////////////////////////////

#include "WireScreen.h"
#include "WireGeom.h"
#include "ScreenMgr.h"


//==== Constructor ====//
WireScreen::WireScreen( ScreenMgr* mgr ) : GeomScreen( mgr, 300, 525, _("Wireframe") )
{

    RemoveTab( GetTab( m_SubSurfTab_ind ) );

    Fl_Group* wire_tab = AddTab( "WireFrame" );
    Fl_Group* wire_group = AddSubGroup( wire_tab, 5 );

    m_WireLayout.SetGroupAndScreen( wire_group, this );

    m_WireLayout.AddDividerBox( _("Wireframe Characteristics") );

    m_TypeChoice.AddItem( _("Lifting") );
    m_TypeChoice.AddItem( _("Non-Lifting") );
    m_WireLayout.AddChoice( m_TypeChoice, _("Type") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( _("Normal Vector") );
    m_WireLayout.AddButton( m_InvertButton, _("Invert") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( _("Swap Point Ordering") );
    m_WireLayout.AddButton( m_SwapIJButton, _("Swap I/J") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( "Reverse" );

    m_WireLayout.AddButton( m_RevIButton, _("Reverse I") );
    m_WireLayout.AddButton( m_RevJButton, _("Reverse J") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( _("Patch") );

    m_IStartPatchTypeChoice.AddItem( _("None") );
    m_IStartPatchTypeChoice.AddItem( _("Point") );
    m_IStartPatchTypeChoice.AddItem( _("Line") );
    m_IStartPatchTypeChoice.AddItem( _("Copy Opposite") );
    m_IStartPatchTypeChoice.AddItem( _("Halfway Opposite") );
    m_WireLayout.AddChoice( m_IStartPatchTypeChoice, _("I Start") );

    m_IEndPatchTypeChoice.AddItem( _("None") );
    m_IEndPatchTypeChoice.AddItem( _("Point") );
    m_IEndPatchTypeChoice.AddItem( _("Line") );
    m_IEndPatchTypeChoice.AddItem( _("Copy Opposite") );
    m_IEndPatchTypeChoice.AddItem( _("Halfway Opposite") );
    m_WireLayout.AddChoice( m_IEndPatchTypeChoice, _("I End") );

    m_JStartPatchTypeChoice.AddItem( _("None") );
    m_JStartPatchTypeChoice.AddItem( _("Point") );
    m_JStartPatchTypeChoice.AddItem( _("Line") );
    m_JStartPatchTypeChoice.AddItem( _("Copy Opposite") );
    m_JStartPatchTypeChoice.AddItem( _("Halfway Opposite") );
    m_WireLayout.AddChoice( m_JStartPatchTypeChoice, _("J Start") );

    m_JEndPatchTypeChoice.AddItem( _("None") );
    m_JEndPatchTypeChoice.AddItem( _("Point") );
    m_JEndPatchTypeChoice.AddItem( _("Line") );
    m_JEndPatchTypeChoice.AddItem( _("Copy Opposite") );
    m_JEndPatchTypeChoice.AddItem( _("Halfway Opposite") );
    m_WireLayout.AddChoice( m_JEndPatchTypeChoice, _("J End") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( _("Start/End Skip") );

    m_WireLayout.AddIndexSelector( m_ISkipStartIndexSelector, _("I Start Skip") );
    m_WireLayout.AddIndexSelector( m_ISkipEndIndexSelector, _("I End Skip") );
    m_WireLayout.AddIndexSelector( m_JSkipStartIndexSelector, _("J Start Skip") );
    m_WireLayout.AddIndexSelector( m_JSkipEndIndexSelector, _("J End Skip") );

    m_WireLayout.AddYGap();
    m_WireLayout.AddDividerBox( "Stride" );

    m_WireLayout.AddIndexSelector( m_IStrideIndexSelector, _("I Stride") );
    m_WireLayout.AddIndexSelector( m_JStrideIndexSelector, _("J Stride") );
}


//==== Show Blank Screen ====//
void WireScreen::Show()
{
    if ( Update() )
    {
        m_FLTK_Window->show();
    }
}

bool WireScreen::Update()
{
    assert( m_ScreenMgr );

    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != WIRE_FRAME_GEOM_TYPE )
    {
        Hide();
        return false;
    }

    GeomScreen::Update();

    //==== Update Point Cloud Specific Parms ====//
    WireGeom* wire_geom_ptr = dynamic_cast< WireGeom* >( geom_ptr );
    assert( wire_geom_ptr );

    m_TypeChoice.Update( wire_geom_ptr->m_WireType.GetID() );
    m_InvertButton.Update( wire_geom_ptr->m_InvertFlag.GetID() );
    m_SwapIJButton.Update( wire_geom_ptr->m_SwapIJFlag.GetID() );
    m_RevIButton.Update( wire_geom_ptr->m_RevIFlag.GetID() );
    m_RevJButton.Update( wire_geom_ptr->m_RevJFlag.GetID() );

    m_ISkipStartIndexSelector.Update( wire_geom_ptr->m_ISkipStart.GetID() );
    m_ISkipEndIndexSelector.Update( wire_geom_ptr->m_ISkipEnd.GetID() );
    m_JSkipStartIndexSelector.Update( wire_geom_ptr->m_JSkipStart.GetID() );
    m_JSkipEndIndexSelector.Update( wire_geom_ptr->m_JSkipEnd.GetID() );

    m_IStrideIndexSelector.Update( wire_geom_ptr->m_IStride.GetID() );
    m_JStrideIndexSelector.Update( wire_geom_ptr->m_JStride.GetID() );

    m_IStartPatchTypeChoice.Update( wire_geom_ptr->m_IStartPatchType.GetID() );
    m_IEndPatchTypeChoice.Update( wire_geom_ptr->m_IEndPatchType.GetID() );
    m_JStartPatchTypeChoice.Update( wire_geom_ptr->m_JStartPatchType.GetID() );
    m_JEndPatchTypeChoice.Update( wire_geom_ptr->m_JEndPatchType.GetID() );

    return true;
}

//==== Non Menu Callbacks ====//
void WireScreen::CallBack( Fl_Widget *w )
{
    GeomScreen::CallBack( w );
}
