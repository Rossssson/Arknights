//
// Created by rossssson on 2022/4/24.
//

#include "find.h"
#include <cstdlib>
#include "iostream"
#include <random>
#include <ctime>
#include <algorithm>

#define STAGE_MIN 1
#define STAGE_ONE_MAX 100
#define STAGE_TWO_MAX 10
#define STAGE_THREE_MAX 2


static std::default_random_engine engine_1(std::time(NULL));
static std::default_random_engine engine_2(std::time(0));
static std::default_random_engine engine_3(114514);

std::vector<int> seq_one;
std::vector<int> seq_two;

void find::run() {
    find::chou();
    if (find::total<300)
    {
        std::cout<<"共"<<find::total<<"抽出货\n";
    } else if (find::total>=300)
    {
        std::cout<<"恭喜您，吃井了\n";
    }
    }

void find::chou() {
   bool ifGet= false;
    for (int i = 1; i <101 ; ++i) {
        seq_one.push_back(i);
    }
    for (int j = 1; j <11 ; ++j) {
        seq_two.push_back(j);
    }
    std::shuffle(seq_one.begin(),seq_one.end(), std::mt19937(std::random_device()()));
    std::shuffle(seq_two.begin(),seq_two.end(), std::mt19937(std::random_device()()));
    while (!ifGet&&find::total<300)
    {
        ifGet= xunfang();
    }

}

bool find::xunfang() {
    int before_six=1;
    int fixed_poss=2;
    while (!do_stage_one(fixed_poss))
    {
        before_six++;
        fixed_poss=(before_six<50)?(2):(2+2*(before_six-50));
    }
    std::cout<<before_six<<"抽出了六星";
    find::total+=before_six;
    if (find::do_stage_two())
    {
        if (find::do_stage_three())
        {
            return true;
        }
    }
    return false;
}

bool find::do_stage_one(int poss)
{
    /*产生随机数*/
    std::uniform_int_distribution<> distribution(1,100);
    int random=distribution(engine_1);
    /*划范围*/
    for (int i = 0; i <poss ; ++i) {
        if (random==seq_one[i])
        {
            return true;//出了六星
        }
    }
    return false;
}

bool find::do_stage_two()
{
    std::uniform_int_distribution<> distribution_2(1,10);
    int random_2=distribution_2(engine_2);
    for (int i = 0; i < 7; ++i) {
        if (random_2==seq_two[i])
        {
            return true;//出了限定或者陪跑
        }
    }
    std::cout<<"歪了\t";
    return false;//歪了
}

bool find::do_stage_three()
{
    std::uniform_int_distribution<> distribution_2(1,2);
    int random_2=distribution_2(engine_3);
    if (random_2==1)
    {
        return true;//出货
    }
    std::cout<<"陪跑了\t";
    return false;//陪跑

}


