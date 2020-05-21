
#define n_mmi_str 7 // количество строк на дисплее MMI
#define n_mmi_str_1 (n_mmi_str-1)
#define n_mmi_str_2 (n_mmi_str-2)
#define n_mmi_str_3 (n_mmi_str-3)
#define n_mmi_str_4 (n_mmi_str-4)

//
//  Файл содержит символьные данные в DOS кодировке символов.
//  Для отображения на дисплее MMI необходимо перекодировать в
//  кодировку Windows (выполняется командой dos_win.exe в .bat)
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
char kran_ch[]="ESC Возврат, 1..4 изм.";
char kran1[]="ESC Возврат , F1-краны";
char kran[]="ESC Возврат";

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
char str_ESC[]="ESC  Возврат";
char str_verify[]="    Поверка расходомера   )   ";
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
  MmiGotoxy(1,1);  MmiPrintf("  Система учета приема и");
  MmiGotoxy(1,2);  MmiPrintf("отпуска СУГ на автоцистерне");
  MmiGotoxy(23,6);  MmiPrintf("9-Откл.");

    if(PageD==0)
    {
     MmiGotoxy(0,3) ; MmiPrintf("Масса       :");
     MmiGotoxy(0,4) ; MmiPrintf("Плотность   :");
     MmiGotoxy(0,5) ; MmiPrintf("Давление    :");
    }
    else if(PageD==1)
    {
     MmiGotoxy(0,3) ; MmiPrintf("Давление    :");
     MmiGotoxy(0,4) ; MmiPrintf("Напр.АКБ    :");
     MmiGotoxy(0,5) ; MmiPrintf("Напр.ИП     :");
    }
    else  if(PageD==2)
    {
     MmiGotoxy(0,3) ; MmiPrintf("Масса MVD1  :");
     MmiGotoxy(0,4) ; MmiPrintf("Масса MVD2  :");
     MmiGotoxy(0,5) ; MmiPrintf("Всего       :");

    }
  }
}
//-------------------------------------
void  f_dsp_ncnt()
{
  MmiGotoxy(1,1); MmiPrintf(" Расход ПФ  %7.1f  кг/ч  ",s_MVD[0].FlowV*3.6*s_MVD[0].Dens);
  MmiGotoxy(1,2); MmiPrintf(" Плотность  %8.2f кг/м3",s_MVD[0].Dens);
  MmiGotoxy(1,3); MmiPrintf(" Давление   %8.2f МПа", s_MVD[0].Press);
  MmiGotoxy(1,4); MmiPrintf(" Температура  %6.2f С  ", s_MVD[0].Temp);
  MmiGotoxy(1,5); MmiPrintf(" Напр.АКБ   %8.2f V  ", s_MVD[0].Volt_A);
}
//-------------------------------------
void  f_dsp_H1()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   Отпуск СУГ");
         MmiGotoxy(17,6); MmiPuts(str_ESC);

  MmiGotoxy(0,1); MmiPrintf("Горловины:Б-пары,В-жидкая фаза");
  MmiGotoxy(1,2); MmiPrintf(" Откройте краны: ");
  MmiGotoxy(1,3); MmiPrintf(" Б, Г, Д, Е , З");
  MmiGotoxy(1,4); MmiPrintf(" Закройте краны: ");
  MmiGotoxy(1,5); MmiPrintf(" А, В, Ж  ");
}
//-------------------------------------
void  f_dsp_H2()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0)   ;    MmiPuts("   Прием  СУГ");
         MmiGotoxy(17,6); MmiPuts(str_ESC);

  MmiGotoxy(0,1); MmiPrintf("Горловины:А-жидкая фаза,Б-пары");
  MmiGotoxy(1,2); MmiPrintf(" Откройте краны: ");
  MmiGotoxy(1,3); MmiPrintf("  В, Г, Д, Ж  ");
  MmiGotoxy(1,4); MmiPrintf(" Закройте краны:");
  MmiGotoxy(1,5); MmiPrintf("  А, Б, Е, З  ");

}
//-------------------------------------
void  f_dsp_H3()
{
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

         MmiGotoxy(0,0); MmiPuts("Прием/Отпуск СУГ без учета");
         MmiGotoxy(17,6); MmiPuts(str_ESC);


  MmiGotoxy(0,1); MmiPrintf("Горловины:Б-пары,Г-жидкая фаза");
  MmiGotoxy(1,2); MmiPrintf(" Откройте краны: ");
  MmiGotoxy(1,3); MmiPrintf("  А, Б, Г    (Д-откр.пары)");
  MmiGotoxy(1,4); MmiPrintf(" Закройте краны:");
  MmiGotoxy(1,5); MmiPrintf("  В, Е, Ж, З (Д-закр.пары)");

}
//-------------------------------------
int un_mmi1=1;
int un_mmi2=2;
int un_mmi3=3;
char *list_un_mmi[]={
"",
" Объем,л   " ,  //1
"Сумма,руб  " ,  //2
"Цена,руб/л " ,  //3
"Масса,кг   " ,  //4
"Сумма,руб  " ,  //5
"Цена,руб/кг" ,  //6
};
//-------------------------------------
int CRC_err=0;
//-------------------------------------
void f_prn_CRC_error()
{
 MmiGotoxy(0,2);   MmiPrintf("!Ошибка контрольной суммы   ");
 MmiGotoxy(0,3);   MmiPrintf("!Параметры потеряны         ");
 MmiGotoxy(0,4);   MmiPrintf("!Необходима перенастройка   ");
 MmiGotoxy(0,5);   MmiPuts(s_empty);
 CRC_err=1;
}
//-------------------------------------
void f_prn_proc()
{
//float ftmp;
          if(PageD==0)
          {
      //      MmiGotoxy(0,4);  MmiPuts(" Плотность     |   Расход      ");
      //      MmiGotoxy(0,5);MmiPrintf("%8.2f кг/м3 | %8.1f кг/ч  ",s_MVD[0].Dens,s_MVD[0].FlowM);
              MmiGotoxy(0,4);  MmiPrintf("Ж:%5.0fкг/ч|%5.1fкг/м3|%5.1f C",s_MVD[0].FlowM,s_MVD[0].Dens,s_MVD[0].Temp);
              MmiGotoxy(0,5);  MmiPrintf("П:%5.0fкг/ч|%5.1fкг/м3|%5.1f C",s_MVD[1].FlowM,s_MVD[1].Dens,s_MVD[1].Temp);
          }
          else if(PageD==1)
          {

//          MmiGotoxy(0,4);    MmiPuts(" P1, МПа | Pнп,МПа |  T,град.C");
//          MmiGotoxy(0,5);    MmiPrintf("%8.4f |%8.4f |%8.2f   ",s_MVD[0].Press ,s_MVD[0].PressG,s_MVD[0].Temp);

           MmiGotoxy(0,4);
               MmiPuts(" P1, МПа | Pнп,МПа |  T,град.C");
           MmiGotoxy(0,5);
             MmiPrintf("%8.4f |%8.4f |%8.2f   ",s_MVD[0].Press,s_MVD[0].PressG,s_MVD[0].Temp);
          }
          else if(PageD==3)
          {

     MmiGotoxy(0,4); MmiPuts("Кл.мнш:");
     if( OUT_VAR & OUT2  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy( 9,4); MmiPuts("Кл.блш:");
     if( OUT_VAR & OUT1  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

/*
     MmiGotoxy(18,4); MmiPuts("Кл.блш:");
     if( OUT_VAR & CLP0  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");
*/

     MmiGotoxy(27,4); MmiPuts("Н:");
     if( OUT_VAR & OUT3  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(18,4); MmiPuts("Пар АЦ:");
     if( OUT_VAR & GAS1  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(0,5); MmiPrintf("АКБ=%5.2fV | ИП=%5.2fV",s_MVD[0].Volt_A,s_MVD[0].Volt_DC);

     MmiGotoxy(23,5); MmiPuts("    П:");
     if( OUT_VAR & OUT8  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");
/*
     MmiGotoxy(9,5); MmiPuts("Пар вн:");
     if( OUT_VAR & GAS2  )
       MmiPuts("1 ");
     else
       MmiPuts("0 ");

     MmiGotoxy(18,5); MmiPuts("Ждк вн:");
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
  MmiGotoxy(2,1);  MmiPrintf("Всего отпущено %8.2f кг  ",-(s_MVD[0].MassI+s_MVD[1].MassI-MassStamp-MassStamp2));
}
//-------------------------------------
void f_prn_MassSt_rcv()
{
   MmiGotoxy(0,1);
   if(Flag_check == 0)
    MmiPrintf("  Всего принято %8.2f кг  ",s_MVD[0].MassI+s_MVD[1].MassI-MassStamp-MassStamp2);
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
  MmiGotoxy(2,1);  MmiPrintf(" Система учета приема и");
  MmiGotoxy(1,2);  MmiPrintf("отпуска СУГ на автоцистерне");

  MmiGotoxy(0,3);  MmiPuts(s_empty);
  MmiGotoxy(0,4);  MmiPrintf(" !Инициализация расходомеров");
  MmiGotoxy(0,5);  MmiPuts(s_empty);
   }
   else
#endif
   {
    MmiGotoxy(0,1);   MmiPrintf("                        ");
    MmiGotoxy(0,2);   MmiPrintf("!Ошибка функционирования ");
    MmiGotoxy(0,3);   MmiPrintf("Sht-F1 отображение ошибок");
    MmiGotoxy(0,4);   MmiPrintf("Sht-ESC очистка ошибок   ");
   }
}
//-------------------------------------
void  f_disp_error()
{ // распечатывает ошибки

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
 MmiGotoxy(0,i1++);   MmiPrintf("Ошибка в драйвере %9s:",ICPl_DEV->name );
  }
  else
  {
 MmiGotoxy(0,i1++);   MmiPrintf("Ошибка системы СУГ:           ");
  }
    if(i1 >= n_mmi_str) return;
    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка чтения устройства");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WR_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка записи в устройство");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка Watch Dog");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Drive_ERR)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка в устройстве,%02X", (itmp>>8) & 0xff);
    if(i1 >= n_mmi_str) return;
    }

  }
  else //(i == icp_lst_max)
  {
    if(itmp & EEE_CRC_error)
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка CRC EEPROM процессора");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_erase_error )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка стирания FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Flash_wr_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка записи во FLASH");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_gas_error  )
    {
MmiGotoxy(0,i1++); MmiPrintf("Расх-р не заполнен СУГ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_Z_mass_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Расх-р не обнулил M/V");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_F_dat_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет обновл.данных для журнала");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & exm_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Недолив больше допустимого");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & exp_err )
    {
MmiGotoxy(0,i1++); MmiPrintf("Перелив больше допустимого");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & Gun_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("Насос отключен при наливе");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & WD_pmlan )
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет связи с базой");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & No_flow )
    {
MmiGotoxy(0,i1++); MmiPrintf("Поток прекратился");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & ES_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("Кнопка ES при отпуске/приеме");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & UZA_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("Нет УЗА при отпуске/приеме");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & MVD_cfg )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка конф.расход-ра ");
    if(i1 >= n_mmi_str) return;
    }
    if(itmp & MVD_com )
    {
MmiGotoxy(0,i1++); MmiPrintf("Ошибка зап.расходомера ");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & MotNotStop )==MotNotStop)
    {
MmiGotoxy(0,i1++); MmiPrintf("Сбой насоса при торм.");
    if(i1 >= n_mmi_str) return;
    }
//    if((itmp & DLT_off)== DLT_off )
//    {
//MmiGotoxy(0,i1++); MmiPrintf("Насос выкл. при отпуске");
//    if(i1 >= n_mmi_str) return;
//    }
    if((itmp & VLT_off)== VLT_off )
    {
MmiGotoxy(0,i1++); MmiPrintf("   АКБ разряжена <%5.2f V",v_lvl2);
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & Flow_big)== Flow_big )
    {
MmiGotoxy(0,i1++); MmiPrintf("Обрыв рукава.Скор.>доп.");
    if(i1 >= n_mmi_str) return;
    }
    if((itmp & N380_off)== N380_off )
    {
MmiGotoxy(0,i1++); MmiPrintf(" !Нет питания 380V ");
    if(i1 >= n_mmi_str) return;
    }
  }
   }
   if(i2==0)
   {
    MmiGotoxy(5,2); MmiPrintf("Ошибок нет");
    MmiGotoxy(2,4); MmiPrintf("Enter - продолжить");
   }
}
//-------------------------------------
void f_drv_list_MMI(int *nn)
{ // показать список драйверов устройств
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
    MmiGotoxy(0,0); MmiPuts("        Список драйверов      ");
    MmiGotoxy(0,1); MmiPuts(" N     Имя   Сост. Порт Адр.");
   for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N      Имя   Сост. Порт Адр.");
//                 "xx.....xxxxx  .x    .x   xx"
      MmiPrintf("%2d%10s  %2d    %2d   %02X",i+1,ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr);
    }
}
//-------------------------------
void f_drv_stat_MMI(int *nn)
{ // показать статистику драйверов устройств
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
    MmiGotoxy(0,0);  MmiPuts(" Статистика работы драйверов");
    MmiGotoxy(0,1);  MmiPuts(" N     Имя    Послано  Ошибок");
    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_DEV=ICP_dd[i];
      if(ICPl_DEV==NULL) break;
      MmiGotoxy(0,3+i2);
//         MmiPuts(" N     Имя    Послано  Ошибок");
//                 "xx.....xxxxx  xxxxxxx xxxxxxx"
         MmiPrintf("%2d%10s  %7ld %7ld",i+1,ICPl_DEV->name,ICPl_DEV->n_transaction,ICPl_DEV->n_timeout_error+ICPl_DEV->n_CRC_error);
    }
}
//-------------------------------
//-------------------------------
void f_mod_list_MMI(int *nn)
{ // показать список обнаруженных модулей
int i,i1,i2;
 char str[31];

  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  f_clr_scr_MMI();
  if(i1==0)
  {
    MmiGotoxy(3,2);   MmiPuts("    Список пуст." );
    MmiGotoxy(3,3);   MmiPuts("Используйте поиск для" );
    MmiGotoxy(3,4);   MmiPuts("  обновления списка." );
  }
  else
  {
    MmiGotoxy(0,0);    MmiPuts(" Список обнаруженных модулей  ");
    MmiGotoxy(0,1);    MmiPuts(" N    Имя Порт.Адр.Скор. TT FF");

      i=*nn;
    if(i<0) i=0;
    if((i+n_mmi_str_3) < i1) i1=i+n_mmi_str_3;
    *nn=i;

    for(i2=0;i<i1;i++,i2++)
    {
      ICPl_MOD=f_get_mod_str(i);
      if(ICPl_MOD==NULL) break;
      MmiGotoxy(0,3+i2);

//         MmiPuts(" N    Имя Порт.Адр.Скор. TT FF");
//                 "xx.....xxxx  x xx xxxxxx xx xx"
      MmiPrintf("%2d%9s  %1d %02X %6ld %02X %02X",i+1,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC],ICPl_MOD->TT,ICPl_MOD->FF);
    }
  }
}
//-------------------------------
int mode_prn=1;
void f_prn_current()
{ // показать состояние отпуска на текущий момент
  int year,month,day,hour,min,sec;
 MmiGotoxy(0,0);   MmiPrintf("Tекущее значение счетчика СУГ");
 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
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
 //  Отображение Массы,плотности,температуры,давления
 //  Текущее значение.
 MmiGotoxy(0,0);   MmiPrintf("Текущие показания расходомера");
 MmiGotoxy(0,1);   MmiPrintf(" Масса инв. %10.3f кг",s_MVD[0].MassI);
 MmiGotoxy(0,2);   MmiPrintf(" Масса тек. %10.3f кг",s_MVD[0].MassT);
 MmiGotoxy(0,3);   MmiPrintf(" Расход    %10.2f кг/ч",s_MVD[0].FlowM);
 MmiGotoxy(0,4);   MmiPrintf(" Плотность %10.2f кг/м3",s_MVD[0].Dens);
// MmiGotoxy(0,2);   MmiPrintf(" Давление     %6.3f МПа  ",s_MVD[0].Press);
// MmiGotoxy(0,3);   MmiPrintf(" Температура  %6.2f град.C",s_MVD[0].TempR);
 MmiGotoxy(0,5);   MmiPrintf(" Темп.расхдм.  %6.2f град.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC-меню,F1-оч.м.тек.");
}
//-------------------------------

/* =============
void f_prn_den_t()
{
float ftmp,ftmp1;
 //  Отображение Плотности,температуры,состава
 //  Текущее значение.
     ftmp=s_MVD[0].Compos;
 MmiGotoxy(0,0);   MmiPrintf("Текущие показания расходомера");
 MmiGotoxy(0,1);   MmiPrintf(" Плотность  %8.2f кг/м3",s_MVD[0].Dens);
 MmiGotoxy(0,2);   MmiPrintf(" Температура  %6.2f град.C",s_MVD[0].Temp);
 MmiGotoxy(0,6);   MmiPuts(" ESC   - возврат в меню");
  MmiGotoxy(0,3);
 if(s_MVD[0].PressG>0)
 {
    MmiPrintf(" Давл.нас.пара %5.3f МПа",s_MVD[0].PressG);
 }
 else
 {  if(ftmp> 1)
      {
         MmiPrintf(" В расходомере паровая фаза ");
         return;
      }
    else
         MmiPrintf(" Давление нас.пара не опред.");
 }

 MoveToXY(0,4);
    {
     if(ftmp>1.)
      MmiPrintf("!СУГ легче жидкого пропана");
     else if(ftmp<0.)
      MmiPrintf("!СУГ тяжелее жидкого бутана");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("СУГ:пропан %6.2f%c,бутан %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
}
======*/

//-------------------------------
void f_prn_comps()
{
float ftmp,ftmp1;
 //  Отображение состава
 //  Текущее значение.
    if((s_MVD[0].Dens>0)&&(s_MVD[0].Temp>-300))
    {
//   ftmp=f_get_composition(s_MVD[0].Dens,s_MVD[0].Temp);
     ftmp=s_MVD[0].Compos;
     if(ftmp>1.)
       MmiPrintf("Пар.фаза ");
     else if(ftmp<0.)
       MmiPrintf("Ждк.тяж.Б");
     else
      {
   //  MmiPrintf("ПРОПАН %6.2f%c",(ftmp*100),'%');
       MmiPrintf("%8.2f ",(ftmp*100.));
      }
    }
    else
       MmiPrintf("Не опред.");
}
//-------------------------------
//-------------------------------
void f_prn_lst_hour()
{ // показать состояние отпуска на последний расч. час

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

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
   MmiGotoxy(5,3);   MmiPrintf("Данные отсутствуют");
  }
  else
  {
  m_ok:
 MmiGotoxy(0,0);   MmiPrintf("   Значение счетчика СУГ ");
 MmiGotoxy(0,1);   MmiPrintf(" на последний расчетный час  ");

 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
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
{ // показать состояние отпуска на указанную дату

 struct tm *tdat;

int year,month,day,hour,min,sec;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;
 // определение времени последней записи в журнал

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

 tim_000=adate00;
 tim_000.hour=ahour00.hour;
 tim_000.min=ahour00.min;
 tim_000.sec=ahour00.sec;

 ltime0=f_get_time_t(&tim_000);

 MmiGotoxy(0,0);   MmiPrintf("   Значение счетчика СУГ ");
 MmiGotoxy(0,1);   MmiPrintf("     на указанную дату  ");

 MmiGotoxy(0,3);   MmiPrintf("  Дата     Время     Масса,кг");
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
      MmiPrintf("Нет данных");
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
{ // показать состояние отпуска за последние 5 суток

 struct tm *tdat;

int year,month,day,hour,min,sec,i;
unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1,ltime2;

long int ltmp;

 f_prepare_t ( &tim_000);
 ltime1=f_get_time_t(&tim_000); // текущее время

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
   ltime2= f_get_time(ar_str_ptr); // последняя запись

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

 MmiGotoxy(0,0);   MmiPrintf("  Дата     Время     Масса,кг");
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
           MmiPrintf("Нет данных");
     }
     else
     // if(tMassI>= 0.)
           MmiPrintf("%11.3f" ,tMassI);
     // else
     //    MmiPrintf(" ------- ");
    }
    MmiGotoxy(0,6);   MmiPuts("ESC,Enter - продолжить");

  }
 }
 else goto m_ok;
 return;

 m_bad:
   MmiGotoxy(5,3);   MmiPrintf("Данные отсутствуют");
 return;
}
//-------------------------------
char *rcv_mm[]={
"отпуск",
"прием",
};
char *Rcv_mm[]={
"Отпуск",
"Прием",
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
     MmiPrintf("%10.3f кг",a_str->MassI);
  else
     MmiPrintf(" ------- " );

   i_ret=i_n+1;
   if(i_ret>=n_mmi_str) return i_ret;

 MoveToXY(0,i_ret);
// switch( (int) a_str->event)
 switch( (int)( a_str->event & ~(int)RCV_FLG) )
 {
  case evt_NCNT_on:
    MmiPrintf(" Старт операции без учета ");
    goto m_val00;

  case evt_verify:
    MmiPrintf(" Старт Поверки");
    goto m_val00;

  case evt_verify_e:
    MmiPrintf(" Стоп Поверки");
    goto m_val00;

  case evt_NCNT_off:
    MmiPrintf(" Завершена операция без учета ");
    goto m_val00;

  case evt_beg_eq:
    MmiPrintf("Старт %sа.Паровая фаза.",rcv_mm[f_rcv]);
    goto m_val0;
  case evt_start_f:
    MmiPrintf("Старт %sа.Жидкая фаза.",rcv_mm[f_rcv]);

m_val0:
   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
  if(a_str->u.fill.VolT != vBIG_P)
      MmiPrintf("Доза %8.3fкг ",a_str->u.fill.VolT    );
  else
      MmiPrintf("Без дозы    ",a_str->u.fill.VolT    );
   goto m_val00;
/*
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%7.3f МПа;" ,a_str->u.fill.UnitPrice);
    MmiPrintf("U АКБ %6.2f V;",a_str->u.fill.Amount);

   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("Плотн.%6.3f кг/м3;" ,a_str->u.fill.Density);
    MmiPrintf("Темп.%6.2fC;" ,a_str->u.fill.Temp);

    if((a_str->u.fill.Density>0)&&(a_str->u.fill.Temp>-300))
    {
   i_ret=++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

     ftmp=f_get_composition(a_str->u.fill.Density,a_str->u.fill.Temp);
     if(ftmp>1.)
      MmiPrintf("!СУГ легче жидкого пропана");
     else if(ftmp<0.)
      MmiPrintf("!СУГ тяжелее жидкого бутана");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("СУГ:пропан %6.2f%c,бутан %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
    break;
*/
  case evt_cont_f:
    MmiPrintf(" Продолжение %sа,",rcv_mm[f_rcv]);
    goto m_val;
  case evt_exm_f:
    MmiPrintf(" Завершено,недолив ");

m_val:

   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
   if(a_str->u.fill.VolT != vBIG_P)
         MmiPrintf(" Масса %sа %9.3f кг ",rcv_mm[f_rcv],a_str->u.fill.VolT );

m_val00:
   i_ret++;
m_val1:
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("P=%7.3f МПа;" ,a_str->u.fill.UnitPrice);
    MmiPrintf("U АКБ %6.2f V;",a_str->u.fill.Amount);

   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
    MmiPrintf("Плотн.%6.3f кг/м3;",a_str->u.fill.Density);
    MmiPrintf("Темп.%6.2fC;" ,a_str->u.fill.Temp);

 /*
    if((a_str->u.fill.Density>0)&&(a_str->u.fill.Temp>-300))
    {
   i_ret++;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);
     ftmp=f_get_composition(a_str->u.fill.Density,a_str->u.fill.Temp);
     if(ftmp>1.)
      MmiPrintf("!СУГ легче жидкого пропана");
     else if(ftmp<0.)
      MmiPrintf("!СУГ тяжелее жидкого бутана");
     else
      {
       ftmp1=(1.- ftmp)*100.;
            MmiPrintf("СУГ:пропан %6.2f%c,бутан %6.2f%c",(ftmp*100),'%',ftmp1,'%');
      }
    }
*/
    break;

  case evt_exp_f:
    MmiPrintf(" Завершено,перелив");
    goto m_val;

  case evt_end_gas:
    MmiPrintf(" %s прерв.нет ждк.фазы",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_end_f:
    MmiPrintf(" Завершено ОК  ");
    goto m_val;

  case evt_est_f:
    MmiPrintf(" %s прерван командой",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_err_f:
    MmiPrintf(" %s прерван ошибкой",Rcv_mm[f_rcv]);
    goto m_val;
  case evt_eq_pr :
    MmiPrintf("Старт выр.давл. паровых фаз");
    goto m_val;
  case evt_stop_eq :
  printf("Заверш.выр.давл. паровых фаз");
    goto m_val;

  case evt_ep1_f:
    MmiPrintf(" %s прерван,Host",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_overfl:
    MmiPrintf(" %s прерван ост.потока",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_ES_off:
    MmiPrintf(" %s прерв.Авар.кнопкой ES",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    MmiPrintf(" %s прерв.Нет сигнала УЗА",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    MmiPrintf(" %s прерв.Нет питания 380V",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_VLT_off:
    MmiPrintf(" %s прерв.АКБ разряжена",Rcv_mm[f_rcv]);
    goto m_val;

  case evt_VLT:
    MmiPrintf(" АКБ разряжена");

    i_ret=i_n+2;
    goto m_val1;

  case evt_wd_pmp:
    MmiPrintf(" %s прерв.WD PMLAN",Rcv_mm[f_rcv]);
    goto m_val;


  case evt_no_dev:
    MmiPrintf(" Старт не принят.Не вкл.драйв");
    goto m_val;

  case evt_clr_err:
    MmiPrintf(" Сброс ошибок. ");
    break;

  case evt_MVD_CL_strt:
    MmiPrintf(" Старт калибровки расходомера");
    break;

  case evt_MVD_CL_BS1 :
    MmiPrintf(" !Попытка клб.расх.при отп.");
    break;

  case evt_MVD_CL_BS2 :
    MmiPrintf(" !Сбой при старте клб.расх.");
    break;

  case evt_MVD_CL_OK :
    MmiPrintf(" Калибровка расходомера OK");
    break;

  case evt_MVD_CL_TM :
    MmiPrintf(" Таймаут калибровки расходом.");
          //  |                              |

    break;

  case evt_ch_date:
    MmiPrintf(" Дата изменена.");
    break;

  case evt_ch_time:
    MmiPrintf(" Время изменено.");
    break;
  case evt_ch_sum:
    MmiPrintf(" Переход на летнее время.");
    break;
  case evt_ch_win:
    MmiPrintf(" Переход на зимнее время.");
    break;
  case evt_res:
    MmiPrintf(" Команда Сброс");
    break;
  case evt_Slot:
    MmiPrintf(" MVD:Конфигурир-е устройства");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     MmiPrintf(" !Изм.множ.объема");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     MmiPrintf(" !Изм.множ.массы");
    }
    else if(a_str->u.fill.VolT == Par_MC)
    {
     MmiPrintf(" !Изм.срез.м.расх.");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     MmiPrintf(" !Изменен пароль");
    }
    else
     {
//    MmiPrintf(" !Изм. парам. ");
      MmiPrintf(" !Изменен параметр ");
      MmiPrintf("N%g ",a_str->u.fill.VolT );
     }

   i_ret=i_n+2;
   if(i_ret>=n_mmi_str) return i_ret;
 MoveToXY(0,i_ret);

    MmiPrintf("Было:%g; ",a_str->u.fill.Amount  );
    MmiPrintf("Стало:%g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    MmiPrintf(" Команда Выход в ДОС");
    break;
  case evt_re:
    MmiPrintf(" Чтение конф.из EEPROM");
    break;
  case evt_re_err:
    MmiPrintf(" Ошибка чтения конф.из EEPROM");
    break;
  case evt_we:
    MmiPrintf(" Запись конф. в EEPROM");
    break;
  case evt_we_err:
    MmiPrintf(" Ош.записи конф. в EEPROM");
    break;

  case evt_wrong_start:
    MmiPrintf(" Cтарт не принят.Ошибка.");
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;ii<=icp_lst_max ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    MmiPrintf(" Ошибка:");
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
 MmiPrintf(" Ошибок нет ");

  break;

  case evt_t_on:
 MmiPrintf(" Включение устройства");
    break;
  case evt_t_off:
 MmiPrintf(" Выключение устройства");
    break;
  default:
 MmiPrintf(" Событие не известно");
   break;
 }
 return i_ret;
}

//----------------------------------
void f_MVD_M1()
{
// отображает параметры MVD  на MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
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
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("TXM версия: %d",s_MVD[0].i);}
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
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Тemp.: --%s--",s_MVD[0].a);}
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
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель массы:     %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 32:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=281;
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель объема:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 33:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=283;
   sw_mvd_m1=14;
   break;

  case 14:
   if(MVD_fn[0] != F_FAULT)
    {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Множитель плотности: %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 34:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=195;
   sw_mvd_m1=15;
   break;

  case 15:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Срез масс.расхода:   %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 35:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=197;
   sw_mvd_m1=16;
   break;

  case 16:
   if(MVD_fn[0] != F_FAULT)
   { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Срез об. расхода:    %.6f",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};

  case 36:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=149;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
  { MoveToXY(0,sw_MMI_cur++); MmiPrintf("Срез плотности :     %.6f",s_MVD[0].f);}
   ff_serv=NULL;
   break;
  }

}
/* ---------------------------------------- */
void f_MVD_M1f()
{
// отображает параметры коррекции расхода  MVD  на MMI
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
     MoveToXY(0,4); MmiPrintf(" !Таймаут чтения MVD");
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
   { MoveToXY(0,4);MmiPrintf("Множитель массы:    %.6f",s_MVD[0].f);}
     k_m_flow=s_MVD[0].f;

  case 32:
   MVD_fn[0]=MVD_RD_F;
//   s_MVD[0].r_addr=281; // Множитель объема
   s_MVD[0].r_addr=195;  // Cuttoff for mass flow
   sw_mvd_m1=13;
   break;

  case 13:
   if(MVD_fn[0] != F_FAULT)
//   { MoveToXY(0,5);MmiPrintf("Множитель объема:   %.6f",s_MVD[0].f);}
 { MoveToXY(0,5); MmiPrintf("Срез м.расх.: %10.2f кг/ч",s_MVD[0].f);}
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
// отображает данные MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход м. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса общ.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса инв.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход об.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем общ.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем инв.: %10.2f %s",s_MVD[0].f,unit4);}
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
      MoveToXY(0,sw_MMI_cur++);MmiPrintf("Плотность  :%.5f %s",s_MVD[0].f,unit5);
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
    MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.потока: %.3f %s",s_MVD[0].f,unit6);
    MMITemp=s_MVD[0].f;
   }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
    if((MMIDens>0)&&(MMITemp>-300))
    {
     MMICompos=f_get_composition(MMIDens,MMITemp);
     if(MMICompos>1)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Смесь легче жидкого пропана");}
     else if(MMICompos<0)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Смесь тяжелее жидкого бутана");}
     else
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("СУГ,пропан %5.2f%c,бутан %5.2f%c",(MMICompos*100.),'%',(100.-MMICompos*100.),'%' );}
    }
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.платы : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Напр.пит.  : %.3f V",s_MVD[0].f);}
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
// отображает данные MVD
  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD");
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход м. : %f %s",s_MVD[0].f,unit1);}
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
    { MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса общ.: %10.3f %s",s_MVD[0].f,unit2);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Масса инв.: %10.2f %s",s_MVD[0].f,unit2); }
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Расход об.: %f %s",s_MVD[0].f,unit3);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем общ.: %10.3f %s",s_MVD[0].f,unit4);}
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
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Объем инв.: %10.2f %s",s_MVD[0].f,unit4);}
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
     MoveToXY(0,sw_MMI_cur++); MmiPrintf("Плотность  :%.5f %s",s_MVD[0].f,unit5);
     MMIDens=s_MVD[0].f;
  }
  else
  {
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("Ошибка чтения");
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
     MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.потока: %.3f %s",s_MVD[0].f,unit6);
     MMITemp=s_MVD[0].f;
    }
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
    if((MMIDens>0)&&(MMITemp>-300))
    {
     MMICompos=f_get_composition(MMIDens,MMITemp);
     if(MMICompos>1)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Смесь легче жидкого пропана");}
     else if(MMICompos<0)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Смесь тяжелее жидкого бутана");}
     else
   {MoveToXY(0,sw_MMI_cur++);MmiPrintf("СУГ,пропан %5.2f%c,бутан %5.2f%c",(MMICompos*100.),'%',(100.-MMICompos*100.),'%' );}
    }
  }
  case 28:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=383;
   sw_mvd_m1=17;
   break;

  case 17:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Темп.платы : %.3f C",s_MVD[0].f);}
   if(sw_MMI_cur>=sw_MMI_lim)  {ff_serv=NULL;break;};
  case 29:
   MVD_fn[0]=MVD_RD_F;
   s_MVD[0].r_addr=385;
   sw_mvd_m1=18;
   break;

  case 18:
   if(MVD_fn[0] != F_FAULT)
     {MoveToXY(0,sw_MMI_cur++);MmiPrintf("Напр.пит.  : %.3f V",s_MVD[0].f);}
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
// отображает ошибки MVD

  ii=i_nn_mvd;

  if((MVD_fn[ii] != 0) && (MVD_fn[ii] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
   MoveToXY(0,sw_MMI_cur); MmiPrintf(" !Таймаут чтения MVD %d",ii+1);
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
        MoveToXY(8,3); MmiPrintf("MVD %d.Ошибок нет.",ii+1);
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
          MmiPrintf(" Ошибка расходомера N%d :",ii+1);
      else if( i>1)
*/
          MmiPrintf(" Ошибки расходомера N%d:",ii+1);
       i2=1;
     }
     else
     {

      MoveToXY(0,0);
         MmiPrintf("Сост./ошибки расходомера N%d:",ii+1);
       i2=2;
     }
       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1)
         {
           MoveToXY(0,i2);
           MmiPuts(str_empty);
           MoveToXY(0,i2);
           if(i==0x11) MmiPrintf("Калибровка расходомера");
           else if(i==0x13) MmiPrintf("Сброс по включению питания");
           else if(i==0x15) MmiPrintf("Инициализация трансмиттера");
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

"MMI:Статус",                 //  0
"MMI:Номер порта",            //  1
"MMI:Адрес",                  //  2
"MMI:Опрос,мс ",              //  3
"MMI:Таймаут,мс",             //  4
"MMI:Флаг CRC",               //  5

"7017/1:Статус",                 //  6
"Нач.стадия переб.",             //  7
"T антидр.прб.,мс",              //  8
"Mode 1-Dens,2-Press.",          //  9
"",                              // 10
"Радиус трубк.MVD,mm",          // 11

"7017/2:Статус",                // 12

"M бол.кл.Прм,кг",                // 13
"M мал.кл.Прм,кг",                // 14

"Клапан Срд N вых.",        // 15
"Питание N вых.",        // 16
"7017/2:Флаг CRC",              // 17

"7060/1:Статус",                 // 18

"",           // 19
"",        // 20
"",        // 21

"Скор.ум.плотн.-прб.",        // 22
"Зона стаб.плотн.+п.",       // 23

"7060/2:Статус",           // 24

"T прб.плюс.,мс",          // 25
"T прб.минус,мс",          // 26
"T прб.антидреб.,мс",      // 27
"Зад.вкл.блш.кл.,мс",      // 28
"T выкл.клп.пара,мс",      // 29

"COM1 Скорость",                // 30
"COM2 Скорость",                // 31
"COM3 Скорость",                // 32
"COM4 Скорость",                // 33

"Скан.:Т-аут,мс",            // 34
"Скан.:Макс.адр.",           // 35
"Скан.ICP:CRC флаг",            // 36

"WDOG/1:Статус",                // 37
"WDOG/1:Номер порта",           // 38
"WDOG/1:Период,мс ",            // 39
"WDOG/1:Задержка,мс",           // 40
"WDOG/1:Флаг CRC",              // 41

"dP для +переб.,МПа",       // 42
"dP для -переб.,МПА",       // 43
"+к T для опр Pнп ",        // 44
"N меньш.клап.(1-3)",       // 45
"WDOG/2:Флаг CRC",              // 46

"7060/1:Разреш.WD",           // 47
"7060/1:Знач.WD,0.1с",        // 48

"7060/2:Разреш.WD",           // 49
"7060/2:Знач.WD,0.1с",        // 50

"MVD1:Статус     ",           //  51
"MVD2:Статус     ",           //  52
"MVD:Адрес",                  //  53
"MVD:Опрос,мс ",              //  54
"MVD:Таймаут,мс",             //  55

"TSD:Статус",                 //  56
"TSD:Номер порта",            //  57
"TSD:Адрес",                  //  58
"TSD:Опрос,мс ",              //  59
"TSD:Таймаут,мс",             //  60

"COM1 Длина",                // 61
"COM2 Длина",                // 62
"COM3 Длина",                // 63
"COM4 Длина",                // 64

"COM1 Четность",           // 65
"COM2 Четность",           // 66
"COM3 Четность",           // 67
"COM4 Четность",           // 68

"COM1 Стоп бит",           // 69
"COM2 Стоп бит",           // 70
"COM3 Стоп бит",           // 71
"COM4 Стоп бит",           // 72

"COMP Скорость",           // 73
"COMP Длина",              // 74
"COMP Четность",           // 75
"COMP Стоп бит",           // 76

"COMP Номер порта",        // 77
"Номер входа Gun",         // 78
"Инвер-я входа Gun",       // 79

"Клапан Блш N вых.",        // 80
"Клапан Мнш N вых.",        // 81
"Флаг расш.отчета.",        // 82
"Адрес PUMALAN",            // 83
"Статус PUMALAN",           // 84
"COM1:Скан.тип 0,1",        // 85
"COM2: 0-ICP,1-RTU",        // 86
"COM3:Скан.тип 0,1",        // 87
"Тип уч.выборки",           // 88
"Переход на лет.вр.",       // 89
"------------------",       // 90
"Знаков после зпт.1",       // 91
"Знаков после зпт.2",       // 92
"Знаков после зпт.3",       // 93
"Параметр индик. 1",        // 94
"Параметр индик. 2",        // 95
"Параметр индик. 3",        // 96
"Обновл-е индик,мс",        // 97
"M бол.кл.Отп,кг",         // 98    p1-p6.CLV
"M мал.кл.Отп,кг",         // 99
"T бол кл.,мс",       // 100
"T мал.кл.,мс",       // 101
"нач.запр.оп.MMI,мс",      // 102
"длит.запр.о.MMI,мс",       // 103
"подстр.отп. 0...1",        // 104   p1-p3.KA
"подстр.прм. 0...1",        // 105
"зад-ка зап.отч.,мс",       // 106

"тестовый режим 1/0",       // 107    p1.CTRL
"зад-ка прох.MVD,мс",       // 108    p2.CTRL
"срез расх.для TST",        // 109    p3.CTRL

"первичная M,кг",           // 110    p1-p5.DSC
"экстраполир-я M,кг",        // 111
"расход при сраб.кл",       // 112
"коррекция M,кг",            // 113
"коррекция T,мс",           // 114

// DNP
"Предел плотн.+",           // 115
"Предел плотн.-",           // 116
"Темпер.норм.20",           // 117
"\% отпуска для t",         // 118
"Режим t отп.0-2",          // 119
"Режим отпуска 1-3",        // 1 2 0

// DNC
"Скор.ум.плотн.срд.",        // 121
"Зона стаб.плотн.срд.",       // 122
"",      // 123
"",        // 124
"",        // 125

//DTC
"плотн.нач.,г/см3",         // 126
"темпер.начальн.,C",        // 127
"доля пропана",             // 128

"U АКБ полная шк,V",       // 129
"U АКБ смещение,V ",       // 130

"U ИП полная шк,V",        // 131
"U ИП смещение,V ",        // 132

"Ед.изм. для пар.3",        // 133
"MAX недолив",              // 134
"MAX перелив",              // 135
"WD пер.PUMALAN,мс",        // 136
// FLCH
"M опр.пот. LTL,кг",      // 137
"T опр.пот.,тик",       // 138
"Вкл.насоса N вых.",        // 139
"Пар.фаза АЦ,N вых.",       // 140
"Пар.фаза внеш.Nвых.",      // 141
"Ждк.фаза внеш.Nвых.",      // 142
"Аварийная кн. N вх.",      // 143
"Аварийная кн.фл.инв",      // 144
"Сигнал УЗА  . N вх.",      // 145
"Сигнал УЗА флаг инв",      // 146
"Время отп.ждк.ф.,с",      // 147
"Время выр.двл.отп,с",     // 148
"Время прм.ждк.ф.,с",      // 149
"Время выр.двл.прм,с",     // 150
"f тока насоса,0.1Гц",     // 151
"T разг.насоса,0.1с",      // 152
"Зад.вкл.мнш.кл.,мс",     // 153
"Зад.выкл.насоса,мс",      // 154
"T торм.насоса,0.1с",      // 155
"P полная шкала,МПа",      // 156
"P смещение,    МПа",      // 157
"Расход  Min,kg/h",      // 158
"Расх.при обрыве,л/с",     // 159
"Контр.опорожн.T1,мс",     // 160
"Контр.опорожн.T2,мс",     // 161
"U предупреждения,V",      // 162
"U отключения ,V",         // 163
"U пит.от сети,V",         // 164
"T до ост.отпуска,мс",     // 165
"T до отключения,мс",      // 166
"",
};
//-------------------------------
char *list2_dsr[]={
" Колич.данных",            //  0
" Знач.АЦП,дискр.",         //  1
" Знач.Давл.,МПа",          //  2
" Знач.Темп.,C",            //  3
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
   {  // введено числовое значение
     key=DATA;  // признак окончания ввода строки
     sw_fst=0;
   }
   else if(i==fst_ESC)
   {
     key=DATA_ESC;  // признак окончания ввода строки
     sw_fst=0;
   }
   else if( MmiKbhit())
   {  // ввод поступившего символа из клавиатуры
    key=MmiGetch();
   }
   else if(sw_fst==0)
   {
    key=PASS; // признак холостого прохода (без введенного символа)
              // используется для индикации изменяющихся значений
   }
   else return 0;

   switch(sw_mmi)
    {
     case 0: /*заголовок*/
//------------------------------------
/*=========
       if(key==F2)
        {
       m_0f2:
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("Введите номер страницы:" );
          sprintf( fst_str,"%d",num_page);
          fst_n=2;
          sw_fst=1;
//        MmiGotoxy(10,3);
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ввод значения
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
        {  // отключение питания
           f_clr_scr_MMI();
           SetDisplayPage(EmptyPage);
        MmiGotoxy(0,1);        MmiPuts("  !!! Отключение питания ");
        MmiGotoxy(0,3);        MmiPuts("Enter  Отключить");
        MmiGotoxy(0,4);        MmiPuts("ESC    Не отключать,продолжить");
           sw_mmi=28;
           break;

        }
//---------------------------------
        if (key==Sht_ESC)
        {  // очистка ошибок

          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);
          sw_mmi=26;
          f_cl_error();
          MmiGotoxy(5,2);    MmiPuts("   Ошибки очищены   ");
          MmiGotoxy(0,4);    MmiPuts(" Enter - продолжить ");

        }
        else if (key==Sht_F1)
        {  // распечатка ошибок

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
          MmiPrintf(" Ошибка запуска калибровки ");
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

            MmiGotoxy(0,0);    MmiPuts("     Меню ");
            MmiGotoxy(0,1);    MmiPuts("1  Отпуск СУГ");
            MmiGotoxy(0,2);    MmiPuts("2  Прием  СУГ");
            MmiGotoxy(0,3);    MmiPuts("3  Операции без учета");
//          MmiGotoxy(0,3);    MmiPuts("3  Показания счетчика СУГ");
            MmiGotoxy(0,4);    MmiPuts("4  Просмотр журнала событий");
            MmiGotoxy(0,5);    MmiPuts("5  Сервисные функции");
//          MmiGotoxy(0,6);    MmiPuts("6  Плотность,темп.,состав");
            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");

          break;
       }
       else if(key==PASS)
        {  // отображение даты и времени
         if((FL_err|CRC_err) == 0)
         {
          if(PageD==0)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.2f кг     ",s_MVD[0].MassI+s_MVD[1].MassI);
             MmiGotoxy(14,4);  MmiPrintf("%8.1f  кг/м3 ",s_MVD[0].Dens);
             MmiGotoxy(14,5);  MmiPrintf("%9.3f МПа    ",s_MVD[0].Press);
//           MmiPrintf("%9.2f град.    ",s_MVD[0].Temp);
            // MmiGotoxy(18,4);
            //    f_prn_comps();
          }
          else if(PageD==1)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.3f МПа    ",s_MVD[0].Press);
             MmiGotoxy(14,4);  MmiPrintf("%9.2f В       ",s_MVD[0].Volt_A);
             MmiGotoxy(14,5);  MmiPrintf("%9.2f В       ",s_MVD[0].Volt_DC);
          }
          else if(PageD==2)
          {
             MmiGotoxy(14,3);  MmiPrintf("%9.2f кг     ",s_MVD[0].MassI);
             MmiGotoxy(14,4);  MmiPrintf("%9.2f кг     ",s_MVD[1].MassI);
             MmiGotoxy(14,5);  MmiPrintf("%9.2f кг     ",s_MVD[0].MassI+s_MVD[1].MassI);
          }
         }
         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(0,6);
         MmiPrintf("%02d.%02d.%02d %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
        }

        break;
 /*========================================*/
    case 11:  /*меню выбора точки для просмотра параметров */
       n_adc_mm=0;
       if(key==ESC)    /* переход в меню M3, Сервисные функции */
       {
         goto m_m3;
       }
       else if(key=='1')  // Базовый список #1
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=0;
        }
       else if(key=='2')  // Базовый список #2
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=max_par/5;
        }
       else if(key=='3')   // Базовый список #3
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*2)/5;
        }
       else if(key=='4')  // Базовый список #4
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*3)/5;
        }
       else if(key=='5')  // Дополнительный список
        {
         f_before_MMI();
         ds_list=ds_list1;
         max_par=max_list1;
         mmi_prm=(max_par*4)/5;
        }
             else if(key=='6')  // Дополнительный список
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
       SetDisplayPage(EmptyPage);    // Чистая страница
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
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"Enter\"Изм. ");
       }
       else
       {
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\",\"F3\",\"ESC\",\"Enter\"         ");
         MmiGotoxy(2,nn_chg);  MmiPuts("#");
       }
       sw_mmi=14;
       break;
 /*========================================*/
    case 14:/* просмотр до 6 параметров */
       if(key==Sht_F2)    /* сохранение изменений в EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptyPage);    // Чистая страница
        MmiGotoxy(0,1);    MmiPuts("Сохранение данных в EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    Сохранить");
        MmiGotoxy(0,4);    MmiPuts("ESC   Не сохранять,продолжить");
        sw_mmi=15;
        break;
       }
       if(key==Sht_F3)    /* чтение данных из EEPROM */
       {
        f_clr_scr_MMI();
        SetDisplayPage(EmptyPage);    // Чистая страница
        MmiGotoxy(0,1);    MmiPuts("Чтение данных из EEPROM");
        MmiGotoxy(0,3);    MmiPuts(" 1    Прочитать ");
        MmiGotoxy(0,4);    MmiPuts("ESC   Не считывать,продолжить");
        sw_mmi=16;
        break;
       }
       if(flag_chg==0)
       {
         if(key==ESC)    /* переход в меню выбора точки для просмотра*/
         {
          goto m_m3_3;
         }
         else if(key== F2 )
           if(mmi_prm==0);
           else if(mmi_prm>=n_mmi_str_1)
           {
            mmi_prm -=n_mmi_str_1;
            f_clr_scr_MMI();
            SetDisplayPage(EmptyPage);    // Чистая страница
            goto par_out14;
           }
           else
           {
            mmi_prm = 0;
            f_clr_scr_MMI();
            SetDisplayPage(EmptyPage);    // Чистая страница
            goto par_out14;
           }
         else if((key== F3 )&& (mmi_prm < (max_par-n_mmi_str_1)) )
         {
          mmi_prm +=n_mmi_str_1;
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // Чистая страница
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
         if(key==ESC)    // очистка флага редактирования
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
         if(key==ENTER)    // редактирование параметра
         {
          if(PassW != Password)
          {
           pass_ret=0;
m_pass:
           MmiGotoxy(1,1);
           f_clr_scr_MMI();
           MmiPuts("Введите пароль:" );
           sprintf( fst_str,"******");
           SetDisplayPage(17);    // Ввод пароля
           sw_mmi=121;
           fst_n=7;
           sw_fst=1;
           MmiGotoxy(11,3);
//         MmiGotoxy(15,3);
           break;
          }

          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(2,nn_chg);  MmiPuts(">");
          MoveToXY(NumPlace,nn_chg);

          PrintMmiOp(&ds_list[nn_chg+mmi_prm],0);
          fst_n=8;
          sw_fst=1;
          break;
         }
       }
       if(key==DATA)    // ввод полученных данных
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
    case 15:/* сохранение данных в EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* возврат к отображению параметров */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // Чистая страница
          goto par_out14;
         }
         else if(key=='1')    // сохранить данные
         {

           if(f_wrt_eee()<0)
           {
              f_wr_evt(evt_we_err);
              MmiGotoxy(0,5);   MmiPuts("Ошибка при сохранении данных");
           }
           else
           {
              f_wr_evt(evt_we);
              MmiGotoxy(0,5);   MmiPuts(" Данные сохранены успешно");
           }
              f_wr_cor();
              MmiGotoxy(0,6);   MmiPuts("      Enter - продолжить");
         }
         break;
 /*========================================*/
    case 16:/* чтение данных из EEPROM */
         if((key==ESC)||(key==ENTER)  )   /* возврат к отображению параметров */
         {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // Чистая страница
          goto par_out14;
         }
         else if(key=='1')    // прочитать
         {
           f_chk_EEE_CRC();
           if(f_rd_eee()<0)
           {
              f_wr_evt(evt_re_err);
              MmiGotoxy(0,5);   MmiPuts("Ошибка при чтении данных");
              CRC_err=1;
           }
           else
           {
              f_wr_evt(evt_re);
              MmiGotoxy(0,5);   MmiPuts("  Данные считаны успешно");
              CRC_err=0;
           }

           f_rd_cor();
           MmiGotoxy(0,6);   MmiPuts("      Enter - продолжить");
         }
         break;
 /*========================================*/
    case 18:
       if((key==ESC)||(key==ENTER))  /* переход на начальную страницу */
           goto m_main;
       if( f_timer(zero_time,Time_zeroing ))
       {
             f_clr_scr_MMI();
             MoveToXY(3,3);
            MmiPrintf(" Таймаут калибровки");
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
         MmiPrintf("Калибровка завершена успешно");
//                |                              |
             f_wr_evt(evt_MVD_CL_OK);
             goto m_SF2;
           }
           fl_rd_err=0;
           sw_mvd_m1=0;  // нач.параметр
           ff_serv=f_MVD_M3;
          }

         GetDate(&year,&month,&day);GetTime(&hour,&min,&sec);
         MoveToXY(4,6);
         MmiPrintf("%02d.%02d.%02d   %02d:%02d:%02d" ,day,month,year-2000 ,hour,min,sec);
         break;
 /*========================================*/
    case 120:  // Основное меню

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           PageD=0;
           goto m_main;
       }
       else if(key== '1') //  1  Отпуск СУГ
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
            MmiGotoxy(0,0);    MmiPuts("   Меню 1.Отпуск СУГ.");
            f_prn_MassSt_dlv();
            MmiGotoxy(0,2);    MmiPuts("1 Отпуск дозы СУГ");
            MmiGotoxy(0,3);    MmiPuts("2 Отпуск до опорожнения");
          if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 Продолжить:");

            MmiGotoxy(0,5);
            if(dose_dlvr != vBIG_P)
                MmiPrintf("Д=%8.2f кг   ",dose_dlvr);
            MmiPrintf("Без дозировки ");
            MmiGotoxy(15,5);   MmiPrintf("О=%8.2f кг   ",-(s_MVD[0].MassT+s_MVD[1].MassT));
          }

            MmiGotoxy(0,6);    MmiPuts(kran);
         sw_mmi=190;


         Out_en_pmp = OUT3;  // Насос
      // Out_en_pmp = 0;  // Насос

         break;
       }
       else if(key== '2') // 2  Прием  СУГ
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
            MmiGotoxy(0,0);    MmiPuts("   Меню 2.Прием СУГ.");

            f_prn_MassSt_rcv();
            MmiGotoxy(0,2);    MmiPuts("1 Прием дозы СУГ");
            MmiGotoxy(0,3);    MmiPuts("2 Прием без дозы");
          if(flag_prn_mass != 0)
          {  MmiGotoxy(0,4);    MmiPuts("3 Продолжить:");

            MmiGotoxy(0,5);
            if(dose_dlvr != vBIG_P)
                MmiPrintf("Д=%8.2f кг   ",dose_dlvr);
            MmiPrintf("Без дозировки ");
            MmiGotoxy(15,5);   MmiPrintf("П=%8.2f кг    ",s_MVD[0].MassT+s_MVD[1].MassT);
          }

            MmiGotoxy(0,6);    MmiPuts(kran);


         Out_en_pmp = OUT3;  // Насос
      // Out_en_pmp = 0;  // Насос
         sw_mmi=200;
         break;
       }
       else if(key== '*')    //  Sht_1 Поверка
       {
        Flag_check = 1;
        flag_rcv=0;
        f_wr_evt(evt_verify);
        sw_mmi=230;
        break;
       }
       else if(key== '3') //  3  Операции без учета
       {
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0); MmiPuts("Прием/Отпуск СУГ без учета");
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
       else if(key== '6') // 6 Плотность,темп.,состав
       {
m_m4:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_den_t();
         flg_ch=0;
         sw_mmi=122;
         break;
       }
       else if(key== '7') // 7 Отображение аналоговых входов
       {
m_m7:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

   MmiGotoxy(0,0); MmiPrintf(" Состояния аналоговых входов:");
//   MmiGotoxy(0,1); MmiPrintf("    I7017C, дискреты АЦП");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625


   MmiGotoxy(0,4); MmiPrintf(" Состояния дискретных входов:");

  _fmemset( &ADC_c[0],0xff,sizeof(ADC)); // очистка буфера экрана
  INP_VAR_c=0xffff;
         sw_mmi=25;
         break;

       }
       else if(key== '8') // 8 Версия sw
       {
m_m8:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

      MmiGotoxy(0,3);   MmiPrintf("   VER %s",sw_ver);
      MmiGotoxy(0,6);   MmiPuts(" ESC   - возврат в меню");
         sw_mmi=-1;
         break;

       }
       else if(key== '9' )//  9  Коррекция расхода
       {
m_m9:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню 9.Коррекция расхода.");
            MmiGotoxy(0,1);    MmiPuts("1 Коррекция массового расхода");
            MmiGotoxy(0,2);    MmiPuts("2 Коррекция среза м. расхода");
  //        MoveToXY(0,4);   MmiPrintf("Множитель массы:     %.6f",s_MVD[0].f);
  //        MoveToXY(0,5);   MmiPrintf("Множитель объема:    %.6f",s_MVD[0].f);
          //  MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

         Flag_f_corr=0;
         sw_mvd_m1=31;
         tm_mvd=TimeStamp;
         ff_serv=f_MVD_M1f;
         sw_mmi=125;
         break;
       }
 //------------------------------------------
       else if(key== '0') // 0 Отображение дискретных выходов
       {
m_m0:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         flag_v2=0;
   MmiGotoxy(0,0); MmiPrintf(" Состояния дискретных выходов:");
   MmiGotoxy(0,2); MmiPrintf(" 1 ...8 - изменить состояние ");
// MmiGotoxy(0,1); MmiPrintf(" xxx.xx xxx.xx xxx.xx xxx.xx");// 20./3276.8=0.006103515625

         OUT_VAR_c=0xffff;
         sw_mmi=27;
         PageD=3;
         break;

       }

       else if(key== '4') // 4  Просмотр журнала событий
       {
m_m2:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

            i= f_get_max_n_arch();
            ar_str_ptr=f_get_fst_stor();
            MmiGotoxy(0,0);    MmiPuts(" Меню 4.Журнал событий.");
            MmiGotoxy(0,1);    MmiPrintf("%4d  ",i);
            j=i%100;
            if((j<=20)&& (j>5))
              MmiPrintf("записей");
            else
            switch(i%10)
            {
             case 1:
             MmiPrintf("запись");
             break;

             case 2:
             case 3:
             case 4:
             MmiPrintf("записи");
             break;

             case 0:
             case 5:
             case 6:
             case 7:
             case 8:
             case 9:
             MmiPrintf("записей");
             break;
            }

   tdat = localtime( &ar_str_ptr->time );
//   MmiPrintf(" с %02d.%02d.%02d %02d:%02d:%02d",
//   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
   MmiPrintf(" с %02d.%02d.%02d",
   tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100);

            MmiGotoxy(0,2);    MmiPuts(" Просмотр журнала событий");
            MmiGotoxy(0,3);    MmiPuts("1  По дате");
            MmiGotoxy(0,4);    MmiPuts("2  По номеру записи");
            MmiGotoxy(0,5);    MmiPuts("3  Последние записи");
        //    MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

         PassW=0;
         sw_mmi=140;
         break;
       }
       else if(key== '5') // 5  Сервисные функции
       {
m_m3:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню 5.Сервисные функции.");
//            MmiGotoxy(0,1);    MmiPuts("1  Список драйверов");
            MmiGotoxy(0,1);    MmiPuts("1  Показания счетчика СУГ");
            MmiGotoxy(0,2);    MmiPuts("2  Статистика  драйверов");
            MmiGotoxy(0,3);    MmiPuts("3  Просмотр/ввод параметров");
            MmiGotoxy(0,4);    MmiPuts("4  Другие функции");
            MmiGotoxy(0,5);    MmiPuts("5  Время, дата");
          //  MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

         sw_mmi=150;
         PassW=0;
       }
       break;
 /*========================================*/
    case 121: // // ввод пароля на изменение данных
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // Чистая страница
 m121:
          switch(pass_ret)
          { // пароль не введен
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
          SetDisplayPage(EmptyPage);    // Чистая страница
          switch(pass_ret)
          { // пароль введен корректно
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
          SetDisplayPage(EmptyPage);    // Чистая страница
          goto m121;
        }

 /*========================================*/
    case 122:
 //  Отображение Плотности,температуры,состава
 //  Текущее значение.
       if((key==ESC)||(key==ENTER))    /* переход в меню */
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
 //  Меню 9.Коррекция расхода.
       if((key==ESC)||(key==ENTER) )    /* переход в меню */
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
          SetDisplayPage(EmptyPage); // ввод значения
          f_clr_scr_MMI();
          MmiPuts("Введите коррекцию массы:" );
          k_mv_tmp=k_m_flow;
          flag_mass=1;
m_m9_1_1:

          MmiGotoxy(0,n_mmi_str_2);  MmiPuts("\"1...9,SHT-7\"-Ввод,\"SHT-4\"-Уд.");
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"ESC - возврат");
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
          SetDisplayPage(EmptyPage); // ввод значения
          f_clr_scr_MMI();
//        MmiPuts("Введите коррекцию объема:" );
          MmiPuts("Введите срез масс.расх.кг/ч:" );
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

      // введенное значение в k_mv_tmp
          if(flag_mass)
          {
           s_MVD[0].r_addr=279; // Множитель массы.

           chg_nn_par=Par_MF;
           chg_old=k_m_flow;
           chg_new= k_mv_tmp;
           f_wr_evt(evt_chg_param);
          }
          else
          {
//         s_MVD[0].r_addr=281; // Множитель объема.
//         chg_nn_par=Par_VF;

           s_MVD[0].r_addr=195; // Срез масс.расхода
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
    case 130: // //  1  Состояние отпуска СУГ

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }

       else if(key== '1')  // 1  На последний расч. час
       {
m_m1_1:
  //     mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_lst_hour();
         sw_mmi=131;
       }
       else if(key== '2')  // 2  За последние 5 суток
       {
m_m1_2:
  //     mmi_str=0;

//printf("\r\n===0===");
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

         f_prn_5day();
         sw_mmi=131;
       }
       else if(key== '3')  // 3  На указанную дату
       {
m_m1_3:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Дата состояния счетчика");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=134;
       }
       else if(key== '4')  //4  На текущий момент
       {
m_m1_4:
    //   mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_prn_current();
         sw_mmi=132;
       }
       else if(key== '5')  //5  Значение расчетного часа
       {
m_m1_5:
      // mmi_str=0;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("  Значение расчетного часа");
           MmiGotoxy(0,1);    MmiPuts("       Час.Мин.Сек");
        // MmiGotoxy(0,2);    MmiPuts("        08.00.00");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)ahour00.hour,(int)ahour00.min,(int)ahour00.sec );
          fst_n=9;
          sw_fst=1;
          sw_mmi=133;
       }
       break;
 /*========================================*/
    case 131:
 //  Отображение Состояния отпуска СУГ.
 // На последний расч. час .
       if((key==ESC)||(key==ENTER))    /* переход в вышестоящее меню */
       {
         goto m_m1;
       }
       break;
 /*========================================*/
    case 132:
 //  Отображение Состояния отпуска СУГ.
 //  Текущее значение.
       if((key==ESC)||(key==ENTER))    /* переход в меню */
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
 //  Отображение расчетного часа.
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
              MmiGotoxy(0,5);   MmiPuts("Ошибка при сохранении данных");
              sw_mmi=131;
           }
           else goto m_m1;

          break;
        }
       break;
 /*========================================*/
    case 134:
 //  Ввод даты
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
            // дата введена
            // отображение значения отпуска
            SetDisplayPage(EmptyPage);
            f_clr_scr_MMI();
            f_prn_date();
            sw_mmi=131;

          break;
        }
       break;
 /*========================================*/
    case 140: // 2  Просмотр журнала событий

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }
        else if (key==DEL)
        {

          f_clr_scr_MMI();
          SetDisplayPage(EmptyPage);    // Чистая страница
          MmiGotoxy(0,1);    MmiPuts(" 1 - Перезагрузка");
          MmiGotoxy(0,2);    MmiPuts(" 6 - Выход из программы в ОС");
          MmiGotoxy(0,3);    MmiPuts("    (при  отладке)");
          MmiGotoxy(0,5);    MmiPuts("ESC   отмена");
          sw_mmi=142;
          break;
        }
       else if(key== '1')  //1  По дате
       {
m_m2_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Дата записи журнала ");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=143;
          break;
       }
       else if(key== '2')  //2  По номеру записи
       {
m_m2_2:
          max_par= f_get_max_n_arch();
          MmiGotoxy(1,1);
          f_clr_scr_MMI();
          MmiPuts("Введите номер записи:" );
          sprintf( fst_str,"%d",max_par);
          fst_n=4;
          sw_fst=1;
          MmiGotoxy(15,3);
          SetDisplayPage(15); // ввод значения
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
       else if(key== '3')  //3  Последние записи
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
         SetDisplayPage(EmptyPage);    // Чистая страница

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
        MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");

        sw_mmi=141;
       }
       break;
 /*========================================*/
    case 141:/*просмотр 2 записей журнала*/
         if(key==ESC)    /* переход в меню выбора точки для просмотра*/
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
    case 142:/* выход из программы */
             /* возврат к просмотру */
       if((key==ESC)||(key==ENTER))    /* переход в меню */
         {
          goto m_m2;
         }
         else if(key== '1' )
         { //  1 - Перезагрузка
           f_wr_evt(evt_res);
           _asm cli
           _asm hlt
         }
         else if(key== '6' )
         {// 6 - Выход из программы в ОС
            f_wr_evt(evt_exit);
            return 1; // выход из программы *.exe в ОС
         }
         break;
 /*========================================*/
    case 143:

 //  Ввод даты
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
            // дата введена

m_m2_1_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("   Время записи журнала ");
           MmiGotoxy(0,1);    MmiPuts("       Час Мин.");
        // MmiGotoxy(0,2);    MmiPuts("        08.01");
            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d",(int)adate00.hour,(int)adate00.min );
          fst_n=6;
          sw_fst=1;
          sw_mmi=144;
       }
          break;

 /*========================================*/
    case 144:
 //  Ввод времени
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
            // время введено

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
    case 150: // 3  Сервисные функции

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto main_menu;
       }

       else if(key== '1') //  1  Показания счетчика СУГ
       {
         f_prepare_t ( &adate00);
m_m1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Показания счетчика СУГ");

            MmiGotoxy(0,1);    MmiPuts("1  На последний расч. час");
            MmiGotoxy(0,2);    MmiPuts("2  За последние 5 суток");

            MmiGotoxy(0,3);    MmiPuts("3  На указанную дату");
            MmiGotoxy(0,4);    MmiPuts("4  На текущий момент");
            MmiGotoxy(0,5);    MmiPuts("5  Значение расчетного часа");
       //    MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

         sw_mmi=130;
         break;
       }

       else if(key== 'A')  // 1  Список драйверов
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_2:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_drv_list_MMI(&mmi_str);
         sw_mmi=22;
       }
       else if(key== '2')  // Статистика  драйверов
       {
         mmi_str=0;
         max_par=icp_lst_max;
m20_3:
         SetDisplayPage(EmptyPage);  // чистый экран
         f_clr_scr_MMI();
         f_drv_stat_MMI(&mmi_str);
         pass_cnt=0;
         sw_mmi=23;
       }
       else if(key== '3')   //  3  Просмотр/ввод параметров
       {
m_m3_3:
        // переход в меню выбора точки для просмотра параметров
//          SetDisplayPage(11);
          sw_mmi=11;
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню выбора списка просмотра");
            MmiGotoxy(0,2);    MmiPuts("1...6 Список параметров");
//            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

          break;
       }
       else if(key== '4')   //  4  Другие функции
       {
m_m3_4:
         SetDisplayPage(EmptyPage);  // чистый экран
         f_clr_scr_MMI();
            MmiGotoxy(0,0);    MmiPuts(" Меню 5.4.Другие функции. ");
            MmiGotoxy(0,1);    MmiPuts("1  Показания расходомера");
            MmiGotoxy(0,2);    MmiPuts("2  Параметры расходомера");
            MmiGotoxy(0,3);    MmiPuts("3  Ошибки расходомера");
            MmiGotoxy(0,4);    MmiPuts("4  Поиск ICP/RTU модулей");
            MmiGotoxy(0,5);    MmiPuts("5  Список найденных модулей");
//            MmiGotoxy(0,6);    MmiPuts("ESC  Возврат");
                        f_d_ESC();

         sw_mmi=160;
          break;
       }
       else if(key== '5')   //  5  Время, дата
       {
m_m3_5:
         f_prepare_t ( &adate00);
         adate11=adate00;
         SetDisplayPage(EmptyPage);  // чистый экран
         f_clr_scr_MMI();
           MmiGotoxy(0,0);    MmiPuts("      Текущая дата ");
           MmiGotoxy(0,1);    MmiPuts("      День.Мес.Год");
        // MmiGotoxy(0,2);    MmiPuts("        08.01.2009");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("Переход лет/зим.время выключен");
else                          MmiPuts("Переход лет/зим.время включен");

/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - летнее
                              MmiPuts("      Летнее время");
     else                     MmiPuts("      Зимнее время");
*/
            MmiGotoxy(0,4);   MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);   MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);   MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%04d",(int)adate00.day,(int)adate00.month,(int)(adate00.year+2000) );
          fst_n=11;
          sw_fst=1;
          sw_mmi=165;
          break;
       }
       break;
 /*========================================*/
    case 160: // M3.4  Другие функции

       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
           goto m_m3;
       }
       else if(key== '1') //  1  Показания расходомера
       {
         max_par=10;
         mmi_prm=0;

m_m3_4_1v:

         if(ff_serv==NULL)
         {
          SetDisplayPage(EmptyPage);
          f_clr_scr_MMI();
          MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
          sw_MMI_cur=0; // строка MMI
          sw_mvd_m1=mmi_prm+20;  // нач.параметр
          sw_MMI_lim=6; // конечная строка
          MMIDens=-1;
          MMITemp=-300;
          ff_serv=f_MVD_M2;
          sw_mmi=171;
         }
         else
          sw_mmi=173;
         break;
       }

       else if(key== '2') //  2  Параметры расходомера
       {
         max_par=17;
         mmi_prm=0;

m_m3_4_2v:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");

         if(ff_serv==NULL)
         {
          sw_MMI_cur=0; // строка MMI
          sw_mvd_m1=mmi_prm+20;  // нач.параметр
          sw_MMI_lim=6; // конечная строка

          ff_serv=f_MVD_M1;
          sw_mmi=172;
         }
         else
          sw_mmi=174;
         break;
       }
       else if(key== '3') // 3  Ошибки расходомера
       {
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,6);    MmiPuts("ESC,ENTER  Возврат");
         sw_mvd_m1=0;
         ff_serv=f_MVD_M3;
         sw_mmi=180;

         break;

       }

       else if(key== '5') //  5  Список подключенных модулей
       {
         mmi_str=0;
         max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
m20_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         f_mod_list_MMI(&mmi_str);
         sw_mmi=21;
       }
       else if(key== '4')  // 4  Поиск ICP/RTU модулей
       {
m20_4:
          f_clr_scr_MMI();
          MmiGotoxy(1,1);
          MmiPuts("Введите номер порта : " );
          sprintf( fst_str,"%2d",mmi_com);
          fst_n=3;
          sw_fst=1;
          MmiGotoxy(13,3);
          SetDisplayPage(15);
          break;
       }
       else if(key== DATA )
       {
          sscanf(fst_str,"%d",&mmi_com);  // номер COM
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
         MmiGotoxy(0,0);     MmiPrintf("ICP COM%d: таймаут %d мс",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("Макс.Адр %d,флаг CRC=%d",licp_amax,LICP_Rqst.CRC_flag);
       }
       else
       {
         MmiGotoxy(0,0);     MmiPrintf("RTU COM%d: таймаут %d мс",licp_port,ToutLicpScan);
         MmiGotoxy(0,1);  MmiPrintf("Макс.Адр %d",licp_amax);
       }

       MmiGotoxy(0,6);  MmiPuts("  Enter - продолжить");
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

 //  Ввод даты для изменения
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
            // дата введена
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
           MmiGotoxy(0,0);    MmiPuts("      Текущее время ");
           MmiGotoxy(0,1);    MmiPuts("       Час Мин Сек");
        // MmiGotoxy(0,2);    MmiPuts("         08.01.00");
           MmiGotoxy(0,3);
if(FlagWinSum==0)             MmiPuts("Переход лет/зим.время выключен");
else                          MmiPuts("Переход лет/зим.время включен");
/*
 if(ReadNVRAM(nr_win_sum))
 // 1 - летнее
                              MmiPuts("      Летнее время");
     else                     MmiPuts("      Зимнее время");
*/





            MmiGotoxy(0,4);    MmiPuts(" 0...9,'.' - изменить");
            MmiGotoxy(0,5);    MmiPuts(" Enter - ввод");
            MmiGotoxy(0,6);    MmiPuts(" ESC   - отменить");
            MmiGotoxy(8,2);
      sprintf(fst_str,"%02d.%02d.%02d",(int)adate00.hour,(int)adate00.min,(int)adate00.sec);
          fst_n=9;
          sw_fst=1;
          sw_mmi=166;
       }
          break;

 /*========================================*/
    case 166:
 //  Ввод времени
       if((key==ESC)||(key==ENTER)||(key==DATA_ESC))    /* переход в меню */
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
            // время введено
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
    case 21:  // просмотр списка модулей

       max_par=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
       if((key==ESC)||(key==ENTER))   /* переход в меню выбора точки для просмотра*/
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
    case 22: // просмотр списка драйверов

       if((key==ESC)||(key==ENTER))    /* переход в меню выбора точки для просмотра*/
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
    case 23: // просмотр статистики драйверов

       if((key==ESC)||(key==ENTER))    /* переход в меню выбора точки для просмотра*/
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
        {  // обнуление счетчиков ошибок
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
    case 24: // отображение сканирования порта
       if((key==ESC)||(key==ENTER))
       {
           goto m_m3_4; //  4  Другие функции
       }
       else //PASS
       {
          MmiGotoxy(0,3);  MmiPrintf("Опрошено   %3d",licp_addr);
          MmiGotoxy(0,4);  MmiPrintf("Обнаружено %3d",licp_fnd);
       }
       break;
 /*========================================*/
    case 25: // отображение аналоговых входов

       if((key==ESC)||(key==ENTER))
       {
           goto m0_f1;
       }
       else // PASS
       {

   MmiGotoxy(0,1); MmiPrintf(" Давление     %8g (In%d)",(float)ADC[0],analog_num[0]-1);
   MmiGotoxy(0,2); MmiPrintf(" Напряж.акк.  %8g (In%d)",(float)ADC[1],analog_num[1]-1);
   MmiGotoxy(0,3); MmiPrintf(" Напряж.DC24  %8g (In%d)",(float)ADC[2],analog_num[2]-1);

     MmiGotoxy(0,5); MmiPuts(" Аварийная кнопка ");
     if(INP_VARi & E_S)
       MmiPuts(" 1");
     else
       MmiPuts(" 0");

     MmiGotoxy(0,6); MmiPuts(" Сигнал УЗА       ");
     if(INP_VARi & UZA)
       MmiPuts(" 1");
     else
       MmiPuts(" 0");

       }

       break;
 /*========================================*/
    case 26:/* ожидание нажатия ESC,Enter */
         if((key==ESC)||(key==ENTER)  )
         {
          goto m_main;
         }
         break;
 /*========================================*/

    case 27: // отображение дискретных выходов

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
       {  // клапан меньший
        OUT_VAR ^= OUT2;
       }
       else if(key== '2')
       {  // клапан средний
        OUT_VAR ^= OUT1;
       }
       else if(key== '3')
       {  // пар АЦ  out4
        OUT_VAR ^= GAS1;
       }
       else if(key== '4')
       {  // насос PUMP
        OUT_VAR ^= OUT3;
       }
 /*
       else if(key== '3')
       {
          // клапан больший  out7
        OUT_VAR ^= CLP0;
       }
       else if(key== '6')
       {  // пар внешний out5
        OUT_VAR ^= GAS2;
       }
       else if(key== '7')
       {  // ЖФ внешняя  LIQ2
        OUT_VAR ^= OUT6;
       }
*/
       else if(key== '8')
       { // питание
        OUT_VAR ^= OUT8;
       }
       f_prn_proc();

    break;

 /*========================================*/
    case 28:  // Отключение питания :ESC,Enter
         if((key == ENTER) || (key == '1') || (key == F1 ))
         { // отключить питанме
          flag_off = 0;
          Out_off(OUT8);
          flag_uu=1;
          goto m_main;
         }
         if(key==ESC)
         { // отменить отключение питания
          Out_on(OUT8);
          flag_off = 0;
          flag_uu=1;
          goto m_main;
         }
         break;
 /*========================================*/
    case 171://  1  Показания расходомера
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
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка
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

    case 172://  2  Параметры расходомера
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка
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
           MmiGotoxy(0,n_mmi_str_1);  MmiPuts("\"F2\"Пред \"F3\"След \"ESC\"Отмена");
           sw_MMI_cur=0; // строка MMI
           sw_mvd_m1=mmi_prm+20;  // нач.параметр
           sw_MMI_lim=6; // конечная строка

           ff_serv=f_MVD_M1;
           sw_mmi=172;
          }
         }
         break;
 /*========================================*/
    case 180:

       if((key==ESC)||(key==ENTER))  /* переход на начальную страницу */
       {
         if(ff_serv==f_MVD_M3) ff_serv=NULL;
            goto m_m3_4;
       }
       break;
 /*========================================*/
    case 190: //  1  Отпуск СУГ
       if((key==ESC)||(key==ENTER))    /* переход в меню */
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
       else if(key== '1')  // 1  Отпуск дозы СУГ
       {
m_m5_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   Отпуск дозы СУГ");
         f_prn_MassSt_dlv();

         MmiGotoxy(0,2);       MmiPuts(" Введите дозу отпуска,кг");
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
       else if(key== '2')  // 2  Отпуск до опорожнения
       {
m_m5_2:
         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m5_1o;
       }
       else if(key== '3')  // 3 Продолжить с задан. дозой
       {
         if(flag_prn_mass)
          {
           goto m_m5_1o;
          }
       }
       else f_prn_MassSt_dlv();

       break;
 /*========================================*/
    case 191: //  Отпуск  СУГ, выбор режима старта

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

     MmiGotoxy(0,0);
     if(Flag_check == 0)
     {
          if(dose_dlvr != vBIG_P)
             MmiPrintf("Отпуск дозы СУГ %g кг",dose_dlvr);
          else
             MmiPrintf("Отпуск СУГ без дозировки");
     }
     else  MmiPuts(str_verify);

      MmiGotoxy(0,6);   MmiPuts("ESC - завершить.");

      sw_dlv_liq=1;
      sw_mmi=193;

m_m5_1d:
          if(flag_prn_mass)
          {
             MassT=-(s_MVD[0].MassT+s_MVD[1].MassT);
             VolT =-(s_MVD[0].VolT+s_MVD[1].VolTd);
              //  вычисляется в f_MVD_rd() при приеме данных от расходомера паровой фазы
              //  s_MVD[1].VolTd=s_MVD[1].MassT*1000./s_MVD[0].Dens;
          }
          else
          {
             MassT=0.;
             VolT =0.;
          }

          if(Flag_check == 0)
          {
            MmiGotoxy(0,2);MmiPrintf("М=%6.1fкг Отпущено О=%6.1fл",MassT,VolT );
          }
          else
          {
            MmiGotoxy(0,2);
            MmiPuts("           Отпущено          ");

            MmiGotoxy(0,3);
            MmiPrintf("М=%10.3f кг|О=%10.3f л ",MassT,VolT );
          }
          f_prn_proc();
          break;
//===========================================
    case 193: //  Отпуск
       if(key==F2)    // индикация Давление,Температура
       {
           PageD=0;
       }
       else if(key==F3)    // индикация Плотность,Состав
       {
           PageD=1;
       }
       else if(key==F1)    // индикация выходов
       {
           PageD=3;
       }
       key=f_dlv_liq(key);
       if(key==ESC)    // переход в меню
       {
           goto m_m5;
       }
  // отображение общей и отпущенной массы
       goto m_m5_1d;

 /*========================================*/
    case 200: //  2  Прием  СУГ
       if((key==ESC)||(key==ENTER))    /* переход в меню */
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
       else if((key== '1')&&(Flag_check == 0) ) // 1  Прием дозы СУГ
       {
m_m6_1:
         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();
         MmiGotoxy(0,0);       MmiPuts("   Прием  дозы СУГ");
         f_prn_MassSt_rcv();

         MmiGotoxy(0,2);       MmiPuts(" Введите дозу приема ,кг");
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
       else if(key== '2')  // 2  Прием до опорожнения
       {
m_m6_2:
         dose_dlvr=vBIG_P;
         flag_dlv_fst=0;
         flag_prn_mass=0;
         goto m_m6_1o;
       }
       else if(key== '3')  // 3 Продолжить с задан. дозой
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
    case 201: //  Прием СУГ, выбор режима старта

         SetDisplayPage(EmptyPage);
         f_clr_scr_MMI();

     MmiGotoxy(0,0);
     if(Flag_check == 0)
     {
          if(dose_dlvr != vBIG_P)
             MmiPrintf("    Прием дозы СУГ %g кг",dose_dlvr);
          else
             MmiPrintf("  Прием СУГ без дозировки");
     }
     else  MmiPuts(str_verify);

         MmiGotoxy(0,6);   MmiPuts("ESC - завершить.");

         sw_dlv_liq=1;
         sw_mmi=203;


m_m6_1d:
          if(flag_prn_mass)
          {
             MassT=s_MVD[0].MassT+s_MVD[1].MassT;
             VolT =s_MVD[0].VolT+s_MVD[1].VolTd;
              //  вычисляется в f_MVD_rd() при приеме данных от расходомера паровой фазы
              //  s_MVD[1].VolTd=s_MVD[1].MassT*1000./s_MVD[0].Dens;
          }
          else
          {
             MassT=0.;
             VolT =0.;
          }

          if(Flag_check == 0)
          {
            MmiGotoxy(0,2);MmiPrintf("М=%6.1fкг  Принято О=%6.1fл",MassT,VolT );
          }
          else
          {
              MmiGotoxy(0,2);
              MmiPuts("           Принято           ");

              MmiGotoxy(0,3);
              MmiPrintf("М=%10.3f кг|О=%10.3f л ",MassT,VolT );
          }

          f_prn_proc();

          break;
//===========================================
    case 203: //  Прием
       if(key==F2)    // индикация Давление,Температура
       {
           PageD=0;
       }
       else if(key==F3)    // индикация Плотность,Состав
       {
           PageD=1;
       }
       else if(key==F1)    // индикация выходов
       {
           PageD=3;
       }
       key=f_rcv_liq(key);
       if(key==ESC)    // переход в меню
       {
           goto m_m6;
       }
  // отображение общей и отпущенной массы
       goto m_m6_1d;
//-------------------
    case 205:  // Прием/Отпуск СУГ без учета
               // ожидание завершения задания направления счета MVD[0]

    if( MVD_t_rslt[0]>0)
    { // останов счета в обоих расходомерах

      // Stop totalizers
       MVD_t_rslt[0]=0;
       MVD_t_rslt[1]=0;
       f_MVD_WR((int)0,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,0);
       f_MVD_WR((int)1,(int)MVD_WR_C,(int) 2,(int)0,(long int) 0,0);
       sw_mmi=206;
       time_t_snd=TimeStamp;
    }
    if( f_timer(time_t_snd,f_MVD_tim + f_MVD_tim ) )
    {  // время вышло
        time_t_snd=TimeStamp;
        MVD_t_rslt[0]=1;
        MVD_t_rslt[1]=1;
    }
    break;
//-------------------
    case 206: // Прием/Отпуск СУГ без учета
          // ожидание завершения останова Totals

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // обнуление среза FlowM  в обоих расходомерах
      // FlowM = 0

       MVD_t_rslt[0]=0;
       MVD_t_rslt[1]=0;

       f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,0);
       f_MVD_WR((int)1,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,0);

       sw_mmi=207;
    }
    if( f_timer(time_t_snd,f_MVD_tim + f_MVD_tim ) )
    {  // время вышло
      MVD_t_rslt[0]=1;
      MVD_t_rslt[1]=1;
    }
    break;
//-------------------
    case 207: // Прием/Отпуск СУГ без учета
          // ожидание обнуления среза FlowM  в обоих расходомерах

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // ожидание обнуления среза FlowM  в обоих расходомерах завершено
      // FlowM = 0
       sw_mmi=210;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // время вышло
      MVD_t_rslt[0]=1;
      MVD_t_rslt[1]=1;
    }
    break;

//-------------------

    case 210: // Прием/Отпуск СУГ без учета

       PageD=3;

       if(key== '1')
       {  // клапан меньший
        OUT_VAR ^= OUT2;
        break;
       }
       else if(key== '2')
       {  // клапан средний
        OUT_VAR ^= OUT1;
        break;
       }
       else if(key== '3')
       {  // пар АЦ  out4
        OUT_VAR ^= GAS1;
        break;
       }
       else if(key== '4')
       {  // насос PUMP
        OUT_VAR ^= OUT3;
        break;
       }
       else if(key==ESC)    // переход в меню
       {
         PageD=0;
         flag_v2=1;
         OUT_VAR = OUT8;
         f_wr_evt(evt_NCNT_off);

         sw_mmi=212;
        // установка среза FlowM для режима ожидания
        f_MVD_WR((int)0,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,Cut_Mass[0]);
        f_MVD_WR((int)1,(int)MVD_WR_F,(int) 195,(int)0,(long int) 0,Cut_Mass[1]);
        break;
       }
/*
       else if(key==F1)    // индикация Help
       {
        f_dsp_H3();
        Ret_cod= sw_mmi;
        sw_mmi=220;
        break;
       }
*/
         MmiGotoxy(0,2);  MmiPrintf("Ж:%5.0fкг/ч|%5.1fкг/м3|%5.1f C",s_MVD[0].FlowM,s_MVD[0].Dens,s_MVD[0].Temp);
         MmiGotoxy(0,3);  MmiPrintf("П:%5.0fкг/ч|%5.1fкг/м3|%5.1f C",s_MVD[1].FlowM,s_MVD[1].Dens,s_MVD[1].Temp);
         f_prn_proc();
//       f_dsp_ncnt();
       break;

//-------------------------------------------
    case 212: // Прием/Отпуск СУГ без учета
          // ожидание установки среза FlowM для режима ожидания в обоих расходомерах

    if(( MVD_t_rslt[1]>0) && ( MVD_t_rslt[0]>0))
    {
      // ожидание установки среза FlowM  в обоих расходомерах завершено
      goto main_menu;
    }
    if( f_timer(time_t_snd,f_MVD_tim ) )
    {  // время вышло
      goto main_menu;
    }
    break;
//-------------------------------------------
    case 220: // Out from Help
 /*========================================*/
       if((key==ESC)||(key==ENTER))    /* переход в меню */
       {
         switch(Ret_cod)
         {
             //  1  Отпуск СУГ
           case 190:  goto m_m5;
           case 200:  goto m_m6;
           case 210:
           case 211:
                      SetDisplayPage(EmptyPage);
                      f_clr_scr_MMI();
                      MmiGotoxy(0,0); MmiPuts("Прием/Отпуск СУГ без учета");
                      MmiGotoxy(0,6); MmiPuts(kran_ch);
                      sw_mmi=Ret_cod;
                      break;
           default:  goto m_main;
         }
       }
       break;
 /*========================================*/
    case 230: // Поверка

          SetDisplayPage(EmptyPage);
          f_clr_scr_MMI();
         MmiGotoxy(0,0);
         MmiPrintf("  Поверка расходомера ");
         sw_pov=1;

         sw_mmi=231;


 /*========================================*/

    case 231: // Поверка
       if(key==F2)    // индикация Давление,Температура
       {
           PageD=0;
       }
       else if(key==F3)    // индикация Плотность,Состав
       {
           PageD=1;
       }
       else if(key==F1)    // индикация выходов
       {
           PageD=3;
       }
       key=f_pov(key);
       if(key==ESC)    // переход в меню
       {
           sw_pov=0;
           f_wr_evt(evt_verify_e);
           goto m0_f1;
       }

       MmiGotoxy(0,3);
              MmiPrintf("M=%9.3f кг |",s_MVD[0].MassI);  // VolT_id, VolT_int
       MmiGotoxy(15,3);
              MmiPrintf("|П=%9.3f кг",s_MVD[0].MassT);  // VolT_id, VolT_int
       f_prn_proc();
       break;

 /*========================================*/
       default:
       if((key==ESC)||(key==ENTER))  /* переход на начальную страницу */
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