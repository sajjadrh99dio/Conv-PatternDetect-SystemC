#include <systemc.h>
#include "MaxPool_TB.h"

int sc_main(int argc, char* argv[]) {

	sc_signal<sc_lv<8>> input0, input1, input2, input3;
	sc_signal<sc_lv<8>> output;
	sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
		SC_DO_NOTHING);

	MaxPool maxpool("maxpool");
		maxpool.input0(input0);
		maxpool.input1(input1);
		maxpool.input2(input2);
		maxpool.input3(input3);
		maxpool.output(output);
		sc_start(1, SC_NS);

		// Test case 1
		input0.write("00000010"); // 2
		input1.write("00000001"); // 1
		input2.write("00000011"); // 3
		input3.write("00000100"); // 4
		sc_start(1, SC_NS);
		cout << "Test case 1: Output = " << output.read().to_uint() << endl;

		// Test case 2
		input0.write("00000101"); // 5
		input1.write("00000111"); // 7
		input2.write("00000110"); // 6
		input3.write("00000011"); // 3
		sc_start(1, SC_NS);
		cout << "Test case 2: Output = " << output.read().to_uint() << endl;

		// Test case 3
		input0.write("00001111"); // 15
		input1.write("00001111"); // 15
		input2.write("00001010"); // 10
		input3.write("00001010"); // 10
		sc_start(1, SC_NS);
		cout << "Test case 3: Output = " << output.read().to_uint() << endl;

		// Test case 4
		input0.write("00001111"); // 0
		input1.write("00010000"); // 0
		input2.write("00001100"); // 0
		input3.write("00001011"); // 0
		sc_start(1, SC_NS);
		cout << "Test case 4: Output = " << output.read().to_uint() << endl;

		// Test case 5
		input0.write("01110001"); // 
		input1.write("00010000"); // 
		input2.write("01111111"); // 
		input3.write("00000001"); // 
		sc_start(1, SC_NS);
		cout << "Test case 5: Output = " << output.read().to_uint() << endl;

	return 0;
};