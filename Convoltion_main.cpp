#include "Convolution_TB.h"
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

vector<int> image = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0 };

void Convolution_TB::clockGeneration() {
	while (true) {
		clk.write(true);
		wait(10, SC_NS);
		clk.write(false);
		wait(10, SC_NS);
	}
}

void Convolution_TB::generate_signals() {
	// Reset sequence
	conv_start.write(false);
	rst.write(true);
	wait(20, SC_NS);
	rst.write(false);

	// Start the convolution process
	conv_start.write(true);
	wait(20, SC_NS);
	conv_start.write(false);
	wait();
}

void Convolution_TB::data_gen() {
	while (true) {
		if (read_img.read() == 1) {
			sc_uint<8> image_val = image[address.read().to_uint()+1];
			input.write(image_val);
		}
		else {
			input.write(image[0]);
		}
		wait(10, SC_NS); // Ensure wait is present to synchronize with clock
	}
}

void Convolution_TB::monitor_signals() {

	while (true) {
		wait(20, SC_NS);

		cout << "@" << sc_time_stamp()
			<< " input: " << image[address.read().to_uint()]
			<< " read_img: " << read_img.read()
			//<< " address: " << address.read()
			<< " conv_done: " << conv_done.read()
			<< " conv_start: " << conv_start.read()
			<< " output0 : " << output0.read()
			<< " output1 : " << output1.read()
			<< " output2 : " << output2.read()
			<< " output3 : " << output3.read()
			<< endl;
	}
}

int sc_main(int argc, char* argv[]) {
	std::cout << image[0] << endl;
	std::cout << image[15] << endl;
	Convolution_TB tb("tb");
	sc_start(1200, SC_NS); // Run simulation for sufficient time

	return 0;
}
