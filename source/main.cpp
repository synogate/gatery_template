#include <gatery/frontend.h>
#include <gatery/utils.h>
#include <gatery/export/vhdl/VHDLExport.h>

#include <gatery/scl/arch/intel/IntelDevice.h>
#include <gatery/scl/synthesisTools/IntelQuartus.h>

#include <gatery/simulation/waveformFormats/VCDSink.h>
#include <gatery/simulation/ReferenceSimulator.h>

using namespace gtry;
using namespace gtry::vhdl;
using namespace gtry::scl;
using namespace gtry::utils; 

int main()
{
	DesignScope design;

	// Optional: Set target technology
	{
		auto device = std::make_unique<IntelDevice>();
		device->setupCyclone10();
		design.setTargetTechnology(std::move(device));
	}

	// Build circuit
	Clock clock{1'000}; // 1KHz
	ClockScope clockScope{ clock };

	hlim::ClockRational blinkFrequency{1, 1}; // 1Hz
	size_t counterMax = hlim::floor(clock.getAbsoluteFrequency() / blinkFrequency);
	UInt counter = BitWidth(utils::Log2C(counterMax+1));
	auto enable = pinIn().setName("button");
	
	IF (enable)
		counter += 1;

	counter = reg(counter, 0);
	HCL_NAMED(counter);

	pinOut(counter.msb()).setName("led");

	design.postprocess();

	// Optional: Setup simulation
	sim::ReferenceSimulator simulator;
	simulator.compileProgram(design.getCircuit());

	simulator.addSimulationProcess([=, &clock]()->SimProcess{
		simu(enable) = '0';
		for ([[maybe_unused]]auto i : Range(300))
			co_await AfterClk(clock);

		simu(enable) = '1';
	});


	// Optional: Record simulation waveforms as VCD file
	sim::VCDSink vcd(design.getCircuit(), simulator, "waveform.vcd");
	vcd.addAllPins();
	vcd.addAllSignals();


	// Optional: VHDL export
	VHDLExport vhdl("vhdl/");
	vhdl.addTestbenchRecorder(simulator, "testbench", false);
	vhdl.targetSynthesisTool(new IntelQuartus());
	vhdl.writeProjectFile("import_IPCore.tcl");
	vhdl.writeStandAloneProjectFile("IPCore.qsf");
	vhdl.writeConstraintsFile("constraints.sdc");
	vhdl.writeClocksFile("clocks.sdc");
	vhdl(design.getCircuit());

	// Run simulation
	simulator.powerOn();
	simulator.advance(hlim::ClockRational(5000,1'000));

	return 0;
}