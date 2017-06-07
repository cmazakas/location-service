#include <string>
#include <utility>
#include <boost/variant.hpp>
#include "handle_http_req.hpp"

namespace 
{
  using exception_t = web::http::http_exception;

  using uri_parse_result_t = boost::variant<
    std::pair<double, utility::string_t>,
    exception_t>;

  auto get_zip_radius(web::http::uri const& uri) -> uri_parse_result_t
  {
    using uri_t = web::http::uri;

    auto const relative_path = uri.path();

    if (relative_path != U("/")) {
      return exception_t{400, U("Incorrect path given. Simply use \"/\"")};
    }

    auto const query_params = uri_t::split_query(uri.query());

    if (query_params.size() != 2) {
      return exception_t{400, U("Invalid query parameters supplied to route")};
    }

    auto const end = query_params.end();

    auto const zip    = query_params.find(U("zip"));
    auto const radius = query_params.find(U("radius"));

    if (zip == end || radius == end) {
      return exception_t{400, U("Invalid query parameters supplied to route")};
    }

    try {
    
      auto const parsed_zip = std::stod((*zip).second);

      return std::make_pair(parsed_zip, (*radius).second);

    } catch (std::exception const& e) {

      return exception_t{400, utility::conversions::to_string_t(e.what())};
    }
  }
}

auto handle_http_req(web::http::http_request const& req) -> pplx::task<void>
{
  auto const zip_and_radius_or_exception = get_zip_radius(req.relative_uri());
   
  return {};
}