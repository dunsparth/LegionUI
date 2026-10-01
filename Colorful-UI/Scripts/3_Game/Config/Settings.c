// Constants.c v3.0.0  —  Configured for The Legion DayZ
static bool StartMainMenu      = false;  // If set to true, the main menu will be forced to show on startup.
static bool ErrorTestScreen    = false; // If set to true, MainMenu boots into the error/dialog test harness (cui.errortest.layout) instead of the normal main menu. Debug/QA only.
static bool NoHints			   = false;  // Hints ON during load screens.
static bool UseImagesets       = false;   // If true, hints.json entries with m_ImageSet/m_ImageName load from the registered `backgrounds` imageset; otherwise m_ImagePath is used.
static bool LoadVideo          = false;  // Loading-screen video OFF.
static bool ShowGameOverOverlay = true;  // Internal runtime flag toggled by DayZPlayerImplement.ShowDeadScreen() to drive the custom game-over overlay in InGameMenu/Respawn. NOT a user-facing config (it is reset each death).

static bool AntiNvidia         = false;  // If set to true, the Anti-NVIDIA Inspector captcha will be shown before connecting.

// The below tend to break right now. Fix with 4.0.0 Update.
static bool EnableMenuVideo    = true;   // Background video on main menu ON (author flags this as possibly buggy — test it).
static bool EnableOptionsVideo = false;  // Background video on options menu (when opened from main menu).
static bool VideoDeathScreens  = false;  // If set to true, a random game over screen will be shown when the player dies.
// static bool RandomDeathScreens = false;  // If set to true, a random game over video that will be shown when the player dies.

// Server Information — The Legion DayZ
static const string SERVER_IP = "104.143.2.218";
static const int SERVER_PORT = 2302;

// Video Settings (Change them up)
static const string m_LoadingVideo     = "CUI_Video.mov";  // Video file name for loading screen video.
static const string m_MainMenuVideo    = "CUI_Video.mov";  // Video file name for Main Menu screen video.
static const string m_OptionsMenuVideo = "CUI_Video.mov";  // Video file name for Options screen video.

// Main Menu Background — picks between imageset sprite and raw .edds
// based on UseImagesets. Edit either side to repoint.
string GetMainMenuBackground()
{
    if (UseImagesets)
        return "set:backgrounds image:mainmenu";
    return "Colorful-UI/GUI/textures/LoadScreens/MainMenu.edds";
}
// Set Single Game Over Screen ( Death Screen )
class GameOverScreen
{
    static string GameOverScreenImage() { return "Colorful-UI/GUI/textures/DeathScreens/DeathScreen.edds"; };
};

// Set Your Servers Logo — The Legion
// Recommended size is 512x512.
class Branding
{
    static string Logo()
    {
        if (UseImagesets)
            return "set:branding image:logo";
        return "Colorful-UI/GUI/textures/Shared/Legion_Logo.paa";
    }
    static void ApplyLogo(ImageWidget widget)
    {
        if (!widget) return;
        widget.LoadImageFile(0, Logo());
        widget.SetFlags(WidgetFlags.STRETCH);
    }
};

// Credits screen
// This must match "DepartmentName" in Colorful-UI/Scripts/Credits.json.
// Rename it in both places if you want your team's credits on top.
static const string CUI_CREDITS_DEPARTMENT = "Colorful-UI";

// Link URLs
// "#" hides the button.
class CustomURL {
    static string Website    = "#";
    static string PriorityQ  = "#";
    static string Custom     = "#";
}

class SocialURL {
    static string Discord    = "https://discord.gg/thelegiondayz";
    static string Facebook   = "#";
    static string Twitter    = "#";
    static string Reddit     = "#";
    static string Youtube    = "#";
}
