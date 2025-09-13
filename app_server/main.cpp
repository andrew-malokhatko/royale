#include "server.hpp"

int main()
{
	net::Server server = net::Server();
	server.start();
}