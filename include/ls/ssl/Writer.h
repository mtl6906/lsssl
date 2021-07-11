#ifndef LS_SSL_WRITER_H
#define LS_SSL_WRITER_H

#include "ls/io/Writer.h"
#include "openssl/ssl.h"

namespace ls
{
	namespace ssl
	{
		class Writer : public io::Writer
		{
			public:
				Writer(SSL *ssl);
				int write(void *data, int len) override;
				int tryWrite(void *data, int len) override;
			protected:
				SSL *ssl;
		};
	}
}

#endif
