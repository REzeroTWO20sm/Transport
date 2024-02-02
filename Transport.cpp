#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

//g++ Transport.cpp -o Transport --std=c++14 -I/usr/local/include -I/usr/include/nlohmann -lcurl

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

template<typename T>
string float_to_str(T a_f){
    stringstream a_ss;
    string a_s;
    a_ss << a_f;
    a_s  = a_ss.str();
    return a_s;
}

string cUrl(const string& url) {
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            curl_easy_cleanup(curl);
            return response;
        } else {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
    }
    return "";
}


void take_closer_station(string address,string station_types){
    string station;
    string url;

    url = "https://catalog.api.2gis.com/3.0/items/geocode?q=" + address + "&fields=items.point&key=0038d200-62ed-4147-8a11-b996a7e2c7a7";
    json response = json::parse(cUrl(url));

    float lat_f = response["result"]["items"][0]["point"]["lat"];
    float lon_f = response["result"]["items"][0]["point"]["lon"];

    string url_1 = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types="+station_types+"&lng=" + float_to_str(lon_f) + "&lat=" + float_to_str(lat_f) + "&distance=50&lang=ru_RU";  
    json response_1 = json::parse(cUrl(url_1));
    int i=0;
    while(!response_1["stations"][i].is_null()){
        station += response_1["stations"][i]["code"];
        station += " ";
        station += response_1["stations"][i]["title"];
        station += " , ";
        i+=1;
    }
    cout << endl << station << endl;
}


string take_station(string address, string station_types){
    string station;
    string url;
    url = "https://catalog.api.2gis.com/3.0/items/geocode?q=" + address + "&fields=items.point&key=0038d200-62ed-4147-8a11-b996a7e2c7a7";
    json response = json::parse(cUrl(url));
    float lat_f = response["result"]["items"][0]["point"]["lat"];
    float lon_f = response["result"]["items"][0]["point"]["lon"];
    string url_1 = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types=" + station_types + "&lng=" + float_to_str(lon_f) + "&lat=" + float_to_str(lat_f) + "&distance=50&lang=ru_RU";
    json response_1 = json::parse(cUrl(url_1));
    station = response_1["stations"][0]["code"];
    return station;
}

void Timing_transport(string cityA,string cityB,string date){
    string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&date=" + date + "&from=" + cityA + "&to=" + cityB ;
    json response = json::parse(cUrl(url));
    
    int i=0;
    while(!response["segments"][i].is_null()){
        std::cout << endl << response["segments"][i]["thread"]["title"] << endl 
        << response["segments"][i]["from"]["title"] << " - " << response["segments"][i]["to"]["title"] << endl
        << response["segments"][i]["start_date"] << endl << response["segments"][i]["arrival"] << endl;
        i+=1;
    }
}

void transport_inf(string cityA,string cityB,string date){
    string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&date=" + date + "&from=" + cityA + "&to=" + cityB ; /*определение station города*/
    int i=0;
    json response = json::parse(cUrl(url));
    while(!response["segments"][i].is_null()){
        int transport_code_i = response["segments"][i]["thread"]["carrier"]["code"];
        cout << endl << float_to_str(transport_code_i) << endl;
        url = "https://api.rasp.yandex.net/v3.0/carrier/?format=json&apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&lang=ru_RU&code=" + float_to_str(transport_code_i);
        json response_1 = json::parse(cUrl(url));
        cout << endl << response_1<< endl;
        i += 1;
    }
}

int main(){
    string adress_A_s;
    string adress_B_s;
    string date,adress_A,adress_B,station_type;
    cin>>date>>adress_A>>adress_B>>station_type;//YYYY-MM-DD,Москва,Казань,airport

    adress_A_s = take_station(adress_A,station_type);
    adress_B_s = take_station(adress_B,station_type);

    int cifra;
    while(cifra != 4){
        cout << endl << "Меню:" << endl;
        cout << "1. Просмотр рейсов из A в B по зад. дате" << endl;
        cout << "2. Ближайшая станции" << endl;
        cout << "3. Информация о перевозчике" << endl;
        cout << "4. Выход" << endl;
        cin >> cifra;
        switch (cifra) {
            case 1:
                Timing_transport(adress_A_s,adress_B_s,date);
                break;
            case 2:
                take_closer_station(adress_A,station_type);
                break;
            case 3:
                transport_inf(adress_A_s,adress_B_s,date);
                break;
            case 4:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Выбрано неверное действие. Попробуйте снова." << endl;
                break;
        }

        cout << endl;
    }
}