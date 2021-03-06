// wang.c 玉女忘情心诀
// looo/2001/6/23
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);



int exert(object me, object target)
{
        string msg;
		string picture;

		string *pictures=({
  HIY"少思、"YEL"少念、"HIC"少欲、"HIR"少事、"HIB"少语、"MAG"少笑"HIW,
  YEL"少愁、"CYN"少乐、"HIG"少喜、"HIR"少怒、"HIY"少好、"RED"少恶"HIW,
  HIC"多思"HIG"则"HIW"神怠，"HIB"多念"MAG"则"HIY"精散"HIW,
  HIR"多欲"YEL"则"BLU"智损，"MAG"多事"RED"则"HIG"形疲"HIW,
  HIB"多语"CYN"则"RED"气促，"HIR"多笑"HIC"则"BLU"肝伤"HIW,
  MAG"多愁"YEL"则"HIR"心慑，"RED"多乐"BLU"则"HIY"意溢"HIW,
  HIW"多喜"HIG"则"HIY"忘错"MAG"昏乱，"HIC"多怒"HIR"则"HIB"百脉"HIG"不定"HIW,
  HIG"多好"RED"则"BLU"专迷"HIG"不治，"HIW"多恶"HIB"则"MAG"焦煎"CYN"无宁"HIW
});

        int skill;

        if( target != me )
                return notify_fail("你只能提升自己的战斗力。\n");

		if (userp(me) && ! me->query("can_perform/yunv-xinjing/wang"))
                return notify_fail("你所学的内功中没有这种功能。\n");


        if (me->query("gender") == "男性")
                return notify_fail("女儿家的心事你怎能明白？\n");


        if (me->query("neili") < 200)
                return notify_fail("你的真气不够。\n");

        if (me->query_temp("wang"))
                return notify_fail("你已经进入「"HIW"忘情"NOR"」的境界了。\n");

        if (me->query_skill("yunv-xinjing",1) < 200)

                return notify_fail("你的玉女心经还不够精熟。\n");

        
       skill = (int) ( me->query_skill("force") + me->query("per") * 20 ) / 5;
       

       picture = pictures[random(sizeof(pictures))];

       message_vision(HIW "$N" HIW "蓦然回首，忧郁眼神淡如清水，心中默念「"+picture+ "」的玉女心经的要诀，不觉间进入忘情境界。\n" NOR, me);
                      
        me->add_temp("apply/sword", skill); 

        me->set_temp("wang", 1);
        me->add("neili", -100);

		me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

		if( me->is_fighting() ) me->start_busy(2);       

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("wang"))
        {
                me->add_temp("apply/sword", -amount);

                me->delete_temp("wang");
                tell_object(me, "一阵心痛，又勾起了你伤心的往事，忘情之意顿消.\n");
        }
}
