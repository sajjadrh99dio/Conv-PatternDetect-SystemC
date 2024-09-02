#include <systemc.h>
#include "Img_RAM.h"

// Testbench for Img_RAM
SC_MODULE(Img_RAM_Testbench) {
	// Signals
	sc_signal<bool> clk;
	sc_signal<bool> rst;
	sc_signal<sc_lv<8>> data_in;
	sc_signal<sc_lv<4>> addr_wr;
	sc_signal<bool> write_enable;
	sc_signal<sc_lv<8>> data_rd1;
	sc_signal<sc_lv<4>> addr_rd1;
	sc_signal<bool> read1;
	sc_signal<sc_lv<8>> data_rd2;
	sc_signal<sc_lv<4>> addr_rd2;
	sc_signal<bool> read2;
	sc_signal<sc_lv<8>> data_rd3;
	sc_signal<sc_lv<4>> addr_rd3;
	sc_signal<bool> read3;

	// Instance of Img_RAM
	Img_RAM* ram_inst;

	SC_CTOR(Img_RAM_Testbench) {
		ram_inst = new Img_RAM("ram_inst");

		// Connect the signals
		ram_inst->clk(clk);
		ram_inst->rst(rst);
		ram_inst->data_in(data_in);
		ram_inst->addr_wr(addr_wr);
		ram_inst->write_enable(write_enable);
		ram_inst->data_rd1(data_rd1);
		ram_inst->addr_rd1(addr_rd1);
		ram_inst->read1(read1);
		ram_inst->data_rd2(data_rd2);
		ram_inst->addr_rd2(addr_rd2);
		ram_inst->read2(read2);
		ram_inst->data_rd3(data_rd3);
		ram_inst->addr_rd3(addr_rd3);
		ram_inst->read3(read3);

		SC_THREAD(test);
	}

	void test() {
		// Initialize signals
		clk.write(false);
		rst.write(true);
		data_in.write("00000000");
		addr_wr.write("0000");
		write_enable.write(false);
		addr_rd1.write("0000");
		read1.write(false);
		addr_rd2.write("0000");
		read2.write(false);
		addr_rd3.write("0000");
		read3.write(false);

		// Reset the RAM
		wait(10, SC_NS);
		rst.write(false);

		// Write some values to the RAM
		for (int i = 0; i < 16; i++) {
			addr_wr.write(i);
			data_in.write(i);
			write_enable.write(true);
			wait(10, SC_NS);
			clk.write(true);
			wait(10, SC_NS);
			clk.write(false);
			write_enable.write(false);
		}

		// Read back the values
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

		// Finish simulation
		sc_stop();
	}

	~Img_RAM_Testbench() {
		delete ram_inst;
	}
};

// Main function to run the testbench
int sc_main(int argc, char* argv[]) {
	Img_RAM_Testbench tb("tb");
	sc_start();
	return 0;
}
