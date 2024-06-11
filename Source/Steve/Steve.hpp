#pragma once

#include <Steve/Steve.hpp>
#include <Steve/Graphics/Draw/Draw.hpp>
#include <Steve/Graphics/Renderer/Renderer.hpp>
#include <Steve/Application/ApplicationWindow.hpp>

class Application : public ApplicationWindow::LifeCycle
{
   void
   OnInit() override;

   void
   OnRender() override;
};

namespace Steve
{
   Result<bool>
   Run();
}
