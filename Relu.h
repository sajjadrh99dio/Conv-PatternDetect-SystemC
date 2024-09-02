#pragma once
#include <systemc.h>

SC_MODULE(Relu) {
	// Ports
	sc_in<sc_lv<8>> input0;
	sc_in<sc_lv<8>> input1;
	sc_in<sc_lv<8>> input2;
	sc_in<sc_lv<8>> input3;
	sc_out<sc_lv<8>> output0;
	sc_out<sc_lv<8>> output1;
	sc_out<sc_lv<8>> output2;
	sc_out<sc_lv<8>> output3;

	SC_CTOR(Relu) {
		SC_METHOD(relu_process);
		sensitive << input0 << input1 << input2 << input3;
	}

	void relu_process() {
		output0.write(input0.read()[7] == SC_LOGIC_0 ? input0.read() : "00000000");
		output1.write(input1.read()[7] == SC_LOGIC_0 ? input1.read() : "00000000");
		output2.write(input2.read()[7] == SC_LOGIC_0 ? input2.read() : "00000000");
		output3.write(input3.read()[7] == SC_LOGIC_0 ? input3.read() : "00000000");
	}
};
