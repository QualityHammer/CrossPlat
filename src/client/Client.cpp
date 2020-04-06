#include "Client.h"
#include <Server.h>

#include <iostream>
#include <SDL.h>

void client::displayNum() {
	std::cout << server::getNum() << std::endl;
	return;
}
