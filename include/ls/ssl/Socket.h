#ifndef LS_SSL_CONNECTION_H
#define LS_SSL_CONNECTION_H

#include "ls/ssl/Reader.h"
#include "ls/ssl/Writer.h"
#include "openssl/ssl.h"

namespace ls
{
	namespace ssl
	{
		class Connection
		{
			public:
				Connection(SSL *ssl);
				Reader *getReader();
				Reader *getWriter();		
			protected:
				SSL *ssl;
		};
	}
}

#endif
