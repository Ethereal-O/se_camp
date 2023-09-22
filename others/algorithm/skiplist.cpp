#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <climits>
#include <time.h>

#define MAX_LEVEL 8

enum SKNodeType
{
    HEAD = 1,
    NORMAL,
    NIL
};

struct SKNode
{
    int key;
    int val;
    SKNodeType type;
    std::vector<SKNode *> forwards;
    SKNode(int _key, int _val, SKNodeType _type)
        : key(_key), val(_val), type(_type)
    {
        for (int i = 0; i < MAX_LEVEL; ++i)
        {
            forwards.push_back(nullptr);
        }
    }
};

class SkipList
{
private:
    SKNode *head;
    SKNode *NIL;
    unsigned long long s = 1;
    double my_rand()
    {
        s = (16807 * s) % 2147483647ULL;
        return (s + 0.0) / 2147483647ULL;
    }
    int randomLevel()
    {
        int result = 1;
        while (result < MAX_LEVEL && my_rand() < 0.5)
        {
            ++result;
        }
        // std::cout<<result<<std::endl;
        return result;
    }

public:
    SkipList()
    {
        head = new SKNode(0, 0, SKNodeType::HEAD);
        NIL = new SKNode(INT_MAX, 0, SKNodeType::NIL);
        for (int i = 0; i < MAX_LEVEL; ++i)
        {
            head->forwards[i] = NIL;
        }
    }
    void Insert(int key, int value)
    {
        // TODO
        SKNode *tmpnode = head;
        SKNode *update[MAX_LEVEL];
        for (int i = MAX_LEVEL - 1; i >= 0; i--)
        {
            if (tmpnode->key == key)
            {
                tmpnode->val = value;
                return;
            }
            while (tmpnode->forwards[i]->key <= key)
            {
                tmpnode = tmpnode->forwards[i];
            }
            update[i] = tmpnode;
        }
        if (tmpnode->key == key)
        {
            tmpnode->val = value;
            return;
        }
        SKNode *newnode = new SKNode(key, value, NORMAL);
        int level = randomLevel();
        // std::cout << level << std::endl;
        for (int i = 0; i < level; i++)
        {
            SKNode *knode = update[i]->forwards[i];
            newnode->forwards[i] = knode;
            update[i]->forwards[i] = newnode;
        }
    }
    void Search(int key)
    {
        // TODO
        SKNode *tmpnode = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--)
        {
            if (tmpnode->key == 0)
            {
                // std::cout << i + 1 << ",h " ;
            }
            else
            {
                // std::cout << i + 1 << "," << tmpnode->key<<" ";
            }
            while (tmpnode->forwards[i]->key < key)
            {
                tmpnode = tmpnode->forwards[i];
                // std::cout << i+1<<"," << tmpnode->key<<" ";
            }
        }
        tmpnode = tmpnode->forwards[0];
        if (tmpnode == NIL)
        {
            // std::cout << "1,N"<< " ";
        }
        else
        {
            // std::cout << "1," << tmpnode->key << " ";
        }

        if (tmpnode->key == key)
        {
            // std::cout << tmpnode->val << std::endl;
            return;
        }
        else
        {
            // std::cout << "Not Found" << std::endl;
        }
    }
    void Search(int lkey, int rkey)
    {
        SKNode *tmpnode = head;
        for (int i = MAX_LEVEL - 1; i >= 0; i--)
        {
            if (tmpnode->key == 0)
            {
                // std::cout << i + 1 << ",h " ;
            }
            else
            {
                // std::cout << i + 1 << "," << tmpnode->key<<" ";
            }
            while (tmpnode->forwards[i]->key < lkey)
            {
                tmpnode = tmpnode->forwards[i];
                // std::cout << i+1<<"," << tmpnode->key<<" ";
            }
        }
        tmpnode = tmpnode->forwards[0];
        if (tmpnode == NIL)
        {
            // std::cout << "1,N"<< " ";
        }
        else
        {
            // std::cout << "1," << tmpnode->key << " ";
        }

        if (tmpnode->key == lkey)
        {
            // std::cout << tmpnode->val << std::endl;
            while (tmpnode->key <= rkey)
            {
                tmpnode = tmpnode->forwards[0];
            }
            return;
        }
        else
        {
            // std::cout << "Not Found" << std::endl;
        }
    }
    void Delete(int key)
    {
        // TODO
        SKNode *tmpnode = head;
        SKNode *pre[MAX_LEVEL];
        for (int i = MAX_LEVEL - 1; i >= 0; i--)
        {
            while (tmpnode->forwards[i]->key < key)
            {
                tmpnode = tmpnode->forwards[i];
            }
            pre[i] = tmpnode;
        }
        for (int i = MAX_LEVEL - 1; i >= 0; i--)
        {
            if (pre[i]->forwards[i]->key == key)
            {
                pre[i]->forwards[i] = pre[i]->forwards[i]->forwards[i];
            }
        }
    }
    void Display()
    {
        for (int i = MAX_LEVEL - 1; i >= 0; --i)
        {
            std::cout << "Level " << i + 1 << ":h";
            SKNode *node = head->forwards[i];
            while (node->type != SKNodeType::NIL)
            {
                std::cout << "-->(" << node->key << "," << node->val << ")";
                node = node->forwards[i];
            }

            std::cout << "-->N" << std::endl;
        }
    }
    ~SkipList()
    {
        SKNode *n1 = head;
        SKNode *n2;
        while (n1)
        {
            n2 = n1->forwards[0];
            delete n1;
            n1 = n2;
        }
    }
};
