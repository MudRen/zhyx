/************************�׻��Դ��书ϵͳ�����ļ�*********************************
created by Rcwiz for YHONLINE
*******************************************************************************/

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>
#include <localtime.h>

#define MEMBER_D                        "/adm/daemons/memberd" 
#define CND_EXP_1                       5000000
#define CND_POT_1                       10000
#define SK_FILE                         "/kungfu/skill/" + my_mkskill["skid"]
#define RATE                            10
#define MAX_POINT                       3000000.0000
#define VERSION                         "V 1.00"

// ���������ȵİٷ���������ս���������ã�
public int get_point(int point)
{
    int pt;
    
    pt = (int)(point / MAX_POINT);

    return pt;
}
// ���������ȵİٷ�����������ʾ��
public float get_point2(int point)
{
 	float fp = (float)point;
	return (float)(fp / MAX_POINT);   
}
// �������������
public int get_max_point()
{
	return MAX_POINT;
}
// ��ȡ�Դ��书
public mixed get_pmsk_id(object me)
{
	mapping skills;
	string *my_skills;
	int i;

        skills = me->query_skills();
        if (! sizeof(skills))return 1;
        my_skills = keys(skills);
        
        // ��ȡ�Դ��书
        for (i = 0; i < sizeof(my_skills); i ++)
        {
              if (("/kungfu/skill/" + my_skills[i])->playermake())
                    return my_skills[i];              
        }
        return 0;
}

string *can_make = ({
	"sword", "blade", "staff", "unarmed", "cuff", "whip",
	"strike", "hand", "club", "finger", "claw"
});

string *weapon_sk = ({
	"sword", "blade", "staff", "whip", "club"
});

mapping damage_type = ([
        "sword"            :    "����",
        "blade"            :    "����",
        "staff"            :    "����",
        "unarmed"          :    "����",
        "cuff"             :    "����",
        "whip"             :    "����",
        "strike"           :    "����",
        "hand"             :    "����",
        "club"             :    "����",
        "finger"           :    "����",
        "claw"             :    "ץ��"
]);       
        
mapping skill_feature = ([
        "dam"              :    "������",
        "att"              :    "�鶯��",
        "def"              :    "������"
]);

private void modify_file(object me, mapping my_mkskill, string strmsg_hitob, int flag);
public int create_actions(object me, string skname, string desc, string ctsk);
public show_pmsk(object me, string skid);

void create()
{
        seteuid(getuid());
        set("channel_id", "ϵͳ����");
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "�Դ��书ϵͳϵͳ�Ѿ�������");       
}

/***************************************************************************
  ����Ƿ�ﵽ�Դ��书��������
****************************************************************************/
public int check_condition1(object me)
{
	string *my_skills;
	mapping skills;
	int i;
	/*
	if (! MEMBER_D->is_valib_member(me->query("id")))
	{
		write("�Բ����Դ��书ϵͳֻ����Ч��Ա���š�\n");
		return 0;		
        }
        */
	if (me->query("combat_exp") < CND_EXP_1)
	{
		write("��ʵս���鲻�㣬 �޷��Դ��书��\n");
		return 0;
	}
	if (me->add("potential", 0) < CND_POT_1)
	{
		write("��Ǳ�ܲ������޷��Դ��书��\n");
		return 0;
	}
	if (me->query_skill("martial-cognize", 1) < 400)
	{
		write("����ѧ�������㣬�޷��Դ��书��\n");
		return 0;		
	}
	if (! me->query("breakup"))
	{
		write("��δ��ͨ�ζ��������޷��Դ��书��\n");
		return 0;		
	}
	if (! ultrap(me))
	{
		write("�㻹���ȳ�Ϊ��ѧ����ʦ��˵�ɣ�\n");
		return 1;
	}
	// �Ƿ��Ѿ��Դ����书
        skills = me->query_skills();
        if (! sizeof(skills))return 1;
        my_skills = keys(skills);

        for (i = 0; i < sizeof(my_skills); i ++)
        {
        	if (("/kungfu/skill/" + my_skills[i])->playermake())
        	{
        	      write("���Ѿ��Դ����书 " + my_skills[i] + " �ˣ�\n");
        	      return 0;
        	}
        }
        if (me->query("pmskills"))
        {
        	write("�Բ���������Դ��书���ݼ�¼����������Դ��书����������\n"
        	      "���߲����ڣ����뱾վ��ʦ��ϵ��������������ݣ�\n");
        	return 0;
        }

        return 1;
}

/***************************************************************************
  ����Ƿ�ﵽ�Դ��书�����������Դ��书���ÿ�ʼ
****************************************************************************/
public int check_condition2(object me)
{
	write(HIG "\n�������Դ��书�����࣬Ϊ��������һ�֣�\n" NOR);
	write(HIR "sword��blade��staff��whip��finger��unarmed��"
	      "strike��hand��cuff��hand��claw��club\n" NOR);
        write(HIR "ע�⣺ѡ������ǰ��ȷ������װ����Ӧ��������֡�\n" NOR);
	write(HIW "�书���ࣺ" NOR);
        input_to("check_skilltype", me);
}
/***************************************************************************
  �Դ��书����
****************************************************************************/
private void check_skilltype(string types, object me)
{
	int lvl1, lvl2;
	string sk_map;
	object weapon;
        mapping my_mkskill = ([]); // �Դ��书��Ϣ

        if (! me || ! types || types == "")
                return;

        write(types + "\n");        
        if (member_array(types, can_make) == -1)
        {
        	write("�Դ��书���಻��ȷ��\n");
        	return;
        }
        // ������
        if (member_array(types, weapon_sk) == -1)
        {
                if (me->query_temp("weapon"))
                {
                	write("�㻹���Ȱ�����ȡ�°ɣ�\n");
                	return;
                }
        }         
        else // ������
        {
                if (! objectp(weapon = me->query_temp("weapon")) ||
                    (string)weapon->query("skill_type") != types)
                {
                	write("��װ�����������ԡ�\n");
                	return;
                }
        }

        // �жϵȼ�
        lvl1 = me->query_skill(types, 1);
        sk_map = me->query_skill_mapped(types);
        lvl2 = me->query_skill(sk_map, 1);        

        if (lvl1 < 420)
        {
        	write(HIG + CHINESE_D->chinese(types) + " �ȼ����㡣\n" NOR);
        	return;
        }
        if (! stringp(sk_map))
        {
        	write(HIG "������ȼ���һ���书�� " + CHINESE_D->chinese(types) + " �ϡ�\n" NOR);
        	return;
        }
        if (lvl2 < 420)
        {
        	write(HIG + CHINESE_D->chinese(sk_map) + " �ȼ����㡣\n" NOR);
        	return;
        }
        if (me->query_skill("force") < 600 ||
            me->query_skill("parry") < 600 ||
            me->query_skill("dodge") < 600)
        {
        	write(HIG "��Ч�ڹ�����Ч�мܻ���Ч�Ṧ�ȼ����㡣\n" NOR);
        	return;
        }
        my_mkskill["types"] = types;
        write(HIG "\n�������Դ��书��Ӣ��������:wuming-jian ��\n" NOR);
        write(HIR "Ӣ�������ȱ���Ϊ10~20���ַ�֮�䣡\n" NOR);
        write(HIR "����������������������ŵ�Ӣ������һ����������ɾ����\n" NOR);
        write(HIW "Ӣ������" NOR);        
        input_to("get_skill_id", me, my_mkskill);
}
/***************************************************************************
  �Դ��书ID����Ӧ�ļ���
****************************************************************************/
private void get_skill_id(string sk, object me, mapping my_mkskill)
{
        if (! me || ! sk || sk == "")
                return;
                
        if (CHINESE_D->check_chinese(sk))
        {
        	write("����Ӣ������\n");
        	return;
        }      
        sk = filter_color(sk);
        sk = replace_string(sk, "\"", "");
        write(sk + "\n");
	if (file_size("/kungfu/skill/" + sk + ".c") != -1)
	{
		write(sk + " �Ѵ��ڣ�\n");
		return;
        }
        if (sizeof(sk) < 10 || sizeof(sk) > 20)
        {
        	write("Ӣ�������ȱ���Ϊ10~20���ַ�֮�䣡\n");
        	return;
        }
        my_mkskill["skid"] = sk;
        write(HIG "\n�������Դ��书�����������磺����������\n" NOR);
        write(HIR "����������������������ŵ���������һ����������ɾ����\n" NOR); 
        write(HIR "����������Ϊ���ֳ��ȱ���Ϊ2~8������֮�䡣\n" NOR);
        write(HIW "��������" NOR);
        input_to("get_skill_name", me, my_mkskill);
}
/***************************************************************************
  �Դ��书������
****************************************************************************/
private void get_skill_name(string skname, object me, mapping my_mkskill)
{
        if (! me || ! skname || skname == "")
                return;
                	
        write(skname + "\n");
	if (! CHINESE_D->check_chinese(skname))
	{
		write("�����书������Ϊ���ĺ��֣�\n");
		return;
	}
	if (stringp(CHINESE_D->find_skill(skname)))
	{
		write("��������Ѿ������ˣ�������ѡ��������������\n");
		return;
	}

	if (sizeof(skname) < 4 || sizeof(skname) > 32)
	{
		write("���������ȱ���Ϊ2~16������֮�䡣\n");
		return;
	}
	my_mkskill["skname"] = skname;
	write(HIG "\n��Ϊ " + HIW + skname + HIG" ָ�����µ�һ�����ԣ�\n" NOR);
	write(HIR "������(1)  �鶯��(2)  ������(3) \n" NOR);
        write(HIR "�����ͣ��нϸߵĹ��������Լ�������ЧΪ׷�ӹ����˺���\n" NOR);
        write(HIR "�鶯�ͣ��нϸߵ������ʣ��Լ�������ЧΪ�Զ����С�\n" NOR);
        write(HIR "�����ͣ�������Ϊ�м�ʱ�нϸߵķ������Լ��з�����Ч\n"
                  "�����⹥����Ч��ʹ�Է�busy���������������Ե�Ӱ�졣\n" NOR);
	write(HIW "����1~3��" NOR);
	input_to("get_skill_feature", me, my_mkskill, 0);
}
/***************************************************************************
  �Դ��书���ԣ��ɹ��ⲿ����, flagΪ0��ʾ�����һ�� 1��ʾ������ʽ
****************************************************************************/
private void get_skill_feature(string choice, object me, mapping my_mkskill, int flag)
{
	string feature;
        
        if (! me || ! choice || choice == "")
                return;

        write(choice + "\n");	
	switch(choice)
	{
		case "1":
		   feature = "dam";
		   break;
		case "2":
		   feature = "att";
		   break;
		case "3":
		   feature = "def";
		   break;
		default :
		   write("�������\n");
		   return;
	}
	my_mkskill["feature"] = feature;
	write(HIG "\n������ " HIW + my_mkskill["skname"] + HIG " ���⹥���������磺\n" NOR);
	write(HIR "$Nһ�й�����������ǧ�����ˣ�̫���ھ���ʱԴԴ����͸��$wӿ��$n���ڣ�\n" NOR);
	write(HIR "���С�$N��Ϊ�����ߣ���$n��Ϊ�����ߣ�$wΪ�������ơ�\n" NOR);
	write(HIR "����������಻����50�����֡�\n" NOR);
	write(HIG "��ѡ���书���ԣ� " HIW + skill_feature[feature] + NOR + "\n");
	write(HIW "��Ч����������" NOR);
	input_to("get_skill_hitob", me, my_mkskill, flag);	

}
/***************************************************************************
  �Դ��书���⹥����Ч����, flag --->>
****************************************************************************/
private void get_skill_hitob(string msg_hitob, object me, mapping my_mkskill, int flag)
{
	string strmsg_hitob;
        if (! me || ! msg_hitob || msg_hitob == "")
                return;

        msg_hitob = replace_string(msg_hitob, "\"", "");
        msg_hitob = filter_color(msg_hitob);
        write(msg_hitob + "\n");

	if (sizeof(msg_hitob) > 100)
	{
		write("���⹥���������Ϊ50�����֡�\n");
		return;
        }

        my_mkskill["msg_hitob"] = msg_hitob;
        my_mkskill["msg_hitob"] = 
        replace_string(my_mkskill["msg_hitob"], "$w", "\" + weapon->name() + HIR + \"");        
        switch(my_mkskill["feature"])
        {
        	case "dam":
                  strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                 "{\n\tobject weapon;\n\n\t"
                                 "weapon = me->query_temp(\"weapon\");\n\t"
                                 "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                 "ax_point())\n\t\t"
                                 "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                 "(\"qi\", (int)(damage_bonus * 2 * PMSKILLS_D->get_point(me->qu"
                                 "ery(\"pmskills/point\"))), me);\n\n\tif (damage_bonus < "
                                 "160)return 0;\n\n\tif (random(3) || me->is_busy() || me"
                                 "->query(\"neili\") < 100)return 0;\n\t"
                                 "victim->receive_wound(\"qi\", (int)(damage_bonus / 2 + "
                                 "damage_bonus * PMSKILLS_D->get_point(me->query(\"pmskill"
                                 "s/point\")) * 2), me);\n\tme->add(\"neili\", -50);\n\n\tr"
                                 "eturn HIR \"" + my_mkskill["msg_hitob"] + "\\n\" NOR;\n}\n\n";
                  break;
        	case "att":
                  strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                 "{\n\tint i, attack_time;\n\n\tobject weapon;\n\n\t"
                                 "weapon = me->query_temp(\"weapon\");\n\n\t"
                                 "attack_time = (int)(me->query_skill(\"" + my_mkskill["skid"] + 
                                 "\", 1) / 40);\n\n\tif (attack_time > 13)attack_time = 13;\n\n\t"
                                 "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                 "ax_point())\n\t\t"
                                 "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                 "(\"qi\", (int)(damage_bonus * PMSKILLS_D->get_point(me->qu"
                                 "ery(\"pmskills/point\")) / 3), me);\n\n\tif (damage_bonus < "
                                 "160 || ! living(victim))return 0;\n\n\tif (random(3) || me-"
                                 ">is_busy() || me->query_temp(\"pmskill/lian\") || me->query"
                                 "(\"neili\") < 100 )return 0;\n\t"  
                                 "message_vision(HIR \"\\n" + my_mkskill["msg_hitob"] + "\\n\" NOR,"
                                 " me, victim);\n\n\tme->start_busy(1 + random(attack_time));\n\n\t"
                                 "me->add(\"neili\", -50);\n\n\t"
                                 "me->set_temp(\"pmskill/lian\", 1);\n\t"
                                 "for (i = 0; i < attack_time; i++)\n\t"
                                 "{\n\t\tif (! me->is_fighting(victim))\n\t\t\tbreak;\n\n\t\t"
                                 "if (! victim->is_busy() && random(2))victim->start_busy(1);"
                                 "\n\n\t\tCOMBAT_D->do_attack(me, victim, weapon, 0);\n\t}\n\n\t"
                                 "me->delete_temp(\"pmskill/lian\");\n\n\treturn 1;\n\n\t"
                                 "\n}\n\n";

                 break;
               case "def":
                 strmsg_hitob = "mixed hit_ob(object me, object victim, int damage_bonus)\n"
                                "{\n\tint ap, dp;\n\tobject weapon;\n\n\t"
                                "weapon = me->query_temp(\"weapon\");\n\n\t"
                                "if (me->query(\"pmskills/point\") < PMSKILLS_D->get_m"
                                "ax_point())\n\t\t"
                                "me->add(\"pmskills/point\", 1);\n\n\tvictim->receive_wound"
                                "(\"qi\", (int)(damage_bonus * PMSKILLS_D->get_point(me->qu"
                                "ery(\"pmskills/point\")) / 3), me);\n\n\t"
                                "ap = me->query_skill(\"" + my_mkskill["types"] + "\");\n\t"
                                "dp = victim->query_skill(\"parry\");\n\n\t"
                                "if (ap / 2 + random(ap) <= dp)return 0;\n\n\t"
                                "if (! living(victim) || victim->is_busy() || random(4))return 0;\n\n\t"
                                "message_vision(HIR \"\\n" + my_mkskill["msg_hitob"] + "\\n\" NOR,"
                                " me, victim);\n\n\tme->add(\"neili\", -50);\n\n\t"
                                "victim->start_busy(2 + random(ap / 80));\n\n\t"
                                "return 0;\n}\n\n"
                                "int query_effect_parry(object attacker, object me)\n"
                                "{\n\treturn (100 + 150 * PMSKILLS_D->get_point(me->query("
                                "\"pmskills/point\")));\n}\n\n";
                 break;
              default: return;
        }
	write(HIG "\n������ " HIW + my_mkskill["skname"] + HIG " ��������������磺\n" NOR);
	write(HIR "����$n�������ܣ��ٽ������ʹ�������両�ࡹ����$N���󣬵����˴��С�\n" NOR);
	write(HIR "ע�⣺����$n�����Լ���$N����Է���$l����Է����岿λ����ϵͳ�����﷨��飬\n����"
	          "���ϸ�ذ��ոø�ʽ���룬�������Ը���\n" NOR);
	write(HIR "�м���������Ϊ�������ҳ��Ȳ�����40�����֡�\n" NOR);
	write(HIW "�����������һ��" NOR);
        input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);

}
/***************************************************************************
  �Դ��书����������� ����  flag --->>
****************************************************************************/
private void get_skill_validdamage(string validdamage_msg, object me, mapping my_mkskill, 
                                  string strmsg_hitob, int flag)
{
        if (! me || ! validdamage_msg || validdamage_msg == "")
                return;

        validdamage_msg = replace_string(validdamage_msg, "\"", "");
        validdamage_msg = filter_color(validdamage_msg);
        write(validdamage_msg + "\n");

	if (sizeof(validdamage_msg) > 80)
	{
		write("��������������ȱ���С��40�����֡�\n");
		return;
        }
        if (! stringp(my_mkskill["validdamage_msg1"]))
        {
                my_mkskill["validdamage_msg1"] = validdamage_msg;
	        write(HIW "���������������" NOR);           
                input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else if (! stringp(my_mkskill["validdamage_msg2"]))
        {
                my_mkskill["validdamage_msg2"] = validdamage_msg;
	        write(HIW "���������������" NOR);                
                input_to("get_skill_validdamage", me, my_mkskill, strmsg_hitob, flag);
                return;        	
        }
        else if (! stringp(my_mkskill["validdamage_msg3"]))
        {
                my_mkskill["validdamage_msg3"] = validdamage_msg;
	        write(HIG "\n������ " HIW + my_mkskill["skname"] + HIG " һ����ʽ���ƣ��磺�з����� ��\n" NOR);
	        write(HIR "��ʽ���Ʊ���Ϊ�������ҳ��ȱ���Ϊ2~8������֮�䡣\n" NOR);
	        write(HIW "��ʽ���ƣ�" NOR);
	        input_to("get_skill_action_name", me, my_mkskill, strmsg_hitob, flag);  
                return;
        }
        else    return;        
      
}
/***************************************************************************
  �Դ��书��ʽ��, �����ڵ�һ�δ����书�ͺ���������ʽʹ�ú���  flag --->>
****************************************************************************/
public void get_extern_action_name(object me, string ctsk)
{
	mapping my_mkskill = ([]);
	
	write(HIG "\n������ " HIW + CHINESE_D->chinese(ctsk) + HIG " һ����ʽ���ƣ��磺�з����� ��\n" NOR);
	write(HIR "��ʽ���Ʊ���Ϊ�������ҳ��ȱ���Ϊ2~8������֮�䡣\n" NOR);
	write(HIW "��ʽ���ƣ�" NOR);
	input_to("get_skill_action_name", me, my_mkskill, 0, 1, ctsk);
	
}
public void get_skill_action_name(string action_skname, object me, mapping my_mkskill, 
                                  string strmsg_hitob, int flag, string ctsk)
{
        if (! me || ! action_skname || action_skname == "")
                return;

        write(action_skname + "\n");
	if (! CHINESE_D->check_chinese(action_skname))
	{
		write("������ʽ������Ϊ���ĺ��֣�\n");
		return;
	}
	if (sizeof(action_skname) < 4 || sizeof(action_skname) > 32)
	{
		write("��ʽ���Ƴ��ȱ���Ϊ2~16������֮�䡣\n");
		return;
	}
	my_mkskill["action_skname"] = action_skname;
	write(HIG "\n��������ʽ " HIW + action_skname + HIG " ����������ʽ���£�\n" NOR);
	write(HIR "$N����$wбָ��һ��$NM������һ�٣�һ����$n��$l��ȥ��\n" NOR);
	write(HIR "����$N��$n�ֱ�������ߺ������ߣ�$w�������߱�����$l����������\n"
	          "���岿λ��$NM������е���ʽ����(��ʡ��)����ϵͳ�����﷨��飬����\n"
	          "���ϸ�ذ��ոø�ʽ���룬�������Ը���\n" NOR);
	write(HIR "��ʽ��������Ϊ�������ҳ��Ȳ�����40�����֡�\n" NOR);
	write(HIW "��ʽ������" NOR);
	input_to("get_skill_action_desc", me, my_mkskill, strmsg_hitob, flag, ctsk);
}
/***************************************************************************
  �Դ��书��ʽ���� flag --->>
****************************************************************************/
private void get_skill_action_desc(string action_desc, object me, mapping my_mkskill, 
                                   string strmsg_hitob, int flag, string ctsk)
{
        if (! me || ! action_desc || action_desc == "")
                return;
        
        action_desc = replace_string(action_desc, "\"", action_desc);
        action_desc = filter_color(action_desc);
        write(action_desc + "\n");

	if (sizeof(action_desc) > 80)
	{
		write("��ʽ�������ȱ���С��40�����֡�\n");
		return;
        }
        action_desc = replace_string(action_desc, 
                                     "$NM", 
                                     "��" + my_mkskill["action_skname"] + "��");
        my_mkskill["action_desc"] = action_desc;

        // ������ʽ
        if (flag)
        {
              create_actions(me, 
                             my_mkskill["action_skname"], 
                             my_mkskill["action_desc"],
                             ctsk);
              return;
        }
        
	write(HIG "\n��������ʽ " HIW + my_mkskill["skname"] + HIG " �����м���������ʽ���£�\n" NOR);
	write(HIR "$n���˷�����ʹ����ɽ���С�������롹��ɭɭ�����������ܣ��ܿ���$N�����С�\n" NOR);
	write(HIR "$n�������ܣ��ٽ������ʹ�������両�ࡹ����$N��$l���뵲�����С�\n" NOR);
	write(HIR "ע�⣺����$n�����Լ���$N����Է���$l����Է����岿λ����ϵͳ�����﷨��飬\n����"
	          "���ϸ�ذ��ոø�ʽ���룬�������Ը�����������֧��$w����������\n" NOR);
	write(HIR "�м���������Ϊ�������ҳ��Ȳ�����40�����֡�\n" NOR);
	write(HIW "�м�����һ��" NOR);
	input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
}
/***************************************************************************
  �Դ��书��ʽ�м����� һ������ flag --->>
****************************************************************************/
private void get_skill_parrymsg(string parry_msg, object me, mapping my_mkskill, 
                                string strmsg_hitob, int flag)
{
        if (! me || ! parry_msg || parry_msg == "")
                return;

        parry_msg = replace_string(parry_msg, "\"", "");
        parry_msg = filter_color(parry_msg);
        write(parry_msg + "\n");

	if (sizeof(parry_msg) > 80)
	{
		write("��ʽ�������ȱ���С��40�����֡�\n");
		return;
        }
        if (! stringp(my_mkskill["parry_msg1"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg1"] = parry_msg;
	        write(HIW "�м���������" NOR);                
                input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else if (! stringp(my_mkskill["parry_msg2"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg2"] = parry_msg;
	        write(HIW "�м���������" NOR);                
                input_to("get_skill_parrymsg", me, my_mkskill, strmsg_hitob, flag);
                return;        	
        }
        else if (! stringp(my_mkskill["parry_msg3"]))
        {
        	parry_msg = replace_string(parry_msg, "$w", "");
                my_mkskill["parry_msg3"] = parry_msg;
                modify_file(me, my_mkskill, strmsg_hitob, flag);
                return;
        }
        else    return;
}

/***************************************************************************
  ��Ϣ�ռ���ϣ������书
****************************************************************************/
private void modify_file(object me, mapping my_mkskill, string strmsg_hitob, int flag)
{
	string strtmp;
	string sk_map;
        string msg_validdamage;
        mapping basic_actions = ([]); // �����书��Ϣ
        
        write(my_mkskill["parry_msg1"] + "\n");
        write(my_mkskill["parry_msg2"] + "\n");
        write(my_mkskill["parry_msg3"] + "\n");      
        
	sk_map = me->query_skill_mapped(my_mkskill["types"]);
	
	if (! stringp(sk_map))
	{
		write("�������Ϊ " + my_mkskill["types"] + " ����һ�������书��\n");
		return;
	}
	basic_actions = ("/kungfu/skill/" + sk_map)->query_action(me);
	
	if (! mapp(basic_actions) || ! sizeof(basic_actions))
	{
		write("��ȡ�书�ļ� " + sk_map + " ʧ�ܡ�\n");
		return;
	}
	// �����Դ��书���Ը�������
	switch(my_mkskill["feature"])
	{
		case "dam":
		   basic_actions["force"] += (basic_actions["force"] * 2 / RATE); 
		   basic_actions["damage"] += (basic_actions["damage"] * 2 / RATE);
		   break;

		case "att":
		   basic_actions["attack"] += (basic_actions["attack"] * 2 / RATE); 

		case "def":
		   basic_actions["parry"] += (basic_actions["parry"] * 2 / RATE);
		   break;

		default :
		   break;
	}

       msg_validdamage = "mixed valid_damage(object ob, object me, int damage, object weapon)\n"
                         "{\n\tmixed result;\n\tint ap, dp, mp;\n\tobject m_weapon;\n\n\t";
                          
       // ������
       if (member_array(my_mkskill["types"], weapon_sk) != -1)
       {
             msg_validdamage += "if ((int) me->query_skill(\"" + my_mkskill["skid"] + "\", 1) < 300\n\t"
                                "|| ! (m_weapon = me->query_temp(\"weapon\"))\n\t"
                                "|| ! living(me)\n\t"
                                "|| m_weapon->query(\"skill_type\") != \"" + my_mkskill["t"
                                   "ypes"] + "\")\n\t\treturn;\n\n\t";
             my_mkskill["validdamage_msg1"] = 
             replace_string(my_mkskill["validdamage_msg1"], "$w", "\" + m_weapon->name() + HIC + \"");
             my_mkskill["validdamage_msg2"] = 
             replace_string(my_mkskill["validdamage_msg2"], "$w", "\" + m_weapon->name() + HIC + \"");
             my_mkskill["validdamage_msg3"] = 
             replace_string(my_mkskill["validdamage_msg3"], "$w", "\" + m_weapon->name() + HIC + \"");
                                   
       }
       else
       {
             msg_validdamage += "if ((int)me->query_skill(\"" + my_mkskill["skid"] + "\", 1) < 300\n\t"
                                " || ob->query_temp(\"weapon\")\n\t || ! living(me))\n\t\t"
                                "return;\n\n\t";
             my_mkskill["validdamage_msg1"] =                                 
             replace_string(my_mkskill["validdamage_msg1"], "$w", "");
             my_mkskill["validdamage_msg2"] = 
             replace_string(my_mkskill["validdamage_msg2"], "$w", "");
             my_mkskill["validdamage_msg3"] = 
             replace_string(my_mkskill["validdamage_msg3"], "$w", "");
       }

       msg_validdamage += "ap = me->query_skill(\"" + my_mkskill["skid"] + "\", 1)";
       if (my_mkskill["feature"] == "def")
               msg_validdamage += " + 50 + 100 * PMSKILLS_D->get_point(me->query(\"pmskills/"
               "point\"));\n\n\t";
       else    msg_validdamage += ";\n\n\t";

       msg_validdamage += "dp = ob->query_skill(\"force\", 1) + ob->query_dex() / 2;\n\n\t";
 
       if (my_mkskill["feature"] != "def")
       {
               msg_validdamage += "if (ob->query_skill(\"count\", 1) > 100)return;\n\n\t";
       }
       msg_validdamage += "if (ap / 2 + random(ap) < dp)\n\t{\n\t\t"
                          "result = ([ \"damage\": -damage ]);\n\t\t"
                          "switch (random(3))\n\t\t{\n\t\t"
                          "case 0:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg1"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\tcase 1:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg2"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\tdefault:\n\t\t   result += ([\"msg\" : HIC \"" + 
                          my_mkskill["validdamage_msg3"] + "\\n\" NOR]);\n\t\t"
                          "break;\n\t\t}\n\t\treturn result;\n\t}\n\n}\n\n";

	// �ٴ�����
	basic_actions["force"] += (basic_actions["force"]  / RATE);
	basic_actions["damage"] += (basic_actions["damage"] / RATE);
	basic_actions["attack"] += (basic_actions["attack"] / RATE);
	basic_actions["dodge"] += (basic_actions["dodge"]  / RATE);
	basic_actions["parry"] += (basic_actions["parry"]  / RATE);

	// ��һ���Դ��书
	if (! flag)
	{
	      // д��ͷ��Ϣ���������ļ�
	      strtmp =  "//      �׻�-����Դ��书ϵͳ\n";
	      strtmp += "//      Made at " + MEMBER_D->bjtime(time(), 1) + " by Rcwiz\n";
	      strtmp += "//      " + SK_FILE + ".c" + "  " + my_mkskill["skname"] + "\n\n";
	      strtmp += "inherit SKILL;\n#include <ansi.h>\n\n";
	      strtmp += "#define PMSKILLS_D        \"/adm/daemons/pmskillsd\"\n\n";

	      strtmp += "string *parry_msg = ({\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg1"] + "\\n\" NOR,\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg2"] + "\\n\" NOR,\n";
	      strtmp += "HIG \"" + my_mkskill["parry_msg3"] + "\\n\" NOR,\n";
	      strtmp += "});\n\n";
              strtmp += "string query_parry_msg(object weapon)\n";
              strtmp += "{\n\treturn parry_msg[random(sizeof(parry_msg))];\n}\n\n";
	      strtmp += "int playermake(){ return 1; }\n";
	      strtmp += "string who_make(){ return \"" + me->query("id") + "\"; }\n\n";

	      if (! write_file(SK_FILE + ".c", strtmp, 1))
	      {
	      	   write("�����ļ�ʧ�ܣ�\n");
	      	   return;
	      }
	      // action���� �ɱ���Ϣ
	      strtmp =  "//####actions start####\n";
	      strtmp += "mapping *action = ({\n";
	      strtmp += "([\t\"action\"     :  \"" + my_mkskill["action_desc"] + "\",\n";
	      strtmp += "  \t\"force\"      :  " + basic_actions["force"] + ",\n";
	      strtmp += "  \t\"attack\"     :  " + basic_actions["attack"] + ",\n";
	      strtmp += "  \t\"parry\"      :  " + basic_actions["parry"] +  ",\n";
	      strtmp += "  \t\"dodge\"      :  " + basic_actions["dodge"] + ",\n";
	      strtmp += "  \t\"damage\"     :  " + basic_actions["damage"] + ",\n";  
	      strtmp += "  \t\"skill_name\" :  \"" + my_mkskill["action_skname"] + "\",\n";                          
	      strtmp += "  \t\"damage_type\":  \"" + 
	                damage_type[my_mkskill["types"]] + "\",\n";
	      strtmp += "])\n});\n";
	      strtmp += "//####actions end####\n\n";
	      strtmp += "mixed get_actions(){ return action;}\n\n";
	      strtmp += "mixed get_actnames()\n{\n\tint i;\n\n\tstring *names;\n\n\t"
	                "names = ({});\n\n\t"
	                "for (i = sizeof(action) - 1; i >= 0; i--)\n\t\t"
	                "names += ({action[i][\"skill_name\"]});\n\n\t"
	                "return names;\n}\n\n";

	      // enable����
	      strtmp += "int valid_enable(string usage)\n";
	      strtmp += "{\n\treturn usage == \"" + my_mkskill["types"] + "\" || "
	                "usage == \"parry\";\n}\n\n";

	      // ���� mapping query_action(object me, object weapon)
	      if (my_mkskill["feature"] == "att")
	      {
	      strtmp += "mapping query_action(object me, object weapon)\n"
                        "{\n\tmapping act;\n\n\t"
                        "act = action[random(sizeof(action))];\n\n\t"
                        "act[\"attack\"] = \n\t"
                        "act[\"attack\"] + 50 + act[\"attack\"] * PMSKILLS_D->get"
                        "_point(me->query(\"pmskills/point\"));\n\n\t"
                        "return act;\n}\n\n";
              }
              else 
              {
              strtmp += "mapping query_action(object me, object weapon)\n"
                        "{\n\treturn action[random(sizeof(action))];\n}\n\n";
              }

              // ���� valid_learn(object me)
              // ������skill
              if (member_array(my_mkskill["types"], weapon_sk) != -1)
              {
                        strtmp += "int valid_learn(object me)\n"
                        "{\n\tobject ob;\n\tif (! (ob = me->query_temp(\"we"
                        "apon\"))\n\t||  (string)ob->query(\"skill_type\") != "
                        "\"" + my_mkskill["types"] + "\")\n\t\treturn notif"
                        "y_fail(\"��ʹ�õ��������ԡ�\\n\");\n\tif (me->query_ski"
                        "ll(\"" + my_mkskill["types"] + "\", 1) < me->query"
                        "_skill(\"" + my_mkskill["skid"] + "\", 1))\n\t\tretu"
                        "rn notify_fail(\"���" + 
                        CHINESE_D->chinese(my_mkskill["types"]) + 
                        "������ޣ��޷����������" + my_mkskill["skname"] + 
                        "��\\n\");\n\treturn 1;\n}\n\n";
               }
               else // ������skill
               {
                        strtmp += "int valid_learn(object me)\n"
                        "{\n\tobject ob;\n\tif (me->query_temp(\"we"
                        "apon\")\n\t|| me->query(\"secondary_weapon\"))\n\t\treturn notif"
                        "y_fail(\"����������ϰ��\\n\");\n\tif (me->query_ski"
                        "ll(\"" + my_mkskill["types"] + "\", 1) < me->query"
                        "_skill(\"" + my_mkskill["skid"] + "\", 1))\n\t\tretu"
                        "rn notify_fail(\"���" + 
                        CHINESE_D->chinese(my_mkskill["types"]) + 
                        "������ޣ��޷����������" + my_mkskill["skname"] + 
                        "��\\n\");\n\treturn 1;\n}\n\n";               	
               }

               // ����query_skill_name(int level)
               strtmp += "string query_skill_name(int level)\n"
                         "{\n\tint i;\n\tfor (i = sizeof(action"
                         ")-1; i >= 0; i--)\n\t\tif (level >= ac"
                         "tion[i][\"lvl\"])\n\t\t\treturn action"
                         "[i][\"skill_name\"];\n}\n\n";

               // ����int double_attack(){ return 1; }
               strtmp += "int double_attack(){ return 1; }\n\n";

               // ����mixed hit_ob(object me, object victim, int damage_bonus)
               strtmp += strmsg_hitob;

               // ����mixed valid_damage(object ob, object me, int damage, object weapon)
               strtmp += msg_validdamage;

               // ����int practice_skill(object me)
               strtmp += "int practice_skill(object me)\n"
                         "{\n\treturn notify_fail(\"�Դ���ѧֻ����"
                         "ѧ(learn)���������ȼ���\\n\");\n}\n\n";

               // ����int difficult_level()
               strtmp += "int difficult_level(){ return 2000;}\n\n";

               // ����string perform_action_file(string action)
               strtmp += "string perform_action_file(string action)\n"
                         "{\n\treturn __DIR__\"" + my_mkskill["skid"] + 
                         "/\" + action;\n}\n\n";

	       write_file(SK_FILE + ".c", strtmp, 0);
	}
	// ��ӵ����Ŀ�
	CHINESE_D->add_translate(my_mkskill["skid"], my_mkskill["skname"]);
	
	// �趨�ȼ�
	me->set_skill(my_mkskill["skid"], me->query_skill(sk_map, 1) - 120);

	// ��¼dbase����
	me->set("pmskills/create_time", time());
	me->set("pmskills/types", my_mkskill["types"]);
	me->set("pmskills/feature", skill_feature[my_mkskill["feature"]]);
	me->set("pmskills/skid", my_mkskill["skid"]);
	me->set("pmskills/point", 0);
	
	// �۳�Ǳ��
	me->add("potential", -1 * CND_POT_1);
	
	// ����perform�ļ���
	mkdir("/kungfu/skill/" + my_mkskill["skid"]);
	
	// ������Ϣ����¼
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) + HIM + 
	           "����������ѧ " + HIW + my_mkskill["skname"] + HIM + "���Ӵ�����"
	           "������\n" NOR);

	log_file("/static/pmsk", me->query("id") + " created skill " + 
	         my_mkskill["skname"] + "(" + my_mkskill["skid"] + ") on " +
	         MEMBER_D->bjtime(time(), 1) + "\n");

	write(HIG "�Դ��书�ɹ���\n" NOR);
	write(HIG "�Ժ���ʹ�� " HIR "pmsk show �书Ӣ����" HIG " �鿴�Դ��书��ϸ���ݡ�\n" NOR);

	return;

}
/***************************************************************************
  ��Ϣ�ռ���ϣ�������ʽ
****************************************************************************/
public int create_actions(object me, string skname, string desc, string ctsk)
{
	mapping *acts, act;
	string strFile, strtmp;
	string sFile;
	int iSize, iItem, i;
	object obj;
	

	sFile = "/kungfu/skill/" + ctsk;
	if (me->add("potential", 0) < CND_POT_1)
	{
		write("��Ǳ�ܲ������޷������µ���ʽ��\n");
		return 0;
	}
	if (! MEMBER_D->is_valib_member(me->query("id")))
	{
		write("�Բ����Դ��书ϵͳֻ����Ч��Ա���š�\n");
		return 0;		
        }
	if (file_size(sFile + ".c") == -1)
	{
		write("δ�ҵ�ָ���ļ���\n");
		return 0;
	}	
	
	acts = sFile->get_actions();

        if (sizeof(acts) >= 10)
        {
        	write("�Դ��书���ֻ�ܴ���ʮ����ʽ��\n");
        	return 0;
        }
	i = 1;
	strFile = "";
	while(1)
	{
		strtmp = read_file(sFile + ".c", i, 1);
		strFile += strtmp;
		if (strtmp == "//####actions start####\n")break;
	        i ++;
	        if (i > 100)
	        {
	      	    write("��ȡ�ļ�����\n");
	      	    return 0;
	        }
	}

        iSize = sizeof(acts);
        if (! acts || ! iSize )
        {
        	write("actions ������Ч��\n");
        	return 0;
        }
        
        strtmp = "";
        strFile += "mapping *action = ({\n";

        for (iSize = 0; iSize < sizeof(acts); iSize ++)
        {
              act = acts[iSize];
	      strtmp += "([\t\"action\"     :  \"" + act["action"] + "\",\n";
	      strtmp += "  \t\"force\"      :  " + act["force"] + ",\n";
	      strtmp += "  \t\"attack\"     :  " + act["attack"] + ",\n";
	      strtmp += "  \t\"parry\"      :  " + act["parry"] +  ",\n";
	      strtmp += "  \t\"dodge\"      :  " + act["dodge"] + ",\n";
	      strtmp += "  \t\"damage\"     :  " + act["damage"] + ",\n";  
	      strtmp += "  \t\"skill_name\" :  \"" + act["skill_name"] + "\",\n";                          
	      strtmp += "  \t\"damage_type\":  \"" + act["damage_type"] + "\",\n";
	      strtmp += "]),\n";
        }
        strFile += strtmp;
        
        strtmp = "";
        act["force"]  += random(10);
        act["damage"] += random(10);
        act["attack"] += random(10);                
        act["dodge"]  += random(10);
        act["parry"]  += random(10);
        
        strtmp += "([\t\"action\"     :  \"" + desc + "\",\n";
	strtmp += "  \t\"force\"      :  " + act["force"] + ",\n";
	strtmp += "  \t\"attack\"     :  " + act["attack"] + ",\n";
	strtmp += "  \t\"parry\"      :  " + act["parry"] +  ",\n";
	strtmp += "  \t\"dodge\"      :  " + act["dodge"] + ",\n";
	strtmp += "  \t\"damage\"     :  " + act["damage"] + ",\n";  
	strtmp += "  \t\"skill_name\" :  \"" + skname + "\",\n";                          
	strtmp += "  \t\"damage_type\":  \"" + act["damage_type"] + "\",\n";
	strtmp += "]),\n";

        strFile += strtmp;      
        strFile += "});\n//####actions end####\n";

        strtmp = "";
        while(1)
        {
        	strtmp = read_file(sFile + ".c", i, 1);
        	i ++;
        	if (strtmp == "//####actions end####\n")break;
        }
        strtmp = "";
        while(1)
        {
        	strtmp = read_file(sFile + ".c", i, 1);
        	if (! strtmp)break;
                strFile += strtmp;
                i ++;
        }

        if (! write_file(sFile + ".c", strFile, 1))
        {
        	write("д���ļ�ʧ�ܣ�\n");
        	return 0;        	
        }
        if (obj = find_object(sFile))destruct(obj);

        me->add("potential", -1 * CND_POT_1);
        write("�����ɹ���\n");
        
        return 1;
}
/***************************************************************************
  �ⲿ���ã���ʾ�Դ��书��ϸ����
****************************************************************************/
public show_pmsk(object me, string skid)
{
	mapping *acts;
	string *actnames;
	mapping performs;
	int i;
	
	//acts = ("/kungfu/skill/" + skid)->get_actions();
	actnames = ("/kungfu/skill/" + skid)->get_actnames();

	performs = me->query("pmskills/perform");

	write(BBLU + HIW "\t\t �׻�Ӣ��ʷ�Դ��书ϵͳ��������\t\t   " + VERSION + " \n" NOR);
        write(HIW "��---------------------------------------------------------------��\n" NOR);
        //�书id�� �书����������ʽ��Ŀ����ʽ���ƣ�������Ŀ���������ƣ�������
        write(HIY "WELCOME TO USE PMSK SYSTEM OF YHHERO AND HOPE YOU ALL GOES WELL.\n\n" NOR);
        write(sprintf(HIC "  �书���ţ�%-25s�������ƣ�%s\n" NOR, 
                      skid, 
                      CHINESE_D->chinese(skid)));
        write(sprintf(HIC "  �书���ԣ�%-25s�书���ԣ�%s\n" NOR, 
                      me->query("pmskills/types"), 
                      me->query("pmskills/feature")));                 
        write(sprintf(HIC "  ����ʱ�䣺%-25sĿǰ�ȼ���%d\n" NOR, 
                      MEMBER_D->bjtime(me->query("pmskills/create_time"), 1), 
                      me->query_skill(skid, 1)));     
        write(sprintf(HIC "  ��ʽ������%-25d����������%d\n" NOR, 
                      sizeof(actnames),
                      sizeof(performs)));
        write(sprintf(HIY "\n  �����ȣ�%.1f ��\n\n" NOR,
                      get_point2(me->query("pmskills/point") * 100)));

        write(HIC "  ��ʽ�б�\n" NOR);
        write(HIC "  ������������\n" NOR);
        for (i = 0; i < sizeof(actnames); i ++)
        {
              if (i % 2 == 0)write(sprintf(HIM "  %-35s" NOR, actnames[i]));
              else write(sprintf(HIM "%s\n" NOR, actnames[i])); 
        }
        if (i % 2)write("\n");
        write(HIC "\n  �����б�\n" NOR);
        write(HIC "  ������������\n" NOR);                
        for (i = 0; i < sizeof(performs); i ++)
        {
              if (i % 2 == 0)write(sprintf(HIM "  %-35s" NOR, performs[i]));
              else write(sprintf(HIM "%s\n" NOR, performs[i])); 
        }
        write(HIG "\n  *��ʹ��" HIR " pmsk ? " HIG " �鿴pmskָ���ʹ�÷�����\n\n" NOR);
        write(HIR "  *Ϊ�����������Ҫ���鷳�������Ķ��Դ��书�����ļ� " HIY "help pmskills\n\n" NOR);
        write(HIY "                (" HIR"Y��H" HIY ").YHHERO WIZARD GROUP http://yhhero."
              "vicp.net\n" NOR);
        write(HIW "��---------------------------------------------------------------��\n" NOR);
}
/***************************************************************************
  �ⲿ���ã���ȴ�Դ��书��ɾ����
****************************************************************************/
public int forget_pmsk(object me, string ctsk)
{
	object obj;

	obj = find_object("/kungfu/skill/" + ctsk);

	CHINESE_D->remove_translate(ctsk);
	me->delete_skill(ctsk);
	rm("/kungfu/skill/" + ctsk + ".c");
	"/cmds/wiz/rm"->rm_dir("/kungfu/skill/" + ctsk);
	me->delete("pmskills");

	if (obj)destruct(obj);
	me->save();
	write("OK.\n");

	return 1;
}
/***************************************************************************
  �ⲿ���ã���ʾ�����Դ��书
****************************************************************************/
public mixed show_all_pmsk(object me)
{
	mixed file;
	string *pmsk;
	int i, size;
	object obj;
	string fname;
	
	file = get_dir("/kungfu/skill/", -1);
	
	pmsk = ({});
        
	for(i = 0; i < sizeof(file); i ++)
	{
		fname = file[i][0];
		size = sizeof(fname);
		
		if (file_size("/kungfu/skill/" + fname) == -1 ||
		    file_size("/kungfu/skill/" + fname) == -2)
		       continue;
                
		if (fname[size - 2..size] != ".c")
		       continue;

		if (("/kungfu/skill/" + fname)->playermake())
		       pmsk += ({ file[i][0] });		
	}
	if (! sizeof(pmsk))
	{
		write("Ŀǰϵͳ�����Դ��书��\n");
		return 0;
	}
	write(HIY "ϵͳ�е��Դ��书�б�\n" NOR);
	write(sprintf(HIG "%-30s%-30s%-30s\n" NOR,
	              "�书����", "��������", "������"));
	write(HIW "--------------------------------------------------------"
	      "---------------\n" NOR);	
	for (i = 0; i < sizeof(pmsk); i ++)
	{
	       write(sprintf(HIC "%-30s%-30s%-30s\n" NOR,
	                     pmsk[i][0..sizeof(pmsk[i]) - 3],
	                     CHINESE_D->chinese(pmsk[i][0..sizeof(pmsk[i]) - 3]),
	                     ("/kungfu/skill/" + pmsk[i])->who_make()));	       
        }
        write(HIW "---------------------------------------------------------"
              "--------------\n" NOR);
	return 1;
}