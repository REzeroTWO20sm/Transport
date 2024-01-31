#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string take_station(string address, string station_types){
    CURL *curl;
    CURLcode res;
    string readBuffer;
    stringstream lat_ss;
    stringstream lon_ss;
    float lat_f;
    float lon_f;
    string lat;
    string lon;
    string station;
    string url;
    curl = curl_easy_init();
    if(curl){
        //"https://catalog.api.2gis.com/3.0/items/geocode?q=Москва, Садовническая, 25&fields=items.point&key=0038d200d-62ed-4147-8a11-b996a7e2c7a7
        url = "https://catalog.api.2gis.com/3.0/items/geocode?q=" + address + "&fields=items.point&key=0038d200-62ed-4147-8a11-b996a7e2c7a7";
        /* string url = "https://geocode-maps.yandex.ru/1.x/?apikey=dbcd5d6e-f034-4c9e-a84d-11c201dbd4d4&lang=ru_RU&geocode="+ city +"&format=json"; определение station города*/
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK){
            json response = json::parse(readBuffer);
            lat_f = response["result"]["items"][0]["point"]["lat"];
            lon_f = response["result"]["items"][0]["point"]["lon"];
            lat_ss << lat_f;
            lon_ss << lon_f;
            lat  = lat_ss.str();
            lon = lon_ss.str();
            /*pos = pos.replace(pos.find(" "),1,"&lat=");*/                                                                                                                        //37.617698&lan=55.755864
            
        }
        else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        readBuffer.clear();
        string url_1 = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types=" + station_types + "&lng=" + lon + "&lat=" + lat + "&distance=50&lang=ru_RU";
        
        curl_easy_setopt(curl, CURLOPT_URL, url_1.c_str());
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK){
            json response = json::parse(readBuffer);
            station = response["stations"][0]["code"];
            
        }
        else{
            std::cerr << endl<<"Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return station;
}
void transport_inf(string cityA,string cityB,string date){
    CURL *curl;
    CURLcode res;
    string readBuffer;
    json response;
    json response_1;
    int transport_code_i;
    stringstream transport_code_ss;
    string transport_code;
    curl = curl_easy_init();

    if(curl){
        
        string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&date=" + date + "&from=" + cityA + "&to=" + cityB ; /*определение station города*/
        cout << url << endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK){
            int i=0;
            response = json::parse(readBuffer);
            readBuffer.clear();
            while(!response["segments"][i].is_null()){
                transport_code_ss.str("");
                transport_code_i = response["segments"][i]["thread"]["carrier"]["code"];
                transport_code_ss << transport_code_i;
                transport_code = transport_code_ss.str();
                url = "https://api.rasp.yandex.net/v3.0/carrier/?format=json&apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&lang=ru_RU&code=" + transport_code ;
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                res = curl_easy_perform(curl);
                if(res == CURLE_OK){
                    response_1 = json::parse(readBuffer);
                    cout << endl << response_1<< endl;
                }
                else {
                    std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
                }
                i += 1;
                readBuffer.clear();
            }
        }
        else {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }


    // "https://api.rasp.yandex.net/v3.0/carrier/?format=json&apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&lang=ru_RU&code=" + transport_code + "&system=iata"


    curl_global_cleanup();
}


int main(){
    string stationA;
    string stationB;
    string station_type;
    string cityA = "москва";
    string cityB = "казань";
    string date = "2024-01-27";
    station_type = "airport";
    
    stationA = take_station(cityA,station_type);
    stationB = take_station(cityB,station_type);
    // cout << stationA << endl << stationB;
    transport_inf(stationA,stationB,date);
}