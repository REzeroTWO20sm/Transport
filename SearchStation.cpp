// #include <iostream>
// #include <curl/curl.h>
// #include <nlohmann/json.hpp>

/*
https://api.rasp.yandex.net/v3.0/stations_list/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&lang=ru_RU&format=json - список всех станций
https://suggests.rasp.yandex.net/all_suggests?format=old&part=Казань - список всех станции по городу
https://api.rasp.yandex.net/v3.0/schedule/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&station=s2014001&transport_types=train&direction=all - все расписания во все стороны
https://api.rasp.yandex.net/v3.0/search/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&from=s2014001&to=s2014001 - расписания из одной в другую точку

первый пункт :
1) https://suggests.rasp.yandex.net/all_suggests?format=old&part=Казань - выводит список всех station кодов города 
https://api.rasp.yandex.net/v3.0/all_suggests/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&part=казань
2) https://api.rasp.yandex.net/v3.0/search/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&from=c43&to=c213&date=2024-01-22 находит рейсы все из одного города в другой с определенной датой
 

https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&lat=50&lng=40&distance=50&lang=ru_RU по широте и долготе ищет станции
https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&format=json&station_types=airport&lat=55.312148&lng=37.038186&distance=50&lang=ru_RU по широте и долготе ищет станции

Казань - s9600379
Санкт-Петербург - s9600220

0038d200-62ed-4147-8a11-b996a7e2c7a7 https://catalog.api.2gis.com/3.0/items/geocode?lat=55.751508&lon=37.615666&fields=items.point&key=0038d200-62ed-4147-8a11-b996a7e2c7a7


"https://api.rasp.yandex.net/v3.0/carrier/?format=json&apikey=a28bf47e-da92-4a54-a246-f0e7a7ed4818&lang=ru_RU&code=" + transport_code + "&system=iata"

*/

#include <iostream>
#include <curl/curl.h>
#include <string>

// Callback функция для записи данных в std::string
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t real_size = size * nmemb;
    data->append(static_cast<char*>(contents), real_size);
    return real_size;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL); // Инициализация libcurl
    curl = curl_easy_init(); // Инициализация easy-интерфейса

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com"); // Установка URL для первого запроса

        // Указываем, что хотим получить ответ в виде строки
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Выполняем первый запрос
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Received data from first URL: " << readBuffer << std::endl;
        }

        // Сбрасываем буфер перед вторым запросом
        readBuffer.clear();

        // Устанавливаем второй URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://example2.com");
        
        // Выполняем второй запрос
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Received data from second URL: " << readBuffer << std::endl;
        }
        
        curl_easy_cleanup(curl); // Освобождаем ресурсы easy-интерфейса
    } else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }

    curl_global_cleanup(); // Освобождение глобальных ресурсов libcurl
    return 0;
}
