#include <ansi.h>
inherit SKILL;
mapping *action = ({
        ([ "name":   "���̽�",
           "action": "$N����������˫��Ĵָͬʱ����������������죬��" HIW "���̽�" NOR "������ʯ���쾪���������֮�ƣ�ָ\n"
                     "��$n��$l",
           "force" : 460,
           "attack": 140,
           "dodge" : 90,
           "parry" : 90,
           "damage": 200,
           "damage_type":  "����"
        ]),
        ([ "name":   "������",
           "action": "$Nʳָ����������԰ת����" HIR "������" NOR "��һ����һ���Ĵ̳�������Ѹ�٣����ɻ��ã������ݺᣬ����\n"
                     "�ܹ����彣������·",
           "force" : 440,
           "attack": 145,
           "dodge" : 110,
           "parry" : 95,
           "damage": 225,
           "damage_type":  "����"
        ]),
        ([ "name":   "�г彣",
           "action": "$N������ָһ������" HIY "�г彣" NOR "����ǰ�̳��������ĵ�����Ȼ���죬���ν���ֱָ$n��$l",
           "force" : 560,
           "attack": 135,
           "dodge" : 10,
           "parry" : 70,
           "damage": 275,
           "damage_type":  "����"
        ]),
        ([ "name":   "�س彣",
           "action": "$N��������ָ�������" HIY "�س彣" NOR "����·׾�͹��ӣ�һ���ۻ��ޱȵ������ĵ�����������ɽ����һ��\n"
                     "$nӿȥ",
           "force" : 530,
           "attack": 140,
           "dodge" : 100,
           "parry" : 95,
           "damage": 225,
           "damage_type":  "����"
        ]),
        ([ "name":   "����",
           "action": "$N����Сָһ�죬һ���������ٳ�Ѩ�м����������" HIW "����" NOR "��������磬ָ��$n��$l",
           "force" : 500,
           "attack": 130,
           "dodge" : 95,                            
           "parry" : 92,
           "damage": 215,
           "damage_type":  "����"
        ]),
        ([ "name":   "�ٳ彣",
           "action": "$N���ַ�ָ��Сָ������������ٳ�Ѩ������������" HIW "�ٳ彣" NOR "��������䣬�������벻���ķ����\n"
                     "��$n��$l",
           "force" : 430,
           "attack": 140,
           "dodge" : 90,
           "parry" : 95,
           "damage": 175,
           "damage_type":  "����"
        ]),
});
string main_skill() { return "six-finger"; }
int can_not_hubo() {return 1;}
mapping sub_skills = ([
        "shaoshang-sword"  : 120,
        "shangyang-sword"  : 120,
        "zhongchong-sword" : 120,
        "guanchong-sword"  : 120,
        "shaoze-sword"     : 120,
        "shaochong-sword"  : 120,
        ]);
int get_ready(object me)
{
        return 1;
}
int get_finish(object me)
{
        if (me->query("int") < 32) {
                tell_object(me, "��������ϣ���������ûʲô��ϵ������һƬãȻ��\n");
                return 0;
        }
        if (me->query("con") < 26) {
                tell_object(me, "��������ϣ��;�����ǰ������ð��̫��Ѩͻͻ������\n");
                return 0;
        }
        if (me->query_skill("literate", 1) < 200) {
                tell_object(me, "����������񽣼�����£��������о�һ��ѧ�ʿ��ܸ��а�����\n");
                return 0;
        }
        if (me->query_skill("lamaism", 1) < 200) {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }
        if (me->query_skill("buddhism", 1) < 200) {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }
        if ((int)me->query("max_neili") < 3000) {
                tell_object(me, "������������̣��޷��ڻ��ͨ������\n");
                return 0;
        }
        if (random(10) < 7) {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ�����������񽣡�\n");
                return 0;
        }
        tell_object(me, HIY "һ�󷲳�����ӿ����ͷ���㼸��������̾����ǰ�������ֳ�����������\n"
                            "���Ǽ䣬������ͨ�������񽣡�\n" NOR);
        return 1;
}
mapping query_sub_skills()
{
        return sub_skills;
}
int valid_enable(string usage) { return usage=="finger" ||  usage=="parry"; }
int double_attack() { return 1; }
int valid_learn(object me)
{
        if (me->query("int") < 32)
                return notify_fail("���о��˰��죬Ҳû����������񽣵İ��\n");
        if (me->query("con") < 26)
                return notify_fail("���о���һ�����ֻ������ǰ������ð��̫��Ѩͻͻ������\n");
        if (me->query_skill("literate", 1) < 200)
                return notify_fail("����������񽣼�����£�����������ѧ��ˮƽ�����о��ġ�\n");
        if (me->query_skill("lamaism", 1) < 200)
                return notify_fail("�㷢���������кܶ����������ķ��йأ�������⡣\n");
        if (me->query_skill("buddhism", 1) < 200)
                return notify_fail("�㷢���������кܶ����������ķ��йأ�������⡣\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������񽣱�����֡�\n");
        if ((int)me->query("max_neili") < 3000)
                return notify_fail("�������̫�����޷�ѧ�����񽣡�\n");
        if ((int)me->query_skill("finger", 1) < 120)
                return notify_fail("��Ļ���ָ����򲻹���\n");
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("six-finger", 1))
                return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷��޷���������������񽣡�\n");
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
int practice_skill(object me)
{
        int cost;
        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˡ�\n");
        cost = me->query_skill("six-finger", 1) / 10 + 20;
        if ((int)me->query("neili") < cost)
                return notify_fail("������������������񽣡�\n");
        me->receive_damage("qi", 50);
        me->add("neili", -cost);
        return 1;
}                                          
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 200) return 0;

        if (random(10) > 4)
        {
                victim->receive_wound("qi", (damage_bonus - 200) / 3);
                return HIR "��������������һ�����죬���Ͼ�����һЩѪ�Σ�\n" NOR;
        }
}
mapping query_action(object me, object weapon)
{
        if (! undefinedp(me->query_temp("six-action")))
                return action[me->query_temp("six-action")];

        if (random(10) == 8)
        {
                me->add("neili", -200);
                return ([
        "action": HIC "$N" HIC "��Ȼ���ý����е���·����һһӿ����ͷ��ʮָ�׵�����ȥ�����������޾���\n" NOR
                      "��ʱֻ���Ĵ������ݺᣬ����������·������ת��ʹ��$n��ʱ������ң�����ȫ������\n"
                      "ʹ������" HIR "��Ѫ" NOR "�����ϱ������ʹ̧ͷһ����һ������ӭ���ֵ�",
        "attack": 140,
        "dodge" : 150,
        "parry" : 120,
        "damage": 340,
        "force" : 580,
        "damage_type": "����"]);
        }
        return action[random(sizeof(action))];
}
// here: the attacker is $N, and you, the defenser is $n
string query_parry_msg(object victim_weapon)
{
        switch (random(4))
        {
        case 0:
                return "$n������������������ݺύ������������$NΨ��������̾��ͽ���κΡ�\n";
        case 1:
                return "$n�������ܣ�һ���г彣ֱϮ$N����ǰ��Ѩ���ȵ�$Nֻ�л����Ծȡ�\n";
        case 2:
                return "$n���������������ص���ֱ���$Nüë���䣬������ͨ����Ҳ����ǰ����֣�\n";
        default:
                return "$nһ����Ц�����ν����Ĵ�ɢ������$N����ס��Ω����ǿ֧�š���Լ�԰�����$n�ķ�����\n";
        }
}
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;
        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
string perform_action_file(string action)
{
        return __DIR__"six-finger/" + action; }
