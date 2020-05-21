

// клапан малый
#define LTLC msk_int[num_out2]

// клапан большой
#define MEDC msk_int[num_out1]

//   насос
#define PUMP msk_int[num_out3]

//   ПФ
#define GAS1 msk_int[num_out4]

// питание
// OUT8

#define UZA msk_int[num_in4]
#define E_S msk_int[num_in1]

    // индекс MVD в ICP_error[]
#define MVD1  2
#define MVD2  3

#define ErrMVD1  ICP_error[MVD1]
#define ErrMVD2  ICP_error[MVD2]

#define RCV_FLG      0x100
#define UZA_E    2
#define STOP_E   5

#define Stage0  0
#define Stage1  2
#define Stage2  4
#define Stage3  6
#define Stage4  8


#define  T_prb_plus_ltl  cl0_delay_off
#define  T_prb_plus_big  cl1_delay_off

extern unsigned int OUT_VAR;  // состояние дискретных выходов
extern unsigned int INP_VAR;  // состояние дискретных входов
extern unsigned int INP_VAR_c;  // состояние дискретных входов
extern unsigned int OUT_VAR_c;  // состояние дискретных выходов

extern int analog_num[];
extern float analog_scale[];
extern float analog_offset[];


#define RCV_FLG      0x100
#define CLP0 msk_int[num_out7]
#define PUMP msk_int[num_out3]

#define GAS2 msk_int[num_out5]
#define LIQ2 msk_int[num_out6]


#define Out_on(IntMsk)  OUT_VAR |= IntMsk
#define Out_off(IntMsk)  OUT_VAR &= ~IntMsk

#define  T_Mot_Stop (15000L)

extern int fl_GO;
extern int fl_EQ;      // флаг выравнивания давления через MVD
extern int flagS_ES;   // признак останова по нажатию ES
extern int flagS_UZA;  // признак останова по отсутствию UZA
extern int flag_dlv_fst;
extern int flag_prn_mass;
extern int flag_rcv_fst;

extern int sw_dlv_liq;
extern int sw_dlv_gas;
extern int sw_rcv_liq;
extern int sw_rcv_gas;
extern float dose_rcv,dose_dlvr;

extern int key__1;
extern int flag_continue;
extern int flag_rcv;

void f_sens();
int f_rcv_dlv_liq(int key);
int f_dlv_liq(int key);
int f_rcv_liq(int key);
void f_stop_cnt_eq();
void f_stop_EQ();
void f_stop_EQn();
int f_need_EQ_dlv();
int f_need_EQ_rcv();
int f_need_LIQ_dlv();
int f_need_LIQ_rcv();

extern long int time_com_cl    ;
extern long int time_com_cl_off;
extern long int time_cnt_cl_off;
extern long int time_gas_cl_on ;
extern long int time_gas_cl_off;

extern long int time_EQ_rcv;
extern long int time_EQ_dlv;
extern long int time_LIQ_rcv;
extern long int time_LIQ_dlv;

extern int flagS_DLT;

extern unsigned int M_PRB[];
extern long int time_pfm[];

extern int stage_rl;
extern int stage_max;
extern int stage_c;
extern long int time_stage_ch;
extern int flag_st_wt;


void f_prb_plus();
void f_prb_minus();

extern char list_avt[][31];

extern long int time_prb_plus;
extern long int time_prb_minus;

extern long int Tim_prb_plus;
extern long int Tim_prb_minus;

extern int BegStage;

extern long int time_antd;
extern long int Tim_antd;

extern int flag_v2;

extern int flag_nstg;
extern long int time_stg_ctrl;
extern long int time_stg_ctrl0;
extern long int Tim_stg_ctrl0;
extern long int Tim_stg_ctrl;

void  f_chk_stg();
void  f_chk_volt();

extern float Fl_perm;

extern float v_lvl1,v_lvl2;
extern long int Tim_volt;
extern long int Tim_volt_mes;

extern float volt_dc_cmp;
extern int flagS_VLT;

extern long int time_t_snd;

extern int Flag_check;

extern int sw_pov;
int f_pov(int key);

extern unsigned int INP_inv;
extern unsigned int INP_VARi;

extern unsigned int Out_en;
extern unsigned int Out_en_r;

extern int flagS_ES;
extern int flagS_UZA;
extern int flagE_UZA;
extern int Flag_massR;

extern int fl_GO_rcv;

extern int flag_AC; // 1 - использовать насос Авто Цистерны

void f_dens_r();

extern float dV_ctrl;
extern float dose_A;

extern long int TimeStampc,tt_vol2rc;

extern int Out_en_pmp;
extern int flag_off;
extern int flag_uu;

