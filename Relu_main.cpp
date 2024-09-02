#include <systemc.h>
#include "Relu_TB.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_lv<8>> input0;
	sc_signal<sc_lv<8>> input1;
	sc_signal<sc_lv<8>> input2;
	sc_signal<sc_lv<8>> input3;
	sc_signal<sc_lv<8>> output0;
	sc_signal<sc_lv<8>> output1;
	sc_signal<sc_lv<8>> output2;
	sc_signal<sc_lv<8>> output3;

	Relu_TB relu("relu");
	relu.input0(input0);
	relu.input1(input1);
	relu.input2(input2);
	relu.input3(input3);
	relu.output0(output0);
	relu.output1(output1);
	relu.output2(output2);
	relu.output3(output3);

	sc_start(1, SC_NS); // Initialize the simulation

	// Testbench code to apply input stimulus and check outputs
	input0.write("00001111"); // Positive number
	input1.write("11110000"); // Negative number
	input2.write("00000000"); // Zero
	input3.write("01111111"); // Positive number

	sc_start(1, SC_NS);

	std::cout << "Output0: " << output0.read() << std::endl; // Should be 00001111
	std::cout << "Output1: " << output1.read() << std::endl; // Should be 00000000
	std::cout << "Output2: " << output2.read() << std::endl; // Should be 00000000
	std::cout << "Output3: " << output3.read() << std::endl; // Should be 01111111

	return 0;
}