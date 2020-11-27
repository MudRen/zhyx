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
        set("gender", "Ů��" );        
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
        set_skill("mizong-neigong", 1200);
        set_skill("xuehai-mogong", 1200);
        set_skill("blade", 1200);
        set_skill("xuedao-daofa", 1200);
        set_skill("sword", 1200);
        set_skill("mingwang-jian", 1200);
        set_skill("dodge", 1200);
        set_skill("shenkong-xing", 1200);
        set_skill("hand", 1200);        
        set_skill("dashou-yin", 1200);
        set_skill("cuff", 1200);
        set_skill("yujiamu-quan", 1200);
        set_skill("parry", 1200);
        set_skill("lamaism", 1200);
        set_skill("literate", 1200);
        set_skill("martial-cognize", 1200);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");
   
        set("hellzhen", 0);
        setup();

        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 
                
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}

void invocation(object target)
{
        object me = this_object();
        int ap, dp, damage;
        string msg;
                
        ap = me->query_skill("blade") * 3 / 2 + me->query("level") * 20 + 
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query("level") * 20 + 
             target->query_skill("martial-cognize", 1);
             
        msg = HIY "$N" HIY "��Ȼʩ����" HIR "��Ѫ��" HIY "�������иֵ�"
              HIY "�����ޱ�ɱ�⣬Я�ŷ���֮����$n" HIY "��ն��ȥ��\n" NOR;

        if (ap + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "ֻ����ǰһ��Ѫ����������"
                                           "���ѱ�$N" HIR "��һ�����˸����С�\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "ֻ��$P" CYN "������ӿ�����Եֵ�����"
                       "��������Ծ�����ߡ�\n" NOR;
        }
        message_combatd(msg, me, target);            
        destruct(me);
}

