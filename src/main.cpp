// #include "coloreo.h"
#include "renderDrawG.h"
#include <iostream>
using namespace std;

int main() {
  int valorE;
  int valorColor;
  CGraph br;

  cout << "Las opciones son 0 y 1:\n(0)-Grafo 01\n(1)-Grafo 02\nLa "
          "opcion: ";
  cin >> valorE;
  cout << "La opcion de coloreo\n(0)-Restringivo\n(1)-Restrictivo\nLa opcion: ";
  cin >> valorColor;

  switch (valorE) {
  case 0:
    br.InsertNode('A', 1, 0, 0);
    br.InsertNode('B', 1, 1, 0);
    br.InsertNode('C', 1, 2, 0);
    br.InsertNode('D', 1, 3, 0);
    br.InsertNode('E', 1, 4, 0);

    br.InsertEdge(br.nodos1[0], br.nodos1[1], 2);
    br.InsertEdge(br.nodos1[0], br.nodos1[4], 2);
    br.InsertEdge(br.nodos1[0], br.nodos1[3], 2);

    br.InsertEdge(br.nodos1[4], br.nodos1[0], 2);
    br.InsertEdge(br.nodos1[4], br.nodos1[3], 2);
    br.InsertEdge(br.nodos1[3], br.nodos1[2], 2);
    br.InsertEdge(br.nodos1[2], br.nodos1[1], 2);

    if (valorColor == 0) {
      br.color_disponible1();
    } else {
      char val;
      int valorZ;
      cout << "nombreColor: ";
      cin >> val;
      cout << "\ncolor: ";
      cin >> valorZ;
      for (size_t i = 0; i < br.nodos1.size(); i++) {
        if (val == br.nodos1[i]->name) {
          br.nodos1[i]->color = valorZ;
          break;
        }
      }

      br.color_disponible2();
    }

    // for (size_t i = 0; i < br.nodos1.size(); i++) {
    //   cout << br.nodos1[i]->name << ' ' << br.nodos1[i]->color << '\n';
    // }
    renderGraphColor(1, br.nodos1, valorColor);
    break;
  case 1:
    br.InsertNode('A', 1, 0, 0);
    br.InsertNode('B', 1, 1, 0);
    br.InsertNode('C', 1, 2, 0);
    br.InsertNode('D', 1, 3, 0);
    br.InsertNode('E', 1, 4, 0);
    br.InsertNode('F', 1, 5, 0);
    br.InsertNode('G', 1, 6, 0);
    br.InsertEdge(br.nodos1[0], br.nodos1[1], 2);
    br.InsertEdge(br.nodos1[1], br.nodos1[2], 2);
    br.InsertEdge(br.nodos1[0], br.nodos1[3], 2);

    br.InsertEdge(br.nodos1[2], br.nodos1[3], 2);
    br.InsertEdge(br.nodos1[3], br.nodos1[4], 2);
    br.InsertEdge(br.nodos1[2], br.nodos1[5], 2);
    br.InsertEdge(br.nodos1[3], br.nodos1[5], 2);
    br.InsertEdge(br.nodos1[4], br.nodos1[5], 2);
    br.InsertEdge(br.nodos1[4], br.nodos1[6], 2);
    br.InsertEdge(br.nodos1[5], br.nodos1[6], 2);
    br.InsertEdge(br.nodos1[1], br.nodos1[6], 2);
    if (valorColor == 0) {
      br.color_disponible1();
    } else {
      char val;
      int valorZ;
      cout << "nombreColor: ";
      cin >> val;
      cout << "\ncolor: ";
      cin >> valorZ;
      for (size_t i = 0; i < br.nodos1.size(); i++) {
        if (val == br.nodos1[i]->name) {
          br.nodos1[i]->color = valorZ;
          break;
        }
      }

      br.color_disponible2();
    }
    // for (size_t i = 0; i < br.nodos1.size(); i++) {
    //   cout << br.nodos1[i]->name << ' ' << br.nodos1[i]->color << '\n';
    // }
    renderGraphColor(0, br.nodos1, valorColor);
    break;
  default:
    cout << "Intenta con los valor 0 o 1.";
    break;
  }
  return 0;
}
// color_disponible1 = restringiva
// color_disponible2 = restrictiva
