// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;

#include <ansi.h>
#include <combat.h>
#include "ghost.h" 

void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        name += last_words[random(sizeof(last_words))];
        
        set_name(name, ({ "ghost"}) );
        set("gender", "����" );        
        set("age",40);
        set("str", 30);
        set("int", 20);
        set("per", 27);
        set("attitude", "killer");
        set("combat_exp", 640000000+random(600000000));
        set("level", 99);
        set("max_qi", 12000000);
        set("max_jing", 1200000);
        set("neili", 8000000);
        set("max_neili", 8000000);
        set("jingli", 8000000);
        set("max_jingli", 8000000);
        
        set_skill("force", 1200);
        set_skill("shenlong-xinfa", 1200);
        set_skill("dodge", 1200);
        set_skill("yixing-bufa", 1200);
        set_skill("hand", 1200);
        set_skill("shenlong-bashi", 1200);
        set_skill("strike", 1200);
        set_skill("huagu-mianzhang", 1200);
        set_skill("parry", 1200);
        set_skill("staff", 1200);
        set_skill("sword", 1200);
        set_skill("shedao-qigong", 1200);
        set_skill("unarmed", 1200);
        set_skill("literate", 1200);
        set_skill("medical", 1200);
        set_skill("shenlong-mixin", 1200);
        set_skill("martial-cognize", 1200);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("unarmed", "shedao-qigong");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");
   
        set("hellzhen", 0);
        setup();

        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 
                
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}

void invocation(object target)
{
        object me = this_object();
        int ap, dp, fp, damage;
        string msg;

        msg = HIW "$N" HIW "һ�����ȣ����и���"
              HIW "��ɨ������һʱ�䳾�����$n"
              HIW "��ʱ���ú���������\n" NOR;
                                      
        ap = me->query_skill("staff") * 3 / 2 + me->query("level") * 20 + 
             me->query_skill("martial-cognize", 1);
        fp = target->query_skill("force") + target->query("level") * 20 + 
             target->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query("level") * 20 + 
             target->query_skill("martial-cognize", 1);
        if (ap / 2 + random(ap) < fp)
        {
                me->add("neili", -200);
                msg += CYN "����$n" CYN "�ڹ���񣬷�������$N"
                       CYN "��һ�У�˿������\n" NOR;
                me->start_busy(2);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -50);
                msg += CYN "$n" CYN "����һЦ��Ʈ��Ծ������$N"
                       CYN "��һ��ȫȻ��ա�\n" NOR;
                me->start_busy(3);
        } else
        {
                me->add("neili", -220);
                me->start_busy(2);
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
                                           HIR "$n" HIR "ֻ����$N" HIR "��������"
                                           "��ɽ����һ�㣬���ֵܵ������ۡ���һ���³�һ�����Ѫ��\n" NOR);
        }
        message_combatd(msg, me, target);
        destruct(me);
}

