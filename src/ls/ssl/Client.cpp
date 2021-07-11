#include "ls/ssl/Client.h"
#include "ls/net/Client.h"
#include "openssl/err.h"
#include "ls/Exception.h"

using namespace std;

namespace ls
{
	namespace ssl
	{
		Client::Client()
		{
			SSL_library_init();
			OpenSSL_add_all_algorithms();
			SSL_load_error_strings();
			ctx = SSL_CTX_new(SSLv23_client_method());
			if(ctx == nullptr)
			{
				ERR_print_errors_fp(stdout);
				throw Exception(Exception::LS_EALLOCATE);
			}
		}

		Client::~Client()
		{
			SSL_CTX_free(ctx);
		}
 
		Connection* Client::getConnection(int fd)
		{
			return new Connection(SSL_new(ctx), fd);
		}
	}
}
