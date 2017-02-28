set moduleName CCLabel_preProcess
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type function
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set pipeII 32
set pipeLatency 32
set C_modelName CCLabel_preProcess
set C_modelType { void 0 }
set C_modelArgList { 
	{ Image_r int 32 regular {array 64 { 1 1 } 1 1 }  }
	{ lbImage int 32 regular {array 64 { 0 0 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "Image_r", "interface" : "memory", "bitwidth" : 32} , 
 	{ "Name" : "lbImage", "interface" : "memory", "bitwidth" : 32} ]}
# RTL Port declarations: 
set portNum 20
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ Image_r_address0 sc_out sc_lv 6 signal 0 } 
	{ Image_r_ce0 sc_out sc_logic 1 signal 0 } 
	{ Image_r_q0 sc_in sc_lv 32 signal 0 } 
	{ Image_r_address1 sc_out sc_lv 6 signal 0 } 
	{ Image_r_ce1 sc_out sc_logic 1 signal 0 } 
	{ Image_r_q1 sc_in sc_lv 32 signal 0 } 
	{ lbImage_address0 sc_out sc_lv 6 signal 1 } 
	{ lbImage_ce0 sc_out sc_logic 1 signal 1 } 
	{ lbImage_we0 sc_out sc_logic 1 signal 1 } 
	{ lbImage_d0 sc_out sc_lv 32 signal 1 } 
	{ lbImage_address1 sc_out sc_lv 6 signal 1 } 
	{ lbImage_ce1 sc_out sc_logic 1 signal 1 } 
	{ lbImage_we1 sc_out sc_logic 1 signal 1 } 
	{ lbImage_d1 sc_out sc_lv 32 signal 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "Image_r_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "Image_r", "role": "address0" }} , 
 	{ "name": "Image_r_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Image_r", "role": "ce0" }} , 
 	{ "name": "Image_r_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Image_r", "role": "q0" }} , 
 	{ "name": "Image_r_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "Image_r", "role": "address1" }} , 
 	{ "name": "Image_r_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "Image_r", "role": "ce1" }} , 
 	{ "name": "Image_r_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "Image_r", "role": "q1" }} , 
 	{ "name": "lbImage_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "lbImage", "role": "address0" }} , 
 	{ "name": "lbImage_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "lbImage", "role": "ce0" }} , 
 	{ "name": "lbImage_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "lbImage", "role": "we0" }} , 
 	{ "name": "lbImage_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "lbImage", "role": "d0" }} , 
 	{ "name": "lbImage_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "lbImage", "role": "address1" }} , 
 	{ "name": "lbImage_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "lbImage", "role": "ce1" }} , 
 	{ "name": "lbImage_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "lbImage", "role": "we1" }} , 
 	{ "name": "lbImage_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "lbImage", "role": "d1" }}  ]}
set Spec2ImplPortList { 
	Image_r { ap_memory {  { Image_r_address0 mem_address 1 6 }  { Image_r_ce0 mem_ce 1 1 }  { Image_r_q0 mem_dout 0 32 }  { Image_r_address1 mem_address 1 6 }  { Image_r_ce1 mem_ce 1 1 }  { Image_r_q1 mem_dout 0 32 } } }
	lbImage { ap_memory {  { lbImage_address0 mem_address 1 6 }  { lbImage_ce0 mem_ce 1 1 }  { lbImage_we0 mem_we 1 1 }  { lbImage_d0 mem_din 1 32 }  { lbImage_address1 mem_address 1 6 }  { lbImage_ce1 mem_ce 1 1 }  { lbImage_we1 mem_we 1 1 }  { lbImage_d1 mem_din 1 32 } } }
}
