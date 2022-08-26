#include "OwtClient.h"

int main() {
  std::string url = "http://localhost::8096";
  std::string token = "p2p";
  OwtClient* owt_client = new OwtClient();
  owt_client->connect(url, token);
  return 0;
}