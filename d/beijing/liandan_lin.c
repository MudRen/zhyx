#include <ansi.h> 
inherit ROOM;

int do_cai(string arg);

void init()
{
        add_action("do_cai", "cai");
}

int do_cai(string arg)
{
        object me = this_player();
        
        

        if ((int)me->query_temp("caiyao") < 1)
                return notify_fail("别在这浪费时间了，快走吧。\n");

        if (! arg || arg != "yao")
                return notify_fail("你要采什么。\n");

        if (me->is_busy())
                return notify_fail("慢慢找，先别急。\n");
       
        if ((int)me->query("jing") < 40)
                return notify_fail("你太累了，休息下吧。\n");

        if ((int)me->query("qi") < 40)
                return notify_fail("你太累了，休息下吧。\n");

        if ((int)me->query_temp("caiyao") == 2)
                return notify_fail("东西到手，快去交了吧。\n");

        message_vision(HIC "\n$N" HIC "趴在地上，瞪大了眼睛在草丛中找寻"
                       "着药草，生怕漏掉了目标。\n" NOR, me); 
        me->start_call_out((: call_other, __FILE__, "cai", me :), 3);
        me->start_busy(4); 
        return 1;
}
 
void cai(object me)
{ 
        object ob;
        object ob1;
        int skill, n;
        
        if( sscanf(file_name(environment(me)), "/d/beijing/liandan_lin%d", n) != 1)
                return;

        if (! objectp(me) || ! living(me) || me->is_fighting())
                return;

        skill = (int)me->query_skill("bencao-changshi", 1);

        if (random(8) == 1)
        {
                tell_room(environment(me), HIR "\n草丛中一阵晃动，突然钻出一条"
                                           "毒蛇。\n\n" NOR );
                ob = new("/clone/beast/dushe");
                ob->move(environment(me));
                ob->kill_ob(me);
        } else
        if (random(10) == 1 &&
           (string)me->query("family/family_name") != "五毒教")
        {
                tell_room(environment(me), HIR "\n突然间林子后面一阵晃动，跳"
                                           "出一个凶神恶刹的男子，手提一把短"
                                           "刀向你扑来！\n" NOR + CYN "毒郎中"
                                           "狞笑道：嘿嘿，今天真不巧，让你撞"
                                           "见了本爷，本爷今天要财要命。\n\n" NOR);
                ob = new("/d/beijing/npc/liandan_langzhong");
                ob->move(environment(me));
                ob->kill_ob(me);
        } else
        if (random(skill) > 70)
        {
                ob1 = new("/d/beijing/npc/dan/caoyao");
                ob1->move(me, 1);
                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                me->set_temp("caiyao", 2);
                message_vision(HIW "$N" HIW "精通百草之道，一眼就发现其中一株"
                               "草苗与众不同，小心翼翼地将它掘了出来。\n" NOR, me);
                me->improve_skill("bencao-changshi", me->query("int") / 4 + 1);
                tell_object(me, HIC "在采药过程中你的「本草常识」提高了！\n" NOR);
        } else
        if (random(10) > 5)
        {
                me->receive_damage("jing", 10 + random(20));
                me->receive_damage("qi", 10 + random(20));   
                message_vision(CYN "一翻摸索后，草丛中似乎没有$N" CYN 
                               "要找的东西，$N" CYN "失望的叹了口气。\n"
                               NOR, me);
        } else
        { 
                ob1 = new("/d/beijing/npc/dan/caoyao");
                ob1->move(me, 1);
                me->receive_damage("jing", 10 + random(20));
                me->receive_damage("qi", 10 + random(20));
                me->set_temp("caiyao", 2);
                message_vision(HIG "$N" HIG "找了半天，终于发现其中一株草苗与其"
                               "它的草略有不同，小心翼翼地掘了出来。\n" NOR, me);
                me->improve_skill("bencao-changshi", me->query("int") / 4 + 1);
                tell_object(me, HIC "在采药过程中你的「本草常识」提高了！\n" NOR);
        }
}
