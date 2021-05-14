#include <gatery/frontend.h>
#include <gatery/export/vhdl/VHDLExport.h>
#include <iostream>

using namespace gtry;

int main()
{
    DesignScope design;

    {
        Clock clock{125'000'000}; // 125MHz
        ClockScope clockScope{ clock };

        hlim::ClockRational blinkFrequency{1, 1}; // 1Hz

        size_t counterMax = hlim::floor(clock.getAbsoluteFrequency() / blinkFrequency);

        BVec counter = BitWidth(utils::Log2C(counterMax+1));
        counter = reg(counter+1, 0);
        HCL_NAMED(counter);

        pinOut(counter.msb()).setName("led");
    }

    design.getCircuit().postprocess(DefaultPostprocessing{});

    vhdl::VHDLExport vhdl{"vhdl/"};
    vhdl(design.getCircuit());
    vhdl.writeVivadoScript("vivado.tcl");

    return 0;
}

