int EchoComN=0;
union {unsigned long int l;
unsigned int i[2];
} ul;
unsigned long int *Flash_ptr;
unsigned int seg=0xc000,offset=0;
int AddrHost=0;
int ComPortHost=4;

int ComPortEcho=1;
int CRC_flag_Echo=1;
int nn_mvd=0;

int flag_echo_host=1;
int flag_Deb=0;
int flag_host_send=0; //1 - у Host есть что послать Slave
int msk_int[]={0,1,2,4,8,0x10,0x20,0x40,0x80,0x100,0x200,
0x400,0x800,0x1000,0x2000,0x4000,0x8000};

float cost_v=1000;       // Unit price
float amount_f=0;        // Amount

float volume_f=0;        // Volume execute
float vol_f=0;           // Volume execute

float summ_v=1000;       // Amount Current value

char *list_pt[]={
"pressure",
"temperature ",
};

// unsigned long int adr_strt= 0xfffff0L;

unsigned long int adr_strt= 0xffff0L; //-- WORK
//---------------------------------
struct s_icp_dev Host=
{
// device 1
0,                // status
1,                // port
0,                // addr
"Host",           // name[8]
06,               // baudrate_cod
0x00,             // type
0x00,             // format
0x00,             // channels
"V1.1",           // firmware
0,                // protocol
1,                // CRC_flag
150,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&Host_Rqst        // *request
};
//--------------------------------
//---------------------------------
struct COM_rqst Host_Rqst={
0,                     //  состояние запроса
ffgets_com_ICP,        //  gets_com
f_send_to_Host,        //  answ_com
f_empty_ans_echo,      //  answ_flt
"Host",                //  name
0,                     //  n_dev
&Host,                 //  *ICP_dd
0,                     //  текущая функция
ToutAnsHost,           //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
""                     //  com[]
};
/*----------------------------*/
struct COM_rqst Host_Rqst_rtu={
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_send_to_Host_rtu,    //  answ_com
f_send_to_Host_rtu,    //  answ_flt
"Host",                //  name
0,                     //  n_dev
&Host,                 //  *ICP_dd
0,                     //  текущая функция
ToutAnsHost_rtu,       //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
""                     //  com[]
};
/*----------------------------*/
struct COM_rqst Host_Rqst_sk={
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_send_to_Host_sk,    //  answ_com
f_send_to_Host_sk,    //  answ_flt
"Host",                //  name
0,                     //  n_dev
&Host,                 //  *ICP_dd
0,                     //  текущая функция
ToutAnsHost_rtu,       //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
""                     //  com[]
};
/*----------------------------*/
#define max_wd 2
//---------------
struct s_icp_dev WDOG[max_wd]=
{
// device 1
0,                // status
1,                // port
0,                // addr
"WDOG/1",         // name[8]
06,               // baudrate_cod
00,               // type
0,                // format
0,                // channels
"V1.1",           // firmware
0,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&WDOG_Rqst[0],   // *request
//--------------------------------
// device 2
//--------------------------------
0,                // status
2,                // port
0,                // addr
"WDOG/2",         // name[8]
06,               // baudrate_cod
00,              // type
00,             // format
0x0,             // channels
"V1.1",           // firmware
0,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&WDOG_Rqst[1],   // *request
};
/*----------------------------*/
/*----------------------------*/
struct COM_rqst WDOG_Rqst[max_wd]={
//---------------------------------------
0,                     //  состояние запроса
ffgets_no_com_ICP,     //  gets_com
f_WD_end,              //  answ_com
f_WD_end,              //  answ_flt
"WDOG/1",              //  name
0,                     //  n_dev
&WDOG[0],              //  *ICP_dd
0,                     //  текущая функция
2,                     //  timeout
0,                     //  time_stamp
6,                     //  com_lgth
1,                     //  CRC_flag
"~**D2\r",             //  com[]
//-------------------------------------
//---------------------------------------
0,                     //  состояние запроса
ffgets_no_com_ICP,     //  gets_com
f_WD_end,              //  answ_com
f_WD_end,              //  answ_flt
"WDOG/2",              //  name
1,                     //  n_dev
&WDOG[1],              //  *ICP_dd
0,                     //  текущая функция
2,                     //  timeout
0,                     //  time_stamp
6,                     //  com_lgth
1,                     //  CRC_flag
"~**D2\r"              //  com[]
//-------------------------------------
};
/*----------------------------*/
void f_WDOG(int ii)
{
  //  ii - номер устройства
  //  Функция передает команду HOST OK ( '~**') .
  //  Период посылки WDOG[ii].pool_time мс.
  //  После передачи ожидается опорожнение буфера и задержка
  //  WDOG_Rqst[ii].timeout мс

int i,fn,sw;
char buf_tmp[20];

//  if(WDOG[ii].status == 0) return;

  if(( WDOG_Rqst[ii].status == Req_OK)||( WDOG_Rqst[ii].status == Req_Flt))
  {
   if( f_timer( WDOG[ii].time_stamp_pool, WDOG[ii].pool_time ))
    {
m1:
     strcpy(buf_tmp,"~**");
     if(f_prepare7000(buf_tmp, WDOG[ii].CRC_flag)) return;
     strcpy( WDOG_Rqst[ii].Cmd,buf_tmp);
     WDOG_Rqst[ii].cmd_lgth=strlen(buf_tmp);
     WDOG_Rqst[ii].time_stamp=TimeStamp;
     WDOG[ii].time_stamp_pool=TimeStamp;
     WDOG[ii].n_transaction++;
     f_queue_put( WDOG[ii].port, &WDOG_Rqst[ii]) ;
    }
  }
  else
   if( f_timer( WDOG[ii].time_stamp_pool, WDOG[ii].pool_time+WDOG[ii].pool_time ))
   {
     if(f_queue_chk(WDOG[ii].port) ) goto m1;
   }
  return;
}
/*----------------------------*/

int host_wd_sw[5]={0,0,0,0,0};
int ffgets_no_com_ICP( int ii)
{
//  Адрес функции будет устанавлен в указателе  ff_gets_com[Port]
//  при посылке команды ~**  в устройства ICP (  7060 и пр.).
//  Функция не ожидает ответа .
//  Если прошло время WDOG_Rqst[ii].timeout мс с момента окончания
// передачи последнего символа функция успешно завершается
//

/* ii - номер COM   1...3 */


   if( !IsTxBufEmpty(ii) )
   {
       host_wd_sw[ii] =0;
       return 0;
   }
   if(host_wd_sw[ii] != 1 )
   {
       time_snd[ii]=TimeStamp;
       host_wd_sw[ii]=1;
   }
   else if (host_wd_sw[ii] == 1 )
   {
        if( f_timer(time_snd[ii],ToutAns[ii]))
        { // истекло время ожидания

           host_wd_sw[ii]=0;
           return 1;
        }
   }
   return 0;
}
/* --------------------------- */
void  f_WD_end (int ii)
{
 struct COM_rqst *request;
 int nn;

  request=COM_que[ii].request[COM_que[ii].empt_ptr];
  nn=request->n_dev; // номер устройства  (0,1..)
  WDOG[nn].n_success++;
  f_queue_free(ii,&WDOG_Rqst[nn]);

}
/* --------------------------- */
int f_123( int n)

/* Проверяет является ли n-ный символ в буфере именем координаты,
   если нет - возвращает -1  , иначе номер координаты по порядку */

{
int i;
           switch(intrpr.wrd[n-1])
           {
            case '1': i=0; goto m_k1;
            case '2': i=1; goto m_k1;
            case '3': i=2; goto m_k1;
            case '4': i=3; goto m_k1;
            case '5': i=4; goto m_k1;
            case '6': i=5; goto m_k1;
            case '7': i=6; goto m_k1;
            case '8': i=7; goto m_k1;
            case '9': i=8; goto m_k1;
            case 'A': i=9; goto m_k1;
            case 'B': i=10; goto m_k1;
            case 'C': i=11; goto m_k1;
            case 'D': i=12; goto m_k1;
            case 'E': i=13; goto m_k1;
            case 'F': i=14; goto m_k1;
           }
           return -1;
   m_k1:   return i;
}
/*----------------------------------------------*/
/*----------------------------*/
int f_host()
{
//  int  hour,min,sec;
     // вводит команду из Host (PC) и интерпретирует ее
         if(ffgets_host(ComPortHost))
         {
          strcpy(intrpr.bfcom,cb_COM[ComPortHost]);
          n_bcom[ComPortHost]=0;
          return  f_intr();
         }
         return 0;
}
/*-------------------------------------------*/
void f_send_to_Host(int ii)
{
/* пересылает принятые из порта ii данные в Host
*/

// char *Result;
// int j,key,nextidx;
// int count;
//  count=n_bcom[ii];  // длина команды

 if(flag_echo_host )
     puts("   ");
 puts(cb_COM[ii]);
 putch('\n\r');
 f_queue_free(ii,&Host_Rqst);
 f_prompt();
}
/*-------------------------------------------*/
void f_prompt()
{
 if(flag_echo_host )
    if(( EchoComN==0)||( EchoComN==4))
     printf("\n\r>");
    else
     printf("\n\rCOM%d>",ComPortEcho);
}

/*-------------------------------------------*/
void f_empty_ans_echo(int ii)
{ // таймаут по ответу

 int count,i;

 if(flag_echo_host )
 {
     printf(" -?- ");
 }
 f_prompt();
 f_queue_free(ii,&Host_Rqst);
}
/*-------------------------------------------*/
/*
int ffgets_com_rtu( int ii)
{
//  Адрес функции будет устанавлен в указателе  ff_gets_com[Port]
// при посылке команды в устройство Modbus RTU.
//  Функция принимает символы из порта COM ii  в буфер cb_COM[ii].
//  При таймауте команда считается введенной и функция возвращает
// значение 1.
//

// ii - номер COM   1...4
 char tmp;
m1:
     if(IsCom(ii)==0)
     {
        if( f_timer(time_snd[ii],ToutAns[ii]))
        { // истек таймаут приема ответа на команду
          //   ff_answ_com[ii]=ff_answ_flt[ii];
           return 1;
        }
        return 0;
      }
     tmp=ReadCom(ii);
     time_snd[ii]= TimeStamp;

// if(ComProt[ii]==RTU)
//     printf(" &%02X", tmp & 0xff);

     cb_COM[ii][n_bcom[ii]]=tmp;
     if( (++n_bcom[ii]) >= n_bufcom )
      {
        cb_COM[ii][n_bufcom-1]=0;
        n_bcom[ii]=0;
  //
  //    printf("\n\r Command buffer overflow !\n\r--");
  //    puts(cb_COM1);
  //
      }
   goto m1;
}
*/
/* ---------------------------------------- */
/*-------------------------------------------*/
#define max_rd_str 40

int MVD_fl_ord[max_MVD]={1,1}; // порядок следования байт для числа float

void f_send_to_Host_sk(int ii)
{
/* пересылает принятые из SK или MVD данные в Host
*/
 // ii - номер COM порта

 struct COM_rqst *request;
 int i,im,fn,i1;
 char buf_tmp[max_rd_str];
 int count;
 unsigned long int val;
 union  { float f; unsigned long l; } o;

  request=COM_que[ii].request[COM_que[ii].empt_ptr];
  fn=request->function;

  count=n_bcom[ii];  // длина команды

  if(count<3) goto m_err;

  if(f_check_crc_RTU(cb_COM[ii],count)==0)
     goto m_err;
 switch(fn)
 {
  case RD_INT:
     if(cb_COM[ii][1] != 3) goto m_err;
     if(cb_COM[ii][2] != 2) goto m_err;
     val=(  (unsigned long int)cb_COM[ii][4] & 0x00ff) |
         ( ((unsigned long int)cb_COM[ii][3] << 8) & 0x00ff00) ;
     printf("  %ld (0x%lX)",val,val);
     break;
  case RD_LONG:
     if(cb_COM[ii][1] != 3) goto m_err;
     if(cb_COM[ii][2] != 4) goto m_err;
     val=
         ( (unsigned long)(cb_COM[ii][6]) & 0x000000ff) |
         ( ((unsigned long)cb_COM[ii][5] << 8) &0xff00) |
         ( ((unsigned long)cb_COM[ii][4] << 16) &0xff0000)  |
         ( ((unsigned long)cb_COM[ii][3] << 24) &0xff000000);
     printf(" %ld (0x%lX)",val,val);
     break;
  case RD_COIL:
     if(cb_COM[ii][1] != 1) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;i<im ;i++,i1++)
     {
       printf(" %02X",cb_COM[ii][i1]&0xff);
     }
     break;
  case RD_FLOAT:
      //
     if(cb_COM[ii][1] != 3) goto m_err;
     if(cb_COM[ii][2] != 4) goto m_err;

     switch(MVD_fl_ord[0])  // ( Reg 0521 )
     {
     case 0:
    //  code == 0 : 0  1  2  3
    //             [3][4][5][6]
     o.l=
         ( (unsigned long)cb_COM[ii][6]  &0xff) |                // 3
         ( ((unsigned long)cb_COM[ii][5] << 8) &0xff00) |        // 2
         ( ((unsigned long)cb_COM[ii][4] << 16) &0xff0000)  |    // 1
         ( ((unsigned long)cb_COM[ii][3] << 24) &0xff000000);    // 0
        break;
     case 1:
    //  code == 1 : 2  3  0  1
    //             [3][4][5][6]
     o.l=
         ( (unsigned long)cb_COM[ii][4]  &  0x000000ff) |         // 3
         ( ((unsigned long)cb_COM[ii][3] << 8) &  0x0000ff00) |   // 2
         ( ((unsigned long)cb_COM[ii][6] << 16) & 0x00ff0000)  |  // 1
         ( ((unsigned long)cb_COM[ii][5] << 24) & 0xff000000);    // 0
         break;
      case 2:
    //  code == 2 : 1  0  3  2
    //             [3][4][5][6]

     o.l=
         ( (unsigned long)cb_COM[ii][5]  &0xff) |              // 3
         ( ((unsigned long)cb_COM[ii][6] << 8) &0xff00) |      // 2
         ( ((unsigned long)cb_COM[ii][3] << 16) &0xff0000)  |  // 1
         ( ((unsigned long)cb_COM[ii][4] << 24) &0xff000000);  // 0
         break;
      case 3:
    //  code == 3 : 3  2  1  0
    //             [3][4][5][6]
     o.l=( (unsigned long)(cb_COM[ii][3]) & 0x000000ff) |      // 3
         ( ((unsigned long)cb_COM[ii][4] << 8) &0xff00) |      // 2
         ( ((unsigned long)cb_COM[ii][5] << 16) &0xff0000)  |  // 1
         ( ((unsigned long)cb_COM[ii][6] << 24) &0xff000000);  // 0
       break;
     }

//  printf(">> %02X",cb_COM[ii][3]);
//  printf(" %02X",cb_COM[ii][4]);
//  printf(" %02X",cb_COM[ii][5]);
//  printf(" %02X<<\n\r",cb_COM[ii][6]);

    if(( o.l == 0x7fa00000) || ( o.l == 0x00007fa0))
       printf(" !bad process variable (%08lX)",o.l);
    else
     //  printf(" %9g",o.f);
       printf(" %f",o.f);
     //printf(" %g (%08lX)",o.f,o.l);
    break;

  case RD_STRING:

     if(cb_COM[ii][1] != 3) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;(i<im)&&(i< (max_rd_str-1)) ;i++,i1++)
     {
      buf_tmp[i]=cb_COM[ii][i1];
     }
     buf_tmp[i]=0;
     printf(" %s",buf_tmp);
     break;

  case WR_INT:
    if(cb_COM[ii][1] != 6) goto m_err;
    break;
  case WR_LONG:
  case WR_FLOAT:
  case WR_STRING:
    if(cb_COM[ii][1] != 16) goto m_err;
    break;

  case WR_COIL:
    if(cb_COM[ii][1] != 5) goto m_err;
    break;

 default: goto m_err;
 }
     f_prompt();
     f_queue_free(ii,&Host_Rqst_sk);
     return;

    // ничего не послано в ответ
m_err:


    if(cb_COM[ii][1] & 0x80 )
    {
      if(cb_COM[ii][2]==1) {printf(" !! Illegal function");goto m2;}
      if(cb_COM[ii][2]==2) {printf(" !! Illegal data address");goto m2;}
      if(cb_COM[ii][2]==3) {printf(" !! Illegal data value");goto m2;}
      if(cb_COM[ii][2]==6) {printf(" !! Busy, rejected message");goto m2;}
    }
/*
    if(count>0) printf(" !! ");
    for(i=0;i<count;i++)
     printf(" %02X",cb_COM[ii][i]&0xff);
*/

      printf(" -?- ");
m2:
     f_prompt();
     f_queue_free(ii,&Host_Rqst_sk);
}
/*-------------------------------------------*/
void f_send_to_Host_rtu(int ii)
{
/* пересылает принятые из порта ii данные в Host
*/

// char *Result;
// int j,key,nextidx;
// int count;
//  count=n_bcom[ii];  // длина команды

 int count,i;

 count=n_bcom[ii];  // длина команды

 if(flag_echo_host )
 {
   if(count)
   {
       puts("   ");
    for(i=0;i<count;i++)
       printf(" %02X",(cb_COM[ii][i])&0xff );
       f_prompt();
//      printf("\n\rCOM%d>",ComPortEcho);
   }
   else
    { // ничего не послано в ответ
       printf(" -?- ");
       f_prompt();
    }
 }
 else
 {
  for(i=0;i<count;i++)
     putch(Host_Rqst.Cmd[i]);
 }

 f_queue_free(ii,&Host_Rqst_rtu);
}
/*-------------------------------------------*/
int (*ff_putch[5])(int ch)= {ToCom1,ToCom1,ToCom2,ToCom3,ToCom4};

int ffgets_host( int port)
{
//  Функция принимает команду от Host контроллера (PC)
//  выходная строка  cb_COM[port];
//  длина строки   n_bcom[port];

 char tmp;
m1:
 if(!IsCom(port))
 {
  return 0;
 }
 tmp=ReadCom(port);
   if( tmp == '\b')
    {
     if(n_bcom[port])
      {
       if(flag_echo_host )
        {
         (*ff_putch[port])(tmp);
         (*ff_putch[port])(' ');
         (*ff_putch[port])(tmp);
        }
       n_bcom[port]--;
      }
     goto m1;
    }
   else
    {
//     if ((tmp >= 'a') && (tmp <= 'z')) tmp &= 0xdf;
     cb_COM[port][n_bcom[port]]=tmp;

     if( (++n_bcom[port]) >= n_bufcom )
      {
        cb_COM[port][n_bufcom-1]=0;
        n_bcom[port]=n_bufcom-1;
      }
    }
   switch(tmp)
   { // указать все терминаторы
 //   case 0x0:
 //   case ';':
    case '\n':
    case '\r':
    n_bcom[port]--;
    cb_COM[port][n_bcom[port]]=0;
    return 1;
   }
   if(flag_echo_host)
         (*ff_putch[port])(tmp);
   goto m1;
  }

/* ================================================== */
/* ------------------------------------------- */
struct intr_r intrpr={0,0,0,0,0,0,0,0,0};
/* ========================================================= */
int f_inw()

/*   Из строки intrpr.bfcom   вводится слово в строку intrpr.wrd
   Начало анализа начинается с символа с индексом  intrpr.i3.
     Начальные пробелы и разделители игнорируются , слово вводится до первого
   пробела или разделителя за непробельным символом .
     Указатель  intrpr.i1 устанавливается на первый символ введенного
   слова в intrpr.bfcom.
     Указатель  intrpr.i2 устанавливается на последний символ введенного
   слова в intrpr.bfcom.
     Указатель  intrpr.i3 устанавливается на первый символ не пробел и не
   запятая  в intrpr.bfcom.
     В intrpr.wdl - длина введенного слова .
     Возвращается 0 если нет слова и достигнут конец строки  иначе 1.
*/

{
        intrpr.i1=intrpr.i3;
        intrpr.wdl=0;

//      printf("\n\r f_inw(),intrpr.i3=%d",intrpr.i3);

sw0:    switch(intrpr.bfcom[intrpr.i1])
        {
         case ' ':
         case 0x9:
         case ',':
         case ':':
         case ';':
         case '>':
         case '"':
         case '<':
         case '=':
         case '\n\r':
         case '\r': intrpr.i1++;goto sw0;

/*       case '*':  */
         case 0  :
//     printf("\n\r f_inw(),return(0),intrpr.i1=%d,intrpr.i1=%d,intrpr.i3=%d",intrpr.i1,intrpr.i2,intrpr.i3);
              return 0;
        }

        intrpr.i2=intrpr.i1;

sw1:    switch(intrpr.bfcom[intrpr.i2])
        {
         case ' ':
         case 0x9:
         case ',':
         case ':':
         case ';':
         case '=':
         case '\r':
         case '\n\r':
         case 0  : goto m3;
        }

         intrpr.wrd[intrpr.wdl]=intrpr.bfcom[intrpr.i2];
         if(++intrpr.wdl==wrd_w)  intrpr.wdl-- ;
         intrpr.i2++;
         goto sw1;

m3:      intrpr.i3=intrpr.i2;
         intrpr.i2--;
         intrpr.wrd[intrpr.wdl]=0;

sw2:    switch(intrpr.bfcom[intrpr.i3])
        {
         case ',':
         case ' ':
         case 0x9:
         case '\n\r':
         case '\r': intrpr.i3++;goto sw2;
        }

//      printf("\n\r f_inw(),return(1),intrpr.i3=%d",intrpr.i3);
        return 1;

}
/* ========================================================= */
int f_innum(char *strg)
/* вводит число в intrr[pp].num_var  */
{
    char cp;
    char *strg1;
    char *stopptr;
    float tmp;
    int i1;
    tmp=1.0;

//---------------------
            i1=0;
            if( strg[0] == '-')
             {
               tmp=-1.0;
               i1=1;
             }
            else if( strg[0] == '~')
             {
               tmp=-2.0;
               i1=1;
             }
//---------------------

    if( (strg[i1] == '0') && (strg[i1+1] == 'x')  || (strg[i1+1] == 'X') )
    {
      strg1=&strg[i1+2];
      while(*strg1)
       {
         cp= *strg1++;
         if( isxdigit(cp) );
         else return 0;
       }

      strg1=&strg[i1];
      if(tmp!=-2.0)
        intrpr.num_var=tmp*(float)strtoul(strg1,&stopptr,16);
      else
       {
        intrpr.num_var=(~(strtoul(strg1,&stopptr,16))) & HEX_MAX; ;
       }

      return 1;
    }
    else
    {
      strg1=&strg[i1];
      while(*strg1)
       {
         cp= *strg1++;
         if( isdigit(cp) || (cp=='+')||(cp=='.')||(cp==' ') || (cp=='-'));
         else return 0;
       }
      strg1=&strg[i1];
      if(tmp!=-2.0)
       {
//       intrpr.num_var = tmp *(float)atof(strg1);
         intrpr.num_var = tmp *(float)strtod(strg1,NULL);

       }
      else
       {
       //  tmp= (float)atof(strg1);
         tmp= (float)strtod(strg1,NULL);

          intrpr.num_var=( ( ~((int)tmp)) ) & HEX_MAX;
       }
    }
    return 1;
}
/*---------------------------------------------------------------------*/
int f_inhex(char *strg)
/* вводит hex число в intrr[pp].num_var  */
{
    char cp;
    char *strg1;
    char *stopptr;

      strg1=strg;

      while(*strg1)
       {
         cp= *strg1++;
         if( isxdigit(cp) );
         else return 0;
       }

      strg1=strg;
      intrpr.num_var=(float)strtoul(strg1,&stopptr,16);

    return 1;
}
/*---------------------------------------------------------------------*/
/*----------------------------------------*/
float f_lim(float vvr,float lim_low,float lim_high)
{
  if(vvr > lim_high) vvr=lim_high;
  else if(vvr < lim_low) vvr=lim_low;
  return vvr;
}
/*----------------------------------------*/
/*---------------------------------------------------*/
/* Отображение/ввод значений */
int f_dis_set( struct dis_set *ds_mas,int ib,int nn)
/*
      ib - длина команды
      nn - количество параметров
*/
{
int i,i_rez,i1;
char *strg;
char str_tmp[15];
long int l_tmp;
    i_rez=0;
    if(intrpr.wdl==ib)
       if(f_inw()) strg=intrpr.wrd;
       else
        {
         for(i=0;i<nn;i++)
         switch(ds_mas[i].type)
         {
          case T_FLOAT:
             printf(" %g", *(float*)ds_mas[i].op );
//           printf(" %f", *(float*)ds_mas[i].op );
             break;
          case T_INT:
             printf(" %d", *(int*)ds_mas[i].op );
             break;
          case T_INT_L:
             printf(" %ld", *(long int*)ds_mas[i].op );
             break;
          case T_HEX:
             printf(" %X", *(int*)ds_mas[i].op );
             break;
          case T_HEX_L:
             printf(" %08lX", *(long int*)ds_mas[i].op );
             break;
          case T_HX2:
             printf(" %02X", *(int*)ds_mas[i].op );
             break;
          case T_HX4:
             printf(" %04X", *(int*)ds_mas[i].op );
             break;
          case T_STR:
             printf(" %s", (char*)ds_mas[i].op );
             break;

         }
         return 0;
        }
    else
        strg=&intrpr.wrd[ib];


    switch(ds_mas[0].type)
     {
         case T_FLOAT:
         case T_INT:
          i1=f_innum(strg);
          break;
         case T_INT_L:
          i1=sscanf(strg,"%ld",&l_tmp);
          break;
        case T_HEX_L:
          i1=sscanf(strg,"%lx",&l_tmp);
          break;
        case T_HEX:
        case T_HX2:
        case T_HX4:
          i1=f_inhex(strg);
          break;
        case T_STR:
          i1=1;
          break;
     }
    if(i1)
     {
        switch(ds_mas[0].type)
       {
        case T_FLOAT:
          *(float*)ds_mas[0].op= (float)f_lim(intrpr.num_var,ds_mas[0].low_l,ds_mas[0].high_l);
          break;
        case T_INT:
        case T_HEX:
        case T_HX2:
        case T_HX4:
          *(int*)ds_mas[0].op= (int)f_lim(intrpr.num_var,ds_mas[0].low_l,ds_mas[0].high_l);
          break;
        case T_INT_L:
        case T_HEX_L:
             if((float)l_tmp < ds_mas[0].low_l) l_tmp =ds_mas[0].low_l;
             else if((float)l_tmp > ds_mas[0].high_l) l_tmp=ds_mas[0].high_l;
             *(long int*)ds_mas[0].op=l_tmp;
          break;
        case T_STR:
          strcpy((char*)ds_mas[0].op, strg);
          break;
       }
       i_rez++;
     }
    else goto dis_e;

    if (nn==1) return i_rez;

    for(;i_rez < nn;i_rez++)
     {
       if(!f_inw()) return i_rez;

       switch(ds_mas[i_rez].type)
        {
            case T_FLOAT:
            case T_INT:
             i1=f_innum(intrpr.wrd);
             break;

           case T_INT_L:
            i1=sscanf(intrpr.wrd,"%ld",&l_tmp);
            break;
        case T_HEX_L:
            i1=sscanf(intrpr.wrd,"%lx",&l_tmp);
            break;
           case T_HEX:
           case T_HX2:
           case T_HX4:
             i1=f_inhex(intrpr.wrd);
             break;
           case T_STR:
             i1=1;
             break;
        }
       if(i1)
        {
           switch(ds_mas[i_rez].type)
          {
           case T_FLOAT:
             *(float*)ds_mas[i_rez].op= (float)f_lim(intrpr.num_var,ds_mas[i_rez].low_l,ds_mas[i_rez].high_l);
             break;
           case T_INT:
           case T_HEX:
           case T_HX2:
           case T_HX4:
             *(int*)ds_mas[i_rez].op= (int)f_lim(intrpr.num_var,ds_mas[i_rez].low_l,ds_mas[i_rez].high_l);
             break;
        case T_INT_L:
        case T_HEX_L:
             if(l_tmp < ds_mas[i_rez].low_l) l_tmp =ds_mas[i_rez].low_l;
             else if(l_tmp > ds_mas[i_rez].high_l) l_tmp=ds_mas[i_rez].high_l;
             *(long int*)ds_mas[i_rez].op=l_tmp;
          break;
           case T_STR:
             strcpy((char*)ds_mas[i_rez].op, intrpr.wrd);
             break;
          }
        }
       else goto dis_e;
     }

 // if(f_inw()) goto dis_e;
    return i_rez;

dis_e:
//    (*ff_putch[ComPortHost])('?');
    putch('?');
    return -1;
}
/*------------------------------*/
float par1=12,par2=13,par3=14,par4=15.345;
struct dis_set  ds_par[4]=
{
/*----------------*/
  &par1,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &par2,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &par3,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &par4,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
unsigned long int p_mem=0xffff0;
unsigned char *mem_ptr=NULL;
struct dis_set  ds_dm=
{
/*----------------*/
  &p_mem,
 -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
};
//----------------------
struct dis_set  ds_zp[]=
{
/*----------------*/
  &ZeroPage,
  0,
  BIG_P,
  T_INT,
/*----------------*/
  &EmptyPage,
  0,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_mvdn=
{
//--------------
  &nn_mvd,
  0,
  2,
  T_INT,
//--------------
};
//----------------------

struct dis_set  ds_scan[4]=
{
/*----------------*/
  &ComPortEcho,
  1,
  3,
  T_INT,
/*----------------*/
  &ToutLicpScan,
  0.,
  BIG_I,
  T_INT,
/*----------------*/
  &licp_amax,
  0.,
  255,
  T_INT,
/*--------------*/
  &LICP_Rqst.CRC_flag,
  0,
  1,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mdn[2]=
{
/*----------------*/
  &ModeReduce ,
  0,
  3,
  T_INT,
/*----------------*/
  &BegStage,
  0,
  Stage4,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mdp=
{
/*----------------*/
  &mode_r ,
  0,
  3,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mdi=
{
/*----------------*/
  &mode_i ,
  0,
  3,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_parp[]=
{
//---------------
  &PressLvl_on0,      // 0.11
  -BIG_P,
  BIG_P,
  T_FLOAT,
//---------------
  &PressLvl_off0,
  -BIG_P,             // 0.05
  BIG_P,
  T_FLOAT,
//---------------
/*
  &Comp_kor,          // 1
  0.1,
  BIG_P,
  T_FLOAT,
*/
//----------------
  &Temp_kor,           // 8.5
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  &R_MVD,             // 12
  0.01,
  BIG_P,
  T_FLOAT,
//----------------
/*===============
  &PressLvl_off1,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  &PressLvl_on2,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
  &PressLvl_off2,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//----------------
======================*/
};
//----------------------
#if defined(RTU_ComSK)
struct dis_set  ds_sk[6]=
{
/*----------------*/
/*
  &ComSK_fn[0],
  0.,
  32,
  T_INT,
*/
/*----------------*/
/*----------------*/
  &ComSK_Ctrl[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &ComSK_SV[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &ComSK_SA[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &ComSK_SD[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &ComSK_State[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &ComSK_Err_cod[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
};
//----------------------
long int sk_reg_n=1;
long int sk_reg_q=1;
struct dis_set  ds_rsk[2]=
{
/*----------------*/
  &sk_reg_n,
  1.,
  65536,
  T_INT_L,
/*----------------*/
  &sk_reg_q,
  0.,
  65535,
  T_INT_L,
/*----------------*/
};
//----------------------
struct dis_set  ds_skwd[4]=
{
/*----------------*/
  &sk_pool_period[0],
  10.,
  BIG_P,
  T_INT_L,
/*----------------*/
  &ComSK_WD_Rqst[0].timeout,
  10.,
  BIG_P,
  T_INT_L,
/*----------------*/
  &sk_pool_period[1],
  10.,
  BIG_P,
  T_INT_L,
/*----------------*/
  &ComSK_WD_Rqst[1].timeout,
  10.,
  BIG_P,
  T_INT_L,
/*----------------*/
};
#endif  // if defined(RTU_ComSK)
//----------------------
#if defined(RTU_Delta)
struct dis_set  ds_dlt[]=
{
/*----------------*/
  &DLT_DEB,
  0.,
  1,
  T_INT,
/*----------------*/
  &Delta_Ctrl[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &Delta_SV[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &Delta_SA[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &Delta_SD[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &Delta_State[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &Delta_Err_cod[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_dltn[3]=
{
/*----------------*/
  &Delta_SV_beg[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &Delta_SA_beg[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &Delta_SD_beg[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
unsigned int dlt_reg_n=1;
long int dlt_reg_q=1;
long int sk_reg_n=1;
long int sk_reg_q=1;
struct dis_set  ds_rdlt[2]=
{
/*----------------*/
  &dlt_reg_n,
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &dlt_reg_q,
  0.,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
#endif  // if defined(RTU_Delta)
//----------------------
//----------------------
long int mvd_reg_n=1;
long int mvd_reg_q=1;
struct dis_set  ds_rmvd[2]=
{
/*----------------*/
  &mvd_reg_n,
  1.,
  65536,
  T_INT_L,
/*----------------*/
  &mvd_reg_q,
  0.,
  65535,
  T_INT_L,
/*----------------*/
};
//----------------------
long int wmvd_reg_v=1;
struct dis_set  ds_wmvd[2]=
{
/*----------------*/
  &mvd_reg_n,
  1.,
  65536,
  T_INT_L,
/*----------------*/
  &wmvd_reg_v,
  0.,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
char str_mvd[40];
struct dis_set  ds_wmvds[3]=
{
/*----------------*/
  &mvd_reg_n,
  1.,
  65536,
  T_INT_L,
/*----------------*/
  &mvd_reg_q,
  0.,
  65535,
  T_INT_L,
/*----------------*/
  &str_mvd[0],
  0,
  65536,
  T_STR,
/*----------------*/
};
//----------------------
float fl_id=0,fl_id1=1;
char chr_id[20]="Default";
struct dis_set  ds_id[3]=
{
/*----------------*/
  &fl_id,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &fl_id1,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &chr_id[0],
  0,
  65536,
  T_STR,
/*----------------*/
};
//----------------------
//----------------------
float wmf_v=0;
 union  { float f; unsigned long l; } mvd;
struct dis_set  ds_wmvf[2]=
{
/*----------------*/
  &mvd_reg_n,
  1.,
  65536,
  T_INT_L,
/*----------------*/
  &mvd.f,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
int tpt[2]={1,1};
int tp_num=1;
float tp_val=0,tp_adc=0;
struct dis_set  ds_tp[3]=
{
/*----------------*/
  &tp_num,
  1.,
  MAX_COR_D,
  T_INT,
/*----------------*/
  &tp_val,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &tp_adc,
  -MaxADC,
  MaxVADC,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_de[]=
{
/*----------------*/
  &ICP_error[0],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[1],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[2],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[3],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[4],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[5],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[6],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[7],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
  &ICP_error[8],
  -BIG_P,
  BIG_P,
  T_HX4,
/*----------------*/
};
//----------------------
struct dis_set  ds_ioch[3]=
{
/*----------------*/
  &I7060[0].channels,
  0.,
  8,
  T_INT,
/*----------------*/
  &I7060[1].channels,
  0.,
  8,
  T_INT,
/*----------------*/
  &flag_ext_t,
  0.,
  1,
  T_INT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_io[]=
{
/*----------------*/
  &OUT_VAR,
  0.,
  255,
  T_HX2,
/*----------------*/
  &INP_VAR,
  0.,
  255,
  T_HX2,
/*----------------*/
  &INP_VARi,
  0.,
  255,
  T_HX2,
/*----------------*/
  &INP_inv,
  0.,
  255,
  T_HX2,
/*----------------*/
};
//----------------------
struct dis_set  ds_io1[6]=
{
/*----------------*/
  &i7060_out[0],
  0.,
  15,
  T_HX2,
/*----------------*/
  &i7060_inp[0],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_inpl[0],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_inph[0],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_wdf[0],
  0.,
  4,
  T_INT,
/*----------------*/
  &i7060_outc[0],
  0.,
  15,
  T_HX2,
/*----------------*/
};
//----------------------
struct dis_set  ds_io2[6]=
{
/*----------------*/
  &i7060_out[1],
  0.,
  15,
  T_HX2,
/*----------------*/
  &i7060_inp[1],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_inpl[1],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_inph[1],
  0,
  15,
  T_HX2,
/*----------------*/
  &i7060_wdf[1],
  0.,
  4,
  T_INT,
/*----------------*/
  &i7060_outc[1],
  0.,
  15,
  T_HX2,
/*----------------*/
};
//----------------------
struct dis_set  ds_iod1[]=
{
/*----------------*/
/*=======
  &i7060_fn[0],
  0.,
  255,
  T_INT,
===========*/
/*----------------*/
  &I7060_wd_E[0],
  0.,
  1,
  T_INT,
/*----------------*/
  &I7060_wd_VV[0],
  0.,
  255,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_iod2[]=
{
/*----------------*/
/*========
  &i7060_fn[1],
  0.,
  255,
  T_INT,
============/
/*----------------*/
  &I7060_wd_E[1],
  0.,
  1,
  T_INT,
/*----------------*/
  &I7060_wd_VV[1],
  0.,
  255,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_dpp[]=
{
/*----------------*/
  &s_MVD[0].PressD,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].PressG,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].PressB,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].Press,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
//float flow_tmp=0;
struct dis_set  ds_dpd[]=
{
/*----------------*/
  &s_MVD[0].MassT,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[1].MassT,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].MassI,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[1].MassI,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].FlowM,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[1].FlowM,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].Dens,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].Temp,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].PressG,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].Press,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].PressB,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].FlowV,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mvd[8]=
{
/*----------------*/
  &MVD_fn[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &s_MVD[0].r_addr,
  1.,
  BIG_P,
  T_INT,
/*----------------*/
  &s_MVD[0].n,
  1.,
  BIG_P,
  T_INT,
/*----------------*/
  &s_MVD[0].i,
  0.,
  BIG_P,
  T_INT,
/*----------------*/
  &s_MVD[0].l,
  0.,
  BIG_P,
  T_INT_L,
/*----------------*/
  &s_MVD[0].f,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].c[0],
  0.,
  BIG_P,
  T_HX4,
/*----------------*/
  &s_MVD[0].a[0],
  0.,
  BIG_P,
  T_STR,
/*----------------*/
};
//----------------------
struct dis_set  ds_mvt[2]=
{
/*----------------*/
  &TimeMVD_Init,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &TimeMVD_evt ,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
/*
float cst_tmp;
struct dis_set  ds_cst[3]=
{
//----------------------
  &cst_tmp,
  0.,
  BIG_P,
  T_FLOAT,
//----------------------
  &summ_v,
  0,
  BIG_P,
  T_FLOAT,
//----------------------
  &cost_v,
  0,
  BIG_P,
  T_FLOAT,
//----------------------
};
*/
//----------------------
//----------------------
struct dis_set  ds_vol[2]=
{
/*----------------*/
  &vol_f,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &vol_f,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
struct dis_set  ds_clv[]=
{
//--------------
  &CL_val[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_val[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_T1,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_T2,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_T3,
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_T4,
  -BIG_P,
  BIG_P,
  T_INT_L,
//--------------
};
//----------------------
//----------------------
struct dis_set  ds_clvr[]=
{
//--------------
  &CL_valR[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &CL_valR[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
};
//----------------------
float dsc_tmp=0;
float offs_cor=0;
float fct_offs=0,fct_delay=0;
float fct_offs_r=0;
struct dis_set  ds_dsc[5]=
{
/*----------------*/
  &vol_mom0,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &vol_mom,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &flow_mom,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &offs_cor,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &dsc_tmp,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};


#if(SIM0 != 0)
//----------------------
struct dis_set  ds_flow[]=
{
/*----------------*/
  &Sim_FlowM[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Sim_FlowM[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};

#endif


//----------------------
struct dis_set  ds_ka[3]=
{
/*----------------*/
  &fct_offs,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &fct_offs_r,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &t_mvd_cor,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
struct dis_set  ds_mko[8]=
{
/*----------------*/
  &num_out1,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out2,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out3,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out4,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out5,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out6,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out7,
  0,
  16,
  T_INT,
/*----------------*/
  &num_out8,
  0,
  16,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mks[]=
{
/*----------------*/
  &num_in1,
  0,
  8,
  T_INT,
/*----------------*/
  &num_in2,
  0,
  8,
  T_INT,
/*----------------*/
  &num_in3,
  0,
  8,
  T_INT,
/*----------------*/
  &num_in4,
  0,
  8,
  T_INT,
/*----------------*/
/*----------------*/
};
//----------------------
struct dis_set  ds_mki[]=
{
/*----------------*/
  &mski_inp1,
  0,
  255,
  T_INT,
/*----------------*/
  &mski_inp2,
  0,
  255,
  T_INT,
/*----------------*/
  &mski_inp3,
  0,
  255,
  T_INT,
/*----------------*/
  &mski_inp4,
  0,
  255,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_mka[]=
{
/*----------------*/
  &analog_num[0],
  0,
  8,
  T_INT,
/*----------------*/
  &analog_num[1],
  0,
  8,
  T_INT,
/*----------------*/
  &analog_num[2],
  0,
  8,
  T_INT,
/*----------------*/
};
//----------------------
//----------------------
float ftmp_na[3];
struct dis_set  ds_na[]=
{
/*----------------*/
  &ftmp_na[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_na[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_na[2],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_no[]=
{
/*----------------*/
  &analog_offset[0],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &analog_offset[1],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &analog_offset[2],
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
unsigned int fle;
struct dis_set  ds_fle=
{
/*----------------*/
  &fle,
  0xC000,
  0xE000,
  T_HX4,
/*----------------*/
};
//----------------------
int n_beg,n_end;
struct dis_set ds_pda[2]=
{
/*----------------*/
  &n_beg,
  1,
  BIG_P,
  T_INT,
/*----------------*/
  &n_end,
  1,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
int n_lst=1;
struct dis_set ds_pdl=
{
/*----------------*/
  &n_lst,
  1,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set ds_pd=
{
/*----------------*/
  &P_dem,
  0,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
int n_dnn;
struct dis_set ds_pdda=
{
/*----------------*/
  &n_dnn,
  1,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
int d_lst=1;
struct dis_set ds_pddl=
{
/*----------------*/
  &d_lst,
  1,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
int tt_sec=0,tt_min=56,tt_hour=1,tt_day=30,tt_month=7,tt_year=9;
struct dis_set ds_pddp[]=
{
/*----------------*/
  &tt_sec,
  0,
  59,
  T_INT,
/*----------------*/
  &tt_min,
  0,
  59,
  T_INT,
/*----------------*/
  &tt_hour,
  0,
  23,
  T_INT,
/*----------------*/
  &tt_day,
  1,
  31,
  T_INT,
/*----------------*/
  &tt_month,
  1,
  12,
  T_INT,
/*----------------*/
  &tt_year,
  0,
  99,
  T_INT,
/*----------------*/
  &s_mode,
  0,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
int pdn_tmp;
struct dis_set ds_pdn=
{
/*----------------*/
  &pdn_tmp,
  0,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set ds_tsd[4]=
{
/*----------------*/
  &n_dot[0][0],
  0,
  6,
  T_INT,
/*----------------*/
  &n_dot[0][1],
  0,
  6,
  T_INT,
/*----------------*/
  &n_dot[0][2],
  0,
  6,
  T_INT,
/*----------------*/
  &TSD_period,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
/*----------------*/

float cutoff_off_M=0.2;
float cutoff_off_V=0.2;
float cutoff_on_M =0.0;
float cutoff_on_V =0.0;
//----------------------
struct dis_set ds_ctrl[]=
{
/*----------------*/
  &t_ctrl,
  0,
  2,
  T_INT,
/*----------------*/
  &cutoff_off_M,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &cutoff_off_V,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &tim_MVD_delay,
  -BIG_P,
  BIG_P,
  T_INT_L,
/*----------------*/
};
/*----------------*/

//----------------------
struct dis_set  ds_br[4]=
{
/*----------------*/
  &ComBaud[1],
  1200,
  115200,
  T_INT_L,
/*----------------*/
  &ComBaud[2],
  1200,
  115200,
  T_INT_L,
/*----------------*/
  &ComBaud[3],
  1200,
  115200,
  T_INT_L,
/*----------------*/
  &ComBaud[4],
  1200,
  115200,
  T_INT_L,
/*----------------*/
};
//----------------------
struct dis_set  ds_cp[4]=
{
/*----------------*/
  &ComProt[1],
  0,
  2,
  T_INT,
/*----------------*/
  &ComProt[2],
  0,
  2,
  T_INT,
/*----------------*/
  &ComProt[3],
  0,
  2,
  T_INT,
/*----------------*/
  &ComProt[4],
  0,
  2,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set ds_trtu[4]=
{
/*----------------*/
  &byte_timout_rtu[1],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &byte_timout_rtu[2],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &byte_timout_rtu[3],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &byte_timout_rtu[4],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
struct dis_set ds_sct[]=
{
/*----------------*/
  &scom_tim[1],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &scom_tim[2],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &scom_tim[3],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &scom_tim[4],
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
int cm_lgth,cm_parity,cm_stop;
long int cm_baud=9600;
struct dis_set  ds_cm[]=
{
/*----------------*/
  &cm_baud,
  1200,
  115200L,
  T_INT_L,
/*----------------*/
  &cm_lgth,
  7,
  8,
  T_INT,
/*----------------*/
  &cm_parity,
  0,
  4,
  T_INT,
/*----------------*/
  &cm_stop,
  1,
  2,
  T_INT,
/*----------------*/
};
//----------------------
int status,port,addr,CRC_flag,pool_time,timeout;

struct dis_set  ds_dev[]=
{
/*----------------*/
  &status,
  0,
  1,
  T_INT,
/*----------------*/
  &port,
  1,
  3,
  T_INT,
/*----------------*/
  &addr,
  0,
  255,
  T_INT,
/*----------------*/
  &CRC_flag,
  0.,
  1,
  T_INT,
/*----------------*/
  &pool_time,
  0.,
  BIG_I,
  T_INT,
/*----------------*/
  &timeout,
  0.,
  BIG_I,
  T_INT,
/*----------------*/
/*----------------*/
};
long int baud=9600;
int TT_par,FF_par,addr0;
//----------------------
struct dis_set  ds_mod[]=
{
/*----------------*/
  &addr,
  0,
  255,
  T_INT,
/*----------------*/
  &baud,
  1200.,
  115200,
  T_INT_L,
/*----------------*/
  &TT_par,
  0.,
  BIG_I,
  T_HX2,
/*----------------*/
  &FF_par,
  0.,
  BIG_I,
  T_HX2,
/*----------------*/
};
//----------------------
float dns_temp=32.,dns_dns=532,dns_cmps=0,dns_dns20=0;
struct dis_set  ds_dns[]=
{
/*----------------*/
  &dns_dns,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &dns_temp,
  -50,
  50,
  T_FLOAT,
/*----------------*/
  &dns_cmps,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &dns_dns20,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
struct dis_set  ds_dn=
{
/*----------------*/
  &s_MVD[0].Dens,
 -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
/*----------------*/
};
//----------------------
struct dis_set  ds_mmu[]=
{
/*----------------*/
  &un_mmi1,
  0,
  6,
  T_INT,
/*----------------*/
  &un_mmi2,
  0,
  6,
  T_INT,
/*----------------*/
  &un_mmi3,
  0,
  6,
  T_INT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_modf=
{
/*----------------*/
  &ModeFill,
  1,
  3,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_stg[3]=
{
/*----------------*/
  &stage_max,
  0,
  10,
  T_INT,
/*----------------*/
  &stage_rl,
  0,
  10,
  T_INT,
/*----------------*/
  &stage_c,
  0,
  10,
  T_INT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_dnf[]=
{
/*----------------*/
  &k_Den,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &i_dens,
  0,
  BIG_P,
  T_HX2,
/*----------------*/
};
//----------------------
struct dis_set  ds_kp[]=
{
/*----------------*/
  &k_p,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &k_i,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &k_d,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_kdp[]=
{
/*----------------*/
  &kd_p,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &kd_i,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &kd_d,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_kip[]=
{
/*----------------*/
  &ki_p,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &ki_i,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &ki_d,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
/*----------------*/

float ftmp_p[4];
/*----------------*/
struct dis_set  ds_lp[]=
{
/*----------------*/
  &ftmp_p[0],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[1],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[2],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[3],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &f_Beg,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};

/*----------------*/
struct dis_set  ds_di[]=
{
/*----------------*/
  &I_dem,
  -BIG_P,
  BIG_P,
  T_INT_L,
/*----------------*/
  &I_real,
  0,
  BIG_P,
  T_INT,
/*----------------*/
  &ftmp_p[0],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};

/*----------------*/
struct dis_set  ds_ldp[]=
{
/*----------------*/
  &ftmp_p[0],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[1],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[2],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[3],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_fdn[]=
{
/*----------------*/
  &Flow_on[1],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_on[2],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_on[3],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_on[4],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_fdf[]=
{
/*----------------*/
  &Flow_off[1],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_off[2],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_off[3],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Flow_off[4],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_dd[]=
{
/*----------------*/
  &P_Dif_d,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].PressD,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ftmp_p[0],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
/*----------------*/
struct dis_set  ds_dp[]=
{
/*----------------*/
  &ftmp_p[0],
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &s_MVD[0].Press,
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Delta_SV[0],
  0.,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_dnt[]=
{
/*----------------*/
  &Tim_prb_plus,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &Tim_prb_minus,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
  &Tim_antd,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
struct dis_set  ds_part[]=
{
  &cl1_delayR_off,
  0,
  BIG_P,
  T_INT_L,
//--------------
  &cl2_delayR_off,
  0,
  BIG_P,
  T_INT_L,
//--------------
  &Out3_delayR_off,
  0,
  BIG_P,
  T_INT_L,
//--------------
};
//----------------------
struct dis_set  ds_pard[]=
{
/*----------------*/
  &k_Den0_Off,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &k_Den0_On,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Tim_antd,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
/*================
//----------------
  &k_Den_Off,
  0,
  BIG_P,
  T_FLOAT,
//----------------
  &k_Den_On,
  0,
  BIG_P,
  T_FLOAT,
//----------------
=================*/
};
//----------------------
struct dis_set  ds_dtc[]=
{
/*----------------*/
  &Density,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Temperature,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Composition,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Dens0,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &Temperature1,
  -BIG_P,
  BIG_P,
  T_FLOAT,
/*----------------*/
/*----------------*/
};
//----------------------
struct dis_set  ds_pass=
{
/*----------------*/
  &Password,
  0,
  BIG_P,
  T_INT_L,
/*----------------*/
};
//----------------------
float ex_p=0.05,ex_m=0.05;
struct dis_set  ds_ex[]=
{
/*----------------*/
  &ex_p,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ex_m,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_flch[]=
{
//--------------
  &val_flch,
 -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &val_flch2,
 -BIG_P,
  BIG_P,
  T_FLOAT,
//--------------
  &Tim_stg_ctrl,
  0,
  BIG_P,
  T_INT_L,
//--------------
  &Tim_stg_ctrl0,
  0,
  BIG_P,
  T_INT_L,
//--------------
  &Fl_perm,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
//----------------------
struct dis_set  ds_stch[]=
{
//----------------
  &Tim_stg_ctrl,
  0,
  BIG_P,
  T_INT_L,
//----------------
//----------------
  &Tim_stg_ctrl0,
  0,
  BIG_P,
  T_INT_L,
//----------------
  &Fl_perm,
  0,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
struct dis_set  ds_vch[]=
{
//----------------
  &v_lvl1,
  -5,
  30,
  T_FLOAT,
/*----------------*/
  &v_lvl2,
  -5,
  30,
  T_FLOAT,
/*----------------*/
  &volt_dc_cmp,
  -5,
  30,
  T_FLOAT,
/*----------------*/
  &Tim_volt,
  0,
  BIG_P,
  T_INT,
//----------------
//----------------
  &Tim_volt_mes,
  0,
  BIG_P,
  T_INT_L,
//----------------
};
//----------------------
char buf_str[20];
struct dis_set  ds_modn=
{
/*----------------*/
  buf_str,
  1,
  BIG_P,
  T_STR,
/*----------------*/
};
//----------------------
struct dis_set  ds_wins=
{
/*----------------*/
  &FlagWinSum,
  0,
  1,
  T_INT,
//-----------
};
//----------------------
//----------------------
#if defined(ICP_7017C)
//----------------------
struct dis_set  ds_adc[8]=
{
/*----------------*/
  &ADC[0],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[1],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[2],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[3],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[4],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[5],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[6],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
  &ADC[7],
  0.,
  BIG_P,
  T_FLOAT,
/*----------------*/
};
//----------------------
struct dis_set  ds_adc1[]=
{
/*----------------*/
  &dat_i[0],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[1],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[2],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[3],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[5],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[6],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[7],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
  &dat_i[8],
  -BIG_P,
  BIG_P,
  T_HEX_L,
/*----------------*/
};
//----------------------
#endif
//----------------------
struct dis_set  ds_com=
{
/*----------------*/
  &EchoComN,
  0,
  4,
  T_INT,
/*----------------*/
};
//----------------------
struct dis_set  ds_echo[2]=
{
/*----------------*/
  &flag_Deb,
  0,
  1,
  T_INT,
/*----------------*/
  &flag_echo_host,
  0,
  1,
  T_INT,
/*----------------*/
};
//----------------------
int fl_wr_eee=0;
struct dis_set  ds_fls[2]=
{
/*----------------*/
  &flag_Serv,
  0,
  1,
  T_INT,
/*----------------*/
  &fl_wr_eee,
  0,
  1,
  T_INT,
/*----------------*/
};
/*
//----------------------
struct dis_set  ds_pmp[]=
{
//----------------
  &ComPortPmp1,
  1,
  4,
  T_INT,
//----------------
  &P_addr,
  0,
  31,
  T_INT,
//----------------
  &flag_spec,
  0,
  1,
  T_INT,
//----------------
  &WD_PMP_Per,
  0,
  BIG_P,
  T_INT_L,
//----------------
};
*/
//-----------------------------------
  /* для trace()  */
//-----------------------------------

long int i_nn_d=5.;
int fl_trace=0;
long int i_nn=0.;
int dim_xyz=dim_xyz_c; /* длина буфера записи */
int fl_trace_loop=0;

//float *buf_xyz=(float *)0x30000000;
long int buf_xyz[dim_xyz_c];
//long int *buf_xyz;
int uk_buf=0;
long int *uk_ns[5]={NULL,NULL,NULL,NULL,NULL};
int f_ns[5]={10,1,4,9,11};
int cnt_after=0;
long int ns_fict=0;
/*----------------*/
void *list_ns[]={
&ns_fict,           // 0

&s_MVD[0].VolT,     // 1
&summ_v,            // 2
&cost_v,            // 3
&s_MVD[0].Dens,     // 4
&VolT_int,          // 5
&summ_v_int,        // 6
&VolT_id,           // 7
&summ_v_id,         // 8
&s_MVD[0].MassT,    // 9
(void *)0x40006c,   // 10 TimeStamp
&i7060_out[0],      // 11
&i7060_inp[0],      // 12
&k_Den,             // 13
&s_MVD[0].MassI,    // 14
&s_MVD[0].VolTd,    // 15
&s_MVD[0].Press,    // 16
&s_MVD[0].Temp,     // 17
&s_MVD[0].Compos,   // 18
&s_MVD[0].PressG,   // 19
&Delta_current[0],  // 20
&INP_VAR,           // 21
&OUT_VAR,           // 22

&s_MVD[0].FlowM,    // 23
&s_MVD[0].PressB,   // 24
&P_Dif_d,           // 25
&XN,                // 26
&Delta_SV[0],       // 27
&XdN,               // 28
&P_dem_c,           // 29
&flag_flow,         // 30
&s_MVD[0].Volt_A,   // 31
&s_MVD[0].Volt_DC,  // 32
&s_MVD[0].FlowV,    // 33

&ns_fict,           // 0

};
int list_ns_type[]={
T_INT_L,      // 0   ns_fict

T_FLOAT,      // 1    s_MVD[0].VolT
T_FLOAT,      // 2    summ_v
T_FLOAT,      // 3    cost_v
T_FLOAT,      // 4    s_MVD[0].Dens
T_FLOAT,      // 5    VolT_int
T_FLOAT,      // 6    summ_v_int
T_FLOAT,      // 7    VolT_id
T_FLOAT,      // 8    summ_v_id
T_FLOAT,      // 9    s_MVD[0].MassT
T_INT_L,      // 10   TimeStamp

T_HX2,        // 11   i7060_out[0],
T_HX2,        // 12   i7060_inp[0],

T_FLOAT,      // 13   k_Den,
T_FLOAT,      // 14   s_MVD[0].MassI
T_FLOAT,      // 15   s_MVD[0].VolTd
T_FLOAT,      // 16   s_MVD[0].s_MVD[0].Press,
T_FLOAT,      // 17   s_MVD[0].s_MVD[0].Temp,
T_FLOAT,      // 18   s_MVD[0].s_MVD[0].Compos,
T_FLOAT,      // 19   s_MVD[0].s_MVD[0].PressG,

T_INT,        // 20  Delta_current[0]
T_HX2,        // 21  INP_VAR
T_HX2,        // 22  OUT_VAR

T_FLOAT,      // 23  s_MVD[0].FlowM,
T_FLOAT,      // 24  s_MVD[0].PressB,
T_FLOAT,      // 25  P_Dif_d,
T_INT_L,      // 26  XN,
T_INT,        // 27  Delta_SV[0],
T_INT_L,      // 28  XdN,
T_INT_L,      // 29  P_dem_c,
T_INT,        // 30  flag_flow,
T_FLOAT,      // 31  s_MVD[0].Volt_A,
T_FLOAT,      // 32  s_MVD[0].Volt_DC,
T_FLOAT,      // 33  s_MVD[0].FlowV,

T_INT_L,      // 0   ns_fict

};

/* ---------------------------------------- */

void PrintOp(int num_op)
{
char fst_str[20];

if(num_op > (sizeof(list_ns) / sizeof(&summ_v)-1) )
    sprintf(fst_str,"====" );
else
  switch (list_ns_type[num_op])
  {
          case T_FLOAT:
    sprintf(fst_str,"%g", *(float*)list_ns[num_op] );
             break;
          case T_INT:
    sprintf(fst_str,"%d", *(int*)list_ns[num_op] );
             break;
          case T_INT_L:
    sprintf(fst_str,"%ld", *(long int*)list_ns[num_op] );
             break;
          case T_HEX:
    sprintf(fst_str,"%X", *(int*)list_ns[num_op] );
             break;
          case T_HX2:
    sprintf(fst_str,"%02X", *(int*)list_ns[num_op] );
             break;
          case T_HX4:
    sprintf(fst_str,"%04X", *(int*)list_ns[num_op] );
             break;
          case T_STR:
    sprintf(fst_str,"%s", (char*)list_ns[num_op] );
             break;
          case T_DBL:
    sprintf(fst_str,"%lg", *(double*)list_ns[num_op] );
             break;
  }
  printf(" %s",fst_str);
}

/*================================================================*/
/* ---------------------------------------- */
struct dis_set  ds_vnn[3]=
{
/*----------------*/
  &TSD_vn[0][0],
  1,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &TSD_vn[0][1],
  1,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &TSD_vn[0][2],
  1,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
};
//----------------------
int v_num_var=9;
/*----------------*/
struct dis_set  ds_var[2]=  /* 1 значениe */
{
/*----------------*/
  &v_num_var,
  1,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &ns_fict,           // 0
  -BIG_P,
  BIG_P,
  T_INT,
/*----------------*/
};
//----------------------
/*----------------*/
struct dis_set  ds_ns[8]=  /* 1 значениe */
{
/*----------------*/
  &f_ns[0],
  0.,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &f_ns[1],
  0.,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &f_ns[2],
  0.,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &f_ns[3],
  0.,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &f_ns[4],
  0.,
 (float)(sizeof(list_ns) / sizeof(&summ_v)-1),
  T_INT,
/*----------------*/
  &i_nn_d,
  0.,
  BIG_P,
  T_INT_L,
/*----------------*/
  &dim_xyz,
  0.,
  dim_xyz_c,
  T_INT,
/*-----------------*/
  &fl_trace_loop,
  0.,
  1.0,
  T_INT,
/*-----------------*/
};
/*----------------*/
/*----------------*/
void f_ns_count()
{
int i;
  for(i=0;i<5;i++)
     if(f_ns[i] > 0)
      {
        if( f_ns[i] <= (int)(sizeof(list_ns) / sizeof(&summ_v)-1) )
          uk_ns[i]=(long int *)list_ns[(int)f_ns[i]];
        else
        {
         f_ns[i] = 0;
         uk_ns[i]=(long int *)&ns_fict;
        }
      }
     else
      {
       f_ns[i] = 0;
       uk_ns[i]=(long int *)&ns_fict;
      }
}
/*----------------------------------------------*/
/* =================
void trace()      // store trace for variables  specified in f_ns[]
{
//----------------------------------
 if(fl_trace_loop != 0)
  {
  if (FL_err+ fl_trace)
   {  if(cnt_after >= Val_after)  return;
      else  cnt_after++;
   }
  else cnt_after=0;


  if(uk_buf > (dim_xyz-6.)) uk_buf=0;
  if( (i_nn+=1.) >= i_nn_d)
    {
//----------------------------------------------
//----------------------------------------------
      i_nn=0.;
      if(f_ns[0] == 0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[0];
      if(f_ns[1] == 0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[1];
      if(f_ns[2]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[2];
      if(f_ns[3]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[3];
      if(f_ns[4]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[4];
//---------------------------------------------
    }

  }
 else
  if(uk_buf < (dim_xyz-6.))
   if( (i_nn+=1.) >= i_nn_d)
    {
      i_nn=0.;
      if(f_ns[0] == 0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[0];
      if(f_ns[1] == 0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[1];
      if(f_ns[2]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[2];
      if(f_ns[3]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[3];
      if(f_ns[4]==0) goto m_end;
      buf_xyz[uk_buf++]=*uk_ns[4];
    }
m_end:
    return;
}

=========*/
// ==============================================
void f_init_TSD()
{
 int i,i1;
for(i1=0;i1<2;i1++)
 for(i=0;i<3;i++)
  TSD_value[i1][i]=list_ns[TSD_vn[i1][i]];
}
//---------------
/* ---------------------------------------- */
// сканирование магистрали

int licp_sw=0;
int licp_addr;
int licp_fnd;
int flag_print_licp=0;
int licp_port=1;
//----------------------------

int ToutLicpScan = 30;
int licp_amax=10;  //QQQQ
int licp_crc_flag=1;
int licp_t_conf=0;

struct icp_mod ICP_MOD[5][icp_mod_max];
int  ICP_mod_fnd[5]={0,0,0,0,0};

//----------------------------
void f_look_ICP()
{
int i;
char buf_tmp[20];
switch(licp_sw)
 {  /* сканирование ICP slave контроллеров на магистрали */
   case 0: break;
   case 1:
          licp_addr=0;
          licp_fnd=0;
          licp_sw=2;
          LICP_Rqst.answ_com=f_result_Licp;
          LICP_Rqst.answ_flt=f_empty_ans_Licp;
          LICP_Rqst.timeout=ToutLicpScan;

   case 2:
      if(licp_addr>=licp_amax)
      { // сканирование закончено
         ICP_mod_fnd[licp_port]=licp_fnd;
         if(licp_fnd)
         {
            LICP_Rqst.answ_com=f_ans_Licp_cfg;
            LICP_Rqst.answ_flt=f_ans_Licp_Flt;
            licp_t_conf=0;

            LICP_Rqst.timeout=ToutLicpScan*5;
            licp_sw=3;
            if(flag_print_licp) puts("\n\r");
            break;
         }
         else
         {
           if(flag_print_licp)
           {
             printf("\n\r COM%d : устройства ICP не найдены\n\r",licp_port);
           }
           if(ff_serv==f_look_ICP) ff_serv=NULL;
           licp_sw=0;
           break;
         }
      }
      if( f_queue_chk(licp_port) && (LICP_Rqst.status == Req_OK) )
      {
       // послать команду "read name" по текущему адресу
           sprintf(buf_tmp,"$%02XM",licp_addr);
           f_prepare7000(buf_tmp,LICP_Rqst.CRC_flag);
           strcpy(LICP_Rqst.Cmd,buf_tmp);
           LICP_Rqst.cmd_lgth=strlen(LICP_Rqst.Cmd);
           LICP_Rqst.time_stamp=TimeStamp;
           f_queue_put(licp_port, &LICP_Rqst);
      }
      break;

   case 3: // опрос конфигурации найденных устройств
      if(licp_t_conf >= licp_fnd)
      {
           licp_sw=4;
           break;
      }
      _fmemset(&ICP_MOD[licp_port][licp_t_conf].TT,0xaa,sizeof(int)*3);
      if( f_queue_chk(licp_port) && (LICP_Rqst.status == Req_OK) )
      {
       // послать команду опроса конфигурации найденным устройствам
           sprintf(buf_tmp,"$%02X2",ICP_MOD[licp_port][licp_t_conf].addr);
           f_prepare7000(buf_tmp,LICP_Rqst.CRC_flag);
           strcpy(LICP_Rqst.Cmd,buf_tmp);
           LICP_Rqst.cmd_lgth=strlen(LICP_Rqst.Cmd);
           LICP_Rqst.time_stamp=TimeStamp;
           f_queue_put(licp_port, &LICP_Rqst);
      }
      break;

   case 4:

       if(flag_print_licp && licp_fnd)
       {
          printf("\n\r COM%d,найдены устройства ICP:",licp_port);
          f_mod_list();
       }
       if(ff_serv==f_look_ICP) ff_serv=NULL;
       licp_sw=0;
       break;
 }
 return;
}
//-------------------------------------------------
// структура запроса при сканировании магистрали
//-------------------------------------------------
struct COM_rqst LICP_Rqst={
0,                     //  состояние запроса
ffgets_com_ICP,        //  gets_com
f_result_Licp,         //  answ_com
f_empty_ans_Licp,      //  answ_flt
"SCAN bus",            //  name
0,                     //  n_dev
&Host,                 // *ICP_dd
0,                     //  текущая функция
50,                    //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
""                     //  com[]
};
/*----------------------------*/
void f_result_Licp(int ii)
{
/* заносит принятые данные в массив структур
    ICP_MOD[]
*/
 int i;
 long int count;
 if(licp_crc_flag==1)
    count=n_bcom[ii]-5;  // длина имени
 else
    count=n_bcom[ii]-3;  // длина имени

//в ответ на $00M принимается  !00MMIFCT41
 if(licp_crc_flag==0) goto m1;
 if(f_check_crc_ICP(cb_COM[ii]))
 {
m1:
  _fmemcpy( ICP_MOD[ii][licp_fnd].name,&cb_COM[ii][3],count);
  ICP_MOD[ii][licp_fnd].name[count]=0;

  cb_COM[ii][3]=0;
  sscanf(&cb_COM[ii][1],"%2x",&i);
  ICP_MOD[ii][licp_fnd].addr=i;
  ICP_MOD[ii][licp_fnd].addr0=licp_addr;
  ICP_MOD[ii][licp_fnd].port=ii;
  licp_fnd++;
 }
 if(licp_fnd == icp_mod_max)
  {
    licp_addr=licp_amax;
  }
  else
    licp_addr++;
 f_queue_free(ii,&LICP_Rqst);
 if(flag_print_licp) putch('x');
}
/*-------------------------------------------*/
void f_empty_ans_Licp(int ii)
{ // таймаут по ответу
 licp_addr++;
 f_queue_free(ii,&LICP_Rqst);
 if(flag_print_licp) putch('.');
}
/*-------------------------------------------*/
/*-------------------------------------------*/
void f_ans_Licp_cfg(int ii)
{
/* заносит принятые данные о конфигурации
   в ICP_MOD[]
*/
 char *result;
 int *dat;
 int i;

// в ответ на $002 приходит
//  !00 01 06 40  AC
 result=cb_COM[ii];
 if(licp_crc_flag==0) goto m1;
 if(f_check_crc_ICP(result))
 {
m1:
  sscanf(&result[1],"%2X",&i);
  if(((i != ICP_MOD[ii][licp_t_conf].addr)&& (ICP_MOD[ii][licp_t_conf].addr !=0) )||(*result != '!')) goto m_flt;

  dat=&ICP_MOD[ii][licp_t_conf].TT;
  sscanf(&result[3],"%2x%2x%2x",&dat[0],&dat[1],&dat[2]);
  ICP_MOD[ii][licp_t_conf].port=ii;
 }
m_flt:
 licp_t_conf++;
 f_queue_free(ii,&LICP_Rqst);
// if(flag_print_licp) putch('+');
}
/*-------------------------------------------*/
void f_ans_Licp_Flt(int ii)
{ // таймаут по ответу
 licp_t_conf++;
 f_queue_free(ii,&LICP_Rqst);
// if(flag_print_licp) putch('-');
}
//-------------------------------
void f_look_RTU()
{
int i,i2;
char buf_tmp[20];
switch(licp_sw)
 {  /* сканирование ICP slave контроллеров на магистрали */
   case 0: break;
   case 1:
          licp_addr=0;
          licp_fnd=0;
          licp_sw=2;
          LICP_Rqst_RTU.answ_com=f_result_Licp_RTU;
          LICP_Rqst_RTU.answ_flt=f_result_Licp_RTU;
          LICP_Rqst_RTU.timeout=ToutLicpScan;

   case 2:
      if(licp_addr>=licp_amax)
      { // сканирование закончено
         ICP_mod_fnd[licp_port]=licp_fnd;
         if(licp_fnd)
         {
            licp_t_conf=0;
            licp_sw=4;
            if(flag_print_licp) puts("\n\r");
            break;
         }
         else
         {
           if(flag_print_licp)
           {
             printf("\n\r COM%d : устройства RTU не найдены\n\r",licp_port);
           }
           if(ff_serv==f_look_RTU) ff_serv=NULL;
           licp_sw=0;
           break;
         }
      }
      if( f_queue_chk(licp_port) && (LICP_Rqst_RTU.status == Req_OK) )
      {
       // послать команду "читать регистр" по текущему адресу
            i2=6;
            buf_tmp[0]=licp_addr;
            buf_tmp[1]=3;
            buf_tmp[2]=0x00; //(ComSK_SV[ii]>>8)&0xff;
            buf_tmp[3]=0x01; //ComSK_SV[ii] & 0xff;
            buf_tmp[4]= 0x00;
            buf_tmp[5]= 0x01;

           f_prepareRTU(buf_tmp,&i2);
           _fmemcpy(LICP_Rqst_RTU.Cmd,buf_tmp,(long)i2);
           LICP_Rqst_RTU.cmd_lgth=i2;
           LICP_Rqst_RTU.time_stamp=TimeStamp;
           f_queue_put(licp_port, &LICP_Rqst_RTU) ;
      }
      break;


   case 4:

       if(flag_print_licp && licp_fnd)
       {
          printf("\n\r COM%d,найдены устройства RTU:",licp_port);
          f_mod_list();
       }
       if(ff_serv==f_look_RTU) ff_serv=NULL;
       licp_sw=0;
       break;
 }
 return;
}
//-------------------------------------------------
//-------------------------------
struct COM_rqst LICP_Rqst_RTU={
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_result_Licp_RTU,     //  answ_com
f_result_Licp_RTU,     //  answ_flt
"SCAN RTU",            //  name
0,                     //  n_dev
&Host,                 // *ICP_dd
0,                     //  текущая функция
50,                    //  timeout
0,                     //  time_stamp
6,                     //  com_lgth
1,                     //  CRC_flag
{01,03,00,01,00,01},                     //  com[]
};
/*----------------------------*/
void f_result_Licp_RTU(int ii)
{
/* заносит принятые данные в массив структур
    ICP_MOD[]
*/
 int i;
 long int count;
 count=n_bcom[ii];  // длина имени
 if(count==0)
 {
  if(flag_print_licp) putch('.');
  goto m_end;
 }
//в ответ на $00M принимается  !00MMIFCT41
 if(f_check_crc_RTU(cb_COM[ii],count))
 {
m1:
  ICP_MOD[ii][licp_fnd].addr=cb_COM[ii][0] & 0xff;
  sprintf(ICP_MOD[ii][licp_fnd].name,"RTU A%02X",cb_COM[ii][0] & 0xff);
  ICP_MOD[ii][licp_fnd].TT=0;
  ICP_MOD[ii][licp_fnd].FF=0;
  ICP_MOD[ii][licp_fnd].CC=f_get_nb(ComBaud[ii]);
  ICP_MOD[ii][licp_fnd].port=ii;
  licp_fnd++;
 if(flag_print_licp) putch('x');
 }
 else
  if(flag_print_licp) putch('?');

m_end:
 if(licp_fnd == icp_mod_max)
  {
    licp_addr=licp_amax;
  }
  else
    licp_addr++;
 f_queue_free(ii,&LICP_Rqst_RTU);
}
/*-------------------------------------------*/
//-------------------------------
void  f_print_que()
{
int i;
    struct COM_rqst *request;
    struct s_icp_dev *ICPl_DEV;
    struct icp_mod *ICPl_MOD;

      printf("\n\r Ports queue:");
      for(i=1;i<4;i++)
      {
        printf("\n\rCOM%d: ",i);
        printf(" busy_ptr=%d,empty_ptr=%d,last_out=%d",COM_que[i].busy_ptr,COM_que[i].empt_ptr,last_out[i]);
        request=COM_que[i].request[COM_que[i].empt_ptr];
        if(request != NULL)
          printf("\n\r   Last srv: %s,status %d",request->name,request->status);
        request=COM_que[i].request[COM_que[i].busy_ptr];
           if(request != NULL)
          printf("\n\r   Last put: %s,status %d",request->name,request->status);
      }
      printf("\n\r ICP device(s):");

 printf(
"\n\rName     Status Port Addr CRC Pool   Send  Success Tout_err CRC_err T_snd T_ans");

      for(i=0;i<icp_lst_max;i++)
      {
        ICPl_DEV=ICP_dd[i];
 printf(
  "\n\r%10s    %1d   %1d   %3d  %d  %d",ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr,ICPl_DEV->CRC_flag,ICPl_DEV->pool_time);

 printf("%8ld %8ld %6ld %6ld %6ld %6ld",ICPl_DEV->n_transaction,ICPl_DEV->n_success,ICPl_DEV->n_timeout_error,ICPl_DEV->n_CRC_error,
   ICPl_DEV->time_stamp_snd,ICPl_DEV->time_stamp_rcv);
      }
      printf("\n\r time %.3f sec",(float)(TimeStamp-TimeClear)/1000.);
/*
      GetTime(&hour,&min,&sec);
      printf("  %2d:%2d:%2d" ,hour,min,sec);
*/
}
//-------------------------------
void f_drv_list()
{ // показать список драйверов устройств
int i;
  struct s_icp_dev *ICPl_DEV;
  struct COM_rqst *request;

  printf("\n\rНомер   Имя       status  port addr CRC_flag pool,ms timeout,ms");
    for(i=0;i<icp_lst_max;i++)
    {
      ICPl_DEV=ICP_dd[i];
      request=ICPl_DEV->request;
      printf("\n\r%2d  %10s      %d      %d   %3d     %d",i+1,ICPl_DEV->name,ICPl_DEV->status,ICPl_DEV->port,ICPl_DEV->addr,ICPl_DEV->CRC_flag);
      printf("      %4ld    %4ld", ICPl_DEV->pool_time,request->timeout);
    }
//    printf("\n\r");
}
//-------------------------------
struct icp_mod *f_get_mod_str(int num)
{ // функция возвращает указатель на структуру модудя
  // с номером num . num = 0...
  //
  int i,i1,nn;
  struct icp_mod *ICPl_MOD;

  nn=num+1;
  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  if((i1==0)|| (nn>i1) )return NULL;

  for(i=1;i<4;i++)
  {
   if(nn<= ICP_mod_fnd[i])
    {
      i1=nn-1;
      break;
    }
   else nn-=ICP_mod_fnd[i];
  }
  ICPl_MOD=&ICP_MOD[i][i1];
  return ICPl_MOD;
}
//-------------------------------
void f_mod_list()
{ // показать список обнаруженных модулей
int i,i1,i2;
 // int ICP_mod_fnd[5];
  struct icp_mod *ICPl_MOD;

  i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
  if(i1==0) printf("  список пуст,используйте SCAN (SCANP)\n\r");
  else
  {
  printf("\n\rНомер    Имя      порт адрес скорость  TT  FF");
  i2=1;
    for(i=0;i<i1;i++)
    {
      ICPl_MOD=f_get_mod_str(i);
      if(ICPl_MOD==0) break;

      if(ICPl_MOD->addr0 != ICPl_MOD->addr)
       printf("\n\r%3d %10s      %d \(%02X\)%02X  %6ld",i2,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr0,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC]);
      else
       printf("\n\r%3d %10s      %d    %02X   %6ld",i2,ICPl_MOD->name,ICPl_MOD->port,ICPl_MOD->addr,baudrate_val[ICPl_MOD->CC]);

      printf("   %02X  %02X",ICPl_MOD->TT,ICPl_MOD->FF);
      i2++;
    }
      printf("\n\r");
  }
}
//-------------------------------
//-------------------------------
//-------------------------------
void  f_icp_hlp()
{
  puts("\n\r ICP modules commands:\n\r");
  puts(" $AAM - read module name\n\r");
  puts(" $AA2 - read module configuration\n\r");
  puts(" ~AAO(Name) - change module name\n\r");
  puts(" %AANNTTCCFF - change module configuration\n\r");
  puts(" $AA5VV - enable analog channels VV (for I7017)\n\r");
  puts(" $AA6 - read channel enable status (for I7017)\n\r");
}
int nn;
unsigned long int ee_nn;
unsigned long int ee_nn1;
//----------------------
union
{
char ch[4];
long int lng;
} *lng_chr;

//struct arch_str ar_str0_;
int f_intr()
{
  int i,i1,i2,i3,j,fn;
  long int i_l;
  char *ch_ptr;
  struct COM_rqst *request;
  struct s_icp_dev *ICPl_DEV;
  struct icp_mod *ICPl_MOD;
  char buf_tmp[50];
  char ch_tmp;
  int  hour,min,sec;
  struct arch_str *a_str;
  float ftmp;

union  { float f; unsigned long l; } o,o1;

        intrpr.i3=0;
        if(f_inw()==0)
        {
          intrpr.n_bcom=0;
          goto fin;
        }

//---------------------------------
        if ((intrpr.wrd[0]=='Q') || (intrpr.wrd[0]=='q'))
        {
            printf ("\n\r QQQ \n\r");
            return 1;
        }
//---------------------------------
        if  ((intrpr.wrd[0]=='C') &&(intrpr.wrd[1]=='M') )
        {   //"CM" 'CM' - Com Mode
         if( ((i=f_123(3)) >= 0 ) &&  (i< 5) )
         {
          i++;
          cm_baud  = ComBaud[i]   ;
          cm_lgth  = Com_lgth[i]  ;
          cm_parity= Com_parity[i];
          cm_stop  = Com_stop[i]  ;

          if((i1=f_dis_set(ds_cm,3,4)) >0 )
          {
//           printf("\n\r i= %d, %ld %d %d %d",i,cm_baud,cm_lgth,cm_parity,cm_stop   );
            if(f_get_nb(cm_baud) < 0  ) goto fin_e;

            ComBaud[i]    = cm_baud   ;
            Com_lgth[i]   = cm_lgth   ;
            Com_parity[i] = cm_parity ;
            Com_stop[i]   = cm_stop   ;

            RestoreCom(i);
            if( InstallCom(i,ComBaud[i],Com_lgth[i],Com_parity[i],Com_stop[i]) < 0 ) goto fin_e;
          }

          ShowCom(ComPortHost,Com_lgth[ComPortHost],ComBaud[ComPortHost]);
          goto fin;
         }
        }
//---------------------------------
        if  ((intrpr.wrd[0]=='D') &&(intrpr.wrd[1]=='R')&&(intrpr.wrd[2]=='V'))
        {   //'DRV'
         if( ((i=f_123(4)) >= 0 ) &&  (i< icp_lst_max ) )
         {
           ICPl_DEV = ICP_dd[i];
           request=ICPl_DEV->request;

           status    = ICPl_DEV->status    ;
           port      = ICPl_DEV->port      ;
           addr      = ICPl_DEV->addr      ;
           CRC_flag  = ICPl_DEV->CRC_flag  ;
           pool_time = ICPl_DEV->pool_time ;
           timeout    = request->timeout;
          if(f_dis_set(ds_dev,4,6) >= 0)
          {
           ICPl_DEV->status    = status    ;
           ICPl_DEV->port      = port      ;
           ICPl_DEV->addr      = addr      ;
           ICPl_DEV->CRC_flag  = CRC_flag  ;
           ICPl_DEV->pool_time = pool_time ;
           request->timeout= timeout;
          }
          goto fin;
         }
        }
//---------------------------------
        if  ((intrpr.wrd[0]=='M') &&(intrpr.wrd[1]=='O') && (intrpr.wrd[2]=='D'))
        {   //'MOD'
         i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
         if( ((i=f_123(4)) >= 0 ) &&  (i< i1 ) )
         {
           ICPl_MOD=f_get_mod_str(i);

           addr0  = ICPl_MOD->addr0;
           addr  = ICPl_MOD->addr;
           baud   = baudrate_val[ICPl_MOD->CC];
           TT_par = ICPl_MOD->TT ;
           FF_par = ICPl_MOD->FF ;

          if((i2=f_dis_set(ds_mod,4,4)) > 0)
          {
            i=f_get_nb(baud);
            if(i<0) goto fin_e;

            ICPl_MOD->addr =  addr  ;
            ICPl_MOD->TT   =  TT_par ;
            ICPl_MOD->CC   = i;
            ICPl_MOD->FF   =  FF_par ;
            if( f_queue_chk(ICPl_MOD->port ) )
            {
             // послать команду "set cfg" по старому адресу устройства
               sprintf(buf_tmp,"%c%02X%02X%02X%02X%02X",'%',addr0,ICPl_MOD->addr,ICPl_MOD->TT,ICPl_MOD->CC,ICPl_MOD->FF);
               f_prepare7000(buf_tmp,LICP_Rqst.CRC_flag);
               strcpy(Host_Rqst.Cmd,buf_tmp);
               Host_Rqst.cmd_lgth=strlen(Host_Rqst.Cmd);
               Host_Rqst.time_stamp=TimeStamp;
               f_queue_put(ICPl_MOD->port, &Host_Rqst);
               return 0;
            }
          }
          goto fin;
         }
        }
//---------------------------------
        if  ((intrpr.wrd[0]=='M') &&(intrpr.wrd[1]=='O')&&(intrpr.wrd[2]=='D')&&(intrpr.wrd[3]=='N'))
        {   //'MODN'
         i1=ICP_mod_fnd[1]+ICP_mod_fnd[2]+ICP_mod_fnd[3];
         if( ((i=f_123(5)) >= 0 ) &&  (i< i1 ) )
         {
           ICPl_MOD=f_get_mod_str(i);

           strcpy(buf_str,ICPl_MOD->name);

          if((i2=f_dis_set(&ds_modn,5,1)) > 0)
          {

           strcpy(ICPl_MOD->name,buf_str);
           if( f_queue_chk(ICPl_MOD->port ) )
            {
             // послать команду set name
               sprintf(buf_tmp,"~%02XO%s",ICPl_MOD->addr,ICPl_MOD->name);
               f_prepare7000(buf_tmp,LICP_Rqst.CRC_flag);
               strcpy(Host_Rqst.Cmd,buf_tmp);
               Host_Rqst.cmd_lgth=strlen(Host_Rqst.Cmd);
               Host_Rqst.time_stamp=TimeStamp;
               f_queue_put(ICPl_MOD->port, &Host_Rqst);
               return 0;
            }
          }
          else if(i2==0);
          else goto fin;

          goto fin;
         }
        }
//---------------------------------
        if  ((intrpr.wrd[0]=='C') &&(intrpr.wrd[1]=='O')&&(intrpr.wrd[2]=='M'))
        {   //'COM'
          if(f_dis_set(&ds_com,3,1) > 0)
          {
           if((EchoComN==4)||(EchoComN==0) )
           {
            EchoComN=0;
            goto fin;
           }
             ComPortEcho=EchoComN;
          }
          goto fin;
        }
//---------------------------------
     if  ((intrpr.wrd[0]=='S') &&(intrpr.wrd[1]=='C')&&(intrpr.wrd[2]=='A')&&(intrpr.wrd[3]=='N') &&(intrpr.wrd[4]=='P'))
   //    if (!strcmp(intrpr.wrd,"SCANP" ))
        {   //'SCANP'
          f_dis_set(ds_scan,5,4);
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"BR" ))
        {   //'BR' Baud Rate for COM1...COM4

          if((i1=f_dis_set(ds_br,2,4)) !=0 )
          {
            for(i=1;i<=i1;i++)
             if(f_get_nb(ComBaud[i]) < 0  ) goto fin_e;
            for(i=1;i<=i1;i++)
                SetBaudrate(i,ComBaud[i]);
          }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MD5" ))
        {   //'MD5'
          f_md5(0);
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"CP" ))
        {   //'CP' Com Protocol
          f_dis_set(ds_cp,2,3);
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"TRTU" ))
        {   //'TRTU' byte Timeout RTU
          f_dis_set(ds_trtu,4,3);
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"SCT" ))
        {   //'SCT'  Time delay for ServiceCom
          f_dis_set(ds_sct,3,3);
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"P" ))
        {   //'P ' - вывести измеренное время
          flag_prn ^= 1;
          printf(" %d",flag_prn);
          io_1=-1;
          goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"OEE" ))
        {   //'OEE' Send 2K EEP
         if(EE_MultiRead_L(0,2048,buf_eep)<0 ) goto fin_e;
         putch(0);
         i1 = 2048;
         i2 = 2048+2+4;
         putch(i2&0xff);
         putch((i2>>8)&0xff);
         putch('S');
         putch('E');
         putch('E');
         putch(0xd);
         putch(i1&0xff);
         putch((i1>>8)&0xff);

         for(i=0;i<i1;i++) putch(buf_eep[i]);

 /*      putch(0);
         i1 = 2048;
         putch(i1&0xff); putch((i1>>8)&0xff);
         for(i=0;i<i1;i++)
         {
          ch_tmp= EE_RandomRead(i>>8,i & 0xff);
          putch(ch_tmp);
         }
 */
         goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"SEE" ))
        {   //'SEE' store 2K EEP

         i1 = getch();
         i2 = getch();
         i1=(i1 & 0xff) | ((i2<<8)&0xff00);
         for(i=0;i<i1;i++)
           buf_eep[i]=getch();

  printf(" %d",i1);

 EE_WriteEnable();
   i2= EE_MultiWrite_L(0,2048,buf_eep);
 EE_WriteProtect();
        if(i2<0) goto fin_e;
         goto fin;
        }
//---------------------------------
       if (!strcmp(intrpr.wrd,"WE" ))
       {   //'WE'
        if(f_wrt_eee()<0)
        {
          f_wr_evt(evt_we_err);

          goto fin_e;
        }
        else
        {
          f_wr_evt(evt_we);
          if(flag_echo_host )
            printf(" %d",ee_members);
        }
        f_wr_cor();
        goto fin;
       }
//---------------------------------
       if (!strcmp(intrpr.wrd,"RE" ))
       {   //'RE'
     // if(f_chk_EEE_CRC()<0) goto fin_e;
        f_chk_EEE_CRC();
        if(f_rd_eee()<0)
        {
           f_wr_evt(evt_re_err);
           goto fin_e;
        }
        f_rd_cor();
        f_wr_evt(evt_re);
        goto fin;
       }
//---------------------------------
       if (!strcmp(intrpr.wrd,"VT" ))
       {   //'VT' Variable Transmit

         f_chk_EEE_CRC();// count  ee_lgth_byte
         i1 = ee_lgth_byte;
         i2 = ee_lgth_byte+2+3;

         putch(0);
         putch(i2&0xff); putch((i2>>8)&0xff);
         putch('V');  putch('L');  putch(0xd);
         putch(i1&0xff); putch((i1>>8)&0xff);

        Eeprom_summ=0;
        for(i=0,i1=0;EE_Dat[i].ptr!=0;i++)
        {
          i2=EE_Dat[i].l;
          ch_ptr=(char *)EE_Dat[i].ptr;
          for(j=0;j<i2;j++)
          {
            ch_tmp= *ch_ptr++;
            putch(ch_tmp);
 //         putch(*ch_ptr++);
            if(EE_Dat[i].ptr!= &Eeprom_summ)
//            Eeprom_summ +=buf_eep[i1];
//            Eeprom_summ +=((unsigned long)(buf_eep[i1])) & 0xffL;
              Eeprom_summ +=((unsigned long)(ch_tmp)) & 0xffL;

            i1++;
          }
        }
        goto fin;
       }
//---------------------------------
       if (!strcmp(intrpr.wrd,"VL" ))
       {   //'VL'  Variable Load
         i1 = getch();
         i2 = getch();
         i1= (i1 & 0xff) | ((i2<<8)&0xff00);
         ch_ptr=buf_eep;
         ee_nn1=0;
          for(i=0;(i<(i1-4)) && (i<max_buf_eep);i++)
          {
            ch_tmp=getch();
            *ch_ptr++ =ch_tmp;
            ee_nn1 +=((unsigned long)(ch_tmp)) & 0xff;
          }
          ch_ptr=(char *)&ee_nn;

        for(;(i<i1) && (i<max_buf_eep);i++)
        {
            ch_tmp=getch();
            *ch_ptr++ =ch_tmp;
        }
          if(ee_nn1 != ee_nn) goto fin_e;
          f_rd_eee();

          goto fin;
       }
//---------------------------------
   if (!strcmp(intrpr.wrd,"SCAN" ))
   {    //'SCAN'

    if(ComProt[ComPortEcho]==0)
    {
      licp_sw=1;
      licp_port=ComPortEcho;
      ff_serv=f_look_ICP;
      flag_print_licp=1;
      LICP_Rqst.timeout=ToutLicpScan;
      printf("\n\r Scanning ICP COM%d: tout %d ms, max addr %d,CRC_CHK=%d",ComPortEcho,ToutLicpScan,licp_amax,LICP_Rqst.CRC_flag);
      licp_crc_flag=LICP_Rqst.CRC_flag;
    }
    else
    {
      licp_sw=1;
      licp_port=ComPortEcho;
      ff_serv=f_look_RTU;
      flag_print_licp=1;
      LICP_Rqst_RTU.timeout=ToutLicpScan;
      printf("\n\r Scanning RTU COM%d: tout %d ms, max addr %d",ComPortEcho,ToutLicpScan,licp_amax);
    }
    goto fin;
   }
//---------------------------------
      if (!strcmp(intrpr.wrd,"SQ" ))
          {   // 'SQ '
           f_print_que();
           goto fin;
          }
//---------------------------------
      if (!strcmp(intrpr.wrd,"HELP" ))
          {   // 'HELP '
           f_icp_hlp() ;
           goto fin;
          }
//---------------------------------
   if (!strcmp(intrpr.wrd,"CQ" ))
          {
           printf("\n\r Queues are cleared");

    for(i=0;i<icp_lst_max;i++)
    {
      ICPl_DEV=ICP_dd[i];
      request=ICPl_DEV->request;
      request->status=0;
    }

           f_queue_clr(1);
           f_queue_clr(2);
           f_queue_clr(3);
           goto fin;
          }
//---------------------------------
   if (!strcmp(intrpr.wrd,"ECHO" ))
     //'ECHO'
          {
            f_dis_set(ds_echo,4,2);
           if(!flag_echo_host ) puts("\n\r");
            goto fin;
          }
//---------------------------------
   if (!strcmp(intrpr.wrd,"DRV" ))
          { // 'DRV' - drivers list
            f_drv_list();
            goto fin;
          }
//---------------------------------
   if (!strcmp(intrpr.wrd,"MOD" ))
          { // 'MOD' - modules list
            f_mod_list();
            goto fin;
          }
//---------------------------------
   if (!strcmp(intrpr.wrd,"WINS" ))
          { // 'WINS' - Winter-summer time
            f_dis_set(&ds_wins,4,1);
            goto fin;
          }
//---------------------------------
      if (!strcmp(intrpr.wrd,"ID" ))
        {   //'ID'
          f_dis_set(ds_id,2,3);
          goto fin;
        }
//---------------------------------
#if defined(ICP_7017C)
//---------------------------------
   if (!strcmp(intrpr.wrd,"ADCI" ))
          { //'ADCI'
            f_dis_set(ds_adc1,4,8);
            goto fin;
          }
   if (!strcmp(intrpr.wrd,"ADC"))
          { //'ADC'
            f_dis_set(ds_adc,3,8);
            goto fin;
          }
//---------------------------------
#endif
//---------------------------------
      if (!strcmp(intrpr.wrd,"DE" ))
        {   //'DE'

//         for(i=0;i<=icp_lst_max;i++)
//           printf(" %04x",ICP_error[i]);
           f_dis_set(ds_de,2,icp_lst_max+1);
         goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"CE" ))
        {   //'CE'
         f_cl_error();
         goto fin;
        }

#if defined(RTU_ComSK)
//---------------------------------
      if (!strcmp(intrpr.wrd,"SK" ))
        {   //'SK'
          f_dis_set(ds_sk,2,6);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RSK" ))
        {   //'RSK'
          sk_reg_q=1;
          if(f_dis_set(ds_rsk,3,1)>= 0)
          { //sk_reg_n = адрес+1

             buf_tmp[0]=ComSK[0].addr;

             buf_tmp[1]=3;
             buf_tmp[2]=((sk_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(sk_reg_n-1)  & 0xff;
             buf_tmp[4]=(sk_reg_q>>8) & 0xff;
             buf_tmp[5]=sk_reg_q & 0xff;
             Host_Rqst_sk.function=RD_INT;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(ComSK[0].port, &Host_Rqst_sk)) goto fin_e;

          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WSK" ))
        {   //'WSK'
        if(intrpr.bfcom[intrpr.i3]==0) goto fin_e;

          sk_reg_q=1;
          if((i1=f_dis_set(ds_rsk,3,2)) == 2)
          { //sk_reg_n = адрес+1
             buf_tmp[0]=ComSK[0].addr;
             buf_tmp[1]=6;
             buf_tmp[2]=((sk_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(sk_reg_n-1)  & 0xff;
             buf_tmp[4]=(sk_reg_q>>8) & 0xff;
             buf_tmp[5]=sk_reg_q & 0xff;
             Host_Rqst_sk.function=WR_INT;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
           /*
             printf("\n\r");
             for(i=0;i<i1;i++)
             {
               printf(" %02X",buf_tmp[i] & 0xff);
             }
             printf("\n\r");
            */
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(ComSK[0].port, &Host_Rqst_sk)) goto fin_e;

          }
          else goto fin_e;
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"SKWD" ))
        {   //'SKWD'
          f_dis_set(ds_skwd,4,4);
          goto fin;
        }

#endif  // if defined(RTU_ComSK)
//---------------------------------
#if defined(RTU_Delta)
//---------------------------------
      if (!strcmp(intrpr.wrd,"DLT" ))
        {   //'DLT'
          f_dis_set(ds_dlt,3,7);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DLTN" ))
        {   //'DLTN'
          f_dis_set(ds_dltn,4,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RDL" ))
        {   //'RDL'
          sk_reg_q=1;
          if(f_dis_set(ds_rdlt,3,1)>= 0)
          { //sk_reg_n = адрес+1
             sk_reg_n=dlt_reg_n;

             buf_tmp[0]=Delta[0].addr;

             buf_tmp[1]=3;
             buf_tmp[2]=((sk_reg_n)>>8) & 0xff;
             buf_tmp[3]=(sk_reg_n)  & 0xff;
             buf_tmp[4]=(sk_reg_q>>8) & 0xff;
             buf_tmp[5]=sk_reg_q & 0xff;
             Host_Rqst_sk.function=RD_INT;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(Delta[0].port, &Host_Rqst_sk)) goto fin_e;

          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WDL" ))
        {   //'WDL'
        if(intrpr.bfcom[intrpr.i3]==0) goto fin_e;

          dlt_reg_q=1;
          if((i1=f_dis_set(ds_rdlt,3,2)) == 2)
          { //sk_reg_n = адрес+1
             sk_reg_n=dlt_reg_n;
             sk_reg_q=dlt_reg_q;

             buf_tmp[0]=Delta[0].addr;
             buf_tmp[1]=6;
             buf_tmp[2]=((sk_reg_n)>>8) & 0xff;
             buf_tmp[3]=(sk_reg_n)  & 0xff;
             buf_tmp[4]=(sk_reg_q>>8) & 0xff;
             buf_tmp[5]=sk_reg_q & 0xff;
             Host_Rqst_sk.function=WR_INT;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
           /*
             printf("\n\r");
             for(i=0;i<i1;i++)
             {
               printf(" %02X",buf_tmp[i] & 0xff);
             }
             printf("\n\r");
            */
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(Delta[0].port, &Host_Rqst_sk)) goto fin_e;

          }
          else goto fin_e;
          return 0;
        }
//---------------------------------

#endif  // if defined(RTU_Delta)
//---------------------------------
//---------------------------------
//---------------------------------
//---------   MVD   ---------------
//---------------------------------
      if (!strcmp(intrpr.wrd,"RMI" ))
        {   //'RMI' Read MVD Integer
          mvd_reg_q=1;  // количество читаемых регистров
          j=1;          // количество вводимых параметров
          i2=RD_INT;
          fn=3;
          goto m_rml;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RML" ))
        {   //'RML' Read MVD Long
          i2=RD_LONG;
          j=1;
          fn=3;
          mvd_reg_q=2;
 m_rml:
          if(f_dis_set(ds_rmvd,3,j)>= 0)
          { //sk_reg_n = адрес+1
             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=fn;
             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;
             buf_tmp[4]=(mvd_reg_q>>8) & 0xff;
             buf_tmp[5]=mvd_reg_q & 0xff;
             Host_Rqst_sk.function=i2;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RMF" ))
        {   //'RML' Read MVD Float
          i2=RD_FLOAT;
          mvd_reg_q=2;
          fn=3;
          j=1;
          goto m_rml;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RMS" ))
        {   //'RMS' Read MVD String
          i2=RD_STRING;
          mvd_reg_q=2;
          j=2;
          fn=3;
          goto m_rml;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RMC" ))
        {   //'RMC' Read MVD Coil
          i2=RD_COIL;
          j=2;
          mvd_reg_q=1;
          fn=1;
          goto m_rml;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WMC" ))
        {   //'WMC' Write MVD Coil
          if(f_dis_set(ds_rmvd,3,2)> 0)
          { //sk_reg_n = адрес+1
             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=5;
             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;
             if(mvd_reg_q != 0)
               buf_tmp[4]= 0xff;
             else
               buf_tmp[4]= 0;
             buf_tmp[5]= 0;

             Host_Rqst_sk.function=WR_COIL;

             i1=6;
       //    for(i=0;i<i1;i++)
       //     printf(" %02X",buf_tmp[i]&0xff);

             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;

        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WMI" ))
        {   //'WMI' Write MVD Integer
          if(f_dis_set(ds_rmvd,3,2)> 0)
          { //sk_reg_n = адрес+1
             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=6;
             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;
             buf_tmp[4]=(mvd_reg_q>>8) & 0xff;
             buf_tmp[5]=mvd_reg_q & 0xff;
             Host_Rqst_sk.function=WR_INT;

             i1=6;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;

        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WML" ))
        {   //'WML' Write MVD Long
          i2=WR_LONG;
          j=2;
//          fn=16;
          mvd_reg_q=2;
          if(f_dis_set(ds_wmvd,3,j)> 0)
          { //sk_reg_n = адрес+1

             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=16;

             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;

             buf_tmp[4]=(mvd_reg_q>>8) & 0xff;         // количество регистров
             buf_tmp[5]=mvd_reg_q & 0xff;

             buf_tmp[6]=(mvd_reg_q+mvd_reg_q) & 0xff;  // количество байт

             buf_tmp[7]=(wmvd_reg_v >> 24) & 0xff;         // количество регистров
             buf_tmp[8]=(wmvd_reg_v >> 16) & 0xff;         // количество регистров
             buf_tmp[9]=(wmvd_reg_v >> 8)  & 0xff;         // количество регистров
             buf_tmp[10]=wmvd_reg_v & 0xff;    // количество регистров

             Host_Rqst_sk.function=i2;

             i1=11;
             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WMS" ))
        {   //'WMS' Write MVD String

          if(f_dis_set(ds_wmvds,3,3) > 0)
          { //sk_reg_n = адрес+1
           puts("\n\r***");
           puts(str_mvd);
           puts("***\n\r");
             j=strlen(str_mvd);
             i1=((j+1)>>1);
             printf("\n\r Length=%d  ==",j);
             if(i1>mvd_reg_q)
               mvd_reg_q=i1;

             i2=mvd_reg_q+mvd_reg_q;
             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=16;

             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;

             buf_tmp[4]=(mvd_reg_q>>8) & 0xff;         // количество регистров
             buf_tmp[5]=mvd_reg_q & 0xff;

             buf_tmp[6]=(mvd_reg_q+mvd_reg_q) & 0xff;  // количество байт
             i1=7;

             for(i1=7,i=0;i<i2;i1++,i++)
             {
              if((str_mvd[i] != '_')&& (i<j) )
                buf_tmp[i1]=str_mvd[i];
              else
                buf_tmp[i1]=' ';
             }
             Host_Rqst_sk.function=WR_STRING;

             printf("\n\r i1=%d===",i1);

             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"WMF" ))
        {   //'WMF' Write MVD Float
          if(f_dis_set(ds_wmvf,3,2)> 0)
          { //sk_reg_n = адрес+1

             buf_tmp[0]=MVD[nn_mvd].addr;
             buf_tmp[1]=16;

             buf_tmp[2]=((mvd_reg_n-1)>>8) & 0xff;
             buf_tmp[3]=(mvd_reg_n-1)  & 0xff;

             buf_tmp[4]=0;         // количество регистров
             buf_tmp[5]=2;

             buf_tmp[6]=4;  // количество байт
    // code 1:

             buf_tmp[7]=(mvd.l >> 8 ) & 0xff;
             buf_tmp[8]=(mvd.l >> 0 ) & 0xff;
             buf_tmp[9]=(mvd.l >> 24)  & 0xff;
             buf_tmp[10]=(mvd.l >> 16) & 0xff;

             Host_Rqst_sk.function=WR_FLOAT;

             i1=11;

        //   for(i=0;i<i1;i++)
        //    printf(" %02X",buf_tmp[i]&0xff);

             f_prepareRTU(buf_tmp,&i1);
             _fmemcpy(Host_Rqst_sk.Cmd,buf_tmp,(long int)i1);
             Host_Rqst_sk.cmd_lgth=i1;
             Host_Rqst_sk.time_stamp=TimeStamp;
             if( f_queue_put(MVD[0].port, &Host_Rqst_sk)) goto fin_e;
          }
          return 0;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MDN" ))
        {   //'MDN'
          f_dis_set(ds_mdn,3,2);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MDP" ))
        {   //'MDP'
          f_dis_set(&ds_mdp,3,1);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MDI" ))
        {   //'MDI'
          f_dis_set(&ds_mdi,3,1);
          goto fin;
        }
//---------------------------------
//---------------------------------
//---------------------------------
      if (!strcmp(intrpr.wrd,"IO" ))
        {   //'IO'
          f_dis_set(ds_io,2,4);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"IOCH" ))
        {   //'IOCH'
          f_dis_set(ds_ioch,4,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"IO1" ))
        {   //'IO'
          f_dis_set(ds_io1,3,6);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"IO2" ))
        {   //'IO2'
          f_dis_set(ds_io2,3,6);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"IOD1" ))
        {   //'IOD1'
          f_dis_set(ds_iod1,4,2);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"IOD2" ))
        {   //'IOD2'
          f_dis_set(ds_iod2,4,2);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DPD" ))
        {   //'DPD' Display Process Data
          f_dis_set(ds_dpd,3,12);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DPP" ))
        {   //'DPP' Display Process Pressures
          f_dis_set(ds_dpp,3,4);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVC" ))
        {   //'MVC' MVD Check
          f_dis_set(ds_mvd,3,8);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVT" ))
        {   //'MVT' MVD Times
          f_dis_set(ds_mvt,3,2);
          goto fin;
        }
//---------------------------------
//---------------------------------
      if ( (!strcmp(intrpr.wrd,"MVP" )) || (!strcmp(intrpr.wrd,"MVP1" ))  )
        {   //'MVP' Display MVD parameters
          ii_MVD=0;
          nn_mvd=0;
m_mvp:
          ff_serv=f_MVD_1;
          sw_mvd_1=0;
          tm_mvd=TimeStamp;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVP2" ))
        {   //'MVP2' Display MVD2 parameters
          ii_MVD=1;
          nn_mvd=1;
          goto m_mvp;
        }
//---------------------------------
//---------------------------------
      if ( (!strcmp(intrpr.wrd,"MVD" ) ) ||  (!strcmp(intrpr.wrd,"MVD1" ) )        )
        {   //'MVD' 'MVD1' Display MVD process Data

          ii_MVD=0;
          nn_mvd=0;
m_mvd:
          HTemp=-300;HDens=-1.;
          ff_serv=f_MVD_2;
          sw_mvd_1=0;
          tm_mvd=TimeStamp;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVD2" ))
        {   //'MVD' Display MVD process Data
          ii_MVD=1;
          nn_mvd=1;
          goto m_mvd;
        }
//---------------------------------
      if ( (!strcmp(intrpr.wrd,"MVE" ))  || (!strcmp(intrpr.wrd,"MVE1" ))  )
        {   //'MVE' Display MVD Error registers

          ii_MVD=0;
          nn_mvd=0;
m_mve:
          ff_serv=f_MVD_3;
          sw_mvd_1=0;
          tm_mvd=TimeStamp;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVE2" ))
        {   //'MVE2' Display MVD2 Error registers
          ii_MVD=1;
          nn_mvd=1;
          goto m_mve;
        }
//---------------------------------
      if( (!strcmp(intrpr.wrd,"MVZ" ))|| (!strcmp(intrpr.wrd,"MVZ1" ))  )
        {   //'MVZ'
          if(f_reset_zer_MVD(0) == 0) goto fin_e;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MVZ2" ))
        {   //'MVZ2'
          if(f_reset_zer_MVD(1) == 0) goto fin_e;
          goto fin;
        }
//---------------------------------
//---------------------------------
      if (!strcmp(intrpr.wrd,"TSD" ))
        {   //'TSD' TSD decimal point set
          if(f_dis_set(ds_tsd,3,4))
          {
          TSD_val_c[0][0]=-44;
          TSD_val_c[0][1]=-44;
          TSD_val_c[0][2]=-44;
          }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"VOL" ))
        {   //'VOL' VOL
         if( f_dis_set(ds_vol,3,1) > 0)
         {
          dose_dlvr=vol_f;
          volume_f=vol_f;

         SetDisplayPage(23);
         f_clr_scr_MMI();
          puts(" Отпуск жидкой фазы. ");
          MmiGotoxy(0,0);
          if(dose_dlvr != vBIG_P)
             MmiPrintf(" Delivery  %g kg",dose_dlvr);
          else
             MmiPrintf(" Delivery");

         MmiGotoxy(0,6);       MmiPuts("ESC - stop");

         sw_dlv_liq=1;
         sw_mmi=193;
        }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"ST" ))
        {   //'ST' Stop filling

          fl_GO=0;
          fl_EQ=0;
//        OUT_VAR=0;
          OUT_VAR=OUT8;
          sw_dlv_liq=-1;
          f_wr_evt(evt_est_f+flag_rcv);
          f_prn_begin();
          sw_mmi=0;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"CLV" ))
        {   //'CLV'
         f_dis_set(ds_clv,3,6);
         goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"CLVR" ))
        {   //'CLVR'
         f_dis_set(ds_clvr,4,2);
         goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"VNN" ))
        {   //'VNN'
         if( f_dis_set(ds_vnn,3,3))
               f_init_TSD();

         goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"CTRL" ))
        {   //'CTRL'
          f_dis_set(ds_ctrl,4,4);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DSC" ))
        {   //'DSC'

    //    if(flow_mom > 0) dsc_tmp=(vol2-vol_f)/flow_mom;
    //    else dsc_tmp=0;
          f_dis_set(ds_dsc,3,5);
          goto fin;
        }
//---------------------------------
#if(SIM0 != 0)
      if (!strcmp(intrpr.wrd,"FLOW" ))
        {   //'FLOW'

          f_dis_set(ds_flow,4,2);
          goto fin;
        }


#endif
//---------------------------------
      if (!strcmp(intrpr.wrd,"KA" ))
        {   //'KA'
          f_dis_set(ds_ka,2,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MKO" ))
        {   //'MKO'
          f_dis_set(ds_mko,3,8);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MKS" ))
        {   //'MKI'
          if(f_dis_set(ds_mks,3,4) >0 )
             f_init_mki();

          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MKI" ))
        {   //'MKI'
          if(f_dis_set(ds_mki,3,4) >0 )
             f_init_mki();
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"MKA" ))
        {   //'MKA'
          f_dis_set(ds_mka,3,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"NA" ))
        {   //'NA'
          ftmp_na[0]=analog_scale[0]*NA_scale;
          ftmp_na[1]=analog_scale[1]*NA_scale;
          ftmp_na[2]=analog_scale[2]*NA_scale;
          if(f_dis_set(ds_na,2,3)>0)
          {
           analog_scale[0]=ftmp_na[0]/NA_scale;
           analog_scale[1]=ftmp_na[1]/NA_scale;
           analog_scale[2]=ftmp_na[2]/NA_scale;
          }
          goto fin;
        }
//---------------------------------
//---------------------------------
      if (!strcmp(intrpr.wrd,"NO" ))
        {   //'NO'
          f_dis_set(ds_no,2,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"FLE" ))
        {   //'FLE'
         if( f_dis_set(&ds_fle,3,1))
          {
           seg=fle;
           if( FlashErase(seg) != 0) goto fin_e;
          }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"FLD" ))
        {   //'FLD'
        seg=0x8000;
        offset=0;
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0x9000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xA000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xB000;
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xC000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xD000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xE000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

        seg=0xF000;
        Flash_ptr=(unsigned long int *) _MK_FP_(seg,offset);
        printf("\n\r %04X:%04X %08lX",seg,offset,*Flash_ptr);

          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"PDN" ))
        {   //'PDN'
          pdn_tmp= f_get_max_n_arch();
          f_dis_set(&ds_pdn,3,1);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"JRN" ))
        {   //'JRN'
         pdn_tmp= f_get_max_n_arch();
//       i2=sizeof(ar_str0_);
         i2=sizeof(struct arch_str);

         i_l = (long int)pdn_tmp * (long int)i2;
//       printf("\r\n i2 = %d, Lgth=%ld\r\n ",i2,i_l);

         i_l+=sizeof(fl_id)+sizeof(fl_id)+sizeof(chr_id)+sizeof(sw_ver);
         putch(1);

         putch4(i_l);

         for(i1=0;i1<20;i1++)
          putch(sw_ver[i1]);

         o1.f=fl_id;
         putch4( o1.l);
         o1.f=fl_id1;
         putch4( o1.l);

         for(i1=0;i1<20;i1++)
          putch(chr_id[i1]);

         for(i1=0;i1<pdn_tmp;i1++)
         {

           if((i1%10)== 0)  f_cycle();

           if( (a_str= f_get_astr(i1)) == NULL )
           {
            a_str=f_get_astr(0);
           }
           ch_ptr=(char *)a_str;
           for(j=0;j<i2;j++)
           {
            ch_tmp= *ch_ptr++;
            putch(ch_tmp);
           }

           WaitTransmitOver(ComPortHost);

         }

          goto fin;
        }
//---------------------------------
//---------------------------------
      if (!strcmp(intrpr.wrd,"PDA" ))
        {   //'PDA'
         i1= f_get_max_n_arch();
         n_end=i1;
         if( f_dis_set(ds_pda,3,2))
          {
           if(n_end > i1)
           {
            n_end=i1;
           }
           if(n_beg>n_end) n_beg=n_end;

           for(i=n_beg-1;i<n_end;i++)
             f_print_a_str(i);
          }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"PDL" ))
        {   //'PDL'
         i1= f_get_max_n_arch();
         n_lst=i1;
         if( f_dis_set(&ds_pdl,3,1))
          {
     m_pdl:
           if(n_lst > i1)
           {
            n_lst=i1;
           }
           for(i=i1-n_lst;i<i1;i++)
             f_print_a_str(i);
          }
         else
         {
           n_lst=20;
           goto m_pdl;
         }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"FLS" ))
        {   //'FLS' флаг включения протокола pmp1
         if( f_dis_set(ds_fls,3,2))
          if(fl_wr_eee)
          {

            f_wr_cor();
            if(f_wrt_eee()<0) goto fin_e;
          }
         goto fin;
        }
//---------------------------------
/*
      if (!strcmp(intrpr.wrd,"PMP" ))
        {   //'PMP'
          f_dis_set(ds_pmp,3,4);
          goto fin;
        }
*/
//---------------------------------
      if (!strcmp(intrpr.wrd,"NS" ))
        {   //'NS'
          if(f_dis_set(ds_ns,2,8) >0)
               f_ns_count();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"CB" ))
        {   //'CB'
          uk_buf=0;
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"VAR" ))
        {   //'VAR'

          if( f_dis_set(ds_var,3,1)<0) goto fin;

          ds_var[1].op= list_ns[v_num_var];
          ds_var[1].type= list_ns_type[v_num_var];

          intrpr.wdl=intrpr.i3;
          f_dis_set(&ds_var[1],intrpr.i3,1 );
          goto fin;

        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"VARC" ))
        {   //'VARC'

          strcpy(intrpr.bfcom,"VARC");
          intrpr.i3=4;
          intrpr.wdl=intrpr.i3;
          f_dis_set(ds_var,intrpr.i3,1 );

          ds_var[1].op= list_ns[v_num_var];
          ds_var[1].type= list_ns_type[v_num_var];
          printf("  \r\n");
          i_l=TimeStamp;
          while(kbhit()==0)
          {
            f_cycle0();
          intrpr.i3=4;
          intrpr.wdl=intrpr.i3;

           if( f_timer( i_l, 100L ))
           {
            f_dis_set(&ds_var[1],intrpr.i3,1 );
            printf(" \r");
            i_l=TimeStamp;
           }
          }
          getch();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"O" ))
         /* - 'O '-  команда Передать наверх буфер записи ---- */
          {
            if(fl_trace_loop == 0)
            {
              putch(0);
              j= uk_buf;
              i_l=(long int)j * 4L;
              putch2(i_l);

              for(i2=0;i2<5;i2++)
              {
                if(f_ns[i2] == 0.) break;
              }
            // i2 - количество переменных
              for(i=0,i3=0;i<j;i++,i3++)
                {
                if((i%50)== 0)  f_cycle();
                 if(i3>=i2) i3=0;
                 o.l= buf_xyz[i];
                 switch(list_ns_type[f_ns[i3]]  )
                 {
                  case T_FLOAT:
                    o1.f=o.f;
                    break;
                  case T_INT_L:
                  case T_HEX_L:
                    o1.f=(float)o.l;
                    break;
                  case T_INT:
                  case T_HEX:
                  case T_HX2:
                  case T_HX4:
                    o1.f=(float) *( (int *)(&o.l));
                    break;
                 }
                 putch4( o1.l);
                }
              goto fin;
            }
            else
            {
              fl_trace=1;
              putch(0);
              for(i2=0;i2<5;i2++)
              {
                if(f_ns[i2] == 0) break;
              }
              j= (int)((dim_xyz-6)/i2) * i2;
              i_l=(long int)j * 4L;
              putch2(i_l);
              for(i=uk_buf,i1=0,i3=0;i1<j;i1++,i++,i3++)
                {
                if((i1%50)== 0)  f_cycle();
                   if(i>=j) i=0;
                   if(i3>=i2) i3=0;
                 o.l= buf_xyz[i];
                 switch(list_ns_type[f_ns[i3]]  )
                 {
                  case T_FLOAT:
                    o1.f=o.f;
                    break;
                  case T_INT_L:
                    o1.f=(float)o.l;
                    break;
                  case T_INT:
                    o1.f=(float) *( (int *)(&o.l));
                    break;
                 }
                 putch4( o1.l);
                }
              fl_trace=0;
              goto fin;
            }
          }
/*----------------------------------------------*/
//---------------------------------
      if (!strcmp(intrpr.wrd,"CMP" ))
        {   //"CMP" 'CM' - Com Mode for Pomp

          cm_baud  = ComBaudPmp1   ;
          cm_lgth  = Com_lgthPmp1  ;
          cm_parity= Com_parityPmp1;
          cm_stop  = Com_stopPmp1  ;

          if((i1=f_dis_set(ds_cm,3,4)) >0 )
          {
           if(f_get_nb(cm_baud) < 0  ) goto fin_e;

           ComBaudPmp1    = cm_baud   ;
           Com_lgthPmp1   = cm_lgth   ;
           Com_parityPmp1 = cm_parity ;
           Com_stopPmp1   = cm_stop   ;

  //       RestoreCom(ComPortPmp1);
  //       if( InstallCom(ComPortPmp1,cm_baud,cm_lgth,cm_parity,cm_stop) < 0 ) goto fin_e;

          }
          goto fin;

        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"2" ))
        {   //'2 '
          f_print_dd();
          flg_prn_reg=1;
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"RES" ))
        {   //'RES'

      free( buf_xyz );
          _asm cli
          _asm hlt
//        (*(void (*)())adr_strt)();
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DM" ))
        {   //'DM'

          f_dis_set(&ds_dm,2,1);
          mem_ptr=(unsigned char *)p_mem;
          for(i=0;i<64;i++)
          {
            if((i%8)==0)
              printf("\n\r%08lX  ",(unsigned long int)(p_mem+i));
            printf("  %02x",mem_ptr[i] &0xff);
          }
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"ZP" ))
        {   //'ZP'
          f_dis_set(ds_zp,2,2);
          goto fin;
        }
 //---------------------------------
      if (!strcmp(intrpr.wrd,"MVDN" ))
        {   //'MVDN'

          f_dis_set(&ds_mvdn,4,1);
          goto fin;
        }
//---------------------------------

      if (!strcmp(intrpr.wrd,"VER" ))
        {   //'VER'
         printf(" %s",sw_ver);
         goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"DNS" ))
        {   //'DNS'
          if(f_dis_set(ds_dns,3,4) >0)
          {
            dns_cmps=f_get_composition(dns_dns,dns_temp);
            dns_dns20=f_get_Dns(dns_cmps,(float)20.);
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"MMU" ))
        {   //'MMU' permissible values of density
         if( f_dis_set(ds_mmu,3,3))
           if(sw_mmi==0) f_prn_begin();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"MODF" ))
        {   //'MODF' режим наполнения
          if(f_dis_set(&ds_modf,4,1)>0)
          {
            if(ModeFill==F_Mass)
            {
             un_mmi1=4;
             un_mmi2=5;
             un_mmi3=6;
            }
            else
            {
             un_mmi1=1;
             un_mmi2=2;
             un_mmi3=3;
            }
           if(sw_mmi==0) f_prn_begin();
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DNT" ))
        {   //'DNT'
          f_dis_set(ds_dnt,3,3);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"PART" ))
        {   //'PART'
          f_dis_set(ds_part,4,3);
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"PARP" ))
        {   //'PARP'
          if(f_dis_set(ds_parp,4,4)>0)
             f_prep_bern();
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"PARD" ))
        {   //'PARD' Control values of density
          f_dis_set(ds_pard,4,3);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"STG" ))
        {   //'STG' stages
          f_dis_set(ds_stg,3,3);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DP" ) )
        {   //'DP' Demand Pressure
          ftmp_p[0] = ((float)P_dem) / K_F_INT;
          if(f_dis_set(ds_dp,2,3)>0)
          {
           P_dem = (long int)(ftmp_p[0] * K_F_INT);
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DD" ) )
        {   //'DD' Demand Difference
          ftmp_p[0] = ((float)P_dem_c) / K_F_INT;
          if(f_dis_set(ds_dd,2,3)>0)
          {
           P_dem_c = (long int)(ftmp_p[0] * K_F_INT);
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"AA" ) )
        {   //'AA'
    printf("\n\r &AA = %8lx\n\r",(long int)&l_state[0]);
    printf(" AA = %8lx\n\r",l_state[0]);
    printf(" BB = %ld\n\r",l_state[1]);
    printf(" CC = %ld\n\r",l_state[2]);
    printf(" DD = %ld\n\r",l_state[3]);
    printf(" AA_ = %8lx\n\r",l_state[l_stt+0]);
    printf(" BB_ = %ld\n\r",l_state[l_stt+1]);
    printf(" CC_ = %ld\n\r",l_state[l_stt+2]);
    printf(" DD_ = %ld\n\r",l_state[l_stt+3]);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DI" ) )
        {   //'DI' Demand I
          ftmp_p[0] = ((float)YiN) / k_div;
          if(f_dis_set(ds_di,2,3)>0)
          {
            YiN=  ftmp_p[0]*k_div;
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"KP" ))
        {   //'KP' PID parameters
          if(f_dis_set(ds_kp,2,3)>0)
                     f_count_cf();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"KDP" ))
        {   //'KDP' PID parameters
          if(f_dis_set(ds_kdp,3,3)>0)
                     f_count_cf();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"KIP" ))
        {   //'KIP' PID parameters
          if(f_dis_set(ds_kip,3,3)>0)
                     f_count_cf();
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"FDN" ))
        {   //'FDN'
          f_dis_set(ds_fdn,3,4);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"FDF" ))
        {   //'FDF'
          f_dis_set(ds_fdf,3,4);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"LP" ))
        {   //'LP' Limits of Pressure regulator

          ftmp_p[0]=(float)(maxP_errP) /K_F_INT;
          ftmp_p[1]=(float)(maxP_errM) /K_F_INT;
          ftmp_p[2]=(float)LIM_P /k_div;
          ftmp_p[3]=(float)LIM_M /k_div;

          if(f_dis_set(ds_lp,2,5)>0)
          {
           maxP_errP = ftmp_p[0] * K_F_INT;
           maxP_errM = ftmp_p[1] * K_F_INT;
           LIM_P     = ftmp_p[2] * k_div;
           LIM_M     = ftmp_p[3] * k_div;
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"LDP" ))
        {   //'LDP' Limits of Difference Pressure regulator

          ftmp_p[0]=(float)(maxPd_errP) /K_F_INT;
          ftmp_p[1]=(float)(maxPd_errM) /K_F_INT;
          ftmp_p[2]=(float)LIMd_P /(k_div * K_F_INT);
          ftmp_p[3]=(float)LIMd_M /(k_div * K_F_INT);

          if(f_dis_set(ds_ldp,3,4)>0)
          {
           maxPd_errP = ftmp_p[0] * K_F_INT;
           maxPd_errM = ftmp_p[1] * K_F_INT;
           LIMd_P     = ftmp_p[2] * k_div * K_F_INT;
           LIMd_M     = ftmp_p[3] * k_div * K_F_INT;
          }
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"LIP" ))
        {   //'LIP' Limits of I  regulator

          ftmp_p[0]=(float)(maxPi_errP);
          ftmp_p[1]=(float)(maxPi_errM);
          ftmp_p[2]=(float)LIMi_P /k_div ;
          ftmp_p[3]=(float)LIMi_M /k_div ;

          if(f_dis_set(ds_ldp,3,4)>0)
          {
           maxPi_errP = ftmp_p[0] ;
           maxPi_errM = ftmp_p[1];
           LIMi_P     = ftmp_p[2] * k_div ;
           LIMi_M     = ftmp_p[3] * k_div ;
          }
          goto fin;
        }
//------------------------------------------
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DNF" ))
        {   //'DNF' factors
          f_dis_set(ds_dnf,3,2);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DN" ))
        {   //'DN' dencity
          f_dis_set(&ds_dn,2,1);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"DTC" ))
        {   //'DTC' Density,Temperature,Composition,Density exec.
          f_dis_set(ds_dtc,3,5);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"PASS" ))
        {   //'PASS'Password
          f_dis_set(&ds_pass,4,1);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"MVH" ))
        {   //'MVH' Help по MVD
 printf("\n\r WMC 04 1 -- Reset all inventories");
 printf("\n\r WMC 56 1 -- Reset mass total");
 printf("\n\r WMC 57 1 -- Reset volume total");
 printf("\n\r MVZ(2)  -- Zeroing (WMC 05 1)");
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"EX" ))
        {   //'PASS'Password
          f_dis_set(ds_ex,2,2);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"FLCH" ))
        {   //'FLCH'FLow CHeck
          f_dis_set(ds_flch,4,5);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"VCH" ))
        {   //'VCH' Voltage  CHeck
          f_dis_set(ds_vch,3,5);
          goto fin;
        }
//------------------------------------------
      if (!strcmp(intrpr.wrd,"REP" ))
        {   //'REP'
          f_rep();
          goto fin;
        }
//---------------------------------
      if (!strcmp(intrpr.wrd,"D" ))
          {
//           printf(" %s %s %s",TsdBuf[0][0],TsdBuf[0][1],TsdBuf[0][2]);

           for(i=0;i<5;i++)
            if(f_ns[i]) PrintOp(f_ns[i]);
            else break;
           goto fin;
          }
//---------------------------------
//---------------------------------
        if (intrpr.wrd[0]=='?')
          {
           f_menu();
           goto fin;
          }
//---------------------------------
fin_e:
         if(( EchoComN==0)||( EchoComN==4))
         {
          if(flag_echo_host )
           printf("?\n\r>");
           return 0;
         }
         else
         { // посылка неопознанной команды в COM (ComPortEcho)
      //   ComPortEcho=EchoComN;

          if(ComProt[ComPortEcho]== ICP)
          {
           if( f_queue_chk(ComPortEcho) && (Host_Rqst.status == Req_OK) )
           {
              { // стать в очередь доступа к COM

                f_prepare7000(intrpr.bfcom,LICP_Rqst.CRC_flag);
                strcpy(Host_Rqst.Cmd,intrpr.bfcom);
                Host_Rqst.timeout= ToutLicpScan;
                Host_Rqst.cmd_lgth=strlen(Host_Rqst.Cmd);
                Host_Rqst.time_stamp=TimeStamp;
                f_queue_put(ComPortEcho, &Host_Rqst);
              }
           }
           else printf(" -- no place in queue COM%d-- \n\r",ComPortEcho);
          }
          else if(ComProt[ComPortEcho]== RTU)
          {
           if( f_queue_chk(ComPortEcho) && (Host_Rqst_rtu.status == Req_OK) )
           {
              { // стать в очередь доступа к COM

                if( (i1=f_chg_toRTU(intrpr.bfcom)) > 0 )
                {
                  f_prepareRTU(intrpr.bfcom,&i1);
                  _fmemcpy(Host_Rqst_rtu.Cmd,intrpr.bfcom,(long int)i1);
                  Host_Rqst_rtu.cmd_lgth=i1;
                  Host_Rqst_rtu.time_stamp=TimeStamp;
                  f_queue_put(ComPortEcho, &Host_Rqst_rtu);
                }
                else goto fin_ee;
              }
           }
           else
           {
             printf(" -- no place in queue COM%d-- \n\r",ComPortEcho);
             goto fin_ee;
           }
          }
          else if(ComProt[ComPortEcho]== 2)
          {  // передача в канал без добавления контрольной суммы
           if( f_queue_chk(ComPortEcho) && (Host_Rqst_rtu.status == Req_OK) )
           {
              { // стать в очередь доступа к COM

                if( (i1=f_chg_toRTU(intrpr.bfcom)) > 0 )
                {
           //     f_prepareRTU(intrpr.bfcom,&i1);
                  _fmemcpy(Host_Rqst_rtu.Cmd,intrpr.bfcom,(long int)i1);
                  Host_Rqst_rtu.cmd_lgth=i1;
                  Host_Rqst_rtu.time_stamp=TimeStamp;
                  f_queue_put(ComPortEcho, &Host_Rqst_rtu);
                }
                else goto fin_e;
              }
           }
           else
           {
             printf(" -- no place in queue COM%d-- \n\r",ComPortEcho);
             goto fin_e;
           }

          }
         }
         return 0;
fin_ee:
 if(flag_echo_host )
   putch('?');
fin:
 if(flag_echo_host )
         if(( EchoComN==0)||( EchoComN==4))
          printf("\n\r>");

         else
          printf("\n\rCOM%d>",ComPortEcho);
          return 0;

     }
/* ---------------------------------------- */
void f_rep()
{

 struct s_icp_dev *ICPl_DEV;
int i,i2=0;
int itmp;

 for(i=0;i<=icp_lst_max;i++)
   if(ICP_error[i])
   {
    i2 |=ICP_error[i];
    ICPl_DEV=ICP_dd[i];
  if(i != icp_lst_max)
   printf("\r\nОшибка в драйвере %9s:",ICPl_DEV->name );
  else
   printf("\r\nОшибка системы СУГ: ");

    itmp=ICP_error[i];
  if(i != icp_lst_max)
  {
    if(itmp & RD_ERR)
      printf("\r\nОшибка чтения устройства");
    if(itmp & WR_ERR)
      printf("\r\nОшибка записи в устройство");
    if(itmp & WD_ERR)
      printf("\r\nОшибка Watch Dog");
    if(itmp & Drive_ERR)
      printf("\r\nОшибка в устройстве,E%02X", (unsigned int) ((itmp>>8) & 0xff) );
  }
  else //(i == icp_lst_max)
  {
    if(itmp & EEE_CRC_error)
       printf("\r\nОшибка CRC EEPROM процессора");
    if(itmp & Flash_erase_error )
       printf("\r\nОшибка стирания FLASH");
    if(itmp & Flash_wr_error  )
       printf("\r\nОшибка записи во FLASH");
    if(itmp & No_gas_error  )
       printf("\r\nРасходомер не заполнен СУГ");
    if(itmp & No_Z_mass_err )
       printf("\r\nРасходомер не обнулил массу/объем");
    if(itmp & No_F_dat_err )
       printf("\n\rНет обновл.данных для журнала");
    if(itmp & exm_err )
       printf("\r\nНедолив больше допустимого");
    if(itmp & exp_err )
       printf("\r\nПерелив больше допустимого");
    if(itmp & Gun_off )
       printf("\r\nНасос отключен при отпуске");
    if(itmp & WD_pmlan )
       printf("\r\nСторожевой таймер PUMALAN");
    if(itmp & No_flow )
       printf("\nПоток прекратился");
    if(itmp & ES_off )
       printf("\nНажата аварийная кнопка (ES) при отпуске/приеме");
    if(itmp & UZA_off )
       printf("\nНет сигнала УЗА при отпуске/приеме");
    if(itmp & MVD_cfg )
       printf("\nОшибка конфигурирования расходомера");
    if((itmp & MotNotStop )==MotNotStop)
       printf("\nОшибка привода насоса при торможении");
//  if((itmp & DLT_off ) == DLT_off)
//     printf("\nОстанов привода насоса при отпуске");
    if((itmp & VLT_off ) == VLT_off)
       printf("\n АКБ разряжена ниже %5.2fV",v_lvl2);
    if( (itmp & Flow_big) == Flow_big )
       printf("\nОбрыв рукава.Скорость>допустимой.");
    if((itmp & N380_off)== N380_off )
       printf(" !No supply 380V ");
  }

   }
   if(i2==0)
       printf("\r\n Ошибок нет");

       if(sw_mmi==193)
       {
          if(dose_dlvr != vBIG_P)
             printf("\n\r Отпуск дозы СУГ %g кг",dose_dlvr);
          else
             printf("\n\r Отпуск СУГ без дозировки");
       }
       else if(sw_mmi==203)
       {
          if(dose_dlvr != vBIG_P)
             printf("\n\r Прием  дозы СУГ %g кг",dose_dlvr);
          else
             printf("\n\r Прием  СУГ без дозировки");
       }
   printf("\r\n  sw_mmi=%d,sw_dlv_liq=%d ",sw_mmi,sw_dlv_liq);
   printf("\r\n flag_rcv = %d, fl_GO_rcv = %d",flag_rcv,fl_GO_rcv );
   printf("\r\n stage_max = %d,ff_serv_N=%8x ",stage_max,(int)ff_serv_N );
   printf("\r\n MVD_fl[0]=%d,MVD_fl[1]=%d",MVD_fl[0],MVD_fl[1] );
   printf("\r\n dV_ctrl=%f",dV_ctrl);
   printf("\r\n VolT_int=%f",VolT_int);
   printf("\r\n k_volr=%f",k_volr);
   printf("\r\n Mas2r=%f",Mas2r);
   printf("\r\n flag_O1=%d,flag_O3=%d",flag_O1,flag_O3 );
   printf("\r\n flag_O1=%d,flag_O3=%d",flag_O1,flag_O3 );
   printf("\r\n dose_A=%f",dose_A );
   printf("\r\n TimeStampc=%ld,tt_vol2rc=%ld ",TimeStampc,tt_vol2rc);


}
/* ---------------------------------------- */

char *list_mnu[]={
//char list_mnu[90][82]={
 "\n\rPDL - вывод последних p1 событий ",
/*======================
 "\n\rVOL - отпуск дозы, старт с отпуска жидкой фазы ",
 "\n\rST  - останов отпуска",
 "\n\rSWT - времена отпуска,выравн.,приема.,выравн.,сек.",
 "\n\rMKO - номера вых.7060:p1-блш.кл,p2-мал.кл,p3-насос,p4-пар.цист,p5-пар.вн.",
 "\n\rMKS,MKI - номера входов,флаги инверсии: p1-Ав.кн.,p2-УЗА",
 "\n\rCTRL - 0-тестовый режим,p2-время задержки прохождения данных из MVD,мс",
 "\n\rKA - p1 - подстройка по объему(0...1)",
 "\n\r     p2 - подстройка по времени срабатывания клапана (0...1)",
 "\n\r     p3 - время задержки между выкл.клапана и записью отчета",
 "\n\rCLV -p1-оставшаяся масса при выкл.клапана 1,л",
 "\n\r     p2-оставшаяся масса при выкл.клапана 2,л",
 "\n\r     p3-время срабатывания клапана 1, мс ",
 "\n\r     p4-время срабатывания клапана 2, мс ",
 "\n\r     p5-время начала запрещения второстеп.опроса, мс ",
 "\n\r     p6-длительность запрета второстеп.опроса, мс ",
 "\n\rDSC   показания массы в момент выключения клапана",
 "\n\r     p1 - первичные данные,   p2 - экстраполированное значение",
 "\n\r     p3 - значение об.расхода,p4 - знач.коррекции по массе,кг",


 "\n\r     p5 - знач.коррекции по времени,мс ",
 "\n\rDNC   параметры управления клапаном 1 в процессе отпуска ",
 "\n\r     p1 - k_Den_Off-скорость уменьшения плотности - для выкл.клап1, кг/м3/с",
 "\n\r     p2 - k_Den_On-зона стабильности плотности - для вкл.клап1, кг/м3/с",
 "\n\r     p3 - время задержки вкл.клап1 после начала отпуска,мс",
 "\n\r     p4 - время задержки вкл.клап2 после начала отпуска,мс",
 "\n\r     p5 - время задержка выкл.насоса после отпуска,мс",
 "\n\r     p6 - миним.время выкл. клап1 при выкл.в процессе отпуска,мс",
 "\n\r     p7 - миним.время вкл.  клап1 до выкл.в процессе отпуска,мс",
 "\n\rDNF   текущие значения управления по плотности ",
 "\n\r     p1 -скорость изменения плотности, кг/м3/с",
 "\n\r     p2 -маска к клапану 1",
 "\n\rDTC   параметры среды в момент старта и конца наполнения ",
 "\n\r     p1 - плотность,кг/м3",
 "\n\r     p2 - температура,C",
 "\n\r     p3 - содержание пропана, 0...1.0",
 "\n\r     p4 - плотность приведенная (результирующая),кг/м3",
 "\n\r     p5 - температура приведения (результирующая),C",
 "\n\rMVT - время Init MVD, задержка до записи в журнал диагностики,ms",
 printf("\n\rFLCH - параметры контроля переполнения");
 printf("\n\r     p1 - значение расхода для останова,кг");
 printf("\n\r     p2 - значение отпуска для начала контроля останова потока,кг");
 printf("\n\r     p3 - время измерения расхода,тик,1 тик=t опроса MVD");
 printf("\n\r     p4 - время отсутствия контроля после включения кл.2,тик");

 "\n\rCMn - параметры COM портов(n= 1...4): скор,длина,четн,стоп бит",
 "\n\rCP -  тип протокола COM1..3, 0 - ICP,1 - RTU,2 - двоичн",

 "\n\rTRTU - таймаут ожидания байта RTU,ms",
 "\n\rSCT - время тишины после приема для COM,ms",
 "\n\rSCANP - параметры сканирования каналов ",
 "\n\rSCAN - автопоиск подключенных ICP/RTU устройств",
 "\n\rMOD - список обнаруженных ICP устройств",
 "\n\rMODn - изменение параметров обнаруженного устройства номер n",
 "\n\rMODNn - изменение имени обнаруженного устройства номер n",
 "\n\rDRV - список драйверов устройств",
 "\n\rDRVn - изменение параметров драйвера номер n",
 "\n\rCOM - режим терминального обмена с каналом COM1..3,0 - выход из режима ",
 "\n\rSQ  - состояние очередей и статистика COM1...COM3",
 "\n\rCQ  - очистка очередей COM1...COM3",
 "\n\rRSK - чтение регистра привода SK n",
 "\n\rWSK - запись регистра привода SK n",
 "\n\rWMI,WMF,WML,WMC  - запись в MVD регистра Int,Float,Long,Coil",
 "\n\rRMI,RMF,RML,RMC  - чтение из MVD регистра Int,Float,Long,Coil",
 "\n\rRMS - чтение из MVD строки",
 "\n\rMVZ - обнуление MVD , MVH - Help по MVD",
 "\n\rADC(1) - индикация состояния аналоговых входов",
 "\n\rECHO - эхо вкл (1) / выкл (0)",
 "\n\rHELP - Help по командам ICP",
 "\n\rDE - отобразить регистры ошибок",

 "\n\rCE - очистить ошибки",
 "\n\rWE - сохранить параметры в EEPROM",
 "\n\rRE - читать параметры из EEPROM",
 "\n\rMMU - единицы отображаемые на MMI 0...6",
 "\n\rVNN - номера отображаемых переменных на TSD",
 "\n\rTSD- p1-p3 количество знаков после запятой для TSD,p4 - период обновл.",
 "\n\rNS - номера переменных,записываемых в буфер:",
 "\n\r 1 - Объем, 2 - сумма, 3 - цена, 4 - плотность,5-объем экстрап.",
 "\n\r 6 - сумма экстрап., 7 - отпуск идеальн,8-сумма идеальн., 9 - масса общ.",
 "\n\r 10 - время,мс, 11 - дискр выходы, 12 - дискр.входы",
 "\n\r 13 - скорость изменения плотности, кг/м3/с,14 - масса инвент.",
 "\n\r 15 - объем из массы и плотности,л",
 "\n\rIO - отобразить состояние входов-выходов",
 "\n\rD  - отобразить состояние TSD",
=======================*/
 "\n\rQ - выход ",
"",
};

void   f_menu()
{
int i;
 for(i=0;list_mnu[i][0]!=0;i++)
 {
  puts(list_mnu[i]);
  if(((i%22) == 0)&& (i !=0)  )
  {
    printf("\n\r-- more --");
    while(kbhit()==0) f_cycle0();
    if(getch()== 0xd) return;
  }
 }

}
//-------------------------------
void putch2(long int i1 )
{
  putch(i1&0xff); putch((i1>>8)&0xff);
}
//-------------------------------
void putch4(long int i1 )
{
  putch(i1&0xff);
  putch((i1>>8)&0xff);
  putch((i1>>16)&0xff);
  putch((i1>>24)&0xff);
}
//-------------------------------
void f_init_mki()
{
  INP_inv=0;
  if(mski_inp1 != 0) INP_inv|=msk_int[num_in1];
  if(mski_inp2 != 0) INP_inv|=msk_int[num_in2];
  if(mski_inp3 != 0) INP_inv|=msk_int[num_in3];
  if(mski_inp4 != 0) INP_inv|=msk_int[num_in4];
/*
  if(mski_inp5 != 0) INP_inv|=msk_int[num_in5];
  if(mski_inp6 != 0) INP_inv|=msk_int[num_in6];
  if(mski_inp7 != 0) INP_inv|=msk_int[num_in7];
  if(mski_inp8 != 0) INP_inv|=msk_int[num_in8];
*/
// INP_MSK_OK = ES_IN | UZA_IN | LVL_IN | TRAP_IN | CONS_IN ;

}
//-------------------------------
