#include "common.h"
#include "Socket.h"
#include "Event.h"

class GameSocket : public ConnectSocket
{
    public:
        GameSocket(SocketHandler *h) : ConnectSocket(h) {}
        GameSocket(SocketHandler *h, const TCPsocket &s) : ConnectSocket(h, s) {}

        void onReadData(PacketHandlerBase *&, Packet &packet) {
            switch(packet.getOpcode()) {
                case '0': 
                    break;
                default:
                    disconnect();
            }
        }

        void onDisconnect()
        {
            
        }
    private:

};

/** The socket that listens for incoming connections */
class GameListenSocket : public ListenSocket
{
    public:
        GameListenSocket(SocketHandler *h) : ListenSocket(h) {}
        ConnectSocket* onConnect(TCPsocket &socket)
        {
            return new GameSocket(NULL, socket);
        }
};

class GameSocketHandler : public SocketHandler, public Updatable
{
    public:
        GameSocketHandler() : SocketHandler(), _updateEv(0, 20, this) {}
        void Update() { update(); }
    private:
        UpdateEvent _updateEv;
};

void nettest()
{
    GameSocketHandler gameSocketHandler;
    gameSocketHandler.initialize(32000);

    GameSocket * connectSocket = new GameSocket(&gameSocketHandler);
    connectSocket->connect("127.0.0.1", 1234);

    GameListenSocket * listenSocket = new GameListenSocket(&gameSocketHandler);
    listenSocket->listen(1234);
}