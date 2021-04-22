#include <hcl/frontend.h>
#include <hcl/export/vhdl/VHDLExport.h>

using namespace gtry;

int main()
{
    DesignScope design;

    {
        Clock clock{125'000'000}; // 125MHz
        ClockScope clockScope{ clock };

        core::hlim::ClockRational blinkFrequency{1, 1}; // 1Hz

        size_t counterMax = core::hlim::floor(clock.getAbsoluteFrequency() / blinkFrequency);

        BVec counter = BitWidth(utils::Log2C(counterMax+1));
        counter = reg(counter+1, 0);
        HCL_NAMED(counter);

        pinOut(counter.msb()).setName("led");
    }

    gtry::scl::adaptToArchitecture(design.getCircuit(), gtry::scl::DefaultArch{});

    core::vhdl::VHDLExport vhdl{"vhdl/"};
    vhdl(design.getCircuit());
    vhdl.writeVivadoScript("vivado.tcl");

    return 0;
}

