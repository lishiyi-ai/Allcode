#include <iostream>
#include <vector>

// 定义路由表项结构体
struct RouteItem {
    std::string dest_ip;
    std::string mask;
    std::string next_hop;
};

// 函数声明：查找下一跳地址
std::string findNextHop(const std::vector<RouteItem>& routeTable, const std::string& destAddress);
void getBits(std::string ipv4, int *bits){
    int len = ipv4.size();
    int tmp = 0;
    int j = 0;
    for(int i = 0; i <= len ; i++){
        // std::cout << ipv4[i] << "\0";
        if(ipv4[i] == '.' || i == len){
            int tmp1[8];
            int k = 0;
            while(tmp){
                int bit = tmp & 1;
                tmp = tmp >> 1;
                tmp1[k++] = bit;
            }
            for(; k < 8;k++){
                tmp1[k] = 0;
            }
            --k;
            for(; k>=0; k--){
                bits[j++] = tmp1[k];
            }
            tmp = 0;
            continue;
        }
        tmp = tmp*10 + (ipv4[i] - '0');
    }
}

int main() {
    // 示例路由表（目的地址 掩码 下一跳）
    std::vector<RouteItem> routeTable = {
        {"192.168.1.0", "255.255.255.0", "192.168.1.1"},
        {"10.0.0.0", "255.0.0.0", "10.0.0.1"},
        {"172.16.0.0", "255.240.0.0", "172.16.0.1"},
    };

    // 示例目的地址
    std::string destAddress = "192.168.1.5";

    // 查找路由表并输出结果
    std::string nextHop = findNextHop(routeTable, destAddress);
    if (!nextHop.empty()) {
        std::cout << "下一跳地址为: " << nextHop << std::endl;
    } else {
        std::cout << "未找到匹配项" << std::endl;
    }

    system("pause");

    return 0;
}

// 实现：查找下一跳地址
std::string findNextHop(const std::vector<RouteItem>& routeTable, const std::string& destAddress) {
    int searchBits[32] ; getBits(destAddress, searchBits);
    for (const auto& Item : routeTable) {
        // 将目的地址与掩码进行按位与操作，以获取网络地址
        int searchBits[32] ; getBits(destAddress, searchBits);
        int maskBits[32] ; getBits(Item.mask, maskBits);
        int destBits[32] ; getBits(Item.dest_ip, destBits);
        int networkBits[32];
        for(int i = 0 ; i < 32 ; i++){
            networkBits[i] = searchBits[i] & maskBits[i];
        }

        int flag = 1;

        for(int i = 0 ; i < 32 ; i++){
            if(networkBits[i] != destBits[i]){
                flag = 0;
                break;
            }
        }
        if (flag) {
            return Item.next_hop;
        }
    }

    // 如果没有匹配项，则返回空值（表示无法找到匹配项）
    return "";
}
