# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: A:\Documents\School\ENSC452\Real_Time_Video_Filter\workspace\Real_Time_Video_Filter_system\_ide\scripts\systemdebugger_real_time_video_filter_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source A:\Documents\School\ENSC452\Real_Time_Video_Filter\workspace\Real_Time_Video_Filter_system\_ide\scripts\systemdebugger_real_time_video_filter_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zed 210248469161" && level==0 && jtag_device_ctx=="jsn-Zed-210248469161-03727093-0"}
fpga -file A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace/Data_Processor/_ide/bitstream/Real_Time_Video_Filter_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace/Real_Time_Video_Filter/export/Real_Time_Video_Filter/hw/Real_Time_Video_Filter_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace/Data_Processor/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace/Data_Processor/Debug/Data_Processor.elf
targets -set -nocase -filter {name =~ "*A9*#1"}
dow A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace/SD_Card_Processor/Debug/SD_Card_Processor.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
targets -set -nocase -filter {name =~ "*A9*#1"}
con
