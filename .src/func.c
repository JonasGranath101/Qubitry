#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

EMSCRIPTEN_KEEPALIVE

// Vertex structure with normal
typedef struct {
    float x, y, z;
    float nx, ny, nz; // Normal vector
} Vertex;

// Face structure (triangle)
typedef struct {
    int v1, v2, v3; // Indices (1-based for OBJ)
} Face;

// Mesh structure
typedef struct {
    Vertex* vertices;
    int vertex_count;
    Face* faces;
    int face_count;
} Mesh;



// Calculate normal for a face (helper)
void calculate_normal(const Vertex* v1, const Vertex* v2, const Vertex* v3, float* nx, float* ny, float* nz) {
    float ux = v2->x - v1->x;
    float uy = v2->y - v1->y;
    float uz = v2->z - v1->z;
    float vx = v3->x - v1->x;
    float vy = v3->y - v1->y;
    float vz = v3->z - v1->z;
    *nx = uy * vz - uz * vy;
    *ny = uz * vx - ux * vz;
    *nz = ux * vy - uy * vx;
    float length = sqrtf((*nx)*(*nx) + (*ny)*(*ny) + (*nz)*(*nz));
    if (length > 0.0001f) {
        *nx /= length;
        *ny /= length;
        *nz /= length;
    }
}

// Write OBJ file with vertices, normals, and faces
void write_obj(const char* filename, const Mesh* mesh) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open OBJ file");
        return;
    }

    // Write vertices
    for (int i = 0; i < mesh->vertex_count; ++i) {
        fprintf(file, "v %.6f %.6f %.6f\n", mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z);
    }

    // Write normals
    for (int i = 0; i < mesh->vertex_count; ++i) {
        fprintf(file, "vn %.6f %.6f %.6f\n", mesh->vertices[i].nx, mesh->vertices[i].ny, mesh->vertices[i].nz);
    }

    // Write faces (with normals)
    for (int i = 0; i < mesh->face_count; ++i) {
        fprintf(file, "f %d//%d %d//%d %d//%d\n",
                mesh->faces[i].v1 + 1, mesh->faces[i].v1 + 1,
                mesh->faces[i].v2 + 1, mesh->faces[i].v2 + 1,
                mesh->faces[i].v3 + 1, mesh->faces[i].v3 + 1);
    }
    fclose(file);
}

// Print mesh information
void print_mesh_info(const Mesh* mesh) {
    printf("Mesh Information:\n");
    printf("  Vertices: %d\n", mesh->vertex_count);
    printf("  Faces:    %d\n", mesh->face_count);
    for (int i = 0; i < mesh->vertex_count; ++i) {
        printf("  Vertex %d: (%.2f, %.2f, %.2f) Normal (%.2f, %.2f, %.2f)\n",
            i, mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z,
            mesh->vertices[i].nx, mesh->vertices[i].ny, mesh->vertices[i].nz);
    }
}

// Example: Create a simple triangle mesh
Mesh create_simple_mesh() {
    Mesh mesh;
    mesh.vertex_count = 3;
    mesh.face_count = 1;
    mesh.vertices = (Vertex*)malloc(mesh.vertex_count * sizeof(Vertex));
    mesh.faces = (Face*)malloc(mesh.face_count * sizeof(Face));

    // Vertices
    mesh.vertices[0] = (Vertex){0.0f, 0.0f, 0.0f, 0,0,0};
    mesh.vertices[1] = (Vertex){1.0f, 0.0f, 0.0f, 0,0,0};
    mesh.vertices[2] = (Vertex){0.0f, 1.0f, 0.0f, 0,0,0};

    // Face
    mesh.faces[0] = (Face){0, 1, 2};

    // Calculate normals for each vertex (flat shading)
    float nx, ny, nz;
    calculate_normal(&mesh.vertices[0], &mesh.vertices[1], &mesh.vertices[2], &nx, &ny, &nz);
    for (int i = 0; i < mesh.vertex_count; ++i) {
        mesh.vertices[i].nx = nx;
        mesh.vertices[i].ny = ny;
        mesh.vertices[i].nz = nz;
    }
    return mesh;
}

// Output mesh info as a string (for advanced data output)
void mesh_info_string(const Mesh* mesh, char* buffer, size_t buf_size) {
    int offset = 0;
    offset += snprintf(buffer + offset, buf_size - offset, "Mesh: %d vertices, %d faces\n",
                      mesh->vertex_count, mesh->face_count);
    for (int i = 0; i < mesh->vertex_count; ++i) {
        offset += snprintf(buffer + offset, buf_size - offset,
            "Vertex %d: (%.2f, %.2f, %.2f) Normal (%.2f, %.2f, %.2f)\n",
            i, mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z,
            mesh->vertices[i].nx, mesh->vertices[i].ny, mesh->vertices[i].nz);
    }
}

int graph () {

    Mesh mesh = create_simple_mesh();

    // Write OBJ file
    write_obj("advanced_output.obj", &mesh);

    // Print mesh info to console
    print_mesh_info(&mesh);

    // Output mesh info as string
    char info_buffer[1024];
    mesh_info_string(&mesh, info_buffer, sizeof(info_buffer));
    printf("\n--- Mesh Info String ---\n%s", info_buffer);

    // Free memory
    free(mesh.vertices);
    free(mesh.faces);

    return mesh;
}

int output () {

    FILE *fp = fopen("advanced_output.obj", "rb");
    if (!fp) return NULL;

    // Seek to end to determine file size
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return NULL;
    }
    long size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        return NULL;
    }
    rewind(fp);

    // Allocate buffer (+1 for null terminator)
    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    // Read file into buffer
    size_t read_size = fread(buffer, 1, size, fp);
    buffer[read_size] = '\0'; // Null-terminate

    fclose(fp);
    return buffer;
}
