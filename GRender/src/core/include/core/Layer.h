#pragma once

#include "core/Event.h"

#include <string>

namespace GRender {
class Layer
{
public:
    Layer(const std::string &name)
        : name_(name)
    {}
    virtual ~Layer() = default;
    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate() {}

    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event &event) {}

    const std::string GetName() const
    {
        return name_;
    }

private:
    std::string name_;
};

} // namespace GRender