#ifndef _H_PLYMESH_H_
#define _H_PLYMESH_H_

#include <boost/noncopyable.hpp>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline std::ostream & operator<<(std::ostream & os, const glm::mat4 & m)
{
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            os << m[i][j] << ", ";
        }
        os << std::endl;
    }
    return os;
}

class PLYMesh : public boost::noncopyable
{
    struct pass
    {
        std::vector<GLushort> faces;
        glm::mat4 mvp;
        glm::vec4 texCoords;
        GLushort texIndice;
    };
    struct face
    {
        std::vector<GLushort> v;
        int offset;
    };
public:
    PLYMesh();

    void loadFromFile(const std::string & ply_model);

    void render(glm::mat4 & vp);

    glm::mat4 & getModel() { return model; }

    void setModel(const glm::mat4 & m) { model = m; }

    void Highlight() { highlight = true; }

    void Unhighlight() { highlight =false; }
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> colors;
    std::vector<face> faces;
    std::vector<GLushort> triangle_faces;
    std::vector<GLushort> quad_faces;
    std::vector<sf::Texture*> textures;
    std::vector<pass> passes;

    sf::Shader shader;
    GLuint vbo_vertices;
    GLuint vbo_normals;
    GLuint vbo_colors;
    GLuint ibo_faces;
    GLuint ibo_triangles;
    GLuint ibo_quads;

    glm::mat4 model;
    bool highlight;
};

#endif
