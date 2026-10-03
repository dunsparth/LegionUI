// TabberUI — CUI tab controls and foreign-mod tab adoption.
// Vanilla source: P:\scripts\5_mission\gui\newui\tabberprefab\tabberui.c

modded class TabberUI
{
	static bool s_CuiRecordForeignTabs = false;
	static ref array<int>    s_CuiForeignTabIndices = new array<int>();
	static ref array<string> s_CuiForeignTabNames    = new array<string>();

	// ---- Legion: mod-tab filter -------------------------------------------
	// Only mod tabs listed here get a visible button in the options menu.
	// Add more names to show other mod tabs, e.g. {"HUD", "EXPANSION"}.
	// Hidden tabs still exist (so their mods don't break), they just have no button.
	protected bool m_CuiFilterTabs = false;
	protected ref array<Widget> m_CuiOwnControls = new array<Widget>();   // tab buttons built with the CUI layout

	void CuiEnableTabFilter()
	{
		m_CuiFilterTabs = true;
	}

	bool CuiIsTabAllowed(string name)
	{
		if (!m_CuiFilterTabs)
			return true;

		array<string> allowed = {"HUD"};

		string n = name;
		n.ToUpper();
		foreach (string a : allowed)
		{
			string au = a;
			au.ToUpper();
			if (n == au)
				return true;
		}
		return false;
	}
	// Catches tab buttons other mods (e.g. Expansion) build themselves,
	// bypassing CUI's AddTab. DayZ can't read text back from a TextWidget,
	// so mod tabs are recognised by a widget inside their page instead.
	// Allowed ones get re-skinned with the CUI button (CUI font), the rest are hidden.
	// builtInCount = CUI's own tabs from the layout (GAME/AUDIO/VIDEO/CONTROLS = 4).
	protected int m_CuiFilterPasses = 0;
	protected int m_CuiLastCount = -1;

	// Returns the tab title to show if this page belongs to an allowed mod, else "".
	// To allow another mod tab, add a line with a widget name from its page.
	protected string CuiAllowedTitleForPane(Widget pane)
	{
		if (!pane)
			return "";

		if (pane.FindAnyWidget("CHOptRoot"))   // REZ_CustomHUD (The Legion HUD)
			return "HUD";

		return "";
	}

	void CuiFilterModTabs(int builtInCount)
	{
		if (!m_CuiFilterTabs || !m_TabControls || !m_Tabs)
			return;

		int count = m_TabControls.Count();
		if (count != m_CuiLastCount)
		{
			m_CuiLastCount = count;
			m_CuiFilterPasses = 0;
		}
		if (m_CuiFilterPasses > 120)   // settle after ~2 seconds, re-check when tabs are added
			return;
		m_CuiFilterPasses++;

		bool changed = false;
		for (int i = builtInCount; i < count; i++)
		{
			Widget c = m_TabControls.Get(i);
			if (!c || m_CuiOwnControls.Find(c) != -1)
				continue;   // built by CUI; already filtered by name in AddTab/CuiAdoptTab

				string title = CuiAllowedTitleForPane(m_Tabs.Get(i));
			if (title != "")
			{
				CuiReskinTabControl(i, title);   // swap in a CUI-styled button
				changed = true;
			}
			else if (c.IsVisible())
			{
				c.Show(false);
				changed = true;
			}
		}

		if (changed)
			AlignTabbers();
	}
	// -----------------------------------------------------------------------

	void CuiCancelInitTimer()
	{
		if (m_InitTimer)
			m_InitTimer.Stop();
	}

	int CuiAdoptTab(string name, Widget pane)
	{
		int new_index = m_Tabs.Count();

		Widget control = GetGame().GetWorkspace().CreateWidgets( "Colorful-UI/GUI/layouts/components/tabber_prefab/cui.tab_control.layout", m_Root.FindAnyWidget( "Tab_Control_Container" ) );
		TextWidget control_text = TextWidget.Cast( control.FindAnyWidget( "Tab_Control_x_Title" ) );

		pane.SetName( "Tab_" + new_index );
		m_Root.AddChild( pane );

		control.SetName( "Tab_Control_" + new_index );
		control_text.SetName( "Tab_Control_" + new_index + "_Title" );
		control.FindAnyWidget( "Tab_Control_x_Background" ).SetName( "Tab_Control_" + new_index + "_Background" );

		control_text.SetText( name );

		if ( !CuiIsTabAllowed( name ) )
			control.Show( false );

		control.SetHandler( this );
		m_CuiOwnControls.Insert( control );
		m_TabControls.Insert( new_index, control );
		m_Tabs.Insert( new_index, pane );

		AlignTabbers();

		return new_index;
	}

	override void AlignTabbers()
	{
		float total_size;
		float x, y;

		Widget tab_controls_container = m_TabControlsRoot.FindAnyWidget( "Tab_Control_Container" );
		Widget tab_controls_scroller  = m_TabControlsRoot.FindAnyWidget( "Tab_Control_Scroller" );

		m_TabControlsRoot.Update();
		tab_controls_container.Update();

		Widget tab_child = tab_controls_container.GetChildren();
		while ( tab_child )
		{
			if ( tab_child.IsVisible() )
			{
				TextWidget tab_text = TextWidget.Cast( tab_child.FindAnyWidget( tab_child.GetName() + "_Title" ) );
				int t_x, t_y;
				tab_text.Update();
				tab_text.GetTextSize( t_x, t_y );

				float tab_width = t_x + 20;
				tab_child.SetSize( tab_width, 1 );

				tab_controls_container.Update();

				total_size += tab_width;
			}

			tab_child = tab_child.GetSibling();
		}

		tab_controls_container.SetSize(total_size, 1);
		tab_child = tab_controls_container.GetChildren();

		float x_f_c, y_f_c;
		tab_controls_container.GetScreenPos( x_f_c, y_f_c );

		while ( tab_child )
		{
			Widget tab_bg = tab_child.FindAnyWidget( tab_child.GetName() + "_Background" );
			tab_child.GetScreenPos( x, y );
			tab_bg.SetPos( ( x_f_c - x ), 0 );

			tab_bg.SetSize( total_size, 1 );

			tab_child = tab_child.GetSibling();
		}

		tab_controls_container.Update();
		if ( tab_controls_scroller )
			tab_controls_scroller.Update();
		m_TabControlsRoot.Update();
	}

	override void SelectTabControl( int index )
	{
		Widget tab_control = m_TabControls.Get( index );
		if( tab_control )
		{
			Widget tab_title = TextWidget.Cast(tab_control.FindAnyWidget( tab_control.GetName() + "_Title" ));

			int color_title = colorScheme.TabHoverColor();
			int color_backg = UIColor.Black();

			tab_title.SetColor( color_title );
			tab_control.SetColor( color_backg );
		}
	}

	override bool OnMouseEnter( Widget w, int x, int y )
	{
		int index = m_TabControls.GetKeyByValue( w );
		if( m_SelectedIndex == index )
		{
			return false;
		}

		Widget tab_control = m_TabControls.Get( index );
		if( tab_control )
		{
			Widget tab_title = TextWidget.Cast(tab_control.FindAnyWidget( tab_control.GetName() + "_Title" ));
			tab_title.SetColor(colorScheme.TabHoverColor());
			tab_control.SetColor(UIColor.Black());
		}

		return false;
	}

	void CuiReskinTabControl( int index, string name )
	{
		Widget old_control = m_TabControls.Get( index );
		if ( !old_control )
			return;

		Widget container = m_TabControlsRoot.FindAnyWidget( "Tab_Control_Container" );
		if ( !container )
			return;

		string cname = old_control.GetName();

		Widget control = GetGame().GetWorkspace().CreateWidgets( "Colorful-UI/GUI/layouts/components/tabber_prefab/cui.tab_control.layout", container );
		TextWidget control_text = TextWidget.Cast( control.FindAnyWidget( "Tab_Control_x_Title" ) );

		control.SetName( cname );
		control_text.SetName( cname + "_Title" );
		control.FindAnyWidget( "Tab_Control_x_Background" ).SetName( cname + "_Background" );
		control_text.SetText( name );
		control.SetHandler( this );
		m_CuiOwnControls.Insert( control );

		m_TabControls.Set( index, control );
		old_control.Unlink();

		if ( index == m_SelectedIndex )
			SelectTabControl( index );

		AlignTabbers();
	}

	override int AddTab( string name )
	{
		int new_index = m_Tabs.Count();
		Widget tab = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/tabber_prefab/tab.layout", m_Root );
		Widget control = GetGame().GetWorkspace().CreateWidgets( "Colorful-UI/GUI/layouts/components/tabber_prefab/cui.tab_control.layout", m_Root.FindAnyWidget( "Tab_Control_Container" ) );
		TextWidget control_text = TextWidget.Cast( control.FindAnyWidget( "Tab_Control_x_Title" ) );

		tab.SetName( "Tab_" + new_index );
		control.SetName( "Tab_Control_" + new_index );
		control_text.SetName( "Tab_Control_" + new_index + "_Title" );
		control.FindAnyWidget( "Tab_Control_x_Background" ).SetName( "Tab_Control_" + new_index + "_Background" );

		control_text.SetText( name );

		if ( !CuiIsTabAllowed( name ) )
			control.Show( false );

		control.SetHandler( this );
		m_CuiOwnControls.Insert( control );
		m_TabControls.Insert( new_index, control );
		m_Tabs.Insert( new_index, tab );

		AlignTabbers();

		if ( s_CuiRecordForeignTabs )
		{
			s_CuiForeignTabIndices.Insert( new_index );
			s_CuiForeignTabNames.Insert( name );
		}

		return new_index;
	}
}
