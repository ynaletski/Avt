
#define n_mmi_str 7 // ���������� ����� �� ������� MMI
#define n_mmi_str_1 (n_mmi_str-1)
#define n_mmi_str_2 (n_mmi_str-2)
#define n_mmi_str_3 (n_mmi_str-3)
#define n_mmi_str_4 (n_mmi_str-4)
//21.05.2020 YN -----\\//-----
long int tm_md=0;
//21.05.2020 YN -----//\\-----
//
//  ���� �������� ���������� ������ � DOS ��������� ��������.
//  ��� ����������� �� ������� MMI ���������� �������������� �
//  ��������� Windows (����������� �������� dos_win.exe � .bat)
//
float MassStamp;
float VolStamp;
float MassStamp2;
float VolStamp2;

int Ret_cod=0;
float vBIG_P=BIG_P;

float VolT=0;
float MassT=0;

int EmptyPage=0;
int i_nn_mvd=0;
char kran_ch[]="ESC �������, 1..4 ���.";
char kran1[]="ESC ������� , F1-�����";
char kran[]="ESC �������";

long int fl_zeroing=0;
#define Time_zeroing (50000)
long int zero_time;

char s_empty[]="                              ";
int PageD=0;
int flg_ch=0;
int Flag_f_corr=0,flag_mass=0,pass_ret=0;
float k_v_flow=1,k_m_flow=1;
float k_mv_tmp;

char str_empty[]="                              ";
char str_ESC[]="ESC  �������";
char str_verify[]="    ������� �����������   )   ";
//char str_def[]=" ------- ";


void f_d_ESC()
{
  MmiGotoxy(0,6); MmiPuts(str_ESC);
}
void f_prn_comps();

void  f_prn_begin()
{
  if(CRC_err) f_prn_CRC_error();
  else if(FL_err) f_prn_error();
  else
  {
    f_clr_scr_MMI();
            //  MmiPrintf("                              ");
  MmiGotoxy(1,1);  MmiPrintf("  ������� ����� ������ �");
  MmiGotoxy(1,2);  MmiPrintf("������� ��� �� ������������");
  MmiGotoxy(23,6);  MmiPrintf("9-����.");

    if(PageD==0)
    {
     MmiGotoxy(0,3) ; MmiPrintf("�����       :");
     MmiGotoxy(0,4) ; MmiPrintf("���������   :");
     MmiGotoxy(0,5) ; MmiPrintf("��������    :");
    }
    else if(PageD==1)
    {
     MmiGotoxy(0,3) ; MmiPrintf("��������    :");
     MmiGotoxy(0,4) ; MmiPrintf("����.���    :");
     MmiGotoxy(0,5) ; MmiPrintf("����.��     :");
    }
    else  if(PageD==2)
    {
     MmiGotoxy(0,3) ; MmiPrintf("����� MVD1  :");
     MmiGotoxy(0,4) ; MmiPrintf("����� MVD2  :");
     MmiGotoxy(0,5) ; MmiPrintf("�����       :");

    }
  }
}
//-------------------------------------
void  f_dsp_ncnt()
{
  MmiGotoxy(1,1); MmiPrintf(" ������ ��  %7.1f  ��/�  ",s_MVD[0].FlowV*3.6*s_MVD[0].Dens);
  MmiGotoxy(1,2); MmiPrintf(" ���������  %8.2f ��/�3",s_MVD[0].Dens);
  MmiGotoxy(1,3); MmiPrintf(" ��������   %8.2f ���", s_MVD[0].Press);
  MmiGotoxy(1,4); MmiPrintf(" �����������  %6.2f �  ", s_MVD[0].Temp);
  MmiGotoxy(1,5); MmiPrintf(" ����.���   %8.2f V  ", s_MVD[0].Volt_A);
}
//-------------------------------------
void  f_dsp_H1()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   ������ ���");
         MmiGotoxy(17,6); MmiPuts(str_ESC);

  MmiGotoxy(0,1); MmiPrintf("���������:�-����,�-������ ����");
  MmiGotoxy(1,2); MmiPrintf(" �������� �����: ");
  MmiGotoxy(1,3); MmiPrintf(" �, �, �, � , �");
  MmiGotoxy(1,4); MmiPrintf(" �������� �����: ");
  MmiGotoxy(1,5); MmiPrintf(" �, �, �  ");
}
//-------------------------------------
void  f_dsp_H2()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0)   ;    MmiPuts("   �����  ���");
         MmiGotoxy(17,6); MmiPuts(str_ESC);

  MmiGotoxy(0,1); MmiPrintf("���������:�-������ ����,�-����");
  MmiGotoxy(1,2); MmiPrintf(" �������� �����: ");
  MmiGotoxy(1,3); MmiPrintf("  �, �, �, �  ");
  MmiGotoxy(1,4); MmiPrintf(" �������� �����:");
  MmiGotoxy(1,5); MmiPrintf("  �, �, �, �  ");

}
//-------------------------------------
void  f_dsp_H3()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

         MmiGotoxy(0,0); MmiPuts("�����/������ ��� ��� �����");
         MmiGotoxy(17,6); MmiPuts(str_ESC);


  MmiGotoxy(0,1); MmiPrintf("���������:�-����,�-������ ����");
  MmiGotoxy(1,2); MmiPrintf(" �������� �����: ");
  MmiGotoxy(1,3); MmiPrintf("  �, �, �    (�-����.����)");
  MmiGotoxy(1,4); MmiPrintf(" �������� �����:");
  MmiGotoxy(1,5); MmiPrintf("  �, �, �, � (�-����.����)");

}
//-------------------------------------
int un_mmi1=1;
int un_mmi2=2;
int un_mmi3=3;
char *list_un_mmi[]={
"",
" �����,�   " ,  //1
"�����,���  " ,  //2
"����,���/� " ,  //3
"�����,��   " ,  //4
"�����,���  " ,  //5
"����,���/��" ,  //6
};
//-------------------------------------
int CRC_err=0;
//-------------------------------------
void f_prn_CRC_error()
{
 MmiGotoxy(0,2);   MmiPrintf("!������ ����������� �����   ");
 MmiGotoxy(0,3);   MmiPrintf("!��������� ��������         ");
 MmiGotoxy(0,4);   MmiPrintf("!���������� �������������   ");
 MmiGotoxy(0,5);   MmiPuts(s_empty);
 CRC_err=1;
}
//-------------------------------------
void f_prn_proc()
{
//float ftmp;
          if(PageD==0)
          {
      //      MmiGotoxy(0,4);  MmiPuts(" ���������     |   ������      ");
      //      MmiGotoxy(0,5);MmiPrintf("%8.2f ��/�3 | %8.1f ��/�  ",s_MVD[0].Dens,s_MVD[0].FlowM);
              MmiGotoxy(0,4);  MmiPrintf("�:%5.0f��/�|%5.1f��/�3|%5.1f C",s_MVD[0].FlowM,s_MVD[0].Dens,s_MVD[0].Temp);
              MmiGotoxy(0,5);  MmiPrintf("�:%5.0f��/�|%5.1f��/�3|%5.1f C",s_MVD[1].FlowM,s_MVD[1].Dens,s_MVD[1].Temp);
          }
          else if(PageD==1)
          {

//          MmiGotoxy(0,4);    MmiPuts(" P1, ��� | P��,��� |  T,����.C");
//          MmiGotoxy(0,5);    MmiPrintf("%8.4f |%8.4f |%8.2f   ",s_MVD[0].Press ,s_MVD[0].PressG,s_MVD[0].Temp);

           MmiGotoxy(0,4);
               MmiPuts(" P1, ��� | P��,��� |  T,����.C");
           MmiGotoxy(0,5);
             MmiPrintf("%8.4f |%8.4f |%8.2f   ",s_MVD[0].Press,s_MVD[0].PressG,s_MVD[0].Temp);
          }
          else if(PageD==3)
          {

     MmiGotoxy(0,4); MmiPuts("��.���:");
     if( OUT_VAR & OUT2  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy( 9,4); MmiPuts("��.���:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

/*
     MmiGotoxy(18,4); MmiPuts("��.���:");
     if( OUT_VAR & CLP0  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");
*/

     MmiGotoxy(27,4); MmiPuts("�:");
     if( OUT_VAR & OUT3  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(18,4); MmiPuts("��� ��:");
     if( OUT_VAR & GAS1  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(0,5); MmiPrintf("���=%5.2fV | ��=%5.2fV",s_MVD[0].Volt_A,s_MVD[0].Volt_DC);

     MmiGotoxy(23,5); MmiPuts("    �:");
     if( OUT_VAR & OUT8  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");
/*
     MmiGotoxy(9,5); MmiPuts("��� ��:");
     if( OUT_VAR & GAS2  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(18,5); MmiPuts("��� ��:");
     if( OUT_VAR & OUT6  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");
 */
          }
}
//-------------------------------------
void f_prn_MassSt_dlv()
{
  MmiGotoxy(2,1);  MmiPrintf("����� �������� %8.2f ��  ",-(s_MVD[0].MassI+s_MVD[1].MassI-MassStamp-MassStamp2));
}
//-------------------------------------
void f_prn_MassSt_rcv()
{
   MmiGotoxy(0,1);
   if(Flag_check == 0)
    MmiPrintf("  ����� ������� %8.2f ��  ",s_MVD[0].MassI+s_MVD[1].MassI-MassStamp-MassStamp2);
   else
    {
      MmiPuts(str_verify);
    }
}

//-------------------------------------
void f_prn_error()
{
   f_clr_scr_MMI();

#if( Test == 0)
   if(flag_mvd_ton[0] | flag_mvd_ton[1])
   {
  MmiGotoxy(2,1);  MmiPrintf(" ������� ����� ������ �");
  MmiGotoxy(1,2);  MmiPrintf("������� ��� �� ������������");

  MmiGotoxy(0,3);  MmiPuts(s_empty);
  MmiGotoxy(0,4);  MmiPrintf(" !������������� ������������");
  MmiGotoxy(0,5);  MmiPuts(s_empty);
   }
   else
#endif
   {
    MmiGotoxy(0,1);   MmiPrintf("                        ");
    MmiGotoxy(0,2);   MmiPrintf("!������ ���������������� ");
    MmiGotoxy(0,3);   MmiPrintf("Sht-F1 ����������� ������");
    MmiGotoxy(0,4);   MmiPrintf("Sht-ESC ������� ������   ");
   }
}
//-------------------------------------
void  f_disp_error()
{ // ������������� ������

 struct s_icp_dev *ICPl_DEV;
int i,i1,i2;
int itmp;
   i1=0;
   i2=0;
 for(i=0;i<=icp_lst_max;i++)
   if(ICP_error[i])
   {
    i2++;
    ICPl_DEV=ICP_dd[i];
  if(i != icp_lst_max)
  {
 MmiGotoxy(0,i1++);   MmiPrintf("������ � �������� %9s:",ICPl_DEV->name );
  }
  else
  {
 MmiGotoxy(0,i1++);   MmiPrintf("������ ������� ���:           ");
  }
    if(i1 >= n_mmi_str) return;
    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WR_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ � ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ Watch Dog");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Drive_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ � ����������,%02X", (itmp>>8) & 0xff);
    if(i1 >= n_mmi_str) return;
    }

  }
  else //(i == icp_lst_max)
  {
    if(itmp & EEE_CRC_error)
    {
MmiGotoxy(0,i1++); MmiPrintf("������ CRC EEPROM ����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_erase_error )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ �������� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_wr_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ������ �� FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_gas_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("����-� �� �������� ���");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Z_mass_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("����-� �� ������� M/V");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_F_dat_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ������.������ ��� �������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & exm_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("������� ������ �����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & exp_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("������� ������ �����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Gun_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("����� �������� ��� ������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_pmlan )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ����� � �����");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_flow )
    {
MmiGotoxy(0,i1++); MmiPrintf("����� �����������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & ES_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ES ��� �������/������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & UZA_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("��� ��� ��� �������/������");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & MVD_cfg )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ����.������-�� ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & MVD_com )
    {
MmiGotoxy(0,i1++); MmiPrintf("������ ���.����������� ");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & MotNotStop )==MotNotStop)
    {
MmiGotoxy(0,i1++); MmiPrintf("���� ������ ��� ����.");
    if(i1 >= n_mmi_str) return;
    }
//    if((itmp & DLT_off)== DLT_off )
//    {
//MmiGotoxy(0,i1++); MmiPrintf("����� ����. ��� �������");
//    if(i1 >= n_mmi_str) return;
//    }
    if((itmp & VLT_off)== VLT_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("   ��� ��������� <%5.2f V",v_lvl2);
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & Flow_big)== Flow_big )
    {
MmiGotoxy(0,i1++); MmiPrintf("����� ������.����.>���.");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & N380_off)== N380_off )
    {
MmiGotoxy(0,i1++); MmiPrintf(" !��� ������� 380V ");
    if(i1 >= n_mmi_str) return;
    }
  }
   }
   if(i2==0)
   {
    MmiGotoxy(5,2); MmiPrintf("������ ���");
    MmiGotoxy(2,4); MmiPrintf("Enter - ����������");
   }
}
//-------------------------------------
void f_drv_list_MMI(int *nn)
{ // �������� ������ ��������� ���������
int i,i1,i2;
char str[31];
  struct s_icp_dev *ICPl_DEV;

   f_clr_scr_MMI();

  //  if( (*nn+n_mmi_str_3) > icp_lst_max) i=icp_lst_max-n_mmi_str_3;
  //  else
    i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < icp_lst_max) i1=i+n_mmi_str_3;
    else i1=icp_lst_max;

    *nn=i;
    MmiGotoxy(0,0); MmiPuts("        ������ ���������      ");
    MmiGotoxy(0,1); MmiPuts(" N     ���   ����. ���� ���.");
   for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N      ���   ����. ���� ���.");
//                 "xx.....xxxxx  .x    .x   xx"
      MmiPrintf("%2d%10s  %2d    %2d   %02X",i+1,ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr);
    }
}
//-------------------------------
void f_drv_stat_MMI(int *nn)
{ // �������� ���������� ��������� ���������
int i,i1,i2;
char str[31];
  struct s_icp_dev *ICPl_DEV;

   f_clr_scr_MMI();

//  if( (*nn+n_mmi_str_3) > icp_lst_max) i=icp_lst_max-n_mmi_str_3;
//  else
    i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < icp_lst_max) i1=i+n_mmi_str_3;
    else i1=icp_lst_max;

    *nn=i;
    MmiGotoxy(0,0);  MmiPuts(" ���������� ������ ���������");
    MmiGotoxy(0,1);  MmiPuts(" N     ���    �������  ������");
    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N     ���    �������  ������");
//                 "xx.....xxxxx  xxxxxxx xxxxxxx"
         MmiPrintf("%2d%10s  %7ld %7ld",i+1,ICPl_DEV->name,ICPl_DEV->n_transaction,ICPl_DEV->n_timeout_error+ICPl_DEV->n_CRC_error);
    }
}
//-------------------------------
//-------------------------------
void f_mod_list_MMI(int *nn)
{ // �������� ������ ������������ �������
int i,i1,i2;
 char str[31];

  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  f_clr_scr_MMI();
  if(i1==0)
  {
    MmiGotoxy(3,2);   MmiPuts("    ������ ����." );
    MmiGotoxy(3,3);   MmiPuts("����������� ����� ���" );
    MmiGotoxy(3,4);   MmiPuts("  ���������� ������." );
  }
  else
  {
    MmiGotoxy(0,0);    MmiPuts(" ������ ������������ �������  ");
    MmiGotoxy(0,1);    MmiPuts(" N    ��� ����.���.����. TT FF");

      i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < i1) i1=i+n_mmi_str_3;
    *nn=i;

    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_MOD=f_get_mod_str(i);
      if(ICPl_MOD==NULL) break;
      MmiGotoxy(0,3+i2);

//         MmiPuts(" N    ��� ����.���.����. TT FF");
//                 "xx.....xxxx  x xx xxxxxx xx xx"
      MmiPrintf("%2d%9s  %1d %02X %6ld %02X %02X",i+1,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC],ICPl_MOD->TT,ICPl_MOD->FF);
    }
  }
}
//-------------------------------
int mode_prn=1;
void f_prn_current()
{ // �������� ��������� ������� �� ������� ������
  int year,month,day,hour,min,sec;
 MmiGotoxy(0,0);   MmiPrintf("T������ �������� �������� ���");
 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
 MoveToXY(0,5); MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
 MmiGotoxy(18,5);  MmiPrintf("%11.3f",s_MVD[0].MassI);
                                   // s_MVD[0].VolI
}
//-------------------------------
//-------------------------------
void f_prn_den_t()
{
float ftmp,ftmp1;
 //  ����������� �����,���������,�����������,��������
 //  ������� ��������.
 MmiGotoxy(0,0);   MmiPrintf("������� ��������� �����������");
 MmiGotoxy(0,1);   MmiPrintf(" ����� ���. %10.3f ��",s_MVD[0].MassI);
 MmiGotoxy(0,2);   MmiPrintf(" ����� ���. %10.3f ��",s_MVD[0].MassT);
 MmiGotoxy(0,3);   MmiPrintf(" ������    %10.2f ��/�",s_MVD[0].FlowM);
 MmiGotoxy(0,4);   MmiPrintf(" ��������� %10.2f ��/�3",s_MVD[0].Dens);
// MmiGotoxy(0,2);   MmiPrintf(" ��������     %6.3f ���  ",s_MVD[0].Press);
// MmiGotoxy(0,3);   MmiPrintf(" �����������  %6.2f ����.C",s_MVD[0].TempR);
 MmiGotoxy(0,5);   MmiPrintf(" ����.������.  %6.2f ����.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC-����,F1-��.�.���.");
}
//-------------------------------

/* =============
void f_prn_den_t()
{
float ftmp,ftmp1;
 //  ����������� ���������,�����������,�������
 //  ������� ��������.
     ftmp=s_MVD[0].Compos;
 MmiGotoxy(0,0);   MmiPrintf("������� ��������� �����������");
 MmiGotoxy(0,1);   MmiPrintf(" ���������  %8.2f ��/�3",s_MVD[0].Dens);
 MmiGotoxy(0,2);   MmiPrintf(" �����������  %6.2f ����.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC   - ������� � ����");
  MmiGotoxy(0,3);
 if(s_MVD[0].PressG>0)
 {
    MmiPrintf(" ����.���.���� %5.3f ���",s_MVD[0].PressG);
 }
 else
 {  if(ftmp> 1)
      {
         MmiPrintf(" � ����������� ������� ���� ");
         return;
      }
    else
         MmiPrintf(" �������� ���.���� �� �����.");
 }

 MoveToXY(0,4);
    {
     if(ftmp>1.)
      MmiPrintf("!��� ����� ������� �������");
     else if(ftmp<0.)
      MmiPrintf("!��� ������� ������� ������");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("���:������ %6.2f%c,����� %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
}
======*/

//-------------------------------
void f_prn_comps()
{
float ftmp,ftmp1;
 //  ����������� �������
 //  ������� ��������.
    if((s_MVD[0].Dens>0)&&(s_MVD[0].Temp>-300))
    {
//   ftmp=f_get_composition(s_MVD[0].Dens,s_MVD[0].Temp);
     ftmp=s_MVD[0].Compos;
     if(ftmp>1.)
       MmiPrintf("���.���� ");
     else if(ftmp<0.)
       MmiPrintf("���.���.�");
     else
      {
   //  MmiPrintf("������ %6.2f%c",(ftmp*100),'%');
       MmiPrintf("%8.2f ",(ftmp*100.));
      }
    }
    else
       MmiPrintf("�� �����.");
}
//-------------------------------
//-------------------------------
void f_prn_lst_hour()
{ // �������� ��������� ������� �� ��������� ����. ���

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 if(ltime0 >ltime1) ltime0-=n_sec_day;
 if( f_get_d_dat(ltime0, s_mode) < 0)
 {
  if(ltime0<ltime1)
  {

  if( (ar_str_ptr=f_get_lst_stor()) == NULL) goto m_bad;
  ltime2= f_get_time(ar_str_ptr);

  if(ltime0>ltime2)
   {
    tMassI= s_MVD[0].MassI;
    tVolI = s_MVD[0].VolI;
    f_wr_evt(evt_none);
    goto m_ok;
   }
   else goto m_bad;
  }
  ltime0-=n_sec_day;
  if( f_get_d_dat(ltime0, s_mode) < 0)
  {
  m_bad:
   MmiGotoxy(5,3);   MmiPrintf("������ �����������");
  }
  else
  {
  m_ok:
 MmiGotoxy(0,0);   MmiPrintf("   �������� �������� ��� ");
 MmiGotoxy(0,1);   MmiPrintf(" �� ��������� ��������� ���  ");

 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 MoveToXY(0,5);
    tdat = localtime( &ltime0 );
    MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
MmiGotoxy(18,5);
    if(tMassI != vBIG_P)
       MmiPrintf("%11.3f" ,tMassI);
//  else
//     MmiPrintf(" ------- ");
  }
 }
 else goto m_ok;

 return;
}
//-------------------------------
void f_prn_date()
{ // �������� ��������� ������� �� ��������� ����

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;
 // ����������� ������� ��������� ������ � ������

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

 tim_000=adate00;
 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 MmiGotoxy(0,0);   MmiPrintf("   �������� �������� ��� ");
 MmiGotoxy(0,1);   MmiPrintf("     �� ��������� ����  ");

 MmiGotoxy(0,3);   MmiPrintf("  ����     �����     �����,��");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");

 MoveToXY(0,5);
    tdat = localtime( &ltime0 );
    MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
MmiGotoxy(18,5);

 if( f_get_d_dat(ltime0, s_mode) < 0)
 {

  if( (ar_str_ptr=f_get_lst_stor()) == NULL) goto m_bad;

  ltime2= f_get_time(ar_str_ptr);

  if((ltime0<ltime1)&&(ltime0>ltime2) )
  {
   f_wr_evt(evt_none);
   if( f_get_d_dat(ltime0, s_mode) >= 0)
         goto m_ok;
   else goto m_bad;
  }
  else
  {
  m_bad:
      MmiPrintf("��� ������");
  }
 }
 else
 {
  m_ok:
    if(tMassI != vBIG_P)
       MmiPrintf("%11.3f",tMassI);
    else
       MmiPrintf(" ------- ");
 }
 return;
}
//-------------------------------
void f_prn_5day()
{ // �������� ��������� ������� �� ��������� 5 �����

 struct tm *tdat;

int year,month,day,hour,min,sec,i;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // ������� �����

 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);
/*
     tdat = localtime( &ltime0 );
     printf("\n\r%02d.%02d.%02d %02d:%02d:%02d",
        tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/

 if( f_get_d_dat(ltime0, s_mode) < 0)
 {
  if(ltime0<ltime1)
  {
   if( (ar_str_ptr=f_get_lst_stor()) == NULL)
   {
//  goto m_bad;
    goto m_ok;
   }
   ltime2= f_get_time(ar_str_ptr); // ��������� ������

   if(ltime0>ltime2)
   {
    tMassI= s_MVD[0].MassI;
    tVolI = s_MVD[0].VolI;
    f_wr_evt(evt_none);
    goto m_ok;
   }
   else
   {
//  goto m_bad;
    goto m_ok;
   }
  }
 else
   ltime0-=n_sec_day;
  {
  m_ok:

  ltime1=ltime0 - n_sec_day * 4;

 MmiGotoxy(0,0);   MmiPrintf("  ����     �����     �����,��");
//MmiGotoxy(0,3);  MmiPrintf("21.02.09 12:10:11  _123456.90");


    for(i=1;i<6;i++,ltime1+=n_sec_day)
    {


     MoveToXY(0,i);
        tdat = localtime( &ltime1 );
        MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
        tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
    MmiGotoxy(18,i);

     if( f_get_d_dat(ltime1, s_mode) < 0)
     {
           MmiPrintf("��� ������");
     }
     else
     // if(tMassI>= 0.)
           MmiPrintf("%11.3f" ,tMassI);
     // else
     //    MmiPrintf(" ------- ");
    }
    MmiGotoxy(0,6);   MmiPuts("ESC,Enter - ����������");

  }
 }
 else goto m_ok;
 return;

 m_bad:
   MmiGotoxy(5,3);   MmiPrintf("������ �����������");
 return;
}
//-------------------------------
char *rcv_mm[]={
"������",
"�����",
};
char *Rcv_mm[]={
"������",
"�����",
};
// rcv_mm[f_rcv]
int  f_prn_mmi_a(struct arch_str *a_str,int i_n)
{
 int ii,itmp,i_ret;
 float ftmp,ftmp1;
 struct tm *tdat;
 int f_rcv;

 if(a_str->event & (int)RCV_FLG)
       f_rcv=1;
 else
       f_rcv=0;

 MoveToXY(0,i_n);
   i_ret=i_n;
   if(i_ret>=n_mmi_str) return i_ret;

//  MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,a_str->day,a_str->month,a_str->year,a_str->hour,a_str->min,a_str->sec);

  tdat = localtime( &a_str->time );
  MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d",
  tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

  if(a_str->MassI != vBIG_P)
     MmiPrintf("%10.3f ��",a_str->MassI);
  else
     MmiPrintf(" ------- " );

   i_ret=i_n+1;
   if(i_ret>=n_mmi_str) return i_ret;

 MoveToXY(0,i_ret);
// switch( (int) a_str->event)
 switch( (int)( a_str->event & ~(int)RCV_FLG) )
 {
  case evt_NCNT_on:
    MmiPrintf(" ����� �������� ��� ����� ");
    goto m_val00;

  case evt_verify:
    MmiPrintf(" ����� �������");
    goto m_val00;

  case evt_verify_e:
    MmiPrintf(" ���� �������");
    goto m_val00;

  case evt_NCNT_off:
    MmiPrintf(" ��������� �������� ��� ����� ");
    goto m_val00;

  case evt_beg_eq:
    MmiPrintf("����� %s�.������� ����.",rcv_mm[f_rcv]);
    goto m_val0;
  case evt_start_f:
    MmiPrintf("����� %s�.������ ����.",rcv_mm[f_rcv]);

m_val0:
   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
  if(a_str->u.fill.VolT != vBIG_P)
      MmiPrintf("���� %8.3f�� ",a_str->u.fill.VolT    );
  else
      MmiPrintf("��� ����    ",a_str->u.fill.VolT    );
   goto m_val00;
/*
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%7.3f ���;" ,a_str->u.fill.UnitPrice);
    MmiPrintf("U ��� %6.2f V;",a_str->u.fill.Amount);

   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("�����.%6.3f ��/�3;" ,a_str->u.fill.Density);
    MmiPrintf("����.%6.2fC;" ,a_str->u.fill.Temp);

    if((a_str->u.fill.Density>0)&&(a_str->u.fill.Temp>-300))
    {
   i_ret=++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

     ftmp=f_get_composition(a_str->u.fill.Density,a_str->u.fill.Temp);
     if(ftmp>1.)
      MmiPrintf("!��� ����� ������� �������");
     else if(ftmp<0.)
      MmiPrintf("!��� ������� ������� ������");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("���:������ %6.2f%c,����� %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
    break;
*/
  case evt_cont_f:
    MmiPrintf(" ����������� %s�,",rcv_mm[f_rcv]);
    goto m_val;
  case evt_exm_f:
    MmiPrintf(" ���������,������� ");

m_val:

   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
   if(a_str->u.fill.VolT != vBIG_P)
         MmiPrintf(" ����� %s� %9.3f �� ",rcv_mm[f_rcv],a_str->u.fill.VolT );

m_val00:
   i_ret++;
m_val1:
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%7.3f ���;" ,a_str->u.fill.UnitPrice);
    MmiPrintf("U ��� %6.2f V;",a_str->u.fill.Amount);

   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("�����.%6.3f ��/�3;",a_str->u.fill.Density);
    MmiPrintf("����.%6.2fC;" ,a_str->u.fill.Temp);

 /*
    if((a_str->u.fill.Density>0)&&(a_str->u.fill.Temp>-300))
    {
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
     ftmp=f_get_composition(a_str->u.fill.Density,a_str->u.fill.Temp);
     if(ftmp>1.)
      MmiPrintf("!��� ����� ������� �������");
     else if(ftmp<0.)
      MmiPrintf("!��� ������� ������� ������");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("���:������ %6.2f%c,����� %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
*/
    break;

  case evt_exp_f:
    MmiPrintf(" ���������,�������");
    goto m_val;

  case evt_end_gas:
    MmiPrintf(" %s �����.��� ���.����",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_end_f:
    MmiPrintf(" ��������� ��  ");
    goto m_val;

  case evt_est_f:
    MmiPrintf(" %s ������� ��������",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_err_f:
    MmiPrintf(" %s ������� �������",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_eq_pr :
    MmiPrintf("����� ���.����. ������� ���");
    goto m_val;
  case evt_stop_eq :
  printf("������.���.����. ������� ���");
    goto m_val;

  case evt_ep1_f:
    MmiPrintf(" %s �������,Host",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_overfl:
    MmiPrintf(" %s ������� ���.������",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_ES_off:
    MmiPrintf(" %s �����.����.������� ES",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    MmiPrintf(" %s �����.��� ������� ���",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    MmiPrintf(" %s �����.��� ������� 380V",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_VLT_off:
    MmiPrintf(" %s �����.��� ���������",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_VLT:
    MmiPrintf(" ��� ���������");

    i_ret=i_n+2;
    goto m_val1;

  case evt_wd_pmp:
    MmiPrintf(" %s �����.WD PMLAN",Rcv_mm[f_rcv]);
    goto m_val;


  case evt_no_dev:
    MmiPrintf(" ����� �� ������.�� ���.�����");
    goto m_val;

  case evt_clr_err:
    MmiPrintf(" ����� ������. ");
    break;

  case evt_MVD_CL_strt:
    MmiPrintf(" ����� ���������� �����������");
    break;

  case evt_MVD_CL_BS1 :
    MmiPrintf(" !������� ���.����.��� ���.");
    break;

  case evt_MVD_CL_BS2 :
    MmiPrintf(" !���� ��� ������ ���.����.");
    break;

  case evt_MVD_CL_OK :
    MmiPrintf(" ���������� ����������� OK");
    break;

  case evt_MVD_CL_TM :
    MmiPrintf(" ������� ���������� ��������.");
          //  |                              |

    break;

  case evt_ch_date:
    MmiPrintf(" ���� ��������.");
    break;

  case evt_ch_time:
    MmiPrintf(" ����� ��������.");
    break;
  case evt_ch_sum:
    MmiPrintf(" ������� �� ������ �����.");
    break;
  case evt_ch_win:
    MmiPrintf(" ������� �� ������ �����.");
    break;
  case evt_res:
    MmiPrintf(" ������� �����");
    break;
  case evt_Slot:
    MmiPrintf(" MVD:����������-� ����������");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     MmiPrintf(" !���.����.������");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     MmiPrintf(" !���.����.�����");
    }
    else if(a_str->u.fill.VolT == Par_MC)
    {
     MmiPrintf(" !���.����.�.����.");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     MmiPrintf(" !������� ������");
    }
    else
     {
//    MmiPrintf(" !���. �����. ");
      MmiPrintf(" !������� �������� ");
      MmiPrintf("N%g ",a_str->u.fill.VolT );
     }

   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("����:%g; ",a_str->u.fill.Amount  );
    MmiPrintf("�����:%g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    MmiPrintf(" ������� ����� � ���");
    break;
  case evt_re:
    MmiPrintf(" ������ ����.�� EEPROM");
    break;
  case evt_re_err:
    MmiPrintf(" ������ ������ ����.�� EEPROM");
    break;
  case evt_we:
    MmiPrintf(" ������ ����. � EEPROM");
    break;
  case evt_we_err:
    MmiPrintf(" ��.������ ����. � EEPROM");
    break;

  case evt_wrong_start:
    MmiPrintf(" C���� �� ������.������.");
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;ii<=icp_lst_max ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    MmiPrintf(" ������:");
 mm_e:

   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

 MmiPrintf(" %01X" ,a_str->u.err.err[0] );
 MmiPrintf(" %04X" ,a_str->u.err.err[1] );
 MmiPrintf(" %01X" ,a_str->u.err.err[2] );
 MmiPrintf(" %01X" ,a_str->u.err.err[3] );
 MmiPrintf(" %01X" ,a_str->u.err.err[4] );
 MmiPrintf(" %01X" ,a_str->u.err.err[5] );
 MmiPrintf(" %01X" ,a_str->u.err.err[6] );
 MmiPrintf(" %04X" ,a_str->u.err.err[7] );
  }
  else
 MmiPrintf(" ������ ��� ");

  break;

  case evt_t_on:
 MmiPrintf(" ��������� ����������");
    break;
  case evt_t_off:
 MmiPrintf(" ���������� ����������");
    break;
  default:
 MmiPrintf(" ������� �� ��������");
   break;
 }
 return i_ret;
}

//----------------------------------
void f_MVD_M1()
{
// ���������� ��������� MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_L;
   s_MVD[0].r_addr=127;
   sw_mvd_m1=1;
   break;

  case 1:
  if(MVD_fn[0] != F_FAULT)
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("SN   %ld",s_MVD[0].l);}
  if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 21:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=425;
   s_MVD[0].n=8;
   sw_mvd_m1=2;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("S  : %s",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 22:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].n=8;
   s_MVD[0].r_addr=96;
   sw_mvd_m1=3;
   break;

  case 3:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM:%s",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 23:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=104;
   s_MVD[0].n=16;
   sw_mvd_m1=4;
   break;

  case 4:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("M:%s",s_MVD[0].a); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 24:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=16;
   sw_mvd_m1=5;
   break;

  case 5:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM ������: %d",s_MVD[0].i);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 25:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=72;
   s_MVD[0].n=5;
   sw_mvd_m1=6;
   break;

  case 6:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Flow : --%s--",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 26:
   MVD_fn[0]=MVD_RD_S;
   s_MVD[0].r_addr=80;
   s_MVD[0].n=7;
   sw_mvd_m1=7;
   break;

  case 7:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("�emp.: --%s--",s_MVD[0].a);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 27:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=155;
   sw_mvd_m1=8;
   break;

  case 8:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("D1:                  %.3f",s_MVD[0].f); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=157;
   sw_mvd_m1=9;
   break;

  case 9:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("D2:                  %.3f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=159;
   sw_mvd_m1=10;
   break;

  case 10:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("K1:                  %.3f",s_MVD[0].f); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 30:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=161;
   sw_mvd_m1=11;
   break;

  case 11:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("K2:                  %.3f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� �����:     %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281;
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� ������:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 33:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283;
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("��������� ���������: %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 34:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=15;
   break;

  case 15:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ����.�������:   %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 35:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;
   sw_mvd_m1=16;
   break;

  case 16:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("���� ��. �������:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 36:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=149;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("���� ��������� :     %.6f",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  }

}
/* ---------------------------------------- */
void f_MVD_M1f()
{
// ���������� ��������� ��������� �������  MVD  �� MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !������� ������ MVD");
     ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 31:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=279;
   sw_mvd_m1=12;
   break;

  case 12:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,4);MmiPrintf("��������� �����:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
//   s_MVD[0].r_addr=281; // ��������� ������
   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
//   { MoveToXY(0,5);MmiPrintf("��������� ������:   %.6f",s_MVD[0].f);}
 { MoveToXY(0,5); MmiPrintf("���� �.����.: %10.2f ��/�",s_MVD[0].f);}
   k_v_flow=s_MVD[0].f;
   ff_serv=NULL;
   Flag_f_corr=1;
   break;
 }
}
/* ---------------------------------------- */
char *unit1=NULL;//I39
char *unit2=NULL;//I45
char *unit3=NULL;//42 // Volume flow codes
char *unit4=NULL;// Volume totalizer or volume inventory codes I 0046
char *unit5=NULL;// Density codes I0040
char *unit6=NULL;// Temperature codes I0041
float MMITemp,MMIDens,MMICompos;
void f_MVD_M2()
{
char *unit;
int u_cod;
// ���������� ������ MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=39; // I039 Mass flow codes
   s_MVD[0].i=-1;
   sw_mvd_m1=1;
   break;

  case 1:
   u_cod=s_MVD[0].i;
    if(u_cod>0)  unit1=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=247;
   sw_mvd_m1++;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit1 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ �. : %f %s",s_MVD[0].f,unit1);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }

  case 21:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr=45; // Mass totalizer or mass inventory unit codes I 0045
   s_MVD[0].i=-1;
   sw_mvd_m1=3;
   break;

  case 3:
   u_cod=s_MVD[0].i;
    if(u_cod>0)  unit2=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=259;
   sw_mvd_m1++;
   break;

  case 4:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit2);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 22:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=263;
   sw_mvd_m1=5;
   break;

  case 5:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit2); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 23:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 42 ; // Volume flow codes I0042
   s_MVD[0].i=-1;
   sw_mvd_m1=6;
   break;

  case 6:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit3=f_get_unit(u_cod);

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=253;
   sw_mvd_m1++;
   break;

  case 7:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit3 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ��.: %f %s",s_MVD[0].f,unit3);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 24:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 46 ; // Volume totalizer or volume inventory codes I 0046
   s_MVD[0].i=-1;
   sw_mvd_m1=8;
   break;

  case 8:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit4=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=261;
   sw_mvd_m1++;
   break;

  case 9:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit4);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 25:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=265;
   sw_mvd_m1=10;
   break;

  case 10:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit4);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 26:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 40 ; // Density codes I0040
   s_MVD[0].i=-1;
   sw_mvd_m1=11;
   break;

  case 11:
   u_cod=s_MVD[0].i;
   if(u_cod>0)
   {
     unit5=f_get_unit(u_cod);
//     printf("\n\r density unit :%s",unit5);
   }
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=249;
   sw_mvd_m1++;
   break;

  case 12:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit5 != NULL)
    {
      MoveToXY(0,sw_MMI_cur++);MmiPrintf("���������  :%.5f %s",s_MVD[0].f,unit5);
//    MMIDens=s_MVD[0].f*K_unit;
      MMIDens=s_MVD[0].f;
    }
   else sw_MMI_cur++;
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  else sw_MMI_cur++;
  case 27:
   MVD_fn[0]=MVD_RD_I;
   s_MVD[0].r_addr= 41 ; // Temperature codes I0041
   s_MVD[0].i=-1;
   sw_mvd_m1=13;
   break;

  case 13:
   u_cod=s_MVD[0].i;
   if(u_cod>0)  unit6=f_get_unit(u_cod);
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=251;
   sw_mvd_m1++;
   break;

  case 14:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit6 != NULL)
   {
    MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.������: %.3f %s",s_MVD[0].f,unit6);
    MMITemp=s_MVD[0].f;
   }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
    if((MMIDens>0)&&(MMITemp>-300))
    {
     MMICompos=f_get_composition(MMIDens,MMITemp);
     if(MMICompos>1)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ����� ������� �������");}
     else if(MMICompos<0)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ������� ������� ������");}
     else
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���,������ %5.2f%c,����� %5.2f%c",(MMICompos*100.),'%',(100.-MMICompos*100.),'%' );}
    }
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.����� : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.���.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }

}
/* ---------------------------------------- */
void f_MVD_MM2()
{
char *unit;
// ���������� ������ MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD");
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 20:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=247;
   sw_mvd_m1=2;
   break;

  case 2:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit1 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ �. : %f %s",s_MVD[0].f,unit1);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }

  case 21:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=259;
   sw_mvd_m1=4;
   break;

  case 4:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit2);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 22:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=263;
   sw_mvd_m1=5;
   break;

  case 5:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit2 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit2); }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 23:

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=253;
   sw_mvd_m1=7;
   break;

  case 7:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit3 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ��.: %f %s",s_MVD[0].f,unit3);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 24:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=261;
   sw_mvd_m1=9;
   break;

  case 9:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.3f %s",s_MVD[0].f,unit4);}
     if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 25:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=265;
   sw_mvd_m1=10;
   break;

  case 10:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit4 != NULL)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ���.: %10.2f %s",s_MVD[0].f,unit4);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  }
  case 26:

   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=249;
   sw_mvd_m1=12;
   break;

  case 12:
  if((MVD_fn[0] != F_FAULT)&&(unit5 != NULL))
  {
     MoveToXY(0,sw_MMI_cur++); MmiPrintf("���������  :%.5f %s",s_MVD[0].f,unit5);
     MMIDens=s_MVD[0].f;
  }
  else
  {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("������ ������");
  }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 27:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=251;
   sw_mvd_m1=14;
   break;

  case 14:
  if(MVD_fn[0] != F_FAULT)
  {
   if(unit6 != NULL)
    {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.������: %.3f %s",s_MVD[0].f,unit6);
     MMITemp=s_MVD[0].f;
    }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
    if((MMIDens>0)&&(MMITemp>-300))
    {
     MMICompos=f_get_composition(MMIDens,MMITemp);
     if(MMICompos>1)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ����� ������� �������");}
     else if(MMICompos<0)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����� ������� ������� ������");}
     else
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("���,������ %5.2f%c,����� %5.2f%c",(MMICompos*100.),'%',(100.-MMICompos*100.),'%' );}
    }
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.����� : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("����.���.  : %.3f V",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  default:
     ff_serv=NULL;
  }

}
//------------------------
void f_MVD_M3()
{
int i,i2,ii;

unsigned long int ltmp,i1;
// ���������� ������ MVD

  ii=i_nn_mvd;

  if((MVD_fn[ii] != 0) && (MVD_fn[ii] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !������� ������ MVD %d",ii+1);
        ff_serv=NULL;
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_m1)
  {
  case 0:

   MVD_fn[ii]=MVD_RD_F;
   s_MVD[ii].r_addr=245;
   sw_mvd_m1++;
   break;

  case 1:
   if(MVD_fn[ii] != F_FAULT)
   {
     ltmp=(unsigned long int)s_MVD[ii].f &0xffffff;
     fl_zeroing=ltmp;
     if(ltmp==0)
     {
        MoveToXY(8,3); MmiPrintf("MVD %d.������ ���.",ii+1);
        ff_serv=NULL;
        return;
     }
     else
     {
       i2=0;
       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1)
         {
          i2++;
         }
       }

     if(sw_mmi!=18)
     {
      MoveToXY(0,0);
/*
      if(i2==1)
          MmiPrintf(" ������ ����������� N%d :",ii+1);
      else if( i>1)
*/
          MmiPrintf(" ������ ����������� N%d:",ii+1);
       i2=1;
     }
     else
     {

      MoveToXY(0,0);
         MmiPrintf("����./������ ����������� N%d:",ii+1);
       i2=2;
     }
       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1)
         {
           MoveToXY(0,i2);
           MmiPuts(str_empty);
           MoveToXY(0,i2);
           if(i==0x11) MmiPrintf("���������� �����������");
           else if(i==0x13) MmiPrintf("����� �� ��������� �������");
           else if(i==0x15) MmiPrintf("������������� ������������");
           else MmiPrintf("!Err %d",i);
//         MmiPrintf("!%s",err_F425R[i]);

           i2++;
           if(i2>=7)
           {
            ff_serv=NULL;
            return;
           }
         }
       }
       for(;i2<6;i2++)
       {
           MoveToXY(0,i2);
           MmiPuts(str_empty);
       }
     }
   }
   ff_serv=NULL;
   break;
  }
}
//------------------------


/* ---------------------------------------- */
//-------------------------------

char *list1_dsr[]={

"MMI:������",                 //  0
"MMI:����� �����",            //  1
"MMI:�����",                  //  2
"MMI:�����,�� ",              //  3
"MMI:�������,��",             //  4
"MMI:���� CRC",               //  5

"7017/1:������",                 //  6
"���.������ �����.",             //  7
"T ������.���.,��",              //  8
"Mode 1-Dens,2-Press.",          //  9
"",                              // 10
"������ �����.MVD,mm",          // 11

"7017/2:������",                // 12

"M ���.��.���,��",                // 13
"M ���.��.���,��",                // 14

"������ ��� N ���.",        // 15
"������� N ���.",        // 16
"7017/2:���� CRC",              // 17

"7060/1:������",                 // 18

"",           // 19
"",        // 20
"",        // 21

"����.��.�����.-���.",        // 22
"���� ����.�����.+�.",       // 23

"7060/2:������",           // 24

"T ���.����.,��",          // 25
"T ���.�����,��",          // 26
"T ���.��������.,��",      // 27
"���.���.���.��.,��",      // 28
"T ����.���.����,��",      // 29

"COM1 ��������",                // 30
"COM2 ��������",                // 31
"COM3 ��������",                // 32
"COM4 ��������",                // 33

"����.:�-���,��",            // 34
"����.:����.���.",           // 35
"����.ICP:CRC ����",            // 36

"WDOG/1:������",                // 37
"WDOG/1:����� �����",           // 38
"WDOG/1:������,�� ",            // 39
"WDOG/1:��������,��",           // 40
"WDOG/1:���� CRC",              // 41

"dP ��� +�����.,���",       // 42
"dP ��� -�����.,���",       // 43
"+� T ��� ��� P�� ",        // 44
"N �����.����.(1-3)",       // 45
"WDOG/2:���� CRC",              // 46

"7060/1:������.WD",           // 47
"7060/1:����.WD,0.1�",        // 48

"7060/2:������.WD",           // 49
"7060/2:����.WD,0.1�",        // 50

"MVD1:������     ",           //  51
"MVD2:������     ",           //  52
"MVD:�����",                  //  53
"MVD:�����,�� ",              //  54
"MVD:�������,��",             //  55

"TSD:������",                 //  56
"TSD:����� �����",            //  57
"TSD:�����",                  //  58
"TSD:�����,�� ",              //  59
"TSD:�������,��",             //  60

"COM1 �����",                // 61
"COM2 �����",                // 62
"COM3 �����",                // 63
"COM4 �����",                // 64

"COM1 ��������",           // 65
"COM2 ��������",           // 66
"COM3 ��������",           // 67
"COM4 ��������",           // 68

"COM1 ���� ���",           // 69
"COM2 ���� ���",           // 70
"COM3 ���� ���",           // 71
"COM4 ���� ���",           // 72

"COMP ��������",           // 73
"COMP �����",              // 74
"COMP ��������",           // 75
"COMP ���� ���",           // 76

"COMP ����� �����",        // 77
"����� ����� Gun",         // 78
"�����-� ����� Gun",       // 79

"������ ��� N ���.",        // 80
"������ ��� N ���.",        // 81
"���� ����.������.",        // 82
"����� PUMALAN",            // 83
"������ PUMALAN",           // 84
"COM1:����.��� 0,1",        // 85
"COM2: 0-ICP,1-RTU",        // 86
"COM3:����.��� 0,1",        // 87
"��� ��.�������",           // 88
"������� �� ���.��.",       // 89
"------------------",       // 90
"������ ����� ���.1",       // 91
"������ ����� ���.2",       // 92
"������ ����� ���.3",       // 93
"�������� �����. 1",        // 94
"�������� �����. 2",        // 95
"�������� �����. 3",        // 96
"������-� �����,��",        // 97
"M ���.��.���,��",         // 98    p1-p6.CLV
"M ���.��.���,��",         // 99
"T ��� ��.,��",       // 100
"T ���.��.,��",       // 101
"���.����.��.MMI,��",      // 102
"����.����.�.MMI,��",       // 103
"������.���. 0...1",        // 104   p1-p3.KA
"������.���. 0...1",        // 105
"���-�� ���.���.,��",       // 106

"�������� ����� 1/0",       // 107    p1.CTRL
"���-�� ����.MVD,��",       // 108    p2.CTRL
"���� ����.��� TST",        // 109    p3.CTRL

"��������� M,��",           // 110    p1-p5.DSC
"�����������-� M,��",        // 111
"������ ��� ����.��",       // 112
"��������� M,��",            // 113
"��������� T,��",           // 114

// DNP
"������ �����.+",           // 115
"������ �����.-",           // 116
"������.����.20",           // 117
"\% ������� ��� t",         // 118
"����� t ���.0-2",          // 119
"����� ������� 1-3",        // 1 2 0

// DNC
"����.��.�����.���.",        // 121
"���� ����.�����.���.",       // 122
"",      // 123
"",        // 124
"",        // 125

//DTC
"�����.���.,�/��3",         // 126
"������.�������.,C",        // 127
"���� �������",             // 128

"U ��� ������ ��,V",       // 129
"U ��� ��������,V ",       // 130

"U �� ������ ��,V",        // 131
"U �� ��������,V ",        // 132

"��.���. ��� ���.3",        // 133
"MAX �������",              // 134
"MAX �������",              // 135
"WD ���.PUMALAN,��",        // 136
// FLCH
"M ���.���. LTL,��",      // 137
"T ���.���.,���",       // 138
"���.������ N ���.",        // 139
"���.���� ��,N ���.",       // 140
"���.���� ����.N���.",      // 141
"���.���� ����.N���.",      // 142
"��������� ��. N ��.",      // 143
"��������� ��.��.���",      // 144
"������ ���  . N ��.",      // 145
"������ ��� ���� ���",      // 146
"����� ���.���.�.,�",      // 147
"����� ���.���.���,�",     // 148
"����� ���.���.�.,�",      // 149
"����� ���.���.���,�",     // 150
"f ���� ������,0.1��",     // 151
"T ����.������,0.1�",      // 152
"���.���.���.��.,��",     // 153
"���.����.������,��",      // 154
"T ����.������,0.1�",      // 155
"P ������ �����,���",      // 156
"P ��������,    ���",      // 157
"������  Min,kg/h",      // 158
"����.��� ������,�/�",     // 159
"�����.�������.T1,��",     // 160
"�����.�������.T2,��",     // 161
"U ��������������,V",      // 162
"U ���������� ,V",         // 163
"U ���.�� ����,V",         // 164
"T �� ���.�������,��",     // 165
"T �� ����������,��",      // 166
"",
};
//-------------------------------
char *list2_dsr[]={
" �����.������",            //  0
" ����.���,�����.",         //  1
" ����.����.,���",          //  2
" ����.����.,C",            //  3
};
//-------------------------------
//#define mmi_page   page_MMI_c
#define mmi_page   page_MMI
char mmi_point=0;
//#define size_max 29
int mmi_prm=0;
int mmi_flag=0;

int num_page=0.;
int sw_mmi=0;
int mmi_str=0;
int mmi_com=1;
int flag_chg=0;
int nn_chg=0;
unsigned int pass_cnt;
int max_par=1;
#define NumPlace 22

int FlagWinSum=1;

struct arch_str_t adate11;

struct dis_set_MMI *ds_list=NULL;


long int Password=5555;
long int PassW=0;
int k_ext=0;
int k_ext1=0;
float chg_nn_par=0,chg_old=0,chg_new=0;
float dose_dlvr=0;
int n_adc_mm=0;

int f_menu_MMI()
{
  time_t ltime1;
  time_t ltime2;
  int year,month,day,hour,min,sec;
  int key;
  char str[31];
  int i,j,k;
  struct s_icp_dev *ICPl_DEV;
struct arch_str *ar_str_ptr;
long int ltmp;
 struct tm *tdat;

//   s_MVD[0].Press=( ADC[0] + analog_offset[0]) * analog_scale[0];

   if((i=fstin())==fst_OK)
   {  // ������� �������� ��������
     key=DATA;  // ������� ��������� ����� ������
     sw_fst=0;
   }
   else if(i==fst_ESC)
   {
     key=DATA_ESC;  // ������� ��������� ����� ������
     sw_fst=0;
   }
   else if( MmiKbhit())
   {  // ���� ������������ ������� �� ����������
    key=MmiGetch();
   }
   else if(sw_fst==0)
   {
    key=PASS; // ������� ��������� ������� (��� ���������� �������)
              // ������������ ��� ��������� ������������ ��������
   }
   else return 0;

   switch(sw_mmi)
    {
     case 0: /*���������*/
//------------------------------------
/*=========
       if(key==F2)
        {
       m_0f2:
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("������� ����� ��������:" );
          sprintf( fst_str,"%d",num_page);
          fst_n=2;
          sw_fst=1;
//        MmiGotoxy(10,3);
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ���� ��������
          break;
        }
       else if(key==DATA)
        {
          sscanf(fst_str,"%d",&num_page);
          if(num_page<0) { num_page=0; goto m_0f2;}
          else if(num_page > 63) {num_page=63; goto m_0f2;}

          SetDisplayPage((int)num_page);
          sw_mmi=100;
          f_clr_scr_MMI();
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_main;
        }
==============*/
//---------------------------------
       if(key==F2)
       {
           PageD=0;
           f_prn_begin();
       }
       else if(key==F3)
       {
           PageD=1;
           f_prn_begin();
       }
       else if(key==F1)
       {
           PageD=2;
           f_prn_begin();
       }
//---------------------------------
        else if ((key=='-') || (key=='9'))
        {  // ���������� �������
           f_clr_scr_MMI();
           SetDisplayPage(EmptyPage);
        MmiGotoxy(0,1);        MmiPuts("  !!! ���������� ������� ");
        MmiGotoxy(0,3);        MmiPuts("Enter  ���������");
        MmiGotoxy(0,4);        MmiPuts("ESC    �� ���������,����������");
           sw_mmi=28;
           break;

        }
//---------------------------------
        if (key==Sht_ESC)
        {  // ������� ������

          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);
          sw_mmi=26;
          f_cl_error();
          MmiGotoxy(5,2);    MmiPuts("   ������ �������   ");
          MmiGotoxy(0,4);    MmiPuts(" Enter - ���������� ");

        }
        else if (key==Sht_F1)
        {  // ���������� ������

          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);
          sw_mmi=26;
          f_disp_error();
        }
        else if(key==Sht_F3)
        {  // MVD2 zeroing
          i_nn_mvd=1;
          goto m_sf2;
        }
        else if(key==Sht_F2)
        {  // MVD1  zeroing
          i_nn_mvd=0;
m_sf2:
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);

          if(f_reset_zer_MVD(i_nn_mvd) == 0)
          {
          f_wr_evt(evt_MVD_CL_BS2);
          MoveToXY(0,3);
          MmiPrintf(" ������ ������� ���������� ");
  m_SF2:
          f_d_ESC();
          sw_mmi=-1;
          break;
          }
          f_wr_evt(evt_MVD_CL_strt);
          sw_mmi=18;
          zero_time=TimeStamp;
          fl_zeroing=1;
          break;
        }

       else if(key==ESC)
       {
m0_f1:
main_menu:
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);
          f_prepare_t (&adate00);
          sw_mmi=120;
          Flag_check = 0;
          PassW=0;

            MmiGotoxy(0,0);    MmiPuts("     ���� ");
            MmiGotoxy(0,1);    MmiPuts("1  ������ ���");
            MmiGotoxy(0,2);    MmiPuts("2  �����  ���");
            MmiGotoxy(0,3);    MmiPuts("3  �������� ��� �����");
//          MmiGotoxy(0,3);    MmiPuts("3  ��������� �������� ���");
            MmiGotoxy(0,4);    MmiPuts("4  �������� ������� �������");
            MmiGotoxy(0,5);    MmiPuts("5  ��������� �������");
//          MmiGotoxy(0,6);    MmiPuts("6  ���������,����.,������");
            MmiGotoxy(0,6);    MmiPuts("ESC  �������");

          break;
       }
       else if(key==PASS)
        {  // ����������� ���� � �������
         if((FL_err|CRC_err) == 0)
         {
          if(PageD==0)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.2f ��     ",s_MVD[0].MassI+s_MVD[1].MassI);
             MmiGotoxy(14,4);  MmiPrintf("%8.1f  ��/�3 ",s_MVD[0].Dens);
             MmiGotoxy(14,5);  MmiPrintf("%9.3f ���    ",s_MVD[0].Press);
//           MmiPrintf("%9.2f ����.    ",s_MVD[0].Temp);
            // MmiGotoxy(18,4);
            //    f_prn_comps();
          }
          else if(PageD==1)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.3f ���    ",s_MVD[0].Press);
             MmiGotoxy(14,4);  MmiPrintf("%9.2f �       ",s_MVD[0].Volt_A);
             MmiGotoxy(14,5);  MmiPrintf("%9.2f �       ",s_MVD[0].Volt_DC);
          }
          else if(PageD==2)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.2f ��     ",s_MVD[0].MassI);
             MmiGotoxy(14,4);  MmiPrintf("%9.2f ��     ",s_MVD[1].MassI);
             MmiGotoxy(14,5);  MmiPrintf("%9.2f ��     ",s_MVD[0].MassI+s_MVD[1].MassI);
          }
         }
         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(0,6);
         MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
        }

        break;
 /*========================================*/
    case 11:  /*���� ������ ����� ��� ��������� ���������� */
       n_adc_mm=0;
       if(key==ESC)    /* ������� � ���� M3, ��������� ������� */
       {
         goto m_m3;
       }
       else if(key=='1')  // ������� ������ #1
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=0;
        }
       else if(key=='2')  // ������� ������ #2
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=max_par/5;
        }
       else if(key=='3')   // ������� ������ #3
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*2)/5;
        }
       else if(key=='4')  // ������� ������ #4
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*3)/5;
        }
       else if(key=='5')  // �������������� ������
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*4)/5;
        }
             else if(key=='6')  // �������������� ������
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm= max_par-2;
        }

       else break;
       flag_chg=0;
       nn_chg=0;

       f_clr_scr_MMI();
       SetDisplayPage(EmptyPage);    // ������ ��������
  par_out14:
       for(i=0;i<n_mmi_str_1;i++)
       {

        k=mmi_prm+i;
        if(k>= max_par) continue;
        MoveToXY(0,i);
           MmiPrintf("%2d %s",k+1,ds_list[k].descr[ds_list[k].ind]);
        MoveToXY(NumPlace,i);
           PrintMmiOp(&ds_list[k],1);
       }
       if(flag_chg==0)
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"Enter\"���. ");
       }
       else
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\",\"F3\",\"ESC\",\"Enter\"         ");
         MmiGotoxy(2,nn_chg);  MmiPuts("#");
       }
       sw_mmi=14;
       break;
 /*========================================*/
    case 14:/* �������� �� 6 ���������� */
       if(key==Sht_F2)    /* ���������� ��������� � EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptyPage);    // ������ ��������
        MmiGotoxy(0,1);    MmiPuts("���������� ������ � EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ���������");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ���������,����������");
        sw_mmi=15;
        break;
       }
       if(key==Sht_F3)    /* ������ ������ �� EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptyPage);    // ������ ��������
        MmiGotoxy(0,1);    MmiPuts("������ ������ �� EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    ��������� ");
        MmiGotoxy(0,4);    MmiPuts("ESC   �� ���������,����������");
        sw_mmi=16;
        break;
       }
       if(flag_chg==0)
       {
         if(key==ESC)    /* ������� � ���� ������ ����� ��� ���������*/
         {
          goto m_m3_3;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=n_mmi_str_1)
           {
            mmi_prm -=n_mmi_str_1;
            f_clr_scr_MMI();
            SetDisplayPage(EmptyPage);    // ������ ��������
            goto par_out14;
           }
           else
           {
            mmi_prm = 0;
            f_clr_scr_MMI();
            SetDisplayPage(EmptyPage);    // ������ ��������
            goto par_out14;
           }
         else if((key== F3 )&& (mmi_prm < (max_par-n_mmi_str_1)) )
         {
          mmi_prm +=n_mmi_str_1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          goto par_out14;
         }
         if(key== ENTER)
         {
          flag_chg=1;

          if((nn_chg+mmi_prm) >= max_par)
             nn_chg=max_par-mmi_prm-1;
          goto par_out14;
         }
       }
       else  // flag_chg!=0
       {
         if(key==ESC)    // ������� ����� ��������������
         {
          flag_chg=0;
          goto par_out14;
         }
         if((key== F2 )&& (nn_chg>0) )
         {
          nn_chg -=1;
          goto par_out14;
         }
         else if((key== F3 )&& (nn_chg < n_mmi_str_2) )
         {
          nn_chg +=1;

          if((nn_chg+mmi_prm) >= max_par)
             nn_chg=max_par-mmi_prm-1;
          goto par_out14;
         }
         if(key==ENTER)    // �������������� ���������
         {
          if(PassW != Password)
          {
           pass_ret=0;
m_pass:
           MmiGotoxy(1,1);
           f_clr_scr_MMI();
           MmiPuts("������� ������:" );
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // ���� ������
           sw_mmi=121;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
//         MmiGotoxy(15,3);
           break;
          }

          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(2,nn_chg);  MmiPuts(">");
          MoveToXY(NumPlace,nn_chg);

          PrintMmiOp(&ds_list[nn_chg+mmi_prm],0);
          fst_n=8;
          sw_fst=1;
          break;
         }
       }
       if(key==DATA)    // ���� ���������� ������
       {
         ScanfMmiOp(&ds_list[nn_chg+mmi_prm]);
         f_after_MMI();
         chg_nn_par=nn_chg+mmi_prm+1;
         f_wr_evt(evt_chg_param);
m_14_ni:
         MoveToXY(NumPlace,nn_chg); MmiPuts("         ");
         goto par_out14;
       }
       else if(key==DATA_ESC)
        {
          goto m_14_ni;
        }
       break;
 /*========================================*/
    case 15:/* ���������� ������ � EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������� � ����������� ���������� */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          goto par_out14;
         }
         else if(key=='1')    // ��������� ������
         {

           if(f_wrt_eee()<0)
           {
              f_wr_evt(evt_we_err);
              MmiGotoxy(0,5);   MmiPuts("������ ��� ���������� ������");
           }
           else
           {
              f_wr_evt(evt_we);
              MmiGotoxy(0,5);   MmiPuts(" ������ ��������� �������");
           }
              f_wr_cor();
              MmiGotoxy(0,6);   MmiPuts("      Enter - ����������");
         }
         break;
 /*========================================*/
    case 16:/* ������ ������ �� EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* ������� � ����������� ���������� */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          goto par_out14;
         }
         else if(key=='1')    // ���������
         {
           f_chk_EEE_CRC();
           if(f_rd_eee()<0)
           {
              f_wr_evt(evt_re_err);
              MmiGotoxy(0,5);   MmiPuts("������ ��� ������ ������");
              CRC_err=1;
           }
           else
           {
              f_wr_evt(evt_re);
              MmiGotoxy(0,5);   MmiPuts("  ������ ������� �������");
              CRC_err=0;
           }

           f_rd_cor();
           MmiGotoxy(0,6);   MmiPuts("      Enter - ����������");
         }
         break;
 /*========================================*/
    case 18:
       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
           goto m_main;
       if( f_timer(zero_time,Time_zeroing ))
       {
             f_clr_scr_MMI();
             MoveToXY(3,3);
            MmiPrintf(" ������� ����������");
          fl_zeroing=0;
          ff_serv=NULL;
          f_wr_evt(evt_MVD_CL_TM);
          goto m_SF2;
       }
          if(ff_serv==NULL)
          {
           if(fl_zeroing==0)
           {
             f_clr_scr_MMI();
             MoveToXY(1,3);
         MmiPrintf("���������� ��������� �������");
//                |                              |
             f_wr_evt(evt_MVD_CL_OK);
             goto m_SF2;
           }
           fl_rd_err=0;
           sw_mvd_m1=0;  // ���.��������
           ff_serv=f_MVD_M3;
          }

         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(4,6);
         MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
         break;
 /*========================================*/
    case 120:  // �������� ����

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           PageD=0;
           goto m_main;
       }
       else if(key== '1') //  1  ������ ���
       {

         flag_rcv=0;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         MassStamp=s_MVD[0].MassI;
         MassStamp2=s_MVD[1].MassI;
         VolStamp=s_MVD[0].VolI;
         VolStamp2=s_MVD[1].VolI;
         dose_dlvr=0;

         PageD=0;
         f_prepare_t ( &adate00);
m_m5:

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("   ���� 1.������ ���.");
            f_prn_MassSt_dlv();
            MmiGotoxy(0,2);    MmiPuts("1 ������ ���� ���");
            MmiGotoxy(0,3);    MmiPuts("2 ������ �� �����������");
          if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 ����������:");

            MmiGotoxy(0,5);
            if(dose_dlvr != vBIG_P)
                MmiPrintf("�=%8.2f ��   ",dose_dlvr);
            MmiPrintf("��� ��������� ");
            MmiGotoxy(15,5);   MmiPrintf("�=%8.2f ��   ",-(s_MVD[0].MassT+s_MVD[1].MassT));
          }

            MmiGotoxy(0,6);    MmiPuts(kran);
         sw_mmi=190;


         Out_en_pmp = OUT3;  // �����
      // Out_en_pmp = 0;  // �����

         break;
       }
       else if(key== '2') // 2  �����  ���
       {

         flag_rcv=1;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         MassStamp=s_MVD[0].MassI;
         MassStamp2=s_MVD[1].MassI;
         VolStamp=s_MVD[0].VolI;
         VolStamp2=s_MVD[1].VolI;
         dose_dlvr=0;

         PageD=0;

         PageD=0;
         f_prepare_t ( &adate00);
m_m6:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts("   ���� 2.����� ���.");

            f_prn_MassSt_rcv();
            MmiGotoxy(0,2);    MmiPuts("1 ����� ���� ���");
            MmiGotoxy(0,3);    MmiPuts("2 ����� ��� ����");
          if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 ����������:");

            MmiGotoxy(0,5);
            if(dose_dlvr != vBIG_P)
                MmiPrintf("�=%8.2f ��   ",dose_dlvr);
            MmiPrintf("��� ��������� ");
            MmiGotoxy(15,5);   MmiPrintf("�=%8.2f ��    ",s_MVD[0].MassT+s_MVD[1].MassT);
          }

            MmiGotoxy(0,6);    MmiPuts(kran);


         Out_en_pmp = OUT3;  // �����
      // Out_en_pmp = 0;  // �����
         sw_mmi=200;
         break;
       }
       else if(key== '*')    //  Sht_1 �������
       {
        Flag_check = 1;
        flag_rcv=0;
        f_wr_evt(evt_verify);
        sw_mmi=230;
        break;
       }
       else if(key== '3') //  3  �������� ��� �����
       {
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0); MmiPuts("�����/������ ��� ��� �����");
         MmiGotoxy(0,6);    MmiPuts(kran_ch);

         flag_v2=0;
         OUT_VAR=OUT8 + GAS1 + OUT2 + OUT1 ;

         time_t_snd=TimeStamp;

     MVD_t_rslt[0]=0;
     MVD_t_rslt[1]=0;

 //                                              |- bidirectional flow
 //                                              |
     f_MVD_WR((int)0,(int)MVD_WR_I,(int) 17,(int)2,(long int) 0,(float)0);
         sw_mmi=205;
     time_t_snd=TimeStamp;

     f_wr_evt(evt_NCNT_on);
         break;
       }
       else if(key== '6') // 6 ���������,����.,������
       {
m_m4:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_den_t();
         flg_ch=0;
         sw_mmi=122;
         break;
       }
       else if(key== '7') // 7 ����������� ���������� ������
       {
m_m7:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

   MmiGotoxy(0,0); MmiPrintf(" ��������� ���������� ������:");
//   MmiGotoxy(0,1); MmiPrintf("    I7017C, �������� ���");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625


   MmiGotoxy(0,4); MmiPrintf(" ��������� ���������� ������:");

  _fmemset( &ADC_c[0],0xff,sizeof(ADC)); // ������� ������ ������
  INP_VAR_c=0xffff;
         sw_mmi=25;
         break;

       }
       else if(key== '8') // 8 ������ sw
       {
m_m8:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

      MmiGotoxy(0,0);   MmiPrintf("   VER %s",sw_ver);
      MmiGotoxy(0,2);   MmiPrintf("   MD5 counting ...");
      MmiGotoxy(0,6);   MmiPuts(" ESC   - ������� � ����");
         tm_md=TimeStamp;
         sw_mmi=271;
         //sw_mmi=-1;
         break;

       }
       else if(key== '9' )//  9  ��������� �������
       {
m_m9:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 9.��������� �������.");
            MmiGotoxy(0,1);    MmiPuts("1 ��������� ��������� �������");
            MmiGotoxy(0,2);    MmiPuts("2 ��������� ����� �. �������");
  //        MoveToXY(0,4);   MmiPrintf("��������� �����:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("��������� ������:    %.6f",s_MVD[0].f);
          //  MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1f;
         sw_mmi=125;
         break;
       }
 //------------------------------------------
       else if(key== '0') // 0 ����������� ���������� �������
       {
m_m0:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         flag_v2=0;
   MmiGotoxy(0,0); MmiPrintf(" ��������� ���������� �������:");
   MmiGotoxy(0,2); MmiPrintf(" 1 ...8 - �������� ��������� ");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625

         OUT_VAR_c=0xffff;
         sw_mmi=27;
         PageD=3;
         break;

       }

       else if(key== '4') // 4  �������� ������� �������
       {
m_m2:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

            i= f_get_max_n_arch();
            ar_str_ptr=f_get_fst_stor();
            MmiGotoxy(0,0);    MmiPuts(" ���� 4.������ �������.");
            MmiGotoxy(0,1);    MmiPrintf("%4d  ",i);
            j=i%100;
            if((j<=20)&& (j>5))
              MmiPrintf("�������");
            else
            switch(i%10)
            {
             case 1:
             MmiPrintf("������");
             break;

             case 2:
             case 3:
             case 4:
             MmiPrintf("������");
             break;

             case 0:
             case 5:
             case 6:
             case 7:
             case 8:
             case 9:
             MmiPrintf("�������");
             break;
            }

   tdat = localtime( &ar_str_ptr->time );
//   MmiPrintf(" � %02d.%02d.%02d %02d:%02d:%02d",
//   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
   MmiPrintf(" � %02d.%02d.%02d",
   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100);

            MmiGotoxy(0,2);    MmiPuts(" �������� ������� �������");
            MmiGotoxy(0,3);    MmiPuts("1  �� ����");
            MmiGotoxy(0,4);    MmiPuts("2  �� ������ ������");
            MmiGotoxy(0,5);    MmiPuts("3  ��������� ������");
        //    MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

         PassW=0;
         sw_mmi=140;
         break;
       }
       else if(key== '5') // 5  ��������� �������
       {
m_m3:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 5.��������� �������.");
//            MmiGotoxy(0,1);    MmiPuts("1  ������ ���������");
            MmiGotoxy(0,1);    MmiPuts("1  ��������� �������� ���");
            MmiGotoxy(0,2);    MmiPuts("2  ����������  ���������");
            MmiGotoxy(0,3);    MmiPuts("3  ��������/���� ����������");
            MmiGotoxy(0,4);    MmiPuts("4  ������ �������");
            MmiGotoxy(0,5);    MmiPuts("5  �����, ����");
          //  MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

         sw_mmi=150;
         PassW=0;
       }
       break;


 /*========================================*/
     case 181:

       if((key==ESC)||(key==ENTER))  // ������� �� ��������� ��������
       {
         goto m0_f1;
       }
       break;

 /*========================================*/
    case 271:/* �������� ������� ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
           goto m0_f1;
         }
         if( (f_timer(tm_md,(long int)1000 )) | fl_md_fst )
         {
           f_md5(1);
           sw_mmi=181;
         }
         break;
 /*========================================*/
    case 121: // // ���� ������ �� ��������� ������
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
 m121:
          switch(pass_ret)
          { // ������ �� ������
          case 0:  goto par_out14;
          case 1:  goto m_m9;
          case 2:  goto m_m9;
          default:
                goto main_menu;
          }
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%ld",&ltmp);
          if(ltmp == Password)
                PassW=Password;
          else goto m_pass;
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          switch(pass_ret)
          { // ������ ������ ���������
          case 0:  goto par_out14;
          case 1:
                sw_mmi=125;
                goto m_m9_1;
          case 2:
                sw_mmi=125;
                goto m_m9_2;
          default:
                goto main_menu;
          }
        }
       else if(key==DATA_ESC)
        {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          goto m121;
        }

 /*========================================*/
    case 122:
 //  ����������� ���������,�����������,�������
 //  ������� ��������.
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
         goto main_menu;
       }
       else if(key==PASS)
       {
         f_prn_den_t();
       }
       else if(key==F1)
       {
          MVD_fn[0]=MVD_WR_C;
          s_MVD[0].r_addr=56; // Reset mass total
/*
          s_MVD[0].r_addr=56; // Reset mass total
          s_MVD[0].r_addr=04; // Reset all inventories
          s_MVD[0].r_addr=57; // Reset volume totales
*/
          s_MVD[0].i=1;
       }
       else if(key==Sht_F1)
       {
        if(flg_ch==2)
        {
          MVD_fn[0]=MVD_WR_C;
          s_MVD[0].r_addr=04; // Reset all inventories
/*
          s_MVD[0].r_addr=56; // Reset mass total
          s_MVD[0].r_addr=04; // Reset all inventories
          s_MVD[0].r_addr=57; // Reset volume totales
*/
          s_MVD[0].i=1;
        }
       }
       else if(key==Sht_F2)
       {
        if(flg_ch==1) flg_ch++;
        else flg_ch=0;
       }
       else if(key==Sht_F3)
       {
        if(flg_ch==0) flg_ch++;
        else flg_ch=0;
       }
       else flg_ch=0;
       break;
 /*========================================*/
 /*========================================*/
    case 125:
 //  ���� 9.��������� �������.
       if((key==ESC)||(key==ENTER) )    /* ������� � ���� */
       {
         sw_fst=0;
         ff_serv=NULL;
         goto main_menu;
       }

       if((key=='1')&&(Flag_f_corr!=0))
       {

          if(PassW != Password)
          {
           pass_ret=1;
           goto m_pass;
          }

m_m9_1:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptyPage); // ���� ��������
          f_clr_scr_MMI();
          MmiPuts("������� ��������� �����:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-����,\"SHT-4\"-��.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - �������");
          if(flag_mass!=0)
          {
           sprintf( fst_str,"%.6f",k_mv_tmp);
           fst_n=9;
          }
          else
          {
           sprintf( fst_str,"%8.2f",k_mv_tmp);
           fst_n=9;
          }
          sw_fst=1;
          MmiGotoxy(10,3);
          break;
       }
       if((key=='2')&&(Flag_f_corr!=0))
       {
          if(PassW != Password)
          {
           pass_ret=2;
           goto m_pass;
          }
m_m9_2:
          MmiGotoxy(0,1);
          SetDisplayPage(EmptyPage); // ���� ��������
          f_clr_scr_MMI();
//        MmiPuts("������� ��������� ������:" );
          MmiPuts("������� ���� ����.����.��/�:" );
          k_mv_tmp=k_v_flow;
          flag_mass=0;
          goto m_m9_1_1;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%f",&k_mv_tmp);

         if(flag_mass)
         {
          if((k_mv_tmp<0.8)||(k_mv_tmp>1.2) )
                goto m_m9_1;
         }
         else
         {
          if(k_mv_tmp<0) goto m_m9_2;
         }

      // ��������� �������� � k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=279; // ��������� �����.

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
//         s_MVD[0].r_addr=281; // ��������� ������.
//         chg_nn_par=Par_VF;

           s_MVD[0].r_addr=195; // ���� ����.�������
           chg_nn_par=Par_MC;

           chg_old=k_v_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          MVD_fn[0]=MVD_WR_F;;
          s_MVD[0].f = k_mv_tmp;
          goto m_m9;
        }
       else if(key==DATA_ESC)
        {
          goto m_m9;
        }

       break;
 /*========================================*/
 /*========================================*/
    case 130: // //  1  ��������� ������� ���

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  �� ��������� ����. ���
       {
m_m1_1:
  //     mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_lst_hour();
         sw_mmi=131;
       }
       else if(key== '2')  // 2  �� ��������� 5 �����
       {
m_m1_2:
  //     mmi_str=0;

//printf("\r\n===0===");
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

         f_prn_5day();
         sw_mmi=131;
       }
       else if(key== '3')  // 3  �� ��������� ����
       {
m_m1_3:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ���� ��������� ��������");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=134;
       }
       else if(key== '4')  //4  �� ������� ������
       {
m_m1_4:
    //   mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_current();
         sw_mmi=132;
       }
       else if(key== '5')  //5  �������� ���������� ����
       {
m_m1_5:
      // mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("  �������� ���������� ����");
           MmiGotoxy(0,1);    MmiPuts("       ���.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.00.00");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)ahour00.hour,(int)ahour00.min,(int)ahour00.sec );
          fst_n=9;
          sw_fst=1;
          sw_mmi=133;
       }
       break;
 /*========================================*/
    case 131:
 //  ����������� ��������� ������� ���.
 // �� ��������� ����. ��� .
       if((key==ESC)||(key==ENTER))    /* ������� � ����������� ���� */
       {
         goto m_m1;
       }
       break;
 /*========================================*/
    case 132:
 //  ����������� ��������� ������� ���.
 //  ������� ��������.
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
         goto m_m1;
       }
       else if(key==PASS)
       {
         f_prn_current();
       }
       break;
 /*========================================*/
    case 133:
 //  ����������� ���������� ����.
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m1;
       }
       else if(key==DATA)
        {
            hour= ahour00.hour;
            min = ahour00.min ;
            sec = ahour00.sec ;
          sscanf(fst_str,"%d.%d.%d",&hour,&min,&sec);
   // printf("\n\r %d.%d.%d ",hour,min,sec);
          if((hour<0)||(hour > 23)) goto m_m1_5;
          if((min<0)|| (min > 59))  goto m_m1_5;
          if((sec<0)|| (sec > 59))  goto m_m1_5;
          i=0;
          if(ahour00.hour != hour)
          {
            ahour00.hour= hour;
            i=1;
          }
          if(ahour00.min != min);
          {
             ahour00.min = min ;
            i=1;
          }
          if(ahour00.sec != sec)
          {
            ahour00.sec = sec ;
            i=1;
          }
          if(i)
           if(f_wrt_eee()<0)
           {
              MmiGotoxy(0,5);   MmiPuts("������ ��� ���������� ������");
              sw_mmi=131;
           }
           else goto m_m1;

          break;
        }
       break;
 /*========================================*/
    case 134:
 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m1;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m1_3;
          if((month<1)|| (month > 12))  goto m_m1_3;
          if((day<1)|| (day > 31))  goto m_m1_3;


             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // ���� �������
            // ����������� �������� �������
            SetDisplayPage(EmptyPage);
            f_clr_scr_MMI();
            f_prn_date();
            sw_mmi=131;

          break;
        }
       break;
 /*========================================*/
    case 140: // 2  �������� ������� �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }
        else if (key==DEL)
        {

          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // ������ ��������
          MmiGotoxy(0,1);    MmiPuts(" 1 - ������������");
          MmiGotoxy(0,2);    MmiPuts(" 6 - ����� �� ��������� � ��");
          MmiGotoxy(0,3);    MmiPuts("    (���  �������)");
          MmiGotoxy(0,5);    MmiPuts("ESC   ������");
          sw_mmi=142;
          break;
        }
       else if(key== '1')  //1  �� ����
       {
m_m2_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ���� ������ ������� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=143;
          break;
       }
       else if(key== '2')  //2  �� ������ ������
       {
m_m2_2:
          max_par= f_get_max_n_arch();
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("������� ����� ������:" );
          sprintf( fst_str,"%d",max_par);
          fst_n=4;
          sw_fst=1;
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ���� ��������
          break;
       }
       else if(key==DATA)
        {
          sscanf(fst_str,"%d",&i);
          if(i<1) { goto m_m2_2;}
          else if(i>max_par) { goto m_m2_2;}
          mmi_prm=i-1;
          goto m_m2_3v;
        }
       else if(key==DATA_ESC)
        {
          goto m_m2;
        }
       else if(key== '3')  //3  ��������� ������
       {
m_m2_3:
         max_par= f_get_max_n_arch();
         mmi_prm=max_par-2;

m_m2_30:
         if(mmi_prm>(max_par-1))
            mmi_prm=max_par-2;
         if(mmi_prm<0) mmi_prm=0;


m_m2_3v:
         f_clr_scr_MMI();
         SetDisplayPage(EmptyPage);    // ������ ��������

   //----------------
        ar_str_ptr= f_get_astr(mmi_prm);
        k=f_prn_mmi_a(ar_str_ptr,0);
        if(k>=3)
        {
          k_ext1=0;
          k_ext=7;
          goto m_m2_32;
        }
  if(mmi_prm==(max_par-1)) goto m_m2_32;

        ar_str_ptr= f_get_astr(mmi_prm+1);
        k_ext=f_prn_mmi_a(ar_str_ptr,k+1);
        k_ext1=0;
  if(mmi_prm==(max_par-2)) goto m_m2_32;

        if(k_ext<4)
        {
          ar_str_ptr= f_get_astr(mmi_prm+2);
          k_ext=f_prn_mmi_a(ar_str_ptr,k_ext+1);
          k_ext1=1;
        }
   //----------------
m_m2_32:
        MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");

        sw_mmi=141;
       }
       break;
 /*========================================*/
    case 141:/*�������� 2 ������� �������*/
         if(key==ESC)    /* ������� � ���� ������ ����� ��� ���������*/
         {
          goto m_m2;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=2)
           {
            mmi_prm -=2;
            goto m_m2_3v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m2_3v;
           }
         else if (key== F3 )
         {
           max_par= f_get_max_n_arch();
           if(mmi_prm <= (max_par-2))
           {
            if(k_ext1==0)
             if(k_ext<=5)
               mmi_prm +=2;
             else
               mmi_prm +=1;
            else
             if(k_ext<=5)
               mmi_prm +=3;
             else
               mmi_prm +=2;
            if(mmi_prm >= max_par)
              mmi_prm=max_par-1;
            goto m_m2_3v;
           }
         }
    break;
 /*========================================*/
    case 142:/* ����� �� ��������� */
             /* ������� � ��������� */
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
         {
          goto m_m2;
         }
         else if(key== '1' )
         { //  1 - ������������
           f_wr_evt(evt_res);
           _asm cli
           _asm hlt
         }
         else if(key== '6' )
         {// 6 - ����� �� ��������� � ��
            f_wr_evt(evt_exit);
            return 1; // ����� �� ��������� *.exe � ��
         }
         break;
 /*========================================*/
    case 143:

 //  ���� ����
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m2;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m2_1;
          if((month<1)|| (month > 12))  goto m_m2_1;
          if((day<1)|| (day > 31))  goto m_m2_1;

             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // ���� �������

m_m2_1_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   ����� ������ ������� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ���.");
        // MmiGotoxy(0,2);    MmiPuts("        08.01");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d",(int)adate00.hour,(int)adate00.min );
          fst_n=6;
          sw_fst=1;
          sw_mmi=144;
       }
          break;

 /*========================================*/
    case 144:
 //  ���� �������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m2_1;
       }
       else if(key==DATA)
        {
          hour=(int)adate00.hour;
          min=(int)adate00.min;

          sscanf(fst_str,"%d.%d",&hour,&min);
          if((min<0)|| (min > 59))  goto m_m2_1_1;
          if((hour<0)|| (hour > 23))  goto m_m2_1_1;


             adate00.min = min;
             adate00.hour = hour;
             adate00.sec = 0;
            // ����� �������

            SetDisplayPage(EmptyPage);
            f_clr_scr_MMI();

         ltime1=f_get_time_t(&adate00);
         k=f_get_dat_n(ltime1);
         if(k<0)
         {
           ltime2=f_get_time(f_get_fst_stor());
           if(ltime1<=ltime2)
           {
             k=0;
           }
           else k=f_get_max_n_arch();
         }
         mmi_prm=k;
         max_par= f_get_max_n_arch();
         goto m_m2_30;
        }
         break;
 /*========================================*/
    case 150: // 3  ��������� �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }

       else if(key== '1') //  1  ��������� �������� ���
       {
         f_prepare_t ( &adate00);
m_m1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ��������� �������� ���");

            MmiGotoxy(0,1);    MmiPuts("1  �� ��������� ����. ���");
            MmiGotoxy(0,2);    MmiPuts("2  �� ��������� 5 �����");

            MmiGotoxy(0,3);    MmiPuts("3  �� ��������� ����");
            MmiGotoxy(0,4);    MmiPuts("4  �� ������� ������");
            MmiGotoxy(0,5);    MmiPuts("5  �������� ���������� ����");
       //    MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

         sw_mmi=130;
         break;
       }

       else if(key== 'A')  // 1  ������ ���������
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_2:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_drv_list_MMI(&mmi_str);
         sw_mmi=22;
       }
       else if(key== '2')  // ����������  ���������
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_3:
         SetDisplayPage(EmptyPage);  // ������ �����
         f_clr_scr_MMI();
         f_drv_stat_MMI(&mmi_str);
         pass_cnt=0;
         sw_mmi=23;
       }
       else if(key== '3')   //  3  ��������/���� ����������
       {
m_m3_3:
        // ������� � ���� ������ ����� ��� ��������� ����������
//          SetDisplayPage(11);
          sw_mmi=11;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� ������ ������ ���������");
            MmiGotoxy(0,2);    MmiPuts("1...6 ������ ����������");
//            MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

          break;
       }
       else if(key== '4')   //  4  ������ �������
       {
m_m3_4:
         SetDisplayPage(EmptyPage);  // ������ �����
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" ���� 5.4.������ �������. ");
            MmiGotoxy(0,1);    MmiPuts("1  ��������� �����������");
            MmiGotoxy(0,2);    MmiPuts("2  ��������� �����������");
            MmiGotoxy(0,3);    MmiPuts("3  ������ �����������");
            MmiGotoxy(0,4);    MmiPuts("4  ����� ICP/RTU �������");
            MmiGotoxy(0,5);    MmiPuts("5  ������ ��������� �������");
//            MmiGotoxy(0,6);    MmiPuts("ESC  �������");
                        f_d_ESC();

         sw_mmi=160;
          break;
       }
       else if(key== '5')   //  5  �����, ����
       {
m_m3_5:
         f_prepare_t ( &adate00);
         adate11=adate00;
         SetDisplayPage(EmptyPage);  // ������ �����
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      ������� ���� ");
           MmiGotoxy(0,1);    MmiPuts("      ����.���.���");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("������� ���/���.����� ��������");
else                          MmiPuts("������� ���/���.����� �������");

/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ������
                              MmiPuts("      ������ �����");
     else                     MmiPuts("      ������ �����");
*/
            MmiGotoxy(0,4);   MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);   MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);   MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=165;
          break;
       }
       break;
 /*========================================*/
    case 160: // M3.4  ������ �������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto m_m3;
       }
       else if(key== '1') //  1  ��������� �����������
       {
         max_par=10;
         mmi_prm=0;

m_m3_4_1v:

         if(ff_serv==NULL)
         {
          SetDisplayPage(EmptyPage);
          f_clr_scr_MMI();
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");
          sw_MMI_cur=0; // ������ MMI
          sw_mvd_m1=mmi_prm+20;  // ���.��������
          sw_MMI_lim=6; // �������� ������
          MMIDens=-1;
          MMITemp=-300;
          ff_serv=f_MVD_M2;
          sw_mmi=171;
         }
         else
          sw_mmi=173;
         break;
       }

       else if(key== '2') //  2  ��������� �����������
       {
         max_par=17;
         mmi_prm=0;

m_m3_4_2v:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");

         if(ff_serv==NULL)
         {
          sw_MMI_cur=0; // ������ MMI
          sw_mvd_m1=mmi_prm+20;  // ���.��������
          sw_MMI_lim=6; // �������� ������

          ff_serv=f_MVD_M1;
          sw_mmi=172;
         }
         else
          sw_mmi=174;
         break;
       }
       else if(key== '3') // 3  ������ �����������
       {
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,6);    MmiPuts("ESC,ENTER  �������");
         sw_mvd_m1=0;
         ff_serv=f_MVD_M3;
         sw_mmi=180;

         break;

       }

       else if(key== '5') //  5  ������ ������������ �������
       {
         mmi_str=0;
         max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
m20_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_mod_list_MMI(&mmi_str);
         sw_mmi=21;
       }
       else if(key== '4')  // 4  ����� ICP/RTU �������
       {
m20_4:
          f_clr_scr_MMI();
          MmiGotoxy(1,1);
          MmiPuts("������� ����� ����� : " );
          sprintf( fst_str,"%2d",mmi_com);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(13,3);
          SetDisplayPage(15);
          break;
       }
       else if(key== DATA )
       {
          sscanf(fst_str,"%d",&mmi_com);  // ����� COM
          if((mmi_com>0)&&(mmi_com<4)) licp_port=mmi_com;
          else
          {
            if(mmi_com<1)  mmi_com=1;
            else if (mmi_com>3)  mmi_com=3;
            goto m20_4;
          }

          if(ComProt[mmi_com]==0)
          {
            licp_sw=1;
            ff_serv=f_look_ICP;
            flag_print_licp=0;
            LICP_Rqst.timeout=ToutLicpScan;
            licp_crc_flag=LICP_Rqst.CRC_flag;
          }
          else
          {
            licp_sw=1;
            ff_serv=f_look_RTU;
            flag_print_licp=0;
            LICP_Rqst_RTU.timeout=ToutLicpScan;
          }

       f_clr_scr_MMI();
       SetDisplayPage(EmptyPage);

       if(ComProt[mmi_com]==0)
       {
         MmiGotoxy(0,0);     MmiPrintf("ICP COM%d: ������� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d,���� CRC=%d",licp_amax,LICP_Rqst.CRC_flag);
       }
       else
       {
         MmiGotoxy(0,0);     MmiPrintf("RTU COM%d: ������� %d ��",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("����.��� %d",licp_amax);
       }

       MmiGotoxy(0,6);  MmiPuts("  Enter - ����������");
       sw_mmi=24;
       break;
       }
       else if(key==DATA_ESC)
        {
          goto m_m3_4;
        }
       break;
 /*========================================*/
    case 165:

 //  ���� ���� ��� ���������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m3;
       }
       else if(key==DATA)
        {
          year=(int)(adate00.year+2000);
          month=(int)adate00.month;
          day=(int)adate00.day;

          sscanf(fst_str,"%d.%d.%d",&day,&month,&year);
          if((year<2000)||(year > 2100)) goto m_m3_5;
          if((month<1)|| (month > 12))  goto m_m3_5;
          if((day<1)|| (day > 31))  goto m_m3_5;

             adate00.year = year-2000 ;
             adate00.month = month;
             adate00.day = day;
            // ���� �������
           if((adate00.year  != adate11.year ) ||
              (adate00.month != adate11.month) ||
              (adate00.day   != adate11.day  ) )
           {

// printf("\n\r %02d.%02d.%02d" ,day,month,year-2000);

            f_wr_evt(evt_none);
            SetDate( year, month, day);

            WriteNVRAM((int)nr_year  ,(int)(year-2000));
            WriteNVRAM((int)nr_month ,(int)month  );
            WriteNVRAM((int)nr_day   ,(int)day    );
            init_win_sum(0);
            f_wr_evt(evt_ch_date);
            adate11=adate00;
//          printf("\n\r Date have changed ");
           }

m_m3_5_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      ������� ����� ");
           MmiGotoxy(0,1);    MmiPuts("       ��� ��� ���");
        // MmiGotoxy(0,2);    MmiPuts("         08.01.00");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("������� ���/���.����� ��������");
else                          MmiPuts("������� ���/���.����� �������");
/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - ������
                              MmiPuts("      ������ �����");
     else                     MmiPuts("      ������ �����");
*/





            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - ��������");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ����");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - ��������");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)adate00.hour,(int)adate00.min,(int)adate00.sec);
          fst_n=9;
          sw_fst=1;
          sw_mmi=166;
       }
          break;

 /*========================================*/
    case 166:
 //  ���� �������
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* ������� � ���� */
       {
         goto m_m3_5;
       }
       else if(key==DATA)
        {
          hour=(int)adate00.hour;
          min=(int)adate00.min;
          sec=(int)adate00.sec;

          sscanf(fst_str,"%d.%d.%d",&hour,&min,&sec);
          if((min<0)|| (min > 59))  goto m_m3_5_1;
          if((sec<0)|| (sec > 59))  goto m_m3_5_1;
          if((hour<0)|| (hour > 23))  goto m_m3_5_1;

             adate00.min = min;
             adate00.hour = hour;
             adate00.sec = sec;
            // ����� �������
           if((adate00.hour  != adate11.hour ) ||
              (adate00.min   != adate11.min) ||
              (adate00.sec   != adate11.sec  ) )
           {
//          printf("\n\r Time have changed ");
            f_wr_evt(evt_none);
            SetTime( adate00.hour, adate00.min,adate00.sec);
    WriteNVRAM((int)nr_hour   ,(int)hour   );
    WriteNVRAM((int)nr_min    ,(int)min    );
    WriteNVRAM((int)nr_sec    ,(int)sec    );
            init_win_sum(0);
            f_wr_evt(evt_ch_time);
           }

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

         goto m_m3;
        }
         break;
 /*========================================*/
 /*========================================*/
    case 21:  // �������� ������ �������

       max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
       if((key==ESC)||(key==ENTER))   /* ������� � ���� ������ ����� ��� ���������*/
       {
          goto m_m3_4;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_1;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_1;
       }
       break;
 /*========================================*/
    case 22: // �������� ������ ���������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� ������ ����� ��� ���������*/
       {
        goto m_m3;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_2;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_2;
       }
       break;
 /*========================================*/
    case 23: // �������� ���������� ���������

       if((key==ESC)||(key==ENTER))    /* ������� � ���� ������ ����� ��� ���������*/
       {
        goto m_m3;
       }
       else if((key== F2 )&& (mmi_str>0) )
       {
        mmi_str -=n_mmi_str_3;
        goto m20_3;
       }
       else if((key== F3 )&& (mmi_str < (max_par-n_mmi_str_3)) )
       {
        mmi_str +=n_mmi_str_3;
        goto m20_3;
       }
       else if (key==Sht_ESC)
        {  // ��������� ��������� ������
           for(i=0;i<icp_lst_max;i++)
           {
             ICPl_DEV=ICP_dd[i];
             if(ICPl_DEV!=NULL)
             {
      //      ICPl_DEV->n_transaction=0;
              ICPl_DEV->n_timeout_error=0;
              ICPl_DEV->n_CRC_error=0;
             }
           }
        }
       else //PASS
       {
         pass_cnt++;
         if((pass_cnt & 0xf) == 0 )
           f_drv_stat_MMI(&mmi_str);
       }
       break;
 /*========================================*/
    case 24: // ����������� ������������ �����
       if((key==ESC)||(key==ENTER))
       {
           goto m_m3_4; //  4  ������ �������
       }
       else //PASS
       {
          MmiGotoxy(0,3);  MmiPrintf("��������   %3d",licp_addr);
          MmiGotoxy(0,4);  MmiPrintf("���������� %3d",licp_fnd);
       }
       break;
 /*========================================*/
    case 25: // ����������� ���������� ������

       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }
       else // PASS
       {

   MmiGotoxy(0,1); MmiPrintf(" ��������     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
   MmiGotoxy(0,2); MmiPrintf(" ������.���.  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
   MmiGotoxy(0,3); MmiPrintf(" ������.DC24  %8g (In%d)",(float)ADC[2],analog_num[2]-1);

     MmiGotoxy(0,5); MmiPuts(" ��������� ������ ");
     if(INP_VARi & E_S)
       MmiPuts(" 1");
     else
       MmiPuts(" 0");

     MmiGotoxy(0,6); MmiPuts(" ������ ���       ");
     if(INP_VARi & UZA)
       MmiPuts(" 1");
     else
       MmiPuts(" 0");

       }

       break;
 /*========================================*/
    case 26:/* �������� ������� ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
          goto m_main;
         }
         break;
 /*========================================*/

    case 27: // ����������� ���������� �������

       if((key==ESC)||(key==ENTER))
       {
           flag_v2=1;
           PageD=0;
           OUT_VAR=OUT8;
/*========
           OUT_VAR=0;
           if(FL_err==0)
              Out_on(OUT8);
=========*/
           goto m0_f1;
       }
       else if(key== '1')
       {  // ������ �������
        OUT_VAR ^= OUT2;
       }
       else if(key== '2')
       {  // ������ �������
        OUT_VAR ^= OUT1;
       }
       else if(key== '3')
       {  // ��� ��  out4
        OUT_VAR ^= GAS1;
       }
       else if(key== '4')
       {  // ����� PUMP
        OUT_VAR ^= OUT3;
       }
 /*
       else if(key== '3')
       {
          // ������ �������  out7
        OUT_VAR ^= CLP0;
       }
       else if(key== '6')
       {  // ��� ������� out5
        OUT_VAR ^= GAS2;
       }
       else if(key== '7')
       {  // �� �������  LIQ2
        OUT_VAR ^= OUT6;
       }
*/
       else if(key== '8')
       { // �������
        OUT_VAR ^= OUT8;
       }
       f_prn_proc();

    break;

 /*========================================*/
    case 28:  // ���������� ������� :ESC,Enter
         if((key == ENTER) || (key == '1') || (key == F1 ))
         { // ��������� �������
          flag_off = 0;
          Out_off(OUT8);
          flag_uu=1;
          goto m_main;
         }
         if(key==ESC)
         { // �������� ���������� �������
          Out_on(OUT8);
          flag_off = 0;
          flag_uu=1;
          goto m_main;
         }
         break;
 /*========================================*/
    case 171://  1  ��������� �����������
         if((key==ESC)||(key==ENTER)  )
         {
          if((ff_serv==f_MVD_MM2)||(ff_serv==f_MVD_M2) ) ff_serv=NULL;
          goto m_m3_4;
         }
         else if(key== PASS )
         {
//        if ((ff_serv==NULL) && ( (flag_nal==0) || (fl_rd_err!=0) ) )
          if ((ff_serv==NULL) && ( (fl_rd_err!=0) ) )
          {
           fl_rd_err=0;
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������
           MMIDens=-1;
           MMITemp=-300;
           ff_serv=f_MVD_MM2;
          }
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=6)
           {
            mmi_prm -=6;
    //       printf("\n\rmmi_prm=%d",mmi_prm);
            goto m_m3_4_1v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m3_4_1v;
           }
         else if (key== F3 )
         {
           if(mmi_prm <= (max_par-6))
           {
            mmi_prm +=6;
      //     printf("\n\rmmi_prm=%d",mmi_prm);
            goto m_m3_4_1v;
           }
         }
 /*========================================*/
         break;

    case 172://  2  ��������� �����������
         if((key==ESC)||(key==ENTER)  )
         {
          if(ff_serv==f_MVD_M1) ff_serv=NULL;
          goto m_m3_4;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=6)
           {
            mmi_prm -=6;
            goto m_m3_4_2v;
           }
           else
           {
            mmi_prm = 0;
            goto m_m3_4_2v;
           }
         else if (key== F3 )
         {
           if(mmi_prm <= (max_par-6))
           {
            mmi_prm +=6;
            goto m_m3_4_2v;
           }
         }
 /*========================================*/
         break;
 /*========================================*/
    case 173:
         if((key==ESC)||(key==ENTER)  )
         {
          ff_serv=NULL;
          goto m_m3_4;
         }
         if(key==PASS  )
         {
          if(ff_serv==NULL)
          {
           SetDisplayPage(EmptyPage);
           f_clr_scr_MMI();
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������
           MMIDens=-1;
           MMITemp=-300;
           ff_serv=f_MVD_M2;
           sw_mmi=171;
          }
         }
         break;
 /*========================================*/
    case 174:
         if((key==ESC)||(key==ENTER)  )
         {
          ff_serv=NULL;
          goto m_m3_4;
         }
         if(key==PASS  )
         {
          if(ff_serv==NULL)
          {
           SetDisplayPage(EmptyPage);
           f_clr_scr_MMI();
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"���� \"F3\"���� \"ESC\"������");
           sw_MMI_cur=0; // ������ MMI
           sw_mvd_m1=mmi_prm+20;  // ���.��������
           sw_MMI_lim=6; // �������� ������

           ff_serv=f_MVD_M1;
           sw_mmi=172;
          }
         }
         break;
 /*========================================*/
    case 180:

       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
       {
         if(ff_serv==f_MVD_M3) ff_serv=NULL;
            goto m_m3_4;
       }
       break;
 /*========================================*/
    case 190: //  1  ������ ���
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }
/*
       else if(key==F1)   // Help
       {
        f_dsp_H1();
        Ret_cod= sw_mmi;
        sw_mmi=220;
        break;
       }
*/
       else if(key== '1')  // 1  ������ ���� ���
       {
m_m5_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   ������ ���� ���");
         f_prn_MassSt_dlv();

         MmiGotoxy(0,2);       MmiPuts(" ������� ���� �������,��");
      // sprintf( fst_str,"");
         strcpy( fst_str,"");
         fst_n=5;
         sw_fst=1;
         MmiGotoxy(10,4);
         break;
       }
       else if(key==DATA)
        {
          dose_dlvr=-1;
          sscanf(fst_str,"%f",&dose_dlvr);
          if(dose_dlvr<=0) { dose_dlvr=0; goto m_m5_1;}
         flag_dlv_fst=0;
         flag_prn_mass=0;
m_m5_1o:
          dose_A=dose_dlvr;
          sw_mmi=191;
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_m5;
        }
       else if(key== '2')  // 2  ������ �� �����������
       {
m_m5_2:
         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m5_1o;
       }
       else if(key== '3')  // 3 ���������� � �����. �����
       {
         if(flag_prn_mass)
          {
           goto m_m5_1o;
          }
       }
       else f_prn_MassSt_dlv();

       break;
 /*========================================*/
    case 191: //  ������  ���, ����� ������ ������

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

     MmiGotoxy(0,0);
     if(Flag_check == 0)
     {
          if(dose_dlvr != vBIG_P)
             MmiPrintf("������ ���� ��� %g ��",dose_dlvr);
          else
             MmiPrintf("������ ��� ��� ���������");
     }
     else  MmiPuts(str_verify);

      MmiGotoxy(0,6);   MmiPuts("ESC - ���������.");

      sw_dlv_liq=1;
      sw_mmi=193;

m_m5_1d:
          if(flag_prn_mass)
          {
             MassT=-(s_MVD[0].MassT+s_MVD[1].MassT);
             VolT =-(s_MVD[0].VolT+s_MVD[1].VolTd);
              //  ����������� � f_MVD_rd() ��� ������ ������ �� ����������� ������� ����
              //  s_MVD[1].VolTd=s_MVD[1].MassT*1000./s_MVD[0].Dens;
          }
          else
          {
             MassT=0.;
             VolT =0.;
          }

          if(Flag_check == 0)
          {
            MmiGotoxy(0,2);MmiPrintf("�=%6.1f�� �������� �=%6.1f�",MassT,VolT );
          }
          else
          {
            MmiGotoxy(0,2);
            MmiPuts("           ��������          ");

            MmiGotoxy(0,3);
            MmiPrintf("�=%10.3f ��|�=%10.3f � ",MassT,VolT );
          }
          f_prn_proc();
          break;
//===========================================
    case 193: //  ������
       if(key==F2)    // ��������� ��������,�����������
       {
           PageD=0;
       }
       else if(key==F3)    // ��������� ���������,������
       {
           PageD=1;
       }
       else if(key==F1)    // ��������� �������
       {
           PageD=3;
       }
       key=f_dlv_liq(key);
       if(key==ESC)    // ������� � ����
       {
           goto m_m5;
       }
  // ����������� ����� � ���������� �����
       goto m_m5_1d;

 /*========================================*/
    case 200: //  2  �����  ���
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
           goto main_menu;
       }
       /*
       else if(key==F1)   // Help
       {
        f_dsp_H2();
        Ret_cod= sw_mmi;
        sw_mmi=220;
        break;
       }
       */
       else if((key== '1')&&(Flag_check == 0) ) // 1  ����� ���� ���
       {
m_m6_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   �����  ���� ���");
         f_prn_MassSt_rcv();

         MmiGotoxy(0,2);       MmiPuts(" ������� ���� ������ ,��");
      // sprintf( fst_str,"");
         strcpy( fst_str," ");
         fst_n=5;
         sw_fst=1;
         MmiGotoxy(10,4);
         break;
       }
       else if(key==DATA)
        {
          dose_dlvr=-1;
          sscanf(fst_str,"%f",&dose_dlvr);
          if(dose_dlvr<=0) { dose_dlvr=0; goto m_m6_1;}
          flag_dlv_fst=0;
          flag_prn_mass=0;
m_m6_1o:
          sw_mmi=201;
          dose_A=dose_dlvr;
          break;
        }
       else if(key==DATA_ESC)
        {
          goto m_m6;
        }
       else if(key== '2')  // 2  ����� �� �����������
       {
m_m6_2:
         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m6_1o;
       }
       else if(key== '3')  // 3 ���������� � �����. �����
       {
         if(flag_prn_mass)
          {
           goto m_m6_1o;
          }
       }
       else
            f_prn_MassSt_rcv();
       break;
 /*========================================*/
    case 201: //  ����� ���, ����� ������ ������

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

     MmiGotoxy(0,0);
     if(Flag_check == 0)
     {
          if(dose_dlvr != vBIG_P)
             MmiPrintf("    ����� ���� ��� %g ��",dose_dlvr);
          else
             MmiPrintf("  ����� ��� ��� ���������");
     }
     else  MmiPuts(str_verify);

         MmiGotoxy(0,6);   MmiPuts("ESC - ���������.");

         sw_dlv_liq=1;
         sw_mmi=203;


m_m6_1d:
          if(flag_prn_mass)
          {
             MassT=s_MVD[0].MassT+s_MVD[1].MassT;
             VolT =s_MVD[0].VolT+s_MVD[1].VolTd;
              //  ����������� � f_MVD_rd() ��� ������ ������ �� ����������� ������� ����
              //  s_MVD[1].VolTd=s_MVD[1].MassT*1000./s_MVD[0].Dens;
          }
          else
          {
             MassT=0.;
             VolT =0.;
          }

          if(Flag_check == 0)
          {
            MmiGotoxy(0,2);MmiPrintf("�=%6.1f��  ������� �=%6.1f�",MassT,VolT );
          }
          else
          {
              MmiGotoxy(0,2);
              MmiPuts("           �������           ");

              MmiGotoxy(0,3);
              MmiPrintf("�=%10.3f ��|�=%10.3f � ",MassT,VolT );
          }

          f_prn_proc();

          break;
//===========================================
    case 203: //  �����
       if(key==F2)    // ��������� ��������,�����������
       {
           PageD=0;
       }
       else if(key==F3)    // ��������� ���������,������
       {
           PageD=1;
       }
       else if(key==F1)    // ��������� �������
       {
           PageD=3;
       }
       key=f_rcv_liq(key);
       if(key==ESC)    // ������� � ����
       {
           goto m_m6;
       }
  // ����������� ����� � ���������� �����
       goto m_m6_1d;
//-------------------
    case 205:  // �����/������ ��� ��� �����
               // �������� ���������� ������� ����������� ����� MVD[0]

    if( MVD_t_rslt[0]>0)
    { // ������� ����� � ����� ������������

      // Stop totalizers
       MVD_t_rslt[0]=0;
       MVD_t_rslt[1]=0;
       f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,0);
       f_MVD_WR((int)1,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,0);
       sw_mmi=206;
       time_t_snd=TimeStamp;
    }
    if( f_timer(time_t_snd,f_MVD_tim + f_MVD_tim ) )
    {  // ����� �����
        time_t_snd=TimeStamp;
        MVD_t_rslt[0]=1;
        MVD_t_rslt[1]=1;
    }
    break;
//-------------------
    case 206: // �����/������ ��� ��� �����
          // �������� ���������� �������� Totals

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // ��������� ����� FlowM  � ����� ������������
      // FlowM = 0

       MVD_t_rslt[0]=0;
       MVD_t_rslt[1]=0;

       f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,0);
       f_MVD_WR((int)1,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,0);

       sw_mmi=207;
    }
    if( f_timer(time_t_snd,f_MVD_tim + f_MVD_tim ) )
    {  // ����� �����
      MVD_t_rslt[0]=1;
      MVD_t_rslt[1]=1;
    }
    break;
//-------------------
    case 207: // �����/������ ��� ��� �����
          // �������� ��������� ����� FlowM  � ����� ������������

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // �������� ��������� ����� FlowM  � ����� ������������ ���������
      // FlowM = 0
       sw_mmi=210;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      MVD_t_rslt[0]=1;
      MVD_t_rslt[1]=1;
    }
    break;

//-------------------

    case 210: // �����/������ ��� ��� �����

       PageD=3;

       if(key== '1')
       {  // ������ �������
        OUT_VAR ^= OUT2;
        break;
       }
       else if(key== '2')
       {  // ������ �������
        OUT_VAR ^= OUT1;
        break;
       }
       else if(key== '3')
       {  // ��� ��  out4
        OUT_VAR ^= GAS1;
        break;
       }
       else if(key== '4')
       {  // ����� PUMP
        OUT_VAR ^= OUT3;
        break;
       }
       else if(key==ESC)    // ������� � ����
       {
         PageD=0;
         flag_v2=1;
         OUT_VAR = OUT8;
         f_wr_evt(evt_NCNT_off);

         sw_mmi=212;
        // ��������� ����� FlowM ��� ������ ��������
        f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,Cut_Mass[0]);
        f_MVD_WR((int)1,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,Cut_Mass[1]);
        break;
       }
/*
       else if(key==F1)    // ��������� Help
       {
        f_dsp_H3();
        Ret_cod= sw_mmi;
        sw_mmi=220;
        break;
       }
*/
         MmiGotoxy(0,2);  MmiPrintf("�:%5.0f��/�|%5.1f��/�3|%5.1f C",s_MVD[0].FlowM,s_MVD[0].Dens,s_MVD[0].Temp);
         MmiGotoxy(0,3);  MmiPrintf("�:%5.0f��/�|%5.1f��/�3|%5.1f C",s_MVD[1].FlowM,s_MVD[1].Dens,s_MVD[1].Temp);
         f_prn_proc();
//       f_dsp_ncnt();
       break;

//-------------------------------------------
    case 212: // �����/������ ��� ��� �����
          // �������� ��������� ����� FlowM ��� ������ �������� � ����� ������������

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // �������� ��������� ����� FlowM  � ����� ������������ ���������
      goto main_menu;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // ����� �����
      goto main_menu;
    }
    break;
//-------------------------------------------
    case 220: // Out from Help
 /*========================================*/
       if((key==ESC)||(key==ENTER))    /* ������� � ���� */
       {
         switch(Ret_cod)
         {
             //  1  ������ ���
           case 190:  goto m_m5;
           case 200:  goto m_m6;
           case 210:
           case 211:
                      SetDisplayPage(EmptyPage);
                      f_clr_scr_MMI();
                      MmiGotoxy(0,0); MmiPuts("�����/������ ��� ��� �����");
                      MmiGotoxy(0,6); MmiPuts(kran_ch);
                      sw_mmi=Ret_cod;
                      break;
           default:  goto m_main;
         }
       }
       break;
 /*========================================*/
    case 230: // �������

          SetDisplayPage(EmptyPage);
          f_clr_scr_MMI();
         MmiGotoxy(0,0);
         MmiPrintf("  ������� ����������� ");
         sw_pov=1;

         sw_mmi=231;


 /*========================================*/

    case 231: // �������
       if(key==F2)    // ��������� ��������,�����������
       {
           PageD=0;
       }
       else if(key==F3)    // ��������� ���������,������
       {
           PageD=1;
       }
       else if(key==F1)    // ��������� �������
       {
           PageD=3;
       }
       key=f_pov(key);
       if(key==ESC)    // ������� � ����
       {
           sw_pov=0;
           f_wr_evt(evt_verify_e);
           goto m0_f1;
       }

       MmiGotoxy(0,3);
              MmiPrintf("M=%9.3f �� |",s_MVD[0].MassI);  // VolT_id, VolT_int
       MmiGotoxy(15,3);
              MmiPrintf("|�=%9.3f ��",s_MVD[0].MassT);  // VolT_id, VolT_int
       f_prn_proc();
       break;

 /*========================================*/
       default:
       if((key==ESC)||(key==ENTER))  /* ������� �� ��������� �������� */
       {
 m_main:
           SetDisplayPage(ZeroPage);
           sw_mmi=0;
           f_clr_scr_MMI();
           f_prn_begin();
           break;
       }
       break;
    }
    return 0;
}
/*-----------------------------------------*/
void f_before_MMI()
{
    ftmp_naMMI[0]=analog_scale[0]*NA_scale;
    ftmp_naMMI[1]=analog_scale[1]*NA_scale;
    ftmp_naMMI[2]=analog_scale[2]*NA_scale;
}
/*-----------------------------------------*/
void f_after_MMI()
{
    analog_scale[0]=ftmp_naMMI[0]/NA_scale;
    analog_scale[1]=ftmp_naMMI[1]/NA_scale;
    analog_scale[2]=ftmp_naMMI[2]/NA_scale;
}


