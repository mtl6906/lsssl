#include "ls/ssl/Writer.h"
#include "ls/Exception.h"

namespace ls
{
	namespace ssl
	{
		Writer::Writer(SSL *ssl) : ssl(ssl)
		{
		
		}

		int Writer::write(void *data, int len)
		{
			int n = SSL_write(ssl, data, len);
			if(n < 0)
				throw Exception(Exception::LS_ESEND);
			return n;
		}

		int Writer::tryWrite(void *data, int len)
		{
			return write(data, len);
		}
	}
}
