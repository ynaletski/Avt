
/*
     Main
*/

#include "ALL.h"

int  MMI_inp_err=0;
int  MMI_out_err=0;

char sw_ver[20]="A1.27 25 May 2020";  // COM0 COM1 COM2 COM3 COM4

unsigned long ComBaud[5]={9600,9600,9600,9600,115200};
int Com_lgth[5]={8,8,8,8,8};
int Com_parity[5]={0,0,0,0,0};//0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)

int Com_stop[5]={1,1,1,1,1};

int  ComProt[5]={0,0,0,0,0};

long int baudrate_val[]={1200,1200,1200,1200,2400,4800,9600,19200,38400,57600,115200};

unsigned long ComBaudPmp1=115200L;
int Com_lgthPmp1  =8;
int Com_parityPmp1=0;// Odd   //0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)
int Com_stopPmp1  =1;
int ComPortPmp1 = 4;
int P_addr=1;
int flag_spec = 0; // 䫠� ���७���� ����
long int WD_PMP_Per=20000;

//------------------------
#define MAX_ADC_COR  2  // ������⢮ ������㥬�� ������� ADC
#define MAX_COR_D 16    // ������⢮ ��室��� �祪 ���४樨

// ��室�� ����� ��� ����஥��� ⠡���� ���४樨
int n_dat_et[MAX_ADC_COR]={0,0};
float adc_et[MAX_ADC_COR][MAX_COR_D]={ 32124 ,  9123, 17342  };
float val_et[MAX_ADC_COR][MAX_COR_D]={  6.54 , 2.743, 4.234  };

//------------------------
int f_get_nb( long int baud)
{
int i;
 for(i=3;i<11;i++)
  if(baudrate_val[i]== baud)
    return i;
 return -1;
}
//------------------------
//--------------------------
void ShowPort(int port)
{
  Show5DigitLedWithDot(1,port);
}
void ShowChecksum(int checksum)
{
  Show5DigitLedWithDot(2,checksum);
}
void ShowBaudrate(long baud)
{ int data;

  if(baud>100000) data=baud/1000;
  else data=baud/100;

  Show5DigitLed(5,data%10);
  data/=10;
  Show5DigitLed(4,data%10);
  data/=10;
  Show5DigitLed(3,data%10);
}

void ShowCom( int port,int checksum,long int baud)
{
  ShowPort(port);
  ShowChecksum(checksum);
  ShowBaudrate(baud);

}
//-------------------
int i_ish;
void ShowNumber(long Num)
{ // �뢮��� �᫮ � �����筮� �ଥ �� 5DigitLed
int i,i1,dig;
char buf[10];

i_ish=Num;
return;
/*
  sprintf(buf,"%ld",Num);
  i=strlen(buf);
  if(i>0) i--;

  for(i1=0;i1<5;i1++,i--)
  {
    if(i>=0)
    {
     dig=buf[i]-'0';
    }
    else dig=0;
      Show5DigitLed(i1,dig);
  }
  printf("\n\r==%s==\n\r",buf);
*/

}
//-------------------
int getch_host()
{
while(!IsCom(ComPortHost));
 return(ReadCom(ComPortHost));
}
//-------------------
int puts_host(char *str)
{
int i;
 for(i=0;str[i];i++)
 putch(str[i]);
 return i;
}
//-------------------

void  f_cycle_cmn()
{

     f_time_dd();
     if( WDOG[0].status)  f_WDOG(0);

#if defined(ICP_7017C)

        if(Flag_check==0)
        {
          if(I7017C[0].status)  f_7017C(0);
        }
        else
        {
          if(ICP_error[N_7017] == 0)
            if(I7017C[0].status)  f_7017C(0);
        }
#endif

      f_ctrl_v2();
//    f_chk_stg();

      f_chk_volt();

      ServiceCOM(1);
      ServiceCOM(2);
      ServiceCOM(3);

#if defined(RTU_MVD)

        if(MVD[0].status != 0)
        {
          if(Flag_check == 0)
          {
            f_MVD(0);
          }
          else if(ICP_error[MVD1] == 0)
          {
                    f_MVD(0);
          }
        }
        else
        {

#if(SIM0 != 0)
         f_sim_MVD(0);
#endif
         MVD_fl[0]=0;
        }

        if(MVD[1].status != 0)
        {
          if(Flag_check == 0)
          {
            f_MVD(1);
          }
          else if(ICP_error[MVD2] == 0)
          {
                    f_MVD(1);
          }
        }
        else
        {
#if(SIM0 != 0)
         f_sim_MVD(1);
#endif
          MVD_fl[1]=0;
        }
#endif

  AAA = 0x110;
        f_ctrl_v2();
  AAA = 0x111;

       i7060_out[0] = OUT_VAR & 0xff;
//     i7060_out[1] = (OUT_VAR>>4) & 0xf;

       INP_VARi = INP_VAR ^ INP_inv;

#if defined(ICP_7060)


        if(Flag_check==0)
        {
          if(I7060[0].status)  f_7060(0);
          else I7060_fl[0]=0;

//        if(I7060[1].status)  f_7060(1);
//        else I7060_fl[1]=0;
        }
        else
        {
          if(ICP_error[N_7060_1] == 0)
            if(I7060[0].status)  f_7060(0);

//        if(ICP_error[N_7060_2] == 0)
//          if(I7060[1].status)  f_7060(1);
        }

  AAA = 0x114;
#endif

#if defined(RTU_ComSK)
//      if(ComSK[0].status)  f_ComSK(0);
//      else ComSK_fl[0]=0;
//      if(ComSK[1].status)  f_ComSK(1);
//      else ComSK_fl[1]=0;
#endif
/*
#if defined(RTU_Delta)
  AAA = 0x115;
        if(Delta_status)  f_Delta(0);
        else Delta_fl[0]=0;
#endif
*/
  AAA = 0x116;
        f_ctrl_v2();

  AAA = 0x117;
     if(ff_serv_N != NULL) (*ff_serv_N)(); // ����,�����襭�� ���᪠/�ਥ��
//   if(flag_Serv==1)
//       f_pump1();

  AAA = 0x118;

     f_sens();

     if(flag_pool)
     {
  AAA = 0x119;
       f_one_sec();
  AAA = 0x120;
       if(ff_serv != NULL) (*ff_serv)(); // ᪠��஢���� ������ࠫ�,
                                         // ���� ��ࠬ��஢ MVD
  AAA = 0x121;
     }

}
/* ================================================== */
int f_cycle()
{  // �᭮���� 横�

  AAA = 0x2;
     f_cycle_cmn();
  AAA = 0x3;

     if(flag_pool)
     {
  AAA = 0x4;
       if(MMI.status)
       {
  AAA = 0x5;
         if(f_menu_MMI()) return -1;
  AAA = 0x6;
         f_MMI();
  AAA = 0x7;
       }
     }
  AAA = 0x8;

     if(f_host()) return -1;
  AAA = 0x9;
  //   trace();
     return 0;
}
/* ================================================== */
int f_cycle0()
{   // ��� �맮�� f_host()
  AAA = 0x10;
     f_cycle_cmn();
  AAA = 0x11;
     if(flag_pool)
     {
  AAA = 0x12;
       if(MMI.status)
       {
  AAA = 0x13;
         if(f_menu_MMI()) return -1;
  AAA = 0x14;
         f_MMI();
  AAA = 0x15;
       }
     }
   //  trace();
  AAA = 0x16;
     return 0;
}
//-------------------
int f_cycle1()
{   // ��� �맮�� f_MMI()

  AAA = 0x17;
     f_cycle_cmn();

  AAA = 0x18;
     if(f_host()) return -1;

  AAA = 0x19;
   //  trace();
     return 0;
}
/* ================================================== */

/* ---- main ------------------------------------------------------------- */
  int flag_Serv=0; // 0 - ��� � Host PC ��� �⫠���

  int ttt1,ttt2,ttt3,ttt4;
  int itt1,itt2,itt3,itt4;
  long int rltt1,rltt2,rltt3,rltt4;
  long int ltt1,ltt2,ltt3,ltt4;
  int  flag_prn=0;

  unsigned long ttt1_l,ttt2_l,ttt3_l;

  int flag_H=0;
  long int *l_state= (long int *) 0x5000000;
/*
#define AAA (*l_state)
#define BBB (l_state[1])
#define CCC (l_state[2])
#define DDD (l_state[3])
*/
void main(void)
{
  double dtmp1,dtmp2,dtmp3,dtmp4;
  float ftmp,ftmp1,ftmp2,ftmp3,ftmp4;
  int iitmp1,iitmp2,iitmp3;
  int i,j;

  char cmd[40];
//  int checksum=1;
  int key;
  int iRet;
  int year,month,day,hour,min,sec;

  int itmp;
/*
  if(!Is7188xa())
  {
    printf("MMICON.EXE must run on I-7188xa");
    exit (0);
  }
  else
    printf("7188xa is found. Flash size %d\n",itmp);
*/

  InitLib();
  tzset();
  f_ns_count();

  daylight=0;
  timezone=0;

  ComPortHost=4;
/*
    if( ( buf_xyz = (long int *)malloc( (size_t)(dim_xyz_c*sizeof(long int))  )) == NULL )
    {
      exit (0);
    }
*/
//  buf_xyz  = (long int *)AllocateTopMemory( (long int) (dim_xyz_c*sizeof(long int)) );

  *(long int *)&(TimeStamp)=0;
  InstallCom(ComPortHost,115200L,8,0,1);

  for(;TimeStamp < 600;)
  {
    if(!IsCom(ComPortHost)) continue;
    key=ReadCom(ComPortHost);
    if(key == '\b')
    {
      flag_H=1;
      printf("\n\r BS pushed  ");
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */

      break;
    }
    if(key == 0x1b )
    {
      flag_H=2;
      printf("\n\r ESC pushed  ");
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */

      break;
    }
  }

  RestoreCom(4);
/*
  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  RestoreCom(4);
*/
//  X607_Init();
  InitEEPROM();

  f_get_flash_p();

  f_wr_evt(evt_t_off);
  f_wr_evt(evt_t_on);


  flag_echo_host=1;

  f_queue_init();
  f_ee_num_init();
  Init5DigitLed();

  if( flag_H == 1)  goto m_n_ee; // BS
  if( flag_H == 2)  goto m_n_ee; // ESC
  if(f_chk_EEE_CRC()<0)
  {
 m_n_ee:
    InstallCom(ComPortHost,ComBaud[4],8,0,1);
    ShowCom(ComPortHost,8,ComBaud[ComPortHost]);
    printf("CRC Error.Default loaded\n");
    f_icp_errS(EEE_CRC_error);
    sw_mmi=99;
    f_rd_cor();
  }
  else
  {
    f_rd_eee();
    if(val_flch != 0)
      if(val_flch < 10) val_flch=1500;

    if( flag_H != 0) flag_Serv=0;

//  if((flag_Serv==0)||(ComPortHost != ComPortPmp1 ) )
    {
     if(f_get_nb(ComBaud[ComPortHost]) <0 ) ComBaud[ComPortHost]=115200L;
     InstallCom(ComPortHost,ComBaud[ComPortHost],Com_lgth[ComPortHost],Com_parity[ComPortHost],Com_stop[ComPortHost]);
     ShowCom(ComPortHost,Com_lgth[ComPortHost],ComBaud[ComPortHost]);
    }
/*
    if(flag_Serv==1)
    {
     if(f_get_nb(ComBaudPmp1) <0 ) ComBaudPmp1=4800L;
     InstallCom(ComPortPmp1,ComBaudPmp1,Com_lgthPmp1,Com_parityPmp1,Com_stopPmp1);
     ShowCom(ComPortPmp1,Com_lgthPmp1,ComBaudPmp1);
    }
*/
    if(FlagWinSum) init_win_sum(1);
  }

//  baud=ComBaud[4];
//ShowPort(ComPortHost);
//ShowChecksum(checksum);
//ShowBaudrate(ComBaud[ComPortHost]);
/*
    if(EepType==16)
     printf("EEPROM 24LC16 is found (2k bytes)\n");
    else if (EepType==128)
     printf("EEPROM 24WC128 is found (16k bytes)\n");
    else
     printf("Unknown EEPROM.\n");
*/

  f_clr_scr_MMI();

#if defined(ICP_TSD)
  f_clr_TSD(0);
//f_clr_TSD(1);
  f_rev_TSD(0);
//f_rev_TSD(1);
#endif

  if(sw_mmi==0 )
  {

// if((flag_Serv==0)||(ComPortHost != ComPortPmp1 ) )
#if( Test == 0)
     printf("\nFacom Ver.%s",sw_ver);

l_state  = (long int *)AllocateTopMemory( (long int) (dim_xyz_c*sizeof(long int)) );

/*
    printf("\n\r Allocated:\n\r");
    printf("\n\r &l_state = %8lx\n\r",(long int)&l_state[0]);
    printf(" *l_state = %8lx\n\r",*l_state);

    printf(" AA = %8lx\n\r",l_state[0]);
    printf(" BB = %ld\n\r",l_state[1]);
    printf(" CC = %ld\n\r",l_state[2]);
    printf(" DD = %ld\n\r",l_state[3]);
*/
     l_state[l_stt+0]=l_state[0];
     l_state[l_stt+1]=l_state[1];
     l_state[l_stt+2]=l_state[2];
     l_state[l_stt+3]=l_state[3];

#else
     printf("\nFacom.Test version.MVD simulate. Ver. %s",sw_ver);
#endif
   f_prn_begin();
  }
  else f_prn_CRC_error();

  AAA = 0x1;

  SetDisplayPage(ZeroPage);

 /* MMI use I_7188 COM1(RS-232,RS-485),9600,N,8,1 */

  for(i=1;i<4;i++)
  {
//   if(i != ComPortPmp1)
   {
    if(f_get_nb(ComBaud[i]) <0)  ComBaud[i]=9600L;
    InstallCom(i,ComBaud[i],Com_lgth[i],Com_parity[i],Com_stop[i]);
   }
  }

#if defined(ICP_TSD)
   f_init_TSD();
#endif


// if((flag_Serv==0)||(ComPortHost != ComPortPmp1 ) )
 printf("\n\r>");

  one_sec_time=TimeStamp;

  OUT_VAR=OUT8;

  while(1)
  {
     BBB = TimeStamp;
     if(f_cycle()<0) break;
  }
printf("\n\rExit\n\r");

  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
  RestoreCom(4);

//  free( buf_xyz );

//  exit (0);
}

/* ================================================== */
int last_out[5]={-1,-1,-1,-1,-1};
long int scom_tim[5]={1,1,1,1,1};
long int Tm_snd[5]= {0,0,0,0,0};


void ServiceCOM( int ii)
/*
  �㭪�� �ਭ����� �⢥� �� SLAVE ����஫���
  �㭪�� �ਭ����� �⢥� �� ������� ��᫠���� �  COM ii.
  ��᫥ �����襭�� �ਥ�� �������, �ਭ��� ������� ��ࠡ��뢠����
  ���ॡ�⥫��, ��᫠�訬 ������� � Slave
*/
{
int i,Addr_rcv,itmp;
struct COM_rqst *request;
struct s_icp_dev *ICPl_DEV;
int  tmp;

  AAA = 0x200;
  if(  f_timer(time_rcv[ii],scom_tim[ii]) == 0)
  {
  AAA = 0x201;
   if(IsCom(ii)!=0)
   {
  AAA = 0x202;
     while(IsCom(ii)!=0)
     {
  AAA = 0x203;
      tmp= ReadCom(ii);

    if(flag_Deb)
      printf("\n%02X",tmp&0xff);
      time_rcv[ii]= TimeStamp;

  AAA = 0x204;
     }
   }
   return;
  }

  AAA = 0x205;
  if(COM_que[ii].busy_ptr != COM_que[ii].empt_ptr)
  {

  AAA = 0x206;
    if(last_out[ii] != COM_que[ii].empt_ptr)
    {
  AAA = 0x207;
      request=COM_que[ii].request[COM_que[ii].empt_ptr];
      if(request==NULL)
         goto m1;

  AAA = 0x208;
      last_out[ii]=COM_que[ii].empt_ptr;

      // �����⮢�� � ���㦨����� ����� � �뢮� � ����

      ff_gets_com[ii]=request->gets_com;
      ff_answ_com[ii]=request->answ_com;
      ff_answ_flt[ii]=request->answ_flt;
      ToutAns[ii]=request->timeout;
      time_snd[ii]= TimeStamp;
      Tm_snd[ii]= TimeStamp;

      ICPl_DEV=request->ICP_dd;
      ICPl_DEV->time_stamp_snd=TimeStamp-request->time_stamp;

  AAA = 0x209;
      // �뢮� � ����
//  ltt1=TimeStamp;
//  tim1();

#if defined(I7188D)
  AAA = 0x210;
  Set485DirToTransmit(ii); //qqq
#endif

  AAA = 0x211;
      ToComBufn(ii,request->Cmd,request->cmd_lgth);

  AAA = 0x212;
#if defined(I7188D)
  AAA = 0x213;
  WaitTransmitOver(ii);
  Set485DirToReceive(ii);
#endif

  AAA = 0x214;
//  tim2();
//  ltt2=TimeStamp;

//   itt1=ttt2-ttt1-10;  // 10 ᫥��� ����� - �� �६� ���������
//   if(itt1 < 0) itt1+=10000;
//   rltt1=ltt2-ltt1;

//   if(flag_prn)
//   {
//     flag_prn=0;
//     printf("\n %d bytes send, time=%ld ms, %.1f mks",request->cmd_lgth,rltt1,(float)(itt1)/10.);
//   }
      request->status=2;
    }
  }

  AAA = 0x215;
m1:
  AAA = 0x216;
  if( (*ff_gets_com[ii])(ii) )
 /* ���� �⢥� �� �������. �����⥫� �� �㭪�� �����
    ��⠭�������� �㭪��, ���樨஢���� ��।��� �������
 */
  {
  AAA = 0x217;
      time_rcv[ii]= TimeStamp;
      request=COM_que[ii].request[COM_que[ii].empt_ptr];
      ICPl_DEV=request->ICP_dd;
      ICPl_DEV->time_stamp_rcv=TimeStamp - request->time_stamp;

   /* � cb_COM[ii][] ��室���� ������� ������  n_bcom[ii]  */

   /* ��ࠡ�⪠ �������. �����⥫� �� �㭪�� ��ࠡ�⪨ ��⠭��������
      �㭪��, ���樨����� ��।���
   */

  AAA = 0x218;
     (*ff_answ_com[ii])(ii);

  AAA = 0x219;
     ff_gets_com[ii]=f_empty_gets;
     ff_answ_com[ii]=f_empty;
     n_bcom[ii]=0;

  AAA = 0x220;
  }
}
/* ================================================== */
int f_timer(unsigned long int time_stamp,unsigned long int delay)
{
// �᫨ �६� � ������ ����� �६������ �⠬�� �ॢ�蠥�
 // delay �� - �����頥� 1, ���� 0.
// if((TimeStamp-time_stamp) > delay) return 1;
// else return 0;
 if((TimeStamp-time_stamp - delay) & 0x80000000 ) return 0;
 else return 1;
}
/* ================================================== */

unsigned long int time_snd[5]={0,0,0,0,0};
unsigned long int time_rcv[5]={0,0,0,0,0};

/* ================================================== */

 char cb_COM[5][n_bufcom];
 int ghj=0;
 int n_bcom[5]={0,0,0,0,0};

void (*ff_serv)() = NULL;

int  (*ff_gets_com[5])(int ii) = {f_empty_gets,f_empty_gets,f_empty_gets,f_empty_gets,f_empty_gets};
void (*ff_answ_com[5])(int ii) = {f_empty,f_empty,f_empty,f_empty,f_empty};
void (*ff_answ_flt[5])(int ii) = {f_empty,f_empty,f_empty,f_empty,f_empty};
int i_empty;
void f_empty(int ii)
{
 i_empty=ii;
}

/*================================================================*/

float ftmp_naMMI[4];
struct dis_set_MMI ds_list1[]=
{
//-----1-----
  list1_dsr,
  156,
  &ftmp_naMMI[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----2-----
  list1_dsr,
  157,
  &analog_offset[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----3-----
  list1_dsr,
  129,
  &ftmp_naMMI[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----4-----
  list1_dsr,
  130,
  &analog_offset[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----5-----
  list1_dsr,
  131,
  &ftmp_naMMI[2],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----6-----
  list1_dsr,
  132,
  &analog_offset[2],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----7-----
  list1_dsr,
  162,           // "U �।�०�����,V"
  &v_lvl1,
  -5,
  30,
  T_FLOAT,
/*-----8----------*/
  list1_dsr,
  163,           // "U �⪫�祭�� ,V",
  &v_lvl2,
  -5,
  30,
  T_FLOAT,
/*-----9----------*/
  list1_dsr,
  164,           // "U ���.�� ��,V"
  &volt_dc_cmp,
  -5,
  30,
  T_FLOAT,
/*----10----------*/
  list1_dsr,
  165,           // T �� ���.���᪠,��
  &Tim_volt,
  0,
  BIG_P,
  T_INT,
//-----11---------
  list1_dsr,
  166,            // T �� �⪫�祭��,��"
  &Tim_volt_mes,
  0,
  BIG_P,
  T_INT_L,
//----12----------
  list1_dsr,
  42,                 // "dP ��� +��ॡ.,���"
  &PressLvl_on0,      // 0.11     0.06
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----13----------*/
  list1_dsr,
  43,                 //   "dP ��� -��ॡ.,���"
  &PressLvl_off0,
  -BIG_P,             // 0.05     0.00
  BIG_P,
  T_FLOAT,
/*----14----------*/
  list1_dsr,
  44,                 // "+� T ��� ��� P�� ",
  &Temp_kor,           // 8.5     0
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----15-----
  list1_dsr,
  11,             // "������ ��㡪� MVD,mm"
  &PressLvl_on1,  //       8      15
  0.01,
  BIG_P,
  T_FLOAT,
//----16----------
  list1_dsr,
  160,             // "�����.���஦�.T1,��",
  &Tim_stg_ctrl,
  0,
  BIG_P,
  T_INT_L,
//----17----------
  list1_dsr,
  161,              // "�����.���஦�.T2,��"
  &Tim_stg_ctrl0,
  0,
  BIG_P,
  T_INT_L,
//-----18---------
  list1_dsr,
  98,
  &CL_val[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----19----
  list1_dsr,
  99,
  &CL_val[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----20----
  list1_dsr,
  13,
  &CL_valR[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----21----
  list1_dsr,
  14,
  &CL_valR[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----22----
  list1_dsr,
 100,
  &CL_T1,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----23----
  list1_dsr,
 101,
  &CL_T2,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----24----
  list1_dsr,
   25,
  &Tim_prb_plus,
  0.,
  BIGL_P,
  T_INT_L,
//-----25----
  list1_dsr,
   26,
  &Tim_prb_minus,
  0.,
  BIGL_P,
  T_INT_L,
//-----26----
  list1_dsr,
   27,
  &Tim_antd,
  0.,
  BIGL_P,
  T_INT_L,
//-----27----
  list1_dsr,
 102,
  &CL_T3,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----28----
  list1_dsr,
 103,
  &CL_T4,
  -BIG_P,
  BIG_P,
  T_INT_L,
//-----29----
  list1_dsr,
  106,
  &t_mvd_cor,
  0,
  BIG_P,
  T_INT_L,
//-----30----
  list1_dsr,
  104,
  &fct_offs,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----31----
  list1_dsr,
  105,
  &fct_offs_r,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//-----32----
  list1_dsr,
   28,
  &cl1_delayR_off,
  0.,
  BIGL_P,
  T_INT_L,
//-----33----
  list1_dsr,
  153,
  &cl2_delayR_off,
  0.,
  BIGL_P,
  T_INT_L,
//-----34----
  list1_dsr,
  154,
  &Out3_delayR_off,
  0,
  BIG_P,
  T_INT_L,
//-----35----
  list1_dsr,
  108,
  &tim_MVD_delay,
  -BIG_P,
  BIG_P,
  T_INT_L,
//-----36----
  list1_dsr,
  158,           //M. ��।.��९ BIG
  &val_flch,
  0,
  BIG_P,
  T_FLOAT,
//------37---
  list1_dsr,
  80,               // ������ ��� N ���.
  &num_out1,
  0,
  16,
  T_INT,
//------38---
  list1_dsr,
  81,               // ������ ��� N ���.
  &num_out2,
  0,
  16,
  T_INT,
//-----39----
  list1_dsr,
  139,               // ���.���� N ���.
  &num_out3,
  0,
  16,
  T_INT,
//-----40----
  list1_dsr,
  140,              // ������ ���.䠧� ��,N ���.
  &num_out4,
  0,
  16,
  T_INT,
//-----41----
  list1_dsr,
  16,             // ��⠭�� N ���.
  &num_out8,
  0,
  16,
  T_INT,
//-----42----
  list1_dsr,
  143,               // ���਩��� ��. N ��.
  &num_in1,
  0,
  8,
  T_INT,
//-----43----
  list1_dsr,
  144,               // ���਩��� ��.䫠� �����ᨨ
  &mski_inp1,
  0,
  8,
  T_INT,
//-----44----
  list1_dsr,
  0,
  &MMI.status,
  0.,
  1.,
  T_INT,
//-----45----
  list1_dsr,
  51,
  &MVD[0].status,
  0.,
  1.,
  T_INT,
//-----46----
  list1_dsr,
  52,
  &MVD[1].status,
  0.,
  1.,
  T_INT,
//-----47----
  list1_dsr,
  6,
  &I7017C[0].status,
  0.,
  1.,
  T_INT,
//-----48----
  list1_dsr,
  18,
  &I7060[0].status,
  0.,
  1.,
  T_INT,
//-----49----
  list1_dsr,
  145,               // ������ ���. N ��.
  &num_in4,
  0,
  8,
  T_INT,
//-----50----
  list1_dsr,
  146,               // ������ ���. 䫠� �����ᨨ
  &mski_inp4,
  0,
  8,
  T_INT,
//-----51----
  list1_dsr, // ���室 ��⭥� �६�
  89,
  &FlagWinSum,
  0,
  1,
  T_INT,
//-----52----
  NULL,
  0,
  NULL,
  0,
  1,
  T_INT,
//-----------
};
/*-----------------------------------------*/
/*=============
//-----------
  list1_dsr,
   25,
  &time_com_cl,
  0.,
  BIGL_P,
  T_INT_L,
//-----50----
  list1_dsr,
   26,
  &Tim_prb_plus,
  0.,
  BIGL_P,
  T_INT_L,
//-----51----
  list1_dsr,
   26,
  &Tim_prb_minus,
  0.,
  BIGL_P,
  T_INT_L,
//-----52----
  list1_dsr,
   26,
  &Tim_antd,
  0.,
  BIGL_P,
  T_INT_L,
//-----53----
  list1_dsr,
   27,
  &time_cnt_cl_off,
  0.,
  BIGL_P,
  T_INT_L,
//-----54----
  list1_dsr,
  33,
  &ComBaud[4],
  1200,
  115200,
  T_INT_L,
//-----------
  list1_dsr,
  147,
  &time_LIQ_dlv,
  30,
  BIGL_P,
  T_INT_L,
//-----2-----
  list1_dsr,
  148,
  &time_EQ_dlv,
  5.,
  BIGL_P,
  T_INT_L,
//-----3-----
  list1_dsr,
  149,
  &time_LIQ_rcv,
  30.,
  BIGL_P,
  T_INT_L,
//-----4-----
  list1_dsr,
  150,
  &time_EQ_rcv,
  5.,
  BIGL_P,
  T_INT_L,
  list1_dsr,
  159,            // "����.�� ���뢥,�/�",
  &Fl_perm,
  0,
  BIG_P,
  T_FLOAT,
//----11-----
//-----------
  list1_dsr,
  45,
  &num_clp_sv,
  1,
  3,
  T_INT,
//-----------
  list1_dsr,
  9,
  &ModeReduce ,
  0,
  3,
  T_INT,
//-----------
  list1_dsr,
   22,
  &k_Den0_Off,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
   23,
  &k_Den0_On,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  158,           //M. ��।.��९ BIG
  &val_flch,
  0,
  BIG_P,
  T_FLOAT,
//-----------
  list1_dsr,
  137,           // M.��।.��९ LTL
  &val_flch2,
  0,
  BIG_P,
  T_FLOAT,
//-----------
//-----------
  list1_dsr,
  138,           // �६� ��९���,⨪
  &time_flch,
  0,
  max_fl_ch_m1,
  T_INT,
//-----------
//-----------
  list1_dsr, // ��� ��.�롮ન
  88,
  &s_mode,
  1,
  4,
  T_INT,
//-----------
  list1_dsr,
  80,               // ������ ��� N ���.
  &num_out7,
  0,
  9,
  T_INT,
//-----------
  list1_dsr,
  141,               // ���.䠧� ����.N���.
  &num_out5,
  0,
  16,
  T_INT,
//-----------
  list1_dsr,
  142,               // ���.䠧� ����.N���.
  &num_out6,
  0,
  16,
  T_INT,

  list1_dsr,
  24,
  &I7060[1].status,
  0.,
  1.,
  T_INT,
//-----------
//-----------
  list1_dsr,
  37,
  &WDOG[0].status,
  0.,
  1.,
  T_INT,
//-----------
*/
/*-----------------------------------------*/
/*-----------------------------------------*/
int max_list1=(sizeof(ds_list1)/sizeof(ds_list1[0])) -1;
/*-----------------------------------------*/
long int time1=0,dd_time,dd_max=-1,dd_min=10000000;
void f_time_dd()
{
long int ltmp;
ltmp=TimeStamp;
dd_time=ltmp-time1;
time1=ltmp;
if(dd_time > dd_max) dd_max=dd_time;
else if(dd_time < dd_min) dd_min=dd_time;
}
//---
void f_print_dd()
{
 printf(" %ld , min= %ld, max=%ld",dd_time,dd_min,dd_max);
 dd_min=10000000;
 dd_max=-1;
}
/*-----------------------------------------*/
unsigned long int one_sec_time=0;

void f_one_sec()
{
union  { float f; char c[4]; } o;
  int win_sum;
  TIME_DATE t;

 if(flag_pool)
 {
  if( f_timer(one_sec_time,1000L) == 0)  return;

  one_sec_time+=1000;

  GetTimeDate(&t);


  if(FlagWinSum)
   {
      if((t.sec <= 2)&& (t.minute==0))
        if((t.day >= 25)&&(t.weekday==0))
        {
          if( (t.month==3)&& (t.hour==2) )
          // � 2 �� ,�� ��, mart,�+=1
          {  /*���室 �� ��⭥� �६� */

           win_sum = ReadNVRAM( nr_win_sum )  ;
           if(win_sum==0)
           { // �� �� ��ॢ�����
            f_wr_evt(evt_none);
            t.hour++;
            win_sum=1;  // 1 - ���
            SetTime((int)t.hour,(int)t.minute,(int)t.sec);

            WriteNVRAM((int)nr_win_sum,(int)win_sum );
            f_wr_evt(evt_ch_sum);
           }
          }
          else if((t.month==10)&& (t.hour==3) )
           // � 3 �� ,�� ��, oct,�-=1
          { //���室 �� ������ �६�

            win_sum  = ReadNVRAM( nr_win_sum )  ;
            if(win_sum)
            { // �� �� ��ॢ�����
              f_wr_evt(evt_none);
              t.hour--;
              win_sum=0; // ������
              SetTime((int)t.hour,(int)t.minute,(int)t.sec);
              WriteNVRAM((int)nr_win_sum,(int)win_sum );
              f_wr_evt(evt_ch_win);
            }
          }
        }
   }
    WriteNVRAM((int)nr_year   ,(int)(t.year-2000));
    WriteNVRAM((int)nr_month  ,(int)t.month  );
    WriteNVRAM((int)nr_day    ,(int)t.day    );
    WriteNVRAM((int)nr_hour   ,(int)t.hour   );
    WriteNVRAM((int)nr_min    ,(int)t.minute );
    WriteNVRAM((int)nr_sec    ,(int)t.sec    );
    o.f=  s_MVD[0].VolI;
    WriteNVRAM((int) nr_v0   ,(int)o.c[0] );
    WriteNVRAM((int) nr_v1   ,(int)o.c[1] );
    WriteNVRAM((int) nr_v2   ,(int)o.c[2] );
    WriteNVRAM((int) nr_v3   ,(int)o.c[3] );
    o.f=  s_MVD[0].MassI + s_MVD[1].MassI;
    WriteNVRAM((int) nr_m0   ,(int)o.c[0] );
    WriteNVRAM((int) nr_m1   ,(int)o.c[1] );
    WriteNVRAM((int) nr_m2   ,(int)o.c[2] );
    WriteNVRAM((int) nr_m3   ,(int)o.c[3] );
 }
}

/*-----------------------------------------*/
int init_win_sum(int cor)
{
//  �����頥� �ਧ��� ������� ��� ��⭥�� �६���
//  ��� ⥪�饣� ������: 1 - ��⭥� �६� , 0 - ������ �६�
//  �᫨ cor != 0 ���४���� ⥪�饥 �६� �� ���室� ���./���.

  int year,month,day,hour,min,sec;
  int win_sum;
  time_t ltime1,ltime2;
  int prev_ws;

  struct tm *tdat;

 int i,i1;
 TIME_DATE t;
struct arch_str_t tim_0;

 f_prepare_t(&tim_0);
 GetTimeDate(&t);
/*
 tim_0.year  = t.year-2000;
 tim_0.month = t.month;
 tim_0.day   = t.day;
 tim_0.hour  = t.hour;
 tim_0.min   = t.minute;
 tim_0.sec   = t.sec;
*/

// printf("\n\r %02d.%02d.%02d  " ,tim_0.day,tim_0.month,tim_0.year);
// printf("%02d.%02d.%02d -- ",(int)tim_0.hour,(int)tim_0.min,(int)tim_0.sec);

 ltime1=f_get_time_t(&tim_0); // ⥪�饥 �६�

  switch((int)tim_0.month)
  {
   case 11:
   case 12:
   case 1:
   case 2: // ����
         win_sum=0;
         break;
   case 4:
   case 5:
   case 6:
   case 7:
   case 8:
   case 9: // ���
         win_sum=1;
         break;
   case 3:  // ����
        if(t.day>= 10) i=t.day-t.weekday;
        else i=t.day+7-t.weekday;
        for(;i<=31;i+=7)
         {
          i1=i;
         }
//        printf("\n\r==Last Sunday - %d Mart ",i1);
      // i1 - �᫮ ��᫥����� ����ᥭ�� ����
         tim_0.day=i1;
         tim_0.hour=2;
         tim_0.min=0;
         tim_0.sec=0;

    ltime2=f_get_time_t(&tim_0); // �६� �

    if(ltime1<ltime2)
         win_sum=0;
    else
         win_sum=1;
    break;
   case 10:  // ������
        if(t.day>= 10) i=t.day-t.weekday;
        else i=t.day+7-t.weekday;
        for(;i<=31;i+=7)
         {
          i1=i;
         }
      // i1 - �᫮ ��᫥����� ����ᥭ�� ������
         tim_0.day=i1;
         tim_0.hour=3;
         tim_0.min=0;
         tim_0.sec=0;
 //       printf("\n\r==Last Sunday - %d Oct ",i1);

// printf("\n\r %02d.%02d.%02d  " ,tim_0.day,tim_0.month,tim_0.year);
// printf("%02d.%02d.%02d -- ",(int)tim_0.hour,(int)tim_0.min,(int)tim_0.sec);

    ltime2=f_get_time_t(&tim_0); // �६� �
//    printf("\n\rltime1=%ld,ltime2=%ld",ltime1,ltime2);

    if( (ltime2>ltime1)&& ((ltime2 - ltime1)< 3600L))
    {
      win_sum=ReadNVRAM(nr_win_sum);
      break;
    }
    if(ltime1<ltime2)
    {
         win_sum=1;
    }
    else
    {
         win_sum=0;
    }
    break;
  }

  if(cor)
  {
    prev_ws=ReadNVRAM(nr_win_sum);
    if((prev_ws==0)&&(win_sum!=0))
    {// ���室 �� ��⭥� �६�
      ltime1+=3600L;

      tdat = localtime( &ltime1 );
      year   = tdat->tm_year+1900;
      month  = tdat->tm_mon+1;
      day    = tdat->tm_mday ;
      hour   = tdat->tm_hour;
      min    = tdat->tm_min;
      sec    = tdat->tm_sec;

      SetTime(hour, min,sec);
      SetDate(year, month, day);
      f_wr_evt(evt_ch_sum);
    }
    else if((prev_ws!=0)&&(win_sum==0))
    {// ���室 �� ������ �६�
      ltime1-=3600L;

      f_wr_evt(evt_ch_win);

      tdat = localtime( &ltime1 );
      year   = tdat->tm_year+1900;
      month  = tdat->tm_mon+1;
      day    = tdat->tm_mday ;
      hour   = tdat->tm_hour;
      min    = tdat->tm_min;
      sec    = tdat->tm_sec;
      SetTime(hour,min,sec);
      SetDate( year, month, day);
    }
  }
  WriteNVRAM((int)nr_win_sum,(int)win_sum );
  return win_sum;
}
/*-----------------------------------------*/
int num_clp_sv=1; // 1...3 ����� ������� ��࠭塞��� � NVRAM
/*-----------------------------------------*/
float cl_val_c=-100000;
float cl_t_c=-100000;
void f_wr_cor()
{
float ftmp;
union  { float f; char c[4]; } o;

    ftmp=CL_val[1]+CL_valR[1];

//  if( (cl_val_c != CL_val[1]) || (cl_t_c != CL_valR[1] ) )
    {
       o.f= CL_val[1] ;
       cl_val_c=o.f;
       WriteNVRAM((int) nr_dv0   ,(int)o.c[0] );
       WriteNVRAM((int) nr_dv1   ,(int)o.c[1] );
       WriteNVRAM((int) nr_dv2   ,(int)o.c[2] );
       WriteNVRAM((int) nr_dv3   ,(int)o.c[3] );

       o.f= CL_valR[1] ;
       cl_t_c=o.f;
       WriteNVRAM((int) nr_dv0_r ,(int)o.c[0] );
       WriteNVRAM((int) nr_dv1_r ,(int)o.c[1] );
       WriteNVRAM((int) nr_dv2_r ,(int)o.c[2] );
       WriteNVRAM((int) nr_dv3_r ,(int)o.c[3] );

       o.f= ftmp;
       WriteNVRAM((int) nr_sm0   ,(int)o.c[0] );
       WriteNVRAM((int) nr_sm1   ,(int)o.c[1] );
       WriteNVRAM((int) nr_sm2   ,(int)o.c[2] );
       WriteNVRAM((int) nr_sm3   ,(int)o.c[3] );
    }
}
/*-----------------------------------------*/
void f_rd_cor()
{
union  { float f; char c[4]; } o;
float ftmp,ftmp1,ftmp2,ftmp3;

 o.c[0]= ReadNVRAM( nr_dv0 );
 o.c[1]= ReadNVRAM( nr_dv1 );
 o.c[2]= ReadNVRAM( nr_dv2 );
 o.c[3]= ReadNVRAM( nr_dv3 );
 ftmp = o.f;
 o.c[0]= ReadNVRAM( nr_dv0_r );
 o.c[1]= ReadNVRAM( nr_dv1_r );
 o.c[2]= ReadNVRAM( nr_dv2_r );
 o.c[3]= ReadNVRAM( nr_dv3_r );
 ftmp1 = o.f;
 ftmp3=ftmp+ftmp1;
 o.c[0]= ReadNVRAM( nr_sm0 );
 o.c[1]= ReadNVRAM( nr_sm1 );
 o.c[2]= ReadNVRAM( nr_sm2 );
 o.c[3]= ReadNVRAM( nr_sm3 );
 ftmp2 = o.f;
 if(ftmp2== ftmp3)
 {
   CL_val[1]=ftmp;
   CL_valR[1]=ftmp1;
 }
}
/*-----------------------------------------*/
/*-----------------------------------------*/

#include "7017c.c"
#include "i7060.c"
//#include "sk.c"
#include "delta.c"
#include "MVD.c"
#include "avt_ctrw.c"
#include "tsd.c"
#include "icp.c"
#include "queue.c"

//25.05.2020 YN --\\//--
//was: #include "mmi.c" now:
#if defined(MMI_ICP)
#include "mmi.c"
#endif
#if defined(MMI_NEW)
#include "MMI_new.c"
#endif
//25.05.2020 YN --//\\--
/*-----------------------------------------*/