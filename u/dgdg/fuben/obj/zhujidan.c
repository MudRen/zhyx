// zhujidan.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "������" NOR, ({ "zhuji dan", "zhuji", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIM "һ�����з��Ƶľ����浤���������񻰰�Ĺ�Ч����˵����֮��\n"
                                "��ƽ����ʮ��Ĺ���,����ҩ���ʺ�������������ʹ��\n" NOR);
                set("value", 10);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
      me=this_player();
      //  int effect;
     //   int neili;

       if (me->query("combat_exp")>800000)
       	{
       	message_vision(HIY "���Ѿ���������Ժ�Ҫ���Լ�Ŭ�������ˡ�\n" NOR, me);
       	return 1;
       	}

        	me->add("combat_exp", 100000 + random(50000));
        	me->add("potential", 30000);
            me->improve_neili(500);
          message_vision(HIY "��ľ��������ˣ����Ǳ�������ˣ�������������ˣ�\n" NOR, me); 
          
           
   /*     	mapsk = me->query_skill_mapped("force");
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
*/
    destruct(this_object());
        return 1;    	
        
	}
        


int query_autoload()
{
        return 1;
}