#include "bits/stdc++.h"

struct TrieNode
{
    std::map<char, TrieNode *> children;
    bool isWord;
};

std::vector<std::string> codeVector;
std::vector<std::string> keyVector;
std::vector<int> codeToKeyVector;

TrieNode *root;
int leafNum = 0;
int maxKeyLength = 0;

std::string tolower(const std::string &str)
{
    std::string res;
    for (auto &&c : str)
        res.push_back(std::tolower(c));
    return res;
}

std::string readFile(const std::string &path)
{
    std::ifstream file(path.data(), std::ios::in);
    if (!file.is_open())
        return "";

    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    file.close();
    return content;
}

void writeFile(const std::string &path, const std::string &content)
{
    std::ofstream file(path.data(), std::ios::out);
    if (!file.is_open())
        return;

    file.write(&content[0], content.size());
}

void LoadData()
{
    std::string codeFilePath, keyFilePath;
    std::cin >> codeFilePath >> keyFilePath;
    std::string code = readFile(codeFilePath);
    std::string key = readFile(keyFilePath);

    std::stringstream codeStream(code);
    std::stringstream keyStream(key);

    int numOfCodeWordBeginOfC = 0;
    int numOfKeyWord = 0;

    while (codeStream.good())
    {
        std::string substr;
        std::getline(codeStream, substr, '\n');
        substr = tolower(substr);
        if (substr[0] == 'C' || substr[0] == 'c')
            numOfCodeWordBeginOfC++;
        codeVector.push_back(substr);
    }

    while (keyStream.good())
    {
        std::string substr;
        std::getline(keyStream, substr, '\n');
        numOfKeyWord++;
        maxKeyLength = std::max(maxKeyLength, static_cast<int>(substr.length()));
        keyVector.push_back(substr);
    }

    std::cout << numOfCodeWordBeginOfC << " " << numOfKeyWord << std::endl;
}

void BuildTrieFrom(TrieNode *node, const std::string &str)
{
    if (str.length() <= 0)
    {
        if (!node->isWord)
            leafNum++;
        node->isWord = true;
        return;
    }

    if (node->children.find(str[0]) == node->children.end())
        node->children[str[0]] = new TrieNode();

    BuildTrieFrom(node->children[str[0]], str.substr(1));
}

void printTrie(TrieNode *node, int space)
{
    for (auto &&c : node->children)
    {
        for (int i = 0; i < space; i++)
            std::cout << " ";

        std::cout << c.first << std::endl;
        printTrie(c.second, space + 1);
    }
}

void BuildTrie()
{
    if (!root)
        root = new TrieNode();

    for (auto &&code : codeVector)
    {
        BuildTrieFrom(root, code);
    }
    // printTrie(root, 0);
    std::cout << leafNum << std::endl;
}

int FindCode(TrieNode *node, const std::string &str, int diff)
{
    if (str.length() <= 0)
    {
        if (node->isWord)
            return diff;
        return -1;
    }

    if (diff == -1)
    {
        for (auto &&c : node->children)
        {
            int res = FindCode(c.second, str.substr(1), (str[0] + 26 - c.first) % 26);
            if (res != -1)
                return res;
        }
    }
    else
    {
        if (node->children.find((26 + str[0] - 'a' - diff) % 26 + 'a') == node->children.end())
            return -1;
        return FindCode(node->children[(26 + str[0] - 'a' - diff) % 26 + 'a'], str.substr(1), diff);
    }
    return -1;
}

void CrackCodeInc()
{
    for (int i = 0; i < codeVector.size() && i < keyVector.size(); i++)
    {
        int diff = FindCode(root, keyVector[i], -1);

        int last = 0;
        if (codeToKeyVector.size() > 0)
            last = codeToKeyVector[codeToKeyVector.size() - 1];
        while (diff <= last)
            diff += 26;

        codeToKeyVector.push_back(diff);
    }

    std::cout << codeToKeyVector[0] << " " << codeToKeyVector[codeToKeyVector.size() - 1] << std::endl;
}

std::string GetStrTo(int x, int y)
{
    std::string res;
    while (x >= 0 && y >= 0)
    {
        res += keyVector[x][y];
        x--;
        y--;
    }
    std::string realRes;
    for (int i = res.size() - 1; i >= 0; i--)
        realRes += res[i];

    return realRes;
}

void CodeInCode()
{
    int maxPosX = -1, maxPosY = -1;
    int maxLength = 0;
    std::string maxStr;
    std::vector<std::vector<int>> matrix(keyVector.size(), std::vector<int>(maxKeyLength, 0));
    for (int i = 0; i < keyVector.size(); i++)
        matrix[i][0] = 1;
    for (int i = 0; i < keyVector[0].size(); i++)
        matrix[0][i] = 1;

    for (int i = 1; i < keyVector.size(); i++)
    {
        for (int j = 1; j < keyVector[i].size(); j++)
        {
            if (matrix[i - 1][j - 1] > 0)
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            else
                matrix[i][j] = 1;

            if (matrix[i][j] > maxLength)
            {

                maxLength = matrix[i][j];
                maxPosX = i;
                maxPosY = j;
            }
            else if (matrix[i][j] == maxLength && GetStrTo(maxPosX, maxPosY) > GetStrTo(i, j))
            {
                maxLength = matrix[i][j];
                maxPosX = i;
                maxPosY = j;
            }
        }
    }

    maxStr = GetStrTo(maxPosX, maxPosY);

    if (maxPosX > maxPosY)
    {
        maxPosX = maxPosX - maxPosY;
        maxPosY = 0;
    }
    else
    {
        maxPosX = 0;
        maxPosY = maxPosY - maxPosX;
    }

    std::string verticalStr;
    for (int i = 0; i < keyVector.size(); i++)
    {
        verticalStr += keyVector[i][0];
    }

    if (keyVector.size() > maxLength || (keyVector.size() == maxLength && maxStr > verticalStr))
    {
        maxLength = keyVector.size();
        maxStr = verticalStr;
        maxPosX = 0;
        maxPosY = 0;
    }

    for (int i = 0; i < keyVector.size(); i++)
    {
        if (keyVector[i].size() > maxLength || (keyVector[i].size() == maxLength && maxStr > keyVector[i]))
        {
            maxLength = keyVector[i].size();
            maxStr = keyVector[i];
            maxPosX = i;
            maxPosY = 0;
        }
    }

    std::cout << maxPosX << " " << maxPosY << " " << maxStr << std::endl;
}

int GetCost(char a, char b)
{
    if (a == b)
        return 26;

    return (b + 26 - a) % 26;
}

bool IsDiff(const std::vector<std::pair<std::string, int>> &a, const std::vector<std::pair<std::string, int>> &b)
{
    if (a.size() != b.size())
        return true;

    for (int i = 0; i < a.size() && i < b.size(); i++)
    {
        if (a[i].first.size() != b[i].first.size() || a[i].second != b[i].second)
            return true;
    }
    return false;
}

std::string DealString(const std::string &origin)
{
    std::string res;
    for (int i = 0; i < origin.size(); i++)
    {
        if (i != 0 && i % 20 == 0)
            res += '\n';
        res += origin[i];
    }
    return res;
}

void PathInCode()
{
    std::vector<std::vector<std::pair<std::string, int>>> matrix(keyVector.size(), std::vector<std::pair<std::string, int>>(maxKeyLength, {"", 100000}));
    matrix[0][0] = std::make_pair("", 0);
    for (int i = 1; i < keyVector[0].size(); i++)
        matrix[0][i] = std::make_pair(matrix[0][i - 1].first + "r", matrix[0][i - 1].second + GetCost(keyVector[0][i - 1], keyVector[0][i]));

    for (int i = 1; i < keyVector.size(); i++)
    {
        std::vector<std::pair<std::string, int>> origin;
        while (IsDiff(origin, matrix[i]))
        {
            origin = matrix[i];
            for (int j = 0; j < keyVector[i].size(); j++)
            {
                int minCost = INT_MAX;
                std::string minPath = "";
                if (j > 0 && matrix[i][j - 1].second + GetCost(keyVector[i][j - 1], keyVector[i][j]) < minCost)
                {
                    minCost = matrix[i][j - 1].second + GetCost(keyVector[i][j - 1], keyVector[i][j]);
                    minPath = matrix[i][j - 1].first + 'r';
                }
                if (j < keyVector[i].size() - 1 && matrix[i][j + 1].second + GetCost(keyVector[i][j + 1], keyVector[i][j]) < minCost)
                {
                    minCost = matrix[i][j + 1].second + GetCost(keyVector[i][j + 1], keyVector[i][j]);
                    minPath = matrix[i][j + 1].first + 'l';
                }
                if (matrix[i - 1][j].second + GetCost(keyVector[i - 1][j], keyVector[i][j]) < minCost)
                {
                    minCost = matrix[i - 1][j].second + GetCost(keyVector[i - 1][j], keyVector[i][j]);
                    minPath = matrix[i - 1][j].first + 'd';
                }
                matrix[i][j] = std::make_pair(minPath, minCost);
            }
        }
    }

    std::cout << matrix[keyVector.size() - 1][keyVector[keyVector.size() - 1].size() - 1].first.size() << " " << matrix[keyVector.size() - 1][keyVector[keyVector.size() - 1].size() - 1].second << std::endl;

    writeFile("path.txt", DealString(matrix[keyVector.size() - 1][keyVector[keyVector.size() - 1].size() - 1].first));
}

int main()
{
    LoadData();
    BuildTrie();
    CrackCodeInc();
    CodeInCode();
    PathInCode();
    return 0;
}