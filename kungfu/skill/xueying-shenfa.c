// xueying-shenfa

inherit SKILL;

mapping *action = ({
([	"action" : "$nһʽ�����ĺ��ǡ����������࣬��$N��ߺ�Ծ������\n",
	"dodge"  : 10
]),
([	"action" : "$nһʽ��Ѫ��Ʈ�㡹����һ����磬�滺��������$N���������ơ�\n",
	"dodge"  : 20
]),
([	"action" : "$nһʽ��ѪӰ���١�����ӯ��һԾ��һת�ۼ���Ƶ���$N�����\n",
	"dodge"  : 30
]),
([	"action" : "$nһʽ����Ѫ��������һת��䣬���Ʈ����һ��Զ\n",
	"dodge"  : 40
]),
([	"action" : "$nһʽ��Ѫ��ãã�����εض����ڰ����һת�����䵽����Զ�ĵط���\n",
	"dodge"  : 50
]),
([	"action" : "$nһʽ��Ѫ��֮Ӱ�����ã�з��ƿ�����ɫ�ĵ��⡣\n",
	"dodge"  : 60
]),
([	"action" : "$nһʽ��Ѫϴ���졹��˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
	"dodge"  : 70
]),
([	"action" : "$nһʽ��Ѫħ֮Ӱ���������Ӱ��Χ��$N���ٵ������˼�Ȧ��\n",
	"dodge"  : 80
]),
([	"action" : "$nһʽ��ѪѪѪ���������Ӱ��Χ��$N���ٵ������˼�Ȧ��\n",
	"dodge"  : 90
])
});

mapping query_action(object me, object weapon)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("huashan-shenfa");

	if (level < 80 )
		zhaoshu--;

	if (level < 60 )
		zhaoshu--;

	if (level < 40 )
		zhaoshu--;

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(string limb)
{
	object me, ob;
	mapping action;

	me = this_player();
	action = query_action(me, ob);

	return action["action"];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 40 )
		return notify_fail("�������̫���ˣ�������ѪӰ����\n");
	me->receive_damage("qi", 30);
	return 1;
}
