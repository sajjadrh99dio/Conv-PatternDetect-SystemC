#pragma once
#include <systemc.h>

SC_MODULE(Result) {
	// Ports
	sc_in<sc_lv<8>> input0;
	sc_in<sc_lv<8>> input1;
	sc_in<sc_lv<8>> input2;
	sc_out<sc_lv<3>> output;

	// Internal signals
	sc_signal<sc_lv<2>> output_signal_1;
	sc_signal<bool> output_signal_2;
	sc_signal<sc_lv<3>> output_signal_3;
	sc_signal<sc_lv<8>> temp1;

	SC_CTOR(Result) {
		SC_METHOD(process_input0_input1);
		sensitive << input0 << input1 <<input2;

		//SC_METHOD(process_temp1_input2);
		//sensitive << temp1 << input2;

		//SC_METHOD(select_output_signal_3);
		//sensitive << output_signal_2 << output_signal_1;
	}

	void process_input0_input1();


	//void process_temp1_input2();


	//void select_output_signal_3();

};





void Result::process_input0_input1() {
	//temp1.write("00000000");
	//output_signal_1.write("00");
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
		SC_DO_NOTHING);
	if (input0.read().to_uint() >= input1.read().to_uint()) {
		if (input0.read().to_uint() >= input2.read().to_uint()){
			temp1.write(input0.read());
			output.write("001");
		}
		else {
			temp1.write(input2.read());
			output.write("100");
		}
	}
	else {
		if (input1.read().to_uint() >= input2.read().to_uint()){
			temp1.write(input1.read());
			output.write("010");
		}
		else {
			temp1.write(input2.read());
			output.write("100");
		}

	
	}

}

/*
void Result :: process_input0_input1() {
		//temp1.write("00000000");
		//output_signal_1.write("00");

		if (input0.read().to_uint() >= input1.read().to_uint()) {
			temp1.write(input0.read());

			output_signal_1.write("01");
		}
		else {
			temp1.write(input1.read());
			output_signal_1.write("10");
		}
	}

void Result::process_temp1_input2() {
		//output_signal_2.write(false);
		if (temp1.read().to_uint() >= input2.read().to_uint()) {
			output_signal_2.write(false);
		}
		else {
			output_signal_2.write(true);
		}
	}

void Result :: select_output_signal_3() {
		if (output_signal_2.read() == false) {
			if (output_signal_1.read() == "01"){
				output_signal_3.write("001");
			}
			else if (output_signal_1.read() == "10"){
				output_signal_3.write("010");
			}
			//output_signal_3.write("0" + output_signal_1.read());
		}
		else {
			output_signal_3.write("100");
		}
		
		output.write(output_signal_3.read());
		//output_temp.write(temp1.read());
}

*/