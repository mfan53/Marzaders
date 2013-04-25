#include "MainGUI.h"
#include "Globals.h"

using namespace Arsenal;

MainGUI::MainGUI() {
	//load scheme for gui
	//background image
	CEGUI::Imageset& MenuImageset = CEGUI::ImagesetManager::getSingleton().createFromImageFile("Background","minecraft.png");
	//sheet
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook","MouseArrow");
}

MainGUI::~MainGUI() {
}

void MainGUI::launch() {
	//main menu window
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	window = wmgr.createWindow("TaharezLook/StaticImage","Background");
	window->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
	window->setProperty("Image","set:Background image:full_image");

	//start game
	CEGUI::Window *start = wmgr.createWindow("TaharezLook/Button","CEGUI/StartGameBt");
	start->setText("Start Game");
	start->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_main, 0), CEGUI::UDim(button_ysize_main, 0)));
	start->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_main,0),CEGUI::UDim(button_ypos_main + (0 * yspread),0)));
	window->addChildWindow(start);
	start->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGUI::start, this));

	//sound toggle button
	CEGUI::Window *sound= wmgr.createWindow("TaharezLook/Button","CEGUI/SoundToggleBtMain");
	sound->setText("Sound Toggle");
	sound->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_main, 0), CEGUI::UDim(button_ysize_main, 0)));
	sound->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_main,0),CEGUI::UDim(button_ypos_main + (1 * yspread),0)));
	window->addChildWindow(sound);
	sound->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGUI::soundToggle, this));

	//exit game button
	CEGUI::Window *quitMain = wmgr.createWindow("TaharezLook/Button","CEGUI/QuitButtonMain");
	quitMain->setText("Quit Game");
	quitMain->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_main,0),CEGUI::UDim(button_ysize_main,0)));
	quitMain->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_main,0),CEGUI::UDim(button_ypos_main + (2 * yspread),0)));
	window->addChildWindow(quitMain);
	quitMain->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGUI::quit, this));

	CEGUI::System::getSingleton().setGUISheet(window);
}

bool MainGUI::start(const CEGUI::EventArgs &e) {
	window->hide();
	window->disable();
	CEGUI::MouseCursor::getSingleton().hide();
	return true;
}

bool MainGUI::quit(const CEGUI::EventArgs &e) {
	Globals::airInst->quitGame();
	return true;
}

bool MainGUI::soundToggle(const CEGUI::EventArgs &e) {
	Globals::airInst->soundToggle();
	return true;
}
