#include "../srv/net.cpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {

	Client* client = new Client();
	client->targetPort = 59203;
	client->connectServer("192.168.1.103");

	while (true) {
		auto ret = client->sendData("kikkare");
		if (ret == true)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
