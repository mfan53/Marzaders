#include "Globals.h"

using namespace Arsenal;
using namespace EventManager;
using namespace std;

EventQueue * Globals::gEventQueue = EventQueue::getEventQueue();
AirTraffic* Globals::airInst;
std::string Globals::mHostIP;