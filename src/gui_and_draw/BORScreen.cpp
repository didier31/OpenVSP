//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//
//////////////////////////////////////////////////////////////////////

#include "BORScreen.h"
#include "ScreenMgr.h"
#include "BORGeom.h"

#include <intl.h>

//==== Constructor ====//
BORScreen::BORScreen( ScreenMgr* mgr ) : GeomScreen( mgr, 300, 680, _("BOR") )
{
    m_CurrDisplayGroup = NULL;

    Fl_Group* design_tab = AddTab( "Design" );
    Fl_Group* design_group = AddSubGroup( design_tab, 5 );

    m_DesignLayout.SetGroupAndScreen( design_group, this );
    m_DesignLayout.AddDividerBox( "Design" );

    //==== Design ====//

    m_DesignLayout.SetButtonWidth( 80 );

    m_ModeChoice.AddItem( _("Flowthrough") );
    m_ModeChoice.AddItem( _("Upper") );
    m_ModeChoice.AddItem( _("Lower") );
    m_DesignLayout.AddChoice( m_ModeChoice, _("Mode") );

    m_DesignLayout.AddYGap();

    m_DesignLayout.AddDividerBox( _("Flowthrough Control") );
    m_DesignLayout.AddSlider( m_BORDiameterSlider, _("Diameter"), 10, "%7.3f" );
    m_DesignLayout.AddSlider( m_AngleSlider, "Angle", 10, "%7.3f" );

    m_DesignLayout.AddYGap();

    m_DesignLayout.SetFitWidthFlag( true );
    m_DesignLayout.AddOutput( m_A0Output, "A0", "%6.5g" );
    m_DesignLayout.AddOutput( m_AeOutput, "Ae", "%6.5g" );

    m_DesignLayout.SetSameLineFlag( true );
    m_DesignLayout.AddOutput( m_AminOutput, _("Amin"), "%6.5g", m_DesignLayout.GetW() / 2 );
    m_DesignLayout.AddOutput( m_AminWOutput, _("Amin W"), "%6.5g" , m_DesignLayout.GetW() / 2 );
    m_DesignLayout.ForceNewLine();

    m_DesignLayout.SetSameLineFlag( false );

    m_DesignLayout.AddYGap();

    m_DesignLayout.AddDividerBox( _("Tessellation Control") );
    m_DesignLayout.AddSlider( m_LEClusterSlider, _("LE Clustering"), 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_TEClusterSlider, _("TE Clustering"), 1, "%6.5f" );


    m_DesignLayout.AddSlider( m_CapTessSlider, _("Cap Tess"), 10, "%3.0f" );


    //==== XSec ====//
    Fl_Group* xsec_tab = AddTab( _("XSec") );
    Fl_Group* xsec_group = AddSubGroup( xsec_tab, 5 );

    m_XSecLayout.SetGroupAndScreen( xsec_group, this );
    m_XSecLayout.AddDividerBox( _("Cross Section") );

    m_XSecLayout.AddYGap();

    m_XSecLayout.AddDividerBox( _("Type") );

    m_XSecTypeChoice.AddItem( _("POINT") );
    m_XSecTypeChoice.AddItem( _("CIRCLE") );
    m_XSecTypeChoice.AddItem( _("ELLIPSE") );
    m_XSecTypeChoice.AddItem( _("SUPER_ELLIPSE") );
    m_XSecTypeChoice.AddItem( _("ROUNDED_RECTANGLE") );
    m_XSecTypeChoice.AddItem( _("GENERAL_FUSE") );
    m_XSecTypeChoice.AddItem( _("FUSE_FILE") );
    m_XSecTypeChoice.AddItem( _("FOUR_SERIES") );
    m_XSecTypeChoice.AddItem( _("SIX_SERIES") );
    m_XSecTypeChoice.AddItem( _("BICONVEX") );
    m_XSecTypeChoice.AddItem( _("WEDGE") );
    m_XSecTypeChoice.AddItem( _("EDIT_CURVE") );
    m_XSecTypeChoice.AddItem( _("AF_FILE") );
    m_XSecTypeChoice.AddItem( _("CST_AIRFOIL") );
    m_XSecTypeChoice.AddItem( _("KARMAN_TREFFTZ") );
    m_XSecTypeChoice.AddItem( _("FOUR_DIGIT_MOD") );
    m_XSecTypeChoice.AddItem( _("FIVE_DIGIT") );
    m_XSecTypeChoice.AddItem( _("FIVE_DIGIT_MOD") );
    m_XSecTypeChoice.AddItem( _("16_SERIES") );

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( false );

    m_XSecLayout.AddChoice( m_XSecTypeChoice, _("Choose Type:") );

    m_XSecLayout.SetFitWidthFlag( false );
    m_XSecLayout.SetSameLineFlag( true );

    m_XSecLayout.SetButtonWidth( m_XSecLayout.GetW() / 2 );
    m_XSecLayout.AddButton( m_ShowXSecButton, _("Show") );

    m_XSecLayout.AddSubGroupLayout( m_ConvertCEDITGroup, m_XSecLayout.GetW(), m_XSecLayout.GetStdHeight() );
    m_ConvertCEDITGroup.SetButtonWidth( m_XSecLayout.GetW() / 2 );
    m_ConvertCEDITGroup.SetFitWidthFlag( false );
    m_ConvertCEDITGroup.AddButton( m_ConvertCEDITButton, _("Convert CEDIT") );

    m_XSecLayout.AddSubGroupLayout( m_EditCEDITGroup, m_XSecLayout.GetW(), m_XSecLayout.GetStdHeight() );
    m_EditCEDITGroup.SetFitWidthFlag( false );
    m_EditCEDITGroup.SetButtonWidth( m_XSecLayout.GetW() / 2 );
    m_EditCEDITGroup.AddButton( m_EditCEDITButton, _("Edit Curve") );

    m_XSecLayout.ForceNewLine();

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( false );

    m_XSecLayout.AddYGap();

    //==== Circle XSec ====//
    m_XSecLayout.AddSubGroupLayout( m_CircleGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_CircleGroup.AddSlider(  m_DiameterSlider, _("Diameter"), 10, "%6.5f" );

    //==== Ellipse XSec ====//
    m_XSecLayout.AddSubGroupLayout( m_EllipseGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_EllipseGroup.AddSlider(  m_EllipseHeightSlider, _("Height"), 10, "%6.5f" );
    m_EllipseGroup.AddSlider(  m_EllipseWidthSlider, _("Width"), 10, "%6.5f" );

    //==== Super XSec ====//
    m_XSecLayout.AddSubGroupLayout( m_SuperGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_SuperGroup.AddSlider( m_SuperHeightSlider, _("Height"), 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperWidthSlider,  _("Width"), 10, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddSlider( m_SuperMaxWidthLocSlider, _("MaxWLoc"), 2, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddSlider( m_SuperMSlider, _("M"), 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperNSlider, _("N"), 10, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddButton( m_SuperToggleSym, _("T/B Symmetric Exponents") );
    m_SuperGroup.AddSlider( m_SuperM_botSlider, _("M Bottom"), 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperN_botSlider, _("N Bottom"), 10, "%6.5f" );

    //==== Rounded Rect ====//
    m_XSecLayout.AddSubGroupLayout( m_RoundedRectGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_RoundedRectGroup.AddSlider( m_RRHeightSlider, _("Height"), 10, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRWidthSlider,  _("Width"), 10, "%6.5f" );
    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.AddSlider( m_RRSkewSlider, _("Skew"), 2, "%6.5f");
    m_RoundedRectGroup.AddSlider( m_RRVSkewSlider, _("VSkew"), 2, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRKeystoneSlider, _("Keystone"), 1, "%6.5f");

    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.SetSameLineFlag( true );
    m_RoundedRectGroup.SetFitWidthFlag( false );

    int oldbw = m_RoundedRectGroup.GetButtonWidth();

    m_RoundedRectGroup.AddLabel( _("Symmetry:"), oldbw );

    m_RoundedRectGroup.SetButtonWidth( m_RoundedRectGroup.GetRemainX() / 4 );
    m_RoundedRectGroup.AddButton( m_RRRadNoSymToggle, _("None") );
    m_RoundedRectGroup.AddButton( m_RRRadRLSymToggle, _("R//L") );
    m_RoundedRectGroup.AddButton( m_RRRadTBSymToggle, _("T//B") );
    m_RoundedRectGroup.AddButton( m_RRRadAllSymToggle, _("All") );

    m_RRRadSymRadioGroup.Init( this );
    m_RRRadSymRadioGroup.AddButton( m_RRRadNoSymToggle.GetFlButton() );
    m_RRRadSymRadioGroup.AddButton( m_RRRadRLSymToggle.GetFlButton() );
    m_RRRadSymRadioGroup.AddButton( m_RRRadTBSymToggle.GetFlButton() );
    m_RRRadSymRadioGroup.AddButton( m_RRRadAllSymToggle.GetFlButton() );

    m_RoundedRectGroup.ForceNewLine();
    m_RoundedRectGroup.SetSameLineFlag( false );
    m_RoundedRectGroup.SetFitWidthFlag( true );

    m_RoundedRectGroup.SetButtonWidth( oldbw );

    m_RoundedRectGroup.AddSlider( m_RRRadiusTRSlider, _("TR Radius"), 10, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRRadiusTLSlider, _("TL Radius"), 10, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRRadiusBLSlider, _("BL Radius"), 10, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRRadiusBRSlider, _("BR Radius"), 10, "%6.5f" );
    m_RoundedRectGroup.AddYGap();

    m_RoundedRectGroup.AddButton( m_RRKeyCornerButton, _("Key Corner") );

    //==== General Fuse XSec ====//
    m_XSecLayout.AddSubGroupLayout( m_GenGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_GenGroup.AddSlider( m_GenHeightSlider, _("Height"), 10, "%6.5f" );
    m_GenGroup.AddSlider( m_GenWidthSlider, _("Width"), 10, "%6.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenMaxWidthLocSlider, _("MaxWLoc"), 1, "%6.5f" );
    m_GenGroup.AddSlider( m_GenCornerRadSlider, _("CornerRad"), 1, "%6.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenTopTanAngleSlider, _("TopTanAng"), 90, "%7.5f" );
    m_GenGroup.AddSlider( m_GenBotTanAngleSlider, _("BotTanAng"), 90, "%7.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenTopStrSlider, _("TopStr"), 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenBotStrSlider, _("BotStr"), 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenUpStrSlider, _("UpStr"), 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenLowStrSlider, _("LowStr"), 1, "%7.5f" );

    //==== Four Series AF ====//
    m_XSecLayout.AddSubGroupLayout( m_FourSeriesGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_FourSeriesGroup.AddOutput( m_FourNameOutput, _("Name") );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddSlider( m_FourChordSlider, _("Chord"), 10, "%7.3f" );
    m_FourSeriesGroup.AddSlider( m_FourThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_FourSeriesGroup.AddYGap();

    int actionToggleButtonWidth = 15;
    int actionSliderButtonWidth = m_FourSeriesGroup.GetButtonWidth() - actionToggleButtonWidth;

    m_FourSeriesGroup.SetSameLineFlag( true );

    m_FourSeriesGroup.SetFitWidthFlag( false );
    m_FourSeriesGroup.SetButtonWidth( actionToggleButtonWidth );
    m_FourSeriesGroup.AddButton( m_FourCamberButton, "" );
    m_FourSeriesGroup.SetButtonWidth( actionSliderButtonWidth );
    m_FourSeriesGroup.SetFitWidthFlag( true );
    m_FourSeriesGroup.AddSlider( m_FourCamberSlider, _("Camber"), 0.2, "%7.5f" );

    m_FourSeriesGroup.ForceNewLine();

    m_FourSeriesGroup.SetFitWidthFlag( false );
    m_FourSeriesGroup.SetButtonWidth( actionToggleButtonWidth );
    m_FourSeriesGroup.AddButton( m_FourCLiButton, "" );
    m_FourSeriesGroup.SetButtonWidth( actionSliderButtonWidth );
    m_FourSeriesGroup.SetFitWidthFlag( true );
    m_FourSeriesGroup.AddSlider( m_FourCLiSlider, _("Ideal CL"), 1, "%7.5f" );

    m_FourSeriesGroup.ForceNewLine();

    m_FourSeriesGroup.SetSameLineFlag( false );
    m_FourSeriesGroup.SetButtonWidth( actionSliderButtonWidth + actionToggleButtonWidth );

    m_FourCamberGroup.Init( this );
    m_FourCamberGroup.AddButton( m_FourCamberButton.GetFlButton() );
    m_FourCamberGroup.AddButton( m_FourCLiButton.GetFlButton() );

    vector< int > camb_val_map;
    camb_val_map.push_back( vsp::MAX_CAMB );
    camb_val_map.push_back( vsp::DESIGN_CL );
    m_FourCamberGroup.SetValMapVec( camb_val_map );

    m_FourSeriesGroup.AddSlider( m_FourCamberLocSlider, _("CamberLoc"), 1, "%7.5f" );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddButton( m_FourInvertButton, _("Invert Airfoil") );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddButton( m_FourSharpTEButton, _("Sharpen TE") );

    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.SetSameLineFlag( true );
    m_FourSeriesGroup.SetFitWidthFlag( false );
    m_FourSeriesGroup.SetButtonWidth( 125 );
    m_FourSeriesGroup.AddButton( m_FourFitCSTButton, _("Fit CST") );
    m_FourSeriesGroup.InitWidthHeightVals();
    m_FourSeriesGroup.SetFitWidthFlag( true );
    m_FourSeriesGroup.AddCounter( m_FourDegreeCounter, _("Degree"), 125 );

    //==== Six Series AF ====//
    m_XSecLayout.AddSubGroupLayout( m_SixSeriesGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_SixSeriesGroup.AddOutput( m_SixNameOutput, _("Name") );
    m_SixSeriesGroup.AddYGap();

    m_SixSeriesChoice.AddItem( "63" );
    m_SixSeriesChoice.AddItem( "64" );
    m_SixSeriesChoice.AddItem( "65" );
    m_SixSeriesChoice.AddItem( "66" );
    m_SixSeriesChoice.AddItem( "67" );
    m_SixSeriesChoice.AddItem( "63a" );
    m_SixSeriesChoice.AddItem( "64a" );
    m_SixSeriesChoice.AddItem( "65a" );
    m_SixSeriesGroup.AddChoice( m_SixSeriesChoice, _("Series") );

    m_SixSeriesGroup.AddYGap();

    m_SixSeriesGroup.AddSlider( m_SixChordSlider, _("Chord"), 10, "%7.3f" );
    m_SixSeriesGroup.AddSlider( m_SixThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.AddSlider( m_SixIdealClSlider, _("Ideal CL"), 1, "%7.5f" );
    m_SixSeriesGroup.AddSlider( m_SixASlider, "A", 1, "%7.5f" );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.AddButton( m_SixInvertButton, _("Invert Airfoil") );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.SetSameLineFlag( true );
    m_SixSeriesGroup.SetFitWidthFlag( false );
    m_SixSeriesGroup.SetButtonWidth( 125 );
    m_SixSeriesGroup.AddButton( m_SixFitCSTButton, _("Fit CST") );
    m_SixSeriesGroup.InitWidthHeightVals();
    m_SixSeriesGroup.SetFitWidthFlag( true );
    m_SixSeriesGroup.AddCounter( m_SixDegreeCounter, _("Degree"), 125 );

    //==== Biconvex AF ====//
    m_XSecLayout.AddSubGroupLayout( m_BiconvexGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_BiconvexGroup.AddSlider( m_BiconvexChordSlider, _("Chord"), 10, "%7.3f" );
    m_BiconvexGroup.AddSlider( m_BiconvexThickChordSlider, _("T/C"), 1, "%7.5f" );

    //==== Wedge AF ====//
    m_XSecLayout.AddSubGroupLayout( m_WedgeGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_WedgeGroup.AddSlider( m_WedgeChordSlider, _("Chord"), 10, "%7.3f" );
    m_WedgeGroup.AddSlider( m_WedgeThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddSlider( m_WedgeThickLocSlider, _("Thick X"), 1, "%7.5f" );
    m_WedgeGroup.AddSlider( m_WedgeFlatUpSlider, _("Flat Up"), 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddButton( m_WedgeSymmThickButton, _("Symm Thickness") );
    m_WedgeGroup.AddSlider( m_WedgeThickLocLowSlider, _("Thick X Low"), 1, "%7.5f" );
    m_WedgeGroup.AddSlider( m_WedgeFlatLowSlider, _("Flat Low"), 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddSlider( m_WedgeZCamberSlider, _("Camber"), 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddSlider( m_WedgeUForeUpSlider, _("U Fwd Up"), 1, "%7.5f" );
    m_WedgeGroup.AddSlider( m_WedgeUForeLowSlider, _("U Fwd Low"), 1, "%7.5f" );
    m_WedgeGroup.AddSlider( m_WedgeDuUpSlider, _("dU Flat Up"), 1, "%7.5f" );
    m_WedgeGroup.AddSlider( m_WedgeDuLowSlider, _("dU Flat Low"), 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddButton( m_WedgeInvertButton, _("Invert Airfoil") );

    //==== Fuse File ====//
    m_XSecLayout.AddSubGroupLayout( m_FuseFileGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_FuseFileGroup.AddButton( m_ReadFuseFileButton, _("Read File") );
    m_FuseFileGroup.AddYGap();
    m_FuseFileGroup.AddSlider( m_FileHeightSlider, _("Height"), 10, "%7.3f" );
    m_FuseFileGroup.AddSlider( m_FileWidthSlider, _("Width"), 10, "%7.3f" );

    //==== Airfoil File ====//
    m_XSecLayout.AddSubGroupLayout( m_AfFileGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_AfFileGroup.AddButton( m_AfReadFileButton, _("Read File") );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddOutput( m_AfFileNameOutput, _("Name") );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddSlider( m_AfFileChordSlider, _("Chord"), 10, "%7.3f" );
    m_AfFileGroup.AddSlider( m_AfFileThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_AfFileGroup.AddOutput( m_AfFileBaseThickChordOutput, _("Base T/C"), "%7.5f" );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddButton( m_AfFileInvertButton, _("Invert Airfoil") );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.SetSameLineFlag( true );
    m_AfFileGroup.SetFitWidthFlag( false );
    m_AfFileGroup.SetButtonWidth( 125 );
    m_AfFileGroup.AddButton( m_AfFileFitCSTButton, _("Fit CST") );
    m_AfFileGroup.InitWidthHeightVals();
    m_AfFileGroup.SetFitWidthFlag( true );
    m_AfFileGroup.AddCounter( m_AfFileDegreeCounter, _("Degree"), 125 );

    //==== CST Airfoil ====//
    m_XSecLayout.AddSubGroupLayout( m_CSTAirfoilGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );

    m_CSTAirfoilGroup.AddOutput( m_CSTThickChordOutput, _("T/C"), "%7.5f" );

    m_CSTAirfoilGroup.AddButton( m_CSTContLERadButton, _("Enforce Continuous LE Radius") );
    m_CSTAirfoilGroup.AddButton( m_CSTInvertButton, _("Invert Airfoil") );

    m_CSTAirfoilGroup.AddYGap();
    m_CSTAirfoilGroup.AddSlider( m_CSTChordSlider, _("Chord"), 10, "%7.3f");

    m_CSTAirfoilGroup.AddYGap();
    m_CSTAirfoilGroup.AddDividerBox( _("Upper Surface") );

    m_CSTAirfoilGroup.SetSameLineFlag( true );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTAirfoilGroup.AddOutput( m_UpDegreeOutput, _("Degree"), m_CSTAirfoilGroup.GetButtonWidth() * 2 );
    m_CSTAirfoilGroup.SetFitWidthFlag( false );
    m_CSTAirfoilGroup.AddButton( m_UpDemoteButton, _("Demote") );
    m_CSTAirfoilGroup.AddButton( m_UpPromoteButton, _("Promote") );

    m_CSTAirfoilGroup.ForceNewLine();

    m_CSTAirfoilGroup.SetSameLineFlag( false );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTUpCoeffScroll = m_CSTAirfoilGroup.AddFlScroll( 60 );

    m_CSTUpCoeffScroll->type( Fl_Scroll::VERTICAL_ALWAYS );
    m_CSTUpCoeffScroll->box( FL_BORDER_BOX );
    m_CSTUpCoeffLayout.SetGroupAndScreen( m_CSTUpCoeffScroll, this );

    m_CSTAirfoilGroup.AddYGap();

    m_CSTAirfoilGroup.AddDividerBox( _("Lower Surface") );

    m_CSTAirfoilGroup.SetSameLineFlag( true );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTAirfoilGroup.AddOutput( m_LowDegreeOutput, _("Degree"), m_CSTAirfoilGroup.GetButtonWidth() * 2 );
    m_CSTAirfoilGroup.SetFitWidthFlag( false );
    m_CSTAirfoilGroup.AddButton( m_LowDemoteButton, "Demote" );
    m_CSTAirfoilGroup.AddButton( m_LowPromoteButton, "Promote" );

    m_CSTAirfoilGroup.ForceNewLine();

    m_CSTAirfoilGroup.SetSameLineFlag( false );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTLowCoeffScroll = m_CSTAirfoilGroup.AddFlScroll( 60 );
    m_CSTLowCoeffScroll->type( Fl_Scroll::VERTICAL_ALWAYS );
    m_CSTLowCoeffScroll->box( FL_BORDER_BOX );
    m_CSTLowCoeffLayout.SetGroupAndScreen( m_CSTLowCoeffScroll, this );

    //==== VKT AF ====//
    m_XSecLayout.AddSubGroupLayout( m_VKTGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_VKTGroup.AddSlider( m_VKTChordSlider, _("Chord"), 10, "%7.3f" );
    m_VKTGroup.AddYGap();
    m_VKTGroup.AddSlider( m_VKTEpsilonSlider, _("Epsilon"), 1, "%7.5f" );
    m_VKTGroup.AddSlider( m_VKTKappaSlider, _("Kappa"), 1, "%7.5f" );
    m_VKTGroup.AddSlider( m_VKTTauSlider, _("Tau"), 10, "%7.5f" );
    m_VKTGroup.AddOutput( m_VKTThickChordOutput, _("T/C"), "%7.5f" );
    m_VKTGroup.AddYGap();
    m_VKTGroup.AddButton( m_VKTInvertButton, _("Invert Airfoil") );
    m_VKTGroup.AddYGap();
    m_VKTGroup.SetSameLineFlag( true );
    m_VKTGroup.SetFitWidthFlag( false );
    m_VKTGroup.SetButtonWidth( 125 );
    m_VKTGroup.AddButton( m_VKTFitCSTButton, _("Fit CST") );
    m_VKTGroup.InitWidthHeightVals();
    m_VKTGroup.SetFitWidthFlag( true );
    m_VKTGroup.AddCounter( m_VKTDegreeCounter, _("Degree"), 125 );

    //==== Four Series AF ====//
    m_XSecLayout.AddSubGroupLayout( m_FourDigitModGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_FourDigitModGroup.AddOutput( m_FourModNameOutput, _("Name") );
    m_FourDigitModGroup.AddYGap();
    m_FourDigitModGroup.AddSlider( m_FourModChordSlider, _("Chord"), 10, "%7.3f" );
    m_FourDigitModGroup.AddSlider( m_FourModThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_FourDigitModGroup.AddYGap();

    m_FourDigitModGroup.SetSameLineFlag( true );

    m_FourDigitModGroup.SetFitWidthFlag( false );
    m_FourDigitModGroup.SetButtonWidth( actionToggleButtonWidth );
    m_FourDigitModGroup.AddButton( m_FourModCamberButton, "" );
    m_FourDigitModGroup.SetButtonWidth( actionSliderButtonWidth );
    m_FourDigitModGroup.SetFitWidthFlag( true );
    m_FourDigitModGroup.AddSlider( m_FourModCamberSlider, _("Camber"), 0.2, "%7.5f" );

    m_FourDigitModGroup.ForceNewLine();

    m_FourDigitModGroup.SetFitWidthFlag( false );
    m_FourDigitModGroup.SetButtonWidth( actionToggleButtonWidth );
    m_FourDigitModGroup.AddButton( m_FourModCLiButton, "" );
    m_FourDigitModGroup.SetButtonWidth( actionSliderButtonWidth );
    m_FourDigitModGroup.SetFitWidthFlag( true );
    m_FourDigitModGroup.AddSlider( m_FourModCLiSlider, _("Ideal CL"), 1, "%7.5f" );

    m_FourDigitModGroup.ForceNewLine();

    m_FourDigitModGroup.SetSameLineFlag( false );
    m_FourDigitModGroup.SetButtonWidth( actionSliderButtonWidth + actionToggleButtonWidth );

    m_FourModCamberGroup.Init( this );
    m_FourModCamberGroup.AddButton( m_FourModCamberButton.GetFlButton() );
    m_FourModCamberGroup.AddButton( m_FourModCLiButton.GetFlButton() );

    m_FourModCamberGroup.SetValMapVec( camb_val_map );

    m_FourDigitModGroup.AddSlider( m_FourModCamberLocSlider, _("CamberLoc"), 1, "%7.5f" );
    m_FourDigitModGroup.AddYGap();
    m_FourDigitModGroup.AddSlider( m_FourModThicknessLocSlider, _("T/CLoc"), 0.5, "%7.5f" );
    m_FourDigitModGroup.AddSlider( m_FourModLERadIndexSlider, _("LERadIndx"), 5, "%7.5f" );
    m_FourDigitModGroup.AddYGap();
    m_FourDigitModGroup.AddButton( m_FourModInvertButton, _("Invert Airfoil") );
    m_FourDigitModGroup.AddYGap();
    m_FourDigitModGroup.AddButton( m_FourModSharpTEButton, _("Sharpen TE") );
    m_FourDigitModGroup.AddYGap();
    m_FourDigitModGroup.SetSameLineFlag( true );
    m_FourDigitModGroup.SetFitWidthFlag( false );
    m_FourDigitModGroup.SetButtonWidth( 125 );
    m_FourDigitModGroup.AddButton( m_FourModFitCSTButton, _("Fit CST") );
    m_FourDigitModGroup.InitWidthHeightVals();
    m_FourDigitModGroup.SetFitWidthFlag( true );
    m_FourDigitModGroup.AddCounter( m_FourModDegreeCounter, _("Degree"), 125 );

    //==== Five Digit AF ====//
    m_XSecLayout.AddSubGroupLayout( m_FiveDigitGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_FiveDigitGroup.AddOutput( m_FiveNameOutput, _("Name") );
    m_FiveDigitGroup.AddYGap();
    m_FiveDigitGroup.AddSlider( m_FiveChordSlider, _("Chord"), 10, "%7.3f" );
    m_FiveDigitGroup.AddSlider( m_FiveThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_FiveDigitGroup.AddYGap();
    m_FiveDigitGroup.AddSlider( m_FiveCLiSlider, _("Ideal CL"), 1, "%7.5f" );
    m_FiveDigitGroup.AddSlider( m_FiveCamberLocSlider, _("CamberLoc"), 1, "%7.5f" );
    m_FiveDigitGroup.AddYGap();
    m_FiveDigitGroup.AddButton( m_FiveInvertButton, _("Invert Airfoil") );
    m_FiveDigitGroup.AddYGap();
    m_FiveDigitGroup.AddButton( m_FiveSharpTEButton, _("Sharpen TE") );
    m_FiveDigitGroup.AddYGap();
    m_FiveDigitGroup.SetSameLineFlag( true );
    m_FiveDigitGroup.SetFitWidthFlag( false );
    m_FiveDigitGroup.SetButtonWidth( 125 );
    m_FiveDigitGroup.AddButton( m_FiveFitCSTButton, _("Fit CST") );
    m_FiveDigitGroup.InitWidthHeightVals();
    m_FiveDigitGroup.SetFitWidthFlag( true );
    m_FiveDigitGroup.AddCounter( m_FiveDegreeCounter, _("Degree"), 125 );

    //==== Five Digit Mod AF ====//
    m_XSecLayout.AddSubGroupLayout( m_FiveDigitModGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_FiveDigitModGroup.AddOutput( m_FiveModNameOutput, _("Name") );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.AddSlider( m_FiveModChordSlider, _("Chord"), 10, "%7.3f" );
    m_FiveDigitModGroup.AddSlider( m_FiveModThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.AddSlider( m_FiveModCLiSlider, _("Ideal CL"), 1, "%7.5f" );
    m_FiveDigitModGroup.AddSlider( m_FiveModCamberLocSlider, _("CamberLoc"), 1, "%7.5f" );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.AddSlider( m_FiveModThicknessLocSlider, _("T/CLoc"), 0.5, "%7.5f" );
    m_FiveDigitModGroup.AddSlider( m_FiveModLERadIndexSlider, _("LERadIndx"), 5, "%7.5f" );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.AddButton( m_FiveModInvertButton, _("Invert Airfoil") );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.AddButton( m_FiveModSharpTEButton, _("Sharpen TE") );
    m_FiveDigitModGroup.AddYGap();
    m_FiveDigitModGroup.SetSameLineFlag( true );
    m_FiveDigitModGroup.SetFitWidthFlag( false );
    m_FiveDigitModGroup.SetButtonWidth( 125 );
    m_FiveDigitModGroup.AddButton( m_FiveModFitCSTButton, _("Fit CST") );
    m_FiveDigitModGroup.InitWidthHeightVals();
    m_FiveDigitModGroup.SetFitWidthFlag( true );
    m_FiveDigitModGroup.AddCounter( m_FiveModDegreeCounter, _("Degree"), 125 );

    //==== 16 Series AF ====//
    m_XSecLayout.AddSubGroupLayout( m_OneSixSeriesGroup, m_XSecLayout.GetW(), m_XSecLayout.GetRemainY() );
    m_OneSixSeriesGroup.AddOutput( m_OneSixSeriesNameOutput, _("Name") );
    m_OneSixSeriesGroup.AddYGap();
    m_OneSixSeriesGroup.AddSlider( m_OneSixSeriesChordSlider, ("Chord"), 10, "%7.3f" );
    m_OneSixSeriesGroup.AddSlider( m_OneSixSeriesThickChordSlider, _("T/C"), 1, "%7.5f" );
    m_OneSixSeriesGroup.AddYGap();
    m_OneSixSeriesGroup.AddSlider( m_OneSixSeriesCLiSlider, _("Ideal CL"), 1, "%7.5f" );
    m_OneSixSeriesGroup.AddYGap();
    m_OneSixSeriesGroup.AddButton( m_OneSixSeriesInvertButton, _("Invert Airfoil") );
    m_OneSixSeriesGroup.AddYGap();
    m_OneSixSeriesGroup.AddButton( m_OneSixSeriesSharpTEButton, _("Sharpen TE") );
    m_OneSixSeriesGroup.AddYGap();
    m_OneSixSeriesGroup.SetSameLineFlag( true );
    m_OneSixSeriesGroup.SetFitWidthFlag( false );
    m_OneSixSeriesGroup.SetButtonWidth( 125 );
    m_OneSixSeriesGroup.AddButton( m_OneSixSeriesFitCSTButton, _("Fit CST") );
    m_OneSixSeriesGroup.InitWidthHeightVals();
    m_OneSixSeriesGroup.SetFitWidthFlag( true );
    m_OneSixSeriesGroup.AddCounter( m_OneSixSeriesDegreeCounter, _("Degree"), 125 );

    DisplayGroup( &m_PointGroup );

    //==== Modify ====//

    Fl_Group* modify_tab = AddTab( "Modify" );
    Fl_Group* modify_group = AddSubGroup( modify_tab, 5 );

    m_ModifyLayout.SetButtonWidth( 70 );

    m_ModifyLayout.SetGroupAndScreen( modify_group, this );
    m_ModifyLayout.AddDividerBox( "Airfoil Section" );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.InitWidthHeightVals();
    m_ModifyLayout.AddDividerBox( "Shift, Rotate, & Scale" );

    m_ModifyLayout.AddSlider( m_AFDeltaXSlider, _("Delta X/C"), 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFDeltaYSlider, _("Delta Y/C"), 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFThetaSlider, _("Theta"), 20, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFScaleSlider, _("Scale"), 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFShiftLESlider, _("Shift LE"), 1, "%7.3f" );

    m_ModifyLayout.SetChoiceButtonWidth( 74 );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddDividerBox( _("Leading Edge") );
    m_LECapChoice.AddItem( "FLAT", vsp::FLAT_END_CAP );
    m_LECapChoice.AddItem( "ROUND", vsp::ROUND_END_CAP );
    m_LECapChoice.AddItem( "EDGE", vsp::EDGE_END_CAP );
    m_LECapChoice.AddItem( "SHARP", vsp::SHARP_END_CAP );

    m_ModifyLayout.AddChoice( m_LECapChoice, _("Cap") );

    m_ModifyLayout.AddSlider( m_LECapLengthSlider, _("Length"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_LECapOffsetSlider, _("Offset"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_LECapStrengthSlider, _("Strength"), 10.0, "%6.5f" );

    m_LECloseChoice.AddItem( _("NONE") );
    m_LECloseChoice.AddItem( _("SKEW LOWER") );
    m_LECloseChoice.AddItem( _("SKEW UPPER") );
    m_LECloseChoice.AddItem( _("SKEW BOTH") );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddChoice( m_LECloseChoice, "Closure:", m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_LECloseABSButton, _("Abs") );
    m_ModifyLayout.AddButton( m_LECloseRELButton, _("Rel") );

    m_LECloseGroup.Init( this );
    m_LECloseGroup.AddButton( m_LECloseABSButton.GetFlButton() );
    m_LECloseGroup.AddButton( m_LECloseRELButton.GetFlButton() );

    vector< int > close_val_map;
    close_val_map.push_back( vsp::ABS );
    close_val_map.push_back( vsp::REL );
    m_LECloseGroup.SetValMapVec( close_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_CloseLEThickSlider, _("T"), 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_LETrimChoice.AddItem( "NONE" );
    m_LETrimChoice.AddItem( "X" );
    m_LETrimChoice.AddItem( "THICK" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddChoice( m_LETrimChoice, _("Trim:"), m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_LETrimABSButton, _("Abs") );
    m_ModifyLayout.AddButton( m_LETrimRELButton, _("Rel") );

    m_LETrimGroup.Init( this );
    m_LETrimGroup.AddButton( m_LETrimABSButton.GetFlButton() );
    m_LETrimGroup.AddButton( m_LETrimRELButton.GetFlButton() );

    vector< int > trim_val_map;
    trim_val_map.push_back( vsp::ABS );
    trim_val_map.push_back( vsp::REL );
    m_LETrimGroup.SetValMapVec( trim_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_TrimLEXSlider, _("X"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TrimLEThickSlider, _("T"), 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddDividerBox( _("Trailing Edge") );
    m_TECapChoice.AddItem( "FLAT", vsp::FLAT_END_CAP );
    m_TECapChoice.AddItem( "ROUND", vsp::ROUND_END_CAP );
    m_TECapChoice.AddItem( "EDGE", vsp::EDGE_END_CAP );
    m_TECapChoice.AddItem( "SHARP", vsp::SHARP_END_CAP );

    m_ModifyLayout.AddChoice( m_TECapChoice, "Cap:" );

    m_ModifyLayout.AddSlider( m_TECapLengthSlider, _("Length"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TECapOffsetSlider, _("Offset"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TECapStrengthSlider, _("Strength"), 10.0, "%6.5f" );

    m_TECloseChoice.AddItem( _("NONE") );
    m_TECloseChoice.AddItem( _("SKEW LOWER") );
    m_TECloseChoice.AddItem( _("SKEW UPPER") );
    m_TECloseChoice.AddItem( _("SKEW BOTH") );
    m_TECloseChoice.AddItem( _("EXTRAPOLATE") );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddChoice( m_TECloseChoice, _("Closure:"), m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_TECloseABSButton, _("Abs") );
    m_ModifyLayout.AddButton( m_TECloseRELButton, _("Rel") );

    m_TECloseGroup.Init( this );
    m_TECloseGroup.AddButton( m_TECloseABSButton.GetFlButton() );
    m_TECloseGroup.AddButton( m_TECloseRELButton.GetFlButton() );

    m_TECloseGroup.SetValMapVec( close_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_CloseTEThickSlider, _("T"), 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_TETrimChoice.AddItem( "NONE" );
    m_TETrimChoice.AddItem( "X" );
    m_TETrimChoice.AddItem( "THICK" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddChoice( m_TETrimChoice, _("Trim:"), m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_TETrimABSButton, _("Abs") );
    m_ModifyLayout.AddButton( m_TETrimRELButton, _("Rel") );

    m_TETrimGroup.Init( this );
    m_TETrimGroup.AddButton( m_TETrimABSButton.GetFlButton() );
    m_TETrimGroup.AddButton( m_TETrimRELButton.GetFlButton() );

    m_TETrimGroup.SetValMapVec( trim_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_TrimTEXSlider, _("X"), 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TrimTEThickSlider, _("T"), 10.0, "%6.5f" );

}


//==== Show BOR Screen ====//
void BORScreen::Show()
{
    if ( Update() )
    {
        m_FLTK_Window->show();
    }
}

//==== Update BOR Screen ====//
bool BORScreen::Update()
{
    assert( m_ScreenMgr );

    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != BOR_GEOM_TYPE )
    {
        Hide();
        return false;
    }

    GeomScreen::Update();

    //==== Update BOR Specific Parms ====//
    BORGeom* bor_ptr = dynamic_cast< BORGeom* >( geom_ptr );
    assert( bor_ptr );

    m_A0Output.Update( bor_ptr->m_A0.GetID() );
    m_AminOutput.Update( bor_ptr->m_Amin.GetID() );
    m_AminWOutput.Update( bor_ptr->m_AminW.GetID() );
    m_AeOutput.Update( bor_ptr->m_Ae.GetID() );

    m_ModeChoice.Update( bor_ptr->m_Mode.GetID() );

    m_BORDiameterSlider.Update( bor_ptr->m_Diameter.GetID() );
    m_AngleSlider.Update( bor_ptr->m_Angle.GetID() );

    if ( bor_ptr->m_Mode() == vsp::BOR_FLOWTHROUGH )
    {
        m_BORDiameterSlider.Activate();
        m_AngleSlider.Activate();

        m_A0Output.Activate();
        m_AeOutput.Activate();
        m_AminOutput.Activate();
        m_AminWOutput.Activate();
    }
    else
    {
        m_BORDiameterSlider.Deactivate();
        m_AngleSlider.Deactivate();

        m_A0Output.Deactivate();
        m_AeOutput.Deactivate();
        m_AminOutput.Deactivate();
        m_AminWOutput.Deactivate();
    }

    m_LEClusterSlider.Update( bor_ptr->m_LECluster.GetID() );
    m_TEClusterSlider.Update( bor_ptr->m_TECluster.GetID() );

    m_CapTessSlider.Update( bor_ptr->m_CapUMinTess.GetID() );

    XSecCurve* xsc = bor_ptr->GetXSecCurve();
    if ( xsc )
    {
        m_XSecTypeChoice.SetVal( xsc->GetType() );

        if ( xsc->GetType() == vsp::XS_POINT )
        {
            DisplayGroup( NULL );
        }
        else if ( xsc->GetType() == vsp::XS_SUPER_ELLIPSE )
        {
            DisplayGroup( &m_SuperGroup );

            SuperXSec* super_xs = dynamic_cast< SuperXSec* >( xsc );
            assert( super_xs );
            m_SuperHeightSlider.Update( super_xs->m_Height.GetID() );
            m_SuperWidthSlider.Update( super_xs->m_Width.GetID() );
            m_SuperMSlider.Update( super_xs->m_M.GetID() );
            m_SuperNSlider.Update( super_xs->m_N.GetID() );
            m_SuperToggleSym.Update( super_xs->m_TopBotSym.GetID() );
            m_SuperM_botSlider.Update( super_xs->m_M_bot.GetID() );
            m_SuperN_botSlider.Update( super_xs->m_N_bot.GetID() );
            m_SuperMaxWidthLocSlider.Update( super_xs->m_MaxWidthLoc.GetID() );

            if ( super_xs->m_TopBotSym() )
            {
                m_SuperM_botSlider.Deactivate();
                m_SuperN_botSlider.Deactivate();
            }
            else if ( !super_xs->m_TopBotSym() )
            {
                m_SuperM_botSlider.Activate();
                m_SuperN_botSlider.Activate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_CIRCLE )
        {
            DisplayGroup( &m_CircleGroup );
            CircleXSec* circle_xs = dynamic_cast< CircleXSec* >( xsc );
            assert( circle_xs );

            m_DiameterSlider.Update( circle_xs->m_Diameter.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_ELLIPSE )
        {
            DisplayGroup( & m_EllipseGroup );

            EllipseXSec* ellipse_xs = dynamic_cast< EllipseXSec* >( xsc );
            m_EllipseHeightSlider.Update( ellipse_xs->m_Height.GetID() );
            m_EllipseWidthSlider.Update( ellipse_xs->m_Width.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_ROUNDED_RECTANGLE )
        {
            DisplayGroup( & m_RoundedRectGroup );
            RoundedRectXSec* rect_xs = dynamic_cast< RoundedRectXSec* >( xsc );
            assert( rect_xs );

            m_RRHeightSlider.Update( rect_xs->m_Height.GetID() );
            m_RRWidthSlider.Update( rect_xs->m_Width.GetID() );
            m_RRRadSymRadioGroup.Update( rect_xs->m_RadiusSymmetryType.GetID() );
            m_RRRadiusBRSlider.Update( rect_xs->m_RadiusBR.GetID() );
            m_RRRadiusBLSlider.Update( rect_xs->m_RadiusBL.GetID() );
            m_RRRadiusTLSlider.Update( rect_xs->m_RadiusTL.GetID() );
            m_RRRadiusTRSlider.Update( rect_xs->m_RadiusTR.GetID() );
            m_RRKeyCornerButton.Update( rect_xs->m_KeyCornerParm.GetID() );
            m_RRSkewSlider.Update( rect_xs->m_Skew.GetID() );
            m_RRKeystoneSlider.Update( rect_xs->m_Keystone.GetID() );
            m_RRVSkewSlider.Update( rect_xs->m_VSkew.GetID() );

            if ( rect_xs->m_RadiusSymmetryType.Get() == vsp::SYM_NONE )
            {
                m_RRRadiusBRSlider.Activate();
                m_RRRadiusBLSlider.Activate();
                m_RRRadiusTLSlider.Activate();
            }
            else if ( rect_xs->m_RadiusSymmetryType.Get() == vsp::SYM_RL )
            {
                m_RRRadiusBRSlider.Activate();
                m_RRRadiusBLSlider.Deactivate();
                m_RRRadiusTLSlider.Deactivate();
            }
            else if ( rect_xs->m_RadiusSymmetryType.Get() == vsp::SYM_TB )
            {
                m_RRRadiusBRSlider.Deactivate();
                m_RRRadiusTLSlider.Activate();
                m_RRRadiusBLSlider.Deactivate();
            }
            else if ( rect_xs->m_RadiusSymmetryType.Get() == vsp::SYM_ALL )
            {
                m_RRRadiusBRSlider.Deactivate();
                m_RRRadiusBLSlider.Deactivate();
                m_RRRadiusTLSlider.Deactivate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_GENERAL_FUSE )
        {
            DisplayGroup( &m_GenGroup );
            GeneralFuseXSec* gen_xs = dynamic_cast< GeneralFuseXSec* >( xsc );
            assert( gen_xs );

            m_GenHeightSlider.Update( gen_xs->m_Height.GetID() );
            m_GenWidthSlider.Update( gen_xs->m_Width.GetID() );
            m_GenMaxWidthLocSlider.Update( gen_xs->m_MaxWidthLoc.GetID() );
            m_GenCornerRadSlider.Update( gen_xs->m_CornerRad.GetID() );
            m_GenTopTanAngleSlider.Update( gen_xs->m_TopTanAngle.GetID() );
            m_GenBotTanAngleSlider.Update( gen_xs->m_BotTanAngle.GetID() );
            m_GenTopStrSlider.Update( gen_xs->m_TopStr.GetID() );
            m_GenBotStrSlider.Update( gen_xs->m_BotStr.GetID() );
            m_GenUpStrSlider.Update( gen_xs->m_UpStr.GetID() );
            m_GenLowStrSlider.Update( gen_xs->m_LowStr.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FOUR_SERIES )
        {
            DisplayGroup( &m_FourSeriesGroup );
            FourSeries* fs_xs = dynamic_cast< FourSeries* >( xsc );
            assert( fs_xs );

            m_FourChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_FourThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_FourCamberSlider.Update( fs_xs->m_Camber.GetID() );
            m_FourCLiSlider.Update( fs_xs->m_IdealCl.GetID() );
            m_FourCamberGroup.Update( fs_xs->m_CamberInputFlag.GetID() );
            if ( fs_xs->m_CamberInputFlag() == vsp::MAX_CAMB )
            {
                m_FourCamberSlider.Activate();
                m_FourCLiSlider.Deactivate();
            }
            else
            {
                m_FourCamberSlider.Deactivate();
                m_FourCLiSlider.Activate();
            }
            m_FourCamberLocSlider.Update( fs_xs->m_CamberLoc.GetID() );
            m_FourInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_FourNameOutput.Update( fs_xs->GetAirfoilName() );
            m_FourSharpTEButton.Update( fs_xs->m_SharpTE.GetID() );
            m_FourDegreeCounter.Update( fs_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_SIX_SERIES )
        {
            DisplayGroup( &m_SixSeriesGroup );
            SixSeries* ss_xs = dynamic_cast< SixSeries* >( xsc );
            assert( ss_xs );

            m_SixChordSlider.Update( ss_xs->m_Chord.GetID() );
            m_SixThickChordSlider.Update( ss_xs->m_ThickChord.GetID() );
            m_SixIdealClSlider.Update( ss_xs->m_IdealCl.GetID() );
            m_SixASlider.Update( ss_xs->m_A.GetID() );

            m_SixInvertButton.Update( ss_xs->m_Invert.GetID() );
            m_SixNameOutput.Update( ss_xs->GetAirfoilName() );
            m_SixSeriesChoice.Update( ss_xs->m_Series.GetID() );
            m_SixDegreeCounter.Update( ss_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_BICONVEX )
        {
            DisplayGroup( &m_BiconvexGroup );
            Biconvex* bi_xs = dynamic_cast< Biconvex* >( xsc );
            assert( bi_xs );

            m_BiconvexChordSlider.Update( bi_xs->m_Chord.GetID() );
            m_BiconvexThickChordSlider.Update( bi_xs->m_ThickChord.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_WEDGE )
        {
            DisplayGroup( &m_WedgeGroup );
            Wedge* we_xs = dynamic_cast< Wedge* >( xsc );
            assert( we_xs );

            m_WedgeChordSlider.Update( we_xs->m_Chord.GetID() );
            m_WedgeThickChordSlider.Update( we_xs->m_ThickChord.GetID() );
            m_WedgeThickLocSlider.Update( we_xs->m_ThickLoc.GetID() );
            m_WedgeZCamberSlider.Update( we_xs->m_ZCamber.GetID() );
            m_WedgeSymmThickButton.Update( we_xs->m_SymmThick.GetID() );
            m_WedgeThickLocLowSlider.Update( we_xs->m_ThickLocLow.GetID() );
            m_WedgeFlatUpSlider.Update( we_xs->m_FlatUp.GetID() );
            m_WedgeFlatLowSlider.Update( we_xs->m_FlatLow.GetID() );
            m_WedgeUForeUpSlider.Update( we_xs->m_UForeUp.GetID() );
            m_WedgeUForeLowSlider.Update( we_xs->m_UForeLow.GetID() );
            m_WedgeDuUpSlider.Update( we_xs->m_DuUp.GetID() );
            m_WedgeDuLowSlider.Update( we_xs->m_DuLow.GetID() );
            m_WedgeInvertButton.Update( we_xs->m_Invert.GetID() );

            if ( we_xs->m_SymmThick() )
            {
                m_WedgeThickLocLowSlider.Deactivate();
                m_WedgeFlatLowSlider.Deactivate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_FILE_FUSE )
        {
            DisplayGroup( &m_FuseFileGroup );
            FileXSec* file_xs = dynamic_cast< FileXSec* >( xsc );
            assert( file_xs );
            m_FileHeightSlider.Update( file_xs->m_Height.GetID() );
            m_FileWidthSlider.Update( file_xs->m_Width.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FILE_AIRFOIL )
        {
            DisplayGroup( &m_AfFileGroup );
            FileAirfoil* affile_xs = dynamic_cast< FileAirfoil* >( xsc );
            assert( affile_xs );

            m_AfFileChordSlider.Update( affile_xs->m_Chord.GetID() );
            m_AfFileThickChordSlider.Update( affile_xs->m_ThickChord.GetID() );
            m_AfFileBaseThickChordOutput.Update( affile_xs->m_BaseThickness.GetID() );
            m_AfFileInvertButton.Update( affile_xs->m_Invert.GetID() );
            m_AfFileNameOutput.Update( affile_xs->GetAirfoilName() );
            m_AfFileDegreeCounter.Update( affile_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
        {
            DisplayGroup( &m_CSTAirfoilGroup );
            CSTAirfoil* cst_xs = dynamic_cast< CSTAirfoil* >( xsc );
            assert( cst_xs );

            int num_up = cst_xs->m_UpDeg() + 1;
            int num_low = cst_xs->m_LowDeg() + 1;

            char str[255];
            sprintf( str, "%d", cst_xs->m_UpDeg() );
            m_UpDegreeOutput.Update( str );
            sprintf( str, "%d", cst_xs->m_LowDeg() );
            m_LowDegreeOutput.Update( str );

            m_CSTChordSlider.Update(cst_xs->m_Chord.GetID());
            m_CSTInvertButton.Update( cst_xs->m_Invert.GetID() );
            m_CSTContLERadButton.Update( cst_xs->m_ContLERad.GetID() );
            m_CSTThickChordOutput.Update( cst_xs->m_ThickChord.GetID() );

            if ( ( m_UpCoeffSliderVec.size() != num_up ) || ( m_LowCoeffSliderVec.size() != num_low ) )
            {
                RebuildCSTGroup( cst_xs );
            }

            for ( int i = 0; i < num_up; i++ )
            {
                Parm *p = cst_xs->m_UpCoeffParmVec[i];
                if ( p )
                {
                    m_UpCoeffSliderVec[i].Update( p->GetID() );
                }
            }

            for ( int i = 0; i < num_low; i++ )
            {
                Parm *p = cst_xs->m_LowCoeffParmVec[i];
                if ( p )
                {
                    m_LowCoeffSliderVec[i].Update( p->GetID() );
                }
            }

            if ( cst_xs->m_ContLERad() && num_low > 0 )
            {
                m_LowCoeffSliderVec[0].Deactivate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_VKT_AIRFOIL )
        {
            DisplayGroup( &m_VKTGroup );
            VKTAirfoil* vkt_xs = dynamic_cast< VKTAirfoil* >( xsc );
            assert( vkt_xs );

            m_VKTChordSlider.Update( vkt_xs->m_Chord.GetID() );
            m_VKTEpsilonSlider.Update( vkt_xs->m_Epsilon.GetID() );
            m_VKTKappaSlider.Update( vkt_xs->m_Kappa.GetID() );
            m_VKTTauSlider.Update( vkt_xs->m_Tau.GetID() );
            m_VKTInvertButton.Update( vkt_xs->m_Invert.GetID() );
            m_VKTDegreeCounter.Update( vkt_xs->m_FitDegree.GetID() );
            m_VKTThickChordOutput.Update( vkt_xs->m_ThickChord.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FOUR_DIGIT_MOD )
        {
            DisplayGroup( &m_FourDigitModGroup );
            FourDigMod* fs_xs = dynamic_cast< FourDigMod* >( xsc );
            assert( fs_xs );

            m_FourModChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_FourModThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_FourModCamberSlider.Update( fs_xs->m_Camber.GetID() );
            m_FourModCLiSlider.Update( fs_xs->m_IdealCl.GetID() );
            m_FourModCamberGroup.Update( fs_xs->m_CamberInputFlag.GetID() );
            if ( fs_xs->m_CamberInputFlag() == vsp::MAX_CAMB )
            {
                m_FourModCamberSlider.Activate();
                m_FourModCLiSlider.Deactivate();
            }
            else
            {
                m_FourModCamberSlider.Deactivate();
                m_FourModCLiSlider.Activate();
            }
            m_FourModCamberLocSlider.Update( fs_xs->m_CamberLoc.GetID() );
            m_FourModInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_FourModNameOutput.Update( fs_xs->GetAirfoilName() );
            m_FourModThicknessLocSlider.Update( fs_xs->m_ThickLoc.GetID() );
            m_FourModLERadIndexSlider.Update( fs_xs->m_LERadIndx.GetID() );
            m_FourModSharpTEButton.Update( fs_xs->m_SharpTE.GetID() );
            m_FourModDegreeCounter.Update( fs_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FIVE_DIGIT )
        {
            DisplayGroup( &m_FiveDigitGroup );
            FiveDig* fs_xs = dynamic_cast< FiveDig* >( xsc );
            assert( fs_xs );

            m_FiveChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_FiveThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_FiveCLiSlider.Update( fs_xs->m_IdealCl.GetID() );
            m_FiveCamberLocSlider.Update( fs_xs->m_CamberLoc.GetID() );
            m_FiveInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_FiveNameOutput.Update( fs_xs->GetAirfoilName() );
            m_FiveSharpTEButton.Update( fs_xs->m_SharpTE.GetID() );
            m_FiveDegreeCounter.Update( fs_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FIVE_DIGIT_MOD )
        {
            DisplayGroup( &m_FiveDigitModGroup );
            FiveDigMod* fs_xs = dynamic_cast< FiveDigMod* >( xsc );
            assert( fs_xs );

            m_FiveModChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_FiveModThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_FiveModCLiSlider.Update( fs_xs->m_IdealCl.GetID() );
            m_FiveModCamberLocSlider.Update( fs_xs->m_CamberLoc.GetID() );
            m_FiveModInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_FiveModNameOutput.Update( fs_xs->GetAirfoilName() );
            m_FiveModThicknessLocSlider.Update( fs_xs->m_ThickLoc.GetID() );
            m_FiveModLERadIndexSlider.Update( fs_xs->m_LERadIndx.GetID() );
            m_FiveModSharpTEButton.Update( fs_xs->m_SharpTE.GetID() );
            m_FiveModDegreeCounter.Update( fs_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_ONE_SIX_SERIES )
        {
            DisplayGroup( &m_OneSixSeriesGroup );
            OneSixSeries* fs_xs = dynamic_cast< OneSixSeries* >( xsc );
            assert( fs_xs );

            m_OneSixSeriesChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_OneSixSeriesThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_OneSixSeriesCLiSlider.Update( fs_xs->m_IdealCl.GetID() );
            m_OneSixSeriesInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_OneSixSeriesNameOutput.Update( fs_xs->GetAirfoilName() );
            m_OneSixSeriesSharpTEButton.Update( fs_xs->m_SharpTE.GetID() );
            m_OneSixSeriesDegreeCounter.Update( fs_xs->m_FitDegree.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_EDIT_CURVE )
        {
            m_EditCEDITGroup.Show();
            m_ConvertCEDITGroup.Hide();
            DisplayGroup( NULL );
        }

        if ( xsc->GetType() != vsp::XS_EDIT_CURVE )
        {
            m_EditCEDITGroup.Hide();
            m_ConvertCEDITGroup.Show();
        }

        m_TECloseChoice.Update( xsc->m_TECloseType.GetID() );
        m_TECloseGroup.Update( xsc->m_TECloseAbsRel.GetID() );

        if ( xsc->m_TECloseType() != vsp::CLOSE_NONE )
        {
            m_TECloseABSButton.Activate();
            m_TECloseRELButton.Activate();
            m_CloseTEThickSlider.Activate();

            if ( xsc->m_TECloseAbsRel() == vsp::ABS )
            {
                xsc->m_TECloseThick.Activate();
                xsc->m_TECloseThickChord.Deactivate();
            }
            else
            {
                xsc->m_TECloseThick.Deactivate();
                xsc->m_TECloseThickChord.Activate();
            }
        }
        else
        {
            m_TECloseABSButton.Deactivate();
            m_TECloseRELButton.Deactivate();
            m_CloseTEThickSlider.Deactivate();
            xsc->m_TECloseThick.Deactivate();
            xsc->m_TECloseThickChord.Deactivate();
        }

        if ( xsc->m_TECloseAbsRel() == vsp::ABS )
        {
            m_CloseTEThickSlider.Update( 1, xsc->m_TECloseThick.GetID(), xsc->m_TECloseThickChord.GetID() );
        }
        else
        {
            m_CloseTEThickSlider.Update( 2, xsc->m_TECloseThick.GetID(), xsc->m_TECloseThickChord.GetID() );
        }

        m_LECloseChoice.Update( xsc->m_LECloseType.GetID() );
        m_LECloseGroup.Update( xsc->m_LECloseAbsRel.GetID() );

        if ( xsc->m_LECloseType() != vsp::CLOSE_NONE )
        {
            m_LECloseABSButton.Activate();
            m_LECloseRELButton.Activate();
            m_CloseLEThickSlider.Activate();

            if ( xsc->m_LECloseAbsRel() == vsp::ABS )
            {
                xsc->m_LECloseThick.Activate();
                xsc->m_LECloseThickChord.Deactivate();
            }
            else
            {
                xsc->m_LECloseThick.Deactivate();
                xsc->m_LECloseThickChord.Activate();
            }
        }
        else
        {
            m_LECloseABSButton.Deactivate();
            m_LECloseRELButton.Deactivate();
            m_CloseLEThickSlider.Deactivate();
            xsc->m_LECloseThick.Deactivate();
            xsc->m_LECloseThickChord.Deactivate();
        }

        if ( xsc->m_LECloseAbsRel() == vsp::ABS )
        {
            m_CloseLEThickSlider.Update( 1, xsc->m_LECloseThick.GetID(), xsc->m_LECloseThickChord.GetID() );
        }
        else
        {
            m_CloseLEThickSlider.Update( 2, xsc->m_LECloseThick.GetID(), xsc->m_LECloseThickChord.GetID() );
        }

        m_TETrimChoice.Update( xsc->m_TETrimType.GetID() );
        m_TETrimGroup.Update( xsc->m_TETrimAbsRel.GetID() );

        m_TrimTEXSlider.Deactivate();
        m_TrimTEThickSlider.Deactivate();
        m_TETrimABSButton.Deactivate();
        m_TETrimRELButton.Deactivate();

        xsc->m_TETrimX.Deactivate();
        xsc->m_TETrimXChord.Deactivate();
        xsc->m_TETrimThickChord.Deactivate();
        xsc->m_TETrimThick.Deactivate();

        if ( xsc->m_TETrimType() != vsp::TRIM_NONE )
        {
            m_TETrimABSButton.Activate();
            m_TETrimRELButton.Activate();
        }

        if ( xsc->m_TETrimType() == vsp::TRIM_X )
        {
            if ( xsc->m_TETrimAbsRel() == vsp::ABS )
            {
                xsc->m_TETrimX.Activate();
            }
            else
            {
                xsc->m_TETrimXChord.Activate();
            }
        }
        else if ( xsc->m_TETrimType() == vsp::TRIM_THICK )
        {
            if ( xsc->m_TETrimAbsRel() == vsp::ABS )
            {
                xsc->m_TETrimThick.Activate();
            }
            else
            {
                xsc->m_TETrimThickChord.Activate();
            }
        }

        if ( xsc->m_TETrimAbsRel() == vsp::ABS )
        {
            m_TrimTEXSlider.Update( 1, xsc->m_TETrimX.GetID(), xsc->m_TETrimXChord.GetID() );
            m_TrimTEThickSlider.Update( 1, xsc->m_TETrimThick.GetID(), xsc->m_TETrimThickChord.GetID() );
        }
        else
        {
            m_TrimTEXSlider.Update( 2, xsc->m_TETrimX.GetID(), xsc->m_TETrimXChord.GetID() );
            m_TrimTEThickSlider.Update( 2, xsc->m_TETrimThick.GetID(), xsc->m_TETrimThickChord.GetID() );
        }

        m_LETrimChoice.Update( xsc->m_LETrimType.GetID() );
        m_LETrimGroup.Update( xsc->m_LETrimAbsRel.GetID() );

        m_TrimLEXSlider.Deactivate();
        m_TrimLEThickSlider.Deactivate();
        m_LETrimABSButton.Deactivate();
        m_LETrimRELButton.Deactivate();

        xsc->m_LETrimX.Deactivate();
        xsc->m_LETrimXChord.Deactivate();
        xsc->m_LETrimThickChord.Deactivate();
        xsc->m_LETrimThick.Deactivate();

        if ( xsc->m_LETrimType() != vsp::TRIM_NONE )
        {
            m_LETrimABSButton.Activate();
            m_LETrimRELButton.Activate();
        }

        if ( xsc->m_LETrimType() == vsp::TRIM_X )
        {
            if ( xsc->m_LETrimAbsRel() == vsp::ABS )
            {
                xsc->m_LETrimX.Activate();
            }
            else
            {
                xsc->m_LETrimXChord.Activate();
            }
        }
        else if ( xsc->m_LETrimType() == vsp::TRIM_THICK )
        {
            if ( xsc->m_LETrimAbsRel() == vsp::ABS )
            {
                xsc->m_LETrimThick.Activate();
            }
            else
            {
                xsc->m_LETrimThickChord.Activate();
            }
        }

        if ( xsc->m_LETrimAbsRel() == vsp::ABS )
        {
            m_TrimLEXSlider.Update( 1, xsc->m_LETrimX.GetID(), xsc->m_LETrimXChord.GetID() );
            m_TrimLEThickSlider.Update( 1, xsc->m_LETrimThick.GetID(), xsc->m_LETrimThickChord.GetID() );
        }
        else
        {
            m_TrimLEXSlider.Update( 2, xsc->m_LETrimX.GetID(), xsc->m_LETrimXChord.GetID() );
            m_TrimLEThickSlider.Update( 2, xsc->m_LETrimThick.GetID(), xsc->m_LETrimThickChord.GetID() );
        }

        m_TECapChoice.Update( xsc->m_TECapType.GetID() );

        m_TECapLengthSlider.Update( xsc->m_TECapLength.GetID() );
        m_TECapOffsetSlider.Update( xsc->m_TECapOffset.GetID() );
        m_TECapStrengthSlider.Update( xsc->m_TECapStrength.GetID() );

        m_TECapLengthSlider.Deactivate();
        m_TECapOffsetSlider.Deactivate();
        m_TECapStrengthSlider.Deactivate();

        switch( xsc->m_TECapType() ){
            case vsp::FLAT_END_CAP:
                break;
            case vsp::ROUND_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                break;
            case vsp::EDGE_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                break;
            case vsp::SHARP_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                m_TECapStrengthSlider.Activate();
                break;
        }

        m_LECapChoice.Update( xsc->m_LECapType.GetID() );

        m_LECapLengthSlider.Update( xsc->m_LECapLength.GetID() );
        m_LECapOffsetSlider.Update( xsc->m_LECapOffset.GetID() );
        m_LECapStrengthSlider.Update( xsc->m_LECapStrength.GetID() );

        m_LECapLengthSlider.Deactivate();
        m_LECapOffsetSlider.Deactivate();
        m_LECapStrengthSlider.Deactivate();

        switch( xsc->m_LECapType() ){
            case vsp::FLAT_END_CAP:
                break;
            case vsp::ROUND_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                break;
            case vsp::EDGE_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                break;
            case vsp::SHARP_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                m_LECapStrengthSlider.Activate();
                break;
        }

        m_AFThetaSlider.Update( xsc->m_Theta.GetID() );
        m_AFScaleSlider.Update( xsc->m_Scale.GetID() );
        m_AFDeltaXSlider.Update( xsc->m_DeltaX.GetID() );
        m_AFDeltaYSlider.Update( xsc->m_DeltaY.GetID() );
        m_AFShiftLESlider.Update( xsc->m_ShiftLE.GetID() );

    }

    return true;
}

void BORScreen::GuiDeviceCallBack( GuiDevice* gui_device )
{
    //==== Find BOR Ptr ====//
    Geom *geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != BOR_GEOM_TYPE )
    {
        return;
    }
    BORGeom *bor_ptr = dynamic_cast< BORGeom * >( geom_ptr );
    assert( bor_ptr );

    if (gui_device == &m_XSecTypeChoice)
    {
        int t = m_XSecTypeChoice.GetVal();
        bor_ptr->SetXSecCurveType( t );

        if ( t == vsp::XS_EDIT_CURVE )
        {
            m_ScreenMgr->ShowScreen( ScreenMgr::VSP_CURVE_EDIT_SCREEN );
        }
    }
    else if ( gui_device == &m_ShowXSecButton )
    {
        m_ScreenMgr->ShowScreen( ScreenMgr::VSP_XSEC_SCREEN );
    }
    else if ( gui_device == &m_ConvertCEDITButton )
    {
        EditCurveXSec* edit_xsec = bor_ptr->ConvertToEdit();

        if ( edit_xsec )
        {
            m_ScreenMgr->ShowScreen( ScreenMgr::VSP_CURVE_EDIT_SCREEN );
        }
    }
    else if ( gui_device == &m_EditCEDITButton )
    {
        m_ScreenMgr->ShowScreen( ScreenMgr::VSP_CURVE_EDIT_SCREEN );
    }
    else if ( gui_device == &m_ReadFuseFileButton  )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_FILE_FUSE  )
            {
                FileXSec* file_xs = dynamic_cast< FileXSec* >( xsc );
                assert( file_xs );
                string newfile = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Fuselage Cross Section"), "*.fxs" );

                file_xs->ReadXsecFile( newfile );
                file_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( gui_device == &m_AfReadFileButton   )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_FILE_AIRFOIL  )
            {
                FileAirfoil* affile_xs = dynamic_cast< FileAirfoil* >( xsc );
                assert( affile_xs );
                string newfile = m_ScreenMgr->GetSelectFileScreen()->FileChooser( _("Airfoil File"), "*.{af,dat}", false  );

                affile_xs->ReadFile( newfile );
                affile_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( gui_device == &m_UpPromoteButton )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
            {
                CSTAirfoil* cst_xs = dynamic_cast<CSTAirfoil*>( xsc );
                assert( cst_xs );

                cst_xs->PromoteUpper();
                cst_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( gui_device == &m_LowPromoteButton )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
            {
                CSTAirfoil* cst_xs = dynamic_cast<CSTAirfoil*>( xsc );
                assert( cst_xs );

                cst_xs->PromoteLower();
                cst_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( gui_device == &m_UpDemoteButton )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
            {
                CSTAirfoil* cst_xs = dynamic_cast<CSTAirfoil*>( xsc );
                assert( cst_xs );

                cst_xs->DemoteUpper();
                cst_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( gui_device == &m_LowDemoteButton )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
            {
                CSTAirfoil* cst_xs = dynamic_cast<CSTAirfoil*>( xsc );
                assert( cst_xs );

                cst_xs->DemoteLower();
                cst_xs->Update();
                bor_ptr->Update();
            }
        }
    }
    else if ( ( gui_device == &m_FourFitCSTButton ) ||
            ( gui_device == &m_SixFitCSTButton ) ||
            ( gui_device == &m_AfFileFitCSTButton ) ||
            ( gui_device == &m_VKTFitCSTButton ) ||
            ( gui_device == &m_FourModFitCSTButton ) ||
            ( gui_device == &m_FiveFitCSTButton ) ||
            ( gui_device == &m_FiveModFitCSTButton ) ||
            ( gui_device == &m_OneSixSeriesFitCSTButton ) )
    {
        XSecCurve* xsc = bor_ptr->GetXSecCurve();
        if ( xsc )
        {
            Airfoil* af_xs = dynamic_cast<Airfoil*>( xsc );

            if ( af_xs )
            {
                VspCurve c = af_xs->GetOrigCurve();
                int deg = af_xs->m_FitDegree();

                //bor_ptr->SetActiveAirfoilType( XS_CST_AIRFOIL );
                bor_ptr->SetXSecCurveType( vsp::XS_CST_AIRFOIL );

                XSecCurve* newxsc = bor_ptr->GetXSecCurve();
                if ( newxsc )
                {
                    if ( newxsc->GetType() == vsp::XS_CST_AIRFOIL )
                    {
                        CSTAirfoil* cst_xs = dynamic_cast<CSTAirfoil*>( newxsc );
                        assert( cst_xs );

                        cst_xs->FitCurve( c, deg );

                        cst_xs->Update();
                        bor_ptr->Update();
                    }
                }
            }
        }
    }

    GeomScreen::GuiDeviceCallBack( gui_device );
}

//==== Non Menu Callbacks ====//
void BORScreen::CallBack( Fl_Widget *w )
{
    GeomScreen::CallBack( w );
}

void BORScreen::DisplayGroup( GroupLayout* group )
{
    if ( m_CurrDisplayGroup == group )
    {
        return;
    }

    m_SuperGroup.Hide();
    m_CircleGroup.Hide();
    m_EllipseGroup.Hide();
    m_RoundedRectGroup.Hide();
    m_GenGroup.Hide();
    m_FourSeriesGroup.Hide();
    m_SixSeriesGroup.Hide();
    m_BiconvexGroup.Hide();
    m_WedgeGroup.Hide();
    m_FuseFileGroup.Hide();
    m_AfFileGroup.Hide();
    m_CSTAirfoilGroup.Hide();
    m_VKTGroup.Hide();
    m_FourDigitModGroup.Hide();
    m_FiveDigitGroup.Hide();
    m_FiveDigitModGroup.Hide();
    m_OneSixSeriesGroup.Hide();

    m_CurrDisplayGroup = group;

    if ( group )
    {
        group->Show();
    }
}


void BORScreen::RebuildCSTGroup( CSTAirfoil* cst_xs)
{
    if ( !cst_xs )
    {
        return;
    }

    if ( !m_CSTUpCoeffScroll || !m_CSTLowCoeffScroll )
    {
        return;
    }

    m_CSTUpCoeffScroll->clear();
    m_CSTUpCoeffLayout.SetGroup( m_CSTUpCoeffScroll );
    m_CSTUpCoeffLayout.InitWidthHeightVals();

    m_UpCoeffSliderVec.clear();

    unsigned int num_up = cst_xs->m_UpDeg() + 1;

    m_UpCoeffSliderVec.resize( num_up );

    for ( int i = 0; i < num_up; i++ )
    {
        m_CSTUpCoeffLayout.AddSlider( m_UpCoeffSliderVec[i], _("AUTO_UPDATE"), 2, "%9.5f" );
    }




    m_CSTLowCoeffScroll->clear();
    m_CSTLowCoeffLayout.SetGroup( m_CSTLowCoeffScroll );
    m_CSTLowCoeffLayout.InitWidthHeightVals();

    m_LowCoeffSliderVec.clear();

    unsigned int num_low = cst_xs->m_LowDeg() + 1;

    m_LowCoeffSliderVec.resize( num_low );


    for ( int i = 0; i < num_low; i++ )
    {
        m_CSTLowCoeffLayout.AddSlider( m_LowCoeffSliderVec[i], _("AUTO_UPDATE"), 2, "%9.5f" );
    }
}
