
char buf_eep[max_buf_eep];
int eee_num=0;
unsigned long int Eeprom_summ;
unsigned int ee_lgth_byte=0;
float fict_float;
long fict_long_ee=0;
// Список параметров сохраняемых в EEPROM
struct eee_dat EE_Dat[]=
{
&ComBaud[0],sizeof(ComBaud[0]),
&ComBaud[1],sizeof(ComBaud[1]),
&ComBaud[2],sizeof(ComBaud[2]),
&ComBaud[3],sizeof(ComBaud[3]),
&ComBaud[4],sizeof(ComBaud[4]),

&eee_num,sizeof(eee_num),

#if defined(ICP_7017C)
//#if (0)    //defined(ICP_7017C)

&I7017C[0].status         ,sizeof(I7017C[0].status        ),
&I7017C[0].port           ,sizeof(I7017C[0].port          ),
&I7017C[0].addr           ,sizeof(I7017C[0].addr          ),
&I7017C[0].type           ,sizeof(I7017C[0].type          ),
&I7017C[0].format         ,sizeof(I7017C[0].format        ),
&I7017C[0].channels       ,sizeof(I7017C[0].channels      ),
&I7017C[0].CRC_flag       ,sizeof(I7017C[0].CRC_flag      ),
&I7017C[0].pool_time      ,sizeof(I7017C[0].pool_time     ),
&I7017_Rqst[0].timeout    ,sizeof(I7017_Rqst[0].timeout   ),

&I7017C[1].status         ,sizeof(I7017C[1].status        ),
&I7017C[1].port           ,sizeof(I7017C[1].port          ),
&I7017C[1].addr           ,sizeof(I7017C[1].addr          ),
&I7017C[1].type           ,sizeof(I7017C[1].type          ),
&I7017C[1].format         ,sizeof(I7017C[1].format        ),
&I7017C[1].channels       ,sizeof(I7017C[1].channels      ),
&I7017C[1].CRC_flag       ,sizeof(I7017C[1].CRC_flag      ),
&I7017C[1].pool_time      ,sizeof(I7017C[1].pool_time     ),
&I7017_Rqst[1].timeout    ,sizeof(I7017_Rqst[1].timeout   ),
#else

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.type           ,sizeof(ICP_fict.type          ),
&ICP_fict.format         ,sizeof(ICP_fict.format        ),
&ICP_fict.channels       ,sizeof(ICP_fict.channels      ),
&ICP_fict.CRC_flag       ,sizeof(ICP_fict.CRC_flag      ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(I7017_Rqst[0].timeout   ),

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.type           ,sizeof(ICP_fict.type          ),
&ICP_fict.format         ,sizeof(ICP_fict.format        ),
&ICP_fict.channels       ,sizeof(ICP_fict.channels      ),
&ICP_fict.CRC_flag       ,sizeof(ICP_fict.CRC_flag      ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(I7017_Rqst[0].timeout   ),

#endif

&MMI.status         ,sizeof(MMI.status        ),
&MMI.port           ,sizeof(MMI.port          ),
&MMI.addr           ,sizeof(MMI.addr          ),
&MMI.type           ,sizeof(MMI.type          ),
&MMI.format         ,sizeof(MMI.format        ),
&MMI.channels       ,sizeof(MMI.channels      ),
&MMI.CRC_flag       ,sizeof(MMI.CRC_flag      ),
&MMI.pool_time      ,sizeof(MMI.pool_time     ),
&MMI_Rqst.timeout    ,sizeof(MMI_Rqst.timeout   ),

&ComPortEcho          ,sizeof(ComPortEcho        ),
&ToutLicpScan         ,sizeof(ToutLicpScan       ),
&licp_amax            ,sizeof(licp_amax          ),
&LICP_Rqst.CRC_flag   ,sizeof(LICP_Rqst.CRC_flag ),

#if (1)    //defined(ICP_7060)

&I7060[0].status         ,sizeof(I7060[0].status        ),
&I7060[0].port           ,sizeof(I7060[0].port          ),
&I7060[0].addr           ,sizeof(I7060[0].addr          ),
&I7060[0].type           ,sizeof(I7060[0].type          ),
&I7060[0].format         ,sizeof(I7060[0].format        ),
&I7060[0].channels       ,sizeof(I7060[0].channels      ),
&I7060[0].CRC_flag       ,sizeof(I7060[0].CRC_flag      ),
&I7060[0].pool_time      ,sizeof(I7060[0].pool_time     ),
&I7060_Rqst[0].timeout    ,sizeof(I7060_Rqst[0].timeout   ),

&I7060[1].status         ,sizeof(I7060[1].status        ),
&I7060[1].port           ,sizeof(I7060[1].port          ),
&I7060[1].addr           ,sizeof(I7060[1].addr          ),
&I7060[1].type           ,sizeof(I7060[1].type          ),
&I7060[1].format         ,sizeof(I7060[1].format        ),
&I7060[1].channels       ,sizeof(I7060[1].channels      ),
&I7060[1].CRC_flag       ,sizeof(I7060[1].CRC_flag      ),
&I7060[1].pool_time      ,sizeof(I7060[1].pool_time     ),
&I7060_Rqst[1].timeout    ,sizeof(I7060_Rqst[1].timeout   ),
#else

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.type           ,sizeof(ICP_fict.type          ),
&ICP_fict.format         ,sizeof(ICP_fict.format        ),
&ICP_fict.channels       ,sizeof(ICP_fict.channels      ),
&ICP_fict.CRC_flag       ,sizeof(ICP_fict.CRC_flag      ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(I7017_Rqst[0].timeout   ),

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.type           ,sizeof(ICP_fict.type          ),
&ICP_fict.format         ,sizeof(ICP_fict.format        ),
&ICP_fict.channels       ,sizeof(ICP_fict.channels      ),
&ICP_fict.CRC_flag       ,sizeof(ICP_fict.CRC_flag      ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(I7017_Rqst[0].timeout   ),

#endif

&WDOG[0].status         ,sizeof( WDOG[0].status        ),
&WDOG[0].port           ,sizeof( WDOG[0].port          ),
&WDOG[0].CRC_flag       ,sizeof( WDOG[0].CRC_flag      ),
&WDOG[0].pool_time      ,sizeof( WDOG[0].pool_time     ),
&WDOG_Rqst[0].timeout   ,sizeof( WDOG_Rqst[0].timeout   ),

&WDOG[1].status         ,sizeof( WDOG[0].status        ),
&WDOG[1].port           ,sizeof( WDOG[0].port          ),
&WDOG[1].CRC_flag       ,sizeof( WDOG[0].CRC_flag      ),
&WDOG[1].pool_time      ,sizeof( WDOG[0].pool_time     ),
&WDOG_Rqst[1].timeout   ,sizeof( WDOG_Rqst[0].timeout   ),

&I7060_wd_E[0]          ,sizeof( I7060_wd_E[0]          ),
&I7060_wd_VV[0]         ,sizeof( I7060_wd_VV[0]         ),
&I7060_wd_E[1]          ,sizeof( I7060_wd_E[1]          ),
&I7060_wd_VV[1]         ,sizeof( I7060_wd_VV[1]         ),

&ComProt[0]     ,sizeof( ComProt[0] ),
&ComProt[1]     ,sizeof( ComProt[1] ),
&ComProt[2]     ,sizeof( ComProt[2] ),
&ComProt[3]     ,sizeof( ComProt[3] ),
&ComProt[4]     ,sizeof( ComProt[4] ),


#if defined(RTU_ComSK)

&ComSK[0].status         ,sizeof(ComSK[0].status        ),
&ComSK[0].port           ,sizeof(ComSK[0].port          ),
&ComSK[0].addr           ,sizeof(ComSK[0].addr          ),
&ComSK[0].pool_time      ,sizeof(ComSK[0].pool_time     ),
&ComSK_Rqst[0].timeout   ,sizeof(ComSK_Rqst[0].timeout   ),
&ComSK_WD_Rqst[0].timeout, sizeof(ComSK_WD_Rqst[0].timeout),
&sk_pool_period[0] ,sizeof(sk_pool_period[0]),

&ComSK[1].status         ,sizeof(ComSK[1].status        ),
&ComSK[1].port           ,sizeof(ComSK[1].port          ),
&ComSK[1].addr           ,sizeof(ComSK[1].addr          ),
&ComSK[1].pool_time      ,sizeof(ComSK[1].pool_time     ),
&ComSK_Rqst[1].timeout   ,sizeof(ComSK_Rqst[1].timeout   ),
&ComSK_WD_Rqst[1].timeout, sizeof(ComSK_WD_Rqst[1].timeout),
&sk_pool_period[1] ,sizeof(sk_pool_period[1]),

#else
#if defined(RTU_Delta)

&Delta[0].status         ,sizeof(Delta[0].status        ),
&Delta[0].port           ,sizeof(Delta[0].port          ),
&Delta[0].addr           ,sizeof(Delta[0].addr          ),
&Delta[0].pool_time      ,sizeof(Delta[0].pool_time     ),
&Delta_Rqst[0].timeout   ,sizeof(Delta_Rqst[0].timeout   ),
&fict_long_ee             ,sizeof(fict_long_ee),
&fict_long_ee             ,sizeof(fict_long_ee),
//&Delta_WD_Rqst[0].timeout, sizeof(Delta_WD_Rqst[0].timeout),
//&Dlt_pool_period[0] ,sizeof(sk_pool_period[0]),

&Delta[1].status         ,sizeof(Delta[1].status        ),
&Delta[1].port           ,sizeof(Delta[1].port          ),
&Delta[1].addr           ,sizeof(Delta[1].addr          ),
&Delta[1].pool_time      ,sizeof(Delta[1].pool_time     ),
&Delta_Rqst[1].timeout   ,sizeof(Delta_Rqst[1].timeout   ),
&fict_long                ,sizeof(fict_long),
&fict_long                ,sizeof(fict_long),
//&Delta_WD_Rqst[1].timeout, sizeof(Delta_WD_Rqst[1].timeout),
//&Dlt_pool_period[1] ,sizeof(sk_pool_period[1]),

#else

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),
&fict_long                ,sizeof(fict_long),
&fict_long                ,sizeof(fict_long),

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),
&fict_long            ,sizeof(fict_long),
&fict_long            ,sizeof(fict_long),

#endif
#endif
//-----------------------

&Com_lgth[0]   ,sizeof(Com_lgth[0]),
&Com_lgth[1]   ,sizeof(Com_lgth[0]),
&Com_lgth[2]   ,sizeof(Com_lgth[0]),
&Com_lgth[3]   ,sizeof(Com_lgth[0]),
&Com_lgth[4]   ,sizeof(Com_lgth[0]),
&Com_parity[0],sizeof(Com_parity[0]),
&Com_parity[1],sizeof(Com_parity[0]),
&Com_parity[2],sizeof(Com_parity[0]),
&Com_parity[3],sizeof(Com_parity[0]),
&Com_parity[4],sizeof(Com_parity[0]),
&Com_stop[0]  ,sizeof(Com_stop[0]),
&Com_stop[1]  ,sizeof(Com_stop[0]),
&Com_stop[2]  ,sizeof(Com_stop[0]),
&Com_stop[3]  ,sizeof(Com_stop[0]),
&Com_stop[4]  ,sizeof(Com_stop[0]),

//-----------------------
#if  (1)   // defined(RTU_MVD)

&MVD[0].status         ,sizeof(MVD[0].status        ),
&MVD[0].port           ,sizeof(MVD[0].port          ),
&MVD[0].addr           ,sizeof(MVD[0].addr          ),
&MVD[0].pool_time      ,sizeof(MVD[0].pool_time     ),
&MVD_Rqst[0].timeout   ,sizeof(MVD_Rqst[0].timeout   ),

&MVD[1].status         ,sizeof(MVD[1].status        ),
&MVD[1].port           ,sizeof(MVD[1].port          ),
&MVD[1].addr           ,sizeof(MVD[1].addr          ),
&MVD[1].pool_time      ,sizeof(MVD[1].pool_time     ),
&MVD_Rqst[1].timeout   ,sizeof(MVD_Rqst[1].timeout   ),

#else

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),

#endif
//-----------------------
#if defined(ICP_TSD)

&TSD[0].status         ,sizeof(TSD[0].status        ),
&TSD[0].port           ,sizeof(TSD[0].port          ),
&TSD[0].addr           ,sizeof(TSD[0].addr          ),
&TSD[0].pool_time      ,sizeof(TSD[0].pool_time     ),
&TSD_Rqst[0].timeout   ,sizeof(TSD_Rqst[0].timeout   ),

&TSD[1].status         ,sizeof(TSD[1].status        ),
&TSD[1].port           ,sizeof(TSD[1].port          ),
&TSD[1].addr           ,sizeof(TSD[1].addr          ),
&TSD[1].pool_time      ,sizeof(TSD[1].pool_time     ),
&TSD_Rqst[1].timeout   ,sizeof(TSD_Rqst[1].timeout   ),

#else

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),

&ICP_fict.status         ,sizeof(ICP_fict.status        ),
&ICP_fict.port           ,sizeof(ICP_fict.port          ),
&ICP_fict.addr           ,sizeof(ICP_fict.addr          ),
&ICP_fict.pool_time      ,sizeof(ICP_fict.pool_time     ),
&Rqst_fict.timeout    ,sizeof(Rqst_fict.timeout   ),

#endif

//-----------------------

&n_dot[0][0]    ,sizeof(n_dot ),
&CL_val[0]      ,sizeof(CL_val[0] ),
&CL_val[1]      ,sizeof(CL_val[1] ),
&TSD_vn[0][0]   ,sizeof(TSD_vn ),
&byte_timout_rtu[0]   ,sizeof(byte_timout_rtu),
&scom_tim[0]   ,sizeof(scom_tim),
&t_ctrl   ,sizeof(t_ctrl),
&tim_MVD_delay   ,sizeof(tim_MVD_delay),
&TSD_period   ,sizeof(TSD_period),
&CL_T1   ,sizeof(CL_T1),
&CL_T2   ,sizeof(CL_T2),
&fct_offs   ,sizeof(fct_offs),
&fct_offs_r ,  sizeof( fct_offs_r ),
&t_mvd_cor   ,sizeof(t_mvd_cor),
&CL_T3   ,sizeof(CL_T3),
&CL_T4   ,sizeof(CL_T4),

&num_out1   ,sizeof(num_out1),
&num_out2   ,sizeof(num_out2),

&cutoff_off_M ,sizeof(cutoff_off_M),

&TimeMVD_Init ,sizeof(TimeMVD_Init),
&TimeMVD_evt  ,sizeof(TimeMVD_evt ),

&ahour00.hour ,sizeof(ahour00.hour),
&ahour00.min  ,sizeof(ahour00.min),
&ahour00.sec  ,sizeof(ahour00.sec),

//-----------------------
&ComBaudPmp1    ,sizeof(ComBaudPmp1   ),
&Com_lgthPmp1   ,sizeof(Com_lgthPmp1  ),
&Com_parityPmp1 ,sizeof(Com_parityPmp1),
&Com_stopPmp1   ,sizeof(Com_stopPmp1  ),
//-----------------------
&ComPortPmp1,sizeof(ComPortPmp1),
&P_addr     ,sizeof(P_addr  ),
&flag_spec   ,sizeof(flag_spec  ),
//-----------------------
&num_out3   ,sizeof(num_out3  ),
&num_out4   ,sizeof(num_out4  ),
&num_in1    ,sizeof(num_in1   ),
&num_in2    ,sizeof(num_in2   ),
&num_in3    ,sizeof(num_in3   ),
&num_in4    ,sizeof(num_in4   ),
&mski_inp1  ,sizeof(mski_inp1 ),
&mski_inp2  ,sizeof(mski_inp2 ),
&mski_inp3  ,sizeof(mski_inp3 ),
&mski_inp4  ,sizeof(mski_inp4 ),

&flag_Serv  ,sizeof(flag_Serv ),

&FlagWinSum ,sizeof(FlagWinSum ),

&f_ns[0]        ,sizeof(f_ns[0]        ),
&f_ns[1]        ,sizeof(f_ns[1]        ),
&f_ns[2]        ,sizeof(f_ns[2]        ),
&f_ns[3]        ,sizeof(f_ns[3]        ),
&f_ns[4]        ,sizeof(f_ns[4]        ),
&i_nn_d         ,sizeof(i_nn_d         ),
&dim_xyz        ,sizeof(dim_xyz        ),
&fl_trace_loop  ,sizeof(fl_trace_loop  ),

//-----------------------
&PermPlus       ,sizeof(PermPlus       ),
&PermMinus      ,sizeof(PermMinus      ),
&t20c           ,sizeof(t20c           ),
&v_Proc         ,sizeof(v_Proc         ),
&flag_20C       ,sizeof(flag_20C       ),
&fict_float     ,sizeof(fict_float     ),

&cl1_delayR_off    ,sizeof(cl1_delayR_off    ),
&cl1_delayR_off    ,sizeof(cl1_delayR_off  ),
&cl1_delayR_off ,sizeof(cl1_delayR_off ),
&k_Den_Off      ,sizeof(k_Den_Off      ),
&k_Den_On       ,sizeof(k_Den_On       ),

&Password       ,sizeof(Password       ),

&ModeFill       ,sizeof(ModeFill      ),

&un_mmi1       ,sizeof(un_mmi1      ),
&un_mmi2       ,sizeof(un_mmi2      ),
&un_mmi3       ,sizeof(un_mmi3      ),

&ex_p       ,sizeof(ex_p     ),
&ex_m       ,sizeof(ex_m     ),

&cost_v     ,sizeof(cost_v   ),

&WD_PMP_Per ,sizeof(WD_PMP_Per  ),

&time_flch ,sizeof(time_flch  ),
&val_flch  ,sizeof(val_flch   ),

&cl2_delayR_off ,sizeof(cl2_delayR_off ),
&Out3_delayR_off ,sizeof(Out3_delayR_off ),

&TimeBegFlch  ,sizeof(TimeBegFlch),

&num_out5   ,sizeof(num_out5  ),
&num_out6   ,sizeof(num_out6  ),
&num_out7   ,sizeof(num_out7  ),
&num_out8   ,sizeof(num_out8  ),

&analog_num[0]      ,sizeof(analog_num[0]    ),
&analog_scale[0]    ,sizeof(analog_scale[0]  ),
&analog_offset[0]   ,sizeof(analog_offset[0] ),

&analog_num[1]      ,sizeof(analog_num[0]    ),
&analog_scale[1]    ,sizeof(analog_scale[0]  ),
&analog_offset[1]   ,sizeof(analog_offset[0] ),

&time_com_cl   ,sizeof(time_com_cl ),
&time_com_cl_off   ,sizeof(time_com_cl_off ),
&time_cnt_cl_off   ,sizeof(time_cnt_cl_off ),
&time_gas_cl_on   ,sizeof(time_gas_cl_on ),
&time_gas_cl_off  ,sizeof(time_gas_cl_off ),

&time_LIQ_dlv  ,sizeof(time_LIQ_dlv ),
&time_EQ_dlv  ,sizeof(time_EQ_dlv ),
&time_LIQ_rcv  ,sizeof(time_LIQ_rcv ),
&time_EQ_rcv  ,sizeof(time_EQ_rcv ),

&Delta_SV_beg[0]  ,sizeof(Delta_SV_beg[0] ),
&Delta_SA_beg[0]  ,sizeof(Delta_SA_beg[0] ),
&Delta_SD_beg[0]  ,sizeof(Delta_SD_beg[0] ),

&ModeReduce               ,sizeof( ModeReduce          ),
&PressLvl_on1             ,sizeof( PressLvl_on1        ),
&PressLvl_off1            ,sizeof( PressLvl_off1       ),
&PressLvl_on2             ,sizeof( PressLvl_on2        ),
&PressLvl_off2            ,sizeof( PressLvl_off2       ),

&Delta_SV[0]         ,sizeof( Delta_SV[0]        ),
&Delta_SV[1]         ,sizeof( Delta_SV[1]        ),

&CL_T0                      ,sizeof( CL_T0                     ),
&CL_valR[0]                 ,sizeof( CL_valR[0]                ),
&cl2_delayR_off             ,sizeof( cl2_delayR_off            ),
&k_Den0_Off                 ,sizeof( k_Den0_Off                ),
&k_Den0_On                  ,sizeof( k_Den0_On                 ),
&PressLvl_on0               ,sizeof( PressLvl_on0              ),
&PressLvl_off0              ,sizeof( PressLvl_off0             ),

&fict_long                 ,sizeof( fict_long                ),
&fict_long                 ,sizeof( fict_long                ),

&v_num_var                ,sizeof( v_num_var    ),

&flag_ext_t             ,sizeof( flag_ext_t     ),
&val0_flch              ,sizeof( val0_flch      ),
&val_flch2              ,sizeof( val_flch2      ),

&fl_id1  ,sizeof( fl_id1),
&chr_id[0] ,sizeof( chr_id),
&fl_id  ,sizeof( fl_id),

&adc_et[0][0]  ,sizeof( adc_et),
&val_et[0][0]  ,sizeof( val_et),
&n_dat_et[0]   ,sizeof( n_dat_et),
&ZeroPage   ,sizeof( ZeroPage),

&BegStage   ,sizeof( BegStage),
&Tim_antd   ,sizeof( Tim_antd),


&k_p        ,sizeof(k_p      ),
&k_i        ,sizeof(k_i      ),
&k_d        ,sizeof(k_d      ),

&maxP_errP  ,sizeof(maxP_errP      ),
&maxP_errM  ,sizeof(maxP_errM      ),
&LIM_P      ,sizeof(LIM_P          ),
&LIM_M      ,sizeof(LIM_M          ),
&f_Beg      ,sizeof(f_Beg     ),
&P_dem      ,sizeof(P_dem     ),

&Temp_kor   ,sizeof(Temp_kor  ),
&Comp_kor   ,sizeof(Comp_kor  ),

&P_Dif_d   ,sizeof(P_Dif_d  ),

&LIMd_P   ,sizeof(LIMd_P  ),
&LIMd_M   ,sizeof(LIMd_M  ),

&maxPd_errP   ,sizeof(maxPd_errP  ),
&maxPd_errM   ,sizeof(maxPd_errM  ),

&kd_p     ,sizeof(kd_p    ),
&kd_i     ,sizeof(kd_i    ),
&kd_d     ,sizeof(kd_d    ),

&Flow_on[1]  ,sizeof(Flow_on[1]    ),
&Flow_on[2]  ,sizeof(Flow_on[2]    ),
&Flow_on[3]  ,sizeof(Flow_on[3]    ),
&Flow_on[4]  ,sizeof(Flow_on[4]    ),

&Flow_off[1] ,sizeof(Flow_off[1]    ),
&Flow_off[2] ,sizeof(Flow_off[2]    ),
&Flow_off[3] ,sizeof(Flow_off[3]    ),
&Flow_off[4] ,sizeof(Flow_off[4]    ),

&mode_r ,sizeof(mode_r ),

&Tim_stg_ctrl ,sizeof(Tim_stg_ctrl ),
&Tim_stg_ctrl0 ,sizeof(Tim_stg_ctrl0 ),

&I_dem   ,sizeof(I_dem ),

&LIMi_P   ,sizeof(LIMi_P  ),
&LIMi_M   ,sizeof(LIMi_M  ),

&maxPi_errP   ,sizeof(maxPi_errP  ),
&maxPi_errM   ,sizeof(maxPi_errM  ),

&ki_p     ,sizeof(ki_p    ),
&ki_i     ,sizeof(ki_i    ),
&ki_d     ,sizeof(ki_d    ),

&mode_i   ,sizeof(mode_i  ),

&num_clp_sv   ,sizeof(num_clp_sv  ),

&Fl_perm   ,sizeof(Fl_perm  ),

&analog_num[2]      ,sizeof(analog_num[0]    ),
&analog_scale[2]    ,sizeof(analog_scale[0]  ),
&analog_offset[2]   ,sizeof(analog_offset[0] ),

&v_lvl1   ,sizeof(v_lvl1 ),
&v_lvl2   ,sizeof(v_lvl2 ),
&Tim_volt ,sizeof(Tim_volt ),
&Tim_volt_mes ,sizeof(Tim_volt ),
&volt_dc_cmp ,sizeof(volt_dc_cmp ),

//-----------------------
&cutoff_off_V,  sizeof(cutoff_off_V),

&EmptyPage ,sizeof(EmptyPage),
//-----------------------
&Eeprom_summ,sizeof(Eeprom_summ),

NULL,0,
};
//---------------------------
void f_ee_num_init()
{
int i;
   for( i=0;EE_Dat[i].ptr != 0;i++) {}
   eee_num=i;
}
//---------------------------
int ee_members=0;
int f_wrt_eee()
/* Store all variables in EEE  */
{
int i,i1,i2,j;
int val;
char *ch_ptr;

 f_init_mki();
 Eeprom_summ=0;

        for(i=0,i1=0;EE_Dat[i].ptr!=0;i++)
        {
          i2=EE_Dat[i].l;
          ch_ptr=(char *)EE_Dat[i].ptr;
          for(j=0;j<i2;j++)
          {
            buf_eep[i1]=*ch_ptr++;
            if(EE_Dat[i].ptr!= &Eeprom_summ)
//              Eeprom_summ +=buf_eep[i1];
              Eeprom_summ +=((unsigned long)(buf_eep[i1])) & 0xff;
            i1++;
          }
        }

          i2=EE_Dat[i].l;
          ch_ptr=(char *)EE_Dat[i].ptr;

 EE_WriteEnable();
   i2= EE_MultiWrite_L(0,i1,buf_eep);
 EE_WriteProtect();

    ee_members=i;

// printf (" %d",i);
 return i2;
}
//--------------------------------------
int f_chk_EEE_CRC()
{
int i,i1,i2,j;
int val;
char *ch_ptr;
unsigned long int Ee_summ;

 Ee_summ=0;

 if((i1=EE_MultiRead_L(0,2048,buf_eep))<0 )
 {
   return i1;
 }
//-----------------------------
   // Check CRC
        for(i=0,i1=0;EE_Dat[i].ptr!=0;i++)
        {
          i2=EE_Dat[i].l;
          ch_ptr=(char *)EE_Dat[i].ptr;
          for(j=0;j<i2;j++)
          {
            if(EE_Dat[i].ptr==&Eeprom_summ)
              *ch_ptr++=buf_eep[i1++];
            else
              Ee_summ +=((unsigned long)(buf_eep[i1++])) & 0xff;
          }
        }

     ee_lgth_byte=i1;
//  printf("\n\rf_chk_EEE_CRC: %d записей,%dбайт,CRC_count=%08lx,CRC_rd%08lx\n\r",i,i1,Ee_summ,Eeprom_summ);
   if(Ee_summ != Eeprom_summ) return -100;
   return 0;
}
//--------------------------------------
int f_rd_eee()
/* Read all variables from  buf_eep  */
{
int i,i1,i2,j;
int val;
char *ch_ptr;

unsigned long int Ee_summ;
 Ee_summ=0;
//-----------------------------

   for(i=0,i1=0;(EE_Dat[i].ptr!=0)&&(i<(eee_num-1)) ;i++)
   {
     i2=EE_Dat[i].l;
     ch_ptr=(char *)EE_Dat[i].ptr;
     for(j=0;j<i2;j++)
     {
       *ch_ptr++=buf_eep[i1];
       Ee_summ +=buf_eep[i1++];
     }
   }
   f_ee_num_init();
   f_prep_bern();
   f_count_cf();

   f_init_mki();

   f_rd_cor();
   return 0;
}
//--------------------------------------

