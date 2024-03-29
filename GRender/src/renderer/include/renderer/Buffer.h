#pragma once

#include "core/Base.h"
#include <vector>

namespace GRender {
enum class BufferDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
    Mat3,
    Mat4
};

static size_t GetSizeOfBufferDataType(BufferDataType type)
{
    switch (type)
    {
    case BufferDataType::Float:
        return 4;
    case BufferDataType::Float2:
        return 8;
    case BufferDataType::Float3:
        return 12;
    case BufferDataType::Float4:
        return 16;
    case BufferDataType::Int:
        return 4;
    case BufferDataType::Int2:
        return 8;
    case BufferDataType::Int3:
        return 12;
    case BufferDataType::Int4:
        return 16;
    case BufferDataType::Bool:
        return 1;
    case BufferDataType::Mat3:
        return 32;
    case BufferDataType::Mat4:
        return 64;
    }
    EGC_ASSERT(false);
    return 0;
}

struct BufferElement
{
    BufferDataType type;
    std::string name;
    size_t offset;
    size_t size;
    bool normalized;

    BufferElement() = default;

    BufferElement(const BufferDataType type_, const std::string &name_, const bool normalized_ = false)
        : type(type_)
        , name(name_)
        , offset(0)
        , size(GetSizeOfBufferDataType(type_))
        , normalized(normalized_)
    {}

    size_t GetComponentCount() const
    {
        switch (type)
        {
        case BufferDataType::Float:
            return 1;
        case BufferDataType::Float2:
            return 2;
        case BufferDataType::Float3:
            return 3;
        case BufferDataType::Float4:
            return 4;
        case BufferDataType::Int:
            return 1;
        case BufferDataType::Int2:
            return 2;
        case BufferDataType::Int3:
            return 3;
        case BufferDataType::Int4:
            return 3;
        case BufferDataType::Bool:
            return 1;
        case BufferDataType::Mat3:
            return 3;
        case BufferDataType::Mat4:
            return 4;
        }
        EGC_ASSERT_MSG(false, "Do Not Suppurt BufferDataType");
        return 0;
    }
};

class BufferLayout
{
public:
    using LayoutIter = std::vector<BufferElement>::iterator;
    using Const_LayoutIter = std::vector<BufferElement>::const_iterator;

    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements)
        : elements_(elements)
    {
        CalculateOffsetAndStride();
    }

    const size_t GetStride() const
    {
        return stride_;
    }
    const std::vector<BufferElement> &GetElements() const
    {
        return elements_;
    }
    LayoutIter begin()
    {
        return elements_.begin();
    }
    LayoutIter end()
    {
        return elements_.end();
    }
    Const_LayoutIter begin() const
    {
        return elements_.begin();
    }
    Const_LayoutIter end() const
    {
        return elements_.end();
    }

private:
    void CalculateOffsetAndStride()
    {
        size_t offset = 0;
        for (auto &elm : elements_)
        {
            elm.offset = offset;
            offset += elm.size;
            stride_ += elm.size;
        }
    }

    size_t stride_ = 0;
    std::vector<BufferElement> elements_;
};

class VertexBuffer
{
public:
    using VTBPtr = std::shared_ptr<VertexBuffer>;

    virtual ~VertexBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void SetData(const void *data, const size_t size) = 0;

    virtual const BufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout &layout) = 0;

    static VTBPtr Create(const size_t size);
    static VTBPtr Create(const float *vertices, const size_t size);
};

class IndexBuffer
{
public:
    using IDBPtr = std::shared_ptr<IndexBuffer>;

    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const size_t GetCount() const = 0;

    static IDBPtr Create(const uint32_t *indices, const size_t count);
};

} // namespace GRender