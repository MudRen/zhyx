
//��һ�����ɿ��� (����force,force,dodge,parry)����1��


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "��һ�ɿ���" NOR, ({ "qiao keli", "chocolate" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��һ�ɿ���������ܼ�һ����\n" NOR);
                set("unit", "��");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_eat","eat");
        }
                

int do_eat( string arg )
{       
        if (arg == "qiao keli" || arg == "chocolate" )

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/wuyi2005/eat") )
        {write(HIR"�������һ���Ѿ��Թ�������ѽ��\n"NOR);return 1;}

        message_vision(HIY "$N���ɿ���һ�����ˣ��������ӡ�˳����Ǿ����˳�����\n" +
                                "��һ��������˵:��ζ���ü���Ӵ������������һ��!\n" NOR, me);

         log_file("static/wuyi", sprintf("%s(%s) eat �ɿ��� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        me->set("liwu/wuyi2005/eat", 1);

         me->add("combat_exp", 50000);
         mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                destruct(this_object());
                return 1;
        }
else {  return 0;}
}
                
