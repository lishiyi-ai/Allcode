#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>


struct TreeNode {
    std::string destination_ip;
    std::string mask;
    std::string next_hop;
    TreeNode* left;
    TreeNode* right;
    bool leftThreaded;
    bool rightThreaded;
};

struct RouteEntry {
    std::string destination_ip;
    std::string mask;
    std::string next_hop;
};

// 创建二叉线索树
TreeNode* createThreadedBST(const std::vector<RouteEntry>& routeTable);

// 在二叉线索树中插入节点
TreeNode* insert(TreeNode* root, const RouteEntry& entry);

// 将IP地址转换为二进制字符串
std::string ipToBinary(const std::string& ipAddress);

// 在二叉线索树中查找下一跳地址
std::string findNextHop(TreeNode* root, const std::string& destinationAddress);

int main() {
    // 示例路由表（目的地址 掩码 下一跳）
    std::vector<RouteEntry> routeTable = {
        {"192.168.1.0", "255.255.255.0", "192.168.1.1"},
        {"10.0.0.0", "255.0.0.0", "10.0.0.1"},
        {"172.16.0.0", "255.240.0.0", "172.16.0.1"},
    };

    // 创建二叉线索树
    TreeNode* root = createThreadedBST(routeTable);

    // 示例目的地址
    std::string destinationAddress = "192.168.1.5";

    // 查找路由表并输出结果
    std::string nextHop = findNextHop(root, destinationAddress);
    if (!nextHop.empty()) {
        std::cout << "下一跳地址为: " << nextHop << std::endl;
    } else {
        std::cout << "未找到匹配项" << std::endl;
    }

    // TODO: 释放二叉线索树的内存（根据实际情况释放内存）

    return 0;
}

// 实现：创建二叉线索树
TreeNode* createThreadedBST(const std::vector<RouteEntry>& routeTable) {
    TreeNode* root = nullptr;

    for (const auto& entry : routeTable) {
        root = insert(root, entry);
    }

    return root;
}

// 实现：在二叉线索树中插入节点
TreeNode* insert(TreeNode* root, const RouteEntry& entry) {
    if (root == nullptr) {
        return new TreeNode{entry.destination_ip, entry.mask, entry.next_hop, nullptr, nullptr, false, false};
    }

    // 将目的地址和掩码转换为二进制字符串
    std::string binaryDestination = ipToBinary(entry.destination_ip);
    std::string binaryMask = ipToBinary(entry.mask);

    // 根据二进制字符串遍历树
    TreeNode* current = root;
    for (size_t i = 0; i < binaryDestination.size(); ++i) {
        char bit = binaryDestination[i];
        if (bit == '0') {
            if (current->left == nullptr) {
                current->left = new TreeNode{"", "", "", nullptr, nullptr, false, false};
                current->leftThreaded = true;
                current->left->right = current;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new TreeNode{"", "", "", nullptr, nullptr, false, false};
                current->rightThreaded = true;
                current->right->left = current;
            }
            current = current->right;
        }
    }

    // 将路由表项信息存储在叶子节点
    current->destination_ip = entry.destination_ip;
    current->mask = entry.mask;
    current->next_hop = entry.next_hop;

    return root;
}

// 实现：将IP地址转换为二进制字符串
std::string ipToBinary(const std::string& ipAddress) {
    std::stringstream result;
    for (const char& c : ipAddress) {
        if (c == '.') {
            continue;
        }
        result << std::bitset<8>(c - '0').to_string();
    }
    return result.str();
}

// 实现：在二叉线索树中查找下一跳地址
std::string findNextHop(TreeNode* root, const std::string& destinationAddress) {
    // 将目的地址转换为二进制字符串
    std::string binaryDestination = ipToBinary(destinationAddress);

    TreeNode* current = root;
    for (size_t i = 0; i < binaryDestination.size(); ++i) {
        char bit = binaryDestination[i];
        if (bit == '0') {
            if (current->leftThreaded) {
                current = current->left;
            } else {
                return current->left->next_hop;
            }
        } else {
            if (current->rightThreaded) {
                current = current->right;
            } else {
                return current->right->next_hop;
            }
        }
    }

    return "";  // 没有匹配项
}