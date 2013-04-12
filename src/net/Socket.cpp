#include "Socket.h"
#include "Host.h"

using namespace Arsenal;
using namespace boost::asio;
using namespace boost::asio::ip;

Socket::Socket(Host &host)
	: socket(host.ioService)
{
	mOpen = false;
}

Socket::~Socket() {
	close();
}

bool Socket::open(uint16_t port) {
	socket.open(udp::v4());	
	socket.bind(udp::endpoint(udp::v4(), port));
	mOpen = true;
	return true;
}

void Socket::close() {
	socket.close();
	mOpen = false;
}

bool Socket::send( const Endpoint &dest, const char *data, size_t size ) {
	socket.send_to(buffer(data, size), dest.endpoint);
	return true;
}

size_t Socket::receive(Endpoint &sender, char *data, size_t size) {
	if (socket.available() == 0)
		return 0;
	return socket.receive_from(buffer(data, size), sender.endpoint);
}
