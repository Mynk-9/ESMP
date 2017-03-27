#include <iostream>
#include <vector>
#include <chrono>	/// for generating random numbers using <random>
#include <random>	/// for generating random numbers
#include "Ninth Sky.hpp"

//using namespace std;

void printVec (std::vector < std::pair <int, int> > v)
{
    for (unsigned int i = 0; i != v.size(); i++)
        std::cout << v[i].first << " " << v[i].second << "\n";
    std::cout << "++++++\n";
}
void printVec (std::vector <auto> v)
{
    auto i = v.begin();
    auto l = v.end();
    for (; i != l; i++)
        std::cout << *i << "\n";
    std::cout << "+++++\n";
    std::flush(std::cout);
}
template <typename T1, typename T2>
void printMap (std::map <T1, T2> & m)
{
	for (std::pair <T1, T2> p : m)
		std::cout << p.first << " -> " << p.second << "\n";
}
void randomize (std::vector <int> & vec, int l)
{
	vec.clear();	/// reuse same old vec.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();	/// generate 100 random no. with random signs.
	std::minstd_rand0 generator (seed);
	for (int i = 1; i <= l; i++)
	{
		int tmp = generator();
		int sgn = generator() % 2 ? -1 : 1;
		vec.push_back((tmp % 100) * sgn);
	}
}

int main()
{
	std::cout << "                                   DEMO OF NINTH SKY\n                                   *****************\n\n\n";
    ninth_sky::error_report.debug_writer_enabled = true;
    //ninth_sky::error_report.debug_write_to_file = true;

    ninth_sky::graph <int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addNeighbour(1, 2, 1);
    g.addNeighbour(2, 1, 1);
    g.addNeighbour(2, 3, -5);

    g.addNeighbour(1, 3, 100);
    g.addNeighbour(3, 2, -1);

    printVec(g.getNeighbours(1));
    /**
    * print array like:
    * neighbour1 weight1
    * neighbour2 weight2
    * neighbour3 weight3
    */

    std::vector <int> vec = {1, 2, 3, 3, 3, 6, 7, 8, 9, 10};

    std::pair <int, int> p;
    p = ninth_sky::binarySearch (vec.begin(), vec.end(), 3);

    std::cout << "Binary Search (of 3) Result for: {1, 2, 3, 3, 3, 6, 7, 8, 9, 10} :-" << p.first << " " << p.second << std::endl;

    ninth_sky::integer_xl a, b, c;
    a = "1234567890";
    b = "0987654321";
    c = a + b;
    std::cout << a << " + " << b << " = " << c << "\n\nEnter two numbers (-ve or +ve): ";

    std::cin >> a;
    std::cin >> b;

    std::cout << a << " < " << b << " ? " << (a < b ? "TRUE" : "FALSE") << "\n";
    std::cout << a << " > " << b << " ? " << (a > b ? "TRUE" : "FALSE") << "\n";
    std::cout << a << " <= " << b << " ? " << (a <= b ? "TRUE" : "FALSE") << "\n";
    std::cout << a << " >= " << b << " ? " << (a >= b ? "TRUE" : "FALSE") << "\n";

    c = a - b;

    std::cout << "\n\n\n" << a << " - " << b << " = " << c << "\n";

    c = a + b;

    std::cout << "\n\n" << a << " + " << b << " = " << c << "\n";
    std::cout << "\n\n" << c << " + " << a << " = ";
    c += a;
    std::cout << c << "\n";
    std::cout << "\n\n" << c << " - " << a << " = ";
    c -= a;
    std::cout << c << "\n";

    std::cout << "\n\nEnter two more numbers (+ve/-ve): ";
    std::cin >> a;
    std::cin >> b;
    c = a * b;
    std::cout << a << " X " << b << " = " << c << "\n";
    std::cout << c << " X " << a << " = ";
    c *= a;
    std::cout << c << "\n\n\n";

    int lambda;
    std::cout << "Enter another number: ";
    std::cin >> lambda;
    c = lambda;
    c.reverse();
	std::cout << "It's reverse is: " << c << "\n";
	std::cout << "\n\n" << ninth_sky::data_type.getName(a) << "\n\n\n";

	std::cout << "+++++++++++++++++++++++++++++++" << "\n\nGraph Algorithm (Bellman Ford) Demo: \n\n";
	ninth_sky::graph <char> _graph;
	_graph.addVertex('s');
	_graph.addVertex('a');
	_graph.addVertex('b');
	_graph.addVertex('c');
	_graph.addVertex('d');
	_graph.addVertex('e');

	_graph.addNeighbour('s', 'a', 10);
	_graph.addNeighbour('s', 'e', 8);

	_graph.addNeighbour('a', 'c', 2);

	_graph.addNeighbour('b', 'a', 1);

	_graph.addNeighbour('c', 'b', -2);

	_graph.addNeighbour('d', 'a', -4);
	_graph.addNeighbour('d', 'c', -1);

	_graph.addNeighbour('e', 'd', 1);

	std::cout << "Graph: can be seen @ https://www.youtube.com/watch?v=obWXjtg0L64\n";

	std::map <char, int> dist = ninth_sky::Algorithms_graph.bellman_ford <char> (_graph, 's');
	printMap <char, int> (dist);

	std::cout << "\n\n\n" << "+++++++++++++++++++++++++++++" << "\n\n" << "Graph Algorithm (BFT) Demo:";
	printVec(ninth_sky::Algorithms_graph.breadthFirstTransversal <char> (_graph, 's'));

	std::cout << "\n\n\n" << "+++++++++++++++++++++++++++++" << "\n\n" << "Graph Algorithm (BFS) Demo:\n";
	std::cout << "'z' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'z') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'s' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 's') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'a' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'a') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'b' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'b') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'c' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'c') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'d' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'd') ? "PRESENT" : "ABSENT") << ".\n";
	std::cout << "'e' is " << (ninth_sky::Algorithms_graph.breadthFirstSearch <char> (_graph, 's', 'e') ? "PRESENT" : "ABSENT") << ".\n";

	/**
	  *		Kadane's max summing sub-array algo. test
	  *		O(n)
	  */
	std::cout << "\n\n\n" << "+++++++++++++++++++++++++++++" << "\n\n";
	std::cout << "\n\n Kadane's Maximum summing Sub-array Algorithm\n Generating 100 random numbers...\n";
	randomize(vec, 100);
	std::cout << "The array: ";
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::pair <int, std::pair <int, int> > kdn = ninth_sky::kadane(vec);
	std::cout << "\n Output with Kadane's Maximum Summing Sub-array algorithm (enhanced):-\n    Max Sum: "
	<< kdn.first << " from range: [" << kdn.second.first << ", " << kdn.second.second << "]" << std::endl;

	/**
	  *		Max summing fixed length sub-array algo. test
	  *		O(n)
	  */
	std::cout << "\n\n\n" << "+++++++++++++++++++++++++++++" << "\n\n";
	std::cout << "\n\n Maximum summing fixed length sub-array Algorithm\n Generating 100 random numbers...\n";
	randomize(vec, 100);
	std::cout << "The array: ";
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << " ";
	std::pair <int, int> mssfl = ninth_sky::maxSumming_SubArray_fixedLength(vec, 15);
	std::cout << "\n Output with Maximum Summing fixed length Sub-array algorithm (len = 15):-\n    Max Sum: "
	<< mssfl.first << " from starting point " << mssfl.second << std::endl;

    return 0;
}
