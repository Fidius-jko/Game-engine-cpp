#include <iostream>
#include <CORE/Application.hpp>
#include <memory>

class MyApp : public Engine::Application {
	virtual void onUpdate() override {
		//std::cout << "Update frame: " << frame++ << "\n";
	}
	int frame = 0;
};

int main() {
	auto myApp = std::make_unique<MyApp>();

	int returnCode = myApp->start(1024, 768, "My frist App");

	std::cin.get();
	return returnCode;
}