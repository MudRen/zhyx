// xiyang-boji.c ���󲫻���
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
	"$n����һŤ��ǡ�ö����$N��һ�С�\n",
	"����$nͻȻ������ˣ����ݵĶ����$N��һ�С�\n",
	"$n�������ƣ�������$N��׷����\n",
	"$n����$Nת���������������$N�޷���׽��$n����Ӱ��\n",
        "$n��Ŀ��ȣ����������ֺ룬$N��һ������ȫȻ��ա�\n",
});

string *dfail_msg = ({
	"$n����һŤ��ͼ���㣬����$N���Ѿ��ϵ���һ�У�$n��ʱ�ܴ졣\n",
	"$nͻȻ������ˣ�$N��������һ���󲽷���$n����ʤ����\n",
	"$n����$Nת�������������Ȼ��$N�����㵽$n����Ӱ��˳�Ʊ�����ǰֱ����\n",
        "$n��Ŀ��ȣ����������ֺ룬����$N����һ�У������߽���$n�����ơ�\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp, mp;

	if ((int) me->query_skill("xiyang-boji", 1) < 300 ||
            me->query_skill_mapped("dodge") != "xiyang-boji" ||
            ! living(me))
		return;

	mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("xiyang-boji", 1) + me->query_skill("dodge", 1) / 2;

        if (ap / 2 + random(ap) < dp)
        {
                msg = dodge_msg[random(sizeof(dodge_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = dfail_msg[random(sizeof(dfail_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 50 )
                return notify_fail("�������̫���ˣ��޷���ϰ���󲫻�����\n");

        me->receive_damage("qi", 40);
        return 1;
}
