#include "Client.h"
#include <Server.h>

#include <iostream>

void client::displayNum() {
	std::cout << server::getNum() << std::endl;
	return;
}
