#include <curl/curl.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

const std::string BINANCE_HOST = "https://api.binance.com";
const std::string PATH = "/api/v3/exchangeInfo";
const std::string query = "\?symbol=ETHUSDT";
std::size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
  auto realized = size * nmemb;

  std::string result(static_cast<unsigned char*>(buffer),
                     static_cast<unsigned char*>(buffer) + realized);

  std::cout << result << std::endl;
  return realized;
}

void demo_get() {
  // init
  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL* curl = curl_easy_init();

  std::string url(BINANCE_HOST + PATH + query);

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1000L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  auto perform_code = curl_easy_perform(curl);
  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  std::cout << "perform code: " << perform_code << ", HTTP code: " << http_code
            << std::endl;
  // release
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

int main(int argc, char** argv) {
  demo_get();
  return EXIT_SUCCESS;
}