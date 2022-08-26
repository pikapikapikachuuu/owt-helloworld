#include <iostream>
#include "OwtClient.h"

OwtClient::OwtClient() : msgCount(0) {
  VideoCodecParameters video_codes_params;
  video_codes_params.name = VideoCodec::kUnknown;
  VideoEncodingParameters video_encoding_parmas(video_codes_params, 0, false);
  configuration_.video_encodings.push_back(video_encoding_parmas);

  AudioCodecParameters audio_codes_params;
  audio_codes_params.name = AudioCodec::kUnknown;
  AudioEncodingParameters audi_encoding_parmas(audio_codes_params, 0);
  configuration_.audio_encodings.push_back(audi_encoding_parmas);

  IceServer ice_server;
  ice_server.urls.push_back("stun.lowratevoip.com:3478");
  configuration_.ice_servers.push_back(ice_server);
  ice_server.urls.clear();
  ice_server.urls.push_back("turn:turn.anyfirewall.com:443?transport=tcp");
  ice_server.username = "webrtc";
  ice_server.password = "webrtc";
  configuration_.ice_servers.push_back(ice_server);
}

void OwtClient::connect(std::string url, std::string token) {
  if (signaling_channel_.get() == nullptr) {
    signaling_channel_.reset(new OwtSignalingChannel());
  }
  if (client_.get() == nullptr) {
    client_.reset(new P2PClient(configuration_, signaling_channel_));
  }
  client_->AddObserver(*this);
  client_->Connect(url, token, nullptr, nullptr);
}

void OwtClient::OnMessageReceived(const std::string& remote_user_id, const std::string message) {
#ifdef OWT_DEBUG
  std::cout << "[" << remote_user_id << "] message: " << message << std::endl;
#endif
  ++msgCount;
  client_->Send(remote_user_id, std::string("I received your message. total count:") + std::to_string(msgCount), nullptr, nullptr);
}

void OwtClient::OnStreamAdded(std::shared_ptr<RemoteStream> stream) {}

void OwtClient::OnServerDisconnected() {}