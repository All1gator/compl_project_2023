#include <iostream>
#include <vector>

class WeightedVertexCover{
private:
  std::vector<int> answer;
  long long ans = 0;
  std::vector<std::vector<int> > graf; // представление в виде матрицы смежности
  std::vector<long long> weights;
  std::vector<long long> old_weights;
  std::vector<int> degs;
  std::vector<bool> used;

  void Solve() {
    old_weights = weights;
    int n = graf.size();
    used.resize(n, 0);
    degs.resize(n, 0);
    //Считаем степени
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        degs[i] += graf[i][j];
      }
    }

    //начинаем наш алгоритм
    for (int i = 0; i < n; ++i) {
      //ищем подходящую вершину, та у которой отношение веса к степени вершины минимально
      int id = -1;
      double minn = 1e15;
      for (int j = 0; j < n; ++j) {
        if (!used[j] && degs[j] > 0) {
          if (minn > static_cast<double>(weights[j]) / degs[j]) {
            id = j;
            minn = static_cast<double>(weights[j]) / degs[j];
          }
        }
      }

      //посетили все рёбра
      if (id == -1) {
        break;
      }

      //Добавляем в ответ
      answer.push_back(id + 1);
      ans += old_weights[id];
      used[id] = 1;
      //Релаксируем оставшийся граф
      for (int j = 0; j < n; ++j) {
        if (graf[id][j]) {
          degs[j]--;
          weights[j] -= minn;
        }
      }
    }
  }

public:

  WeightedVertexCover(std::vector<std::vector<int> >& g, std::vector<long long>& w): graf(g), weights(w) {
    Solve();
  }

  long long GetAnsSum() {
    return ans;
  }

  std::vector<int> GetAnsVerticles() {
    return answer;
  }

  void WriteAnsSum() {
    std::cout << ans << '\n';
  }

  void WriteAnsVerticles() {
    for (auto u : answer) {
      std::cout << u << ' ';
    }
    std::cout << '\n';
  }
};
