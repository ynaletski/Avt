//---------------------------
  // inp1 - ES
  // inp4 - UZA

  // OUT1 -      - ������� ������
  // OUT2 -      - ������� ������
  // OUT3 - PUMP - ��������� ������
  // OUT4 - ������� ����

  // OUT8 -  �������


  // 7060[1]
// �� ��������� , �� ������������
  // OUT4 - GAS1 - ������ ������� ���� ��������
  // OUT5 - GAS2 - ������ ������� ���� �������� �����������
  // OUT6 - LIQ2 - ������ ������ ���� �������� �����������
  // CLP0 -      - ������� ������
  // OUT8 -  ����� ������� ������

int Out_en_pmp=0;

//---------------------------
char list_avt[][31]={

"�������� ��������.ESC - ����",  // 0~
"Sht-ESC ������� ������      ",  // 1~
"   !������ ��������� ������  ", // 2
"   �������� ����������.      ", // 3
"    !��� ������� ���         ", // 4~
"��������� ����� �����������  ", // 5
" !��� ����� � ������������   ", // 6
"������� ����� � ������������ ", // 7
"��������� ������� �����������", // 8
"��������� �������� ����������", // 9
"", //10~
"  1 ������.����|",//11
"                              ",//12
" ���������� ������ ��������   ",//13
"���������� ����-� ����������  ",//14
"�������� �����������.ESC-����",//15
"  ���������� � ������         ",//16~
"!��� ����� � ������������ 1  ",//17~
"!��� ����� � ������������ 2  ",//18~
"  2-������ ����|",//19
"ESC - ��������� ������        ",//20
" ���������� ������ �����      ",//21
"        ������ �������        ",//22
" ESC - ����������             ",//23
"!�������� MVD,7060 �� ��������",//24
"       !������� ��������      ",//25
" ESC-����, 1-��, 2-��, 8-�����",//26~    " ESC - ���� , 1 - ��, 2 - ��  "
" ESC - ���� , 4 - ����������  ",//27~
" ESC - ����                   ",//28
" ������ �������� �� ����.����.",//29~
"     �������� ����������       ",//30~
"     ������ ������ =ESC=      ",//31
" ������ ������ ��� ���������� ",//32
" ����� ��� � ������.���.����  ",//33
" ����� ��� ��� ������.���.����",//34
"3 ���.���.���.  ",//35
"4 ����.��.���.  ",//36
" ������� � ���-� ����.���.��� ",//37
" ������� � ������� ������ ����",//38
" ������� � ������ ������ ���� ",//39
"  ! ��� ������� 380V          ",//40

};

char *list_rcv[]={
"�����.���-� ����.���.���      ",//0 17
"  2-����� ����.|",//1 19
"ESC - ��������� �����         ",//2 20
"       !������� ������        ",//3 25
"        ���� �������          ",//4 26
"      ����� ����������        ",//5 30
};

//---------------------------

int flag_AC=0; // 1 - ������������ ����� ���� ��������

int Flag_check=0;
unsigned int TimeRest=0;
int flag_v2=1;
float Fl_perm=8.5; //max ���������� ������ ��� �������� ������ ������,�/�

//---------------------------
int stage_rl=0;
int stage_max=0;
int stage_c=0;
int BegStage=Stage2;
long int time_stage_ch=0;
int flag_st_wt=0;
//---------------------------

long int time_antd=0;
long int Tim_antd=0;

long int time_antd_p=0;
long int time_antd_m=0;

long int time_prb_plus=0;
long int time_prb_minus=0;

long int Tim_prb_plus=1000;
long int Tim_prb_minus=200;
//----------------------------
void f_prb_plus()
{
 time_antd_m=TimeStamp;
 if( f_timer(time_prb_plus,Tim_prb_plus ) )
 {
   if( f_timer(time_antd_p,Tim_antd ) )
   {
    time_antd_p=TimeStamp;
    time_prb_plus=TimeStamp;
    time_prb_minus=TimeStamp;
//  Tim_prb_plus=T_prb_plus_big;
//  Tim_prb_minus=T_prb_minus_ltl;
    stage_max+=1;
    if(stage_max > 2) stage_max=2;
   }
 }
}
//---------------------------
void f_prb_minus()
{
 time_antd_p=TimeStamp;
 if( f_timer(time_prb_minus,Tim_prb_minus ) )
 {

   if( f_timer(time_antd_m,Tim_antd ) )
   {
     time_prb_minus=TimeStamp;
     time_prb_plus=TimeStamp;
     time_antd_p=TimeStamp;
     time_antd_m=TimeStamp;
     stage_max-=1;
     if(stage_max < 0) stage_max=0;
   }
 }
}
//---------------------------

void f_alarm();
unsigned int OUT_VAR=0;    // ��������� ���������� �������
unsigned int INP_VAR=0;    // ��������� ���������� ������
unsigned int OUT_VAR_c=0;  // ����� ��������� ���������� �������
unsigned int INP_VAR_c=0;  // ����� ��������� ���������� ������

unsigned int INP_inv=0;    // ����� �������� ������
unsigned int INP_VARi=0;    // ��������� ���������� ������

unsigned int Out_en=0xffff;
unsigned int Out_en_r=0xffff;


int analog_num[8]={1,2,3,4,5,6,7,8};
float analog_scale[8]={1,1,1,1,1,1,1,1};
float analog_offset[8]= {0,0,0,0,0,0,0,0};

int fl_GO_rcv=0;
int fl_GO=0;    // ���� �������/������ ����� MVD
int fl_EQ=0;    // ���� ������������ �������� ����� MVD
int flagS_ES=0; // ������� �������� �� ������� ES
int flagS_UZA=0; // ������� �������� �� ���������� UZA
int flagS_DLT=0; // ������� �������� �� ���������� DELTA

int flag_rcv=0;

long int time_com_cl=2000; // ��, ����� ��������� �������� ����������
long int time_com_cl_off=2000; // ��, ����� ���������� ��������  ����������
long int time_cnt_cl_off=2000; // ��, �������� ����� ��������� ����� � ����������� �������� ����������
long int time_gas_cl_on =2000; // ��, ����� ��������� �������� ����
long int time_gas_cl_off=2000; // ��, ����� ���������� �������� ����

long int time_EQ_rcv=200; // ������
long int time_EQ_dlv=200; // ������
long int time_LIQ_rcv=600; // ������
long int time_LIQ_dlv=600; // ������

int flag_dlv_fst=0; // 0 - �������� Mass total ����� ������� ������� ������
int flag_prn_mass=0;

int sw_dlv_liq=0;
int sw_dlv_gas=0;
int sw_rcv_liq=0;
int sw_rcv_gas=0;

int flag_continue=0;

long int time_t_snd=0;
long int time_t_swtch=0;
int sw_ret=0;
//-----------------------------
void f_prn_key( int key)
{
  MmiGotoxy(0,1);    MmiPuts(" !������ ������  ");
  if(key == ESC) MmiPuts("ESC");
  else if(key == '1') MmiPuts("'1'");
  else if(key == '2') MmiPuts("'2'");
  else if(key == '3') MmiPuts("'3'");
  else MmiPuts("?");
  MmiPuts("             ");
  MmiGotoxy(26,0); MmiPuts("     ");
}
//---------------------------
void f_enable_cnt_rcv()
{

  uk_buf=0;
  if(FL_err)
   if(Flag_check == 0)
   {
    f_wr_evt(evt_wrong_start);
    return;
   }
  Out_en=0xffff;

  fl_GO_rcv=1;

  flag_pool=1;
  flag_O1=1;
  flag_O3=1;

  beg_flch=0;
  flag_flch=0;
  flag_nstg=0;
  time_stg_ctrl=TimeStamp;
  time_stg_ctrl0=TimeStamp;

  flag_fill_ok=0;
  f_wr_evt(evt_start_f+flag_rcv );

  time_beg_fill=TimeStamp;
}
/* ---------------------------------------- */
//---------------------------
/* ---------------------------------------- */
void f_stop_cnt_rcv()
{
//printf("\r\n f_stop_cnt_rcv() ");

//  f_Drive_Stop();
  if(fl_GO_rcv)
  {
   ff_serv_N=f_MVD_cor_rcv;

   tm_mvd_p=TimeStamp;
   t_prep_MVD=TimeStamp;
  }
  fl_GO_rcv=0;
  cl_MVD_sw=0;
  flag_pool=1;
}
/* ---------------------------------------- */
void f_stop_cnt_rcvM()
{
//printf("\r\n f_stop_cnt_rcv() ");

//  f_Drive_Stop();

  if(fl_GO_rcv)
  {
//   ff_serv_N=f_MVD_cor_rcv;

   tm_mvd_p=TimeStamp;
   t_prep_MVD=TimeStamp;
  }
  fl_GO_rcv=0;
  cl_MVD_sw=0;
  flag_pool=1;
}
/* ---------------------------------------- */
void f_stop_cnt_rcvB()
{

//if(fl_GO_rcv)
  {
   ff_serv_N=f_MVD_cor_rcv;

//   tm_mvd_p=TimeStamp;
   t_prep_MVD=TimeStamp;
  }
  fl_GO_rcv=0;
  cl_MVD_sw=0;
  flag_pool=1;
}
/* ---------------------------------------- */
//-----------------------------
int flagE_UZA=0; // ��� ������
int Flag_massR=1;
int key__1=0;
//-----------------------------
int f_rcv_liq(int key)
{
flag_rcv=RCV_FLG;
return f_rcv_dlv_liq(key);

}

int f_dlv_liq(int key)
{
flag_rcv=0;
return f_rcv_dlv_liq(key);

}
int dir_cnt=2;
int f_rcv_dlv_liq(int key)
{
long int ltmp;
float ftmp1,ftmp2;

  if(Flag_check == 0)
    if((FL_err) && (sw_dlv_liq != -1))
    {
      f_clr_scr_MMI();
      f_disp_error();

//    MmiGotoxy(0,5);   MmiPuts("������ ����������.ESC - ����");
//    MmiGotoxy(0,6);   MmiPuts("Sht-ESC ������� ������");
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
           MmiGotoxy(0,5);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,6);   MmiPuts(list_avt[1]);
#else
           MmiGotoxy(0,14);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,15);   MmiPuts(list_avt[1]);
#endif
//25.05.2020 YN --//\\--

      Out_off(OUT1 | OUT2 | OUT3 | OUT4);
      sw_dlv_liq=-1;
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
      f_wr_evt(evt_err_f+flag_rcv);
    }

  switch(sw_dlv_liq)
  {
   // ��������� ��������� - ��� ������� �������,
   // ����� ����������
   // ���������� � ������ ������ ����

   case 1:  // ������ ������ ������ ����

//   printf("\n\r sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);

// flag_rcv=RCV_FLG;

   f_icp_errS(0);
   Out_off(OUT1 | OUT2 | OUT3 | OUT4);

   if(Flag_check != 0) goto mfc1;
   if( (INP_VARi & E_S)==0 )
    {
       f_icp_errS(ES_off);
//     MmiGotoxy(0,1);    MmiPuts("  !������ ��������� ������   ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[2]);
m_err:
//     MmiGotoxy(0,0);    MmiPuts("  ����� ����������.         ");
       MmiGotoxy(0,0);    MmiPuts(list_avt[3]);
//     flag_rcv=0;
       sw_dlv_liq=-1;
       return 0;
    }
   if( (INP_VARi & UZA)==0  )
    {
       flagE_UZA=UZA_E;

       f_icp_errS(UZA_off);
//     MmiGotoxy(0,1);    MmiPuts("  !��� ������� ���           ");
       MmiGotoxy(0,1);    MmiPuts(list_avt[4]);
       goto m_err;
    }
 mfc1:
    sw_dlv_liq=2;
//   printf("\n\r sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);

    MmiGotoxy(0,1);    MmiPuts(list_avt[16]);
    break;
//-----------------------------
   case  2:

   ltmp=TimeStamp+5000;
   MVD[0].time_stamp_pool=ltmp;
   MVD[1].time_stamp_pool=ltmp;
 //
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
 time_t_snd=TimeStamp;

   sw_dlv_liq=3;
   break;
//----------------------------------
//-----------------------------
   case  3:
     MVD_t_rslt[0]=0;
     if(flag_dlv_fst==0)
       sw_dlv_liq=5;
     else
     {
       sw_dlv_liq=64;
       MVD_t_rslt[0]=1;
       time_t_snd=TimeStamp;
     }
//   printf("\n\r sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);
   break;
//-----------------------------
   case  5:
     // ������� ����������� ����� ����������� 1
 MVD_t_rslt[0]=0;
 //
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
 //
 time_t_snd=TimeStamp;
 sw_dlv_liq=501;
//  MmiGotoxy(0,1);    MmiPuts("������� ����������� ����� 1");
//  MmiGotoxy(0,1);    MmiPuts(list_avt[8]);


if(flag_rcv != 0) dir_cnt=2;     //          2- bidirectional flow
else dir_cnt=5;                  //          5 - reverce bidirectional flow
                                 //          |

if(  f_MVD_WR((int)0,(int)MVD_WR_I,(int) 17,dir_cnt,(long int) 0,(float)0) == 0)
 { // ������ ��� �������� ������� MVD
m_e1:
    MmiGotoxy(0,1); MmiPuts(list_avt[17]);// !��� ����� � ������������ 1
   if(Flag_check == 0)
   {
       f_icp_errS(MVD_com);
       goto m_err;
   }
 }
 break;
//-----------------------------
   case  501:
    // �������� ���������� ������� ������� ����� ����-���� 1
    if(key==ESC)    // ������� � ����
     {
         sw_dlv_liq=-2;
         return ESC;
     }
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )  goto mfc51;
    if( MVD_t_rslt[0]>0)
    {
 mfc51:
      MVD_t_rslt[0]=0;
      //
      time_t_snd=TimeStamp;
      sw_dlv_liq=6;

      if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )
      {
         MVD_t_rslt[0]=1;
// printf("\n\rA sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);
         break;
      }

     // ��������� Totalizers ����������� 1
      if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 3 ,(int)1,(long int) 0,(float)0)== 0)
      { // ������ ��� �������� ������� MVD
        goto m_e1;
      }
      MVD_t_rslt[0]=0;
// printf("\n\r sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);
      break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
            goto m_e1;
      MVD_t_rslt[0]=1;
    }
    break;
//-----------------------------

//-----------------------------
   case  6:
    // �������� ���������� ������� ���������  ����-���� 1
    if(key==ESC)    // ������� � ����
     {
         sw_dlv_liq=-2;
         return ESC;
     }
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )  goto mfc3;
    if( MVD_t_rslt[0]>0)
    {
mfc3:

      s_MVD[0].VolT =0;
      s_MVD[0].MassT=0;

#if(SIM0 != 0)
      Sim_VolT[0]=0;
      Sim_MassT[0]=0;
#endif

      MVD_t_rslt[1]=0;
      //
      time_t_snd=TimeStamp;
 MVD_Rqst_T[1].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[1].answ_flt=f_MVD_rd_t;

     // ��������� Totalizers ����������� 2

      sw_dlv_liq=63;
      if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0) && (Flag_check != 0) ) )
      {
         MVD_t_rslt[1]=1;
// printf("\n\rA sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);
         break;
      }

      if( f_MVD_WR((int)1,(int)MVD_WR_C,(int) 3 ,(int)1,(long int) 0,(float)0)== 0)
      { // ������ ��� �������� ������� MVD
m_e1_2:
        if(Flag_check == 0)
           f_icp_errS(MVD_com);
        MmiGotoxy(0,1); MmiPuts(list_avt[18]);  //!��� ����� � ������������ 2
        if(Flag_check == 0)
          goto m_err;
      }
      MVD_t_rslt[1]=0;
// printf("\n\r sw =%d, VI =%f,%ld ms",sw_dlv_liq,s_MVD[0].VolI,TimeStamp-time_beg_fill);
      break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
            goto m_e1;
      MVD_t_rslt[0]=1;
    }
    break;
//-----------------------------
   case  63:
    if(key==ESC)    // ������� � ����
    {
      sw_dlv_liq=-2;
      return ESC;
    }
    // �������� ���������� ������� ��������� All Totals ����-���� 2
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) ) MVD_t_rslt[0]=1;
    if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0) && (Flag_check != 0) ) ) MVD_t_rslt[1]=1;
    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
     sw_dlv_liq=64;

     flag_dlv_fst=1; // Mass Total � Volume Total �������� � ����� ������������

     s_MVD[0].VolT=0;
     s_MVD[1].VolT=0;
     s_MVD[0].MassT=0;
     s_MVD[1].VolTd=0;
     s_MVD[1].MassT=0;

#if(SIM0 != 0)
     Sim_VolT[1]=0;
     Sim_MassT[1]=0;
#endif

     flag_prn_mass=1;
     vol2r=0;
     VolT_int=0;
     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
            goto m_e1;
      MVD_t_rslt[0]=1;
      MVD_t_rslt[1]=1;
    }
    break;
//-----------------------------
   case  64:

     sw_dlv_liq=69;
     break;
//-----------------------------
 case 69:

     MVD_t_rslt[0]=0;

     MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
     MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;

     time_t_snd=TimeStamp;

     sw_dlv_liq=70;
     // ���������� ����� ����������� 1 (cutoff for Mass Flow)
     if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,(float) 0) == 0)
     { // ������ ��� �������� ������� MVD

      if(Flag_check == 0)
              goto m_e1;
     }
     break;

//-----------------------------
   case  70:
    if(key==ESC)    // ������� � ����
    {
         goto m_exit;
    }
    // �������� ���������� ������� ��������� cutoff for Mass Flow ����������� 1
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )  goto mfc70;
    if( MVD_t_rslt[0]>0)
    {
mfc70:
     // ���������� ����� ����������� 1 Start totalizers
      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;
      if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
         if(Flag_check == 0)
               goto m_e1;
      }
     sw_dlv_liq=7;

   MVD[0].time_stamp_pool=TimeStamp;
   MVD[1].time_stamp_pool=TimeStamp+250;

     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
          goto m_e1;
      goto mfc70;
    }
    break;

//-----------------------------
   case  7:
    if(key==ESC)    // ������� � ����
    {
         goto m_exit;
    }
    // �������� ���������� ������� Start totalizers ����������� 1
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )  goto mfc9;
    if( MVD_t_rslt[0]>0)
    {
     // ���������� ����� ����������� 1 (cutoff for Volume Flow)
mfc9:
      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;
      if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 197,(int)0,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
         if(Flag_check == 0)
               goto m_e1;
      }
     sw_dlv_liq=8;

     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
          goto m_e1;
    }
    break;

//-----------------------------
   case  8:
    if(key==ESC)    // ������� � ����
    {
         goto m_exit;
    }
 // �������� ���������� ������� ��������� cutoff for Volume Flow  ����������� 1
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) )  goto mfc10;
    if( MVD_t_rslt[0]>0)
    {
     // ���������� ����� ����������� 2 (cutoff for Mass Flow)
 mfc10:

      if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0) && (Flag_check != 0) ) )
      {
         MVD_t_rslt[1]=1;
         sw_dlv_liq=82;

         break;
      }

      MVD_t_rslt[1]=0;
      time_t_snd=TimeStamp;
     // ���������� ����� ����������� 2 (cutoff for Mass Flow)
      if( f_MVD_WR((int)1,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
          if(Flag_check == 0)
               goto m_e1_2;
      }
     sw_dlv_liq=81;

     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
          goto m_e1;
      else goto mfc10;
    }
    break;

//-----------------------------
   case  81:
    if(key==ESC)    // ������� � ����
    {
         goto m_exit;
    }
    // �������� ���������� ������� ��������� cutoff for Mass Flow ����������� 2
    if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0) && (Flag_check != 0) ) )  goto mfc11;
    if( MVD_t_rslt[1]>0)
    {
mfc11:
     // ���������� ����� ����������� 2 (cutoff for Volume Flow)
      MVD_t_rslt[1]=0;
      time_t_snd=TimeStamp;
      if( f_MVD_WR((int)1,(int)MVD_WR_F,(int) 197,(int)0,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
          if(Flag_check == 0)
               goto m_e1_2;
      }
     sw_dlv_liq=82;
     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      if(Flag_check == 0)
                   goto m_e1_2;
      else goto mfc11;
    }
    break;
//-----------------------------
   case  82:
    if(key==ESC)    // ������� � ����
    {
         goto m_exit;
    }
 // �������� ���������� ������� ��������� cutoff for Volume Flow ����������� 2
    if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0) && (Flag_check != 0) ) ) MVD_t_rslt[0]=1;
    if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0) && (Flag_check != 0) ) ) MVD_t_rslt[1]=1;
    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {

     // ���������� ����� ����������� 2 Start totalizers
      MVD_t_rslt[1]=0;
      time_t_snd=TimeStamp;
      if( f_MVD_WR((int)1,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
         if(Flag_check == 0)
               goto m_e1_2;
      }

  mfc12:
     sw_dlv_liq=9;
     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����

      if(Flag_check == 0)
          goto m_e1_2;
      else goto mfc12;
    }
    break;
//-----------------------------
   case  9:
//  if(key==ESC)    // ������� � ��������� ����������
//      sw_dlv_liq=20;
//  else
    {
//      Out_en_r=0xffff  ;
      // ��������� ��������� ��
      Out_en_r = ~(OUT1 | OUT2 | OUT3 );   // ������� ��������� ���� � �����
      sw_dlv_liq=11;


//     MmiGotoxy(0,1);  MmiPuts(" ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[12]);
    }
    break;
//-----------------------------
   case  11:
       //  ��������� ������ ��������

      f_enable_cnt_rcv();

      MmiGotoxy(0,0);
      if(Flag_check == 0)
      if(flag_rcv != 0)
      {
       if(dose_dlvr != vBIG_P)
        {
         if ( Flag_massR != 0 )
             MmiPrintf("����� ���� %.0f ��         ",dose_dlvr);
         else
           MmiPrintf("����� ���� %.0f �          ",dose_dlvr);
        }
       else
          MmiPuts("����� ��� ���������        ");
      }
      else
      {
       if(dose_dlvr != vBIG_P)
        {
         if ( Flag_massR != 0 )
             MmiPrintf("������ ���� %.0f ��         ",dose_dlvr);
         else
             MmiPrintf("������ ���� %.0f �          ",dose_dlvr);
        }
       else
          MmiPuts("������ ��� ���������        ");
      }

//    MmiGotoxy(0,1);      MmiPuts("                              ");

      MmiGotoxy(0,1);      MmiPuts(list_avt[12]);
      if(Flag_check != 0)
      {
        MmiGotoxy(0,0);  MmiPuts(list_avt[19]);  //  �������
        if((MVD[0].status==0 ) || ( (ICP_error[MVD1] != 0)  ) )
        {
          MmiGotoxy(0,1);      MmiPuts(list_avt[17]);
        }
        else if((MVD[1].status==0 ) || ( (ICP_error[MVD2] != 0)  ) )
        {
          MmiGotoxy(0,1);      MmiPuts(list_avt[18]);
        }
      }

//    MmiGotoxy(0,2);      MmiPuts("                              ");
      MmiGotoxy(0,2);      MmiPuts(list_avt[12]);
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
      MmiGotoxy(0,6);  MmiPuts(list_avt[26]);
#else
      MmiGotoxy(0,15);  MmiPuts(list_avt[26]);
#endif
//25.05.2020 YN --//\\--
      sw_dlv_liq=12;

   break;
//-----------------------------
   case  12:
       //  �����


         if(Flag_check == 0)
         {
           MmiGotoxy(25,0);
           if( (Out_en_r & OUT2)==0  )
              MmiPuts("  ");
           else if( OUT_VAR & OUT2  )
               MmiPuts("��");
           else
               MmiPuts("��");

           MmiGotoxy(28,0);
           if( (Out_en_r & OUT4)==0  )
              MmiPuts("  ");
           else if( OUT_VAR & OUT4  )
               MmiPuts("��");
           else
               MmiPuts("��");

           MmiGotoxy(21,0);
           if( Out_en_pmp )  // �����
               MmiPuts("�_�");
           else
               MmiPuts("   ");

         }


    if((FL_err != 0) && (Flag_check == 0) )   // ������� � ��������� ����������
    {
        key__1=ESC;
        sw_dlv_liq=30;
    //  printf("\n\r sw =A %d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
    }
    else if(key==ESC)       // ������� � ��������� ����������
    {
        key__1=key;
        sw_dlv_liq=30;
// printf("\n\r sw =B %d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
    }
    else if(key=='1')
    {
      Out_en_r ^= (OUT1 | OUT2 | OUT3);   // ������� ��������� � �����
    }
    else if(key=='2')
    {
      Out_en_r ^= OUT4;  // ������ "������� ����"
    }
    else if(key=='8')
    {
      Out_en_pmp ^= OUT3;  // �����
    }
    else if(fl_GO_rcv == 0 ) // ������� � ���������� �� ����������� ������
    {
      key__1=-1;
      if(Flag_check == 0)
      {
        MmiGotoxy(0,0);   MmiPuts(list_avt[25]);  //"       !������� ������       "
      }
//    MmiGotoxy(0,1);   MmiPuts(list_avt[25]);
      sw_dlv_liq=30;
      tm_mvd_p=TimeStamp;

// printf("\n\r sw =C %d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
    }

    if( (Out_en_r & OUT2) == 0 )
    { // ���������� �������� �������� ������
       flag_nstg=0;
       time_stg_ctrl=TimeStamp;
       time_stg_ctrl0=TimeStamp;
       time_beg_fill=TimeStamp;
    }
    break;
//-----------------------------
   case  13:
       //  ������� ������
        key__1=ESC;
        sw_dlv_liq=30;
// printf("\n\r sw =%d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
    break;
//-----------------------------
   case  30:
      // ���������� �������� ������������ ������
      // ���������� � ��������� Tim_prb_minus

      Out_en =  ~OUT1;

      if(Flag_check == 0)
        time_t_snd=TimeStamp;

      if(Flag_check == 0)
        sw_dlv_liq=32;
      else
        sw_dlv_liq=40;

      break;
//-----------------------------
   case  32:

    if( f_timer(time_t_snd,Tim_prb_minus ) )
    {  // ����� �����
      Out_en &= ~OUT2;
      time_t_snd=TimeStamp;
      sw_dlv_liq=33;
    }
      break;
//-----------------------------
   case  33:

    if( f_timer(time_t_snd,Tim_prb_minus ) )
    {  // ����� �����
      sw_dlv_liq=40;
    }
      break;
//-----------------------------
//-----------------------------
   case  40:
      // ������� ������

       tm_mvd_p=TimeStamp;
       Temperature=s_MVD[0].Temp;
       Density=s_MVD[0].Dens;
       f_stop_cnt_rcvM();
       sw_dlv_liq=44;


// printf("\n\r sw =%d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
//     MmiGotoxy(0,1);  MmiPuts(" ���������� ������ ��������   ");
          MmiGotoxy(0,1);
       if(Flag_check == 0)
       {
          MmiPuts(list_avt[13]);
       }
       else
          MmiPuts("   ����������� ��������      ");

       time_t_snd=TimeStamp;

    break;
//-----------------------------
   case  44:
       sw_dlv_liq=50;
// printf("\n\rA sw =%d,%ld ms",sw_dlv_liq,TimeStamp-time_beg_fill);
  //   flag_rcv=0;


       if(key__1== ESC)
       {
m_esc:
         if(Flag_check == 0)
         {
          MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" ������ ����������            ",//30
         }
          MmiGotoxy(0,1);   MmiPuts(list_avt[31]);  //" ������ ������   ESC          ",//31
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
          MmiGotoxy(0,6);   MmiPuts(list_avt[27]);  //" ESC - ���� , 4 - ����������  ",//27
#else
          MmiGotoxy(0,15);   MmiPuts(list_avt[27]);  //" ESC - ���� , 4 - ����������  ",//27
#endif
//25.05.2020 YN --//\\--
          break;
       }
       else if(key__1== STOP_E)
       {
        MmiGotoxy(0,1);   MmiPuts(list_avt[33]);  //"     ������ ������ =STOP=     ",//33

        if(Flag_check == 0)
        {
         MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" ����� ����������            ",//30
        }
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
        MmiGotoxy(0,6);   MmiPuts(list_avt[28]);  //" ESC - ����                   ",//28
#else
        MmiGotoxy(0,15);   MmiPuts(list_avt[28]);  //" ESC - ����                   ",//28
#endif
//25.05.2020 YN --//\\--
        break;
       }
       else if (FL_err)
       {
         f_clr_scr_MMI();
         f_disp_error();
//       MmiGotoxy(0,6);       MmiPuts("������ �������.ESC - ����    ");
         //25.05.2020 YN --\\//--
#if defined(MMI_ICP)
         MmiGotoxy(0,6);       MmiPuts(list_avt[15]);
#else
         MmiGotoxy(0,15);       MmiPuts(list_avt[15]);
#endif
//25.05.2020 YN --//\\--
         break;
       }

//          MmiGotoxy(0,0);   MmiPuts(" ������ ����������            "  );
         if(Flag_check == 0)
         {
             MmiGotoxy(0,0);   MmiPuts(list_avt[30]);
         }
//          MmiGotoxy(0,6);       MmiPuts(" ESC - ����    ");
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
            MmiGotoxy(0,6);       MmiPuts(list_avt[28]);
#else
            MmiGotoxy(0,15);       MmiPuts(list_avt[28]);
#endif
//25.05.2020 YN --//\\--
       if(flag_fill_ok !=0)
          {
//          MmiGotoxy(0,1);       MmiPuts(" ���� ��������     ");
            MmiGotoxy(0,1);


         if(flag_rcv)
         {
            if ( Flag_massR != 0 )
              MmiPrintf(" ���� %g �� �������            ",dose_dlvr);
            else
              MmiPrintf(" ���� %g � �������              ",dose_dlvr);
         }
         else
         {
            if ( Flag_massR != 0 )
              MmiPrintf(" ���� %g �� ��������           ",dose_dlvr);
            else
              MmiPrintf(" ���� %g � ��������             ",dose_dlvr);
         }

            dose_dlvr=vBIG_P;

            break;
          }
          else if(flag_flch !=0)
          {
//          MmiGotoxy(0,1);       MmiPuts(" ������ �������� �� ����.����.");
            MmiGotoxy(0,1);       MmiPuts(list_avt[29]);
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
            MmiGotoxy(0,6);   MmiPuts(list_avt[27]);  //" ESC - ���� , 4 - ����������  ",//27
#else
            MmiGotoxy(0,15);   MmiPuts(list_avt[27]);  //" ESC - ���� , 4 - ����������  ",//27
#endif
//25.05.2020 YN --//\\--
            break;
          }
          else break;
//-----------------------------
   case  50:

       if((key==ESC)||(key==ENTER)  )    // ������� � ����
       {
 m_exit:
         MmiGotoxy(0,0); MmiPuts(list_avt[12]);
         MmiGotoxy(9,0); MmiPuts("����� � ����");
         f_stop_cnt_rcvB();
         sw_dlv_liq=51;
         time_t_snd=TimeStamp;
         return 0;
       }
       else if(key=='4')       // ����������
       {
         if((flag_flch !=0 ) || (key__1== ESC))
         {
             sw_dlv_liq=11;
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
             MmiGotoxy(0,6);       MmiPuts(list_avt[28]);
#else
             MmiGotoxy(0,15);       MmiPuts(list_avt[28]);
#endif
//25.05.2020 YN --//\\--
         }
         return 0;
       }
       break;

//-----------------------------
   case  51:
    if(ff_serv_N== NULL)
    {
//     flag_rcv=0;

       sw_dlv_liq=-2;
       return ESC;
    }
    else
     if( f_timer(time_t_snd,(t_mvd_cor*5) ) )
     {  // ����� �����
      ff_serv_N = NULL;
      f_icp_errS(MVD_com);
      Temperature=s_MVD[0].Temp;
      Density=s_MVD[0].Dens;
      f_wr_evt(evt_est_f+flag_rcv);
      sw_dlv_liq=-2;
      return ESC;
     }

    return PASS;

//-----------------------------
    case -1:
       if((key==ESC)||(key==ENTER)  )    // ������� � ����
       {
         MmiGotoxy(0,0);   MmiPuts("   ����� � ����");
         f_stop_cnt_rcvB();
         sw_dlv_liq=51;
         time_t_snd=TimeStamp;
         sw_dlv_liq=-2;
         return ESC;
       }
       else if (key==Sht_ESC)
        {  // ������� ������
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);
          f_cl_error();
//        MmiGotoxy(0,2);    MmiPuts("        ������ �������       ");
//        MmiGotoxy(0,4);    MmiPuts(" ESC - ����������            ");
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
          MmiGotoxy(0,5);    MmiPuts(list_avt[22]);
          MmiGotoxy(0,6);    MmiPuts(list_avt[23]);
#else
           MmiGotoxy(0,14);   MmiPuts(list_avt[22]);
           MmiGotoxy(0,15);   MmiPuts(list_avt[23]);
#endif
//25.05.2020 YN --//\\--
          sw_dlv_liq=-2;
          return ESC;
        }
       else
         return 0;
//-----------------------------
  }
  return 0;
}
//-----------------------------

/*
void Out_on(int msk)
{
 OUT_VAR |= msk;
}
//-----------------------------
void Out_off(int msk)
{
 OUT_VAR &= ~msk;
}
*/
//-----------------------------
void f_alarm()
{
  TimeOut3=TimeStamp-Out3_delayR_off;
}
//-----------------------------

float dV_ctrl=0;
float dose_A=0;
float dose_Ac=0;
long int TimeStampc=0,tt_vol2rc=0;

int f_ctrl_rcv()
{  // ���������� ��������� � ��������� ���� ��� ������
int itmp;
float ftmp;
long int ltmp;
float CL_V0,CL_V1;

 // ��� ������ ���������� ������� � +
  VolT_int= f_int_v2r();
 /*
  if(fabs(VolT_int) > 10000)
  {
   printf("\r\n VolT_int=%f",VolT_int);
   printf("\r\n vol2r=%f",vol2r);
   printf("\r\n k_volr=%f",Mas2r);
   printf("\r\n tt_vol2r=%ld ",tt_vol2r);
   printf("\r\n TimeStamp=%ld ",TimeStamp);

  }
*/
//  ftmp=  dose_dlvr - VolT_int;
  ftmp=  dose_A - VolT_int;
// � ftmp ������� ������ ��������

 itmp= 0;
 if(fl_GO_rcv == 1)
 {
  if((FL_err != 0) && (Flag_check == 0) )   // ������� � ��������� ����������
  {
    flag_O3=0;
    f_stop_cnt_rcvM();
    goto m_end;
  }

  if(flag_rcv !=0)
  {
    CL_V0=CL_valR[0];
    CL_V1=CL_valR[1];
  }
  else
  {
    CL_V0=CL_val[0];
    CL_V1=CL_val[1];
  }

  TimeOut3=TimeStamp;
        // ������� ������
  if(flag_O1)
    if( (ftmp-k_volr*CL_T1 )> CL_V0 )
    {
      itmp |= OUT1 | OUT4;  // ������� ������ � ���
    }
    else flag_O1=0;
        // ������� ������
  if( (ftmp-k_volr*CL_T2 )> CL_V1 ) itmp |= OUT2;

  if(flag_pool==1)
   if( (ftmp-k_volr*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7060[0].time_stamp_pool=ltmp;
     I7017C[0].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
    }
  if(itmp == 0)
  {// ���������� �� ���������� ��������� ������

    dV_ctrl=ftmp;
//  dose_Ac=dose_A;
//  TimeStampc=TimeStamp;
//  tt_vol2rc=tt_vol2r;

    vol_mom=VolT_int;
    vol_mom0=vol2r;
    flow_mom=k_volr;

    flag_fill_ok=1;
    f_stop_cnt_rcvM();
  }

//if(flag_O1)
  {
    f_dens_r();
    itmp &= i_dens;
  }
 }
  // ���������� ��������
 if(flag_O3)
  if( f_timer(TimeOut3,Out3_delayR_off ))
  {
    flag_O3=0;
  }
  else  itmp |= (OUT3 & Out_en_pmp );

 m_end:
   return itmp;
}
//---------------------------

float P_gas=1.0;

void f_dens_r()
{// ������� ����������� ��������� ��������� � ��������� ����� ���������� ��� ������
 //  ��� ������������� ���������� ������� �������
  float ftmp;

     i_dens =  OUT4 ;   // ������ ���
/*
  if(s_MVD[0].Press > P_gas)
     i_dens =  0 ;   // ������ ���
  else
     i_dens =  OUT4; // ������ ���
*/

  if( f_timer(time_beg_fill,cl2_delayR_off) ==0 )
  { // ��������� ��������� �������� ������� ������ cl2_delay_off �� ����� ������ ������
    time_chg_den=TimeStamp;
    time_antd_m=TimeStamp;
    time_antd_p=TimeStamp;
    time_prb_plus=TimeStamp;
    beg_flch=0;
  }
  else
       i_dens |= OUT2;

  if( f_timer(time_beg_fill,cl1_delayR_off) ==0 )
  { // ��������� ��������� �������� ������� ������ cl1_delay_off �� ����� ������ ������
//    i_dens &=~OUT1;
  }
  else
       i_dens |= OUT1;

    ftmp = s_MVD[0].Press - s_MVD[0].PressG - s_MVD[0].PressB;
    s_MVD[0].PressD=ftmp;

    if( ftmp < PressLvl_off0)
          f_prb_minus();
    else if( ftmp > PressLvl_on0 )
          f_prb_plus();
    else
    {
      time_antd_p=TimeStamp;
      time_antd_m=TimeStamp;
    }

     if(stage_max==0)
       i_dens=~(OUT1 | OUT2) ;            // ������� ��� �������
     else if(stage_max==1)
       i_dens &= ~(OUT1) ;  // ������� ������� ������
}
//---------------------------
void f_sens()
{ // ��������� ��������� ������ ES � UZA ��� �������/������ ���
  // ������� ��������  - ����� �����������
  // inp1 - ES
  // inp2 - UZA
  // (OUT_VAR & LV90)

if(Flag_check == 0)
 if (fl_GO_rcv  != 0)
 {
       if( (INP_VARi & UZA)==0  )
        {
           flagE_UZA=UZA_E;
m_err:
           flagS_UZA=1;
m_err0:
           f_icp_errS(UZA_off);
m_err1:
           f_alarm();
           f_stop_cnt_rcvM();
           sw_dlv_liq=-1;

           f_clr_scr_MMI();
           f_disp_error();

//         MmiGotoxy(0,5);   MmiPuts("������ ����������.ESC - ����");
//         MmiGotoxy(0,6);   MmiPuts("Sht-ESC ������� ������");
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
           MmiGotoxy(0,5);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,6);   MmiPuts(list_avt[1]);
#else
           MmiGotoxy(0,14);   MmiPuts(list_avt[0]);
           MmiGotoxy(0,15);   MmiPuts(list_avt[1]);
#endif
//25.05.2020 YN --//\\--
           return;
        }
m2:

       if( (INP_VARi & E_S)==0 )
        {
           flagS_ES=1;
           f_icp_errS(ES_off);
           goto m_err1;

        }
m1:

/*
  if(flag_O3!=0)
  {
    if( *DriveStatus != 0)
    {
       if(f_Drive_Rn_chk() != 1)
       {
         flagS_DLT=1;
         f_icp_errS(DLT_off);
         f_stop_cnt_rcvM();
       }
    }
  }
*/

  if((flag_O3!=0) && ( (Out_en_pmp & Out_en_r) != 0))
  {
    if(s_MVD[0].Volt_DC <=  volt_dc_cmp)
    {
       flagS_DLT=1;
       f_icp_errS(N380_off);
       goto m_err1;
    }
  }
 }

     if(Fl_perm != 0.)
     {
      if(fabs(s_MVD[0].FlowV) > Fl_perm )
      {
        f_icp_errS(Flow_big);
        goto m_err1;
      }
     }


  return;
}
//---------------------------
//-----------------------------

int flag_nstg=0;
long int time_stg_ctrl=0;
long int time_stg_ctrl0=0;
long int Tim_stg_ctrl0=40000;
long int Tim_stg_ctrl=8000;

void  f_chk_stg()
{
// ������������ ��������� ����������� �������� ��� �������-������
//
// ���� ����� ���.�������� �� ��� �������,����������� ��������, �������
// ��� ������ ������ �����������  ������ ������������
//
// �������� ���������� ����� Tim_stg_ctrl0 (���� !=0) ����� ������ ������� ���
// ����� Tim_stg_ctrl (���� !=0) ����� ������������� �������� ��������.

  if((fl_GO_rcv) && ( Flag_check==0))
  {
   if( ((Tim_stg_ctrl != 0) || ( Tim_stg_ctrl0 != 0 )  ) )
   //
   {
     if(flag_nstg == 0)
     {
       if(stage_max != 2)  time_stg_ctrl=TimeStamp;

       if( f_timer(time_stg_ctrl,Tim_stg_ctrl) )
          flag_nstg=1;

       if( Tim_stg_ctrl0 != 0 )
         if( f_timer(time_stg_ctrl0,Tim_stg_ctrl0) )
           flag_nstg=1;
     }
     else
     {
        if( stage_max != 2)
        {
           flag_flch=1;
           f_stop_cnt_rcvM(); // ������� ������
        }
        else if(flag_O1 != 0)
        {
          if (( val_flch != 0 ) && ( val_flch  > fabs(s_MVD[0].FlowM )) )
          {
           flag_flch=1;
           f_stop_cnt_rcvM(); // ������� ������ �� ������������ ����
          }
        }
        else
        {
          if ( (val_flch2  != 0.) && (  val_flch2  > fabs(s_MVD[0].FlowM ) ))
          {
           flag_flch=1;
           f_stop_cnt_rcvM(); // ������� ������� �� ������������ ����
          }
        }
     }

   }


  }
  return;
}
//-----------------------------------
//-----------------------------------
//float v_lvl1=24.5,v_lvl2=24.0;
float v_lvl1=-4,v_lvl2=-4;
float volt_dc_cmp=-4;
long int Tim_volt=5000;
long int Tim_volt_mes=10000;
long int t_volt_warn=0;
long int t_volt_alarm=0;
int t_off=0;

long int Tim_blink=350;
long int t_blink=0;

//s_MVD[0].Volt_A
//s_MVD[0].Volt_DC

int flagS_VLT=0;
int flag_volt=0;
int flag_blink=0;
int flag_off=0;

#define V_warn  (0x1)
#define V_alarm (0x2)

int flag_uu=0;

void  f_chk_volt()
{
// ������������ ��������� ������������
  if(Flag_check != 0) return;

  if ( s_MVD[0].Volt_A < v_lvl1 )
  {
       flag_volt |= V_warn;
  }
  else
  {
       flag_volt &= ~V_warn;
  }

   if(flag_volt )
   {
     flag_uu=1;
     MmiGotoxy(0,1);
     MmiPrintf("!U");
   }
/*
   else if(flag_uu)
   {
     MmiGotoxy(0,1);
     MmiPrintf("  ");
     flag_uu=0;
   }
*/
  if (( s_MVD[0].Volt_A < v_lvl2 ) || (flag_off != 0))
  {
    t_off=(Tim_volt_mes-(TimeStamp-t_volt_alarm))/1000;
    if( t_off<0) t_off=0;
    flag_volt |= V_alarm;

    MmiGotoxy(0,1);  MmiPrintf("%2d",t_off);

    if( f_timer(t_volt_alarm,Tim_volt))
     if(flag_off==0)
     {
       flagS_VLT=1;
       f_wr_evt(evt_VLT);
       f_icp_errS(VLT_off);
       flag_off=1;
     }

    if( f_timer(t_volt_alarm,Tim_volt_mes))
     {

       Out_off(OUT8);
     }
  }
  else
  {
    t_volt_alarm=TimeStamp;
    flag_volt &= ~V_alarm;
  }

  if(flag_volt )
  {
    if( f_timer(t_blink,Tim_blink))
    {
     t_blink=TimeStamp;
     flag_blink ^= 1;
    }
    if(flag_blink)
    {
      MmiGotoxy(0,1);  MmiPrintf("  ");
    }
  }
//-----------------------------------
}
//-----------------------------------
int sw_pov=0;
int f_pov(int key)
{

  switch(sw_pov)
  {
    case 1:  //

    sw_pov=3;
    time_t_swtch=TimeStamp;
    flag_continue=0;
    break;

   case  3:
   // ������ ��������� ����������� ����� �����������
 MVD_t_rslt[0]=0;
 //
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
//MmiGotoxy(0,1);    MmiPuts("��������� ����� ����������� ");
  MmiGotoxy(0,1);    MmiPuts(list_avt[5]);
 time_t_snd=TimeStamp;
 //                                              |- bidirectional flow
 //                                              |
 if( f_MVD_WR((int)0,(int)MVD_WR_I,(int) 17,(int)2,(long int) 0,(float)0)== 0)
 { // ������ ��� �������� ������� MVD
       f_icp_errS(MVD_com);
       MmiGotoxy(0,1);  MmiPuts(" !��� ����� � ������������   ");
//     MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
m_err:
      sw_pov=9;
      break;
 }
    sw_pov=4;
  break;
//-----------------------------
   case  4:
    // �������� ���������� ������� ������� ����������� �����
    if( MVD_t_rslt[0]>0)
    {
       sw_pov=5;
     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
//     MmiGotoxy(0,1);  MmiPuts("������� ����� � ������������ ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[7]);
       goto m_err;
    }
    break;
//-----------------------------
   case  5:
     // ��������� MassTotal �����������
 MVD_t_rslt[0]=0;
 //
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
 //
 //
 time_t_snd=TimeStamp;
//  MmiGotoxy(0,1);    MmiPuts("��������� ������� �����������");
  MmiGotoxy(0,1);    MmiPuts(list_avt[8]);
 if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 56,(int)1,(long int) 0,(float)0)== 0)
 { // ������ ��� �������� ������� MVD
       f_icp_errS(MVD_com);
//  MmiGotoxy(0,1);  MmiPuts("!��� ����� � ������������    ");
    MmiGotoxy(0,1);  MmiPuts(list_avt[6]);
       goto m_err;
 }
    sw_pov=6;
  break;

//-----------------------------
   case  6:
    // �������� ���������� ������� ��������� MassTotal
    if( MVD_t_rslt[0]>0)
    {
     sw_pov=7;
     flag_dlv_fst=1; // Mass Total ��������
     flag_prn_mass=1;

  vol2=0;
  VolT_int=0;
  VolT_id=0;


  vol2=0;
  k_vol=0;
  Mas2=0;


     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
//     MmiGotoxy(0,1);  MmiPuts("������� ����� � ������������ ");
       MmiGotoxy(0,1);  MmiPuts(list_avt[7]);
       goto m_err;
    }
    if(key==ESC)    // ������� � ����
         return ESC;
    break;
//-----------------------------

   case  7:
     // ���������� ����� ����������� (cutoff for Mass Flow)

 MVD_t_rslt[0]=0;
 //
 MVD_Rqst_T[0].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[0].answ_flt=f_MVD_rd_t;
 //
 //
 time_t_snd=TimeStamp;
  MmiGotoxy(0,1);  MmiPuts(list_avt[5]); //   MmiPuts("���������� ����� �����������");
 if( f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,cutoff_on_M) == 0)
 { // ������ ��� �������� ������� MVD
       f_icp_errS(MVD_com);
    MmiGotoxy(0,1);  MmiPuts(list_avt[6]); // MmiPuts("!��� ����� � ������������    ");
       goto m_err;
 }
    sw_pov=8;
  break;

//-----------------------------
   case  8:
    // �������� ���������� ������� ��������� cutoff for Mass Flow
    if( MVD_t_rslt[0]>0)
    {
     MmiGotoxy(0,1);  MmiPuts(list_avt[12]); // MmiPuts("              ");
//25.05.2020 YN --\\//--
#if defined(MMI_ICP)
     MmiGotoxy(0,6);  MmiPuts(list_avt[28]); // MmiPuts("  ESC - ����   );
#else
     MmiGotoxy(0,15);  MmiPuts(list_avt[28]); // MmiPuts("  ESC - ����   );
#endif
//25.05.2020 YN --//\\--
     sw_pov=9;

     // ���������� ����� ����������� 1 Start totalizers
      MVD_t_rslt[0]=0;
      time_t_snd=TimeStamp;
      if( f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)1,(long int) 0,(float) 0) == 0)
      { // ������ ��� �������� ������� MVD
        f_icp_errS(MVD_com);
        MmiGotoxy(0,1);  MmiPuts(list_avt[6]); // MmiPuts("!��� ����� � ������������    ");
        goto m_err;
      }
     break;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
       MmiGotoxy(0,1);  MmiPuts(list_avt[7]); // MmiPuts("������� ����� � ������������ ");
       goto m_err;
    }
    break;

//-----------------------------

   case  9:
   if(key==ESC)       // �������
    {

       f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,(float) 0);
       MmiGotoxy(0,0);  MmiPuts(" ������� ����������� ");
       f_prn_key(key);
       sw_pov=10;
    }
   break;

//-----------------------------
   case 10:

    if((key==ESC)||(key==ENTER)  )     // ������� � ����
         return ESC;
   break;

//-----------------------------

    default: return ESC;

  }
   return 0;

}
//-----------------------------------
