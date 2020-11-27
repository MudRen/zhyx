// Updated by Lonely

#include <ansi.h>
#include <combat.h>
#include <net/dns.h>

inherit F_CLEAN_UP;
string bar_string = "������������������������";
string blank_string = "������������������������";
string blank_string3 = "������������������������";
string blank_string2 = "������������������������";

mapping oprank = ([
        "��ʦ"     : HIW "������",
        "�Ƿ��켫" : HIY "������",
        "��������" : HIY "�����  ",
        "��������" : HIR "�����  ",
        "¯����" : HIR "����    ",
        "���д��" : HIC "����    ",
        "��ͬ����" : HIC "���      ",
        "�������" : HIG "���      ",
        "���ֲ���" : HIG "��        ",
        "����С��" : HIM "��        ",
]);

string display_attr(int gift, int value);
string status_color(int current, int max);
string tribar_graph(int val, int eff, int max, string color);
string tribar_graph2(int val, int eff, int max, string color);
string tribar_graph3(int a);
void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        mapping my,mci;
        string line , skill_type;
        object weapon;
        int attack_points, dodge_points, parry_points,jings, qis, j, i, x, cnt;
        string jbd, msg;
        mixed wind,cold,fire,lightning,poison;
        int can_score = 0;
        int age, month;
        string startroom = "";
        object the_room = 0;

        seteuid(getuid(me));

        if(! arg)
                ob = me;
        else
                ob = present(arg, environment(me));

        if (! ob) ob = find_player(arg);
        if (! ob) ob = find_living(arg);
        if (! ob) return notify_fail("��Ҫ�쿴˭��״̬��\n");

        if (wizardp(me) || ob == me) 
                can_score = 1;
        else 
        if (ob->is_pet() && ob->query("owner") == me->query("id")) 
                can_score = 1;
        else 
        if (me->query("couple/child") == ob->query("id"))
                can_score = 1;
        else 
        if (stringp(startroom = ob->query("startroom")) &&
            objectp(the_room = load_object(startroom)) &&
            the_room->query("room_owner_id") == me->query("id"))
                can_score = 1;
        if (! can_score)
                return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");

        my = ob->query_entire_dbase();
        mci = my["combat"];
        if (! mci) mci = ([ ]);
        
        if (playerp(ob) && (! stringp(my["born"]) || ! my["born"])) 
                return notify_fail("��û�г����ţ��쿴ʲô��\n"); 

        jings = (my["eff_jing"] * 12 / my["max_jing"]) * 2;
        qis = (my["eff_qi"] * 12 / my["max_qi"]) * 2;
        // line = sprintf("                          ��" + MUD_NAME + "�����˵���                      \n\n", ob->query("language"),);
        line = sprintf( BOLD "\n%s" NOR "%s\n", RANK_D->query_rank(ob), ob->short(1) );
        // ob->update_age();
        
        line += sprintf( YEL "���������������������������������������ש���������������������������\n" NOR );

	if (playerp(ob))
	{
                age = ob->query("age");
                month = ob->query("mud_age");
                if (age >= 60)
                {
                        month -= (age - 60) * 86400 * 4;
                        month = (month - 118 * 86400) / 7200 / 4 + 1;
                } else
                if (age >= 30)
                {
                        month -= (age - 30) * 86400 * 3;
                        month = (month - 28 * 86400) / 7200 / 3 + 1;
                } else
                if (age >= 18)
                {
                        month -= (age - 18) * 86400 * 2;
                        month = (month - 4 * 86400) / 7200 / 2 + 1;
                } else
                {
                        month -= (age - 14) * 86400;
                        month = month / 7200 + 1;
                }

                // not show invalid month
                if (month > 12 || month < 1)
                        month = 1;

        	line += sprintf( YEL "��" HIY "�����䡿" NOR "%-24s  " YEL "  ��" NOR ,
                        chinese_number(age) + "��" + 
                        chinese_number(month) + "����");
        } else
                line += sprintf( YEL "��" HIY "�����䡿" NOR "%-24s  " YEL "  ��" NOR , 
                        chinese_number(ob->query("age")) + "��" +  
                        chinese_number((ob->query("mud_age")-(ob->query("age")-14)*86400)/7200 + 1 ) + "����"); 
                
	if (objectp(weapon = ob->query_temp("weapon")))
        {
		skill_type = weapon->query("skill_type");
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	} else
        {
                mapping prepare;
                string *sk;

                prepare = me->query_skill_prepare();
                if (! prepare) prepare = ([]);
                sk = keys(prepare);
        
                if (sizeof(sk) == 0) skill_type = "unarmed"; 
                else skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if (sizeof(prepare) == 2)
                {
                        int temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);
                        if (attack_points < temp) attack_points = temp;
                }
        }

	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);

        line += sprintf( HIW "��ս����������" NOR " %10d" YEL " ��\n" NOR ,
                attack_points/100 + 1);

        line += sprintf( YEL "��" HIY "���Ա�" NOR "%-26.8s" YEL "  ��" NOR ,
                    ob->query("gender")+ob->query("race"));
                                        
        line += sprintf( HIW "��ս����������" NOR " %10d" YEL " ��\n" NOR ,
                (dodge_points + (weapon? parry_points: (parry_points/10)))/100 + 1);

        line += sprintf( YEL "��" HIY "���Ը�" NOR "%-28.28s" YEL "��" NOR ,
                ob->query("character")?ob->query("character"):"��δȷ��" );

        line += sprintf( HIW "��ս���˺�����" NOR " %10d" YEL " ��\n" NOR ,
                weapon ? ob->query_temp("apply/damage")
                               : ob->query_temp("apply/unarmed_damage"));

        line += sprintf( YEL "��" HIY "��������" MAG "%-28.28s" NOR+YEL "��" NOR ,
                CHINESE_D->chinese_date(ob->query("birthday")));

        line += sprintf( HIW "��ս����������" NOR " %10d" YEL " ��\n" NOR ,
                ob->query_temp("apply/armor"));

        line += sprintf( YEL "��                          �����������ߩ���������������������������\n" NOR,);      
        if (mapp(my["family"]))
        {
                if( my["family"]["family_name"] )
                        line += sprintf( YEL "��" HIG "�����ɡ�" NOR "%-18.8s" YEL "��" NOR,
                                my["family"]["family_name"] );
                else  
                        line += sprintf( YEL "��" HIG "�����ɡ�" NOR "��ͨ����          " YEL "��" NOR );
        }
        else  
                line += sprintf( YEL "��" HIG "�����ɡ�" NOR "��ͨ����          " YEL "��" NOR );
        line += sprintf( HIY "��������" HIW "%2d |%3d   " HIY "�����ԡ�" HIW "%2d |%3d" NOR+YEL "   ��\n" NOR , 
                ob->query("str"),
                ob->query_str(),
                ob->query("int"), 
                ob->query_int());

        if (mapp(my["family"]))
        {
                if( my["family"]["master_name"] )
                        line += sprintf( YEL "��" HIG "��ʦ�С�" NOR "%-18.18s" YEL "��" NOR,
                                my["family"]["master_name"] );
                else
                        line += sprintf( YEL "��" HIG "��ʦ�С�" NOR "�㻹û�а�ʦ      " YEL "��" NOR );
        }
        else  
                line += sprintf( YEL "��" HIG "��ʦ�С�" NOR "�㻹û�а�ʦ      " YEL "��" NOR );
        line += sprintf( HIY "�����ǡ�" HIW "%2d |%3d   " HIY "������" HIW "%2d |%3d" NOR+YEL "   ��\n" NOR , 
                ob->query("con"),           
                ob->query_con(),
                ob->query("dex"), 
                ob->query_dex());

        line += sprintf( YEL "��" HIW "�����ɡ�" NOR "%-18.18s", stringp(ob->query("party/party_name"))?ob->query("party/party_name"):"������ʿ");
        line += sprintf( YEL "��" HIC "��ȭ�š�" NOR "%s" HIC "��������" NOR "%s" NOR YEL "��\n" NOR,ob->query("opinion/unarmed")? oprank[ob->query("opinion/unarmed")]:CYN "������    " NOR,ob->query("opinion/weapon")? oprank[ob->query("opinion/weapon")]:CYN "������    " NOR); 
        if (stringp(ob->query("degree")))
                line += sprintf( YEL "��" HIW "��ְ��" NOR "%" + sprintf("%d",18 + color_len(ob->query("degree"))) + "-s", ob->query("degree"));
        else
        if (stringp(ob->query("bunch/title")))
                line += sprintf( YEL "��" HIW "��ְ��" NOR "%" + sprintf("%d",18 + color_len(ob->query("party/title"))) + "-s", ob->query("party/title"));
        else
                line += sprintf( YEL "��" HIW "��ְ��" NOR "��                " );
        line += sprintf( YEL "��" HIC "���ڹ���" NOR "%s" HIC "���Ṧ��" NOR "%s" NOR YEL "��\n" NOR,ob->query("opinion/force")? oprank[ob->query("opinion/force")]:CYN "������    " NOR,ob->query("opinion/dodge")? oprank[ob->query("opinion/dodge")]:CYN "������    " NOR); 
        /*
        if (ob->query("is_vendor"))
                line += sprintf(YEL "��" HIG "��ְҵ��" NOR "����              " );
        else
                line += sprintf(YEL "��" HIG "��ְҵ��" NOR "��                " );
        */
        line += sprintf(YEL "��" HIG "��������" NOR "%-10d        ", ob->query("meili"));
        line += sprintf( YEL "��" HIY "�����顿" HIW "%-10d" HIY "��Ǳ�ܡ�" NOR "%s%-10d" NOR YEL "��\n" NOR ,my["combat_exp"],(int)ob->query("potential")>=(int)ob->query_potential_limit()?HIM:HIW,(int)ob->query("potential") - (int)ob->query("learned_points") );
        line += sprintf( YEL "��" HIG "��������" NOR "%-18d" YEL "��" NOR, ob->query("weiwang") );
        line += sprintf( HIY "��%s��" HIW "%-10d" HIY "����᡿" HIW "%s%-10d" NOR YEL "��\n" NOR ,(ob->query("shen")>=0)?"����":"а��",ob->query("shen")?ob->query("shen"):0,my["combat_exp"] < 100000 ? HIR :
                        my["experience"] < ob->query_experience_limit() ? HIW : HIM,
                        (my["experience"] - my["learned_experience"]) );
        if (! ob->query("private_room"))
                line += sprintf(YEL "��" HIW "��סլ��" NOR "%-18.8s" , "���˽�ͷ");
        else
                line += sprintf(YEL "��" HIW "��סլ��" NOR "%-18.8s" , ob->query("private_room/name") );
        line += sprintf( YEL "��" HIY "�����ס�" HIW "%-10d" HIY "����ݡ�" NOR HIW "%-10d" NOR YEL "��\n" NOR ,my["gongxian"] ,my["magic_points"] - my["magic_learned"] );
        /*
        if (mapp(my["couple"]))
        {
                line += sprintf(YEL "��" HIW "��������" NOR "%-18.8s" , "���" + chinese_number(my["couple"]["married"]) + "��");
                line += sprintf( YEL "��" HIY "��������" NOR HIW "%-10d" NOR HIY "��������"NOR HIW "%-10d" NOR YEL "��\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                if (my["couple"]["have_couple"])
                {
                        line += sprintf(YEL "��" HIW "��%s��" NOR "%-18.8s" YEL "����������������������������������������\n" NOR , my["couple"]["couple_gender"],my["couple"]["couple_name"] + "(" + my["couple"]["couple_id"]  + ")");
                } else
                {
                        line += sprintf(YEL "��" HIW "�����¡�" NOR "%-18.8s" YEL "����������������������������������������\n" NOR , "û��");
                }                       
                line += sprintf(YEL "��" HIW "����Ů��" NOR "%-56s" NOR YEL "��\n", mapp(my["couple"]["child"]) ? my["couple"]["child"]["name"] : "û��");
        }
        */
        if (mapp(my["couple"]))
        {
                line += sprintf(YEL "��" HIW "��������" NOR "%-18.8s" , my["couple"]["name"] ? "���" : "ɥż");
                line += sprintf(YEL "��" HIY "��������" NOR HIW "%-10d" NOR HIY "��������"NOR HIW "%-10d" NOR YEL "��\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                if (my["couple"]["name"])
                {
                        line += sprintf(YEL "��" HIW "��%s��" NOR "%-18s" YEL "����������������������������������������\n" NOR , "����",my["couple"]["name"] + "(" + my["couple"]["id"]  + ")");
                } else
                {
                        line += sprintf(YEL "��" HIW "�����¡�" NOR "%-18.8s" YEL "����������������������������������������\n" NOR , "û��");
                }                       
                line += sprintf(YEL "��" HIW "����Ů��" NOR "%-56s" NOR YEL "��\n", mapp(my["couple"]["child_name"]) ? my["couple"]["child_name"] : "û��");
        }
        else
        { 
                line += sprintf( YEL "��" HIW "��������" NOR "����              " );
                line += sprintf( YEL "��" HIY "��������" NOR HIW "%-10d" NOR HIY "��������"NOR HIW "%-10d" NOR YEL "��\n" NOR ,ob->query("score")?ob->query("score"):0,ob->query("total_hatred")?ob->query("total_hatred"):0 );
                line += sprintf( YEL "��" HIW "�����¡�" NOR "û��              " YEL "����������������������������������������\n" NOR );
                line += sprintf( YEL "��" HIW "����Ů��" NOR "%-56s" NOR YEL "��\n", "û��" );
        }

        if (my["gender"] == "����")
                line += sprintf( YEL "��" HIW "�����ԡ�" NOR "%-56s" NOR YEL "��\n","���Ǹ�̫�ࡣ" );
        else if (! ob->query("sex/times"))
        {
                if (my["gender"] == "Ů��")
                        line += sprintf( YEL "��" HIW "�����ԡ�" NOR "%-56s" NOR YEL "��\n","�㻹�Ǵ�Ů��" );
                else
                        line += sprintf( YEL "��" HIW "�����ԡ�" NOR "%-56s" NOR YEL "��\n","�㻹��ͯ�С�" );
        } else
        {
                string *ks;
                        ks = keys(ob->query("sex"));
                        ks -= ({ "times", "first", "" });
                        if (sizeof(ks) >= 5)
                                line += sprintf( YEL "��" HIW "�����ԡ�" NOR "%-56s" NOR YEL "��\n",
                                                "����������������˷�������ϵ�����Լ���������˭��");
                        else
			{
                                msg = "��������" + implode(ks,"��") + "��������ϵ��";
                                line += sprintf( YEL "��" HIW "�����ԡ�" NOR "%" + sprintf("%d", (56 + color_len(msg))) + "-s" NOR YEL "��\n",
                                                "��������" + implode(ks,"��") + "��������ϵ��");
			}
        }

        line += sprintf(YEL "��" HIW "�����" NOR "%-56s" NOR YEL "��\n", mapp(ob->query("can_whistle")) ? "ӵ��" : "û��");
        
        if (ob->query("balance") <= 0)
                line += sprintf( YEL "��" HIY "��Ǯׯ��" HIY "û�л���                                                " NOR+YEL "��\n" NOR );
        else
        {
                line += sprintf ( YEL "��"  HIY "��Ǯׯ��" NOR );
                line += sprintf (HIY"%-56.56s"NOR,
                MONEY_D->money_str((int)ob->query("balance")));
                line += sprintf ( NOR+YEL "��\n" NOR );
        }
        cold=ob->query_temp("apply/cold_defence");
if (cold>=75) cold="���"; else cold =cold+"��";
fire=ob->query_temp("apply/fire_defence");
if (fire>=75) fire="���"; else fire =fire+"��";
lightning=ob->query_temp("apply/lightning_defence");
if (lightning>=75) lightning="���"; else lightning =lightning+"��";
poison=ob->query_temp("apply/poison_defence");
if (poison>=75) poison="���"; else poison =poison+"��";
wind=ob->query_temp("apply/wind_defence");
if (wind>=75) wind="���"; else wind =wind+"��";

        line += HIW+"\n\n ����" +NOR+"��"+cold +"\t   "+HIG+"����" + NOR+"��"+poison+NOR+YEL+"\t   ����" +NOR+"��"+ wind;
        line += HIR+"\n ����" +NOR+"��"+fire + "\t\t\t   "+HIB+"����" + NOR+"��"+lightning;
        line += sprintf( YEL "��                                                                ��\n" NOR );
        line += sprintf( YEL "��" NOR HIY " ��ѧ��ʦ�� %s" NOR HIY "    �ζ������� %s" NOR HIY "   ԪӤ������ %s" NOR HIY "    ת��������%s " NOR YEL "��\n" NOR,
                ultrap(ob) ? "��" : HIC "��", ob->query("breakup") ? "��" : HIC "��", ob->query("animaout") ? "��" : HIC "��", ob->query("reborn") ? "��" : HIC "��" );
        
        /*
        msg = "";
        if (ultrap(ob))
                msg = " ���Ѿ���Ϊ����ʦ";
        if (ob->query("breakup"))
                msg += "����ͨ�ζ�����";
        if (ob->query("animaout"))
                msg += "���޳�ԪӤ����";
        if (ob->query("tianmo_jieti/times"))
                msg += "����ħ����" + chinese_number((int)ob->query("tianmo_jieti/times")) + "��";

        if (msg != "")
        {       
                msg += "��";
                line += sprintf( YEL "��" NOR HIC "%-64s" NOR YEL "��\n" NOR, msg );
                line += sprintf( YEL "��                                                                ��\n" NOR );
        }

        if( my["max_jing"] >= my["eff_jing"])
                line += sprintf( YEL "��" HIC" ��  "NOR"��%-24s   ", tribar_graph(my["jing"], my["eff_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"])) + tribar_graph3(jings));
        else
                line += sprintf( YEL "��" HIC" ��  "NOR"��%-24s   " , tribar_graph2(my["jing"], my["max_jing"], my["max_jing"], status_color(my["jing"], my["max_jing"]))+ tribar_graph3(jings));

        if( my["max_jingli"] > 0 )
                line += sprintf( HIC "����"NOR"��%-24s"+ NOR+YEL+"��\n"NOR, tribar_graph(my["jingli"], my["max_jingli"], my["max_jingli"], status_color(my["jingli"], my["max_jingli"])));
        else
                line += sprintf( HIC "����"NOR "��" HIG "%-24s"+ NOR+YEL+"��\n"NOR, blank_string );

        if( my["max_qi"] >= my["eff_qi"])
                line += sprintf( YEL "��" HIC" ��  "NOR"��%-24s   ", tribar_graph(my["qi"], my["eff_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));
        else    
                line += sprintf( YEL "��" HIC" ��  "NOR"��%-24s   ", tribar_graph2(my["qi"], my["max_qi"], my["max_qi"], status_color(my["qi"], my["max_qi"])) + tribar_graph3(qis));

        if( my["max_neili"] > 0 )
                line += sprintf( HIC "����"NOR"��%-24s"+ NOR+YEL+"��\n"NOR, tribar_graph(my["neili"], my["max_neili"], my["max_neili"], status_color(my["neili"], my["max_neili"])));
        else
                line += sprintf( HIC "����"NOR "��" HIG "%-24s"+ NOR+YEL+"��\n"NOR, blank_string );

        if( ob->max_food_capacity() > 0 )
                line += sprintf( YEL "��" HIC" ʳ��"NOR"��%-24s   ", tribar_graph(my["food"], ob->max_food_capacity(), ob->max_food_capacity(), YEL));
        else
                line += sprintf( YEL "��" HIC" ʳ��"NOR"��"YEL   "%-24s"+ NOR+YEL+"��\n"NOR, blank_string );
        
        if( ob->max_water_capacity() > 0 )
                line += sprintf( HIC "��ˮ"NOR"��%-24s"+ NOR+YEL+"��\n"NOR , tribar_graph(my["water"], ob->max_water_capacity(), ob->max_water_capacity(), CYN));
        else
                line += sprintf( HIC "��ˮ"NOR CYN"��%-24s"+ NOR+YEL+"��\n"NOR, blank_string );

        */          
        line += sprintf( YEL "�ǩ��������������������ש��������������������ש���������������������\n" NOR );        

        line += sprintf( YEL "��" HIB "��ɱ��������" NOR HIR"%6dλ"NOR, 
                (int)mci["MKS"] + (int)mci["PKS"]);
        line += sprintf( YEL "��" HIB "��ɱ����ҡ�" NOR HIR"%6dλ"NOR, 
                (int)mci["PKS"]);
        line += sprintf( YEL "��" HIB "������ɱ����" NOR HIR"%6dλ"NOR, 
                (int)mci["WPK"]);
        line += YEL "��\n" NOR;

        line += sprintf( YEL "��" HIB "��������ҡ�" NOR HIR"%6dλ"NOR, 
                (int)mci["DPS"]);
        line += sprintf( YEL "��" HIB "��������ʿ��" NOR HIR"%6dλ"NOR, 
                (int)mci["DPS_GOOD"]);
        line += sprintf( YEL "��" HIB "��а����ʿ��" NOR HIR"%6dλ"NOR, 
                (int)mci["DPS_BAD"]);
        line += YEL "��\n" NOR;

        line += sprintf( YEL "�ǩ��������������������ߩ��������������������ߩ���������������������\n" NOR );

        line += sprintf( YEL "��" NOR HIB " ��Ŀǰ��ɱ���ǣ�%s%-47d"NOR YEL "��\n" NOR,
                         ((int)ob->query("pk_score")>2000)?HIR:((int)ob->query("pk_score")>1000)?HIM:HIW,
                         (int)ob->query("pk_score") );

        msg = "";
        if ((int)mci["dietimes"])
 	        msg = sprintf(HIB " �㵽ĿǰΪֹ�ܹ����ڰ��޳�����"
				"����%s�Ρ�" NOR,
				chinese_number(mci["dietimes"]));
        if (msg != "")
                line += sprintf( YEL "��" NOR "%" + sprintf("%d",(64 + color_len(msg))) + "-s" NOR YEL "��\n" NOR, msg );

        msg = "";
        if (stringp(mci["last_die"]))
			msg += sprintf(HIB " �����һ����%s��" NOR,
					mci["last_die"]);
        if (msg != "")
                line += sprintf( YEL "��" NOR "%" + sprintf("%d",(64 + color_len(msg))) + "-s" NOR YEL "��\n" NOR, msg );
        line += YEL "���������������������������������������������������������˵���������\n" NOR;

         write(line);
         return 1;
}


string display_attr(int gift, int value)
{
        if( value > gift ) return sprintf( HIY "%6s" NOR, chinese_number(value) );
        else if( value < gift ) return sprintf( CYN "%6s" NOR, chinese_number(value) );
        else return sprintf("%6s", chinese_number(value));
}

string status_color(int current, int max)
{
        int percent;

        if( max ) percent = current * 100 / max;
        else percent = 100;

        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return HIB;
}

string tribar_graph(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph2(int val, int eff, int max, string color)
{
        return color + bar_string[0..(val*12/max)*2-1]
                + ((eff > val) ? blank_string2[(val*12/max)*2..(eff*12/max)*2-1] : "") + NOR;
}
string tribar_graph3(int a)
{
        return BLU + blank_string3[0..(23-a)] + NOR;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : score
           score <��������>                   (��ʦר��)

���ָ�������ʾ��(��)��ָ������(������)�Ļ������ϡ�
�������ϵ��趨����� 'help setup'��

see also : hp
HELP
    );
    return 1;
}

