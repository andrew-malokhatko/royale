namespace Net
{
	class Client
	{
		int mSocket;
		bool mConnected;

	public:
		Client();
		~Client();

		void startConnection(int port = 3490);
		void endConnection();

		void sendPacket(int packetId);
		int receivePacket();

		bool isConnected();
	};
}