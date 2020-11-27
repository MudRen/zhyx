// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// damo-jian.c ��Ħ��

#include <ansi.h>

inherit SHAOLIN_SKILL;

string *action_msg = ({
        "$Nʹһʽ��������Ե����������$w����΢�񣬻ó�һ���������$n��$l",
        "$N����ǰ��ʹ������ȥ�����С��������������ޣ�$w��������$n��$l��ȥ",
        "$Nһʽ��������ɣԶ��������Ʈ�����ߣ��˷�����������$wңҡָ��$n��$l",
        "$N��������Ծ��һʽ���ֻط����᡹���������ּ�ת������ն��$n��$l",
        "$N����$w�й�ֱ����һʽ��ˮ��ͨ���š���������Ϣ�ض�׼$n��$l�̳�һ��",
        "$N����$wбָ���죬��â���£�һʽ������������������׼$n��$lбб����",
        "$N��ָ�����㣬����$w�Ƴ�����ѩ����â��һʽ��ǧ��һέȥ������$n��$l",
        "$N���Ƶ�����һʽ�����Ķ���������$w�Ի���Ծ�����缲�������$n���ؿ�",
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_combine(string combo) { return combo == "xiuluo-dao"; }

int valid_learn(object me)
{
        if ((int)me->query("int") < 30)
                return notify_fail("������ʲ��㣬�޷�����Ħ�����Ľ��⡣\n");  
               
        if ((int)me->query("max_neili") < 300)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("damo-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ĵ�Ħ������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int j, wt, level;
        object target;
        string *msg;

        level   = (int) me->query_skill("damo-jian",1);
        wt = me->query_temp("sl_weituo");
        target = me->select_opponent();
        weapon = me->query_temp("weapon");

        msg = ({ 
                HIR"\n$N����Խ��Խ��������ͻ�죬���֮�䣬$n" +HIR"��ȫ�ǽ���������\n"NOR,
                HIY"\n$N���潣ת���ؽ����ӣ�һ������һ�������಻�����������������������ޱȡ�\n"NOR,
                HIC"\nԭ����Ħ���ߵľ��Ǹ���·�ӣ��˿�ȴ���������鶯֮�������Ƹ���������\n"NOR,
                HIW"\n��ʱ$N�Ľ���һ���Ƴ���Ȼ������Τ�ӷ�ħ�������ӵ������쾡�¡�\n"NOR,
        });

        if( wt > 1 && wt < 6 && !me->query_temp("weituo_attack")) {

                message_vision( msg[wt-2] , me, weapon);
                me->set_temp("weituo_attack", 1);
                for( j=0; j < wt-1; j++ )
                {
                        if (! me->is_fighting(target)) break;
                        me->add("neili", -50);
                        COMBAT_D->do_attack(me, target, weapon);
                }
                me->delete_temp("weituo_attack", 1);
                me->add_temp("sl_weituo", 1);

        }

        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 140 + random(60),
                "attack": 80 + random(10),
                "dodge" : 80 + random(10),
                "parry" : 80 + random(10),
                "damage_type" : random(2)?"����":"����",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("qi") < 90)
                return notify_fail("���������������Ħ����\n");
        if ((int)me->query("neili") < 90)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("qianye-shou", 1) < 100)
                return notify_fail("�������ǧҶ����Ϊ��������\n");

        me->receive_damage("qi", 80);
        me->add("neili", -80);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"damo-jian/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (! me->query_temp("weapon"))
                return 0;

        lvl = me->query_skill("damo-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        object weapon;
        int i;
        
        if (me->query("neili") < 300 
        ||  me->query_skill_mapped("sword") != "damo-jian" 
        ||  ! objectp(weapon = me->query_temp("weapon")) 
        ||  weapon->query("skill_type") != "sword") 
                return 0; 
                
        if (me->query_temp("damo-jian/lian") ||
            me->is_busy())
                return 0;

        message_combatd(HIY "\n$N" HIY "���潣ת���ؽ����ӣ�һ������һ�������಻����"
                        "�������������������ޱȡ�\n" NOR, 
                        me, victim); 
                                             
        me->add("neili", -270); 
                       
        me->set_temp("damo-jian/lian", 1); 
        
        for (i = 0; i < 3; i++) 
        { 
                if (! me->is_fighting(victim)) 
                        break; 
                  
                if (! victim->is_busy() && random(2) == 1) 
                        victim->start_busy(1); 
        
                COMBAT_D->do_attack(me, victim, weapon, 0); 
        } 
        me->delete_temp("damo-jian/lian"); 
        
}
                        
