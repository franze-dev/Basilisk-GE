#include "Material.h"


#include <GL/glew.h>
#include "Renderer.h"

#include "Colors.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace basilisk
{
    using ShaderProc = unsigned int;
    
    Material::Material(const bool isTextured, const bool hasFilter) : 
        IsTextured(isTextured), HasFilter(hasFilter)
    {
    }

    void Material::OverrideColorFilter(const Color& color) const
    {
        glUseProgram(this->ShaderProgram);

        const GLint location = glGetUniformLocation(this->ShaderProgram, "FilterColor");

        glUniform4f(location, color.R, color.G, color.B, color.A);
    }

    std::shared_ptr<Material> Material::New(const bool isTextured, const bool hasFilter)
    {
        // Makes a new object with a shared pointer.
        return std::make_shared<Material>(isTextured, hasFilter);
    }

    void Material::BuildShader()
    {
        Log::Get()->info("Building shaders");
        const ShaderProc vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const ShaderProc fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        this->ShaderProgram = glCreateProgram();
        Log::Get()->info("Shader id: {}", this->ShaderProgram);

        GLint hasCompiled;

        Log::Get()->info("Compiling shaders");

        glShaderSource(vertexShader, 1, &VertexShader, nullptr);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ShaderCompileError(vertexShader);
        }

        auto fragShader = &FragShaderTextureless;

        if (this->IsTextured && this->HasFilter)
        {
            fragShader = &FilterFragShader;
        }
        else if (this->IsTextured)
        {
            fragShader = &FragShader;
        }

        glShaderSource(fragmentShader, 1, fragShader, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ShaderCompileError(fragmentShader);
        }

        Log::Get()->info("Linking and attaching shader program");
        /*Shader program attachment and linking*/
        glAttachShader(this->ShaderProgram, vertexShader);
        glAttachShader(this->ShaderProgram, fragmentShader);
        glLinkProgram(this->ShaderProgram);

        glGetProgramiv(this->ShaderProgram, GL_LINK_STATUS, &hasCompiled);
        if (!hasCompiled)
        {
            ProgramCompileError(this->ShaderProgram);
        }

        Log::Get()->info("Deleting compiled shaders");
        
        /*Deletion*/
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        this->IsMatBuilt = true;
    }

    SPProc Material::GetShaderProgram() const
    {
        return this->ShaderProgram;
    }

    bool Material::GetIsTextured() const
    {
        return IsTextured;
    }

    void Material::UpdateGLMatrix(const glm::mat4& matrix, const std::string& name) const
    {
        glUseProgram(this->ShaderProgram);

        const GLint location = glGetUniformLocation(this->ShaderProgram, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    bool Material::IsMaterialBuilt()
    {
        return this->IsMatBuilt;
    }
    
    void Material::ShaderCompileError(const ShaderProc& shader)
    {
        constexpr int infoBufferSize = 512;

        char infoLog[infoBufferSize];
        glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);
        Log::Get()->error("Shader failed to compile:\n{}", std::string(infoLog));
        
        abort();
    }

    void Material::ProgramCompileError(const SPProc& program)
    {
        constexpr int infoBufferSize = 512;

        char infoLog[infoBufferSize];
        glGetProgramInfoLog(program, infoBufferSize, nullptr, infoLog);
        Log::Get()->error("Shader program failed to compile:\n{}", std::string(infoLog));
        
        abort();
    }

    const char* Material::VertexShader = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 Pos;\n"
        "layout (location = 1) in vec4 Color;\n"
        "layout (location = 2) in vec2 TexCoord;\n"

        "out vec4 OutColor;\n"
        "out vec2 OutTexCoord;\n"

        "uniform mat4 matrix;\n"

        "void main()\n"
        "{\n"
        " gl_Position = matrix * vec4(Pos, 1.0);\n"
        " OutColor = Color;\n"
        " OutTexCoord = TexCoord;\n"
        "}\0";

    const char* Material::FragShader = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
        "in vec2 OutTexCoord;\n"

        "uniform sampler2D OutTexture;\n"

        "void main()\n"
        "{\n"
        " FragColor = texture(OutTexture, OutTexCoord) * OutColor;\n"
        "}\n";


    const char* Material::FilterFragShader = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"
        "in vec2 OutTexCoord;\n"

        "uniform vec4 FilterColor;\n"
        "uniform sampler2D OutTexture;\n"

        "void main()\n"
        "{\n"
        " FragColor = texture(OutTexture, OutTexCoord) * (OutColor + FilterColor);\n"
        "}\n";

    const char* Material::FragShaderTextureless = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 OutColor;\n"

        "void main()\n"
        "{\n"
        " FragColor = OutColor;\n"
        "}\n";
} // namespace basilisk
