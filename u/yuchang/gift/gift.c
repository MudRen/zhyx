// /d/city/obj/gift.c
#include <ansi.h>
#define LAST_PAR "sorry"
#define THIS_PAR "sorrysf"
#define GIFT_NAME "���˰�"	
inherit ITEM;
void create()
{
    set_name(HIR + GIFT_NAME + NOR, ({"gift","liwu"}));
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
        set("long", @LONG
������������������������������������������������	
��                                            �� 	
��  �л�Ӣ�ۣ�������ʦ��                      �� 	
��                                            �� 	
��       ������������ף����WANFU ALL          ��                	
��                                            �� 	
��            ϣ�����ǵ����������!           ��        	
��                                            �� 	
��                                            �� 	
��                                 YUCHANG    �� 	
��                                            �� 	
������������������������������������������������	
ZHYX ��ʦ��һ��С���⣬���(chai)��������ʲô��	
LONG
);
    set("value", 0);
    set("no_give",1);
    set("no_get",1);
    set("no_put",1);
    set("no_drop",1);
  }
    setup();
}
void init()
{
    add_action("do_chai", "chai");
}
int do_chai(string arg)
{
     object me = this_player();


  if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
  if (me->query(THIS_PAR + "_chai",1)) 
	{
	  destruct(this_object());
	  return notify_fail("һ��Ư������ӰͻȻ��һ�������г���,һ��ץ�������е����,����ͷ���˰��죺��ѽ~����Ѿ��ù��˰�~����͵��Ŷ~!!��˵��ת������.\n");
		
		
	}
       me->add("max_neili", 500);
       me->add("max_jingli", 500);  
       me->add("per", 3);
       me->add("kar", 3);


      tell_object(me,HIC "��С������Ĳ��������ֻ��һ������������ʱ����ԼԼ�е��Լ���������һЩ�仯��\n" NOR);

//ɾ���ϴ����������ɵĲ��������ӱ��β�����ȷ��ÿλ���ֻ����һ�Ρ�
      me->delete(LAST_PAR + "_chai");
      me->set(THIS_PAR + "_chai",1);
     destruct(this_object());
	 return 1;
}
void owner_is_killed() { destruct(this_object()); }
int query_autoload() { return 1; }
