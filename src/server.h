#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

void server_pause();
void server_resume();
bool get_wifi_is_on();

#endif