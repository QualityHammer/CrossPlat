#include "Server.h"
#include <common/Common.h>

int server::getNum() {
	return 3 * common::getMultiplier();
}