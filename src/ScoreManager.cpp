#include "ScoreManager.h"
#include "BaseApplication.h"
#include <stdio.h>

using namespace Arsenal;
using namespace EventManager;

int ScoreManager::p1Score = 0;
int ScoreManager::p2Score = 0;
int ScoreManager::numPlayed = 0;
Sound * ScoreManager::mSound;

/*
ScoreManager::ScoreManager() {
	reset();
}

ScoreManager::ScoreManager(EventManager::EventQueue* eq): eventQueue(eq) {
	reset();
}

ScoreManager::~ScoreManager() {
	// Nothing to do
}
*/

void ScoreManager::netP1UpdateScore(EventManager::score_t delta) {
	if (delta == EventManager::PLUS_ONE)
		p1Score += 1;
	else
		p1Score += -3;
	mSound->play(0);
}

void ScoreManager::netP2UpdateScore(EventManager::score_t delta) {
	if (delta == EventManager::PLUS_ONE)
		p2Score += 1;
	else
		p2Score += -3;
	mSound->play(0);
}

void ScoreManager::p1UpdateScore(int delta) {
	mSound->play(0);
	/*
	if (delta == 1)
		eventQueue->add(createScoreEvent(0, PLUS_ONE));
	else
		eventQueue->add(createScoreEvent(0, MINUS_THREE));
	*/
}

void ScoreManager::p2UpdateScore(int delta) {
	mSound->play(0);
	/*
	if (delta == 1)
		eventQueue->add(createScoreEvent(1, PLUS_ONE));
	else
		eventQueue->add(createScoreEvent(1, MINUS_THREE));
	*/
}

void ScoreManager::reset() {
	p1Score = 0;
	p2Score = 0;
	numPlayed = 0;
}
