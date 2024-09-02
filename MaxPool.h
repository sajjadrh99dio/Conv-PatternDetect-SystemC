#pragma once
#include <systemc.h>

SC_MODULE(MaxPool) {

	sc_in<sc_lv<8>> input0, input1, input2, input3;
	sc_out<sc_lv<8>> output;

	sc_signal<sc_lv<8>> output_signal;
	sc_signal<sc_lv<8>> temp1, temp2;

	SC_CTOR(MaxPool) {
		SC_METHOD(process_inputs1);
		sensitive << input0 << input1;

		SC_METHOD(process_inputs2);
		sensitive << input2 << input3;

		SC_METHOD(process_temps);
		sensitive << temp1 << temp2;

		SC_METHOD(assign_output);
		sensitive << output_signal;
	}

	void process_inputs1();
	void process_inputs2();
	void process_temps();
	void assign_output();
};

void MaxPool::process_inputs1() {
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
		SC_DO_NOTHING);
	temp1.write("00000000");
	if (input0.read().to_uint() >= input1.read().to_uint()){
		temp1 = (input0.read());

	}
	else
		temp1 = (input1.read());
}

void MaxPool::process_inputs2() {
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
		SC_DO_NOTHING);
	temp2.write("00000000");
	if (input2.read().to_uint() >= input3.read().to_uint()){
		temp2 = (input2.read());

	}
	else
		temp2 = (input3.read());
}

void MaxPool::process_temps() {
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
		SC_DO_NOTHING);
	if (temp1.read().to_uint() >= temp2.read().to_uint()){
		output_signal = (temp1.read());

	}
	else
		output_signal = (temp2.read());
}

void MaxPool::assign_output() {
	output.write(output_signal.read());
}
