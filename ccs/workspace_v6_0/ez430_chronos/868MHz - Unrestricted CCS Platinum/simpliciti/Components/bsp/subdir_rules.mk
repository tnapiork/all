################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
simpliciti/Components/bsp/bsp.obj: ../simpliciti/Components/bsp/bsp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/opt/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" --cmd_file="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Applications/configuration/smpl_nwk_config.dat" --cmd_file="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Applications/configuration/End Device/smpl_config.dat"  -vmspx --abi=coffabi -O4 --opt_for_speed=0 --include_path="/opt/ti/ccsv6/ccs_base/msp430/include" --include_path="/opt/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/include" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/logic" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/driver" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/bluerobin" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Applications/application/End Device" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/boards" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/boards/CC430EM" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/drivers" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/drivers/code" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/bsp/mcus" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/mrfi" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/mrfi/radios" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/mrfi/radios/family5" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/mrfi/smartrf" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/nwk" --include_path="/home/tomek/soft/ccs/workspace_v6_0/ez430_chronos/simpliciti/Components/nwk_applications" -g --define=__CC430F6137__ --define=__CCE__ --define=ISM_EU --define=MRFI_CC430 --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="simpliciti/Components/bsp/bsp.pp" --obj_directory="simpliciti/Components/bsp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


