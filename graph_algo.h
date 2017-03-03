/**

Copyright 2017 Mayank Mathur

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef ERROR_SUBMISSION_9THSKY
#include "error_submission.h"
#endif

#ifndef GRAPH_ALGO_9THSKY
#define GRAPH_ALGO_9THSKY

#include <utility>
#include <map>
#include <vector>
#include <list>

#include "graph.h"

namespace ninth_sky
{
	struct algorithms_graph
	{
		/**
		*	@brief		Uses the Breadth-First Transversal Algorithm
		*				to return a vector of the vertexes transversed from source.
		*   @param      graph <VERTEX_TYPE>     :   Graph on which algorithm should
		*                                           be used.
		*   @param      src                     :   Source vertex
		*/
		template <typename VERTEX_TYPE>
		std::vector <VERTEX_TYPE> breadthFirstTransversal (ninth_sky::graph <VERTEX_TYPE> & g, const VERTEX_TYPE& src)
		{
			std::vector <VERTEX_TYPE> v;
			v.resize(g.vertexCount());
			std::list <VERTEX_TYPE> q;
			std::map <VERTEX_TYPE, bool> check;
			q.push_back (src);
			check[src] = true;
			while (!q.empty())
			{
				v.push_back(q.front());
				std::vector < std::pair <VERTEX_TYPE, int> > n = g.getNeighbours(q.front());
				check[q.front()] = true;
				q.pop_front();

				for (auto i = n.begin(); i != n.end(); i++)
				{
					if (check[(*i).first] == false)
						q.push_back((*i).first);
				}
			}
			return v;
		}

		/**
		*	@brief		Uses the Breadth-First Search Algorithm
		*				to check whether a vertex is present in graph.
		*   @param      graph <VERTEX_TYPE>     :   Graph on which algorithm should
		*                                           be used.
		*   @param      src                     :   Source vertex
		*/
		template <typename VERTEX_TYPE>
		bool breadthFirstSearch (ninth_sky::graph <VERTEX_TYPE> & g, const VERTEX_TYPE& src, const VERTEX_TYPE& dest)
		{
			if (src == dest)
				return true;
			std::list <VERTEX_TYPE> q;
			std::map <VERTEX_TYPE, bool> check;
			q.push_back (src);
			check[src] = true;
			while (!q.empty())
			{
				std::vector < std::pair <VERTEX_TYPE, int> > n = g.getNeighbours(q.front());
				check[q.front()] = true;
				q.pop_front();

				for (auto i = n.begin(); i != n.end(); i++)
				{
					if (check[(*i).first] == false)
					{
						if ((*i).first == dest)
							return true;
						q.push_back((*i).first);
					}
				}
			}
			return false;
		}

		/**
		*   @brief      Uses the Bellman-Ford Algorithm to find shortest path
		*               between a source vertex and all others.
		*               Returns the path weight.
		*   @param      graph <VERTEX_TYPE>     :   Graph on which algorithm should
		*                                           be used.
		*   @param      src                     :   Source vertex
		*/
		template <typename VERTEX_TYPE>
		std::map <VERTEX_TYPE, int> bellman_ford (ninth_sky::graph <VERTEX_TYPE> & g, const VERTEX_TYPE& src)
		{
			std::map <VERTEX_TYPE, int> distance;
			for (VERTEX_TYPE vt : g.getAllVertexesById())
				distance[vt] = INT_MAX;
			distance[src] = 0;

			std::vector < std::pair <VERTEX_TYPE, int> > tmp;
			bool change = true;
			int count = 0;

			while (change && count++ < g.vertexCount())
			{
				change = false;
				for (std::pair <VERTEX_TYPE, int> u : distance)					/// u -> {VERTEX_TYPE, path_weight}
				{
					if (u.second != INT_MAX)
					{
						for (std::pair <VERTEX_TYPE, int> n : g.getNeighbours(u.first))
						{
							int weight = u.second + n.second;
							if (distance[n.first] > weight && n.first != src)
							{
								change = true;
								distance[n.first] = weight;
							}
						}
					}
				}
			}

			return distance;
		}
	} Algorithms_graph;
}


#endif
