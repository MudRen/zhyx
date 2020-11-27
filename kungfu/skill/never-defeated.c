// never-defeated.c ������
//updated by kasumi
//updated by xiner 2009-07-30 ǿ��ƽ�й���Ч����������9j�����Ը�

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("never-defeated", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *action_default = ({
([      "action" : "$N���ƺ��������裬�ƽ������Ƶ�����׽��������$n������ȥ",
        "force" : 450,
        "attack": 180,
        "dodge" : 180,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ�������۶�������ɨ$n",
        "force" : 460,
        "attack": 180,
        "dodge" : 190,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "����"
]),
([      "action":"$N�������е�$w������$n�ҿ����ң�û�а���·�",
        "force" : 470,
        "attack": 190,
        "dodge" : 200,
        "parry" : 190,
        "damage": 250,
        "damage_type":  "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n��Χ",
        "force" : 480,
        "attack": 190,
        "dodge" : 210,
        "parry" : 190,
        "damage": 260,
        "damage_type":  "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
        "force" : 490,
        "attack": 200,
        "dodge" : 220,
        "parry" : 190,
        "damage": 250,
        "damage_type":  "����"
]),
([      "action":"$N��̾һ������$w���ֵݳ������Լ�Ҳ��֪��Ҳ��������",
        "force" : 500,
        "attack": 200,
        "dodge" : 180,
        "parry" : 180,
        "damage": 250,
        "damage_type":  "����"
]),
([      "action":"$N��ɫ���أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n",
        "force" : 510,
        "attack": 210,
        "dodge" : 190,
        "parry" : 190,
        "damage": 260,
        "damage_type":  "����"
]),
([      "action":"$N����$w�������籩�꣬���������з���$n��$l�����Ա�$n����",
        "force" : 520,
        "attack": 220,
        "dodge" : 250,
        "parry" : 190,
        "damage": 270,
        "damage_type":  "����"
]),
([      "action":"$NͻȻ���������е�$w��Ȼ��$n�����Ҵ�����",
        "force" : 530,
        "attack": 250,
        "dodge" : 260,
        "parry" : 200,
        "damage": 280,
        "damage_type":  "����"
]),
([      "action":"$N��$w����һ�ڣ�$n�����Լ���$wײ�����������֮����ʵ�����Ѳ�",
        "force" : 540,
        "attack": 250,
        "dodge" : 170,
        "parry" : 210,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N���е�$w�����ƣ�ȴ�ƻ򵶷����ּ��ӹ���֮�⣬��$nѣĿ",
        "force" : 550,
        "attack": 260,
        "dodge" : 250,
        "parry" : 280,
        "damage": 300,
        "damage_type":  "����"
]),
});

mapping *action_whip = ({
([      "action" : "$N���ƺ��������裬$w�仯�޳���׽��������$n������ȥ",
        "force" : 480,
        "attack": 180,
        "dodge" : 75,
        "parry" : 215,
        "damage": 225,
        "damage_type": "����"
]),
([      "action":"$N���е�$wͻ������ɭ�ϣ�����ǧ�������۶�����$w�������һ���ɨ$n",
        "force" : 450,
        "attack": 190,
        "dodge" : 85,
        "parry" : 225,
        "damage": 210,
        "damage_type": "����"
]),
([      "action":"$N�������е�$w����������һ�����$n�ҿ����ң�û�а���·�",
        "force" : 480,
        "attack": 195,
        "dodge" : 180,
        "parry" : 125,
        "damage": 205,
        "damage_type": "����"
]),
([      "action":"$N����$w�û���һ��һ��ԲȦ���ƺ�Ҫ��$n���Ű�Χ",
        "force" : 465,
        "attack": 190,
        "dodge" : 165,
        "parry" : 125,
        "damage": 290,
        "damage_type": "����"
]),
([      "action":"$N��Ц��ת$w������һָ���ĵ��黨ָ֮�⣬����$n��$l",
        "force" : 510,
        "attack": 210,
        "dodge" : 180,
        "parry" : 120,
        "damage": 200,
        "damage_type": "����"
]),
});

string *usage_skills = ({ "sword", "blade", "dagger",
                          "staff", "hammer", "club", "whip",  
                          "parry", "force", "throwing" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "never-defeated";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        switch (weapon ? weapon->query("skill_type") : "default")
        {
        case "whip":
                return action_whip[random(sizeof(action_whip))];
        default:
                return action_default[random(sizeof(action_default))];
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp;
        object m_weapon;

        if ((int) me->query_skill("never-defeated", 1) < 120
           || ! (m_weapon = me->query_temp("weapon"))
           || ! living(me) 
           )
                return;
        
        ap = ob->query_skill("parry");
        dp = me->query_skill("parry", 1) / 2 + me->query_skill("never-defeated", 1);       
             if (ap / 2 + random(ap) < dp)
             {
                        result = ([ "damage": -damage ]);
                        result += (["msg" : HIG "$n" HIG "�����$N" HIG "�Ĺ��ƣ�"
                                    "����ӳ�һ�У�������$N" HIG "��\n" NOR]);            
                        ob->start_busy(2);
             }             
             return result;
             
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (! objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("never-defeated", 1);
        if (lvl < 200) return 10;
        if (lvl < 400) return 60;
        if (lvl < 600) return 90;
        return 120;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{	
	object weapon;
	if (damage_bonus > 150 && objectp(weapon = me->query_temp("weapon")) && random(8) > 0)
        {
		me->add("neili", -30);			    
		victim->receive_wound("qi", (damage_bonus - 100) / 2, me);          
                return random(2) ? HIM "$N" HIM "Ĭ���ھ���" NOR + weapon->name() + HIM "�Ϲ���һ�У���ʱ��ֻ�������������粨�˰���ӿ����ɱ��$n" HIM "��\n" NOR:
				   HIW "����$N" HIW "�����������ת����" NOR + weapon->name() + HIW"��ɲ�Ǽ����������������͵ؾ���$n" HIW "��\n" NOR;
        }     
}


int valid_learn(object me)
{
        int level;
        int i;
	int lvl1, lvl2, lvl3;

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("����ò��������֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("����ò����񹦹�����£���"
                                   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

        if (me->query("character") != "������")
                return notify_fail("��ѧ�˰��죬���ֲ����񹦹Źֵ�"
                                   "�������ϳ��������޷���ᡣ");

        if (me->query("int") < 39)
                return notify_fail("����ò����񹦹�����£���"
                                   "���Լ�������������⡣\n");

	if (me->query("gender") == "����" &&
	    (int)me->query_skill("never-defeated", 1) > 49)
		return notify_fail("���޸����ԣ���������������������Ĳ����񹦡�\n");

        level = me->query_skill("never-defeated", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("������Լ�����ѧ�������ޣ�������������Ĳ����񹦡�\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("��Ի����ڹ�����⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");

        if (me->query_skill("parry", 1) < level)
                return notify_fail("��Ի����мܵ���⻹�������޷�����"
                                   "��������Ĳ����񹦡�\n");   

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("�����񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{
	object me;
	int lvl1, lvl2, lvl3;
	if(me = this_player())
	{
		lvl1 = (int)me->query_skill("never-defeated", 1);
		lvl2 = (int)me->query_skill("dugu-jiujian", 1);
		lvl3 = (int)me->query_skill("xuantie-jian", 1);
		if (lvl1 > lvl2 && lvl1 < lvl3)
			return 700;
		else
			return 800;
	}
	return 1100;
}

string perform_action_file(string action)
{
        return __DIR__"never-defeated/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"never-defeated/exert/" + action;
}


