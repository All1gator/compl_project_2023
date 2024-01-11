#pragma once

#include "WeightedVertexCover.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

mt19937 rn(time(NULL));

const int MaxSize = 18;

struct graf{
  vector<vector<int>> g;
  vector<long long> w;
  int m;
};


graf generate_graf(bool plot) {
  int n = rn() % (MaxSize - 5) + 5;
  graf now;
  vector<vector<int> > g(n, vector<int> (n));
  vector<long long> w(n);
  int k = 0;
  if (plot) {
    //плотный граф
    int m = ((rn() % (n/2)) + n/2);
    int l = ((rn() % (n/2)) + n/2 - 1);
    k = m * l / 2;
  } else {
    k = rn() % (n * int(sqrt(n)));
  }
  //костыль, чтобы не было nan в тестах
  if (k == 0) {
    k = n;
  }
  while (k > 0) {
    int i = rn() % n;
    int j = rn() % n;
    if (i != j && g[i][j] == 0) {
      k--;
      g[i][j] = 1;
      g[j][i] = 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    w[i] = (rn() % 100000) + 10;
  }
  now.g = g;
  now.w = w;
  now.m = k;
  return now;
}

long long bruteforce(graf& now) {
  auto g = now.g;
  auto w = now.w;
  long long answer = 1e9;
  int mask = 0;
  int n = g.size();

  for (int mask = 0; mask < (1 << g.size()); ++mask) {
    int num = now.m;
    long long now_answer = 0;
    for (int i = 0; i < n; ++i) {
      if (((1 << i) & mask) > 0) {
        now_answer += w[i];
      }
    }
    bool yes = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (g[i][j]) {
          if (((mask & (1 << i)) > 0) || ((mask & (1 << j)) > 0)) {
            continue;
          }
          yes = 0;
        }
      }
    }
    if (yes) {
      answer = min(answer, now_answer);
    }
  }
  return answer;
}



void test(bool type_test){
  cerr << "!!!" << endl;
  auto now = generate_graf(type_test);
  auto g = now.g;
  auto w = now.w;
  long long PerfectAns = bruteforce(now);
  WeightedVertexCover our(g, w);
  long long OurAns = our.GetAnsSum();
  cout << OurAns << '\n' << PerfectAns << '\n' << OurAns - PerfectAns << '\n' << double(OurAns)/PerfectAns << endl;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    //freopen("abbreviation.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n = 1000;
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
      test(0);
    }

    return 0;
}
