
// Массовый расходомер Micro Motion MVD

#define Max_CL_V  30

float FctBern=0;

void (*ff_serv_N)()=NULL;
#define RTU_MVD
//---------------
struct s_icp_dev MVD[max_MVD]=
{
// device 1, ЖФ
0,                // status
2,                // port
1,                // addr
"MVD/1",          // name[8]
06,               // baudrate_cod
0x00,             // type
0x00,             // format
0x00,             // channels
"B1.7",           // firmware
1,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&MVD_Rqst[0],   // *request
//--------------------------------
// device 2  , ПФ
//--------------------------------
0,                // status
2,                // port
2,                // addr
"MVD/2",        // name[8]
06,               // baudrate_cod
0x00,             // type
0x00,             // format
0x00,             // channels
"B1.7",           // firmware
1,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&MVD_Rqst[1],   // *request
};
/*----------------------------*/
struct COM_rqst MVD_Rqst[max_MVD]={
//----------------------
// device 1
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVD_rd,            //  answ_com
f_MVD_rd,            //  answ_flt
"MVD/1",              //  name
0,                     //  n_dev номер устройства в группе однотипных устройств
&MVD[0],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
//--------------------------
// device 2
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVD_rd,            //  answ_com
f_MVD_rd,            //  answ_flt
"MVD/2",              //  name
1,                     //  n_dev номер устройства в группе однотипных устройств
&MVD[1],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
};
/*----------------------------*/
struct COM_rqst MVD_Rqst_T[max_MVD]={
//----------------------
// device 1
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVD_rd_t,            //  answ_com
f_MVD_rd_t,            //  answ_flt
"MVD/1",               //  name
0,                     //  n_dev номер устройства в группе однотипных устройств
&MVD[0],               //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,        //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
//--------------------------
// device 2
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVD_rd_t,            //  answ_com
f_MVD_rd_t,            //  answ_flt
"MVD/2",               //  name
1,                     //  n_dev номер устройства в группе однотипных устройств
&MVD[1],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
};
/*----------------------------*/
struct s_MVD_dev s_MVD[max_MVD]=
{
0 , //int r_addr;       // address of MODBUS register
0,  //int n;            // number of data - for read coils and ascii
0,  //int type;         // data type
0,  //int i;            // int,coil value for write
0,  //int exc;          // exception
0,  //long int  l;      // long
0,    //float f;          // float

-1.0, //float FlowM;         // float
-1.0, //float FlowV;         // float
111.111, //BIG_P, //float MassI;        // float
00.0, //float MassT;         // float
0.1,  //float VolI;          // float
00.0, //float VolT;          // float
-1.0, //float VolTd;         // float
-1.0, //float Temp;          // float
-1.0, //float Dens;          // float
-1.0, //float Dens;          // float
-1.0, //float Compos;        // float
-1.0, //float PressG;        // float
-1.0, //float PressB;        // float
-1.0, //float PressD;        // float
-1.0, //float PressGN;       // float
27.0, //float Volt_A         // float
27.0, //float Volt_DC        // float

"",   //char c[n_coil_b]; // coil(s) value(s) read from MVD
"",   //char a[n_char_b]; // ascii
0,    //int reg_err;
//------------------------------------------
0 , //int r_addr;       // address of MODBUS register
0,  //int n;            // number of data - for read coils and ascii
0,  //int type;         // data type
0,  //int i;            // int,coil value for write
0,  //int exc;          // exception
0,  //long int  l;      // long
0,    //float f;          // float

-1.0, //float FlowM;         // float
-1.0, //float FlowV;         // float
222.222, //BIG_P, //float MassI;        // float
00.0, //float MassT;         // float
0.1,  //float VolI;          // float
00.0, //float VolT;          // float
00.0, //float VolTd;         // float
-1.0, //float Temp;          // float
-1.0, //float Dens;          // float
-1.0, //float Dens;          // float
-1.0, //float Compos;        // float
-1.0, //float PressG;        // float
-1.0, //float PressB;        // float
-1.0, //float PressD;        // float
-1.0, //float PressGN;       // float
-1.0, //float Volt_A         // float
-1.0, //float Volt_DC        // float

"",   //char c[n_coil_b]; // coil(s) value(s) read from MVD
"",   //char a[n_char_b]; // ascii
0,    //int reg_err;


};
//--------------------------------
float Dens0=1000.;
float Mas2=0,k_Mas=1.;
long int tt_Mas1=0;
long int tt_Mas2=0;
//--------------------------------

int MVD_fn[max_MVD]={0,0};    // регистр функций драйвера

//  Если записать значение функции в регистр функции , например:
//  ComSK_fn[0]= RES_SK_ERR;  драйвер выполнит заданную функцию - в данном случае
// пошлет в устройство ComSK команду сброса привода.
//  После постановки запроса с установленной функцией в очередь на вывод в COM,
// регистр функции очищается драйвером.

int MVD_sw[max_MVD]={0,0};

unsigned int MVD_inp_err[max_MVD]={0,0};  // счетчик ошибок ввода

  // последовательность функций опроса
/*
int MVD_seq[16]={
mMassT, mDens ,mMassT, mMassI,
mMassT, mDens ,mMassT, mTemp,
mMassT, mDens ,mMassT, mVolI,
mMassT, mDens ,mMassT, mErr,
};
*/
int MVD_seq[16]={
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
};

int fl_rd_err=0;
int MVD_fl[max_MVD]={0,0};
unsigned char MVD_Rd_err[] ={1,3,0x01,0xa2,0x00,0x01};  // R419 - регистр ошибки
unsigned char MVD_Rd_FlowM[]={1,3,0x00,0xF6,0x00,0x02}; // R247  - mass flow
unsigned char MVD_Rd_Dens[]={1,3,0x00,0xF8,0x00,0x02};  // R249  - Density
unsigned char MVD_Rd_Temp[]={1,3,0x00,0xFA,0x00,0x02};  // R251  - Temperature
unsigned char MVD_Rd_FlowV[]={1,3,0x00,0xFC,0x00,0x02}; // R253  - volume flow

unsigned char MVD_Rd_Press[]={1,3,0x01,0x00,0x00,0x02}; // R257  - pressure
unsigned char MVD_Rd_MassT[]={1,3,0x01,0x02,0x00,0x02}; // R259  - mass total
unsigned char MVD_Rd_VolT[] ={1,3,0x01,0x04,0x00,0x02}; // R261  - volume total
unsigned char MVD_Rd_MassI[]={1,3,0x01,0x06,0x00,0x02}; // R263  - mass inventory
unsigned char MVD_Rd_VolI[]={1,3,0x01,0x08,0x00,0x02};  // R265  - Volume inventory

unsigned char MVD_Rd_Slot[]={1,3,0x02,0xae,0x00,0x0F};  // R687-1  - Slot data , 15 registers 16 bit

// R419 - регистр ошибки , int
// R247 - mass flow      , float
// R259 - mass total     , float
// R261 - volume total   , float


void f_MVD(int ii)
{
 // ii - номер устройства
 //  Функция циклически шлет запрос на получение данных  из
 // устройства MVD  '01 03 01A2 0001' - R419 - регистр ошибки,
 //
 //   Период посылки MVD[ii].pool_time мс.
 //
 //    Если  регистр функции != 0 - заданная функция выполняется
 //  в первую очередь ( приоритет выше, чем приоритет циклического опроса).
 //   После постановки запроса с указанной функцией в очередь COM порта
 //  в регистр функции записывается F_PROGRESS
 //  После приема ответа от устройства в регистр функции запишется либо 0 - OK,
 // либо F_FAULT

int i,fn,sw,i2,itmp;
long int i1,l_tmp;
union  { float f; unsigned long l; } o;
unsigned char buf_tmp[20];

 if(MVD[ii].status == 0) return;

 if( MVD_fl[ii] >= 0 )
            f_init_MVD(ii);

  if((MVD_Rqst[ii].status == Req_Flt) ||
     (MVD_Rqst[ii].status == Req_OK));
  else return;

 if(f_queue_chk(MVD[ii].port)== 0) return;// очередь переполнена

 if((MVD_fn[ii] != 0) && (MVD_fn[ii] < F_PROGRESS))
      fn=MVD_fn[ii];
 else if( f_timer(MVD[ii].time_stamp_pool,MVD[ii].pool_time ))
      fn=MVD_RD_P;
 else return;

      switch(fn)
      {
        case MVD_RD_I :
           // чтение данных Integer
            buf_tmp[5]=1;
 m_rdi:
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=3;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
            buf_tmp[4]=0;
            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case  MVD_RD_L :
          case  MVD_RD_F:
           // чтение данных Long, Float

           buf_tmp[5]=2;
          goto m_rdi;

          case MVD_RD_C:
           // чтение данных Coil
            buf_tmp[1]=1;
     m_rdc:
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
            buf_tmp[4]=(s_MVD[ii].n>> 8) & 0xff;
            buf_tmp[5]= s_MVD[ii].n & 0xff;
            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case MVD_RD_S:
           // чтение данных String
            buf_tmp[1]=3;
            goto m_rdc;

          case MVD_WR_I :
           // запись данных Integer
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=6;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
            buf_tmp[4]=(s_MVD[ii].i>> 8) & 0xff;
            buf_tmp[5]= s_MVD[ii].i & 0xff;
            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case MVD_WR_L :
           // запись данных Long
            i1=11;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
             l_tmp=s_MVD[ii].l;
            buf_tmp[7]=(l_tmp >> 24) & 0xff;         // количество регистров
            buf_tmp[8]=(l_tmp >> 16) & 0xff;         // количество регистров
            buf_tmp[9]=(l_tmp >> 8)  & 0xff;         // количество регистров
            buf_tmp[10]=l_tmp & 0xff;    // количество регистров

            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case MVD_WR_F :
           // запись данных Float
            i1=11;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
            o.f=s_MVD[ii].f;
            buf_tmp[7] =(o.l >> 8 ) & 0xff;
            buf_tmp[8] =(o.l >> 0 ) & 0xff;
            buf_tmp[9] =(o.l >> 24)  & 0xff;
            buf_tmp[10]=(o.l >> 16) & 0xff;

            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case MVD_WR_C :
           // запись данных Coil
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=5;
            buf_tmp[2]=((s_MVD[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVD[ii].r_addr-1) & 0xff;
//          if(s_MVD[ii].w_coil != 0)
            if(s_MVD[ii].i != 0)
               buf_tmp[4]= 0xff;
            else
               buf_tmp[4]= 0;
            buf_tmp[5]= 0;
            MVD_fn[ii]=F_PROGRESS;
            s_MVD[ii].type=fn;
            s_MVD[ii].exc=-1;
            break;

          case MVD_RD_P:  // циклическое  чтение состояния
          // формирует команды чтения
             MVD_sw[ii]=(MVD_sw[ii]+1) & 0xf;
             sw=MVD_seq[MVD_sw[ii]];
             i1=6;
             MVD_fn[ii]=0;
             switch (sw)
             {
              case mErr:
            _fmemcpy(buf_tmp,MVD_Rd_err,(long int)i1);
                break;

              case mVolT:
             _fmemcpy(buf_tmp,MVD_Rd_VolT,(long int)i1);
                break;

              case mDens:
             _fmemcpy(buf_tmp,MVD_Rd_Dens,(long int)i1);
                break;
       /*
              case mFlowM:
             _fmemcpy(buf_tmp,MVD_Rd_FlowM,(long int)i1);
                break;
       */
              case mSlot:
             _fmemcpy(buf_tmp,MVD_Rd_Slot,(long int)i1);
                break;
              case mMassT:
             _fmemcpy(buf_tmp,MVD_Rd_MassT,(long int)i1);
                break;

      //      case mFlowV:
      //     _fmemcpy(buf_tmp,MVD_Rd_FlowV,(long int)i1);
      //        break;

              case mTemp:
             _fmemcpy(buf_tmp,MVD_Rd_Temp,(long int)i1);
                break;

              case mVolI:
             _fmemcpy(buf_tmp,MVD_Rd_VolI,(long int)i1);
                break;

              case mMassI:
             _fmemcpy(buf_tmp,MVD_Rd_MassI,(long int)i1);
                break;

              default:
                return;
             }
             buf_tmp[0]=MVD[ii].addr;
             fn+=sw;
             break;

          default:
          MVD_fn[ii]=0;
          return;
      }
           MVD_Rqst[ii].function = fn;
           i2=i1;
           f_prepareRTU(buf_tmp,&i2);
           _fmemcpy(MVD_Rqst[ii].Cmd,buf_tmp,(long)i2);
           MVD_Rqst[ii].cmd_lgth=i2;
           MVD_Rqst[ii].time_stamp=TimeStamp;
           MVD[ii].time_stamp_pool=TimeStamp;
           MVD[ii].n_transaction++;
           f_queue_put(MVD[ii].port, &MVD_Rqst[ii]) ;
}
/*----------------------------*/
int f_MVD_WR(int ii,int fn,int addr,int i_val,long int l_val,float f_val)
{
 // записывает значение в регистр MVD
 // ii - номер устройства
int i,sw,i2,itmp;
long int i1;
union  { float f; unsigned long l; } o;
unsigned char buf_tmp[20];

// if(MVD[ii].status == 0) return 0;

#if(SIM0 != 0)
 if(MVD[ii].status == 0)
 {
   MVD_t_rslt[ii]=1;
   return 1;
 }
#endif


 switch(ii)
 {
  case 0:
    if(ICP_error[MVD1] != 0)  return 0;
    break;
  case 1:
    if(ICP_error[MVD2] != 0)  return 0;
    break;

  default: return 0;
 }

  if((MVD_Rqst_T[ii].status == Req_Flt) ||
     (MVD_Rqst_T[ii].status == Req_OK));
  else return 0;

 if(f_queue_chk(MVD[ii].port)== 0) return 0;// очередь переполнена
     switch(fn)
      {
          case MVD_WR_I :
           // запись данных Integer
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=6;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]=(i_val>> 8) & 0xff;
            buf_tmp[5]= i_val & 0xff;
            break;

          case MVD_WR_L :
           // запись данных Long
            i1=11;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
            buf_tmp[7]=(l_val >> 24) & 0xff;         // B3  -- данные --
            buf_tmp[8]=(l_val >> 16) & 0xff;         // B2
            buf_tmp[9]=(l_val >> 8)  & 0xff;         // B1
            buf_tmp[10]=l_val & 0xff;                // B0

            break;

          case MVD_WR_F :
           // запись данных Float
            i1=11;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
            o.f=f_val;
            buf_tmp[7] =(o.l >> 8 ) & 0xff;
            buf_tmp[8] =(o.l >> 0 ) & 0xff;
            buf_tmp[9] =(o.l >> 24)  & 0xff;
            buf_tmp[10]=(o.l >> 16) & 0xff;
            break;

          case MVD_WR_C :
           // запись данных Coil
            i1=6;
            buf_tmp[0]=MVD[ii].addr;
            buf_tmp[1]=5;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            if(i_val != 0)
               buf_tmp[4]= 0xff;
            else
               buf_tmp[4]= 0;
            buf_tmp[5]= 0;
            break;

          default:
          return 0;
      }

           MVD_Rqst_T[ii].function = fn;
           i2=i1;
           f_prepareRTU(buf_tmp,&i2);
           _fmemcpy(MVD_Rqst_T[ii].Cmd,buf_tmp,(long)i2);
           MVD_Rqst_T[ii].cmd_lgth=i2;
           MVD_Rqst_T[ii].time_stamp=TimeStamp;
           MVD[ii].n_transaction++;
           MVD_t_err[ii]=0;
           f_queue_put(MVD[ii].port, &MVD_Rqst_T[ii]) ;
           return 1;
}
/*----------------------------*/
int  MVD_t_err[max_MVD]={0,0};
int  MVD_t_rslt[max_MVD]={0,0};

void f_MVD_rd_t(int ii)
{   // принят ответ на команду записи в MVD
// ii - номер порта
// заносит принятые данные в переменные
//
 struct COM_rqst *request;
 int i,nn,i1,im;
 int count,tmp;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // номер устройства MVD (0,1..)

 count=n_bcom[ii];  // длина команды
 if(count < 3)
   {
      goto m_tout_err;
   }
 if(f_check_crc_RTU(cb_COM[ii],count)==0)
   {
      goto m_crc_err;
   }
 if(cb_COM[ii][1] & 0x80)
   {
     s_MVD[nn].exc=cb_COM[ii][2];
     goto m_end;
   }
    // ответ на команду записи
  if ((cb_COM[ii][1] == 6)  || (cb_COM[ii][1] == 16) ||(cb_COM[ii][1] == 5));
  else  goto m_crc_err;

  MVD_t_rslt[nn]+=1;
 m_end:
  MVD[nn].n_success++;
  MVD_inp_err[nn]=0;
  f_queue_free(ii,&MVD_Rqst_T[nn]);
  MVD_t_err[nn]=0;
  return;

m_crc_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_CRC_error++;
 goto m_err;

m_tout_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_timeout_error++;

m_err:
 MVD_t_err[nn]++;

 f_queue_free(ii,&MVD_Rqst_T[nn]);
 if(MVD_t_err[nn]>=MVD_max_t_err)
 {
   MVD_t_err[nn]=MVD_max_t_err;
   f_icp_error(&MVD[nn],WR_ERR );
 }
 else
 {
  MVD_Rqst_T[nn].time_stamp=TimeStamp;
  f_queue_put(ii, &MVD_Rqst_T[nn]) ;
 }
  MVD[nn].n_transaction++;
}
/* ---------------------------------------- */
void f_MVD_rd_tS(int ii)
{   // принят ответ на команду записи в MVD
// ii - номер порта
// старт наполнения
//
 struct COM_rqst *request;
 int i,nn,i1,im;
 int count,tmp;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // номер устройства MVD (0,1..)

 count=n_bcom[ii];  // длина команды
 if(count < 3)
   {
      goto m_tout_err;
   }
 if(f_check_crc_RTU(cb_COM[ii],count)==0)
   {
      goto m_crc_err;
   }
 if(cb_COM[ii][1] & 0x80)
   {
     s_MVD[nn].exc=cb_COM[ii][2];
     goto m_end;
   }
    // ответ на команду записи
  if ((cb_COM[ii][1] == 6)  || (cb_COM[ii][1] == 16) ||(cb_COM[ii][1] == 5));
  else  goto m_crc_err;


 m_end:
  MVD[nn].n_success++;
  MVD_inp_err[nn]=0;
  f_queue_free(ii,&MVD_Rqst_T[nn]);
  MVD_t_err[nn]=0;

  vol2=0;
  VolT_int=0;
  VolT_id=0;
//  f_enable_cnt();
//  tt_vol1=TimeStamp;
  return;

m_crc_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_CRC_error++;
 goto m_err;

m_tout_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_timeout_error++;

m_err:
 MVD_t_err[nn]++;

 f_queue_free(ii,&MVD_Rqst_T[nn]);
 if(MVD_t_err[nn]>=MVD_max_t_err)
 {
   MVD_t_err[nn]=MVD_max_t_err;
   f_icp_error(&MVD[nn],WR_ERR );
 }
 else
 {
 MVD_Rqst_T[nn].time_stamp=TimeStamp;
 f_queue_put(ii, &MVD_Rqst_T[nn]) ;
 }
 MVD[nn].n_transaction++;
}
/* ---------------------------------------- */
/*----------------------------*/
unsigned long int MVDit[max_MVD];
int n_send[max_MVD];
int flag_mvd_fst[max_MVD]={0,0};
int flag_mvd_ton[max_MVD]={0,0};

int ii_MVD_i[max_MVD]={0,0};
int ii_MVD_fl[max_MVD]={0,0};

float  TimeMVD_Init=30000;  // Max Init time for MVD,ms
float  TimeMVD_evt =1000 ;  // time for generate event,ms

struct mvd_init {
int addr;
int val;
};

struct mvd_init MVD_i[]=
{
 655,258, // Mass total     687 --    1
 656,248, // Density        689 --    2
 657,250, // Temperature    691 --    3
 658,262, // Mass inventory 693 --    4

 659,264, // Volume invntry 695 --    5
// 659,252, // Volume flow    701 --
 660,246, // Mass flow      697 --    6

 661,260, // Volume total   699 --    7
 662,418, // Error          701 --    8
 39,75,  // unit for mass flow,kg/hour
 42,24,  // Volume flow  l/sec
 40,92,  // Density unit kg/m3 --
//  45,61,  // unit for mass total,61- kg, 60-g
//  46,41,  // unit for volume total, l
 41,32,  // unit for temperature, C

 17,2 ,   // Flow direction code: 0 - forward flow  only
          //                      2 - bidirectional flow
          //                      5 - reverce bidirectional flow
};

int ii_MVD_max=sizeof(MVD_i) / sizeof(MVD_i[0]);
//----------------------------------------------

float Cut_Vol[3]={3.,3.,3.};
float Cut_Mass[3]={3000.,3000.,3000.};

void f_init_MVD(int ii)
 {

 float ftmp1,ftmp2;

 union  { float f; unsigned long l; } o;

  if((MVD_fn[ii] != 0) && (MVD_fn[ii] != F_FAULT))
  {
    return;
  }
  switch (MVD_fl[ii])
   {
    case 0:
      n_send[ii]=0;
       MVD_fl[ii]++;
       break;

    case 1:  // проверяет текущее значение порядка
             // следования байт в регистрах float
             // если не 1 , то устанавливает =1.

      if(MVD_fn[ii] != 0) break;
      MVD_fn[ii]=MVD_RD_I;;
      s_MVD[ii].r_addr=521; // I521  Byte order code for float registers
      MVD_fl[ii]++;
      break;

    case 2:

      flag_mvd_ton[ii]=1;
      if(sw_mmi==0) f_prn_begin();

      if((MVD_fn[ii] == F_FAULT) || (s_MVD[ii].i == 1) )
       { // byte order is correct or RFT9739 device connected
         MVD_fl[ii]=3;
         ii_MVD_i[ii]=0;
         ii_MVD_fl[ii]=0;
         n_send[ii]=0;
         break;
       }
       MVD_fn[ii]=MVD_WR_I;
       s_MVD[ii].r_addr=521; // I521  Byte order code  for float registers
       s_MVD[ii].i = 1;
       if((n_send[ii]++) > 3)
       {
         flag_mvd_ton[ii]=0;
//    if(flag_prn)
//      printf("\n\rfault of 3 attempts to wtite conf. A521 MVD%d",ii);
         f_icp_error(&MVD[ii],WR_ERR );
         MVD_fl[ii]=-1;
       }
       MVD_fl[ii]=1;
       break;

    case 3:
      MVD_fn[ii]=MVD_RD_I;
      s_MVD[ii].r_addr=MVD_i[ii_MVD_i[ii]].addr;
      MVD_fl[ii]=4;
      break;

    case 4:
      if(s_MVD[ii].i == MVD_i[ii_MVD_i[ii]].val);
      else ii_MVD_fl[ii]=1;
      ii_MVD_i[ii]++;
      if(ii_MVD_i[ii] >= ii_MVD_max)
      {
        if( ii_MVD_fl[ii] == 0 )
        { // значения записаны корректно
         if(flag_prn)
         printf("\r\nMVD%d  Slot OK,%d values",ii,ii_MVD_i[ii]);
         MVD_fl[ii]=53;
         break;
        }
        else
        { // значения нужно записать

         if((n_send[ii]++) > 3)
         { // за 3 попытки записать не удалось
           flag_mvd_ton[ii]=0;
//    if(flag_prn)
//      printf("\n\rfault of 3 attempts to wtite conf.MVD%d",ii);
//         f_icp_error(&MVD[ii],WR_ERR );
           f_icp_errS(MVD_cfg);
           MVD_fl[ii]=-1;
           break;
         }

      if(flag_prn)
        printf("\r\nMVD%d.Slot need to write",ii);
         f_wr_evt(evt_Slot);
         MVD_fl[ii]=5;
         ii_MVD_i[ii]=0;
         ii_MVD_fl[ii]=0;
         break;
        }
      }
      else
      {
        MVD_fl[ii]=3;
        break;
      }

//--------------------------
    case 5: // запись значений Slot
      MVD_fn[ii]=MVD_WR_I;;
      s_MVD[ii].r_addr=MVD_i[ii_MVD_i[ii]].addr;
      s_MVD[ii].i = MVD_i[ii_MVD_i[ii]].val;

      ii_MVD_i[ii]++;
      if(ii_MVD_i[ii] >= ii_MVD_max)
      {  // все значения записаны , проверить запись

      if(flag_prn)
         printf("\r\n MVD%d,Slot is wrote,%d values",ii,ii_MVD_i[ii]);
         ii_MVD_i[ii]=0;
         ii_MVD_fl[ii]=0;
         MVD_fl[ii]=3;
         break;
      }
      break;
//------------------------------------

    case 53:
    if( f_timer(0L,TimeMVD_Init ) )
       flag_mvd_fst[ii] = 0;
    else
//    if(f_get_icp_error(&MVD[ii]))
        flag_mvd_fst[ii] = 1;

     MVD_fl[ii]++;

     case 54:
     if(flag_mvd_fst[ii])
       if( f_timer(0L,TimeMVD_Init ) == 0 ) break;
      flag_mvd_ton[ii]=0;
      f_icp_error(&MVD[ii],0 );
    if(sw_mmi==0) f_prn_begin();

// printf("\n\r MVD init finished");// qqq

       MVD[ii].n_transaction    = 0;
       MVD[ii].n_success        = 0;
       MVD[ii].n_timeout_error  = 0;
       MVD[ii].n_CRC_error      = 0;

       MVDit[ii]=TimeStamp;
       MVD_fl[ii]=80;
       break;

   case 80:
       // cutoff for Mass Flow
      MVD_fn[ii]=MVD_WR_F;
      s_MVD[ii].r_addr = 195;
      s_MVD[ii].f= Cut_Mass[ii];
      MVD_fl[ii]=81;
       break;

   case 81:
       // cutoff for Vol Flow
      MVD_fn[ii]=MVD_WR_F;
      s_MVD[ii].r_addr = 197;
      s_MVD[ii].f= Cut_Vol[ii];
      MVD_fl[ii]=55;
       break;

     case 55:
       MVD_fl[ii]=-1;
       break;

    case -1:
       break;
    default:break;
   }
 }
//-----------------------------------------





//-----------------------------------------
unsigned int f_get_int( char *buf)
{
unsigned int itmp;
        itmp=(buf[4] & 0xff) | ( ((unsigned int)buf[3] << 8) &0xff00)  ;
        return itmp;
}
//-----------------------------------------
float f_get_float( char *buf, int cod)
{
 union  { float f; unsigned long l; } o;

     switch(cod)  // ( Reg 0521 )
     {
     case 0:
    //  code == 0 : 0  1  2  3
    //             [3][4][5][6]
     o.l=
         ( (unsigned long)buf[6]  &0xff) |                // 3
         ( ((unsigned long)buf[5] << 8) &0xff00) |        // 2
         ( ((unsigned long)buf[4] << 16) &0xff0000)  |    // 1
         ( ((unsigned long)buf[3] << 24) &0xff000000);    // 0
        break;
     case 1:
    //  code == 1 : 2  3  0  1
    //             [3][4][5][6]
     o.l=
         (  (unsigned long)buf[4]  &  0x000000ff) |        // 3
         ( ((unsigned long)buf[3] << 8) &  0x0000ff00) |   // 2
         ( ((unsigned long)buf[6] << 16) & 0x00ff0000)  |  // 1
         ( ((unsigned long)buf[5] << 24) & 0xff000000);    // 0
         break;
      case 2:
    //  code == 2 : 1  0  3  2
    //             [3][4][5][6]

     o.l=
         ( (unsigned long)buf[5]  &0xff) |              // 3
         ( ((unsigned long)buf[6] << 8) &0xff00) |      // 2
         ( ((unsigned long)buf[3] << 16) &0xff0000)  |  // 1
         ( ((unsigned long)buf[4] << 24) &0xff000000);  // 0
         break;
      case 3:
    //  code == 3 : 3  2  1  0
    //             [3][4][5][6]
     o.l=( (unsigned long)(buf[3]) & 0x000000ff) |      // 3
         ( ((unsigned long)buf[4] << 8) &0xff00) |      // 2
         ( ((unsigned long)buf[5] << 16) &0xff0000)  |  // 1
         ( ((unsigned long)buf[6] << 24) &0xff000000);  // 0
       break;
       default : return 0.;
     }

  if(( o.l == 0x7fa00000) || ( o.l == 0x00007fa0))
     o.f= BIG_P;
  return o.f;

}
//-----------------------------------------
int ModeFill=2;
long int tim_snd_MVD=0;

void f_MVD_rd(int ii)
{
float ftmp;
// ii - номер порта
// заносит принятые данные в переменные
//
 struct COM_rqst *request;
 int i,nn,fn,i1,im;
 int count,tmp;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // номер устройства MVD (0,1..)
 fn=request->function;

 count=n_bcom[ii];  // длина команды
 if(count < 3)
   {
      goto m_tout_err;
   }
 if(f_check_crc_RTU(cb_COM[ii],count)==0)
   {
      goto m_crc_err;
   }
 if(cb_COM[ii][1] & 0x80)
   {
     s_MVD[nn].exc=cb_COM[ii][2];
     MVD_fn[nn]=F_FAULT ;
     goto m_end;
   }
 if(( fn & 0xf8)==MVD_RD_P) // ответ на команду циклического опроса
  {
      fn &= 0x7;
      switch(  fn )
      {

      case mSlot:    // чтение Slot data

       if(count < 33)
       {
         goto m_tout_err;
       }
        s_MVD[nn].MassT= f_get_float( &cb_COM[ii][0], 1);
//      s_MVD[nn].Dens=  f_get_float( &cb_COM[ii][4], 1);
        ftmp = f_get_float( &cb_COM[ii][4], 1);
        if(ftmp <=0.0001) ftmp=0.001;
        s_MVD[nn].Dens = ftmp;

        s_MVD[nn].Temp=  f_get_float( &cb_COM[ii][8], 1);
        s_MVD[nn].MassI=  f_get_float( &cb_COM[ii][12], 1);
        s_MVD[nn].VolI =  f_get_float( &cb_COM[ii][16], 1);
//      s_MVD[nn].FlowV =  f_get_float( &cb_COM[ii][16], 1); // 9,10
        s_MVD[nn].FlowM=  f_get_float( &cb_COM[ii][20], 1);
//      if(s_MVD[nn].Dens > 0.002) s_MVD[nn].FlowV=s_MVD[nn].FlowM/(s_MVD[nn].Dens/1000.);
        if(s_MVD[nn].Dens > 0.002) s_MVD[nn].FlowV=s_MVD[nn].FlowM/(s_MVD[nn].Dens);
        s_MVD[nn].VolT =  f_get_float( &cb_COM[ii][24], 1);
        s_MVD[nn].reg_err=  f_get_int( &cb_COM[ii][28]);

//      s_MVD[nn].VolT =  s_MVD[nn].VolI - VolI_beg;
        tim_snd_MVD=Tm_snd[ii];
      if(nn==0)
      {
        //рассчитывает падение давления вследствие скорости
        s_MVD[0].PressB= FctBern*s_MVD[0].FlowM*s_MVD[0].FlowM/s_MVD[0].Dens;

        //рассчитывает s_MVD[0].Compos и s_MVD[0].PressG
        f_get_pressDT(s_MVD[0].Dens,s_MVD[0].Temp);


//      f_prep_int_MassF();

//      f_prep_int_dens();

/*
          if(flag_rcv==0)
          {
            f_prep_int_v2();
            f_flow_chk(); // для MVD[2]

          }
          else
*/
          {
           f_prep_int_rcv();
           f_chk_stg();  // для MVD[0]
          }

        fl_rd_err=1;

        fl_MI=1;
        fl_VI=1;

      }
      else if(nn==1)
      {
        ftmp=s_MVD[0].Dens;
        if(ftmp < 450 ) ftmp=540.;
        s_MVD[1].VolTd=s_MVD[1].MassT*1000./ftmp;
      }
        if(s_MVD[nn].reg_err & 0x8000)
        {
          if( f_get_icp_error(&MVD[nn]) != 0 ) break;
//        f_icp_error(&MVD[nn],Drive_ERR | ( s_MVD[nn].reg_err & 0xffff) );
          f_icp_error(&MVD[nn],Drive_ERR);
        }
        else flag_mvd_fst[nn]=0;
        break;

      default:
           //      goto m_tout_err;
               goto m_crc_err;
      }
  }
 else
  switch(fn)
 {
   case MVD_RD_I: // чтение Int
     s_MVD[nn].i=(cb_COM[ii][4] & 0xff) | ( ((unsigned int)cb_COM[ii][3] << 8) &0xff00)  ;
     MVD_fn[nn]=0;
     break;

  case MVD_RD_F: // чтение Float

    if(cb_COM[ii][1] != 3)
    {
     goto m_crc_err;
    }
    if(cb_COM[ii][2] != 4)
    {
       goto m_crc_err;
    }
    s_MVD[nn].f = f_get_float( cb_COM[ii], 1);
    MVD_fn[nn]=0;
    break;

  case MVD_RD_L: // чтение Long
    if(cb_COM[ii][1] != 3)
    {
     goto m_crc_err;
    }
    if(cb_COM[ii][2] != 4)
    {
       goto m_crc_err;
    }
    s_MVD[nn].l =
          ( (unsigned long)(cb_COM[ii][6]) & 0x000000ff) |
          ( ((unsigned long)cb_COM[ii][5] << 8) &0xff00) |
          ( ((unsigned long)cb_COM[ii][4] << 16) &0xff0000)  |
          ( ((unsigned long)cb_COM[ii][3] << 24) &0xff000000);
    MVD_fn[nn]=0;
    break;
  case  MVD_RD_C: // чтение Coil

     if(cb_COM[ii][1] != 1) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;(i<im)&(i<n_coil_b) ;i++,i1++)
     {
       s_MVD[nn].c[i]=cb_COM[ii][i1]&0xff;
     }
     MVD_fn[nn]=0;
     break;

  case  MVD_RD_S: // чтение String

     if(cb_COM[ii][1] != 3) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;(i<im)&&(i< (n_char_b-1)) ;i++,i1++)
     {
      s_MVD[nn].a[i]=cb_COM[ii][i1];
     }
     s_MVD[nn].a[i]=0;
     MVD_fn[nn]=0;
     break;
  default:
    // ответ на команду записи
    if ((cb_COM[ii][1] == 6)  || (cb_COM[ii][1] == 16) ||(cb_COM[ii][1] == 5));
    else
    {
      goto m_crc_err;
    }
    MVD_fn[nn]=0;
    break;
 }

 m_end:
  MVD[nn].n_success++;
  MVD_inp_err[nn]=0;
  f_queue_free(ii,&MVD_Rqst[nn]);
  return;

m_crc_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_CRC_error++;
 goto m_err;

m_tout_err:
 MVD[nn].time_stamp_rcv=0;
 MVD[nn].n_timeout_error++;

m_err:
 MVD_inp_err[nn]++;

 if (fn>0)
  if(( fn & 0xf8) != MVD_RD_P)
 {
// printf("\r\n if(( fn & ~0x7) != MVD_RD_P)  %d , %d",( fn & ~0x7),MVD_RD_P);
     MVD_fn[nn]=fn;
 }
 if(MVD_inp_err[nn]>=MVD_max_inp_err)
 {
   MVD_inp_err[nn]=MVD_max_inp_err;
   f_icp_error(&MVD[nn],RD_ERR );
 }
 f_queue_free(ii,&MVD_Rqst[nn]);
}
/* ---------------------------------------- */
char *unit_lst[]={
// Volume flow codes I0042
  "l/sec",
  "l/hour",
// Temperature codes I0041
"C",
"F",
"R",
"K",
// Volume totalizer or volume inventory codes I 0046
  "l",
  "m3",
// Mass totalizer or mass inventory unit codes I 0045
  "kg",
// I039 Mass flow codes
  "kg/sec",
  "kg/min",
  "kg/hour",
  "kg/day",

// Density codes I0040
  "g/cm3",
  "kg/m3",

"Special",

};
/* ---------------------------------------- */



char *f_get_unit(int code)
{ // возвращает указатель на наименование единиц
int i;
  for(i=0;unit_codes[i]>0;i++)
  {
   if(unit_codes[i]== code) return unit_lst[i];
  }
  return NULL;
}

/* ---------------------------------------- */

int unit_codes[]={
// Volume flow codes I0042
  24,
  138,
//Temperature codes I0041
32,
33,
34,
35,
// Volume totalizer or volume inventory codes I 0046
  41,
  43,
// Mass totalizer or mass inventory unit codes I 0045
  61,
// I039 Mass flow codes
  73,
  74,
  75,
  76,

// Density codes I0040
  91,
  92,

253,
-1
};
/* ---------------------------------------- */


/* ---------------------------------------- */
int sw_mvd_1=0;
long int tm_mvd;
long int tm_mvd_p;
int mode_mvd=0;
int ii_MVD=0;

void f_MVD_1()
{
// отображает параметры MVD
  if((MVD_fn[ii_MVD] != 0) && (MVD_fn[ii_MVD] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
        ff_serv=NULL;
        printf("\n\r  ! Answer timeout happend");
        f_prompt();
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_1)
  {
  case 0:
   MVD_fn[ii_MVD]=MVD_RD_L;
   s_MVD[ii_MVD].r_addr=127;
   sw_mvd_1=1;
   break;

  case 1:
  if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r Serial number %ld",s_MVD[ii_MVD].l);

   MVD_fn[ii_MVD]=MVD_RD_S;
   s_MVD[ii_MVD].r_addr=425;
   s_MVD[ii_MVD].n=8;
   sw_mvd_1++;
   break;

  case 2:
  if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r Sensor description: %s",s_MVD[ii_MVD].a);
   MVD_fn[ii_MVD]=MVD_RD_S;
   s_MVD[ii_MVD].n=8;
   s_MVD[ii_MVD].r_addr=96;
   sw_mvd_1++;
   break;

  case 3:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Tramsmitter description: %s",s_MVD[ii_MVD].a);
   MVD_fn[ii_MVD]=MVD_RD_S;
   s_MVD[ii_MVD].r_addr=104;
   s_MVD[ii_MVD].n=16;
   sw_mvd_1++;
   break;

  case 4:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Message: %s",s_MVD[ii_MVD].a);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=16;
   sw_mvd_1++;
   break;

  case 5:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Transmitter software revision : %d",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_S;
   s_MVD[ii_MVD].r_addr=72;
   s_MVD[ii_MVD].n=8;
   sw_mvd_1++;
   break;

  case 6:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Flow calibration: %s",s_MVD[ii_MVD].a);
   MVD_fn[ii_MVD]=MVD_RD_S;
   s_MVD[ii_MVD].r_addr=80;
   s_MVD[ii_MVD].n=7;
   sw_mvd_1++;
   break;

  case 7:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Temp.calibration: %s",s_MVD[ii_MVD].a);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=155;
   sw_mvd_1++;
   break;

  case 8:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r D1 F155: %.3f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=157;
   sw_mvd_1++;
   break;

  case 9:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r D2 F157: %.3f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=159;
   sw_mvd_1++;
   break;

  case 10:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r K1 F159: %.3f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=161;
   sw_mvd_1++;
   break;

  case 11:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r K2 F161: %.3f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=279;
   sw_mvd_1++;
   break;

  case 12:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Mass flow meter factor    F279: %.6f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=281;
   sw_mvd_1++;
   break;

  case 13:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Volume flow meter factor  F281: %.6f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=283;
   sw_mvd_1++;
   break;

  case 14:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Density flow meter factor F283: %.6f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=195;
   sw_mvd_1++;
   break;

  case 15:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Cutoff for mass flow   F195: %.6f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=197;
   sw_mvd_1++;
   break;

  case 16:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Cutoff for volume flow F197: %.6f",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=149;
   sw_mvd_1++;
   break;

  case 17:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Cutoff for density     F149: %.6f",s_MVD[ii_MVD].f);
   ff_serv=NULL;
   f_prompt();
   break;
  }

}
/* ---------------------------------------- */
int sw_MMI_cur=0; // начальная строка на дисплее MMI
int sw_MMI_lim=7;
int sw_mvd_m1=0;
/* ---------------------------------------- */
/* ---------------------------------------- */
int u_cod;
float HTemp,HDens,HCompos;
void f_MVD_2()
{
 float ftmp;
char *unit;
// отображает данные MVD
  if((MVD_fn[ii_MVD] != 0) && (MVD_fn[ii_MVD] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
        ff_serv=NULL;
        printf("\n\r  ! Answer timeout happend");
        f_prompt();
    }
    return;
  }
  tm_mvd=TimeStamp;
  ftmp=BIG_P;
  switch(sw_mvd_1)
  {
  case 0:
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=39; // I039 Mass flow codes
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1=1;
   break;

  case 1:
   u_cod=s_MVD[ii_MVD].i;
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=247;
   sw_mvd_1++;
   break;

  case 2:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Mass flow %f %s",s_MVD[ii_MVD].f,unit);
  }

   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=45; // Mass totalizer or mass inventory unit codes I 0045
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 3:
   u_cod=s_MVD[ii_MVD].i;
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=259;
   sw_mvd_1++;
   break;

  case 4:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Mass total: %f %s",s_MVD[ii_MVD].f,unit);
  }
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=263;
   sw_mvd_1++;
   break;

  case 5:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Mass inventory : %f %s",s_MVD[ii_MVD].f,unit);
  }
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr= 42 ; // Volume flow codes I0042
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 6:
   u_cod=s_MVD[ii_MVD].i;

   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=253;
   sw_mvd_1++;
   break;

  case 7:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Volume flow: %f %s",s_MVD[ii_MVD].f,unit);
  }
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr= 46 ; // Volume totalizer or volume inventory codes I 0046
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 8:
   u_cod=s_MVD[ii_MVD].i;
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=261;
   sw_mvd_1++;
   break;

  case 9:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Volume total : %f %s",s_MVD[ii_MVD].f,unit);
  }
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=265;
   sw_mvd_1++;
   break;

  case 10:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
     printf("\n\r Volume inventory: %f %s",s_MVD[ii_MVD].f,unit);
  }
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr= 40 ; // Density codes I0040
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 11:
   u_cod=s_MVD[ii_MVD].i;

   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=249;
   sw_mvd_1++;
   break;

  case 12:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
   {
     printf("\n\r Density: %f %s",s_MVD[ii_MVD].f,unit);
//   HDens=s_MVD[ii_MVD].f*K_unit;
     HDens=s_MVD[ii_MVD].f;
   }
  }
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr= 41 ; // Temperature codes I0041
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 13:
   u_cod=s_MVD[ii_MVD].i;
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=251;
   sw_mvd_1++;
   break;

  case 14:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
   {
     printf("\n\r Process temperature %f %s",s_MVD[ii_MVD].f,unit);
     HTemp=s_MVD[ii_MVD].f;
    if((HDens>0)&&(HTemp>-300))
    {
     HCompos=f_get_composition(HDens,HTemp);
     if(HCompos>1.)
      printf("\r\n !СУГ легче жидкого пропана");
     else if(HCompos<0.)
      printf("\r\n !СУГ тяжелее жидкого бутана");
     else
      {
       ftmp=(1.- HCompos)*100.;
       printf("\r\n СУГ: пропан %8.2f%c, бутан %8.2f%c",(HCompos*100),'%',ftmp,'%');
      }
    }
   }
  }

   sw_mvd_1+=2;
/*
   goto m16;
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr= 44 ; // Pressure codes I0044
   s_MVD[ii_MVD].i=-1;
   sw_mvd_1++;
   break;

  case 15:
   u_cod=s_MVD[ii_MVD].i;
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=257;
   sw_mvd_1++;
   break;

  case 16:
  if((MVD_fn[ii_MVD] != F_FAULT)&& (u_cod>0))
  {
    unit=f_get_unit(u_cod);
   if(unit != NULL)
   {
     printf("\n\r Pressure : ");
     if(s_MVD[ii_MVD].f == ftmp)
      printf(" ! bad process variable");
     else printf(" %f %s",s_MVD[ii_MVD].f,unit);
   }
  }

m16:
*/
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=383;
   sw_mvd_1++;
   break;

  case 17:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Board temperature: %.3f C",s_MVD[ii_MVD].f);
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=385;
   sw_mvd_1++;
   break;

  case 18:
   if(MVD_fn[ii_MVD] != F_FAULT)
     printf("\n\r Supply voltage: %.3f V",s_MVD[ii_MVD].f);
   ff_serv=NULL;
   f_prompt();
   break;
  }

}
/* ---------------------------------------- */
void f_MVD_3()
{
int i;
long int ltmp,i1;
// отображает ошибки MVD
  if((MVD_fn[ii_MVD] != 0) && (MVD_fn[ii_MVD] != F_FAULT))
  {
    if( f_timer(tm_mvd,f_MVD_tim ) )
    {
        ff_serv=NULL;
        printf("\n\r  ! Answer timeout happend");
        f_prompt();
    }
    return;
  }
  tm_mvd=TimeStamp;
  switch(sw_mvd_1)
  {
  case 100:
   MVD_fn[ii_MVD]=MVD_RD_C;
   s_MVD[ii_MVD].r_addr=21;
   s_MVD[ii_MVD].n=16;
   sw_mvd_1=1;
   break;

  case 101:
  if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r Coils 21 ... 34: %02X%02X",s_MVD[ii_MVD].c[1]&0xff,s_MVD[ii_MVD].c[ii_MVD]&0xff);

   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=1;
   sw_mvd_1++;
   break;

  case 2:
  if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 001: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=125;
   sw_mvd_1++;
   break;

  case 3:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 125: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=126;
   sw_mvd_1++;
   break;

  case 4:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 126: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=400;
   sw_mvd_1++;
   break;

  case 5:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 400: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=419;
   sw_mvd_1++;
   break;

  case 6:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 419: %04X",s_MVD[ii_MVD].i);
    if(s_MVD[ii_MVD].i & 0x8000)
     printf("\n\r !!! High severity alarm(s) active");
    else
     printf("\n\r  No high severity alarm active");
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=420;
   sw_mvd_1++;
   break;

  case 7:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 420: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=421;
   sw_mvd_1++;
   break;

  case 8:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 421: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=422;
   sw_mvd_1++;
   break;

  case 9:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 422: %04X",s_MVD[ii_MVD].i);
   MVD_fn[ii_MVD]=MVD_RD_I;
   s_MVD[ii_MVD].r_addr=423;
   sw_mvd_1++;
   break;

  case 10:
   if(MVD_fn[ii_MVD] != F_FAULT)
    printf("\n\r INT REG 423: %04X",s_MVD[ii_MVD].i);

  case 0:
   MVD_fn[ii_MVD]=MVD_RD_F;
   s_MVD[ii_MVD].r_addr=245;
   sw_mvd_1++;
   break;

  case 1:
   if(MVD_fn[ii_MVD] != F_FAULT)
   {
     ltmp=(long int)s_MVD[ii_MVD].f &0xffffff;
     printf("\n\r Float REG 245: %.0f (%06lX)",s_MVD[ii_MVD].f,ltmp);
  /*
     if(ltmp)
     {
       printf("\n\r Error(s) occured:");
       for(i=0,i1=1;i<24;i++,i1=i1<<1)
       {
         if(ltmp & i1) printf("\n\r!%s",err_F425[i]);
       }
     }
     else printf("  No errors");
   */
   }
   ff_serv=NULL;
   f_prompt();
   break;
  }

}


float CL_val[3]={0.5,0.1,0};
float CL_valR[3]={0.5,0.1,0};


int num_out1=1,num_out2=2;
int num_out3=3,num_out4=4;
int num_out5=5,num_out6=6;
int num_out7=7,num_out8=8;

int num_in1=1,num_in2=2;
int num_in3=3,num_in4=4;

// 25-30 л/мин = 500 мл/сек
//     5 л/мин =  83 мл/сек

int t_ctrl=0;   // 1 - изменять cutoff

int fl_take_temp=0;
void  f_ctrl_v1()
{ // непосредственное  управление клапанами
float ftmp;
int itmp;

  itmp=0;
  ftmp=  vol_f-s_MVD[0].VolT;

 if(fl_GO == 1)
 {
   if( ftmp > CL_val[0]) itmp |= OUT1;
   if( ftmp > CL_val[1]) itmp |= OUT2;
   if(itmp == 0) fl_GO=0;
 }

 i7060_out[0]=itmp;
}
/* ---------------------------------------- */
float vol2=0,k_vol=1.;
long int tt_vol1=0;
long int tt_vol2=0;
long int tim_MVD_delay=35;  // ms , время задержки чтения MVD
void  f_prep_int_v2()
{ // подготовка параметров интерполяции volume total
  // индикация и отпуск по объему
float ftmp;
int itmp;
long int ltmp;
  ftmp=s_MVD[0].VolT;
//summ_v=ftmp*cost_v;
  ltmp=tim_snd_MVD-tt_vol1;
 if(ltmp>0)
 {
  k_vol=(ftmp-vol2)/(float)ltmp;
  vol2=ftmp;
#if( Test == 0)
  tt_vol2=tim_snd_MVD+tim_MVD_delay;
#else
  tt_vol2=tim_snd_MVD;
#endif
 }
 tt_vol1= tim_snd_MVD;

}
/* ---------------------------------------- */
void  f_prep_int_MassF()
{ // подготовка параметров интерполяции Mass
  // индикация массы, отпуск по массе
float ftmp;
int itmp;
unsigned long int ltmp;
 ftmp=s_MVD[0].MassT;

// summ_v=s_MVD[0].MassT*cost_v;

 ltmp=tim_snd_MVD-tt_Mas1;
 if(ltmp>0)
 {
  k_vol=(ftmp-Mas2)/(float)ltmp; // kg/ms
  Mas2=ftmp;
  vol2=ftmp;
  tt_vol2=tim_snd_MVD+tim_MVD_delay;
  tt_Mas1= tim_snd_MVD;
 }
}
/* ---------------------------------------- */

float Mas2r=0,k_Masr=1.;
long int tt_Mas1r=0;
long int tt_Mas2r=0;

float vol2r=0,k_volr=1.;
long int tt_vol1r=0;
long int tt_vol2r=0;

void f_prep_int_rcv()
{ // подготовка параметров интерполяции для приема
  // используются показания двух расходомеров
float ftmp;
int itmp;
unsigned long int ltmp;

 if(flag_rcv != 0)
   ftmp=s_MVD[0].MassT + s_MVD[1].MassT;
 else
   ftmp= -(s_MVD[0].MassT + s_MVD[1].MassT);

// summ_v=ftmp*cost_v;

 ltmp=tim_snd_MVD-tt_Mas1r;
 if(ltmp>0)
 {
  k_volr=(ftmp-Mas2r)/(float)ltmp;
  Mas2r=ftmp;
  vol2r=ftmp;
  tt_vol2r=tim_snd_MVD+tim_MVD_delay;
  tt_Mas1r= tim_snd_MVD;
 }
 else
 {
  Mas2r=ftmp;
  vol2r=ftmp;

  tt_vol2r=tim_snd_MVD+tim_MVD_delay;
  tt_Mas1r= tim_snd_MVD;
 }
}
/* ---------------------------------------- */
float  f_int_v2r()
{ // экстраполяция volume total во времени
  return (vol2r+k_volr*(TimeStamp-tt_vol2r));
}
/* ---------------------------------------- */

/* ---------------------------------------- */
float  f_int_v2()
{ // экстраполяция volume total во времени
 long int ltmp;
 ltmp=TimeStamp-tt_vol2;

 if((ltmp>0) && (ltmp < 1000000))
   return (vol2+k_vol*((float)ltmp));
 else
   return vol2;
}
/* ---------------------------------------- */
float VolT_int=0;
float summ_v_int=0;

float VolT_id=0;
float summ_v_id=0;


float CL_T0=100 ; // ms, время срабатывания кл.0
float CL_T1=100 ; // ms, время срабатывания кл.1
float CL_T2=150 ; // ms, время срабатывания кл.2
float CL_T3=250 ; // ms, до конца отпуска/приема,
                  // момент отключения второстепенного опроса

long int CL_T4=350 ; // ms, максимальная длительность запрета второстепенного опроса


/* ---------------------------------------- */
long int tim_snd_MVDT=0;
float MVDT1=0;
float k_Test=0.0001;

#if(SIM0 != 0)

float Sim_MassT[3] =  {0.1,0.2,0.3};
float Sim_Dens[3]  =  {542.1,15.6,855};
float Sim_Temp[3]  =  {11.1,22.2,33.3};
float Sim_MassI[3] =  {11111,222,33333};
float Sim_VolI[3]  =  {22222,444,66666};
float Sim_FlowM[3] =  {2000,70,2.3};
float Sim_VolT[3]  =  {0.2,0.4,0.6};
int   Sim_Reg_err[3]= {0,0,0};

#endif
int ii_mbn=0;
void f_sim_MVD( int nn)
{
ii_mbn=nn;
#if(SIM0 != 0)
float ftmp;

 if( f_timer(MVD[nn].time_stamp_pool,MVD[nn].pool_time ) )
 {
        s_MVD[nn].f=0;
        MVD[nn].time_stamp_pool=TimeStamp;

        tim_snd_MVD=TimeStamp;

        s_MVD[nn].MassT  = Sim_MassT[nn]  ;
        s_MVD[nn].Dens   = Sim_Dens[nn]   ;
        s_MVD[nn].Temp   = Sim_Temp[nn]   ;
        s_MVD[nn].MassI  = Sim_MassI[nn]  ;
        s_MVD[nn].VolI   = Sim_VolI[nn]   ;
        s_MVD[nn].FlowM  = Sim_FlowM[nn]  ;
        s_MVD[nn].VolT   = Sim_VolT[nn]   ;
        s_MVD[nn].reg_err= Sim_Reg_err[nn];

       if(s_MVD[nn].Dens <= 0.001) s_MVD[nn].Dens=0.001;
       if(s_MVD[nn].Dens > 0.00000002) s_MVD[nn].FlowV=s_MVD[nn].FlowM * 1000. /s_MVD[nn].Dens;

       if(fl_GO_rcv)
       {
        ftmp=Sim_FlowM[nn]/3600.;
        Sim_MassT[nn]+=ftmp;
        Sim_MassI[nn]+=ftmp;

        ftmp=s_MVD[nn].FlowV/3600.;
        Sim_VolT[nn] += ftmp;
        Sim_VolI[nn] += ftmp;
       }


      if(nn==0)
      {

        //рассчитывает падение давления вследствие скорости
        s_MVD[0].PressB= FctBern*s_MVD[0].FlowM*s_MVD[0].FlowM/s_MVD[0].Dens;

        //рассчитывает s_MVD[0].Compos и s_MVD[0].PressG
        f_get_pressDT(s_MVD[0].Dens,s_MVD[0].Temp);


//      f_prep_int_MassF();

//      f_prep_int_dens();

        f_prep_int_rcv();
        f_chk_stg();  // для MVD[0]

        fl_rd_err=1;

        fl_MI=1;
        fl_VI=1;

      }
      else if(nn==1)
      {
        ftmp=s_MVD[0].Dens;
        if(ftmp < 450 ) ftmp=540.;
        s_MVD[1].VolTd=s_MVD[1].MassT*1000./ftmp;
      }

        MVD_Rqst[nn].status = Req_OK;
        MVD[nn].n_transaction++;
        MVD_fn[nn]=0;

        fl_rd_err=1;

        if(s_MVD[nn].reg_err & 0x8000)
        {
          if( f_get_icp_error(&MVD[nn]) != 0 ) return;
//        f_icp_error(&MVD[nn],Drive_ERR | ( s_MVD[nn].reg_err & 0xffff) );
          f_icp_error(&MVD[nn],Drive_ERR);
        }
        else flag_mvd_fst[nn]=0;

 }
#endif
}
/* ---------------------------------------- */
//-------------------------------
int f_reset_zer_MVD(int ii)
{ // обнуление MVD (усреднение)
// Return 1  - OK, 0 - error
/*
   if(MVD_fn[0] != 0) return 0;
   MVD_fn[0]=MVD_WR_C;
   s_MVD[0].r_addr=5; // Start/stop zero
   s_MVD[0].i=1;
   return 1;
*/
 MVD_Rqst_T[ii].answ_com=f_MVD_rd_t;
 MVD_Rqst_T[ii].answ_flt=f_MVD_rd_t;
 return  f_MVD_WR(ii,(int)MVD_WR_C,(int) 5,(int)1,(long int) 0,(float)0);
}
//-------------------------------
int io_1=0;
unsigned long int TimeOut3=0;
//unsigned int Out_en=0xffff;
int flag_O0=0;
int flag_O1=0;
int flag_O3=0;
int flag_pool=1;
int flag_fill_ok=0;
int flag_gas=0;
float vol_mom=0,vol_mom0=0,flow_mom=0;

void  f_ctrl_v2()
{ // управление клапанами по экстраполированному значению
float ftmp;
int itmp,itmp1;
unsigned long int ltmp;

if(flag_v2)
{

 itmp = f_ctrl_rcv();

 OUT_VAR &= ~(  OUT1 | OUT2 | OUT3 | OUT4);

 if(Flag_check == 0)
   OUT_VAR |= (itmp & Out_en & Out_en_r);

}

 i7060_out[0] = OUT_VAR & 0xff;

 if(flag_prn)
 {
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }
        if(Flag_check==0)
        {
          f_7060(0);
          ServiceCOM(I7060[0].port);
        }
 return;
}
/* ---------------------------------------- */
float Den2=0,k_Den=1.;
long int tt_Dens1=0;
long int tt_Dens2=0;
void  f_prep_int_dens()
{ // подготовка параметров интерполяции density
float ftmp;
int itmp;
unsigned long int ltmp;
 ftmp=s_MVD[0].Dens;
 ltmp=tim_snd_MVD-tt_Dens1;
 if(ltmp>0)
 {
  k_Den=(ftmp-Den2)*1000./(float)ltmp;
  Den2=ftmp;
  tt_Dens2=tim_snd_MVD+tim_MVD_delay;
  tt_Dens1= tim_snd_MVD;
 }
}
/* ---------------------------------------- */
void  f_prep_int_Mass()
{ // подготовка параметров интерполяции Mass
  // индикация объема, объем вычисляется через отпущенную
  //  массу и плотность
float ftmp;
int itmp;
unsigned long int ltmp;
 ftmp=s_MVD[0].MassT;

 s_MVD[0].VolTd=ftmp*1000./Dens0;
// summ_v=s_MVD[0].VolTd*cost_v;

 ltmp=tim_snd_MVD-tt_Mas1;
 if(ltmp>0)
 {
  k_vol=((ftmp-Mas2)*1000.)/((float)ltmp * Dens0);
  Mas2=ftmp;
  vol2=(ftmp*1000.)/Dens0;
  tt_vol2=tim_snd_MVD+tim_MVD_delay;
  tt_Mas1= tim_snd_MVD;
 }
}
/* ---------------------------------------- */

/* ---------------------------------------- */
long int time_beg_fill=0;
int i_dens=0xffff;
long int time_chg_den=0,tim_dens=0;
long int tim_dens0=0,tim_dens2=0;
long int time_chg_den0;
long int time_chg_den2;

//long int TimDensOff   =800; // мс,минимальное время нахождения клапана в выкл.состоянии
//long int TimDensOn    =700; // мс,минимальное время нахождения клапана во вкл.состоянии
//long int TimDensWt0   =300; // мс,время между выключениями двух клапанов
//long int TimDensWt1   =300; // мс,время между включениями двух клапанов


//long int cl0_delay_off=2000;
long int cl1_delayR_off=1000;
long int cl2_delayR_off=500;
long int Out3_delayR_off=2000;

// kg/m3/s, скорость изменения плотности

float    k_Den0_Off   = 2.000;
float    k_Den0_On    = 0.5;

float    k_Den_Off    = 10.0;
float    k_Den_On     = 3.00;

int TimeBegFlch=15;

int   ModeReduce   = ReducePress;
float PressLvl_on0 =0.11; // МПа
float PressLvl_off0=0.05; // МПа
// WWWWWW
float PressLvl_on1 =12;  // мм  R_MVD


float PressLvl_off1=0.5; // кг/см2

float PressLvl_on2 =0.5; // кг/см2
float PressLvl_off2=0.0; // кг/см2

//---------------------
//---------------------
void f_prep_bern()
{
 if(R_MVD>=0)
   FctBern=ConstBern/(R_MVD*R_MVD*R_MVD*R_MVD);
 else
   FctBern=0;
}
//---------------------
/* ---------------------------------------- */
/* ---------------------------------------- */
int  fl_VI=0, fl_MI=0;
long int t_mvd_cor=300;
int flag_nal=0;
int cl_MVD_sw=0;
long int t_prep_MVD=0;
/* ---------------------------------------- */
long int t_MVD_flg;
void f_MVD_cor_rcv()
{
  // запускается после окончания отпуска
  // через время t_mvd_cor мс состояние процесса записывается в журнал
int i;
long int ltmp,i1;
float ftmp,ftmp1,ftmp2;

  if( f_timer(tm_mvd_p,t_mvd_cor-1000 )==0 )
  {
   fl_VI=0;
   fl_MI=0;
   cl_MVD_sw=0;
   t_prep_MVD=TimeStamp;
   return;
  }


//  if(t_ctrl==0) goto m00;
  if(cl_MVD_sw == 10) goto m00;

//  if((MVD_fn[0] != 0) && (MVD_fn[0] != F_FAULT))
  if(MVD_fn[0] != 0)
  {
    if((MVD[0].status==0 ) || ( (ErrMVD1 != 0) && (Flag_check != 0) ) ) ;
    else
      {
      if( f_timer(t_prep_MVD,(long int)2000L ) == 0 ) return;
      f_icp_errS(No_F_dat_err);
      return;
      }
  }
//  if((MVD_fn[1] != 0) && (MVD_fn[1] != F_FAULT))
  if(MVD_fn[1] != 0)
  {
    if((MVD[1].status==0 ) || ( (ErrMVD2 != 0) && (Flag_check != 0) ) ) ;
    else
    {
      if( f_timer(t_prep_MVD,(long int)2000L ) == 0 ) return;
      f_icp_errS(No_F_dat_err);
      return;
    }
  }
  switch (cl_MVD_sw)
   {
       // Расходомер 1
       // Останов счета
    case 0:  // Stop totalizers


   ltmp=TimeStamp+5000;
   MVD[0].time_stamp_pool=ltmp;
   MVD[1].time_stamp_pool=ltmp;


            MVD_fn[0]=MVD_WR_C;
            s_MVD[0].r_addr=2; // Stop totalizers
            s_MVD[0].i=0;
            cl_MVD_sw=1;
            t_prep_MVD=TimeStamp;
            return;
    case 1:
       // Расходомер 1
       // установка значения среза массового расхода для режима ожидания
        MVD_fn[0]=MVD_WR_F;
        s_MVD[0].r_addr=195; // Cutoff for mass flow
        s_MVD[0].f=cutoff_off_M;
        cl_MVD_sw=2;
        t_prep_MVD=TimeStamp;
//        printf("\n\r0");
        return;

    case 2:
       // Расходомер 1
       // установка значения среза объемного расхода для режима ожидания
        MVD_fn[0]=MVD_WR_F;
        s_MVD[0].r_addr=197; // Cutoff for volume flow
        s_MVD[0].f=cutoff_off_V;
        t_prep_MVD=TimeStamp;
//        printf("\n\r1");
        cl_MVD_sw=50;
        return;

    case 50:
       // Расходомер 2
       // установка значения среза массового расхода для режима ожидания
        MVD_fn[1]=MVD_WR_F;
        s_MVD[1].r_addr=195; // Cutoff for mass flow
        s_MVD[1].f=cutoff_off_M;
        cl_MVD_sw=51;
        t_prep_MVD=TimeStamp;
//        printf("\n\r0");
        return;

    case 51:
       // Расходомер 2
       // установка значения среза объемного расхода для режима ожидания
        MVD_fn[1]=MVD_WR_F;
        s_MVD[1].r_addr=197; // Cutoff for volume flow
        s_MVD[1].f=cutoff_off_V;
        t_prep_MVD=TimeStamp;
//        printf("\n\r1");
        cl_MVD_sw=22;
        return;

    case 22:
//        printf("\n\r2");
        t_MVD_flg=TimeStamp;
        cl_MVD_sw=3;
        fl_VI=0;
        fl_MI=0;
        return;
    case 3:
       if( f_timer(t_MVD_flg,t_mvd_cor )==0 )
       {
        fl_VI=0;
        fl_MI=0;
        return;
       }

       if((fl_VI==0) || (fl_MI==0))
       {
       }
       else
       {
         cl_MVD_sw=6;
       }
       return;

    case 6:
        cl_MVD_sw=10;

   MVD[0].time_stamp_pool=TimeStamp;
   MVD[1].time_stamp_pool=TimeStamp+250;

        return;
    default:
        return;
   }

m00:
  if((fl_VI==0) || (fl_MI==0))
  {

    if((MVD[0].status==0 ) || ( (ErrMVD1 != 0) && (Flag_check != 0) ) )  goto m1;
    if( f_timer(tm_mvd_p,t_mvd_cor*2)==0 )
       return;
    else
     {
       f_icp_errS(No_F_dat_err);
       goto m1;
     }
  }
m1:

 Temperature=s_MVD[0].Temp;
 Density=s_MVD[0].Dens;

  if(flag_fill_ok)
  {
       f_wr_evt(evt_end_f+flag_rcv);
  }
  else
  {
     if(flag_flch)
      {
        f_wr_evt(evt_overfl+flag_rcv);
      }
     else if(flagS_ES)
        f_wr_evt(evt_ES_off+flag_rcv);
     else if(flagS_UZA)
      {
        switch(flagE_UZA)
        {
         case UZA_E:
           f_wr_evt(evt_UZA_off+flag_rcv);
           break;
         default:
           f_wr_evt(evt_UZA_off+flag_rcv);
           break;
        }
      }
     else if(flagS_DLT)
        f_wr_evt(evt_DLT_off+flag_rcv);
     else if(FL_err)
        f_wr_evt(evt_err_f+flag_rcv);
     else
        f_wr_evt(evt_est_f+flag_rcv);
  }

     ff_serv_N=NULL;

     offs_cor=(vol2r-dose_A);

// корректирует параметры наполнения
     if(fct_offs_r==0)
     {
m_end:
          return;
     }
    if(flag_fill_ok != 1) goto m_end;
   if(flag_rcv != 0)
   {
       CL_valR[1] += fct_offs_r * offs_cor;
       if(CL_valR[1] < 0)  CL_valR[1]=0;
       if(CL_valR[1] > Max_CL_V)  CL_valR[1]=Max_CL_V;

   }
   else
   {
       CL_val[1] += fct_offs * offs_cor;
       if(CL_val[1] < 0)  CL_val[1]=0;
       if(CL_val[1] > Max_CL_V)  CL_val[1]=Max_CL_V;


   }

    f_wr_cor();
}
/* ---------------------------------------- */
int igun_1=0;
int mski_inp1=0;
int mski_inp2=0;
int mski_inp3=0;
int mski_inp4=0;

int flag_fst_gun=1;
//#define TimeGunInit 2000
//-----------------------------------

float  fl_chp[max_fl_ch];
int last_flch=0;

int flag_flch=0;
int flag_gun=0;
int time_flch=20;
long int beg_flch=0;
float val_flch=0.0; // предельное  значение потока для останова
float val_flch2=0.05; // предельное  значение потока для останова
float val0_flch=0.195; // значение для начала контроля потока
/* ==============
void  f_flow_chk()
{
// контролирует прохождение жидкости при наливе
 int itmp;
 float ftmp;
 float val_cur;

  val_cur=s_MVD[0].MassT;
  if(fl_GO)
  {
   last_flch=(last_flch+1) & max_fl_ch_m1;
   fl_chp[last_flch]=val_cur;

     itmp=(last_flch-time_flch) & max_fl_ch_m1;
     ftmp=val_cur-fl_chp[itmp];
     if(ftmp < 0) ftmp=-ftmp;

     if((OUT1|CLP0 ) & OUT_VAR)
     {
       if(ftmp<val_flch)
       { // за time_flch тиков прошло < val_flch литров
m1:
         stage_max=BegStage;
         time_antd=TimeStamp;
         time_prb_plus=TimeStamp;
       }
     }
     else    // только меньший клапан включен
       if(ftmp<val_flch2)
       { // за time_flch тиков прошло < val_flch литров
         goto m1;
       }
  }
  return;
}
void  f_flow_chk()
{
// контролирует прохождение жидкости при наливе
 int itmp;
 float ftmp;
 float val_cur;

  val_cur=s_MVD[0].MassT;

  if(flag_rcv==0)
   // отпуск
    if(fl_GO)
    {

     last_flch=(last_flch+1) & max_fl_ch_m1;
     fl_chp[last_flch]=val_cur;
     if(beg_flch < (time_flch+TimeBegFlch))
     {  // начало налива, не проверять первые time_flch тиков

       beg_flch++;
       if(val_cur>val0_flch)
       {
         beg_flch=time_flch+TimeBegFlch;
       }
     }
     else
     {
       itmp=(last_flch-time_flch) & max_fl_ch_m1;
       ftmp=val_cur-fl_chp[itmp];

       if(ftmp<val_flch)
       { // за time_flch тиков прошло < val_flch литров
         flag_flch=1;
         f_stop_cnt(); // останов отпуска по переполнению бака
       }
     }

    }
  return;
}
========= */
//-----------------------------------
