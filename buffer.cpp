#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string take_station(string city){
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl){
        string pos;
        string station;
        string url = "https://geocode-maps.yandex.ru/1.x/?apikey=dbcd5d6e-f034-4c9e-a84d-11c201dbd4d4&lang=ru_RU&geocode="+ city +"&format=json"; /*определение station города*/
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK){
            json response = json::parse(readBuffer);
            pos = response["response"]["GeoObjectCollection"]["featureMember"][0]["GeoObject"]["Point"]["pos"];
            pos = pos.replace(pos.find(" "),1,"&lat=");                                                                                                                        //37.617698&lan=55.755864
            
        }
        else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        readBuffer.clear();
        string url_1 = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types=airport&lng=" + pos/*"&lat=55.312148&lng=37.038186"*/ +"&distance=50&lang=ru_RU";
        cout << url_1;
        
        curl_easy_setopt(curl, CURLOPT_URL, url_1.c_str());
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK){
            json response = json::parse(readBuffer);
            station = response["stations"][0]["code"];
            return station;
        }
        else{
            std::cerr << endl<<"Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main(){
    setlocale(LC_ALL, "Russian");
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if(curl){
        string pos;
        string station;
        string city = "moscow";
        string url = "https://geocode-maps.yandex.ru/1.x/?apikey=dbcd5d6e-f034-4c9e-a84d-11c201dbd4d4&lang=ru_RU&geocode="+ city +"&format=json"; /*определение station города*/
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK){
            json response = json::parse(readBuffer);
            cout << response << std::endl;
            pos = response["response"]["GeoObjectCollection"]["featureMember"][0]["GeoObject"]["Point"]["pos"];
            cout << endl << pos ;
            pos = pos.replace(pos.find(" "),1,"&lat=");
            cout <<  endl <<  pos << endl;                                                                                                                              //37.617698&lan=55.755864
            
        }
        else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        readBuffer.clear();
        string url_1 = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types=airport&lng=" + pos/*"&lat=55.312148&lng=37.038186"*/ +"&distance=50&lang=ru_RU";
        cout << url_1;
        
        curl_easy_setopt(curl, CURLOPT_URL, url_1.c_str());
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK){
            json response = json::parse(readBuffer);
            station = response["stations"][0]["code"];
            cout << endl << response << endl << endl << station;
        }
        else{
            std::cerr << endl<<"Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}