#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <codecvt>
#include "pugi/src/pugixml.hpp"
#include <iomanip>


#define earthRadiusKm 6371.0

double deg2rad(double deg) {
    return (deg * M_PI / 180);
}

double distanceEarth(double x1, double y1, double x2, double y2) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(x1);
    lon1r = deg2rad(y1);
    lat2r = deg2rad(x2);
    lon2r = deg2rad(y2);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


void  parsing_routes(std::string &routes, std::vector <std::string> &nums){
    std::string cur_str = "";

    for (int i = 0; i < routes.size(); i++) {
        if (i == routes.size() - 1) {
            cur_str += routes[i];
            nums.push_back(cur_str);
            break;
        }
        if ((routes[i] != ',') && (routes[i] != '.'))
            cur_str += routes[i];
        else {
            nums.push_back(cur_str);
            cur_str = "";
        }
    }
}

void  parsing_coord(std::string &coordinates, std::vector <double> &coords){
    std::string cur_str = "";

    for (int i = 0; i < coordinates.size(); i++) {
        if (i == coordinates.size() - 1) {
            cur_str += coordinates[i];
            coords.push_back(atof(cur_str.c_str()));
            break;
        }
        if ((coordinates[i] != ','))
            cur_str += coordinates[i];
        else {
            coords.push_back(atof(cur_str.c_str()));
            cur_str = "";
        }
    }
}

int main() {
    std::string routes;

    pugi::xml_document doc;
    pugi::xml_parse_result data = doc.load_file("data.xml");
    if (!data)
        return -1;
    pugi::xml_node station = doc.child("dataset").child("transport_station");

    std::unordered_map <std::string, std::unordered_map<std::string, std::vector< std::vector <double> > > >  all_data;

    double sum_distance;

    while(station) {

        routes = station.child_value("routes");
        std::vector<std::string> routes_numbers;

        std::vector<double> coords;
        std::string not_parsed_coords = station.child_value("coordinates");

        parsing_routes(routes, routes_numbers);
        parsing_coord(not_parsed_coords, coords);

        for (int i = 0; i < routes_numbers.size(); i++)
            all_data[station.child_value("type_of_vehicle")][routes_numbers[i]].push_back(coords);
        station = station.next_sibling();


    }


    auto it = all_data.begin();

    for (; it != all_data.end(); it++){
        int MAX_stations = 0;
        double max_sum_distance = 0;
        std::string route = "";
        std::string route_t = "";
        auto it2 = it->second.begin();



        for (; it2 != it->second.end(); it2++){
            if (it2->second.size() > MAX_stations) {
                MAX_stations = it2->second.size();
                route = it2->first;
            }
            sum_distance = 0;
            for (int i = 0; i < it2->second.size()-1; i++ ){
                sum_distance += distanceEarth(it2->second[i][0],it2->second[i][1], it2->second[i+1][0],it2->second[i+1][1]) ;
            }
            if (sum_distance > max_sum_distance){
                max_sum_distance = sum_distance;
                route_t = it2->first;
            }
        }

        std::cout << it->first << " has route: " << route << " with stations: " << MAX_stations << std::endl;
        std::cout << it->first << " has route: " << route_t << " with max distance: " << max_sum_distance/2 << std::endl;
        std::cout << std::endl;
    }



    return 0;
}