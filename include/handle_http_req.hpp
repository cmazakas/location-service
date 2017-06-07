#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>

auto handle_http_req(web::http::http_request const& req) -> pplx::task<void>;