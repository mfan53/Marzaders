#ifndef INC_ARSENAL_NET_ENDPOINT_H
#define INC_ARSENAL_NET_ENDPOINT_H

#include <boost/asio.hpp>
#include <string>

namespace Arsenal
{
	class Endpoint {
	public:
		Endpoint() {};
		Endpoint(const std::string &ip, uint16_t port);
	
		std::string getIP() { return m_endpoint.address().to_string(); }

	private:
		friend class Socket;
		
		boost::asio::ip::udp::endpoint m_endpoint;
	};
}

#endif // INC_ARSENAL_NET_ENDPOINT_H
