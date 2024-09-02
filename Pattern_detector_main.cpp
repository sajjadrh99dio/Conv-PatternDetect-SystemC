#include "Pattern_detector.h"
#include <vector>
#include <iostream>

using namespace std;

vector<int> image1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0,0 };
vector<int> image2 = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 };
vector<int> image3 = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 };

void Pattern_detector::clockGeneration() {
	while (true) {
		clk.write(true);
		wait(10, SC_NS);
		clk.write(false);
		wait(10, SC_NS);
	}
}
/*
void Pattern_detector::ram_store() {
	wait(80, SC_NS);
	write_enable.write(true);
	for (int i = 0; i < 16; i++) {
		data_in.write(image1[i]);
		cout << "image : " << i << " is " << image1[i] << endl;
		addr_wr.write(i);
		//wait(20, SC_NS);
	}
	write_enable.write(false);
	wait();
	//write_enable.write(false);
}


void Pattern_detector::data_gen1() {
	while (true) {
		if (read1.read() == 1) {
			sc_uint<8> image_val = image1[addr_rd1.read().to_uint()+1];
			//cout << "\nconv1 data = " << image_val<<endl;
			data_rd1.write(image_val);
		}
		else {
			data_rd1.write(image1[0]);
		}
		wait(10, SC_NS); // Ensure wait is present to synchronize with clock
	}
}

void Pattern_detector::data_gen2() {
	while (true) {
		if (read2.read() == 1) {
			sc_uint<8> image_val = image2[addr_rd2.read().to_uint()+1];
			//cout << "\nconv2 data = " << image_val<<endl;
			data_rd2.write(image_val);
		}
		else {
			data_rd2.write(image2[0]);
		}
		wait(10, SC_NS); // Ensure wait is present to synchronize with clock
	}
}

void Pattern_detector::data_gen3() {
	while (true) {
		if (read3.read() == 1) {
			sc_uint<8> image_val = image3[addr_rd3.read().to_uint()+1];
			//cout << "\nconv3 data = " << image_val << endl;
			data_rd3.write(image_val);
		}
		else {
			data_rd3.write(image3[0]);
		}
		wait(10, SC_NS); // Ensure wait is present to synchronize with clock
	}
}
*/
void Pattern_detector::generate_signals() {
	// Reset sequence
	conv_start.write(false);
	rst.write(true);
	wait(20, SC_NS);
	rst.write(false);
	write_enable.write(true);
	for (int i = 0; i < 16; i++) {
		write_enable.write(true);
		addr_wr.write(i);
		data_in.write(image1[i]);
		cout << "image : " << i << " is " << image1[i] << endl;
		wait(20, SC_NS);
		write_enable.write(false);
	}
	write_enable.write(false);
	wait(500, SC_NS);

	// Start the convolution process
	conv_start.write(true);
	wait(20, SC_NS);
	conv_start.write(false);

	wait();
}

void Pattern_detector::done_process() {
	//done.write(conv_done1.read() && conv_done2.read() && conv_done3.read());
	while (true){
		if ( conv_done1 == 1){
			conv_start2.write(1);
			wait(20, SC_NS);
			conv_start2.write(0);
		}
		else if (conv_done2.read() == 1){
			conv_start3.write(1);
			wait(20, SC_NS);
			conv_start3.write(0);
		}
		else if (conv_done3.read() == 1){
			done.write(1);
			wait(20, SC_NS);
			done.write(0);
		}
		wait(10, SC_NS);
	}
}

void Pattern_detector::final_result_process() {
	Final_Result.write(result_out.read());
}

void Pattern_detector::monitor_signals() {
	while (true) {
		sc_report_handler::set_actions(SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_,
			SC_DO_NOTHING);
		wait(20, SC_NS);
		/*
		cout << "@" << sc_time_stamp()
			<< " Conv Start: " << conv_start.read()
			<< " Conv Start: " << conv_start2.read()
			<< " Conv Start: " << conv_start3.read()
			<< " done: " << conv_done1.read()
			<< " address 1 is " << addr_rd1.read()
			<< " address 2 is " << addr_rd2.read()
			<< " address 3 is " << addr_rd3.read()
			<< " output1: " << output_conv2_0.read()
			<< " output2: " << output_conv2_1.read()
			<< " output3: " << output_conv2_2.read()
			<< " output4: " << output_conv2_3.read()
			<< endl;
			*/
		
		cout << "read1 = " << read1.read() << endl <<
			"address1 = " << addr_rd1.read() << endl <<
			"data = " << data_rd1.read();


		/*
		cout << " \nmaxpool\noutput1: " << MaxPool1_out.read()
			<< " output2: " << MaxPool2_out.read()
			<< " output3: " << MaxPool3_out.read();
			//<< " output4: " << relu1_out3.read();
	
		for (int i = 0; i < 16; i++) {
			addr_rd1.write(i);
			read1.write(true);
			wait(10, SC_NS);
			clk.write(true);
			wait(10, SC_NS);
			clk.write(false);
			cout << "Address " << i << ": Data = " << data_rd1.read() << endl;
			read1.write(false);
		}
		*/
		


	}
}

int sc_main(int argc, char* argv[]) {
	Pattern_detector Pattern_detector_TB("Pattern_detector_TB");
	sc_start(6000, SC_NS); // Run simulation for sufficient time
	return 0;
}
