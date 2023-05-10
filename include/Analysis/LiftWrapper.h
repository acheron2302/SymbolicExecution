extern "C" {
#include <libvex.h>
#include <libvex_guest_offsets.h>
#include <pyvex.h>
}
#include <vector>

namespace vex {
class Lifter {
  private:
    IRSB *irsb;
    VexArchInfo vex_arch_info;

  public:
    Lifter();
    void Lift(std::vector<uint8_t> _vec);
};
} // namespace vex