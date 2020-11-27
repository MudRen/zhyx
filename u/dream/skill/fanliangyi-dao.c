// fanliangyi-dao.c ∑¥¡Ω“«µ∂∑®
// by Lonely

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit SKILL;

mapping *action_msg = ({
        "$N ÷÷–$w–±÷∏£¨“ª’–°∏ªÏ„Á“ª∆∆°π£¨∑¥…Ì“ª∂Ÿ£¨“ªµ∂œÚ$nµƒ$l¡√»•",
        "$N“ª’–°∏Ã´““…˙√»°π£¨◊Û”“Õ»–Èµ„£¨$w“ªÃ·“ª ’£¨∆Ω»–ª”œÚ$nµƒæ±≤ø",
        "$N’π…Ì–È≤Ω£¨Ã·—¸‘æ¬‰£¨“ª’–°∏¡Ω“«∫œµ¬°π£¨µ∂∑ÊªØ◊˜¡Ωπ…’∂œÚ$n",
        "$N“ª’–°∏»’‘¬ªﬁ√˜°π£¨$w¥Ûø™¥Û„ÿ£¨◊‘…œ∂¯œ¬ªÆ≥ˆ“ª∏ˆ¥Ûª°£¨± ÷±≈¸œÚ$n",
        "$N ÷÷–$w“ª≥¡£¨“ª’–°∏Œﬁ…´Œﬁœ‡°π£¨À´ ÷≥÷»–¿π—¸∑¥«–£¨ø≥œÚ$nµƒ–ÿø⁄",
        "$Nª”ŒË$w£¨ π≥ˆ“ª’–°∏ÕÚΩŸ≤ª∏¥°π£¨…œ≈¸œ¬¡√£¨◊Ûµ≤”“ø™£¨∆Î∆Î’÷œÚ$n",
});


int valid_enable(string usage) 
{ 
        return usage == "blade" || usage == "parry" || usage == "array"; 
}

int form_array(object leader)
//int perform(object leader, object target)
{
        object *member,ob, weapon;
        int i,j,n;
        int max,min,skill;

        member = leader->query_team();
        if( sizeof(member) != 2 )
                return notify_fail("∑¥¡Ω“«µ∂π≤–Ë¡Ω»À£¨…Ÿ“ª∏ˆ∂‡“ª∏ˆ∂º≤ª––°£\n");

        j=sizeof (member);
        for (i=0;i<j;i++)
        {
                ob=member[i];
                if (!ob||!living(ob)||!ob->is_character())
                {
                        return notify_fail("ƒ„œÎ∫ÕÀ≠Õ¨ π∑¥¡Ω“«µ∂£ø\n");
                }
                if (ob->query_temp("array/name"))
                {
                        return notify_fail("“—æ≠◊È≥…µ∂’Û¡À°£\n");
                }
                if (environment(leader)!=environment(ob))
                {
                        return notify_fail("»À ˝≤ªπª¡Ω»À°£\n");
                }
                if (!ob->query_skill("fanliangyi-dao",1))
                {
                        return notify_fail(ob->name()+"ªπ≤ªª·∑¥¡Ω“«µ∂∑®°£\n");
                }
                if (ob->is_ghost())
                {
                        return notify_fail("÷ª”–—Ùº‰µƒ»À≤≈ƒ‹◊Èµ∂’Û°£\n");
                }

                if( (int)ob->query("max_neili") < 50 )
                        return notify_fail(ob->query("name")+"µƒƒ⁄¡¶≤ªπª°£\n");

                if( (string)ob->query_skill_mapped("force")!= "zixia-gong")
                        return notify_fail(ob->query("name")+"√ª”– π”√ª™…Ω≈…ƒ⁄π¶°£\n");

                if( !(weapon = ob->query_temp("weapon"))
                ||      (string)weapon->query("skill_type") != "blade" )
                        return notify_fail(ob->query("name")+"±ÿ–Îƒ√∞—µ∂◊ˆŒ‰∆˜°£\n");

                if( (int)ob->query_skill("fanliangyi-dao",1)<30)
                        return notify_fail(ob->query("name")+"µƒ∑¥¡Ω“«µ∂∑®ªπ≤ªπª Ï¡∑°£\n");

                if( (string)ob->query_skill_mapped("blade")!="fanliangyi-dao")
                        return notify_fail(ob->query("name")+"±ÿ–Î π”√∑¥¡Ω“«µ∂∑®°£\n");

        }

//get the average array skill of the team
        n=0;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                n+=(int)ob->query_skill("fanliangyi-dao",1);
        }
        n/=2;

//get the difference of the array skill,
//first get the max and mix skill level of the array
        max=member[0]->query_skill("fanliangyi-dao",1);
        min=max;
        for (i=0;i<j;i++)
        {
                skill=member[i]->query_skill("fanliangyi-dao",1);
                if(skill>max)
                        max=skill;
                else if(skill<min)
                        min=skill;
        }

//and the leader is important
        n += leader->query_skill("fanliangyi-dao", 1) * 5;
        n /= max - min + 1;
        for (i=0;i<j;i++)
        {
                ob=member[i];
                ob->set_temp("no_quit",1);

                ob->set_temp("array/name","fanliangyi-dao");
                ob->set_temp("array/level",n);

                ob->add_temp("apply/attack",n);
                ob->add_temp("apply/defense", n);
                ob->add_temp("apply/damage",n);
                ob->add_temp("apply/armor", n);
        }
        message_vision( HIG "$N¬ ¡Ï$N’æ∂®¡Ω“«∑ΩŒª£¨∂Ÿ ±¡Ω»À÷Æº‰œ‘µ√ªÎ»ªÃÏ≥…°¢∫¡Œ
ﬁ∆∆’¿°£\n" NOR, leader);
        return 1;
}

int dismiss_array(object person)
{
        int i,j,n;
        object *member,ob;

        member = person->query_team();
        j=sizeof(member);
        n=person->query_temp("array/level");
        for (i=0;i<j;i++)
        {
                ob=member[i];
                ob->delete_temp("array");
                ob->add_temp("apply/attack",-n);
                ob->add_temp("apply/damage",-n);
                ob->add_temp("apply/defense",-n);
                ob->add_temp("apply/armor", -n);
                tell_object(ob,"µ∂’ÛΩ‚…¢¡À\n");
        }
}

//if the leader kills enemy, then all members in the array kill enemy
int array_kill(object leader, object enemy)
{
        object *member, ob;
        int i,j;
        member=leader->query_team();
        j=sizeof(member);

        for(i=0;i<j;i++) {
                ob=member[i];
                ob->kill_ob(enemy);
        }

        return 1;
}

int effective_level() { return 10;}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("ƒ„µƒƒ⁄¡¶≤ªπª°£\n");
        if ((int)me->query_skill("zixia-shengong", 1) < 10)
                return notify_fail("ƒ„µƒ°∏◊œœº…Òπ¶°πª∫ÚÃ´«≥°£\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 120 + random(50), 
                "attack": 60 + random(10), 
                "dodge" : 60 + random(10), 
                "parry" : 60 + random(10), 
                "damage_type" : "∏Ó…À", 
        ]); 
}

int practice_skill(object me)
{
        object weapon;

        if( !me->query_skill("zixia-shengong", 1))
                return notify_fail("¡∑°∏∑¥¡Ω“«µ∂∑®°π±ÿ–Î“™“‘°∏◊œœº…Òπ¶°πŒ™ª˘¥°°£\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("ƒ„ π”√µƒŒ‰∆˜≤ª∂‘°£\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("ƒ„µƒÃÂ¡¶≤ªπª¡∑°∏∑¥¡Ω“«µ∂∑®°π°£\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("ƒ„µƒƒ⁄¡¶≤ªπª°£\n");

        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fanliangyi-dao/" + action;
}


