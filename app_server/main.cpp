#include "server.hpp"

int main()
{
	Net::Server server = Net::Server();
	server.start();
}