#include "ls/ssl/Connection.h"
#include "ls/Exception.h"
#include "openssl/err.h"
#include "openssl/ssl.h"

using namespace std;

namespace ls
{
	namespace ssl
	{
		Connection::Connection(SSL *ssl, int fd) : ssl(ssl), sock(new net::Socket(fd))
		{
			SSL_set_fd(ssl, fd);
		}

		Connection::~Connection()
		{
			SSL_shutdown(ssl);
			SSL_free(ssl);
			delete sock;
		}

		void Connection::setHostname(const string &hostname)
		{
			SSL_set_tlsext_host_name(ssl, hostname.c_str());	
		}

		void Connection::connect()
		{
			if(SSL_connect(ssl) < 0)
			{
				ERR_print_errors_fp(stdout);
				throw Exception(Exception::LS_ECONN);
			}
		}

		Reader* Connection::getReader()
		{
			return new Reader(ssl);
		}

		Writer* Connection::getWriter()
		{
			return new Writer(ssl);
		}
	}
}
