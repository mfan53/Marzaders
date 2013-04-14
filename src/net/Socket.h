#ifndef INC_ARSENAL_NET_SOCKET_H
#define INC_ARSENAL_NET_SOCKET_H

#include <stdint.h>
#include <boost/asio.hpp>

#include "Endpoint.h"

namespace Arsenal {
	class Host;

	class Socket {
	public:
		Socket(Host &host);
		~Socket();
	
		bool open(const uint16_t port);
		void close();
		
		bool send(const Endpoint &dest, const char *data, const size_t size);
		size_t receive(Endpoint &sender, char *data, const size_t size);

		bool isOpen() { return mOpen; };
	
	private:
		boost::asio::ip::udp::socket socket;

		bool m_open;
	};
}

#endif // INC_ARSENAL_NET_SOCKET_H
