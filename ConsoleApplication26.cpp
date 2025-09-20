#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>

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
    unordered_map<int, vector<int>> destinationTimestamps; // 每个目的地的时间戳列表
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
        destinationTimestamps[destination].push_back(timestamp); // 添加到目的地时间戳列表

        if (data.size() > maxSize) {
            Packet oldest = data.front();
            data.pop_front();
            compare.erase(oldest);
            // 从目的地时间戳列表中移除最旧的时间戳
            auto& timestamps = destinationTimestamps[oldest.destination];
            timestamps.erase(timestamps.begin());
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
        // 从目的地时间戳列表中移除最旧的时间戳
        auto& timestamps = destinationTimestamps[packet.destination];
        timestamps.erase(timestamps.begin());
        return { packet.source, packet.destination, packet.timestamp };
    }

    int getCount(int destination, int startTime, int endTime) {
        if (destinationTimestamps.find(destination) == destinationTimestamps.end()) {
            return 0;
        }

        const auto& timestamps = destinationTimestamps[destination];
        if (timestamps.empty()) {
            return 0;
        }

        // 使用二分查找确定时间范围
        auto start_it = lower_bound(timestamps.begin(), timestamps.end(), startTime);
        auto end_it = upper_bound(timestamps.begin(), timestamps.end(), endTime);

        // 直接返回范围内的数据包数量
        return end_it - start_it;
    }
};