//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, Indiana University,
// Bloomington, IN 47405.
//
// Permission to modify the code and to distribute the code is
// granted, provided the text of this NOTICE is retained, a notice if
// the code was modified is included with the above COPYRIGHT NOTICE
// and with the COPYRIGHT NOTICE in the LICENSE file, and that the
// LICENSE file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
#include <boost/config.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>

int
main()
{
  using namespace boost;
  typedef adjacency_list<vecS, vecS, directedS, no_property,
    property< edge_weight_t, int, property< edge_weight2_t, int > > > Graph;
  const int V = 5;
  typedef std::pair < int, int >Edge;
  Edge edge_array[] =
    { Edge(0, 1), Edge(0, 4), Edge(0, 2), Edge(1, 3), Edge(1, 4),
    Edge(2, 1), Edge(3, 2), Edge(3, 0), Edge(4, 3)
  };
  const std::size_t E = sizeof(edge_array) / sizeof(Edge);
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // VC++ can't handle the iterator constructor
  Graph g(V);
  for (std::size_t j = 0; j < E; ++j)
    add_edge(edge_array[j].first, edge_array[j].second, g);
#else
  Graph g(edge_array, edge_array + E, V);
#endif

  property_map < Graph, edge_weight_t >::type w = get(edge_weight, g);
  int weights[] = { 3, -4, 8, 1, 7, 4, -5, 2, 6 };
  int *wp = weights;

  graph_traits < Graph >::edge_iterator e, e_end;
  for (boost::tie(e, e_end) = edges(g); e != e_end; ++e)
    w[*e] = *wp++;

  std::vector < int >d(V, (std::numeric_limits < int >::max)());
  int D[V][V];
  johnson_all_pairs_shortest_paths(g, D, distance_map(&d[0]));

  std::cout << "     ";
  for (int k = 0; k < V; ++k)
    std::cout << std::setw(5) << k;
  std::cout << std::endl;
  for (int i = 0; i < V; ++i) {
    std::cout << i << " -> ";
    for (int j = 0; j < V; ++j) {
      if (D[i][j] > 20 || D[i][j] < -20)
        std::cout << std::setw(5) << "inf";
      else
        std::cout << std::setw(5) << D[i][j];
    }
    std::cout << std::endl;
  }

  std::ofstream fout("figs/johnson-eg.dot");
  fout << "digraph A {\n"
    << "  rankdir=LR\n"
    << "size=\"5,3\"\n"
    << "ratio=\"fill\"\n"
    << "edge[style=\"bold\"]\n" << "node[shape=\"circle\"]\n";

  graph_traits < Graph >::edge_iterator ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    fout << source(*ei, g) << " -> " << target(*ei, g)
      << "[label=" << get(edge_weight, g)[*ei] << "]\n";

  fout << "}\n";
  return 0;
}
