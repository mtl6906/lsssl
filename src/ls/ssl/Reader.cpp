#include "ls/ssl/Reader.h"
#include "ls/Exception.h"

namespace ls
{
	namespace ssl
	{
		Reader::Reader(SSL *ssl) : ssl(ssl)
		{
		
		}
			
		int Reader::read(void *data, int len)
		{
			int n = SSL_read(ssl, data, len);
			if(n < 0)
				throw Exception(Exception::LS_ERECV);
			if(n == 0)
				throw Exception(Exception::LS_EEOF);
			return n;
		}

		int Reader::tryRead(void *data, int len)
		{
			return read(data, len);
		}
	}
}
