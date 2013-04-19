#include "Socket.h"
#include "Host.h"

using namespace Arsenal;
using namespace boost::asio;
using namespace boost::asio::ip;

Socket::Socket(Host &host)
	: m_socket(host.m_ioService)
{
	m_open = false;
}

Socket::~Socket() {
	close();
}

bool Socket::open(const uint16_t port) {
	m_socket.open(udp::v4());	
	m_socket.bind(udp::endpoint(udp::v4(), port));
	m_open = true;
	return true;
}

void Socket::close() {
	m_socket.close();
	m_open = false;
}

bool Socket::send(const Endpoint &dest, const char *data, const size_t size) {
	m_socket.send_to(buffer(data, size), dest.m_endpoint);
	return true;
}

size_t Socket::receive(Endpoint &sender, char *data, const size_t size) {
	if (m_socket.available() == 0)
		return 0;
	return m_socket.receive_from(buffer(data, size), sender.m_endpoint);
}
