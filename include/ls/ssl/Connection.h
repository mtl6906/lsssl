#ifndef LS_SSL_CONNECTION_H
#define LS_SSL_CONNECTION_H

#include "ls/ssl/Writer.h"
#include "ls/ssl/Reader.h"
#include "ls/net/Socket.h"
#include "string"

namespace ls
{
	namespace ssl
	{
		class Connection
		{
			public:
				Connection(SSL *ssl, int fd);
				~Connection();
				void setHostname(const std::string &hostname);
				void connect();
				Reader *getReader();
				Writer *getWriter();
			protected:
				SSL *ssl;
				net::Socket *sock;
		};
	}
}

#endif
