#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <vector>
using namespace std;

struct CEdge;

struct CNode {
  CNode(char name1, float x1, float y1, int color1) {
    name = name1;
    valuex = x1;
    valuey = y1;
    color = color1;
  }

  list<CEdge *> edges;
  int valuex;
  int valuey;
  char name;
  int color = 0;
  bool estado = 1;
  int hermanos = 0;
  list<int> cdisponibles = {};
  int strike = 0;
  int disponible = 0;
};

struct CEdge {
  CEdge(CNode *a, CNode *b, float distance) {
    nodes[0] = a;
    nodes[1] = b;
    distancia = distance;
    nodes[0]->edges.push_back(this);
    nodes[1]->edges.push_back(this);
  }

  ~CEdge() {}

  CNode *nodes[2];
  float distancia;
};

class CGraph {
public:
  bool InsertNode(char name, int x, int y, int color) {
    nodos1.push_back(new CNode(name, x, y, color));
    return true;
  }

  bool InsertEdge(CNode *a, CNode *b, float dist) {
    new CEdge(a, b, dist);
    a->hermanos++;
    b->hermanos++;
    return true;
  }

  void color_disponible1() {
    ordenar();
    for (size_t i = 0; i < nodos1.size(); i++) {
      cout << nodos1[i]->name << ' ' << nodos1[i]->color << '\n';
    }

    vector<CNode *> copia(nodos1);
    vector<CNode *> eliminados = {};
    while (copia.size()) {
      list<int> color;
      color.assign(colores.begin(), colores.end());
      for (auto edge : copia[0]->edges) {
        if (copia[0] == edge->nodes[1]) {
          color.remove(edge->nodes[0]->color);

        } else {
          color.remove(edge->nodes[1]->color);
        }
      }
      if (color.size() == 0) {
        for (size_t u = eliminados.size() - 1; u >= 0; u--) {
          if (!eliminados[u]->cdisponibles.size()) {
            eliminados[u]->color = 0;
            copia.insert(copia.begin(), eliminados[u]);
            eliminados.erase(eliminados.begin() + u);

          } else if (eliminados[u]->disponible >= eliminados[u]->strike) {
            eliminados[u]->color = eliminados[u]->cdisponibles.front();
            eliminados[u]->cdisponibles.pop_front();
            eliminados[u]->strike = eliminados[u]->strike + 1;
            break;
          } else {
            eliminados[u]->color = 0;
            copia.insert(copia.begin(), eliminados[u]);
            eliminados.erase(eliminados.begin() + u);
          }
        }
        continue;
      } else {
        copia[0]->color = color.front();
        eliminados.push_back(copia[0]);
        copia[0]->strike = copia[0]->strike + 1;
        copia[0]->cdisponibles.clear();
        copia[0]->disponible = color.size();
        color.pop_front();
        copia[0]->cdisponibles.assign(color.begin(), color.end());
        copia.erase(copia.begin());
      }
    }
    /*for (size_t i = 0; i < nodos1.size(); i++) {

        color.assign(colores.begin(), colores.end());
        for (auto edge : nodos1[i]->edges) {

            color.remove(edge->nodes[0]->color);
            color.remove(edge->nodes[1]->color);
        }
        nodos1[i]->color = color.front();

    }*/
  }
  void ordenar() {
    auto comparador = [](const CNode *a, const CNode *b) {
      return a->hermanos > b->hermanos;
    };
    sort(nodos1.begin(), nodos1.end(), comparador);
  }
  void color_disponible2() {
    vector<CNode *> copia(nodos1);
    vector<CNode *> eliminados = {};
    list<int> color;
    list<int> color2;

    while (copia.size()) {

      int iterator = 0;

      color.assign(colores.begin(), colores.end());
      for (CEdge *d : copia[0]->edges) {
        if (copia[0] == d->nodes[1]) {
          color.remove(d->nodes[0]->color);

        } else {
          color.remove(d->nodes[1]->color);
        }
      }
      color2.assign(color.begin(), color.end());

      for (size_t i = 1; i < copia.size(); i++) {
        color.assign(colores.begin(), colores.end());
        // cout << copia[i]->name << '\n';
        for (CEdge *d : copia[i]->edges) {
          if (copia[i] == d->nodes[1]) {
            color.remove(d->nodes[0]->color);
            // cout << 1 << '\n';
          } else {
            color.remove(d->nodes[1]->color);
            // cout << 1 << '\n';
          }
        }
        // cout <<color.size() << ' ' << color2.size() << '\n';
        if (color.size() < color2.size()) {

          color2.assign(color.begin(), color.end());
          iterator = i;
        }
      }
      cout << copia[iterator]->name << "e" << '\n';
      if (copia[iterator]->color == 0) {
        if (color2.size() == 0) {
          for (size_t u = eliminados.size() - 1; u >= 0; u--) {
            if (!eliminados[u]->cdisponibles.size()) {
              eliminados[u]->color = 0;
              copia.push_back(eliminados[u]);
              eliminados.erase(eliminados.begin() + u);

            } else if (eliminados[u]->disponible >= eliminados[u]->strike) {
              eliminados[u]->color = eliminados[u]->cdisponibles.front();
              eliminados[u]->cdisponibles.pop_front();
              eliminados[u]->strike = eliminados[u]->strike + 1;
              break;
            } else {
              eliminados[u]->color = 0;
              copia.push_back(eliminados[u]);
              eliminados.erase(eliminados.begin() + u);
            }
          }
          continue;
        } else {
          // cout << color2.front() << '\n';
          copia[iterator]->color = color2.front();
          copia[iterator]->disponible = color2.size();
          color2.pop_front();
          copia[iterator]->cdisponibles.clear();
          copia[iterator]->cdisponibles.assign(color2.begin(), color2.end());
          copia[iterator]->strike = copia[iterator]->strike + 1;
        }
      }
      eliminados.push_back(copia[iterator]);
      copia.erase(copia.begin() + iterator);
    }
  }

public:
  list<int> colores = {1, 2, 3};
  vector<CNode *> nodos1;
};
