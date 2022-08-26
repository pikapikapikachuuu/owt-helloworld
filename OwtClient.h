#ifndef OWT_CLIENT_H
#define OWT_CLIENT_H

#include "owt/p2p/p2pclient.h"
#include "OwtSignalingChannel.h"

using namespace owt::p2p;
using namespace owt::base;

class OwtClient: P2PClientObserver {
public:
	explicit OwtClient();
	void connect(std::string url, std::string token);

	virtual void OnMessageReceived(const std::string& remote_user_id, const std::string message);
	virtual void OnStreamAdded(std::shared_ptr<RemoteStream> stream);
	virtual void OnServerDisconnected();

private:
	P2PClientConfiguration configuration_;
	std::shared_ptr<P2PClient> client_;
	std::shared_ptr<OwtSignalingChannel> signaling_channel_;
	int msgCount;
};

#endif