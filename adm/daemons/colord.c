#include <ansi.h>
string clean_color(string str)
{
        int i;
        string  *color  =    ({ BLK,
                                RED,
                                GRN,
                                YEL,
                                BLU,
                                MAG,
                                CYN,
                                WHT,
                                HIR,
                                HIG,
                                HIY,
                                HIB,
                                HIM,
                                HIC,
                                HIW,
                                HBRED,
                                HBGRN,
                                HBYEL,
                                HBBLU,
                                HBMAG,
                                HBCYN,
                                HBWHT,
                                BBLK,
                                BRED,
                                BYEL,
                                BBLU,
                                BMAG,
                                BCYN,
                                NOR,
                                BLINK });

        if( !str || !stringp(str) ) return 0;
        i = sizeof(color);
        while( i-- ) {
                str = replace_string(str, color[i], "");
        }
        return str;
}


varargs string replace_color(string arg,int flag)
{
        arg = replace_string(arg, "$BLK$", flag?BLK:"");
        arg = replace_string(arg, "$RED$", flag?RED:"");
        arg = replace_string(arg, "$GRN$", flag?GRN:"");
        arg = replace_string(arg, "$YEL$", flag?YEL:"");
        arg = replace_string(arg, "$BLU$", flag?BLU:"");
        arg = replace_string(arg, "$MAG$", flag?MAG:"");
        arg = replace_string(arg, "$CYN$", flag?CYN:"");
        arg = replace_string(arg, "$WHT$", flag?WHT:"");
        arg = replace_string(arg, "$HIR$", flag?HIR:"");
        arg = replace_string(arg, "$HIG$", flag?HIG:"");
        arg = replace_string(arg, "$HIY$", flag?HIY:"");
        arg = replace_string(arg, "$HIB$", flag?HIB:"");
        arg = replace_string(arg, "$HIM$", flag?HIM:"");
        arg = replace_string(arg, "$HIC$", flag?HIC:"");
        arg = replace_string(arg, "$HIW$", flag?HIW:"");
        arg = replace_string(arg, "$NOR$", flag?NOR:"");
        arg = replace_string(arg, "$BLINK$", flag?BLINK:"");

        // Background color
        arg = replace_string(arg, "$BBLK$", BBLK);
        arg = replace_string(arg, "$BRED$", BRED);
        arg = replace_string(arg, "$BGRN$", BGRN);
        arg = replace_string(arg, "$BYEL$", BYEL);
        arg = replace_string(arg, "$BBLU$", BBLU);
        arg = replace_string(arg, "$BMAG$", BMAG);
        arg = replace_string(arg, "$BCYN$", BCYN);
        arg = replace_string(arg, "$HBRED$", HBRED);
        arg = replace_string(arg, "$HBGRN$", HBGRN);
        arg = replace_string(arg, "$HBYEL$", HBYEL);
        arg = replace_string(arg, "$HBBLU$", HBBLU);
        arg = replace_string(arg, "$HBMAG$", HBMAG);
        arg = replace_string(arg, "$HBCYN$", HBCYN);
        if(flag) arg+=NOR;
        return arg;
}
/*
type: 1 : �漴��ɫ
      2 : �漴��ɫ��ǰ��ɫ
      3 : �漴��ɫ
      4 ���漴��ɫ
blink: 1 : ��˸
*/
varargs string random_color(int type,int blink)
{
        string  *color_a  = ({  RED,
                                GRN,
                                YEL,
                                BLU,
                                MAG,
                                CYN,
                                HIR,
                                HIG,
                                HIY,
                                HIB,
                                HIM,
                                HIC,
                                HIW,
                                WHT
                                });

        string *color_b =   ({  BRED,
                                BGRN,
                                BYEL,
                                BBLU,
                                BMAG,
                                BCYN,
                                HBRED,
                                HBGRN,
                                HBYEL,
                                HBBLU,
                                HBMAG,
                                HBCYN,
                                HBWHT,
                        });
        string co="";
        int co1,co2;
        if( blink ) co+=BLINK;

        if( type==1 ) co+=color_b[random(sizeof(color_b))];
        else
        if( type==2 ) {
                co1=random(sizeof(color_b));
                co2=random(sizeof(color_a));
                while ( co1==co2 )
                {
                co1=random(sizeof(color_b));
                co2=random(sizeof(color_a));
                }
                co+=color_b[co1]+color_a[co2];
                }
        else
        if( type == 3 ) {
                if( random(6) )
                co1=random(6);
                else co1=13;
                co+=color_a[co1];
                }
        else
        if ( type == 4 ) {
                co1=6+random(7);
                co+=color_a[co1];
        }
        else    co+=color_a[random(sizeof(color_a))];

        return co;
}

string get_color(string arg)
{
        if( strsrch(arg,BLK)!=-1 ) return BLK;
        if( strsrch(arg,RED)!=-1 ) return RED;
        if( strsrch(arg,GRN)!=-1 ) return GRN;
        if( strsrch(arg,YEL)!=-1 ) return YEL;
        if( strsrch(arg,BLU)!=-1 ) return BLU;
        if( strsrch(arg,MAG)!=-1 ) return MAG;
        if( strsrch(arg,CYN)!=-1 ) return CYN;
        if( strsrch(arg,WHT)!=-1 ) return WHT;
        if( strsrch(arg,HIR)!=-1 ) return HIR;
        if( strsrch(arg,HIG)!=-1 ) return HIG;
        if( strsrch(arg,HIY)!=-1 ) return HIY;
        if( strsrch(arg,HIB)!=-1 ) return HIB;
        if( strsrch(arg,HIM)!=-1 ) return HIM;
        if( strsrch(arg,HIC)!=-1 ) return HIC;
        if( strsrch(arg,HIW)!=-1 ) return HIW;
        if( strsrch(arg,BLINK)!=-1 ) return BLINK;
        return "";
}

string transfer_color(string arg)
{
       if( arg=="BLK" ) return BLK;
       if( arg=="RED" ) return RED;
       if( arg=="GRN" ) return GRN;
       if( arg=="YEL" ) return YEL;
       if( arg=="BLU" ) return BLU;
       if( arg=="MAG" ) return MAG;
       if( arg=="CYN" ) return CYN;
       if( arg=="WHT" ) return WHT;
      if( arg=="HIR" ) return HIR;
       if( arg=="HIG" ) return HIG;
       if( arg=="HIY" ) return HIY;
       if( arg=="HIB" ) return HIB;
       if( arg=="HIM" ) return HIM;
       if( arg=="HIC" ) return HIC;
       if( arg=="HIW" ) return HIW;
       if( arg=="HBRED" ) return HBRED;
       if( arg=="HBGRN" ) return HBGRN;
       if( arg=="HBYEL" ) return HBYEL;
       if( arg=="HBBLU" ) return HBBLU;
       if( arg=="HBMAG" ) return HBMAG;
       if( arg=="HBCYN" ) return HBCYN;
       if( arg=="HBWHT" ) return HBWHT;
       if( arg=="BBLK" ) return BBLK;
       if( arg=="BRED" ) return BRED;
       if( arg=="BYEL" ) return BYEL;
       if( arg=="BBLU" ) return BBLU;
       if( arg=="BMAG" ) return BMAG;
       if( arg=="BCYN" ) return BCYN;
       if( arg=="NOR" ) return NOR;
       if( arg=="BLINK" ) return BLINK;
       return "";
 }
string random_jjww()
{
string *jjww=({
"����˯�μ������������μ��ڿ���",
"����������֣�Ӧ����ô�����",
"�����μ��������������ׯ����",
"��������Ӧ��ϲ�������������",
"���˷�ɲ����������ס���ļ��ֽ�",
"���˷�ɲ����������ס�����ڷ���",
"�����ɲ���ɳ����Ϥ�����󸣹�",
"���з�ɲ���ɳ����Ϥ��ʩ���߱�",
"����Χɽ�߹����������Ϊ���",
"�������������٣���ͷ���m������",
"�����˵ȵ�ʤ������������������",
"�˵�������ʤ�ߣ����ޱ��������",
"�ǹʵ��Ŵ�������߳����ַ���",
"�����ޱߴ󸣾ۣ��ٵ�֤�����ϵ�"
});
        return WHT"���ƣ���"+random_color(2)+jjww[random(sizeof(jjww))]+NOR+WHT+"����";
}

