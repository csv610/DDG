#include <iostream>
#include <cassert>
#include "Mesh.h"
#include "DenseMatrix.h"
#include "LinearSystem.h"
#include "SparseMatrix.h"

using namespace DDG;

int main()
{
    std::cout << "=== BaseCode Unit Tests ===" << std::endl;
    
    std::cout << "Test 1: Mesh loading... " << std::endl;
    Mesh mesh;
    mesh.read( "testdata/armadillo.obj" );
    std::cout << "  Loaded " << mesh.vertices.size() << " vertices, " << mesh.edges.size() << " edges, " << mesh.faces.size() << " faces" << std::endl;
    assert( mesh.vertices.size() > 0 );
    assert( mesh.edges.size() > 0 );
    assert( mesh.faces.size() > 0 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 2: Mesh vertex count (armadillo should have ~32k verts)... " << std::endl;
    std::cout << "  V=" << mesh.vertices.size() << std::endl;
    assert( mesh.vertices.size() > 30000 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 3: Mesh edge count... " << std::endl;
    std::cout << "  E=" << mesh.edges.size() << std::endl;
    assert( mesh.edges.size() > 90000 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "Test 4: Mesh face count... " << std::endl;
    std::cout << "  F=" << mesh.faces.size() << std::endl;
    assert( mesh.faces.size() > 60000 );
    std::cout << "  PASSED" << std::endl;
    
    std::cout << "=== All BaseCode tests PASSED ===" << std::endl;
    return 0;
}