#include <steve/steve.hpp>

using namespace steve;
using namespace application;
using namespace ui;
using namespace StylingSpec;

/* ------------------------------------------------------------------------------------------------------- */

Ref<Container>
DrawUI() {
   auto canvas                = CreateRef<Container>();
   canvas->GetProperties().id = "body";
   {
      Styles styles {};
      styles.GetPadding().SetAll(8.0f);
      styles.SetBackgroundColor(Color::FromHexString("#fff"));
      styles.SetWidth(1056.0f);

      canvas->UpdateStyles(styles);
   }

   // Rest of the ui
   {
      Width width {};
      width.SetMin(100.0f);

      // Left side
      {
         auto l                = CreateRef<Container>();
         l->GetProperties().id = "left-side";
         l->SetParent(canvas);

         Styles styles {};
         // styles.SetWidth(width);
         styles.GetWidth().SetMin(500.0f);
         styles.SetHeight(100.0f);
         styles.SetBackgroundColor(Color::FromHexString("#ff0000"));
         l->UpdateStyles(styles);

         canvas->PushChild(l);
      }
      // Right side
      {
         auto r                = CreateRef<Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(Color::FromHexString("#00ff00"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
      // Right side
      {
         auto r                = CreateRef<Container>();
         r->GetProperties().id = "right-side";
         r->SetParent(canvas);

         Styles styles {};
         styles.SetWidth(width);
         styles.SetHeight(80.0f);
         styles.SetBackgroundColor(Color::FromHexString("#0000ff"));
         r->UpdateStyles(styles);

         canvas->PushChild(r);
      }
   }

   canvas->CalculateBounds();

   return canvas;
}

/* ------------------------------------------------------------------------------------------------------- */

class Application : public BasicLifecycle {
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
         auto vertices = TranslateToQuads(canvas);
         for (auto &v : vertices)
            steve::renderer::draw_vertices({ v.begin(), v.end() })
                .except("Failed to draw vertices.")
                .panic_if_error();
      }

      steve::renderer::end_scene().except("Failed to end scene.").panic_if_error();
   }
};

/* ------------------------------------------------------------------------------------------------------- */

int
main() {
   run_as_app({
       .Title     = "Steve Browser",
       .Width     = (uint32_t)(1920.0f * 0.55f),
       .Height    = (uint32_t)(1080.0f * 0.65f),
       .Lifecycle = CreateRef<Application>(),
       .IsVSync   = false,
   });

   return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------------- */
