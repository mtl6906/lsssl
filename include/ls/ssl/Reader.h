#ifndef LS_SSL_READER_H
#define LS_SSL_READER_H

#include "ls/io/Reader.h"
#include "openssl/ssl.h"

namespace ls
{
	namespace ssl
	{
		class Reader : public io::Reader
		{
			public:
				Reader(SSL *ssl);
				int read(void *text, int len) override;
				int tryRead(void *text, int len) override;
			protected:
				SSL *ssl;
		};
	}
}

#endif
