// �Ϲ�ʮ������֮ ������
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + MAG "������" NOR, ({ "fuxi qin", "fuxi", "qin" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", NOR + MAG "����һ�ѿ�����ͨ�Ĺ��٣���˵���Ϲŷ�����\n"
                                      "���á�\n"
                                      "����(tan)��ɻָ����о��������������쳣״̬��\n" 
                                      "��Ҫ���ټ���һ�ټ���tan ? �鿴ʹ�ô�����\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_tan", "tan"); 
}

int do_tan(string arg)
{
        object me;
        mapping my;
        
        me = this_player();
        
        if(! objectp(present("fuxi qin", me)))return 0;

        if (arg == "?")
        {
        	 write(HIG "ʹ�ô��� " + this_object()->query("count") + "/3\n" NOR);
        	 return 1;
        }
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");

        message_sort(NOR + MAG + "\n$N" NOR + MAG "��ϥ����������ز�Ū�ŷ����٣�"
                                 "���������������������$N" NOR + MAG "ֻ��������"
                                 "��̩֮����\n" NOR, me);

        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"];
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();
        me->clear_condition();
        me->save();
        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 3)
        {
        	write(HIW "ֻ����һ����죬�����������ˡ�\n" NOR);
        	destruct(this_object());	
        }

        return 1;
}
