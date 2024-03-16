#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>

class Router {
public:
    // std::string id;
    std::map<std::string, int> neighbors; // 邻居节点及其链路权值
    std::map<std::string, int> minpathlen;
    std::map<std::string , std::vector<std::string> > minpath; 
};

class Network {
public:
    std::map<std::string, Router> routers;

    // 泛洪广播链路信息
    void floodLinkInfo(std::string router, std::map<std::string, int> neighbors) {
        printRouters();
        // 根据新的信息重新构建网络拓扑
        routers[router].neighbors.clear();
        for (auto [destRouter, path]: neighbors) {
            routers[router].neighbors.emplace(destRouter, path);
            routers[destRouter].neighbors.emplace(router,path);
        }
        printRouters();
    }

    void printRouters(){
        for(const auto &[routerName, routerMes]: routers){
            std::cout << "routerName:" << routerName <<" neighbors { ";
            for(const auto &[destRouter, path]: routerMes.neighbors){
                std::cout << " {" << "\"" << destRouter << "\" , "<< path << "} ";
            }
            std::cout << " }"<<std::endl;
        }
    }

    // 构建网络拓扑
    void buildTopology() {
        // 实现链路信息的接收和处理，构建拓扑
        // 在这个简化的例子中，我们直接通过手动设置邻居节点和链路权值来模拟
        // routers["A"].neighbors = {{"B", 4}, {"E", 5}};
        routers["B"].neighbors = {{"C", 2}, {"F", 6}};
        routers["C"].neighbors = {{"B", 2}, {"D", 3}, {"E", 1}};
        routers["D"].neighbors = {{"C", 3}, {"F", 7}};
        routers["E"].neighbors = {{"C", 1}};
        routers["F"].neighbors = {{"B", 6}, {"F", 7}};
    }

    // Dijkstra算法计算最短路径
    void dijkstra(const std::string& sourceId) {
        std::map<std::string, int> distance;
        // 距离, 原点, 目的点
        std::priority_queue<std::pair<int, std::string>, 
                            std::vector<std::pair<int, std::string > >, 
                            std::greater<std::pair<int, std::string> > > pq;

        // 初始化距离为无穷大
        for (const auto& [id, router] : routers) {
            distance[id] = std::numeric_limits<int>::max();
        }

        // 设置源节点距离为0，并将其加入优先队列
        distance[sourceId] = 0;
        pq.push({0, sourceId});

        routers[sourceId].minpath[sourceId].emplace_back(sourceId);

        while (!pq.empty()) {

            std::string u = pq.top().second;
            int pathlen =  pq.top().first;
            std::cout << sourceId << " " << pathlen << " " << u << std::endl;
            pq.pop();
            if(pathlen > distance[u]){
                continue;
            }
            // std::cout << "开始遍历" << std::endl;
            // 遍历u的邻居节点
            for (const auto& [v, weight] : routers[u].neighbors) {
                // std::cout << u << " " << weight << " " << v << std::endl;
                // 松弛操作
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;

                    // 将现有路径存储
                    routers[sourceId].minpath[v] = routers[sourceId].minpath[u];
                    routers[sourceId].minpath[v].emplace_back(v);

                    pq.push({distance[v],v});
                }
            }


        }

        routers[sourceId].minpathlen = distance;

        return;
    }

    // 生成路由表
    void generateRoutingTable(const std::string& sourceId) {
        dijkstra(sourceId);

        std::map<std::string, int> shortestPathsLen = routers[sourceId].minpathlen;

        // 输出路由表
        std::cout << "Routing Table for Router " << sourceId << ":\n";
        for (const auto& [destination, distance] : shortestPathsLen) {
            std::cout << "To " << destination << ", Distance: " << distance << "\n" ;
            int len = routers[sourceId].minpath[destination].size();
            std::cout <<"走过的点有:" << len << " 路径为: ";
            int i = 1;
            for(const auto &path: routers[sourceId].minpath[destination]){
                std::cout << path;
                if(i != len){
                    std::cout << "->";
                    i++;
                }    
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Network network;

    // 构建网络拓扑
    network.buildTopology();

    // 泛洪广播链路信息，假设节点1是发送者
    // std::string senderNodeId = "A";
    network.floodLinkInfo("A",{{"B", 4}, {"E", 5}});

    // 计算最短路径和生成路由表，假设选择节点2作为源节点
    std::string sourceNodeId = "B";
    network.generateRoutingTable(sourceNodeId);
    system("pause");
    return 0;
}