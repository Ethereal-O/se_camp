#include <bits/stdc++.h>
namespace DNA
{
    // enum DNAType
    // {
    //     A,
    //     T,
    //     C,
    //     G,
    //     UNKNOWN
    // };

    class DNAConfig
    {
    public:
        DNAConfig() {}
        DNAConfig(int e, int p, std::vector<std::string> &dna) : E(e), P(p), Dna(dna){};
        int E;
        int P;
        std::vector<std::string> Dna;
    };

    DNAConfig dnaConfig;

    void LoadData();
    // DNAType parseDNA(char c);
    int LevDist(const std::string &a, const std::string &b);
    std::vector<std::string> RangeQuery(const std::vector<std::string> &dna_set, const std::string &target_dna, int eps);
    void caculteMap(const std::vector<std::string> &dna_set, int eps, int minpts, std::map<std::string, std::vector<std::string>> &coreMap, std::map<std::string, std::vector<std::string>> &borderMap, std::map<std::string, std::vector<std::string>> &outlierMap);
    bool isInCoreMap(const std::map<std::string, std::vector<std::string>> &coreMap, const std::string &dna);
    void search(std::vector<std::string> &cluster, const std::map<std::string, std::vector<std::string>> &coreMap, std::set<std::string> &visiterSet, const std::string &dna);
    std::vector<std::vector<std::string>> DBSCAN(const std::vector<std::string> &dna_set, int eps, int minpts, int &num_cores, int &num_borders, int &num_outliers, int &num_clusters);
    int MinEPS(const std::vector<std::string> &dna_set, int minpts);
}

namespace PRINT
{
    void print_step_1(DNA::DNAConfig &dnaConfig);
    void print_step_2(DNA::DNAConfig &dnaConfig);
    void print_step_3(DNA::DNAConfig &dnaConfig);
    void print_step_4(DNA::DNAConfig &dnaConfig);
    void print_step_5(DNA::DNAConfig &dnaConfig);
}