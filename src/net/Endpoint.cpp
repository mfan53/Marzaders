#include "Endpoint.h"

using namespace Arsenal;
using namespace boost::asio;
using namespace boost::asio::ip;

Endpoint::Endpoint( const std::string &ip, uint16_t port )
	: endpoint(address::from_string(ip), port)
{
	
}
