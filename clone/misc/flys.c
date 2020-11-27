#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_fly","flyup");
}

void create()
{
       set_name("���а�", ({ "fly bag", "flybag", "bag" }) );
       set_weight(10);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "��");
               set("long", "����һ���������õķ��а�,�������flyup�����ٷ��С�\n");
               set("no_get", 1);
               set("no_put", 1);
               set("no_drop", 1);
 }
       setup();
}

int do_fly( )
{
  object ob, myenv, where;
  ob = this_player () ;
  if (ob->is_busy())
  return notify_fail("��������æ���ء�\n");
  if (ob->is_fighting() )
  return notify_fail("���޷���ս����ʹ�÷��а���\n");
      if(!ob->query("bonr"))
  return notify_fail("�㻹û�����ɸ�ƨ��\n");


  if (ob->query("age") < 16)
  {
        where = environment(ob);
        if((string)where->short()==HIR"��ʮ�˲����"NOR)
                return notify_fail("�������治��ʹ�÷��а���\n");

        if (file_name(where)[0..5] == "/d/pk/" || where->query("no_ride") 
              || file_name(where)[0..11] == "/d/zhuanshi/" ) 
                return notify_fail("���ﲻ��ʹ�÷��а���\n");   
        
        message_vision(HIC"$N�����˷��а�,$N����������\n"NOR,ob);
        message_vision(HIC"$N�ɰ���,���˺ܳ�ʱ�����ڷɵ��˸߿�......\n"NOR, ob);
        ob->add("jing",ob->quer("max_jing"));
        ob->add("qi",ob->quer("max_qi"));
        myenv = environment (ob) ;
        ob->move ("/clone/misc/tian");
        return 1;
  }
  else  
  message_vision("ֻ��16�����£����ڰ�ȫ�ش�"HIR"<��׼ս���ĵط�>"HIR"����ʹ�÷��а�!!\n"NOR,ob);
  return 1;
}
void owner_is_killed() {

        write(HIY"ֻ����ǰ���һ��...������.....\n"NOR);
        destruct(this_object());
}

