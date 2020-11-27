// zhuangzi-wu.c ׯ����
// updated by kasumi,2008.6.16

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "����$n����΢΢һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
        "$n����΢�Σ��о����յرܿ���$N��һ�С�\n",
        "$n���������������Ī�⣬��$N��һ��û�з����κ����á�\n",
        "$n�Թ��Ե��߳���������Ȼ����$N���й���δ���\n",
        "$N��һ���ۿ���Ҫ���У�����$n���Ա�һ�ã�ȥ��֮�ʵ���Ƿ�����˼��\n",
        "$n��ǰһ������Ȼ���ˣ�ǡǡ�ܿ�$N��һ�У��о����ա�\n",
});

int valid_enable(string usage) 
{ 
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("zhuangzi-wu", 1);
        if (lvl > 300) lvl = 300;
        	
       /* if ((string)me->query("gender") != "Ů��") 
        	return notify_fail("ׯ����������������֮��������ο�����ϰ��\n"); */

        if (me->query("dex") < 36 && me->query("family/family_name") != "�컨��")
                return notify_fail("��������̫��޷�ѧϰׯ���衣\n");
                
         if (me->query("dex") < 26 && me->query("family/family_name") == "�컨��")
                return notify_fail("��������̫��޷�ѧϰׯ���衣\n");

        if (me->query("max_neili") < 2400 + lvl * 15)
                return notify_fail("�㰴��ׯ������ʾ�Ĳ��������������£���ʱ"
                                   "ֻ��ͷ��Ŀѣ���������������á�\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("zhuangzi-wu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;       
        if (me->query("family/family_name") != "�컨��")
        	dp = me->query_skill("dodge")* 3/4;
       	else
       		dp = me->query_skill("dodge");
		

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : MAG "ֻ��$n" MAG "����ڵ�������һ�㣬������"
                                            "�Ӷ�ʱ���Ʈ������׾ٶ㿪��$N" MAG "����"
                                            "ʽ��\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : MAG "����$n" MAG "����΢΢һ����������������"
                                            "��ˮ����ƮƮ������һ�ԣ���ʱʹ$N" MAG "�Ĺ�"
                                            "����ա�\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : MAG "����$n" MAG "΢΢һЦ��������չ��������"
                                            "��̤��Ʈ�𣬴�$N" MAG "һ�л��պ��������"
                                            "�䣬����$N" MAG "��ǰ��\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "��$n" MAG "��˿�������$N" MAG "��������"
                                            "����ӭ�汼�ϣ��ó�����ٻӰ�������裬$N" MAG
                                            "����͸��ʵ��Ψ�����С�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "ֻ��$n" HIY "��������棬���ƮȻ��"
                                 "�𣬿�$N" HIY "��Ӱ���٣�һ����Ц���漴��"
                                 "�����ϡ�\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "����΢΢һ������������������"
                                 "ˮ����Ʈ���䣬��$N" HIY "������ᣬ������"
                                 "����һ�С�\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "΢΢һЦ��������չ�������˾�"
                                 "̤��Ʈ�𣬿��ּ�$N" HIY "Ҳ�漴Ʈ���ڰ�"
                                 "�չ������С�\n" NOR;
                        break;
                default:
                        result = HIY "����$n" HIY "����һչ���ó�����ٻӰ��"
                                 "�����裬��$N" HIY "����˼������һ�У�����"
                                 "ʵӰ���ڡ�\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
	
	if (me->query("family/family_name") != "�컨��")
		{return 50;}
		else
			{
        int lvl;

        lvl = me->query_skill("zhuangzi-wu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;            
        return 100;
      }
}

int practice_skill(object me)
{
        if (me->query_skill("zhuangzi-wu", 1) < 180
	   && me->query("family/family_name") != "�컨��")
                return notify_fail("���ׯ�����˽ⲻ���������������ж�����\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˣ�������ϰׯ���衣\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("������������ˣ��޷���ϰׯ���衣\n");

        me->receive_damage("qi", 90);
        me->add("neili", -100);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhuangzi-wu/" + action;
}
