#include <steve/steve.hpp>

using namespace steve;

Ref<steve::ui::Container>
DrawUI() {
   auto canvas                = CreateRef<steve::ui::Container>();
   canvas->GetProperties().id = "body";
   {
      steve::ui::Styles styles {};
      styles.GetPadding().SetAll(8.0f);
      styles.SetBackgroundColor(steve::ui::StylingSpec::Color::FromHexString("#fff"));
      styles.SetWidth(1056.0f);

      canvas->UpdateStyles(styles);
   }

   // Rest of the ui
   {
      steve::ui::StylingSpec::Width width {};
      width.SetMin(100.0f);

      // Left side
      {
         auto l                = CreateRef<steve::ui::Container>();
         l->GetProperties().id = "left-side";
         l->SetParent(canvas);

         steve::ui::Styles styles {};
         // styles.SetWidth(width);
         styles.GetWidth().SetMin(500.0f);
         styles.SetHeight(100.0f);
         styles.SetBackgroundColor(steve::ui::StylingSpec::Color::FromHexString("#ff0000"));
         l->UpdateStyles(styles);

         canvas->PushChild(l);
      }
      // Right side
      {
         auto r                = CreateRef<steve::ui::Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         steve::ui::Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(steve::ui::StylingSpec::Color::FromHexString("#00ff00"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
      // Right side
      {
         auto r                = CreateRef<steve::ui::Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         steve::ui::Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(steve::ui::StylingSpec::Color::FromHexString("#0000ff"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
   }

   canvas->CalculateBounds();

   return canvas;
}

class Application : public application::BasicLifecycle {
public:
   void
   on_init() override {
      steve::renderer::initialize().except("Failed to initialize renderer.").panic_if_error();
   }

   void
   on_render() override {
      steve::renderer::begin_scene().except("Failed to begin scene.").panic_if_error();

      // Draw ui
      {
         auto canvas   = DrawUI();
         auto vertices = steve::ui::TranslateToQuads(canvas);
         for (auto &v : vertices)
            steve::renderer::draw_vertices({ v.begin(), v.end() })
                .except("Failed to draw vertices.")
                .panic_if_error();
      }

      steve::renderer::end_scene().except("Failed to end scene.").panic_if_error();
   }
};

int
main() {
   steve::run({
       .Title     = "Steve Browser",
       .Width     = (uint32_t)(1920.0f * 0.55f),
       .Height    = (uint32_t)(1080.0f * 0.65f),
       .Lifecycle = CreateRef<Application>(),
       .IsVSync   = false,
   });

   return EXIT_SUCCESS;
}
