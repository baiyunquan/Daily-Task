#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <array>
#include <set>
#include <cctype>
#include <deque>

using namespace std;


struct Packet {
    int source;
    int destination;
    int timestamp;

    Packet(int source, int destination, int timestamp)
        : source(source), destination(destination), timestamp(timestamp) {
    }

    bool operator<(const Packet& other) const {
        if (source != other.source) return source < other.source;
        if (destination != other.destination) return destination < other.destination;
        return timestamp < other.timestamp;
    }
};

class Router {
    deque<Packet> data;
    set<Packet> compare;
    const int maxSize;

public:
    Router(int memoryLimit) : maxSize(memoryLimit) {}

    bool addPacket(int source, int destination, int timestamp) {
        Packet packet(source, destination, timestamp);
        if (compare.find(packet) != compare.end()) {
            return false;
        }
        compare.insert(packet);
        data.push_back(packet);

        if (data.size() > maxSize) {
            Packet oldest = data.front();
            data.pop_front();
            compare.erase(oldest);
        }
        return true;
    }

    vector<int> forwardPacket() {
        if (data.empty()) {
            return {};
        }
        Packet packet = data.front();
        data.pop_front();
        compare.erase(packet);
        return { packet.source, packet.destination, packet.timestamp };
    }

    int getCount(int destination, int startTime, int endTime) {
        if (data.empty()) {
            return 0;
        }

        auto cmp = [](const Packet& p, int value) {
            return p.timestamp < value;
            };

        auto it_start = lower_bound(data.begin(), data.end(), startTime, cmp);
        auto it_end = lower_bound(data.begin(), data.end(), endTime + 1, cmp);

        int count = 0;
        for (auto it = it_start; it != it_end; ++it) {
            if (it->destination == destination) {
                count++;
            }
        }
        return count;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */