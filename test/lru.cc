#include <list>
#include <map>
#include <unordered_map>
#include <iostream>

using list_iter = std::list<std::pair<int, int>>::iterator;

class LRU {
public:
    int get(int key);
    void set(int key, int value);
    void print();
private:
    std::unordered_map<int, list_iter> tmp;
    std::list<std::pair<int, int>> tmp1;
};

int LRU::get(int key) {
    auto iter = tmp.find(key);
    if (iter != tmp.end()) {
        std::pair<int, int> tmp_pair = *tmp[key];
        tmp1.erase(tmp[key]);
        tmp1.push_front(tmp_pair);
        tmp[key] = tmp1.begin();
        return tmp_pair.second;
    }
    return -1;
}

void LRU::set(int key, int value) {
    auto iter = tmp.find(key);
    if (iter != tmp.end()) {
        tmp1.erase(iter->second);
        tmp1.push_front(std::make_pair(key, value));
        tmp[key] = tmp1.begin();
    }
    else {
        if (tmp1.size() > 2) {
            tmp.erase(tmp1.back().first);
            tmp1.pop_back();
        }
        tmp1.push_front(std::make_pair(key, value));
        tmp[key] = tmp1.begin();
    }
}

void LRU::print() {
    for (auto& iter : tmp1) {
        std::cout << iter.first;
        std::cout << " ";
    }
    std::cout << " " << std::endl;
}

int main() {
    LRU lru;
    lru.set(1,1);
    lru.set(2,2);
    lru.set(3,3);
    std::cout << lru.get(1) << std::endl;
    lru.print();
    std::cout << lru.get(2) << std::endl;
    lru.print();
    std::cout << lru.get(3) << std::endl;
    lru.print();
    return 0;
}
