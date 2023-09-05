#include "dna.h"

namespace DNA
{
    void LoadData()
    {
        std::string filePath;
        std::ifstream dnaFileStream;
        while (true)
        {
            std::cin >> filePath;
            dnaFileStream.open(filePath, std::ios::in);
            if (dnaFileStream.is_open())
                break;
            else
                std::cout << "open error!" << std::endl;
        }

        int N, E, P;
        dnaFileStream >> N >> E >> P;
        std::vector<std::string> dna;
        for (int i = 0; i < N; i++)
        {
            std::string s;
            dnaFileStream >> s;
            dna.push_back(s);
        }
        dnaConfig = DNAConfig(E, P, dna);
    }

    // DNAType parseDNA(char c)
    // {
    //     switch (c)
    //     {
    //     case 'A':
    //     case 'a':
    //         return DNAType::A;
    //     case 'T':
    //     case 't':
    //         return DNAType::T;
    //     case 'C':
    //     case 'c':
    //         return DNAType::C;
    //     case 'G':
    //     case 'g':
    //         return DNAType::G;
    //     default:
    //         return DNAType::UNKNOWN;
    //     }
    // }

    int LevDist(const std::string &a, const std::string &b)
    {
        std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>(a.size() + 1, std::vector<int>(b.size() + 1, 0));

        for (int i = 1; i <= a.size(); i++)
            matrix[i][0] = i;
        for (int i = 1; i <= b.size(); i++)
            matrix[0][i] = i;

        for (int i = 1; i <= a.size(); i++)
        {
            for (int j = 1; j <= b.size(); j++)
            {
                int minScore = INT_MAX;
                minScore = std::min(minScore, matrix[i - 1][j] + 1);
                minScore = std::min(minScore, matrix[i][j - 1] + 1);
                if (a[i - 1] == b[j - 1])
                    minScore = std::min(minScore, matrix[i - 1][j - 1]);
                else
                    minScore = std::min(minScore, matrix[i - 1][j - 1] + 1);
                matrix[i][j] = minScore;
            }
        }

        return matrix[a.size()][b.size()];
    }

    std::vector<std::string> RangeQuery(const std::vector<std::string> &dna_set, const std::string &target_dna, int eps)
    {
        std::vector<std::string> res;
        for (auto &&dna : dna_set)
            if (LevDist(dna, target_dna) <= eps)
                res.push_back(dna);
        return res;
    }

    void caculteMap(const std::vector<std::string> &dna_set, int eps, int minpts, std::map<std::string, std::vector<std::string>> &coreMap, std::map<std::string, std::vector<std::string>> &borderMap, std::map<std::string, std::vector<std::string>> &outlierMap)
    {
        // first get coreMap
        for (auto &&dna : dna_set)
        {
            auto dna_vector = RangeQuery(dna_set, dna, eps);
            if (dna_vector.size() >= minpts)
                coreMap.insert(std::make_pair(dna, dna_vector));
        }

        // get other maps
        for (auto &&dna : dna_set)
        {
            auto dna_vector = RangeQuery(dna_set, dna, eps);
            if (coreMap.find(dna) != coreMap.end())
                continue;
            if (isInCoreMap(coreMap, dna))
                borderMap.insert(std::make_pair(dna, dna_vector));
            else
                outlierMap.insert(std::make_pair(dna, dna_vector));
        }
    }

    bool isInCoreMap(const std::map<std::string, std::vector<std::string>> &coreMap, const std::string &dna)
    {
        for (auto &&coreDna : coreMap)
            for (auto &&coreDna_v : coreDna.second)
                if (dna.compare(coreDna_v) == 0)
                    return true;

        return false;
    }

    void search(std::vector<std::string> &cluster, const std::map<std::string, std::vector<std::string>> &coreMap, std::set<std::string> &visiterSet, const std::string &dna)
    {
        // have found
        if (visiterSet.find(dna) != visiterSet.end())
            return;

        visiterSet.insert(dna);
        cluster.push_back(dna);

        // not corePoint
        auto iter = coreMap.find(dna);
        if (iter == coreMap.end())
            return;

        for (auto &&next_dna : iter->second)
            search(cluster, coreMap, visiterSet, next_dna);
    }

    std::vector<std::vector<std::string>> DBSCAN(const std::vector<std::string> &dna_set, int eps, int minpts, int &num_cores, int &num_borders, int &num_outliers, int &num_clusters)
    {
        std::map<std::string, std::vector<std::string>> coreMap;
        std::map<std::string, std::vector<std::string>> borderMap;
        std::map<std::string, std::vector<std::string>> outlierMap;

        caculteMap(dna_set, eps, minpts, coreMap, borderMap, outlierMap);

        num_cores = coreMap.size();
        num_borders = borderMap.size();
        num_outliers = outlierMap.size();

        std::set<std::string> visiterSet;
        std::vector<std::vector<std::string>> res;
        for (auto &&corePoint : coreMap)
        {
            if (visiterSet.find(corePoint.first) != visiterSet.end())
                continue;
            std::vector<std::string> cluster;
            search(cluster, coreMap, visiterSet, corePoint.first);
            res.push_back(cluster);
        }
        num_clusters = res.size();
        return res;
    }

    int MinEPS(const std::vector<std::string> &dna_set, int minpts)
    {
        int l = 1, r = INT_MAX;
        while (true)
        {
            std::map<std::string, std::vector<std::string>> coreMap;
            std::map<std::string, std::vector<std::string>> borderMap;
            std::map<std::string, std::vector<std::string>> outlierMap;
            caculteMap(dna_set, l, minpts, coreMap, borderMap, outlierMap);
            if (outlierMap.size() == 0)
            {
                r = l;
                l = l / 2;
                break;
            }
            l *= 2;
        }

        while (l != r)
        {
            std::map<std::string, std::vector<std::string>> coreMap;
            std::map<std::string, std::vector<std::string>> borderMap;
            std::map<std::string, std::vector<std::string>> outlierMap;
            caculteMap(dna_set, (l + r) / 2, minpts, coreMap, borderMap, outlierMap);
            if (outlierMap.size() == 0)
                r = (l + r) / 2;
            else
                l = (l + r) / 2;
        }

        return r;
    }
}

namespace PRINT
{
    void print_step_1(DNA::DNAConfig &dnaConfig)
    {
        int minLen = INT_MAX;
        int maxLen = INT_MIN;
        for (auto &&dna : dnaConfig.Dna)
        {
            minLen = std::min(static_cast<int>(dna.length()), minLen);
            maxLen = std::max(static_cast<int>(dna.length()), maxLen);
        }
        std::cout << minLen << " " << maxLen << std::endl;
    }

    void print_step_2(DNA::DNAConfig &dnaConfig)
    {
        if (dnaConfig.Dna.size() <= 1)
            return;
        std::cout << DNA::LevDist(dnaConfig.Dna[0], dnaConfig.Dna[1]) << std::endl;
    }

    void print_step_3(DNA::DNAConfig &dnaConfig)
    {
        if (dnaConfig.Dna.size() <= 0)
            return;
        std::cout << DNA::RangeQuery(dnaConfig.Dna, dnaConfig.Dna[0], dnaConfig.E).size() << std::endl;
    }

    void print_step_4(DNA::DNAConfig &dnaConfig)
    {
        int num_cores, num_borders, num_outliers, num_clusters;
        auto res = DNA::DBSCAN(dnaConfig.Dna, dnaConfig.E, dnaConfig.P, num_cores, num_borders, num_outliers, num_clusters);
        std::cout << num_cores << " " << num_borders << " " << num_outliers << " " << num_clusters << std::endl;
    }

    void print_step_5(DNA::DNAConfig &dnaConfig)
    {
        std::cout << DNA::MinEPS(dnaConfig.Dna, dnaConfig.P) << std::endl;
    }
}

int main()
{
    using namespace DNA;
    LoadData();
    PRINT::print_step_1(dnaConfig);
    PRINT::print_step_2(dnaConfig);
    PRINT::print_step_3(dnaConfig);
    PRINT::print_step_4(dnaConfig);
    PRINT::print_step_5(dnaConfig);
}