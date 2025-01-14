#include <osmium/io/reader.hpp>
#include <osmium/io/pbf_input.hpp>
#include <osmium/handler.hpp>
#include <osmium/visitor.hpp>
#include <iostream>

using namespace std;

class MyHandler : public osmium::handler::Handler {
public:
    void node(const osmium::Node& node) {
        cout << "Node: " << node.id() << " at " << node.location() << "\n";
    }

    void way(const osmium::Way& way) {
        cout << "Way: " << way.id() << " with " << way.nodes().size() << " nodes\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file.osm.pbf>\n";
        return 1;
    }

    osmium::io::Reader reader(argv[1], osmium::osm_entity_bits::all);
    MyHandler handler;
    osmium::apply(reader, handler);
    reader.close();

    return 0;
}
