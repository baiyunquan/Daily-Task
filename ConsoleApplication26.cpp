#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <tuple>

using namespace std;

class MovieRentingSystem {
private:
    // 存储 shop -> movie -> price 的映射
    unordered_map<int, unordered_map<int, int>> priceMap;

    // 按电影ID索引的可用电影集合，存储 (price, shop)
    unordered_map<int, set<pair<int, int>>> availableMovies;

    // 已出租电影集合，存储 (price, shop, movie)
    set<tuple<int, int, int>> rentedMovies;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (const auto& entry : entries) {
            int shop = entry[0], movie = entry[1], price = entry[2];
            priceMap[shop][movie] = price;
            availableMovies[movie].emplace(price, shop);
        }
    }

    vector<int> search(int movie) {
        vector<int> result;
        if (availableMovies.find(movie) == availableMovies.end())
            return result;

        auto& movieSet = availableMovies[movie];
        int count = 0;
        for (auto it = movieSet.begin(); it != movieSet.end() && count < 5; ++it, ++count) {
            result.push_back(it->second);
        }
        return result;
    }

    void rent(int shop, int movie) {
        // 检查电影是否可用
        if (priceMap.find(shop) == priceMap.end() ||
            priceMap[shop].find(movie) == priceMap[shop].end()) {
            return;
        }

        // 获取价格
        int price = priceMap[shop][movie];

        // 从可用电影中移除
        if (availableMovies.find(movie) != availableMovies.end()) {
            availableMovies[movie].erase({ price, shop });

            // 如果集合为空，移除电影条目
            if (availableMovies[movie].empty()) {
                availableMovies.erase(movie);
            }
        }

        // 添加到已出租集合
        rentedMovies.emplace(price, shop, movie);
    }

    void drop(int shop, int movie) {
        // 检查电影是否已出租
        if (priceMap.find(shop) == priceMap.end() ||
            priceMap[shop].find(movie) == priceMap[shop].end()) {
            return;
        }

        // 获取价格
        int price = priceMap[shop][movie];

        // 从已出租集合中移除
        auto it = rentedMovies.find({ price, shop, movie });
        if (it != rentedMovies.end()) {
            rentedMovies.erase(it);
        }

        // 添加回可用电影集合
        availableMovies[movie].emplace(price, shop);
    }

    vector<vector<int>> report() {
        vector<vector<int>> result;
        int count = 0;
        for (const auto& movie : rentedMovies) {
            if (count >= 5) break;
            result.push_back({ get<1>(movie), get<2>(movie) });
            count++;
        }
        return result;
    }
};