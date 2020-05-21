//-------------

#define Beg_temp (-50)

float PermPlus = 8;
float PermMinus= 8;
float t20c     =20.;
float v_Proc   =50.;
int   flag_20C =0;
//float K_unit   =1000.; // ��ॢ���� �� �/�3 � ��/�3

float Temp_kor=8.5;
float Comp_kor=1.0;

float Density=0;
float Temperature=0;
float Temperature1=0;
float Composition=0;
//----------------------------
float f_get_dens()
{// �����頥� �ਢ������� � 20C ���祭�� ���⭮��, �᫨ flag_20C != 0
 // ��� -1. �� �訡��

 //  s_MVD[0].Dens - ���祭�� ���⭮��
 //  s_MVD[0].Temp - ���祭�� ⥬�������
 float ftmp;
 if(flag_20C == 1)
 {
  Temperature=s_MVD[0].Temp;
  Density=s_MVD[0].Dens;
  ftmp=f_get_composition(s_MVD[0].Dens,Temperature);
  if(ftmp<= (-PermMinus)) return -1; // ���⭮��� ᬥ� ����� ���⭮�� ��⠭�
  if(ftmp>= PermPlus) return -1;             // ���⭮��� ᬥ� ����� ���⭮�� �ய���

// � ftmp ������⢮ �ய��� � ᬥ� 0...1.0
  Composition=ftmp;
  Temperature1=t20c;
  ftmp=f_get_Dns(ftmp,t20c);
// printf("f_get_Dns() = %f",ftmp);
  return ftmp;
 }
 else //if(flag_20C == 0)
 {
   Temperature=s_MVD[0].Temp;
   Temperature1=Temperature;
   ftmp=s_MVD[0].Dens;
   Density = ftmp;

   ftmp=f_get_composition(ftmp,Temperature);
   if(ftmp<= (-PermMinus)) return -1; // ���⭮��� ᬥ� ����� ���⭮�� ��⠭�
   if(ftmp>= PermPlus) return -1;             // ���⭮��� ᬥ� ����� ���⭮�� �ய���

   Composition=ftmp;
   return s_MVD[0].Dens;
 }
}
//------------------------------------
void f_get_dens_c()
{// ������ � Dens0  �ਢ������� � ⥪�饩 ⥬������ ���祭�� ���⭮��, �᫨ flag_20C == 2

 //  s_MVD[0].Dens - ���祭�� ���⭮��
 //  s_MVD[0].Temp - ���祭�� ⥬�������
 float ftmp;
 if(flag_20C == 2)
 {
  if((s_MVD[0].Temp>=-50) && (s_MVD[0].Temp<=50))
  {
   Temperature1=s_MVD[0].Temp;
   ftmp=f_get_Dns(Composition,Temperature1);
   Dens0 = ftmp;
  }
 }
}
//------------------------------------

float f_get_composition(float Dens,float Temp)
{
int itmp,itmp1;
float r_propan,r_butan,ftmp;
if((Temp > 50) || (Temp< -50)) return -1;

  if( Temp == 50.)
  {
   r_propan=propan[100];
   r_butan=butan[100];
  }
  else
  {
    itmp=Temp-(float)Beg_temp;
    itmp1=itmp+1;
    ftmp=Temp-(float)Beg_temp-(float)itmp;
    r_propan=(propan[itmp1]-propan[itmp]) * ftmp + propan[itmp];
    r_butan =(butan[itmp1] -butan[itmp] ) * ftmp + butan[itmp];

//  printf("\r\n itmp=%d,ftmp=%.3f,r_prop=%.3f,r_but=%.3f",itmp,ftmp,r_propan,r_butan);
  }

//   ������⢮ �ய��� � ᬥ� 0...1.0
  return (r_butan-Dens)/(r_butan-r_propan);
}
//-------------
float f_get_Dns(float Compos,float Temp)
{
int itmp,itmp1;
float r_propan,r_butan,ftmp;
if((Temp > 50) || (Temp< -50)) return -1;
//if((Compos > 1.0) || (Compos< 0)) return -1;

  if( Temp == 50.)
  {
   r_propan=propan[100];
   r_butan=butan[100];
  }
  else
  {
    itmp=Temp-(float)Beg_temp;
    itmp1=itmp+1;
    ftmp=Temp-(float)Beg_temp-(float)itmp;
    r_propan=(propan[itmp1]-propan[itmp]) * ftmp + propan[itmp];
    r_butan =(butan[itmp1] -butan[itmp] ) * ftmp + butan[itmp];
//  printf("\r\n itmp=%d,ftmp=%.3f,r_prop=%.3f,r_but=%.3f",itmp,ftmp,r_propan,r_butan);
  }
   return ( Compos*r_propan + (1.- Compos) * r_butan );
}
//-------------
float f_get_pressCT(float Compos,float Temp)
{
// �� ��⠢� � ⥬������ �����頥� �������� ����饭���� ���
// Compos - ������⢮ �ய��� � ᬥ� 0...1.0
int itmp,itmp1;
float r_propan,r_butan,ftmp;
if((Temp > 35) || (Temp< -30)) return -1;

  if( Temp == 50.)
  {
   r_propan=PropanP[100];
   r_butan=ButanP[100];
  }
  else
  {
    itmp=Temp-(float)Beg_temp;
    itmp1=itmp+1;
    ftmp=Temp-(float)Beg_temp-(float)itmp;
    r_propan=(PropanP[itmp1]-PropanP[itmp]) * ftmp + PropanP[itmp];
    r_butan =(ButanP[itmp1] -ButanP[itmp] ) * ftmp + ButanP[itmp];
  }

  return (r_butan*(1.0-Compos)+(r_propan*Compos) );
}
//-------------
// �ਥ��஢�筮� ᮤ�ঠ��� �ய��� ��� ����஫� ���뢠 諠���

#define CompID  0.55

void f_get_pressDT(float Dens,float Temp)
{
// �� ���⭮�� � ⥬������
// �����뢠�� ��⠢ ᬥ� ������ 䠧� s_MVD[0].Compos
// � �������� ����饭���� ��� �� ������ ⥬������ s_MVD[0].PressG
// Compos - ������⢮ �ய��� � ᬥ� 0...1.0

int itmp,itmp1;
float r_propan,r_butan,ftmp,Compos,Ttmp;

  AAA = 0x400;
if((Temp > 50) || (Temp< -50))
 {
  s_MVD[0].PressG=10.00 ;
  s_MVD[0].PressGN=10.00 ;
//  AAA = 0x401;
  return;
 }

  if( Temp == 50.)
  {
//  AAA = 0x402;
   r_propan=propan[100];
   r_butan=butan[100];
  }
  else
  {
//  AAA = 0x403;
    itmp=Temp-(float)Beg_temp;
    itmp1=itmp+1;
    ftmp=Temp-(float)Beg_temp-(float)itmp;
    r_propan=(propan[itmp1]-propan[itmp]) * ftmp + propan[itmp];
    r_butan =(butan[itmp1] -butan[itmp] ) * ftmp + butan[itmp];
//  AAA = 0x404;
  }

//  AAA = 0x405;
//   ������⢮ �ய��� � ᬥ� 0...1.0
  Compos = (r_butan-Dens)/(r_butan-r_propan);
  s_MVD[0].Compos=Compos;

    Ttmp=Temp + Temp_kor;
    if(Ttmp > 50) Ttmp=50;

//  AAA = 0x406;
  if((Compos<=1.) && (Compos>=0.))
  {
//  AAA = 0x407;
    Compos=Compos * Comp_kor;
    if(Compos>1.)  Compos=1.;

//  AAA = 0x408;

//  AAA = 0x409;
    if( Ttmp == 50.)
    {
     r_propan=PropanP[100];
     r_butan=ButanP[100];
    }
    else
    {
//  AAA = 0x410;
      itmp=Ttmp -(float)Beg_temp;
      itmp1=itmp+1;
      ftmp=Ttmp-(float)Beg_temp-(float)itmp;

      r_propan=(PropanP[itmp1]-PropanP[itmp]) * ftmp + PropanP[itmp];
      r_butan =(ButanP[itmp1] -ButanP[itmp] ) * ftmp + ButanP[itmp];
    }
//  AAA = 0x411;

    s_MVD[0].PressG=r_butan*(1.0-Compos)+(r_propan*Compos) ;
//  AAA = 0x412;
  }
  else
  {
//  AAA = 0x413;
    s_MVD[0].PressG=10.00 ;
//  AAA = 0x414;
  }
//  AAA = 0x421;
}
//--------------------
// ������� �����
//--------------------
// ���⭮��� ������� �ய��� � �㭪樨 ⥬�������
float propan[]={
593     ,   //-50C ====
591.8   ,   //-49
590.6   ,   //-48
589.4   ,   //-47
588.2   ,   //-46
587     ,   //-45
585.8   ,   //-44
584.6   ,   //-43
583.4   ,   //-42
582.2   ,   //-41
581     ,   //-40 ====
579.7   ,   //-39
578.4   ,   //-38
577.1   ,   //-37
575.8   ,   //-36
574.5   ,   //-35
573.2   ,   //-34
571.9   ,   //-33
570.6   ,   //-32
569.3   ,   //-31
568     ,   //-30 ====
566.7   ,   //-29
565.4   ,   //-28
564.1   ,   //-27
562.8   ,   //-26
561.5   ,   //-25
560.2   ,   //-24
558.9   ,   //-23
557.6   ,   //-22
556.3   ,   //-21
555     ,   //-20 ====
553.7   ,   //-19
552.4   ,   //-18
551.1   ,   //-17
549.8   ,   //-16
548.5   ,   //-15
547.2   ,   //-14
545.9   ,   //-13
544.6   ,   //-12
543.3   ,   //-11
542     ,   //-10 ====
540.6   ,   //-9
539.2   ,   //-8
537.8   ,   //-7
536.4   ,   //-6
535     ,   //-5
533.6   ,   //-4
532.2   ,   //-3
530.8   ,   //-2
529.4   ,   //-1
528     ,   // 0 ====
526.6   ,   // 1
525.2   ,   // 2
523.8   ,   // 3
522.4   ,   // 4
521     ,   // 5
519.6   ,   // 6
518.2   ,   // 7
516.8   ,   // 8
515.4   ,   // 9
514     ,   //10 ====
512.5   ,   //11
511     ,   //12
509.5   ,   //13
508     ,   //14
506.5   ,   //15
505     ,   //16
503.5   ,   //17
502     ,   //18
500.5   ,   //19
499     ,   //20 ====
497.4   ,   //21
495.8   ,   //22
494.2   ,   //23
492.6   ,   //24
491     ,   //25
489.4   ,   //26
487.8   ,   //27
486.2   ,   //28
484.6   ,   //29
483     ,   //30 ====
481.25  ,   //31
479.5   ,   //32
477.75  ,   //33
476     ,   //34
474.25  ,   //35
472.5   ,   //36
470.75  ,   //37
469     ,   //38
467.25  ,   //39
465.5   ,   //40 ====
463.55  ,   //41
461.6   ,   //42
459.65  ,   //43
457.7   ,   //44
455.75  ,   //45
453.8   ,   //46
451.85  ,   //47
449.9   ,   //48
447.95  ,   //49
446     ,   //50 ====
};
//-------------
// ���⭮��� ������� ��⠭� � �㭪樨 ⥬�������
float butan[]={
647    ,           //-50C ====
646.1  ,           //-49
645.2  ,           //-48
644.3  ,           //-47
643.4  ,           //-46
642.5  ,           //-45
641.6  ,           //-44
640.7  ,           //-43
639.8  ,           //-42
638.9  ,           //-41
638    ,           //-40 ====
637.1  ,           //-39
636.2  ,           //-38
635.3  ,           //-37
634.4  ,           //-36
633.5  ,           //-35
632.6  ,           //-34
631.7  ,           //-33
630.8  ,           //-32
629.9  ,           //-31
629    ,           //-30 ====
628.1  ,           //-29
627.2  ,           //-28
626.3  ,           //-27
625.4  ,           //-26
624.5  ,           //-25
623.6  ,           //-24
622.7  ,           //-23
621.8  ,           //-22
620.9  ,           //-21
620    ,           //-20 ====
619.1  ,           //-19
618.2  ,           //-18
617.3  ,           //-17
616.4  ,           //-16
615.5  ,           //-15
614.6  ,           //-14
613.7  ,           //-13
612.8  ,           //-12
611.9  ,           //-11
611    ,           //-10 ====
610    ,           //-9
609    ,           //-8
608    ,           //-7
607    ,           //-6
606    ,           //-5
605    ,           //-4
604    ,           //-3
603    ,           //-2
602    ,           //-1
601    ,           // 0 ====
600    ,           // 1
599    ,           // 2
598    ,           // 3
597    ,           // 4
596    ,           // 5
594.8  ,           // 6
593.6  ,           // 7
592.4  ,           // 8
591.2  ,           // 9
590    ,           //10 ====
588.8  ,           //11
587.6  ,           //12
586.4  ,           //13
585.2  ,           //14
584    ,           //15
582.8  ,           //16
581.6  ,           //17
580.4  ,           //18
579.2  ,           //19
578    ,           //20 ====
576.8  ,           //21
575.6  ,           //22
574.4  ,           //23
573.2  ,           //24
572    ,           //25
570.8  ,           //26
569.6  ,           //27
568.4  ,           //28
567.2  ,           //29
566    ,           //30 ====
564.8  ,           //31
563.6  ,           //32
562.4  ,           //33
561.2  ,           //34
560    ,           //35
558.8  ,           //36
557.6  ,           //37
556.4  ,           //38
555.2  ,           //39
554    ,           //40 ====
552.8  ,           //41
551.6  ,           //42
550.4  ,           //43
549.2  ,           //44
548    ,           //45
546.8  ,           //46
545.6  ,           //47
544.4  ,           //48
543.2  ,           //49
542    ,           //50 ====   C
};
//-------------
#define k_Pa (0.1019368)

//�ய�� , �������� ����饭���� ���  � �㭪樨 ⥬�������
// -50...+50 �ࠤ,蠣 1 �ࠤ, ��/�2




float PropanP[]=
{
0.2425  * k_Pa, //-50     //-50C ====
0.3145  * k_Pa,           //-49
0.3865  * k_Pa,           //-48
0.4585  * k_Pa,           //-47
0.5305  * k_Pa,           //-46
0.6025  * k_Pa,           //-45
0.6745  * k_Pa,           //-44
0.7465  * k_Pa,           //-43
0.8185  * k_Pa,           //-42
0.8905  * k_Pa,           //-41
0.9625  * k_Pa,           //-40 ====
1.0345  * k_Pa,           //-39
1.1065  * k_Pa,           //-38
1.1785  * k_Pa,           //-37
1.2505  * k_Pa,           //-36
1.3225  * k_Pa,           //-35
1.3945  * k_Pa,           //-34
1.4665  * k_Pa,           //-33
1.5385  * k_Pa,           //-32
1.6105  * k_Pa,           //-31
1.6825  * k_Pa,           //-30 ====
1.7545  * k_Pa,           //-29
1.8265  * k_Pa,           //-28
1.8985  * k_Pa,           //-27
1.9705  * k_Pa,           //-26
2.0425  * k_Pa,           //-25
2.119   * k_Pa,           //-24
2.1955  * k_Pa,           //-23
2.272   * k_Pa,           //-22
2.3485  * k_Pa,           //-21
2.425   * k_Pa,           //-20 ====
2.5275  * k_Pa,           //-19
2.63    * k_Pa,           //-18
2.7325  * k_Pa,           //-17
2.835   * k_Pa,           //-16
2.9375  * k_Pa,           //-15
3.0375  * k_Pa,           //-14
3.1375  * k_Pa,           //-13
3.2375  * k_Pa,           //-12
3.3375  * k_Pa,           //-11
3.4375  * k_Pa,           //-10 ====
3.57    * k_Pa,           //-9
3.7025  * k_Pa,           //-8
3.835   * k_Pa,           //-7
3.9675  * k_Pa,           //-6
4.1     * k_Pa,           //-5
4.2325  * k_Pa,           //-4
4.365   * k_Pa,           //-3
4.4975  * k_Pa,           //-2
4.63    * k_Pa,           //-1
4.7625  * k_Pa,           // 0 ====
4.92    * k_Pa,           // 1
5.0775  * k_Pa,           // 2
5.235   * k_Pa,           // 3
5.3925  * k_Pa,           // 4
5.55    * k_Pa,           // 5
5.725   * k_Pa,           // 6
5.9     * k_Pa,           // 7
6.075   * k_Pa,           // 8
6.25    * k_Pa,           // 9
6.425   * k_Pa,           //10 ====
6.6275  * k_Pa,           //11
6.83    * k_Pa,           //12
7.0325  * k_Pa,           //13
7.235   * k_Pa,           //14
7.4375  * k_Pa,           //15
7.651   * k_Pa,           //16
7.8645  * k_Pa,           //17
8.078   * k_Pa,           //18
8.2915  * k_Pa,           //19
8.505   * k_Pa,           //20 ====
8.744   * k_Pa,           //21
8.983   * k_Pa,           //22
9.222   * k_Pa,           //23
9.461   * k_Pa,           //24
9.7     * k_Pa,           //25
9.965   * k_Pa,           //26
10.23   * k_Pa,           //27
10.495  * k_Pa,           //28
10.76   * k_Pa,           //29
11.025  * k_Pa,           //30 ====
11.325  * k_Pa,           //31
11.625  * k_Pa,           //32
11.925  * k_Pa,           //33
12.225  * k_Pa,           //34
12.525  * k_Pa,           //35
12.825  * k_Pa,           //36
13.125  * k_Pa,           //37
13.425  * k_Pa,           //38
13.725  * k_Pa,           //39
14.025  * k_Pa,           //40 ====
14.325  * k_Pa,           //41
14.625  * k_Pa,           //42
14.925  * k_Pa,           //43
15.225  * k_Pa,           //44
15.525  * k_Pa,           //45
15.825  * k_Pa,           //46
16.125  * k_Pa,           //47
16.425  * k_Pa,           //48
16.725  * k_Pa,           //49
17.025  * k_Pa,           //50 ====   C
};


//��⠭ ; �������� ����饭���� ���  � �㭪樨 ⥬�������
// -50...+50 �ࠤ; 蠣 1 �ࠤ; ��/�2
float ButanP[]=
{
0.2625 * k_Pa ,            //-50C ====
0.27   * k_Pa,             //-49
0.2775 * k_Pa,             //-48
0.285  * k_Pa,             //-47
0.2925 * k_Pa,             //-46
0.3    * k_Pa,             //-45
0.3075 * k_Pa,             //-44
0.315  * k_Pa,             //-43
0.3225 * k_Pa,             //-42
0.33   * k_Pa,             //-41
0.3375 * k_Pa,             //-40 ====
0.345  * k_Pa,             //-39
0.3525 * k_Pa,             //-38
0.36   * k_Pa,             //-37
0.3675 * k_Pa,             //-36
0.375  * k_Pa,             //-35
0.3825 * k_Pa,             //-34
0.39   * k_Pa,             //-33
0.3975 * k_Pa,             //-32
0.405  * k_Pa,             //-31
0.4125 * k_Pa,             //-30 ====
0.42   * k_Pa,             //-29
0.4275 * k_Pa,             //-28
0.435  * k_Pa,             //-27
0.4425 * k_Pa,             //-26
0.45   * k_Pa,             //-25
0.4625 * k_Pa,             //-24
0.475  * k_Pa,             //-23
0.4875 * k_Pa,             //-22
0.5    * k_Pa,             //-21
0.5125 * k_Pa,             //-20 ====
0.53   * k_Pa,             //-19
0.5475 * k_Pa,             //-18
0.565  * k_Pa,             //-17
0.5825 * k_Pa,             //-16
0.6    * k_Pa,             //-15
0.617  * k_Pa,             //-14
0.634  * k_Pa,             //-13
0.651  * k_Pa,             //-12
0.668  * k_Pa,             //-11
0.685  * k_Pa,             //-10 ====
0.718  * k_Pa,             //-9
0.751  * k_Pa,             //-8
0.784  * k_Pa,             //-7
0.817  * k_Pa,             //-6
0.85   * k_Pa,             //-5
0.8875 * k_Pa,             //-4
0.925  * k_Pa,             //-3
0.9625 * k_Pa,             //-2
1      * k_Pa,             //-1
1.0375 * k_Pa,             // 0 ====
1.0825 * k_Pa,             // 1
1.1275 * k_Pa,             // 2
1.1725 * k_Pa,             // 3
1.2175 * k_Pa,             // 4
1.2625 * k_Pa,             // 5
1.306  * k_Pa,             // 6
1.3495 * k_Pa,             // 7
1.393  * k_Pa,             // 8
1.4365 * k_Pa,             // 9
1.48   * k_Pa,             //10 ====
1.539  * k_Pa,             //11
1.598  * k_Pa,             //12
1.657  * k_Pa,             //13
1.716  * k_Pa,             //14
1.775  * k_Pa,             //15
1.8375 * k_Pa,             //16
1.9    * k_Pa,             //17
1.9625 * k_Pa,             //18
2.025  * k_Pa,             //19
2.0875 * k_Pa,             //20 ====
2.1615 * k_Pa,             //21
2.2355 * k_Pa,             //22
2.3095 * k_Pa,             //23
2.3835 * k_Pa,             //24
2.4575 * k_Pa,             //25
2.5385 * k_Pa,             //26
2.6195 * k_Pa,             //27
2.7005 * k_Pa,             //28
2.7815 * k_Pa,             //29
2.8625 * k_Pa,             //30 ====
2.95   * k_Pa,             //31
3.0375 * k_Pa,             //32
3.125  * k_Pa,             //33
3.2125 * k_Pa,             //34
3.3    * k_Pa,             //35
3.3875 * k_Pa,             //36
3.475  * k_Pa,             //37
3.5625 * k_Pa,             //38
3.65   * k_Pa,             //39
3.7375 * k_Pa,             //40 ====
3.825  * k_Pa,             //41
3.9125 * k_Pa,             //42
4      * k_Pa,             //43
4.0875 * k_Pa,             //44
4.175  * k_Pa,             //45
4.2625 * k_Pa,             //46
4.35   * k_Pa,             //47
4.4375 * k_Pa,             //48
4.525  * k_Pa,             //49
4.6125 * k_Pa,             //50 ====
};

