// ����lywin 2000/8/27

#include <ansi.h>
inherit ITEM;  

string *kuang1=({__DIR__"tong-kuang",__DIR__"tie-kuang"});
string *kuang2=({__DIR__"tong-kuang",__DIR__"tie-kuang",__DIR__"yin-kuang"});
string *kuang3=({__DIR__"tong-kuang",__DIR__"tie-kuang",__DIR__"yin-kuang",__DIR__"jin-kuang"});
string *kuang4=({__DIR__"tong-kuang",__DIR__"tie-kuang",__DIR__"yin-kuang",__DIR__"jin-kuang",__DIR__"xuantie-kuang"});
string *kuang5=({__DIR__"tong-kuang",__DIR__"tie-kuang",__DIR__"yin-kuang",__DIR__"jin-kuang",__DIR__"xuantie-kuang",__DIR__"hantie-kuang1"});
string *kuang6=({__DIR__"tong-kuang",__DIR__"tie-kuang",__DIR__"yin-kuang",__DIR__"jin-kuang",__DIR__"xuantie-kuang",__DIR__"hantie-kuang1",__DIR__"hantie-kuang2"});

void init()
{
        add_action("do_wakuang", "wakuang");
}


void create() 
{
        set_name("����",({"kuang mai", "mai"}));
        set_weight(500000000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("no_drop","��Ҫ�Ҷ����ⶫ������ʹ��\n");
                set("no_put",1);
                set("no_get:",1);
                set("long", "����һ���ܺõĿ�����������ã�wakuang�����������������Ρ�\n");
             }
        setup();
}

int do_wakuang()
{
        object me=this_player();

        if( me->is_busy() ) return notify_fail("�����ں�æ�������ڣ�\n");
        if ((me->query("jing") < 100))
        {  
          tell_object(me,"��ľ���״̬�����ʺ���ô���ص��Ͷ���\n");
          return 1;
        }
        else
        if ((me->query("qi") < 200 ))
        {
          tell_object(me,"�����������������ǿ׳�������ڿ�ʯ��\n");
          return 1;
        }

        message_vision(HIC"$N�Ӷ����俪ʼ�ڵ�������������\n"NOR,me);
        me->add("jing",-100);
        me->add("qi",-150);
        me->add("combat_exp",40+random(20));
        me->add("potential",20+random(5));
        me->start_busy(10+random(5));
        
        remove_call_out("wakuang"); 
        call_out("wakuang",5,me);

        return 1;
}

int wakuang(object me)
{
      object ob;
      object ob1;        

      if (random(5)<3)
      {
          message_vision(CYN"һ���ھ�֮��$NʲôҲû�ڵ���\n"NOR,me);;
          return 1;
      }
      else
      if ((int)me->query("work/wakuang") > 600 )
        {
           message_vision(HIR"$N�������ڿ�����������ȥ����һ������ҳ�һ��ÿ�ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang6[random(7)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }
       else
      if ((int)me->query("work/wakuang") > 500 )
        {
           message_vision(HIY"$N�������ڿ�����������ȥ����һ������ҳ�һ��ÿ�ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang5[random(6)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }
       else
      if ((int)me->query("work/wakuang") > 400 )
        {
           message_vision(HIY"$N�������ڿ�����������ȥ����һ������ҳ�һ��ÿ�ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang4[random(5)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }       
       else
      if ((int)me->query("work/wakuang") > 300 )
        {
           message_vision(HIY"$N�ڿ����з�����ȥ���ҳ�һ��ÿ�ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang3[random(4)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }
       else
      if ((int)me->query("work/wakuang") > 200 )
        {
           message_vision(HIY"$N�ڿ�����������ȥ���þò��ҳ�һ���ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang2[random(3)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }
       else
      if ((int)me->query("work/wakuang") > 100 )
        {
           message_vision(HIY"$N�ڿ�����������ȥ���ò������ҳ�һ���ʯ��\n"NOR,me); 
           me->add("work/wakuang",1);
           ob=new(kuang1[random(2)]);
           ob->move(me);
           destruct(this_object());
           return 1;
       }
      else
      { 
        message_vision(HIG"$N���˰��죬���ڷ�������һ��ʯͷ�ǿ�ʯ��\n"NOR,me); 
        me->add("work/wakuang",1);
        ob1 = new( __DIR__ "tong-kuang");
        ob1->move(me);
        destruct(this_object());
      }
      return 1;
}

