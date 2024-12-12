#pragma once

#define RETURN_IF_ERROR(result)  \
   if (result.is_error()) {      \
      return result.get_error(); \
   }

#define DLOG std::cout << __FILE__ << ":" << __LINE__ << " " << __func__ << std::endl
#define DGLERROR \
   std::cout << __FILE__ << ":" << __LINE__ << " " << __func__ << " " << glGetError() << std::endl

#define MAX_QUADS    1000
#define MAX_VERTICES (MAX_QUADS * 4)
#define MAX_INDICES  (MAX_QUADS * 6)
