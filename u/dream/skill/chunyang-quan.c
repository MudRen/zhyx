// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// chunyang-quan.c ����ȭ

#include <ansi.h>
inherit SKILL;

int chunyangwuji(object me, object victim, object weapon, int damage);

string *action_msg = ({
        "$Nʩչ�����ײ�ʳ���������ڿ�Ծ�������ſ������ɺ��ٿգ���������ȭ����ͻȻ������ǰ��̽������$n$l",
        "$N����ʹ��������Ϸ�꡹��������μ��У���ȭ��ಡ���һ�����Ʒ����ʹ�����������$n��$l",
        "$N���������Ȼŭ��һ������ǰһ��������˫�ơ�Ұ���ϲۡ������ŷ���֮����������$n",
        "$N�ڿշ���һʽ���ڻ����ġ�����ȭ����$n�ؿ��������͵���ȥ",
        "$N��ǰһ���ͳ壬һʽ������Ϸ�项��˫ȭͻȻͬʱ������ֱȡ$n��˫Ŀ",
        "$N�������һ�������ñܿ�$n�Ĺ�����ͻȻһת������һ�С����뷴�ҡ���һ��Ťס$n�۰���ȭȴ����$n������",
        "$N��ǰһ����������ʹ����������ʳ����һ�ǹ�ȭ������һ�еص���$n",
        "$N������֮�����ͺ�һ����ͻȻһʽ���������ơ�����ȭ��ĳ�죬Ю���ſ�磬�����Ƶ絷��$n$l",
});

int valid_enable(string usage) { return  usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) { return combo=="sanhua-juding"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ȭ������֡�\n");
        if ((int)me->query_skill("xiantian-gong", 1) < 15)
                return notify_fail("����������칦��򲻹����޷�ѧ����ȭ��\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷�������ȭ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(20), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "post_action": (: chunyangwuji :),
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("�����������������ȭ��\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chunyang-quan/" + action;
}

void finish_chunyangwuji(object me, int skill_lvl) 
{ 
        me->set_temp("apply/attack", me->query_temp("cyq-wuji/old_attack")); 
        me->set_temp("apply/damage", me->query_temp("cyq-wuji/old_damage")); 
        me->delete_temp("perform/chunyangwuji"); 
        me->delete_temp("cyq-wuji"); 
        me->start_busy(2+random(2)); 
} 
int chunyangwuji(object me, object victim, object weapon, int damage) 
{        
        string msg; 
        int cyq_wuji = me->query_temp("perform/chunyangwuji"); 
        int skill_lvl = me->query_skill("chunyang-quan", 1)/4; 
        int exp_m = me->query("combat_exp", 1);
        int exp_t = victim->query("combat_exp", 1);

        if( damage > 0 ) {
                if( victim->query("qi") <= 0 ) {
                        msg = HIR"\n\tֻ��$Nȭ�����ͣ�����"+chinese_number(cyq_wuji)+"�з���ʱ��$n�Ѿ��ܲ�ס$N��ȭ�磡\n"NOR;
                        if( me->is_killing(victim->query("id")))
                                victim->receive_wound("qi", victim->query("max_qi")+100,"��"+ me->name()+"�������޼�����ǿ������������");
                        message_vision(msg , me, victim); 
                        finish_chunyangwuji(me, skill_lvl);                       
                        return 1;
                }else msg = HIY"\n\t$Nһ�����У�����$n��Ӧ��"+chinese_number(cyq_wuji+1)+"���Ѿ�����ɽ����֮����$n������\n"NOR;
        }else{
                if( random(exp_m) < random(exp_t / 2) ){
                        msg = HIW"\n\t$Nһ�в��У���ʱ�����Լ��������������޼���������ʽ��Ҳʹ��������\n"NOR;
                        message_vision(msg , me, victim); 
                        finish_chunyangwuji(me, skill_lvl);                       
                        return 1;
                }else{
                        msg = HIY"\n\t$Nһ�в��У���ת���ν���"+chinese_number(cyq_wuji+1)+"��Ѹ�ٵݳ����ٶȽ�ǰ���ҷ������\n"NOR;
                        me->add_temp("apply/damage", skill_lvl / 3);
                }
        }
        if( cyq_wuji >= me->query_temp("cyq-wuji/max_times")){
                msg = HIY"\n\t$Nһ������$n��������"+chinese_number(cyq_wuji)+"�У�����ȭ��������ʵ���ɱ����ӣ�\n"NOR;
                message_vision(msg , me, victim); 
                finish_chunyangwuji(me, skill_lvl); 
                return 1;
        }
        me->add("neili", -skill_lvl / 3); 
        me->add("jingli", -skill_lvl / 4); 
        me->add_temp("perform/chunyangwuji", 1); 
        me->add_temp("apply/attack", skill_lvl / 2); 
        me->add_temp("apply/damage", -skill_lvl / 2); 
        message_vision(msg , me, victim); 
        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
        return 1;
} 

