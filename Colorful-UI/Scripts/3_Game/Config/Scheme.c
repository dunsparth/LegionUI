// UI THEME ---------------------------------------------------------------
// The Legion — dark theme with fire accents.
// To change the whole accent color, edit BrandColor() and AccentColor() only.
//   Blood red: BrandColor -> UIColor.legionBloodRed(), AccentColor -> UIColor.cuiSubtleRed()
//   Gold:      BrandColor -> UIColor.legionGold(),     AccentColor -> UIColor.legionEmberDark()
class colorScheme 
{
	// Brand Specific 
	static int BrandColor()          { return UIColor.legionEmber(); }      // Fire orange
	static int AccentColor()         { return UIColor.legionEmberDark(); }  // Burnt orange
	static int TertiaryColor()       { return UIColor.legionAsh(); }        // Warm light grey

	// Base Typography 
	static int PrimaryText()         { return UIColor.White(); }            // Primary text color
	static int SecondaryText()       { return UIColor.legionSmoke(); }      // Subtitles / info text
	static int TextHover()           { return UIColor.legionFlame(); }      // Brighter flame on hover so it pops
	static int DisabledText()        { return ARGB(150, 100, 96, 92); };    // Dim warm grey

	// Global UI Elements 
	static int ButtonHover()         { return BrandColor(); }           	// Button color on hover
	static int Icons()         		 { return BrandColor(); }           	// Primary Color for all icons
	static int LogOutTimer()         { return BrandColor(); }           	// Timer color for logout on logout Screen
	static int Separator()           { return AccentColor(); }          	// Subtler burnt-orange dividers
	static int Loadingbar()          { return BrandColor(); }           	// Loading bar color
	
	// Buttons
	static int BtnText()          { return PrimaryText(); }
	static int BtnHoverText()     { return TextHover(); }
	static int BtnSolidBG()       { return AccentColor(); }                 // Darker solid buttons
	static int BtnSolidHoverBG()  { return BrandColor(); }                  // Light up to full fire on hover
	static int BtnIcon()          { return Icons(); }

	// Tabs
	static int TabIdle()           { return SecondaryText(); }
	static int TabHoverColor()     { return TextHover(); }
	static int TabSelectedColor()  { return BrandColor(); }
	static int TabBackground()     { return UIColor.Black(); }

	// Shader Colors 
	static int TopShader()           {return UIColor.Black();}  			// Top shader on layouts
	static int BottomShader()        {return UIColor.Black();}  			// Bottom shader on layouts

	// Loading Screen
	static int TipText()             { return PrimaryText(); }          	// Main text color for tips
	static int LoadingMsg()          { return TertiaryColor(); }        	// Color for loading messages
	static int TipHeader()           { return BrandColor(); }           	// Header color for tips
	static int TipLine()             { return AccentColor(); }          	// Divider line color in tips

	// Main Menu
	static int NavIcon()             { return BrandColor(); }           	// Navigation icon color
	static int SurvivorBox()         { return UIColor.legionCharcoal(); }	// Background for "Survivor" box
	static int StatsBox()            { return UIColor.legionCharcoal(); }  	// Background for "Stats" box

	// Options Page 
	static int OptionHeaders()       { return BrandColor(); }           	// Header color in options
	static int OptionLine()          { return AccentColor(); }          	// Line under headers
	static int OptionInputColors()   { return BrandColor(); }           	// Input fields color
	static int OptionSliderColors()  { return BrandColor(); }           	// Slider color in options
	static int OptionSelectionText() { return BrandColor(); }           	// Selected text in dropdowns
	static int OptionCaretColors()   { return BrandColor(); }           	// Caret color for dropdowns
	static int OptionIconHover()     { return TextHover(); }
	static int OptionIconNormal()    { return PrimaryText(); }

	static int OptionBGHover()       { return UIColor.legionCoal(); }  	    // Dark ember glow on hovered options
}
