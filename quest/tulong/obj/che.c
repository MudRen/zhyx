inherit ITEM;

void create()
{
        set_name("�ڳ�", ({ "biaoche" }) );
        set_weight(1500000);
        set_max_encumbrance(6);        set("no_get",1);
        set("no_magic", 1);
        set("no_fight", 1);
         if( clonep() )
                set_default_object(__FILE__);
        else{ 
                set("unit", "��");
                set("long", "һ����ľ�ڳ�������һ����ӣ�����д�š������ھ֡��ĸ����֡�\n");
                set("value", 0);
              }
}       
      
void init()
{
        add_action("do_drive", "drive");
}

int do_drive(string arg)
{
        object me, ob; 
   me = this_player();
   ob = this_object();

   if( me->is_busy())
      return notify_fail("����һ��������û����ɣ����������ڳ���\n");
   if( arg=="w"){
    me->command("west");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="e"){
    me->command("east");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="s"){
    me->command("south");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="n"){
    me->command("north");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="ne"){
    me->command("northeast");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="nw"){
    me->command("northwest");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="sw"){
    me->command("southwest");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }     
   if( arg=="se"){
    me->command("southeast");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="d"){
    me->command("down");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="nd"){
    me->command("northdown");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="sd"){
    me->command("southdown");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="wd"){
    me->command("westdown");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="ed"){
    me->command("eastdown");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    } 
   if( arg=="u"){
    me->command("up");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="su"){
    me->command("southup");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="nu"){
    me->command("northup");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="wu"){
    me->command("westup");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    }
   if( arg=="eu"){
    me->command("eastup");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="out"){
    me->command("out");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    }
   if( arg=="enter"){
    me->command("enter");
    ob->move(environment(me));
    message_vision("�ڳ�¡¡��ʻ�˹�����\n",me);
    return 1;
    } 
  return notify_fail("û���������\n"); 
}

int is_container() { return 1; }

