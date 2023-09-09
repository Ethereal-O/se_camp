#include "haffman.h"

class Node
{
public:
    bool isLeaf;
    char c;
    int freq;
    int high;
    Node *left, *right;
    Node(char c, int freq)
    {
        this->isLeaf = true;
        this->c = c;
        this->freq = freq;
        this->high = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(Node *left, Node *right)
    {
        this->isLeaf = false;
        this->c = std::min(left->c, right->c);
        this->freq = left->freq + right->freq;
        this->high = std::max(left->high, right->high) + 1;
        this->left = left;
        this->right = right;
    }
    // bool operator<(const Node &b) const
    // {
    //     // 实现less中需要的<,大顶堆
    //     return freq < b.freq || (freq == b.freq && c < b.c);
    // }
};

const std::string name = "sample";
const std::string inFile = "../input/" + name + ".txt";
const std::string outFileIdx = "../output/" + name + ".huffidx";
const std::string outFileZip = "../output/" + name + ".huffzip";
std::vector<std::pair<char, int>> freqTable;
Node *huffmanTree;
std::vector<std::pair<char, std::string>> codingTable;

std::string readAll(std::string fileName)
{
    std::ifstream ifs(fileName, std::ios::binary | std::ios::in);
    if (ifs.is_open())
    {
        ifs.seekg(0, std::ios::end);
        int len = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        char *buff = new char[len + 1];

        ifs.read(buff, len);
        ifs.close();
        std::string str = std::string(buff, len);
        delete[] buff;
        return str;
    }

    return "";
}

void writeAll(std::string fileName, const std::string &str)
{
    std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
    if (ofs.is_open())
    {
        ofs.write(str.c_str(), str.size());
        ofs.close();
    }
}

std::string convert(std::string str)
{
    std::string res;
    char r = 0;
    int i = 0;
    for (auto &&c : str)
    {
        if (i % 8 == 0)
        {
            res.push_back(r);
            r = 0;
        }
        else
        {
            r = r << 1;
        }

        if (c == '1')
            r = r | 1;
        if (c == '0')
            r = r | 0;

        i++;
    }

    while (i % 8 != 0)
    {
        r = r << 1;
        i++;
    }
    res.push_back(r);
    return res;
}

void do_statistics()
{
    std::string str = readAll(inFile);

    std::map<char, int> freq;

    for (auto &&c : str)
    {
        if (freq.find(c) == freq.end())
            freq[c] = 1;
        else
            freq[c]++;
    }

    for (auto &&i : freq)
        freqTable.push_back(i);

    std::sort(freqTable.begin(), freqTable.end(), [](std::pair<char, int> a, std::pair<char, int> b)
              { return a.second > b.second || (a.second == b.second && a.first < b.first); });
}

void build_tree()
{
    auto cmp = [](Node *a, Node *b)
    {
        return a->freq > b->freq || (a->freq == b->freq && a->c > b->c);
    };
    std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)> pq(cmp);

    for (auto &&i : freqTable)
        pq.push(new Node(i.first, i.second));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        pq.push(new Node(left, right));
    }
    huffmanTree = pq.top();
}

void encode(Node *node, std::string path)
{
    if (node->isLeaf)
    {
        codingTable.push_back(std::make_pair(node->c, path));
        return;
    }
    encode(node->left, path + "0");
    encode(node->right, path + "1");
}

std::string compress()
{
    std::string str = readAll(inFile);
    std::string originRes;
    for (auto &&c : str)
    {
        for (auto &&i : codingTable)
        {
            if (i.first == c)
            {
                originRes += i.second;
                break;
            }
        }
    }
    std::string res = convert(originRes);
    writeAll(outFileZip, originRes);
    return originRes;
}

int main()
{
    do_statistics();
    std::cout << freqTable.size() << std::endl;
    for (int i = 0; i < 3 && i < freqTable.size(); i++)
        std::cout << freqTable[i].first << " " << freqTable[i].second << std::endl;

    build_tree();
    std::cout << huffmanTree->high << std::endl;

    encode(huffmanTree, "");
    std::sort(codingTable.begin(), codingTable.end(), [](std::pair<char, std::string> a, std::pair<char, std::string> b)
              { return a.first < b.first || (a.first == b.first && a.second < b.second); });

    std::stringstream ss;
    for (auto &&i : codingTable)
    {
        ss << i.first << " " << i.second << std::endl;
        if (i.first == 'e')
            std::cout << i.second << std::endl;
    }
    writeAll(outFileIdx, ss.str());

    std::string res = compress();
    std::cout << res.size() << std::endl;
}