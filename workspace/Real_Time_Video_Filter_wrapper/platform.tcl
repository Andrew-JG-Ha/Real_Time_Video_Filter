# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct A:\Documents\School\ENSC452\Real_Time_Video_Filter\workspace\Real_Time_Video_Filter_Wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source A:\Documents\School\ENSC452\Real_Time_Video_Filter\workspace\Real_Time_Video_Filter_Wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Real_Time_Video_Filter_Wrapper}\
-hw {A:\Documents\School\ENSC452\Real_Time_Video_Filter\Real_Time_Video_Filter_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {A:/Documents/School/ENSC452/Real_Time_Video_Filter/workspace}

platform write
platform generate -domains 
platform active {Real_Time_Video_Filter_Wrapper}
platform generate
platform config -updatehw {A:/Documents/School/ENSC452/Real_Time_Video_Filter/Real_Time_Video_Filter_wrapper.xsa}
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
platform generate -domains 
platform generate
domain create -name {standalone_ps7_cortexa9_1} -display-name {standalone_ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {Real_Time_Video_Filter_Wrapper}
domain active {zynq_fsbl}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_1}
platform generate -quick
platform generate -domains standalone_ps7_cortexa9_1 
bsp reload
bsp setlib -name xilffs -ver 4.4
bsp write
bsp reload
catch {bsp regenerate}
bsp reload
platform generate -domains standalone_ps7_cortexa9_1 
platform generate
platform active {Real_Time_Video_Filter_Wrapper}
platform config -updatehw {S:/Documents/GitHub/Real_Time_Video_Filter/Real_Time_Video_Filter_wrapper.xsa}
platform generate -domains 
platform active {Real_Time_Video_Filter_Wrapper}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra -DUSE_AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_ps7_cortexa9_1 
bsp write
domain active {standalone_domain}
bsp reload
bsp reload
platform generate -domains 
domain active {standalone_ps7_cortexa9_1}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra"
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp config extra_compiler_flags "-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -nostartfiles -g -Wall -Wextra  -DUSE_AMP=1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_domain,standalone_ps7_cortexa9_1 
domain active {standalone_ps7_cortexa9_1}
bsp write
platform active {Real_Time_Video_Filter_Wrapper}
