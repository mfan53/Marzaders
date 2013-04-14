#ifndef INC_ARSENAL_NET_HOST_H
#define INC_ARSENAL_NET_HOST_H

#include <boost/asio.hpp>

namespace Arsenal {
	class Host {
	public:	
		static const uint32_t protocolID = (unsigned) 0x16610be1b30c8375;
		
	private:
		friend class Socket;
		boost::asio::io_service ioService;
	};
}

#endif // INC_ARSENAL_NET_HOST_H
