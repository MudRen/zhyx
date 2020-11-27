// qingfu-shenfa.c ������
// by jeeny
// modify by xiner 02/3/2009
 
#include <ansi.h> 
      
inherit SKILL; 
        
string *dodge_msg = ({
	"ֻ��$nһ�С�����Ǭ���������ζ�Ȼ���𣬶����$N��һ�С�\n",
	"$nһʽ���������١������λζ�����һ��Ʈ�����ܿ���$N��һ�С���\n"
	"$nʹ�������츣�ء���һ�����Ľ��󷭳����ܿ���$N���������ơ�\n",
	"$nһ�С��������𡹣�������ת��$Nֻ����ǰһ����$n������$N�����\n",
        "$N��һ���ۿ���Ҫ���У�����$n��һ�����ܹ�$N�ľ�����ʵ��������˼��\n", 
        "$n���˷�������$N���������ǡǡ�ܿ���һ�С�\n", 
}); 
       
int valid_enable(string usage)  
{  
        return usage == "dodge"; 
} 
       
int valid_learn(object me) 
{ 
        int lvl; 
       
        lvl = me->query_skill("qingfu-shenfa", 1); 
        if (lvl > 300) lvl = 300;
       
        if (me->query("max_neili") < 2000 + lvl * 10) 
                return notify_fail("���������Ϊ��Ƿ���\n");
 
        if (me->query("dex") < 26)
		return notify_fail("�����ʲ���,ѧ������˸�����Ṧ��\n");

	if ((!me->query("reborn")&&me->query("str") > 25)||
		(me->query("reborn")&&me->query("str") > 35))
               	return notify_fail("��ʵ��̫���أ��޷�ѧϰ�����ӯ�Ĳ�����\n");

        if (me->query("static/sadly") > 2)
                return notify_fail("��ֻ������һ��������Ϯ�������������������ˮƽ��\n"); 

        return 1; 
} 
       
string query_dodge_msg(string limb) 
{ 
        return dodge_msg[random(sizeof(dodge_msg))]; 
} 
       
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp; 
       
	if ((int)me->query_skill("qingfu-shenfa", 1) < 100 ||
		me->query_skill_mapped("dodge") != "qingfu-shenfa" ||
		me->query("family/family_name") != "����" || 
            ! living(me)) 
                return; 
        
        ap = ob->query_skill("dodge"); 
        dp = me->query_skill("dodge", 1) / 2 + 
             me->query_skill("qingfu-shenfa", 1); 

        if (ap / 2 + random(ap) < dp * 4 / 5) 
        { 
                result = ([ "damage": -damage ]); 
       
                switch (random(5)) 
                { 
                case 0: 
                        result += (["msg" : HIB "����$n" HIB "��¶΢Ц������һ�죬$N" 
                                            HIB "ֻ����ǰһ�����ƺ�������ǧ�ٸ�$n��" 
                                            HIB "��Ӱ��\n" NOR]); 
                        break; 
                case 1: 
                        result += (["msg" : HIB "$N" HIB "ֻ����ǰһ����Ӱ��һ��һ�Σ�"
                                            HIB "��ʱ������$n����Ӱ��\n" NOR]); 
                        break; 
                case 2: 
                        result += (["msg" : HIB "����$n" HIB "����һ������󵹷ɳ�ȥ��$N" 
                                            HIB "�����͹���ȴ�ּ�$n" HIB "һ��ɲ������ת" 
                                            "$N��󣬵������˷�����˼��\n" NOR]); 
                case 3:
                        result += (["msg" : HIB "ֻ��$n" HIB "��Хһ������һֻ��"
                                            "��һ����������ڰ�յ�����$N" HIB 
                                            "����ȴ���˸��ա�\n" NOR]);
                        break;
		default:
                        result += (["msg" : HIB "����$n" HIB "����ӯ�ޱȣ���ȻԾ"
                                    "�ߺ������£���$N" HIB "��ȫ�޴ӹ�����\n" NOR]);
                        break;
                        break; 
                } 
                return result; 
        }
 
} 
      
int query_effect_dodge(object attacker, object me)
{
	if (me->query("family/family_name") != "����")
	{return 10;}
	else
	{
        int lvl;
        lvl = me->query_skill("qingfu-shenfa", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 70;
        if (lvl < 250) return 90;
        if (lvl < 300) return 100;
        return 110;
	}
}
      
int practice_skill(object me) 
{ 
	int cost;
	cost = 60 + (int) me->query_skill("qingfu-shenfa", 1) / 3;

        if (me->query_skill("qingfu-shenfa", 1) > 100
	   && me->query("family/family_name") != "����")
                return notify_fail("û��ΤһЦ��ָ�㣬�㲻�����׶�����������\n");

        if ((int)me->query("qi") < 70) 
                return notify_fail("�������̫���ˣ�������ϰ��������\n"); 
     
        if ((int)me->query("neili") < cost) 
                return notify_fail("������������ˣ��޷���ϰ��������\n"); 
      
        me->receive_damage("qi", 50); 
        me->add("neili", -cost); 
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"qingfu-shenfa/" + action; 
} 

void skill_improved(object me)
{
        int lvl;
        int lvl2;
        lvl = me->query_skill("qingfu-shenfa", 1);
        lvl2 = me->query_skill("jiuyang-shengong", 1);

        if (lvl > 100 && lvl2 < lvl)
        {
                me->apply_condition("bianfu-except", lvl / 2 +
                                    (int)me->query_condition("bianfu-except"));
        }
}