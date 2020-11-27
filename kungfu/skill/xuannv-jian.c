// xuannv-jian.c ��Ů���� �������Ծ�����Ů������ϰ
// �ɼ���Ϊ�������мܼ��Ṧ


inherit SKILL;
#include <ansi.h>

string *dodge_msg = ({
        "$n��Ť��������ʱ�ܿ���$N��ȫ��������\n",
        "$n�����϶���죬���α�ò�����$N����ʽ������ա�\n",
        "$n���ļ�����$Nֻ������ǰ������$n�Ļ�Ӱ�������޴ӳ��С�\n",
        "$n��̤��Ůɢ�������㲻��أ���$N�Ľ���ȫ�������\n",
});

mapping *action = ({
([      "action":"$N�Ų���ͣ�����е�$w����һ��˿��������$n��$l",
        "force" : 460,
        "attack": 200,
        "dodge" : 150,
        "parry" : 40,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N��ǰ�����������Ȼ����漴�������裬���е�$w����$n��$l",
        "force" : 490,
        "attack": 185,
        "dodge" : 160,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N����Ʈ��������������Ů��ͻȻ����$w�̳���ֱָ$n��$l",
        "force" : 465,
        "attack": 210,
        "dodge" : 180,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬$w����������$n��$l",
        "force" : 480,
        "attack": 190,
        "dodge" : 195,
        "parry" : 55,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"�ۼ�$N�趯����$w��ֱ����$n�ؿڣ�Ȼ��������;ȴ��ͻȻ����$n������",
        "force" : 500,
        "attack": 220,
        "dodge" : 180,
        "parry" : 57,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N���α��Ī�⣬ͻȻһ������$w����Ѹ�ײ����ڶ�֮�Ʋ���$n��$l",
        "force" : 520,
        "attack": 260,
        "dodge" : 195,
        "parry" : 50,
        "damage": 300,
        "damage_type":  "����"
]),
});

string *usage_skills = ({ "sword", "dodge", "parry" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
       return action[random(sizeof(action))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        if (me->query("gender") != "Ů��")
                return notify_fail("��������ȥ����������������ʺ�Ů����ϰ��\n");

        if ( ! me->query("special_skill/queen"))
                return notify_fail("�㲻�Ǿ�����Ů���޷���ϰ��Ů������\n");
  
        if ((int)me->query_skill("dodge", 1) < 200)
                  return notify_fail("��Ļ����Ṧ��򲻵����޷�ѧϰ��Ů������\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ľ������ײ��У����������Ů������\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("�������̫��޷�ѧϰ��Ů������\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("xuannv-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ů������\n");

	if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xuannv-jian", 1))
		return notify_fail("��Ļ����Ṧˮƽ���ޣ��޷������������Ů������\n");

	//if ((int)me->query_skill("parry", 1) < (int)me->query_skill("xuannv-jian", 1))
	//	return notify_fail("��Ļ����м�ˮƽ���ޣ��޷������������Ů������\n");

       if (me->query_skill("martial-cognize", 1) < me->query_skill("xuannv-jian", 1))
                return notify_fail("�����ѧ�����������޷���������"
                                   "�������Ů������\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��Ů����������޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level()
{       
       if ( this_player()->query_skill("xuannv-jian", 1) > 300)
       return 1100;
       else   return 900;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("xuannv-jian", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;    
         return 120;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("xuannv-jian", 1) < 150 ||
            ! (m_weapon = me->query_temp("weapon")) ||
            me->query_skill_mapped("dodge") != "xuannv-jian" ||
            ! living(me) || m_weapon->query("skill_type") != "sword")
                return;
       
        ap = ob->query_skill("dodge") ;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("xuannv-jian", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIM "$n" HIM "��̤��Ůɢ������$N" HIM
                                            "��ǰ��ʱ������������$n" HIM "��ٻӰ����$N"
                                            HIM "�����޴ӽ�����\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "$n" HIM "���������ǡ"
                                            "����$N" HIM "�Ĺ���ƫ�����硣\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIM "$N" HIM "һ�м���������Ȼ��$n"
                                            HIM "����һ��������һ˿�����������ѽ�$N"
                                            HIM "��һ�иպñܿ���\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIM "$n" HIM "����һԾ��ͻȻ��������Ӱ��$N"
                                            HIM "���д󺧣�ȴ�ּ�$n" HIM "��ͻȻ�ص���ǰ��"
                                            "�ٶ�֮�쵱�����˷�����˼��\n" NOR]);
                        break;
                }
                return result;
        } 
        /*
        else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIM "ֻ��$n" HIM "��̤��Ůɢ������"
                                 "��ʱ������������$n" HIM "��ٻӰ������$N"
                                 HIM "��ͨ������������ʵ������������\n" NOR;
                        break;
                case 1:
                        result = HIM "$n" HIM "���������Ȼ��$N"
                                 HIM "�����棬��λ���岻�\n" NOR;
                        break;
                case 2:
                        result = HIM "$n" HIM "����һ��������һ˿�����������ѽ�$N"
                                 HIM "��һ�иպñܿ�������$N"
                                 HIM "�������У�����ȴ�ǲ�ֹ��\n" NOR;
                        break;
                default:
                        result = HIM "����$n" HIM "����һԾ���Ѳ�������Ӱ��Ȼ��$N"
                                 HIM "������У�����ȴ�������\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
        */
}

mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon = me->query_temp("weapon");       
	      name = "����" + weapon->name();       

        attack_time = (int)(me->query_skill("xuannv-jian", 1) / 40);

        if (attack_time > 9)
                attack_time = 9;
        
        if (me->is_busy()
        	 || random(2) == 0
           || ! living(victim)           
           || damage_bonus < 120
           || me->query("neili") < 300
           || me->query_temp("is_attacking") 
           || me->query_skill("xuannv-jian", 1) < 200
           || me->query_skill_mapped("sword") != "xuannv-jian")
        	return 0;

        
	        message_vision(HIG "\n��ʱ��ֻ��$N��֫΢�ڣ���������ӭ�����裬" + 
                         name + HIG"����һ���������$n��\n"
                	       NOR, me, victim);                	       
                	       
        me->set_temp("is_attacking", 1);
        me->start_busy(1 + random(attack_time / 2));
        me->add("neili", -attack_time * 20);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        me->delete_temp("is_attacking");

	

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuannv-jian/" + action;
}

