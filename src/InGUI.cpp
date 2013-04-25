#include "InGUI.h"
#include "Globals.h"

using namespace Arsenal;

InGUI::InGUI() {
	//load scheme for gui
	//sheet
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");
}

InGUI::~InGUI() {
}

void InGUI::create() {
	//main menu window
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	window = wmgr.createWindow("DefaultWindow","InGameSheet");
	window->setPosition(CEGUI::UVector2(CEGUI::UDim(xwindow,0),CEGUI::UDim(ywindow,0)));

	//resume game button
	CEGUI::Window *resume = wmgr.createWindow("TaharezLook/Button","CEGUI/ResumeButton");
	resume->setText("Resume Game");
	resume->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_ingame, 0), CEGUI::UDim(button_ysize_ingame, 0)));
	resume->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_ingame,0),CEGUI::UDim(button_ypos_ingame + (0 * yspread),0)));
	window->addChildWindow(resume);
	resume->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InGUI::resume, this));

	//sound toggle button
	CEGUI::Window *sound = wmgr.createWindow("TaharezLook/Button","CEGUI/SoundToggleButton");
	sound->setText("Sound Toggle");
	sound->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_ingame, 0), CEGUI::UDim(button_ysize_ingame, 0)));
	sound->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_ingame ,0),CEGUI::UDim(button_ypos_ingame + (1 * yspread),0)));
	window->addChildWindow(sound);
	sound->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InGUI::soundToggle, this));

	//exit game button
	CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button","CEGUI/QuitButton");
	quit->setText("Quit Game");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_ingame,0),CEGUI::UDim(button_ysize_ingame,0)));
	quit->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_ingame,0),CEGUI::UDim(button_ypos_ingame + (2 * yspread),0)));
	window->addChildWindow(quit);
	quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InGUI::quit, this));
}

void InGUI::launch() {
	//show the mouse cursor
	CEGUI::MouseCursor::getSingleton().show();
	window->enable();
	window->show();
	CEGUI::System::getSingleton().setGUISheet(window);
}

void InGUI::hide() {
	window->disable();
	window->hide();
	CEGUI::MouseCursor::getSingleton().hide();
}

bool InGUI::resume(const CEGUI::EventArgs &e) {
	window->hide();
	window->disable();
	CEGUI::MouseCursor::getSingleton().hide();
	Globals::airInst->hideIngame();
	return true;
}

bool InGUI::quit(const CEGUI::EventArgs &e) {
	Globals::airInst->quitGame();
	return true;
}

bool InGUI::soundToggle(const CEGUI::EventArgs &e) {
	Globals::airInst->soundToggle();
	return true;
}
