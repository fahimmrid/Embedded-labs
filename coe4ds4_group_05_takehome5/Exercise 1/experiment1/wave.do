	add wave -noupdate /test_bench/CLOCK_50_I
	add wave -noupdate /test_bench/RESET_N_I
	
	add wave -noupdate -divider IOs
	add wave -noupdate -radix hexadecimal /test_bench/SWITCH_I
	add wave -noupdate -radix hexadecimal /test_bench/PUSH_BUTTON_I
	add wave -noupdate -radix hexadecimal /test_bench/LED_RED_O
	add wave -noupdate -radix hexadecimal /test_bench/LED_GREEN_O

	add wave -noupdate -divider CPU_Avalon_Master 
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_waitrequest
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_writedata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_address
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_write
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_read
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_readdata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/cpu_0_data_master_byteenable

	add wave -noupdate -divider JTAG_UART_Avalon_Slave
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_chipselect
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_address
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_read_n
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_readdata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_write_n
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_writedata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_waitrequest
	add wave -noupdate -radix hexadecimal /test_bench/DUT/jtag_uart_0/av_irq

	add wave -noupdate -divider counter
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/chipselect
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/address
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/read
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/write
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/writedata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/readdata
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/counter_expire_irq

	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/reset_counter
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/load
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/load_config
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/load_config_buf
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/counter_value
	add wave -noupdate -radix hexadecimal /test_bench/DUT/custom_counter_component_0/custom_counter_unit_inst/counter_expire
