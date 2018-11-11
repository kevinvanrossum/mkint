#include "kmint/main.hpp"          // voor de main loop
#include "kmint/graphics.hpp"      // kleuren en afbeeldingen
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
#include "kmint/map/map.hpp"
#include <iostream>
#include "cow.hpp"
#include "hare.hpp"
#include <set>
#include <queue>
#include <map>
#include "priority_queue.hpp"

# define INF 0x3f3f3f3f

using namespace kmint; // alles van libkmint bevindt zich in deze namespace

static const char* map_description =
	R"graph(32 24 32
resources/firstmap.png
G 1 1
C 1 1
H 1 1
W 0 0
B 1 8

WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
WWWGGGGGBBBBBBBGCGGGGGGGGGGGGWWW
WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
)graph";

const map::map_node& find_cow_node(const map::map_graph& graph)
{
	for (std::size_t i = 0; i < graph.num_nodes(); ++i)
	{
		if (graph[i].node_info().kind == 'C')
		{
			return graph[i];
		}
	}
	throw "could not find starting point";
}

class rectangle_drawable : public ui::drawable
{
public:
	rectangle_drawable(play::actor const& actor) : drawable{}, actor_{&actor}
	{
	}

	void draw(ui::frame& f) const override;

private:
	play::actor const* actor_;
};

void rectangle_drawable::draw(ui::frame& f) const
{
	f.draw_rectangle(actor_->location(), {10.0, 10.0}, graphics::colors::white);
}

class hello_actor : public play::free_roaming_actor
{
public:
	hello_actor(math::vector2d location)
		: free_roaming_actor{location}, drawable_{*this}
	{
	}

	const ui::drawable& drawable() const override { return drawable_; }
	void move(math::vector2d delta) { location(location() + delta); }

private:
	rectangle_drawable drawable_;
};

void print_path(std::vector<double> parent, int dest)
{
	// Base Case : If dest is source
	if (parent[dest] == -1)
		return;

	print_path(parent, parent[dest]);

	printf("%d ", dest);
}

void tag_shortest_path_dijkstra(std::vector<double> parent, int dest, map::map_graph& graph)
{
	graph.untag_all();
	// Base Case : If dest is source
	if (parent[dest] == -1)
		return;

	tag_shortest_path_dijkstra(parent, parent[dest], graph);

	graph[dest].tagged(true);
}

void print_solution(std::vector<int> dist, int number_of_nodes, std::vector<double>& parent)
{
	int src = 0;
	printf("Vertex\t Distance\tPath");
	for (int i = 1; i < number_of_nodes; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ",
		       src, i, dist[i], src);
		print_path(parent, i);
	}
}

void move_cow_dijkstra(cow cow, std::vector<double>& parent, int dest, map::map_graph& graph)
{
	// cow.act()
};

int main()
{
	// een app object is nodig om
	ui::app app{};

	//  maak een venster aan
	ui::window window{app.create_window({1024, 768}, "hello")};

	// maak een podium aan
	play::stage s{};

	// laad een kaart
	map::map m{map::read_map(map_description)};
	auto& graph = m.graph();
	for (std::size_t i = 0; i < graph.num_nodes(); ++i)
	{
		std::cout << "Knoop op: " << graph[i].location().x() << ", "
			<< graph[i].location().y() << "\n";
	}

	s.build_actor<play::background>(
		math::size(1024, 768),
		graphics::image{m.background_image()});
	s.build_actor<play::map_actor>(
		math::vector2d{0.0f, 0.0f},
		m.graph());


	auto& cow_node = find_cow_node(m.graph());
	auto& my_cow = s.build_actor<cow>(m.graph(), cow_node);
	auto& my_hare = s.build_actor<hare>(m.graph());
	my_hare.set_cow(my_cow);

	math::vector2d center{512.0, 384.0};
	auto& my_actor = s.build_actor<hello_actor>(center);

	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};


	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls& ctl)
	{
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.

		for (ui::events::event& e : event_source)
		{
			// event heeft een methjode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
			e.handle_key_up([&my_actor](ui::events::key_event k)
			{
				switch (k.key)
				{
				case ui::events::key::w:
				case ui::events::key::up:
					my_actor.move({0, -5.0f});
					break;
				case ui::events::key::s:
				case ui::events::key::down:
					my_actor.move({0, 5.0f});
					break;
				case ui::events::key::a:
				case ui::events::key::left:
					my_actor.move({-5.0f, 0});
					break;
				case ui::events::key::d:
				case ui::events::key::right:
					my_actor.move({5.0f, 0});
					break;
				default:
					break;
				}
			});
		}

		system("cls");

		// Find cow location
		const auto src = my_cow.node().node_id();
		std::cout << "cow is walking on note: " << src << std::endl;
		// Find hare location
		const auto end = my_hare.node().node_id();
		std::cout << "hare is walking on note: " << end << std::endl;


		// Create a priority queue to store vertices that 
		// are being preprocessed. This is weird syntax in C++. 
		// Refer below link for details of this syntax 
		// http://geeksquiz.com/implement-min-heap-using-stl/ 
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

		const int num_nodes = graph.num_nodes();
		// Create a vector for distances and initialize all 
		// distances as infinite (INF) 
		std::vector<int> dist((num_nodes), INF);

		// Parent array to store 
		// shortest path tree 
		// int parent[num_nodes];
		std::vector<double> parent((num_nodes), -1);
		parent[0] = -1;

		// Insert source itself in priority queue and initialize 
		// its distance as 0. 
		pq.push(std::make_pair(0, src));
		dist[src] = 0;

		/* Looping till priority queue becomes empty (or all 
		distances are not finalized) */
		while (!pq.empty())
		{
			// The first vertex in pair is the minimum distance 
			// vertex, extract it from priority queue. 
			// vertex label is stored in second of pair (it 
			// has to be done this way to keep the vertices 
			// sorted distance (distance must be first item 
			// in pair) 
			const auto u = pq.top().second;
			pq.pop();

			// Get all adjacent of u.  
			for (auto x : graph[u])
			{
				// Get vertex label and weight of current adjacent 
				// of u. 
				int v = x.to().node_id();
				const int weight = x.weight();

				// If there is shorted path to v through u. 
				if (dist[v] > dist[u] + weight)
				{
					// Updating distance of v 
					parent[v] = u;
					dist[v] = dist[u] + weight;
					pq.push(std::make_pair(dist[v], v));
				}
			}
		}

		// Print shortest distances stored in dist[] 
		// print_solution(dist, num_nodes, parent);
		tag_shortest_path_dijkstra(parent, end, graph);

		move_cow_dijkstra();

		// std::cin.get(); // get one more char from the user
	});
}
