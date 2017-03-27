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
#include "error_submission.hpp"
#endif

#ifndef GRAPH_9THSKY
#define GRAPH_9THSKY


#include <vector>
#include <map>
#include <utility>

namespace ninth_sky
{
	/**
	*	@brief	Vertex class has properties -> id (int), neighbous: {neighbous, weights}, initialised (T/F)
	*/
	template <typename ID_TYPE>
	class vertex: public object
	{
		public:
			ID_TYPE id;
			std::vector < std::pair < ID_TYPE, int > > neighbous;
			bool initialised		= false;
	};

	template <typename VERTEX_TYPE>
	class graph: public object
	{
		private:
			std::map < VERTEX_TYPE, vertex <VERTEX_TYPE> > vertices;
			int vertex_count = 0;

		public:
			/**
			*   @brief	  Adds a vertex to the graph.
			*   @param	  VERTEX_TYPE a   :   The vertex ID
			*/
			void addVertex (VERTEX_TYPE a)
			{
				vertex <VERTEX_TYPE> v;
				v.id = a;
				v.initialised = true;
				this -> vertices[a] = v;
				this -> vertex_count++;
				//ninth_sky::error_report.debug_write("Adding new vertex: " + std::to_string(a));
			}

			/**
			*   @brief	  Adds a directed and weighted connection from vertex
			*			   u to v.
			*   @param	  VERTEX_TYPE v         :   Primary vertex, i.e., vertex from which
			*								        connection has to be extended.
			*   @param	  VERTEX_TYPE u         :   Secondary vertex, i.e, vertex to which
			*								        connection has to be extended.
			*   @param	  int weight	        :   edge/path weight from v -> u
			*   @param    bool bidirectional    :   set true if the path is
			*                                       bidirectional, false if directed.
			*/
			void addNeighbour (VERTEX_TYPE v, VERTEX_TYPE u, int weight, bool bidirectional = false)
			{
				if (!vertices[v].initialised || !vertices[u].initialised)
					return;
				this -> vertices[v].neighbous.push_back({u, weight});
				if (bidirectional == true)
                    this -> vertices[u].neighbous.push_back({v, weight});
				/*ninth_sky::error_report.debug_write
					("Setting " + std::to_string(u) + " as a neighbour of " + std::to_string(v) + " with weight " + std::to_string(weight));*/
			}

			/**
			*   @brief	  Supposed to remove a vertex from the graph
			*			   effectively removing all connections related
			*			   to it. But is currently reserved for future.
			*   @param	  None.
			*/
			void removeVertex (VERTEX_TYPE id);

			/**
			*   @brief	  Return a vector of pair { VERTEX_TYPE, int } which
			*			   represent connected vertexes and their path
			*			   weight.
			*   @param	  None
			*/
			std::vector < std::pair < VERTEX_TYPE, int > >
				getNeighbours (VERTEX_TYPE v)
			{
				return this -> vertices[v].neighbous;
			}

			/**
			*   @brief  Return the count of vertices in the graph.
			*/
			int vertexCount ()
			{
			    return this -> vertex_count;
			}

			/**
			*	@brief	Return a vector of all the ID's of Vertexes.
			*/
			std::vector <VERTEX_TYPE> getAllVertexesById ()
			{
				std::vector <VERTEX_TYPE> vec;
				for (std::pair < VERTEX_TYPE, vertex <VERTEX_TYPE> > v : this -> vertices)
				{
					vec.push_back (v.first);
				}
				return vec;
			}

			/**
			*	@brief	Clears the whole graph
			*/
			void clear ()
			{
				this -> vertex_count = 0;
				this -> vertices.clear();
			}
	};
}


#endif
