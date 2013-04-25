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
		bool start(const CEGUI::EventArgs &e);
		bool quit(const CEGUI::EventArgs &e);
		bool soundToggle(const CEGUI::EventArgs &e);
	private:
		CEGUI::Window *window;
		static const float button_xsize_main = 0.2;
		static const float button_ysize_main = 0.07;
		static const float button_xpos_main = 0.4;
		static const float button_ypos_main = 0.4;
		static const float yspread = 0.1;
	};
}

#endif // INC_ARSENAL_MAINGUI_H

