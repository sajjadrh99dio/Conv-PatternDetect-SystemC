#pragma once
#include <systemc.h>

SC_MODULE(Img_RAM) {
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_in<sc_lv<8>> data_in;
	sc_in<sc_lv<4>> addr_wr;
	sc_in<bool> write_enable;
	sc_out<sc_lv<8>> data_rd1;
	sc_in<sc_lv<4>> addr_rd1;
	sc_in<bool> read1;
	sc_out<sc_lv<8>> data_rd2;
	sc_in<sc_lv<4>> addr_rd2;
	sc_in<bool> read2;
	sc_out<sc_lv<8>> data_rd3;
	sc_in<sc_lv<4>> addr_rd3;
	sc_in<bool> read3;

	sc_lv<8> ram[18];

	SC_CTOR(Img_RAM) {
		SC_METHOD(ram_process);
		sensitive << clk.pos();
	}

	void ram_process() {
		static int temp1 = 0;
		static int temp2 = 0;
		static int temp3 = 0;
		if (rst.read() == 1) {
			for (int i = 0; i < 16; i++) {
				ram[i] = "00000000";
			}
		}
		else if (clk.posedge()) {
			if (write_enable.read() == 1) {
				ram[addr_wr.read().to_uint()] = data_in.read();
			}
			if (read1.read() == 1) {
				if (addr_rd1.read() == 0)
					temp1++;
			if (temp1<=1)
					data_rd1.write(ram[addr_rd1.read().to_uint()+1]);
				else
					data_rd1.write(ram[addr_rd1.read().to_uint()+temp1]);
			}
			else {
				data_rd1.write(ram[0]);
			}
			if (read2.read() == 1) {
				if (addr_rd2.read() == 0)
					temp2++;
				if (temp2 <= 1)
					data_rd2.write(ram[addr_rd2.read().to_uint() + 1]);
				else
					data_rd2.write(ram[addr_rd2.read().to_uint() + temp2]);
			}
			else {
				data_rd2.write(ram[0]);
			}
			if (read3.read() == 1) {
				if (addr_rd3.read() == 0)
					temp3++;
				if (temp3 <= 1)
					data_rd3.write(ram[addr_rd3.read().to_uint() + 1]);
				else
					data_rd3.write(ram[addr_rd3.read().to_uint() + temp3]);
			}
			else {
				data_rd3.write(ram[0]);
			}
		}
	}
};


