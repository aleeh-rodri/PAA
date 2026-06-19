#ifndef ALGORITMOS_H_INCLUDED
#define ALGORITMOS_H_INCLUDED

#include <vector>
#include <string>

void printGrafo(const std::string& titulo, const std::vector<std::vector<int>>& adj);

std::vector<std::vector<int>> reducaoDFS(int V, const std::vector<std::vector<int>>& adj);
std::vector<std::vector<int>> reducaoBFS(int V, const std::vector<std::vector<int>>& adj);
std::vector<std::vector<int>> reducaoTransitivaMemoization(int V, const std::vector<std::vector<int>>& adj);
std::vector<std::vector<int>> reducaoTransitivaTarjan(int V, const std::vector<std::vector<int>>& adj);
std::vector<std::vector<int>> reducaoWarshall(int V, const std::vector<std::vector<int>>& adj);

#endif
