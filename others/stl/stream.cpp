#include "bits/stdc++.h"

std::string readFile1(const std::string &filename)
{
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

std::string readFile2(const std::string &filename)
{
    std::ifstream file(filename.data(), std::ios::in);
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

void writeFile(const std::string &filename, const std::string &content)
{
    std::ofstream ofs(filename);
    ofs << content;
    ofs.close();
}

std::vector<std::string> split1(const std::string &s, const std::string &delim)
{
    std::vector<std::string> res;
    if ("" == delim)
    {
        res.push_back(s);
        return res;
    }
    std::string::size_type pos1, pos2;
    pos2 = s.find(delim);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        res.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delim.size();
        pos2 = s.find(delim, pos1);
    }
    if (pos1 != s.length())
        res.push_back(s.substr(pos1));
    return res;
}

std::vector<std::string> split2(const std::string &s, const std::string &delim)
{
    std::vector<std::string> res;
    if ("" == delim)
    {
        res.push_back(s);
        return res;
    }
    std::istringstream iss(s);
    std::string tmp;
    while (std::getline(iss, tmp, delim[0]))
        res.push_back(tmp);
    return res;
}

std::string getFirstLine(const std::string &s)
{
    std::istringstream iss(s);
    std::string line;
    std::getline(iss, line);
    return line;
}

std::string getFirstLine()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string intToString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

int stringToInt(const std::string &s)
{
    std::stringstream ss(s);
    int num;
    ss >> num;
    return num;
}

int main()
{
    // // read file
    // std::cout << readFile1("./stl/stream.cpp") << std::endl;
    // std::cout << readFile2("./stl/stream.cpp") << std::endl; // this method must make sure the file is stored in LF format

    // // read from cin and getline
    // int intValue;
    // std::string strValue;
    // std::cin >> intValue;
    // std::cin.ignore(); // ignore the '\n' in the buffer
    // std::getline(std::cin, strValue);

    // // write file
    // writeFile("./stl/test.txt", "hello world");

    // // split string
    // std::string s = "1,2,3,4,5\nand more 1,2,3,4";
    // std::vector<std::string> res = split1(s, "3,");
    // // std::vector<std::string> res = split2(s, ","); // this method can't split multiple delimiters
    // for (auto &i : res)
    //     std::cout << i << std::endl;

    // // convert
    // std::string s = "123";
    // int num = stringToInt(s);
    // std::cout << num << std::endl;
    // std::cout << intToString(num) << std::endl;
}