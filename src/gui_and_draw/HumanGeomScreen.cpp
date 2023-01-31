//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//
//////////////////////////////////////////////////////////////////////

#include "HumanGeomScreen.h"
#include "ScreenMgr.h"
#include "HumanGeom.h"

#include <intl.h>

//==== Constructor ====//
HumanGeomScreen::HumanGeomScreen( ScreenMgr* mgr ) : GeomScreen( mgr, 350, 615, _("Human") )
{
    Fl_Group* design_tab = AddTab( _("Anthropometric") );
    Fl_Group* design_group = AddSubGroup( design_tab, 5 );

    m_AnthropoLayout.SetGroupAndScreen( design_group, this );

    m_AnthropoLayout.AddDividerBox( _("Units") );

    m_LenUnitChoice.AddItem( "MM" );
    m_LenUnitChoice.AddItem( "CM" );
    m_LenUnitChoice.AddItem( "M" );
    m_LenUnitChoice.AddItem( "IN" );
    m_LenUnitChoice.AddItem( "FT" );
    m_LenUnitChoice.AddItem( "YD" );
    m_AnthropoLayout.AddChoice( m_LenUnitChoice, _("Length Unit") );

    m_MassUnitChoice.AddItem( "G" );
    m_MassUnitChoice.AddItem( "KG" );
    m_MassUnitChoice.AddItem( "TONNE" );
    m_MassUnitChoice.AddItem( "LBM" );
    m_MassUnitChoice.AddItem( "SLUG" );
    m_MassUnitChoice.AddItem( "LBFSEC2IN" );
    m_AnthropoLayout.AddChoice( m_MassUnitChoice, _("Mass Unit") );

    m_AnthropoLayout.AddYGap();
    m_AnthropoLayout.AddDividerBox( _("Anthropometric") );

    m_GenderChoice.AddItem( _("MALE") );
    m_GenderChoice.AddItem( _("FEMALE") );
    m_AnthropoLayout.AddChoice( m_GenderChoice, _("Gender") );
    m_AnthropoLayout.AddYGap();

    m_AnthropoLayout.AddSlider( m_StatureSlider, _("Stature"), 100, "%7.3f" );
    m_AnthropoLayout.AddSlider( m_StaturePctSlider, _("% Stature"), 1, "%7.3f" );
    m_AnthropoLayout.AddYGap();

    m_AnthropoLayout.AddSlider( m_BMISlider, _("BMI"), 10, "%7.3f" );
    m_AnthropoLayout.AddSlider( m_BMIPctSlider, _("% BMI"), 1, "%7.3f" );
    m_AnthropoLayout.AddSlider( m_MassSlider, _("Mass"), 100, "%7.3f" );

    m_AnthropoLayout.SetSameLineFlag( true );
    m_AnthropoLayout.AddOutput( m_VolumeOutput, _("Volume"), "%6.2f", 100 );
    m_AnthropoLayout.SetFitWidthFlag( false );
    m_AnthropoLayout.SetButtonWidth( 100 );
    m_AnthropoLayout.AddButton( m_AutoDensityToggle, _("Auto Density") );
    m_AnthropoLayout.InitWidthHeightVals();
    m_AnthropoLayout.ForceNewLine();
    m_AnthropoLayout.SetSameLineFlag( false );
    m_AnthropoLayout.SetFitWidthFlag( true );

    m_AnthropoLayout.AddYGap();

    m_AnthropoLayout.AddSlider( m_AgeSlider, _("Age"), 10, "%7.3f" );
    m_AnthropoLayout.AddYGap();

    m_AnthropoLayout.AddSlider( m_SitFracSlider, _("Sitting H / H"), 1.0, "%7.3f" );

    m_AnthropoLayout.AddYGap();

#ifdef SHOW_SHOW_SKEL_BUTTON
    m_AnthropoLayout.AddButton( m_ShowSkelButton, _("Show Skeleton") );
#endif

    Fl_Group* pose_tab = AddTab( _("Pose") );
    Fl_Group* pose_group = AddSubGroup( pose_tab, 5 );

    m_PoseLayout.SetGroupAndScreen( pose_group, this );
    m_PoseLayout.AddDividerBox( _("Pose") );

    m_PoseLayout.SetButtonWidth( m_PoseLayout.GetButtonWidth() + 25 );

    m_PresetPoseChoice.AddItem( _("STANDING") );
    m_PresetPoseChoice.AddItem( _("SITTING") );

    m_PoseLayout.SetChoiceButtonWidth( m_PoseLayout.GetButtonWidth() );

    m_PoseLayout.SetSameLineFlag( true );

    m_PoseLayout.AddChoice( m_PresetPoseChoice, _("Preset"), m_PoseLayout.GetButtonWidth() );

    m_PoseLayout.SetFitWidthFlag( false );
    m_PoseLayout.AddButton( m_SetPose, _("Set") );

    m_PoseLayout.ForceNewLine();
    m_PoseLayout.SetSameLineFlag( false );
    m_PoseLayout.SetFitWidthFlag( true );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( _("Body") );

    m_PoseLayout.AddSlider( m_BackSlider, _("Back"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_WaistSlider, _("Waist"), 100, "%7.3f" );

    int oldDH = m_PoseLayout.GetDividerHeight();
    m_PoseLayout.SetDividerHeight( m_PoseLayout.GetStdHeight() );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( _("Right Side") );

    m_PoseLayout.SetDividerHeight( oldDH );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( _("Arm") );




    m_PoseLayout.AddSlider( m_ShoulderABADRtSlider, _("Shoulder AB/AD"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ShoulderFERtSlider, _("Shoulder FE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ShoulderIERtSlider, _("Shoulder IE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ElbowRtSlider, _("Elbow"), 100, "%7.3f" );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( _("Leg") );

    m_PoseLayout.AddSlider( m_HipABADRtSlider, _("Hip AB/AD"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_HipFERtSlider, _("Hip FE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_KneeRtSlider, _("Knee"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_AnkleRtSlider, _("Ankle"), 100, "%7.3f" );


    m_PoseLayout.SetDividerHeight( m_PoseLayout.GetStdHeight() );

    m_PoseLayout.AddYGap();
    m_PoseLayout.SetSameLineFlag( true );
    m_PoseLayout.AddDividerBox( _("Left Side"), m_PoseLayout.GetButtonWidth() );
    m_PoseLayout.SetFitWidthFlag( false );
    m_PoseLayout.AddButton( m_RLSymButton, _("R/L Sym") );
    m_PoseLayout.ForceNewLine();
    m_PoseLayout.SetFitWidthFlag( true );
    m_PoseLayout.SetSameLineFlag( false );

    m_PoseLayout.SetDividerHeight( oldDH );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( "Arm" );

    m_PoseLayout.AddSlider( m_ShoulderABADLtSlider, _("Shoulder AB/AD"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ShoulderFELtSlider, _("Shoulder FE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ShoulderIELtSlider, _("Shoulder IE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_ElbowLtSlider, _("Elbow"), 100, "%7.3f" );

    m_PoseLayout.AddYGap();
    m_PoseLayout.AddDividerBox( "Leg" );

    m_PoseLayout.AddSlider( m_HipABADLtSlider, _("Hip AB/AD"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_HipFELtSlider, _("Hip FE"), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_KneeLtSlider, _("Knee "), 100, "%7.3f" );
    m_PoseLayout.AddSlider( m_AnkleLtSlider, _("Ankle"), 100, "%7.3f" );

}


//==== Show Ellipsoid Screen ====//
void HumanGeomScreen::Show()
{
    if ( Update() )
    {
        m_FLTK_Window->show();
    }
}

//==== Update Ellipsoid Screen ====//
bool HumanGeomScreen::Update()
{
    assert( m_ScreenMgr );

    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != HUMAN_GEOM_TYPE )
    {
        Hide();
        return false;
    }

    GeomScreen::Update();

    //==== Update Human Specific Parms ====//
    HumanGeom* human_ptr = dynamic_cast< HumanGeom* >( geom_ptr );
    assert( human_ptr );

    m_PresetPoseChoice.Update( human_ptr->m_PresetPose.GetID() );

    m_LenUnitChoice.Update( human_ptr->m_LenUnit.GetID() );
    m_MassUnitChoice.Update( human_ptr->m_MassUnit.GetID() );

    m_GenderChoice.Update( human_ptr->m_GenderFlag.GetID() );

    m_StatureSlider.SetMinBound( human_ptr->m_Stature.GetLowerLimit() );
    m_StatureSlider.SetMaxBound( human_ptr->m_Stature.GetUpperLimit() );

    m_StatureSlider.Update( human_ptr->m_Stature.GetID() );
    m_StaturePctSlider.Update( human_ptr->m_Stature_pct.GetID() );

    m_BMISlider.Update( human_ptr->m_BMI.GetID() );
    m_BMIPctSlider.Update( human_ptr->m_BMI_pct.GetID() );
    m_MassSlider.Update( human_ptr->m_Mass.GetID() );

    m_AutoDensityToggle.Update( human_ptr->m_AutoDensity.GetID() );
    m_VolumeOutput.Update( human_ptr->m_Volume.GetID() );

    m_AgeSlider.Update( human_ptr->m_Age.GetID() );
    m_SitFracSlider.Update( human_ptr->m_SitFrac.GetID() );

#ifdef SHOW_SHOW_SKEL_BUTTON
    m_ShowSkelButton.Update( human_ptr->m_ShowSkelFlag.GetID() );
#endif

    m_RLSymButton.Update( human_ptr->m_RLSymFlag.GetID() );

    m_BackSlider.Update( human_ptr->m_Back.GetID() );
    m_WaistSlider.Update( human_ptr->m_Waist.GetID() );

    m_ElbowRtSlider.Update( human_ptr->m_ElbowRt.GetID() );
    m_ShoulderABADRtSlider.Update( human_ptr->m_ShoulderABADRt.GetID() );
    m_ShoulderFERtSlider.Update( human_ptr->m_ShoulderFERt.GetID() );
    m_ShoulderIERtSlider.Update( human_ptr->m_ShoulderIERt.GetID() );

    m_HipABADRtSlider.Update( human_ptr->m_HipABADRt.GetID() );
    m_HipFERtSlider.Update( human_ptr->m_HipFERt.GetID() );
    m_KneeRtSlider.Update( human_ptr->m_KneeRt.GetID() );
    m_AnkleRtSlider.Update( human_ptr->m_AnkleRt.GetID() );

    m_ElbowLtSlider.Update( human_ptr->m_ElbowLt.GetID() );
    m_ShoulderABADLtSlider.Update( human_ptr->m_ShoulderABADLt.GetID() );
    m_ShoulderFELtSlider.Update( human_ptr->m_ShoulderFELt.GetID() );
    m_ShoulderIELtSlider.Update( human_ptr->m_ShoulderIELt.GetID() );

    m_HipABADLtSlider.Update( human_ptr->m_HipABADLt.GetID() );
    m_HipFELtSlider.Update( human_ptr->m_HipFELt.GetID() );
    m_KneeLtSlider.Update( human_ptr->m_KneeLt.GetID() );
    m_AnkleLtSlider.Update( human_ptr->m_AnkleLt.GetID() );




    if( human_ptr->m_RLSymFlag() )
    {
        m_ElbowLtSlider.Deactivate();
        m_ShoulderABADLtSlider.Deactivate();
        m_ShoulderFELtSlider.Deactivate();
        m_ShoulderIELtSlider.Deactivate();

        m_HipABADLtSlider.Deactivate();
        m_HipFELtSlider.Deactivate();
        m_KneeLtSlider.Deactivate();
        m_AnkleLtSlider.Deactivate();
    }

    return true;
}


//==== Non Menu Callbacks ====//
void HumanGeomScreen::CallBack( Fl_Widget *w )
{
    GeomScreen::CallBack( w );
}

void HumanGeomScreen::GuiDeviceCallBack( GuiDevice* gui_device )
{
    //==== Find Human Ptr ====//
    Geom *geom_ptr = m_ScreenMgr->GetCurrGeom();
    if (!geom_ptr || geom_ptr->GetType().m_Type != HUMAN_GEOM_TYPE) {
        return;
    }

    HumanGeom *human_ptr = dynamic_cast< HumanGeom * >( geom_ptr );
    assert(human_ptr);

    if (gui_device == &m_SetPose )
    {
        human_ptr->SetPreset();
        human_ptr->Update();
    }

    GeomScreen::GuiDeviceCallBack( gui_device );
}


