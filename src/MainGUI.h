#ifndef INC_ARSENAL_MAINGUI_H
#define INC_ARSENAL_MAINGUI_H


#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Arsenal {
	class MainGUI {
	public:
		MainGUI();
		virtual ~MainGUI();
		void launch();
		void hide();
		void show();
		bool start(const CEGUI::EventArgs &e);
		bool multi(const CEGUI::EventArgs &e);
		bool quit(const CEGUI::EventArgs &e);
		bool soundToggle(const CEGUI::EventArgs &e);
		bool handleIP(const CEGUI::EventArgs &e);
	private:
		CEGUI::Window *window;
		CEGUI::Editbox* ipbox;
		static const float button_xsize_main = 0.3;
		static const float button_ysize_main = 0.09;
		static const float button_xpos_main = 0.35;
		static const float button_ypos_main = 0.35;
		static const float yspread = 0.1;
		static const float ip_xsize = 0.35;
		static const float ip_ysize = 0.1;
		static const float ip_x = 0.31;
		static const float ip_y = 0.42;
	};
}

#endif // INC_ARSENAL_MAINGUI_H

