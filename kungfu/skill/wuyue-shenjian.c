// wuyue-shenjian.c ������
// ��ѧ�Ừɽ����ɽ����ɽ��pfm������á�
// By Kasumi 2009


#include <ansi.h>
inherit SKILL;

string *msg = ({
"$Nʹһ�л�ɽ�������з����ǡ�������$w���Ⱪ������$n��$l��ȥ",
"$N������ת��һ�л�ɽ�������ޱ���ľ������$n��$l",
"$N�趯$w��һ�л�ɽ���������ڤڤ��Ю�������������$n��$l",
"$N����$w����һ����������ɽ������ƽɳ���㡹��$n��$l�̳�����",
"$N����$w���Ⱪ����һ�л�ɽ�������������á���$n$l��ȥ",
"$N����$w����һ���⻡��ֱָ$n$l��һ�л�ɽ�������׺���ա���������������ȥ",
"$N����$wһ�����ٽ���������������ʹһ�С��������ڡ����ǵ�ϵ���ڵ���ɽ����",
"$N����$wͻȻ�佣��һ�£�����һ���׺磬������ΰ������Ʈ�ݣ�������ɽ�����ľ�Ҫ���ڣ�һ�С�ǧ����������$n$lֱ�̹���",
"$N����$wͻȻ�佣��һ�£�һ����ɽ���������両�ࡹ����һ����⣬��׳�ۻ룬��$n$lֱ�̹���",
"$N����$w����һ�£�һ����ɽ�����������ء��������࣬������ΰ����$n$lֱ�̹���",
"$N��������һ�֣�����$w�����ӳ���ʹ������ɽ�ɽ��������ż�ɽ��",
"$N����$w���϶��µ���$nֱ����ȥ��һ�С�������ɽ��������ʯ���쾪�����ƣ�����ɽ����֮�������ӵ����쾡��",
"$N����$wˢ��һ��������Ҽ�����ȥ������һ����ɽ�����ڽ���������������������$w�԰���к��������������ֱ����������һ������һ��",
"$N����$wһ�Σ����һ���������һ��̩ɽ�������������ơ���ת������������΢����$w��$nбб��ȥ",
"$N����$wȦת��һ��̩ɽ�����������ա�ȥ���漲�������������$n��$l",
"$Nչ�����ƣ����潣�ߣ����һ�գ��ұ�һ�䣬ԽתԽ�����͵�$w���Ⱪ����һ��̩ɽ������̩ɽʮ���̡���$n$l��ȥ",
"$N����$wٿ�ش̳���һ���彣��ÿһ���Ľ��нԲ�Ȼ�й��⡣�������ӣ��ڲ���䣬����̩ɽ���������򽣡�",
"$N����$w���ⶸ�������е�$w���͵ط��̣�ֱָ$n�ؿڡ���һ�³��п켫������������ã����ǡ��ٱ�ǧ�ú�ɽ����ʮ��ʽ���еľ���",
"$N�����Է�������·������$wˢ��һ����ɽ������Ȫ��ܽ�ء�����$nС����ȥ",
"$N�����Է�������·������$wˢ��һ����ɽ�����������ϸǡ�����$n��ͷ��ȥ",
"$N����$wٿ�ش̳������ƴ����ػأ�������ã�����һ�к�ɽ������ʯ������������$n$l��ȥ",
"$N����$wٿ�ش̳�����������֮���£������޶�������׽��������һ�к�ɽ������������������ָ��$n$l",
"$N����Ծ��ʹ����ɽ���������ף�ڡ�����$w����һ�������Ӱ��������$n��$l",
"$N������У�һʽ��ɽ����������ӭ�͡���$w����ɶ�������һƬ���⣬Χ��$nȫ��",
"$Nʹһ�к�ɽ���������Ƽ��ա�����������Ʈ������$w����ʵʵ�ó���㺮������$n$l",
"$N���쳤Ц������ƮȻ�����ڰ��������һ����һʽ��ɽ���������Ʊ��¡�����ػ���$n",
"$N�������Ž���������̤��һ�к�ɽ�������ǻ����ա�����б�̣�������ȻԾ��ٿ�Ļ��������ǹ�����$n��$l",
"$N��ǰ��ȥһ�󲽣�ʹ����ɽ������֯Ů���󡹣�����$w���һ������Ѹ�����׻���$n��$l",
"$N���һ����һ�к�ɽ����������ͨ�ġ���$w����㻮��һ����Բ������$n��$l",
"$N��Ȼ���θ߸�Ծ��ʹ����ɽ����������Ǭ������$w�ó����컨�꣬Ѹ����������$n��$l",
});

mapping query_action(object me, object weapon)
{
	int lvl = me->query_skill("wuyue-shenjian", 1);
	if (lvl > 600) lvl = 600;

	if (lvl > 400)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 200+random(lvl/2),
			"force"  : 350+random(lvl/2),
			"dodge"  : 200,
			"parry"  : 200,
			"damage" : 200+random(lvl/2),
			"damage_type" : "����",
			]);
	}else
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 100+random(lvl/4),
			"force"  : 150+random(lvl/4),
			"dodge"  : 100,
			"parry"  : 100,
			"damage" : 100+random(lvl/4),
			"damage_type" : "����",
			]);
	}

}


int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

	if (me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "��ɽ��")
		return notify_fail("����������������������������о������ʽ��\n");;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�������ܹ���ϰ��\n");      

		if (!me->query("can_perform/huashan-jian/xian"))
			    return notify_fail("��û�����򵽻�ɽ�����ľ��У������������ɽ���û�а취���������񽣡�\n");

		if (!me->query("can_perform/wushen-jian/shen"))
			    return notify_fail("��û�����򵽺�ɽ���񽣵ľ��У�����Ԫ�ƣ�û�а취���������񽣡�\n");

		if (!me->query("can_perform/poyang-jian/long"))
			    return notify_fail("��û��������ɽ������⽣�ľ��У�����������û�а취���������񽣡�\n");


        if (me->query_skill("martial-cognize", 1) < 300)
                return notify_fail("����������񽣼�����£������Լ�����ѧ����"
                                   "������⡣\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ������û�а취�������񽣡�\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("��Ļ�������̫�û�а취�������񽣡�\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wuyue-shenjian", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������������񽣡�\n");

        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp,level,backdamage;
        object m_weapon;

        if (! (int)me->query_temp("wysj_mian") ||
            ! (m_weapon = me->query_temp("weapon")) ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;
		level=(int)me->query_skill("wuyue-shenjian", 1);
		if (level<200) backdamage=0;
		else if (level<400) backdamage=(int)damage/3 ;
		else if (level<600) backdamage=(int)damage/2 ;
		else backdamage=damage;
      
        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("wuyue-shenjian", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "��ת���е�" + m_weapon->name() +
                                            HIR "ֱ��$N" + HIR "�������������ꡱһ�����˸�Ѫ������\n" NOR]);
						ob->receive_wound("qi", backdamage);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "�Ӷ����е�" + m_weapon->name() +
                                            HIC "����ס�ı�ý��ƣ���$N"
                                            HIC "���Ȼط����أ�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "��ס�䶯��ʽ����ͼ��ס$N" HIY "��"
                                 "���������Ǽ�ȴ��$N" HIY "���ֻ�ת���ٹ���"
                                 "һ�С�\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "�ֽ��������������ھ��赲$N"
                                 HIY "�Ĺ��ƣ���$N" HIY "��ı��У�����һ��"
                                 "λ���롣\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "������磬ƮȻ��סȫ����$N"
                                 HIY "��Ҳ����ֻ�������ھ������ƹ��롣\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        int cost;
        me = this_player(); 		
	if ((int) me->query_skill("wuyue-shenjian", 1) < 300)
	        return notify_fail("��������񽣵����򲻹����ټ��в�����������ϰ��\n");

        cost = me->query_skill("wuyue-shenjian", 1);
        if (me->query("family/family_name") == "��ɽ��")
	cost = cost/2 + random(cost)/2;
        else
	cost = cost + random(cost);

        if ((int)me->query("neili") < cost)
                return notify_fail("������������������񽣡�\n");

        if ((int)me->query("qi") < cost / 2)
                return notify_fail("������������������񽣡�\n");

        me->receive_damage("qi", cost / 2);
        me->add("neili", -cost);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuyue-shenjian/" + action;
}
