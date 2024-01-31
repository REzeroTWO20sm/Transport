// #include <string>
// #include <curl/curl.h>
// #include <nlohmann/json.hpp>
// #include <iostream>
// using namespace std;

// class TransportTiming {
// public:
//     string CityA;
//     string CityB;
//     string time;
//     string dateA;
//     string dateB;
//     string typeOfTransportation;
//     void print(){
//         cout << "Citys: "<< CityA<<"->"<<CityB<<endl;
//         cout << "Time of transition: "<< time<<endl;
//         cout << "Date: "<< dateA<<"->"<<dateB<<endl;
//         cout << "Type of transportation: "<< typeOfTransportation <<endl;
//     }
//     TransportTiming(string p_CityA,string p_CityB,string p_time,string p_dateA,string p_dateB,string p_typeOfTransportation){
//         CityA = p_CityA;
//         CityB = p_CityB;
//         time = p_time;
//         dateA = p_dateA;
//         dateB = p_dateB;
//         typeOfTransportation = p_typeOfTransportation;
//     }
    
// private:
    
// };

// int main() {
//     TransportTiming one{"Boston","New York","13:45"," 13.02.2024","14.02.2024","Bus"};
//     one.print();
// }


// #include <iostream>
// #include <curl/curl.h>
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;

// size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
//     ((std::string*)userp)->append((char*)contents, size * nmemb);
//     return size * nmemb;
// }

// int main() {
//     CURL *curl;
//     CURLcode res;
//     std::string readBuffer;

//     curl = curl_easy_init();
//     if (curl) {
//         std::string apiKey = "a28bf47e-da92-4a54-a246-f0e7a7ed4818";
//         std::string from = u8"Москва";
//         std::string to = u8"Санкт-Петербург";
//         std::string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=" + apiKey + "&from=" + from + "&to=" + to;

//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//         res = curl_easy_perform(curl);
//         curl_easy_cleanup(curl);

//         if (res == CURLE_OK) {
//             json response = json::parse(readBuffer);
//             // Обработка JSON-ответа здесь
//             std::cout << response << std::endl;
//         } else {
//             std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
//         }
//     }

//     return 0;
// }

/*https://api.rasp.yandex.net/v3.0/schedule/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818    &station=s2014001    &transport_types=train     &direction=all
https://api.rasp.yandex.net/v3.0/schedule/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&title="Адлер — Москва"


*/
/*#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string apiKey = "a28bf47e-da92-4a54-a246-f0e7a7ed4818";
        std::string from = "Moscow";
        std::string to = "Saint+Petersburg";
        std::string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=" + apiKey + "&from=" + from + "&to=" + to;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            json response = json::parse(readBuffer);
            // Обработка JSON-ответа здесь
            std::cout << response << std::endl;
        } else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return 0;
}*/

#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std ; 

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    float lat;
    float lon;
    curl = curl_easy_init();
    if (curl) {
        
        std::string date = "2024-01-22";
        std::string apiKey = "a28bf47e-da92-4a54-a246-f0e7a7ed4818";
        std::string station = "s9600379"; //Moscow
        std::string format = "json";
        std::string lang = "ru_RU";
        std::string url = "https://catalog.api.2gis.com/3.0/items/geocode?q=Москва,Садовническая,25&fields=items.point&key=0038d200-62ed-4147-8a11-b996a7e2c7a7";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        int count;
        if (res == CURLE_OK) {
            json response = json::parse(readBuffer);
            lat = response["result"]["items"][0]["point"]["lat"];
            lon = response["result"]["items"][0]["point"]["lon"];
            std::cout << endl << lat<<endl<<lon<< std::endl;
        } 
        else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
    }

    return 0;
}
//g++ Ransport.cpp -o Ransport --std=c++14 -I/usr/local/include -I/usr/include/nlohmann -lcurl