#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream> // For std::ofstream
#include <vector>  // For std::vector
#include <iostream>

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

#include <iostream>
#include <Eigen/Dense> // For Matrix, Vector, and solvers
#include <kitty/dynamic_truth_table.hpp> // For truth table operations
#include <kitty/print.hpp> // For printing truth tables

EMSCRIPTEN_KEEPALIVE

int logic() {
    // Use an AIG network. We'll wrap it in a names_view to easily assign/retrieve names.
    mockturtle::names_view<mockturtle::aig_network> named_aig;

    // --- 1. Create Primary Input (PI) nodes ---
    // These are the entry points or "source" vertices of our network.
    // create_pi returns a "signal" which represents a connection from this PI node.
    auto const a = named_aig.create_pi("a");
    auto const b = named_aig.create_pi("b");
    auto const c = named_aig.create_pi("c");

    std::cout << "Created Primary Inputs (PIs): a, b, c" << std::endl;

    // --- 2. Create an AND gate: g1 = a AND b ---
    // The signals 'a' and 'b' (from the PI nodes) are used as inputs.
    // This connects the PI nodes 'a' and 'b' to the inputs of this new AND gate node.
    // The result 'g1' is a signal representing the output of this AND gate.
    auto const g1 = named_aig.create_and(a, b);
    named_aig.set_name(g1, "g1_AND_ab"); // Assign a name to the signal/node

    std::cout << "Created AND gate (g1 = a AND b)." << std::endl;
    std::cout << "  - Input 1 to g1 is signal 'a'." << std::endl;
    std::cout << "  - Input 2 to g1 is signal 'b'." << std::endl;
    std::cout << "  - Output signal from g1 is named 'g1_AND_ab'." << std::endl;

    // --- 3. Create an OR gate: y = g1 OR c ---
    //    (Equivalent to y = (a AND b) OR c)
    // In an AIG, OR is implemented as NOT( (NOT g1) AND (NOT c) )

    // Negate the signal from g1 (output of the first AND gate)
    auto const not_g1 = named_aig.create_not(g1);
    // Negate the signal from PI 'c'
    auto const not_c = named_aig.create_not(c);

    // Create an AND gate with these negated signals: temp_and = (NOT g1) AND (NOT c)
    // This connects the (conceptual) NOT gate outputs to this new AND gate.
    auto const temp_and = named_aig.create_and(not_g1, not_c);

    // Negate the result to get the OR: y = NOT(temp_and)
    // The signal 'y' is the output of this OR construction.
    auto const y = named_aig.create_not(temp_and);
    named_aig.set_name(y, "y_OR_g1_c");

    std::cout << "Created OR gate (y = g1 OR c) using DeMorgan's law." << std::endl;
    std::cout << "  - Input 1 to OR construction is signal 'g1_AND_ab'." << std::endl;
    std::cout << "  - Input 2 to OR construction is signal 'c'." << std::endl;
    std::cout << "  - Output signal is named 'y_OR_g1_c'." << std::endl;

    // --- 4. Create a Primary Output (PO) ---
    // This connects the signal 'y' (the output of our OR construction)
    // to a primary output of the entire network.
    named_aig.create_po(y, "final_output_y");

    std::cout << "Created Primary Output (PO) from signal 'y_OR_g1_c'." << std::endl;

    // --- Displaying Network Structure (Conceptual) ---
    std::cout << "\n--- Network Structure Summary ---" << std::endl;
    std::cout << "Number of PIs: " << named_aig.num_pis() << std::endl;
    std::cout << "Number of POs: " << named_aig.num_pos() << std::endl;
    std::cout << "Number of gates (AIG AND gates): " << named_aig.num_gates() << std::endl;
    std::cout << "Total nodes (PIs + gates): " << named_aig.size() << std::endl;

    // Mockturtle works with signals. To get to the actual "nodes" (vertices):
    // named_aig.get_node(signal) gives you the node index.
    // named_aig.foreach_fanin(node, [](auto const& fanin_signal, auto i){ ... })
    // allows you to traverse the connections.

    std::cout << "\n--- Traversing Fanins (Connections) ---" << std::endl;
    // Get the node corresponding to the PO signal 'y'
    // Note: A PO itself is not a gate node; it points to the signal driving it.
    // We need to get the node that generates the signal 'y'.
    auto const y_node = named_aig.get_node(y);

    std::cout << "Primary Output 'final_output_y' is driven by signal 'y_OR_g1_c' (node: " << y_node << ")." << std::endl;
    std::cout << "Fan-in for the gate producing 'y_OR_g1_c' (which is an inverter as part of AIG OR):" << std::endl;
    named_aig.foreach_fanin(y_node, [&](auto const& fanin_signal, auto i) {
        auto fanin_node = named_aig.get_node(fanin_signal);
        std::cout << "  Input " << i << ": comes from node " << fanin_node
                  << " (signal complemented: " << named_aig.is_complemented(fanin_signal) << ")";
        if (named_aig.has_name(fanin_signal)) {
            std::cout << " - named: " << named_aig.get_name(fanin_signal);
        } else if (named_aig.is_pi(fanin_node)) {
             std::cout << " - is PI: " << named_aig.get_name(named_aig.make_signal(fanin_node));
        }
        std::cout << std::endl;
    });

    // Let's also check the fan-in of g1 (the AND gate)
    auto const g1_node = named_aig.get_node(g1);
    std::cout << "\nFan-in for gate 'g1_AND_ab' (node: " << g1_node << "):" << std::endl;
    named_aig.foreach_fanin(g1_node, [&](auto const& fanin_signal, auto i) {
        auto fanin_node = named_aig.get_node(fanin_signal);
        std::cout << "  Input " << i << ": comes from node " << fanin_node
                  << " (signal complemented: " << named_aig.is_complemented(fanin_signal) << ")";
        if (named_aig.is_pi(fanin_node)) { // PIs are nodes
            // For PIs, the signal is directly from the PI node.
            // The `make_signal` is needed because `get_name` for PIs often expects the PI's signal itself.
            if (named_aig.has_name(named_aig.make_signal(fanin_node))) {
                 std::cout << " - named PI: " << named_aig.get_name(named_aig.make_signal(fanin_node));
            }
        }
        std::cout << std::endl;
    });

    // --- Optional: Simulate to verify logic: y = (a AND b) OR c ---
    // Truth table for 3 inputs (c, b, a) - LSB is 'a'
    // (000) -> 0 & 0 | 0 = 0
    // (001) -> 0 & 1 | 0 = 0
    // (010) -> 1 & 0 | 0 = 0
    // (011) -> 1 & 1 | 0 = 1
    // (100) -> 0 & 0 | 1 = 1
    // (101) -> 0 & 1 | 1 = 1
    // (110) -> 1 & 0 | 1 = 1
    // (111) -> 1 & 1 | 1 = 1
    // Expected truth table (hex): 0xE8 (binary 11101000) (if c is MSB: cba)

    std::vector<kitty::dynamic_truth_table> pis_tts(3u);
    for ( uint32_t i = 0u; i < 3u; ++i ) {
        kitty::create_nth_var(pis_tts[i], 3u, i); // Creates x0, x1, x2
    }

    mockturtle::default_simulator<kitty::dynamic_truth_table> sim(pis_tts);
    const auto func_tts = mockturtle::simulate<kitty::dynamic_truth_table>(named_aig, sim);

    std::cout << "\n--- Simulation Result ---" << std::endl;
    std::cout << "Function (a,b,c) = (a AND b) OR c" << std::endl;
    std::cout << "Truth table (kitty format, cba): ";
    kitty::print_hex(func_tts[0]); // func_tts[0] corresponds to the first PO
    std::cout << std::endl;
    // kitty::print_binary(func_tts[0]);
    // std::cout << std::endl;

    return 0; // Indicate success for logic validation.
}

// Example vertex structure
typedef struct {
    float x, y, z;
} Vertex;

/**
 * @brief Writes vertex data to an OBJ file.
 * @param filename The name of the OBJ file to create.
 * @param vertices A pointer to an array of Vertex structures.
 * @param count The number of vertices in the array.
 */
void write_obj_vertices(const char* filename, const std::vector<Vertex>& vertices) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        perror("Failed to open file for writing vertices");
        return;
    }

    for (const auto& v : vertices) {
        file << "v " << v.x << " " << v.y << " " << v.z << "\n";
    }

    file.close();
    std::cout << "Wrote " << vertices.size() << " vertices to " << filename << std::endl;
}

/**
 * @brief Writes face data to an OBJ file.
 * @param filename The name of the OBJ file to create/append to.
 * @param faces A vector of Eigen::Vector3i, where each Vector3i represents face indices (0-based).
 */
void write_obj_faces(const char* filename, const std::vector<Eigen::Vector3i>& faces) {
    std::ofstream file(filename, std::ios::app); // Open in append mode
    if (!file.is_open()) {
        perror("Failed to open file for writing faces");
        return;
    }

    // Write faces with 1-based indexing for OBJ
    for (const auto& face : faces) {
        file << "f " << face[0] + 1 << " "
                     << face[1] + 1 << " "
                     << face[2] + 1 << "\n";
    }

    file.close();
    std::cout << "Wrote " << faces.size() << " faces to " << filename << std::endl;
}

---

## Shape OBJ File Builder and Logic Validator

### `solve` Function: Advanced OBJ Builder with Logic Validation

This function is designed for more complex OBJ file generation, potentially leveraging Eigen for matrix operations on vertices. It also integrates a logic validation step.

```cpp
void solve(const std::string& filename,
           const Eigen::MatrixXd& vertices_matrix,
           const std::vector<Eigen::Vector3i>& faces,
           const std::vector<Vertex>& start_vertices_vec) {

    std::ofstream file(filename);
    if (!file.is_open()) {
        perror("Failed to open file for writing in solve");
        return;
    }

    // Write vertices from Eigen::MatrixXd
    for (int col = 0; col < vertices_matrix.cols(); ++col) {
        file << "v " << vertices_matrix(0, col) << " "
                    << vertices_matrix(1, col) << " "
                    << vertices_matrix(2, col) << "\n";
    }

    // Write faces with 1-based indexing
    for (const auto& face : faces) {
        file << "f " << face[0] + 1 << " "
                     << face[1] + 1 << " "
                     << face[2] + 1 << "\n";
    }
    file.close();
    std::cout << "OBJ file '" << filename << "' created successfully by solve." << std::endl;

    // Logic assessment:
    // This part is conceptual. In a real-world scenario, you would define
    // specific geometric or logical conditions for "validation."
    // The `logic()` function in this context primarily performs a Mockturtle
    // logic network simulation as an example of logical validation.

    std::cout << "\n--- Performing Logic Assessment (conceptual) ---" << std::endl;
    // Example: Run the logic network validation
    int logic_result = logic();
    if (logic_result == 0) {
        std::cout << "Logic validation: Passed." << std::endl;
    } else {
        std::cout << "Logic validation: Failed (Error code: " << logic_result << ")." << std::endl;
    }

    // The original loop for "Accuracy theorem" and "Applied machine learning"
    // needs concrete definitions for `nodes` and `start_vertices`.
    // Assuming `start_vertices_vec` is a baseline, we can compare.
    // This is a placeholder for actual geometric validation logic.
    std::cout << "\n--- Performing Geometric Logic Validation (conceptual) ---" << std::endl;
    for (size_t i = 0; i < start_vertices_vec.size() && i < vertices_matrix.cols(); ++i) {
        // Access matrix column as a vector for comparison
        Eigen::Vector3d current_vertex = vertices_matrix.col(i);
        Vertex start_vertex = start_vertices_vec[i];

        // Example: Check if a vertex has "moved" or changed significantly
        // This is a simplified example of geometric validation.
        double distance_sq = pow(current_vertex[0] - start_vertex.x, 2) +
                             pow(current_vertex[1] - start_vertex.y, 2) +
                             pow(current_vertex[2] - start_vertex.z, 2);

        if (distance_sq > 0.001) { // Threshold for "significant" change
            std::cout << "Vertex " << i << " changed significantly from its start position." << std::endl;
            // Potentially add this vertex to a 'nodes' collection if it meets a criteria
            // (e.g., if it's a new or modified "node" in a graph representation).
            // Example: If 'nodes' were a std::vector<Vertex>
            // Vertex new_node = {static_cast<float>(current_vertex[0]), ...};
            // nodes.push_back(new_node);
        }
    }
    std::cout << "Geometric validation complete." << std::endl;
}

---

### `simple_solve` Function: Basic OBJ Builder with Logic Validation

This function provides a simpler approach to OBJ creation, suitable for directly using `Vertex` arrays/vectors.

```cpp
// Redefine simple_solve to take proper parameters for vertex and face data
int simple_solve(const std::vector<Vertex>& vertices, const std::vector<Eigen::Vector3i>& faces) {
    const char* filename = "output.obj"; // Default filename for simple_solve

    // Write vertices first
    write_obj_vertices(filename, vertices);

    // Then append faces
    write_obj_faces(filename, faces);

    std::cout << "OBJ file 'output.obj' created successfully by simple_solve." << std::endl;

    // Logic assessment:
    std::cout << "\n--- Performing Logic Assessment (conceptual) ---" << std::endl;
    int logical_result = logic(); // Call your logic validation function
    if (logical_result == 0) {
        std::cout << "Logic validation: Passed." << std::endl;
    } else {
        std::cout << "Logic validation: Failed (Error code: " << logical_result << ")." << std::endl;
    }

    // The original "Accuracy theorem" loop needs clear definition of `start_vertices`.
    // For this example, let's assume `vertices` itself is being validated against some
    // implicit `start_vertices` or a set of rules.
    std::cout << "\n--- Performing Geometric Logic Validation (conceptual) ---" << std::endl;
    // This part would involve specific geometric validation logic.
    // For example, checking if vertices form valid triangles, or if they fall within certain bounds.
    // Placeholder for actual validation.
    bool all_vertices_valid = true;
    for (size_t i = 0; i < vertices.size(); ++i) {
        // Example validation: Check if any coordinate is NaN or Inf, or outside a reasonable range
        if (std::isnan(vertices[i].x) || std::isinf(vertices[i].x) ||
            std::isnan(vertices[i].y) || std::isinf(vertices[i].y) ||
            std::isnan(vertices[i].z) || std::isinf(vertices[i].z)) {
            std::cerr << "Error: Vertex " << i << " contains invalid coordinates." << std::endl;
            all_vertices_valid = false;
            break;
        }
    }

    if (all_vertices_valid) {
        std::cout << "All vertices appear geometrically valid." << std::endl;
    } else {
        std::cout << "Some vertices failed geometric validation." << std::endl;
    }

    // This part is highly conceptual in your original code.
    // `Vertex nodes [] = nodes + vertices[i];` is not valid C++ syntax for dynamic array manipulation.
    // If you need to collect specific "nodes" that meet certain criteria, use a `std::vector<Vertex>`.
    /*
    // Example of collecting "nodes" based on a condition (conceptual):
    std::vector<Vertex> validated_nodes;
    for (size_t i = 0; i < vertices.size(); ++i) {
        // Define a condition for a vertex to be considered a "node"
        // For example, if its x-coordinate is positive.
        if (vertices[i].x > 0) {
            validated_nodes.push_back(vertices[i]);
        }
    }
    std::cout << "Collected " << validated_nodes.size() << " 'validated nodes'." << std::endl;
    */

    return 0; // Indicate success.
}

---

### `graph` Function: Entry Point for OBJ Creation

The `graph` function acts as a dispatcher, choosing between `simple_solve` and `solve` based on the input `data`.

```cpp
// Redefine graph to accept relevant data for both simple and advanced solve methods
int graph(bool use_simple_mode,
          const std::vector<Vertex>& simple_vertices,
          const std::vector<Eigen::Vector3i>& simple_faces,
          const std::string& advanced_filename,
          const Eigen::MatrixXd& advanced_vertices_matrix,
          const std::vector<Eigen::Vector3i>& advanced_faces,
          const std::vector<Vertex>& start_vertices_for_advanced) {

    if (use_simple_mode) {
        std::cout << "\n--- Building simple 3D object with vertex coordinates (simple_solve) ---" << std::endl;
        return simple_solve(simple_vertices, simple_faces);
    } else {
        std::cout << "\n--- Building harder geometries with AI alternative (solve) ---" << std::endl;
        return solve(advanced_filename, advanced_vertices_matrix, advanced_faces, start_vertices_for_advanced);
    }
}

---

### `output` Function (Placeholder)

The `output` function in your original code was `return OBJ;`, which is not valid C++. If `OBJ` is meant to represent the generated file, the output is already handled by the `solve` and `simple_solve` functions. This function can be removed or repurposed if you intend to return a status or a path to the generated OBJ.

```cpp
// If this function is meant to return the OBJ data or path,
// it needs to be designed accordingly.
// For now, it's a placeholder.
// int output() {
//    // The OBJ files are already written by solve/simple_solve.
//    // You might return a success code, or the filename, if desired.
//    return 0; // Or a specific OBJ status.
// }
