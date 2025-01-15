#include <osmium/io/reader.hpp>
#include <osmium/io/pbf_input.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>
#include <iostream>

using namespace std;

class GraphBuilder : public osmium::handler::Handler {
public:
    // Node list (id, (latitude, longitude))
    unordered_map<int64_t, pair<double, double>> nodes;

    // Adjacency list
    unordered_map<int64_t, vector<int64_t>> adjacency_list;

    // Function to fill the node list
    void node(const osmium::Node& node) {
        nodes[node.id()] = {node.location().lat(), node.location().lon()};
    }

    // Function to fill the adjacency list
    void way(const osmium::Way& way) {
        const auto& nodes_in_way = way.nodes();
        for (auto it = nodes_in_way.begin(); it != prev(nodes_in_way.end()); ++it) {
            int64_t from = it->ref();
            int64_t to = next(it)->ref();
            adjacency_list[from].push_back(to);
            // If bidirectional
            adjacency_list[to].push_back(from);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file.osm.pbf>\n";
        return 1;
    }

    osmium::io::Reader reader(argv[1], osmium::osm_entity_bits::all);
    GraphBuilder builder;
    osmium::apply(reader, builder);
    reader.close();

    // Print of adjacency list
    /*for (const auto& [node, neighbors] : builder.adjacency_list) {
        cout << "Node " << node << " connects to: ";
        for (int64_t neighbor : neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }*/

    return 0;
}
