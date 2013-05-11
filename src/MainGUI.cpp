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

	//single player button
	CEGUI::Window *single = wmgr.createWindow("TaharezLook/Button","CEGUI/SinglePlayer");
	single->setText("Start Game");
	single->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_main,0),CEGUI::UDim(button_ysize_main,0)));
	single->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_main,0),CEGUI::UDim(button_ypos_main + (0 * yspread),0)));
	window->addChildWindow(single);
	single->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGUI::start, this));

	//multi player button
	/*CEGUI::Window *multi = wmgr.createWindow("TaharezLook/Button","CEGUI/MultiPlayer");
	multi->setText("Multi Player");
	multi->setSize(CEGUI::UVector2(CEGUI::UDim(button_xsize_main,0),CEGUI::UDim(button_ysize_main,0)));
	multi->setPosition(CEGUI::UVector2(CEGUI::UDim(button_xpos_main,0),CEGUI::UDim(button_ypos_main + (1 * yspread),0)));
	window->addChildWindow(multi);
	multi->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGUI::multi, this));*/

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
	hide();
	return true;
}

bool MainGUI::multi(const CEGUI::EventArgs &e) {
	Globals::airInst->inIP();
	//pop up edit box for ip
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	ipbox = (CEGUI::Editbox*)wmgr.createWindow("TaharezLook/Editbox","CEGUI/Editbox");
	ipbox->enable();
	ipbox->setPosition(CEGUI::UVector2(CEGUI::UDim(ip_x,0),CEGUI::UDim(ip_y,0)));
	ipbox->setSize(CEGUI::UVector2(CEGUI::UDim(ip_xsize,0),CEGUI::UDim(ip_ysize,0)));
	ipbox->setMaxTextLength(15);
	ipbox->setReadOnly(false);
	ipbox->setText("127.0.0.1");
	window->addChildWindow(ipbox);
	ipbox->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber(&MainGUI::handleIP, this));
	return true;
}

bool MainGUI::handleIP(const CEGUI::EventArgs &e) {	
	CEGUI::String str = ipbox->getText();
	std::string ip = str.c_str();
	Globals::mHostIP = ip;
	ipbox->hide();
	ipbox->disable();
	Globals::airInst->outIP();
	ipbox->destroy();
	hide();
	return true;
}

void MainGUI::hide() {
	window->hide();
	window->disable();
	CEGUI::MouseCursor::getSingleton().hide();
	Globals::airInst->startGame();
}

void MainGUI::show() {
	window->show();
	window->enable();
	CEGUI::MouseCursor::getSingleton().show();
	CEGUI::System::getSingleton().setGUISheet(window);
}

bool MainGUI::quit(const CEGUI::EventArgs &e) {
	Globals::airInst->quitGame();
	return true;
}

bool MainGUI::soundToggle(const CEGUI::EventArgs &e) {
	Globals::airInst->soundToggle();
	return true;
}
