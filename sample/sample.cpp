#include "ls/net/Client.h"
#include "ls/ssl/Client.h"
#include "ls/io/Factory.h"
#include "ls/http/Request.h"
#include "ls/http/Response.h"
#include "ls/DefaultLogger.h"
#include "ls/json/API.h"
#include "iostream"
#include "unistd.h"

using namespace std;
using namespace ls;
class Transacation
{
	public:
		void parseFrom(json::Object &root)
		{
			cout << __LINE__ << endl;
			json::Object tick;
			cout << __LINE__ << endl;
			json::api.get(root, "tick", tick);
			cout << __LINE__ << endl;
			json::Array array;
			cout << __LINE__ << endl;
			json::api.get(tick, "bid", array);
			cout << __LINE__ << endl;
			json::api.get(array, 0, buy);
			cout << __LINE__ << endl;
			json::api.get(tick, "ask", array);
			json::api.get(array, 0, sell);
			cout << __LINE__ << endl;
		}
		double buy;
		double sell;
};

ssl::Client sslClient;

unique_ptr<io::InputStream> in(io::factory.makeInputStream());
unique_ptr<io::OutputStream> out(io::factory.makeOutputStream());

string getinfo(const string &url, const string &host, const string &ip, int port)
{
	net::Client client(ip, port);
	int connfd = client.connect();
	unique_ptr<ssl::Connection> connection(sslClient.getConnection(connfd));
	connection -> setHostname(host);
	connection -> connect();
	
	in -> reset(connection -> getReader());
	out -> reset(connection -> getWriter());

	http::Request request;
	request.getMethod() = "GET";
	request.getURL() = url;
	request.getVersion() = "HTTP/1.1";
	request.setDefaultHeader();
	request.setAttribute("Host", host);
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
	auto rtext = in -> split("\r\n\r\n", true);
	http::Response response;
	response.parseFrom(rtext);
	response.setBody(new StringBody(in -> split, "text/plain"));
	cout << response.getBody() << endl;
	return response.getBody();
}

Transacation getMdxCoin()
{
	Transacation transacation;
	auto root = json::api.decode(getinfo("/market/detail/merged?symbol=mdxusdt", "api.huobi.de.com",  "104.16.231.188", 443));
	transacation.parseFrom(root);
	return transacation;
}

Transacation getMdxContract()
{
	Transacation transacation;
	auto root = json::api.decode(getinfo("/linear-swap-ex/market/detail/merged?contract_code=MDX-USDT", "api.btcgateway.pro", "104.19.166.88", 443));
	transacation.parseFrom(root);
	return transacation;
}

double getBuyOneCoin()
{
		
}	

int main(int argc, char **argv)
{
	for(;;)
	{
		auto t1 = getMdxCoin();
		auto t2 = getMdxContract();
		cout << "buy: " <<  t1.buy << ", "<< t2.buy << endl;
		sleep(1);
	//	cout << "sell: " << t1.sell << ", " << t2.sell << endl;
//		sleep(1);
	}
	return 0;
}
