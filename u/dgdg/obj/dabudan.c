
//�󲹵�(��20��Ǳ��)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�󲹵�" NOR, ({ "da budan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���ǵĴ󲹵�,ζ��һ��������ϧÿ��ֻ�ܳ����š�\n" NOR);
                set("unit", "��");
                set("value", 10);
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
	string mapsk;	 
        object me; 
        me = this_player();         
        
        if ( ! arg || (arg != "da budan" &&
             arg != "dan") )
        return 0;
        
        if (me->query("gift2009/newyear/eat") >= 3 )
        {
            write(HIR"���Ѿ���ó�����̲����ٳ���ȥ���»����ը����!\n"NOR);
            return 1;
        }

        message_vision(HIW "$N" HIW "�������ɣ��ó��󲹵��������һ�ɰ���������ͷ������\n" NOR, me);
        me->add("combat_exp", 200000);
        me->add("potential",200000);

        	mapsk = me->query_skill_mapped("parry");
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("parry"))
                	me->improve_skill("parry", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);

        	mapsk = me->query_skill_mapped("dodge");
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);
          if (me->can_improve_skill("dodge"))
                	me->improve_skill("dodge", 1500000);
        	if (stringp(mapsk) && me->can_improve_skill(mapsk))
                	me->improve_skill(mapsk, 1500000);	
	    

        tell_object(me, HIG"��ϲ�������˶�ʮ��㾭���Ǳ�ܡ�"
                    "�����������Ṧ�м�ˮƽ���˴����ߣ�\n"NOR);
        me->add("gift2009/newyear/eat", 1);
        destruct(this_object());
        return 1;    
}

