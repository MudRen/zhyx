// wuyue-shenjian.c ������
// ���������ɵĻ�ɽ��������ɽ������̩ɽ��������ɽ��������ɽ��������һ��
// ��λ��ת������

#include <ansi.h>
inherit SKILL;

string *parry_msg = ({
        "$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$P�͹����ػӳ���λ�����̩ɽ���������������\n",
        "$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ�����ġ�������������ʹ$P���С�\n",
        "$n�������ܣ��ٽ������ʹ�������両�ࡹ����$P�����󣬵����˴��С�\n",
        "$nͦ��һ�����ǡ����Ƴ�ᶡ��ش�$P�����󣬶�ʱ��$P�Ĺ��ƻ��⡣\n",
        "ֻ��$n���˷���������Ʈ�磬һʽ�����������������޶�����ס��$P��\n������\n",
        "$n���˷�����ʹ����ɽ���С�������롹��ɭɭ�����������ܣ��ܿ���$P�����С�\n",
});

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

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

	if (lvl > 300)
	{
		return ([
			"action" : msg[random(sizeof(msg))],
			"attack" : 250+random(lvl/2),
			"force"  : 200+random(lvl/2),
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
			"force"  : 100+random(lvl/4),
			"dodge"  : 100,
			"parry"  : 100,
			"damage" : 100+random(lvl/4),
			"damage_type" : "����",
			]);
	}

}

string main_skill()
{
        return "wuyue-shenjian";
}

mapping sub_skills = ([
        "huashan-sword"  : 200,
        "songshan-sword" : 200,
        "taishan-sword"  : 200,
        "hengshan-sword" : 200,
        "henshan-sword"  : 200,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        me = this_player();

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
        {
                tell_object(me, "��������˰��죬����������ý�ʵ������������\n");
                return 0;
        }

        if (me->query("int") < 40)
        {
                tell_object(me, "��������ϣ�ֻ�����ֽ�������ǣ���������������"
                                "�ԣ��޷������һ��\n");
                return 0;
        }

        if (me->query("dex") < 40)
        {
                tell_object(me, "��������ϣ�ֻ�����Լ������鶯�ԣ������޷���"
                                "���ֽ�����һ��\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 150)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ�������"
                                "�������ֽ�����һ��\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 3200)
        {
                tell_object(me, "��ͻȻ�����������̣��������Լ���������Ϊ���޷�"
                                "�����ֽ�����һ��\n");
                return 0;
        }

        if (random(20) < 17)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ����"
                                "���ֽ�����һ��\n");
                return 0;
        }

        tell_object(me, HIY "\nһ�󷲳�����ӿ����ͷ���㼸��������̾�����Ǽ�����"
                        "���ɵĽ���������\n����Ժ��ｻ�����֣���������ڻ��ͨ"
                        "����Ϊһ�塣������ͨ��������\n�񽣵ľ��ϡ�\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

	if (me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "̩ɽ��")
		return notify_fail("����������������������������о������ʽ��\n");;

        if (! (ob = me->query_temp("weapon"))
           || (string)ob->query("skill_type") != "sword")
                return notify_fail("���������һ�������ܹ���ϰ��\n");

        if (me->query("int") < 40)
                return notify_fail("����������Բ��㣬û�а취�������񽣡�\n");

        if (me->query("dex") < 40)
                return notify_fail("���������������û�а취�������񽣡�\n");

        if (me->query_skill("martial-cognize", 1) < 180)
                return notify_fail("����������񽣼�����£������Լ�����ѧ����"
                                   "������⡣\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("���������Ϊ������û�а취�������񽣡�\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ļ�������̫�û�а취�������񽣡�\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wuyue-shenjian", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������������񽣡�\n");

        return 1;
}

int practice_skill(object me)
{
        int cost;

        if ((int)me->query_skill("wuyue-shenjian", 1) < 300)
                return notify_fail("��������񽣵���������������ϰ��\n");

        cost = me->query_skill("wuyue-shenjian", 1);
	cost = cost + random(cost);

        if ((int)me->query("neili") < cost)
                return notify_fail("������������������񽣡�\n");

        if ((int)me->query("qi") < cost / 2)
                return notify_fail("������������������񽣡�\n");

        me->receive_damage("qi", cost / 2);
        me->add("neili", -cost);
        return 1;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("wuyue-shenjian", 1);

        if (damage_bonus < 120
		|| me->query("neili") < 500
		|| me->query_skill_mapped("sword") != "wuyue-shenjian"
		|| random(4) == 0)
                     return 0;

	tell_object(me, HIG "�����Ծ��顿��HIT�ж����ɿ�ʼ "+me->query("family/family_name")+me->query_skill_mapped("force")+" ��\n" NOR);

	if (me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "��ɽ��"
		&& me->query("family/family_name") != "̩ɽ��")
                     return 0;


	if (me->query_skill_mapped("force") == "zixia-shengong") //��ɽ ��ϼ��
	{
		me->add("neili", -100);
		victim->receive_damage("qi", damage_bonus / 2, me);
		victim->receive_wound("qi", damage_bonus / 3, me);
		return HIM "����$N" HIM "����������ʢ��ȫ�������ڽ��У�����ԴԴ��������$n" HIM "��\n" NOR;
	}
	if (me->query_skill_mapped("force") == "hanbing-zhenqi") //��ɽ ��������
	{
		me->add("neili", -100);
		victim->start_busy(random(2));
		victim->receive_damage("jing", damage_bonus / 4, me);
		return HIB "$N"HIB"�����������������ڽ��ˣ�ԴԴ���ϵ�����$n"HIB"������\n" NOR;
	}
	if (me->query_skill_mapped("force") == "zhenyue-jue") //��ɽ ������
	{
		me->add("neili", -100);
		victim->receive_damage("qi", damage_bonus / 3, me);
		victim->receive_damage("jing", damage_bonus / 3, me);
		return HIW "$N"HIW"��������������������һ������ƽ�͵Ľ�������$n"HIW"����\n" NOR;
	}
	if (me->query_skill_mapped("force") == "baiyun-xinfa") //��ɽ�����ķ�������
	{
		me->add("neili", -100);
		victim->receive_damage("jing", damage_bonus / 2, me);
		victim->receive_wound("jing", damage_bonus / 3, me);
		return HIW "$N"HIG"�İ����ķ�͸����������ӿ����������$n"HIG"����\n" NOR;
	}
	if (me->query_skill_mapped("force") == "panshi-shengong") //̩ɽ��ʯ�񹦴�����
	{
		me->add("neili", -100);
		victim->start_busy(1 + random(lvl / 80));
		victim->receive_wound("qi", damage_bonus / 4, me);
		victim->receive_wound("jing", damage_bonus / 4, me);
		return HIW "$N"HIG"����ʯ�����ڽ���$n"HIW"��ʱѹ��������\n" NOR;
	}
	
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp, mp;

	if ((int) me->query_skill("wuyue-shenjian", 1) < 300 ||
            me->query_skill_mapped("sword") != "wuyue-shenjian" ||
            me->query_skill_mapped("parry") != "wuyue-shenjian" ||
            ! living(me))
		return;

	if (me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "��ɽ��"
		|| me->query("family/family_name") != "̩ɽ��")
		return;

	mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry",1) + mp;
        dp = me->query_skill("wuyue-shenjian", 1);

	if (ap / 2 + random(ap) < dp)
        {
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$P", "$P" HIW);
                msg = replace_string(msg, "$l", "$l" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = "$n�ὣ�����м�$P�Ĺ���������$P��Ҳ����ͻȻ�������ȹ���$n��\n";
                msg = HIY + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}



string perform_action_file(string action)
{
        return __DIR__"wuyue-shenjian/" + action;
}
