#pragma once

/* ------------------------------------------------------------------------------------------------------- */

namespace steve::application {
   class ILifecycle {
   public:
      virtual void
      on_init() = 0;

      virtual void
      on_render() = 0;

      virtual void
      on_terminate() = 0;

      virtual void
      on_key(int key) = 0;
   };
}

/* ------------------------------------------------------------------------------------------------------- */

namespace steve::application {
   class BasicLifecycle : public ILifecycle {
   public:
      inline void
      on_init() override {}

      inline void
      on_render() override {}

      inline void
      on_terminate() override {}

      inline void
      on_key(int key) override {}
   };
}

/* ------------------------------------------------------------------------------------------------------- */
