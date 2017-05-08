#ifndef MAKE_SERVER_HPP_
#define MAKE_SERVER_HPP_

//#define _TURN_OFF_PLATFORM_STRING

#include <string>
#include <cpprest/http_listener.h>

using http_listener_t = web::http::experimental::listener::http_listener;

auto make_server(std::string const& filename) -> http_listener_t;

#endif // MAKE_SERVER_HPP_