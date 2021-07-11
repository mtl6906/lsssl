#ifndef LS_SSL_CLIENT_H
#define LS_SSL_CLEINT_H

#include "string"
#include "ls/ssl/Connection.h"

namespace ls
{
	namespace ssl
	{
		class Client
		{
			public:
				Client();
				~Client();
				Connection* getConnection(int fd);
			protected:
				SSL_CTX *ctx;
		};
	}
}

#endif
