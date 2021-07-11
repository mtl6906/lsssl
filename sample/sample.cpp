#include "ls/net/Client.h"
#include "ls/ssl/Client.h"
#include "ls/io/Factory.h"
#include "ls/http/Request.h"
#include "ls/http/Response.h"
#include "ls/DefaultLogger.h"
#include "iostream"
#include "unistd.h"

using namespace std;
using namespace ls;

int main(int argc, char **argv)
{
	ssl::Client sslClient;
	
	unique_ptr<io::InputStream> in(io::factory.makeInputStream());
	unique_ptr<io::OutputStream> out(io::factory.makeOutputStream());

	for(;;)
	{
	net::Client client(argv[1], stoi(argv[2]));
	int connfd = client.connect();
	unique_ptr<ssl::Connection> connection(sslClient.getConnection(connfd));
	connection -> setHostname("api.huobi.de.com");
	connection -> connect();

	in -> reset(connection -> getReader());
	out -> reset(connection -> getWriter());

	http::Request request;
	request.getMethod() = "GET";
	request.getURL() = argv[3];
	request.getVersion() = "HTTP/1.1";
	request.setDefaultHeader();
	request.setAttribute("Host", "api.huobi.de.com");
	request.setAttribute("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:89.0) Gecko/20100101 Firefox/89.0");

	auto text = request.toString();
	LOGGER(ls::INFO) << "send request: \n" << text << ls::endl;

	out -> append(text);
	out -> write();

	for(;;)
	{
		try
		{
			in -> read();
		}
		catch(Exception &e)
		{
			break;
		}
	}

	LOGGER(ls::INFO) << "read ok" << ls::endl;
	text = in -> split("\r\n\r\n", true);
	LOGGER(ls::INFO) << "find header:\n" << text << ls::endl;
	http::Response response;
	response.parseFrom(text);
	LOGGER(ls::INFO) << "heaer parse ok" << ls::endl;
	response.getBody() = in -> split();
	LOGGER(ls::INFO) << response.getBody() << ls::endl;
	cout << response.getBody() << endl;

	usleep(1000 * 200);

	}

	return 0;
}
