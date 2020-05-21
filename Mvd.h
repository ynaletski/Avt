

    //
    // SIM0  1  -- ࠧ�襭�� ࠡ��� (��� �⫠���) ��� ��室����
    // SIM0  0  -- �㤥� �뤠������ �訡�� �� ���� ���᪠   if(MVD[ii].status == 0)
    //

#define   SIM0  0

#define   R_MVD  PressLvl_on1

#define   ReduceDens  1
#define   ReducePress 2

// value factor for tube r=1mm

#define   ConstBern  (0.015635985)

#define max_fl_ch     64
#define max_fl_ch_m1  63

#define max_MVD 2

#define f_MVD_tim 1000

extern float  TimeMVD_Init;
extern float  TimeMVD_evt ;

#define OUT1 msk_int[num_out1]
#define OUT2 msk_int[num_out2]
#define OUT3 msk_int[num_out3]
#define OUT4 msk_int[num_out4]
#define OUT5 msk_int[num_out5]
#define OUT6 msk_int[num_out6]
#define OUT7 msk_int[num_out7]
#define OUT8 msk_int[num_out8]

#define INP1 msk_int[num_in1]
#define INP2 msk_int[num_in2]

#define F_Vol       1
#define F_Vol_Dens  2
#define F_Mass      3

float f_get_float( char *buf, int cod);
void f_MVD_1();
void f_MVD_2();
void f_MVD_3();

char *f_get_unit(int code);

#define ToutAnsMVD_rtu 100

#define MVD_max_out_err 5
#define MVD_max_inp_err 5
#define MVD_max_t_err 3

void f_MVD(int ii);
void f_MVD_rd(int ii);
void f_init_MVD(int ii);

int f_reset_VolT();
int f_reset_zer_MVD(int ii);

extern struct s_icp_dev MVD[];
extern struct COM_rqst MVD_Rqst[];

extern int MVD_fn[];     // ॣ���� �㭪権 �ࠩ���
extern int MVD_fl[];

#define MVD_RD_I   1
#define MVD_RD_L   2
#define MVD_RD_F   3
#define MVD_RD_S   4
#define MVD_RD_C   5
#define MVD_RD_P   8
#define MVD_WR_I   16
#define MVD_WR_L   17
#define MVD_WR_F   18
#define MVD_WR_C   19

#define F_PROGRESS  20
#define F_FAULT     21

#define n_coil_b 8
#define n_char_b 50

struct s_MVD_dev
{
unsigned int r_addr; // address of MODBUS register
int n;            // number of data - for read coils and ascii
int type;         // data type
int i;            // int,coil value for write
int exc;          // exception
long int  l;      // long
float f;          // float

float FlowM;          // float
float FlowV;          // float
float MassI;          // float
float MassT;          // float
float VolI;          // float
float VolT;          // float
float VolTd;          // float
float Temp;          // float
float Dens;          // float
float Press;         // float
float Compos;       // float
float PressG;       // float
float PressB;       // float
float PressD;       // float
float PressGN;      // float
float Volt_A;        // float
float Volt_DC;       // float

char c[n_coil_b]; // coil(s) value(s) read from MVD
char a[n_char_b]; // ascii
int reg_err;
};

extern int sw_mvd_1;
extern long int tm_mvd;
extern int unit_codes[];
extern char *unit_lst[];
extern char *err_F425[];

extern int flag_mvd_fst[];
void  f_ctrl_v1();

extern float CL_val[];
extern float CL_valR[];

extern int t_ctrl;
void  f_prep_int_v2();
float  f_int_v2();
void  f_ctrl_v2();

extern float VolT_int  ;
extern float summ_v_int;

extern int fl_take_temp;

extern float CL_T1;
extern float CL_T2;
extern float CL_T3;
extern long int CL_T4;

void f_stop_cnt();
void f_enable_cnt();
int f_MVD_WR(int ii,int fn,int addr,int i_val,long int l_val,float f_val);
void f_MVD_rd_t(int ii);
void f_gun();

extern float vol_mom,vol_mom0,flow_mom;

extern long int t_mvd_cor;

extern float VolT_id;
extern float summ_v_id;

extern int flag_pool;
extern int flag_O1;


extern int num_out1,num_out2;
extern int num_out3,num_out4;
extern int num_out5,num_out6;
extern int num_out7,num_out8;

extern int num_in1,num_in2;
extern int num_in3,num_in4;

extern float vol2,k_vol;
extern long int tt_vol1;
extern long int tt_vol2;

#define mErr   0
#define mVolT  1
#define mDens  2
//#define mFlowM 3
#define mSlot  3
#define mMassT 4
#define mTemp  5
//#define mFlowV 5
#define mVolI  6
#define mMassI 7

extern int flag_mvd_ton[];
extern long int tm_mvd_p;
extern int flag_nal;
extern void (*ff_serv_N)();

extern int  fl_VI, fl_MI;

extern int mski_inp1;
extern int mski_inp2;
extern int mski_inp3;
extern int mski_inp4;

extern struct s_MVD_dev s_MVD[];
extern long int tim_MVD_delay;

extern int mode_mvd;

extern int sw_MMI_cur; // ��砫쭠� ��ப� �� ��ᯫ�� MMI
extern int sw_MMI_lim;
extern int sw_mvd_m1;
void f_MVD_M1();
void f_sim_MVD();
void  f_prep_int_dens();
void  f_prep_int_Mass();

extern int flag_fst_gun;

extern int i_dens;
void f_density();
float f_get_composition(float Dens,float Temp);
float f_get_Dns(float Compos,float Temp);
float f_get_dens();
void f_get_dens_c();
unsigned int f_get_int( char *buf);
void  f_prep_int_MassF();

void  f_flow_chk();
extern int fl_rd_err;


extern long int TimDensOn;

extern long int cl1_delayR_off;
extern long int cl2_delayR_off;
extern long int Out3_delayR_off;
extern float k_Den_Off;
extern float k_Den_On;
extern float Den2,k_Den;

extern float Dens0;
extern float propan[];
extern float butan[];

extern float PropanP[];
extern float ButanP[];


extern float PermPlus;
extern float PermMinus;
extern int flag_20C;
extern float Temperature;
extern float Temperature1;
extern float Density;
extern float Composition;

extern float t20c;
extern float v_Proc;
extern float K_unit; // ��ॢ���� �� �/�3 � ��/�3
extern float HTemp,HDens,HCompos;

extern int ModeFill;
extern int igun_1;

extern int flag_flch;
extern long int beg_flch;

extern int   time_flch;
extern float val_flch;
extern float val_flch2;
extern float val0_flch;

extern long int time_beg_fill;
extern int TimeBegFlch;

extern int MVD_t_rslt[];
void f_get_pressDT(float Dens,float Temp);

extern int ModeReduce;

extern int   ModeReduce   ;

extern float PressLvl_on1 ;
extern float PressLvl_off1;
extern float PressLvl_on2 ;
extern float PressLvl_off2;

extern int flag_gas;
extern int flag_O0;

extern float    CL_T0        ;
extern float    CL_val0      ;
extern long int cl0_delay_off;
extern float    k_Den0_Off   ;
extern float    k_Den0_On    ;
extern float    PressLvl_on0 ;
extern float    PressLvl_off0;

extern long int TimDensWt0  ;
extern long int TimDensWt1  ;

extern unsigned int Out_en;
extern long int t_prep_MVD;

extern float  fl_chp[];
extern int io_1;
extern int flag_O3;
void f_prep_bern();

extern int  MVD_t_err[];
extern int ii_MVD;

extern float Cut_Vol[];
extern float Cut_Mass[];


extern float Mas2r,k_Masr;
extern long int tt_Mas1r;
extern long int tt_Mas2r;

extern float vol2r,k_volr;
extern long int tt_vol1r;
extern long int tt_vol2r;

void f_prep_int_rcv();
float  f_int_v2r();

extern float Sim_FlowM[];





