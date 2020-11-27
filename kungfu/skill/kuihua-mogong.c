// kuihua-shengong ����ħ��
// modify by kasumi 15/3/2007

inherit FORCE;
#include <ansi.h>

string *dodge_msg = ({
        "$n΢΢һ������ȻԶȥ��ʹ$N�Ľ���ȫȻ���á�\n",
        "$n��ʱ��ƽ����������������ȣ�ʹ$NȫȻ�޷����ա�\n",
        "$n����һ�ˣ���ȥ�����κ�׷����\n",
        "$n�㲻��أ���֫�Ͱڣ���Ȼ��$N�Ľ���ȫ�������\n",
});

string *finger_name = ({ "������ָ", "��������ָ", "����ʳָ",
                         "������ָ", "��������ָ", "����ʳָ", }); 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-mogong", 1);
        return lvl * lvl * 19 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫����ָ����$n��$l",
        "force" : 410,
        "attack": 200,
        "dodge" : 215,
        "parry" : 60,
        "damage": 200,
        "damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽������ָ���Ĵ���$n��$l",
        "force" : 430,
        "attack": 220,
        "dodge" : 230,
        "parry" : 70,
        "damage": 220,
        "damage_type":  "����"
]),
([      "action":"$N����һת����ָ�̳���ֱָ$n��$l",
        "force" : 450,
        "attack": 240,
        "dodge" : 240,
        "parry" : 50,
        "damage": 240,
        "damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬һָ����������$n��$l",
        "force" : 480,
        "attack": 260,
        "dodge" : 260,
        "parry" : 65,
        "damage": 260,
        "damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ�ţ�����$n��$l",
        "force" : 510,
        "attack": 280,
        "dodge" : 270,
        "parry" : 55,
        "damage": 280,
        "damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһָ����$n��$l",
        "force" : 540,
        "attack": 300,
        "dodge" : 280,
        "parry" : 55,
        "damage": 300,
        "damage_type":  "����"
]),
});

mapping *actionw = ({
([      "action":"$Nٿ�Ľ�ǰ�����ο켫�����е�$w����$n��$l",
        "force" : 460,
        "attack": 250,
        "dodge" : 150,
        "parry" : 40,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N����ǰ����������ͬ���ȣ���������׽�������е�$w���Ĵ���$n��$l",
        "force" : 490,
        "attack": 280,
        "dodge" : 180,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N����һת��$w�̳���ֱָ$n��$l",
        "force" : 465,
        "attack": 320,
        "dodge" : 220,
        "parry" : 45,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$NƮȻԶȥ�����ֽ�ǰ���ٶȿ�Ĳ���˼�飬$w����������$n��$l",
        "force" : 480,
        "attack": 360,
        "dodge" : 240,
        "parry" : 55,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N����һ�Σ�ͻȻ����һ������$n��������������ջأ�����$w����$n��$l",
        "force" : 500,
        "attack": 400,
        "dodge" : 260,
        "parry" : 57,
        "damage": 300,
        "damage_type":  "����"
]),
([      "action":"$N���¼��ߣ����α��Ī�⣬ͻȻһ���֣�$w��Ҳ�ƵĲ���$n��$l",
        "force" : 520,
        "attack": 400,
        "dodge" : 300,
        "parry" : 50,
        "damage": 300,
        "damage_type":  "����"
]),
});

string *usage_skills = ({ "unarmed", "sword", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "kuihua-mogong";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("����ÿ���ħ�����֮����"
                                   "ƾ�Լ���ս������һʱ��������ᡣ\n");

        if ((int)me->query_skill("martial-cognize", 1) < 150)
                return notify_fail("����ÿ���ħ���������֮������"
                                   "�Լ�����ѧ����ȫȻ�޷����ס�\n");

        if (me->query("character") == "��������" )
                return notify_fail("������Բ���������������ħ����\n"); 
         if (me->query("character") == "�ĺ�����" )
                return notify_fail("������Բ���������������ħ����\n");  
         if (me->query("character") == "������" )
                return notify_fail("������Բ���������������ħ����\n"); 				
                                   
      
        if (me->query("dex") < 38)
                return notify_fail("������Լ����������鶯��������������ôƮ�"
                                   "����Ŀ���ħ����\n");
 
        if (me->query("int") < 34)
                return notify_fail("������Լ����������Բ�����������������ô����"
                                   "����Ŀ���ħ����\n");

        level = me->query_skill("kuihua-mogong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("������Լ�����ѧ�������ޣ�������������Ŀ���ħ����\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("���" + to_chinese(usage_skills[i]) +
                                           "����⻹�������޷�������������Ŀ���ħ����\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("����ħ��������޷��򵥵�ͨ����ϰ������\n");
}

int difficult_level(object me)
{
       me = this_player();  
       if (me->query("family/master_name") == "��������")
       return 300;
       else		
       return 500;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("kuihua-mogong", 1);
        if (lvl <= 200) return 100;
        if (lvl <= 300) return 115;
        if (lvl <= 400) return 130;        
        return 150;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("kuihua-mogong", 1) < 210 ||
            ! living(me) ||
            me->query_skill_mapped("dodge") != "kuihua-mogong")
                return;

        //mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge");
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("kuihua-mogong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$N" HIW "�۾�һ����$n" HIW "��û����"
                                            "Ӱ��ͻȻ$n" HIW "���������һ��$N" HIW "��"
                                            "ͷ������Ծ����\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$N" HIW "��ǰһ�����ƺ�����$n" HIW "��"
                                            "��һ�Σ����漴�ּ�$n" HIW "�ص�ԭ�أ�ȴ��"
                                            "��δ�뿪��\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$n" HIW "��Хһ������Ȼ����һת�Ѳ�������Ӱ��$N" HIW
                                           "ֻ�����߷������ϣ����漴�ּ�$n" HIW "�ص���ԭ�ء�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "��Ȼ�䣬ֻ��$n" HIW "��֦һ�ڣ���ʱ����������"
                                            "$n" HIW "��Ӱ�ӣ�$N" HIW "ȴ�޷�����$n" HIW "�ķ�λ��\n" NOR]);
                        break;
                }
                return result;
        }/* 
        else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "$N" HIY "�۾�һ����$n" HIY "��û����Ӱ"
                                 "������$N" HIY "��ͨ����˿����Ϊ���ң�����"
                                 "���С�\n" NOR;
                        break;
                case 1:
                        result = HIY "$N" HIY "��ǰһ�����ƺ�����$n" HIY "��"
                                 "��һ�Ρ�$N" HIY "һ����Ц����˲�俴��������"
                                 "ʵ��\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "����Ʈ����������ȣ�ת�˼�ת��"
                                 "����$N" HIY "��Ҳ�����������о�ֱ������\n"
                                 NOR;
                        break;
                default:
                        result = HIY "ͻȻ���Ӱ���Σ�$n" HIY "���ζ�ʱ���ֳ���ǧ��Ӱ��"
                                 "����$N" HIY "����˼����׷���ϣ�����������"
                                 "����\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }*/
}

mixed hit_ob(object me, object victim, int damage_bonus)
{       
        if ((damage_bonus / 4 > victim->query_dex()) )
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                return MAG "$n" MAG "��ʱ������ǰ������������˫������������ȫ���������һ�㣡\n" NOR;                
        }
}



/*
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        object weapon;
        string name;

        weapon = me->query_temp("weapon");

        if (me->query_temp("weapon"))
	        name = "����" + weapon->name();
        else
	        name = finger_name[random(sizeof(finger_name))];

        attack_time = (int)(me->query_skill("kuihua-mogong", 1) / 40);

        if (attack_time > 9)
                attack_time = 9;

        if (random(2) == 1
           || ! living(victim)                    
           || me->query("neili") < 300
           || me->query_temp("action_flag") == 0
           || me->query_skill("kuihua-mogong", 1) < 200)
        	return 0;

        // ������ʹ��PfmʱѶϢ�ظ�
        if (! me->query_temp("kuihua-mogong/hit_msg"))
	        message_vision(HIW "\n��ʱ��ֻ��$N" HIW "�����Ͱڣ���ʱ����Ϊ������Ӱ��" + name +
        	               HIW "�������ǰ�ִӲ�ͬ�ķ�λͬʱ����$n" HIW "��\n"
                	       NOR, me, victim);

	me->start_busy(1 + random(attack_time));
        me->add("neili", -attack_time * 30);
        me->set_temp("action_flag", 1);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;
                COMBAT_D->do_attack(me, victim, weapon, 0);
        }
        me->delete_temp("action_flag");
        
         if (damage_bonus / 4 > victim->query_dex()
	         && damage_bonus > 150
           && me->query("neili") > 200
           && me->query_skill("martial-cognize", 1) >= 220 )
        {
                me->add("neili", -50);
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                return MAG "$n" MAG "��ʱ������ǰ������������˫������������ȫ���������һ�㣡\n" NOR;
        }

        return 1;
}
*/
string perform_action_file(string action)
{
        return __DIR__"kuihua-mogong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"kuihua-mogong/exert/" + action;
}
