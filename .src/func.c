#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

// Include mockturtle headers. Logic.
#include <mockturtle/mockturtle.hpp>
#include <mockturtle/algorithms/cut_enumeration.hpp>
#include <mockturtle/networks/aig.hpp>

// Include lorina for AIGER parsing
#include <lorina/aiger.hpp>

#include <Eigen/Dense> // For Matrix, Vector, and solvers

// Example vertex structure
typedef struct {
    float x, y, z;
} Vertex;

EMSCRIPTEN_KEEPALIVE
int logic() {
    mockturtle::names_view<mockturtle::aig_network> named_aig;

    auto const a = named_aig.create_pi("a");
    auto const b = named_aig.create_pi("b");
    auto const c = named_aig.create_pi("c");

    auto const g1 = named_aig.create_and(a, b);
    named_aig.set_name(g1, "g1_AND_ab");

    auto const not_g1 = named_aig.create_not(g1);
    auto const not_c = named_aig.create_not(c);

    auto const temp_and = named_aig.create_and(not_g1, not_c);
    auto const y = named_aig.create_not(temp_and);
    named_aig.set_name(y, "y_OR_g1_c");

    named_aig.create_po(y, "final_output_y");

    return 0;
}

void write_obj_vertices(const char* filename, Vertex* vertices, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "v %f %f %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
    }

    fclose(file);
}

void solve(const std::string& filename,
           const Eigen::MatrixXd& vertices,
           const std::vector<Eigen::Vector3i>& faces,
           const Eigen::MatrixXd& start_vertices) {
    std::ofstream file(filename);

    for (int col = 0; col < vertices.cols(); ++col) {
        file << "v " << vertices(0, col) << " "
             << vertices(1, col) << " "
             << vertices(2, col) << "\n";
    }

    for (const auto& face : faces) {
        file << "f " << face[0] + 1 << " "
             << face[1] + 1 << " "
             << face[2] + 1 << "\n";
    }

    // Example logic usage
    logic();

    file.close();
}

int simple_solve(int b, int c) {
    // Example vertices and faces
    Vertex vertices[] = { {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f} };
    int vertex_count = sizeof(vertices) / sizeof(vertices[0]);

    write_obj_vertices("output.obj", vertices, vertex_count);

    printf("OBJ file written.\n");

    return vertex_count;
}

int graph() {
    // Call simple_solve with example parameters
    int result = simple_solve(1, 2);
    std::cout << "simple_solve returned: " << result << std::endl;
    return result;
}

int output () {

    return vertices

}
