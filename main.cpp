#include <iostream>
#include <random>

template<size_t size>
void generate_random_graph(unsigned (&graph)[size][size], double density) {
    std::default_random_engine generator(time(nullptr));
    std::uniform_real_distribution<double> prob(0, 1.);
    std::uniform_int_distribution<unsigned> rand_dst(0, 100);

    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            graph[i][j] = graph[j][i] = i == j ? 0 : static_cast<int>(prob(generator) < density) * rand_dst(generator);
        }
    }

}

template<size_t size>
std::ostream &operator<<(std::ostream &out, const unsigned (&arr)[size][size]) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            out << arr[i][j] << (j != size - 1 ? "\t" : "");
        }

        out << (i != size - 1 ? "\n" : "");
    }

    return out;
}

template<size_t size>
bool is_connected(unsigned (&graph_matr)[size][size]) {
    bool open[size];
    bool closed[size];
    size_t c_size = 0;

    for (int i = 0; i < size; ++i) {
        open[i] = false;
        closed[i] = false;
    }

    open[0] = true;
    while (c_size < size) {
        size_t old_c_size = c_size;

        for (int i = 0; i < size; ++i) {
            if (open[i] && not closed[i]) {
                closed[i] = true;
                c_size++;

                for (int j = 0; j < size; ++j) {
                    open[j] = (open[j] or graph_matr[i][j]);
                }
            }
        }

        if (c_size == old_c_size) // we have no nodes in the open set
            return false;
    }

    return true;
}

int main(int argc, const char *argv[]) {
    const size_t graph_size = 5;
    unsigned graph_matr[graph_size][graph_size];

    generate_random_graph(graph_matr, 0.4);

    std::cout << graph_matr << std::endl;
    std::cout << is_connected(graph_matr) << std::endl;

    return 0;
}
