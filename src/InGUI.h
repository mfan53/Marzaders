#ifndef INC_ARSENAL_INGUI_H
#define INC_ARSENAL_INGUI_H


#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Arsenal {
	class InGUI {
	public:
		InGUI();
		virtual ~InGUI();
		void create();
		void launch();
		void hide();
		bool resume(const CEGUI::EventArgs &e);
		bool quit(const CEGUI::EventArgs &e);
		bool soundToggle(const CEGUI::EventArgs &e);
	private:
		CEGUI::Window *window;
		static const float button_xsize_ingame = 0.15;
		static const float button_ysize_ingame = 0.05;
		static const float button_xpos_ingame = 0.0;
		static const float button_ypos_ingame = 0.0;
		static const float yspread = 0.08;
		static const float xwindow = 0.42;
		static const float ywindow = 0.35;
	};
}

#endif // INC_ARSENAL_INGUI_H
